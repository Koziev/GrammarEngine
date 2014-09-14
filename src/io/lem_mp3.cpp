#include <lem/conversions.h>
#include <lem/mp3.h>


using namespace lem;
using namespace lem::File_Factory;

// list of genres
static char* g_arrMP3Genre[] =
{
 "Blues","Classic Rock","Country","Dance","Disco","Funk","Grunge","Hip-Hop",
 "Jazz","Metal","New Age","Oldies","Other","Pop","R&B","Rap","Reggae","Rock",
 "Techno","Industrial","Alternative","Ska","Death Metal","Pranks","Soundtrack",
 "Euro-Techno","Ambient","Trip Hop","Vocal","Jazz Funk","Fusion","Trance",
 "Classical","Instrumental","Acid","House","Game","Sound Clip","Gospel","Noise",
 "Alternative Rock","Bass","Soul","Punk","Space","Meditative","Instrumental Pop",
 "Instrumental Rock","Ethnic","Gothic","Darkwave","Techno-Industrial","Electronic",
 "Pop Folk","Eurodance","Dream","Southern Rock","Comedy","Cult","Gangsta","Top 40",
 "Christian Rap","Pop Funk","Jungle","Native American","Cabaret","New Wave",
 "Psychadelic","Rave","ShowTunes","Trailer","Lo-Fi","Tribal","Acid Punk","Acid Jazz",
 "Polka","Retro","Musical","Rock & Roll","Hard Rock","Folk","Folk Rock",
 "National Folk","Swing","Fast Fusion","Bebob","Latin","Revival","Celtic",
 "Bluegrass","Avantgarde","Gothic Rock","Progressive Rock","Psychedelic Rock",
 "Symphonic Rock","Slow Rock","Big Band","Chorus","Easy Listening","Acoustic",
 "Humour","Speech","Chanson","Opera","Chamber Music","Sonata","Symphony","Booty Bass",
 "Primus","Porn Groove","Satire","Slow Jam","Club","Tango","Samba","Folklore","Ballad",
 "Power Ballad","Rhytmic Soul","Freestyle","Duet","Punk Rock","Drum Solo","A Capella",
 "Euro House","Dance Hall","Goa","Drum & Bass","Club House","Hardcore","Terror",
 "Indie","BritPop","Negerpunk","Polsk Punk","Beat","Christian Gangsta Rap",
 "Heavy Metal","Black Metal","Crossover","Contemporary Christian","Christian Rock",
 "Merengue","Salsa","Trash Metal","Anime","JPop","SynthPop"
};

static int g_nMP3GenreCount = 148;

// matrix of bitrates [based on MPEG version data][bitrate index]
static int g_nMP3BitRate[6][16] =
{
 {0,32,64,96,128,160,192,224,256,288,320,352,384,416,448,-1},
 {0,32,48,56, 64, 80, 96,112,128,160,192,224,256,320,384,-1},
 {0,32,40,48, 56, 64, 80, 96,112,128,160,192,224,256,320,-1},
 {0,32,48,56, 64, 80, 96,112,128,144,160,176,192,224,256,-1},
 {0, 8,16,24, 32, 40, 48, 56, 64, 80, 96,112,128,144,160,-1},
 {0, 8,16,24, 32, 64, 80, 56, 64,128,160,112,128,256,320,-1},
};


CMP3Info::CMP3Info(void)
{
 Clear();
}

// helper functions
bool CMP3Info::GetNextFrameHeader(
                                  Stream &bin,
                                  MP3FRAMEHEADER* pHeader,
                                  int nPassBytes
                                 )
{
 memset( pHeader, 0, sizeof(*pHeader) );
 if( nPassBytes>0 )
  bin.seekp( nPassBytes, SEEK_CUR );

 int n = 0;
 DWORD dwNumBytesRead;
 do
  {
   dwNumBytesRead = bin.read( pHeader, 4 );
   ChangeEndian(pHeader,4); // convert from big-endian to little-endian

   // only search in 10kb
   if(
      dwNumBytesRead != 4 ||
      pHeader->framesync == 0x7FF ||
      ++n > 10000
     )
    break;

   bin.seekp( -3, SEEK_CUR );
  }
 while(1);

 return pHeader->framesync == 0x7FF;
}


// operations
bool CMP3Info::Open( Stream &bin )
{
 Clear(); // make sure all data is blank

 int nNextSearch = 0;

 MP3FRAMEHEADER sFrameHeader;
 memset(&sFrameHeader,0,sizeof(sFrameHeader));

 int nFrameBR=0;
 double dLength = 0; // total length of file
 ULONG nTotalBR = 0; // total frames bit rate (used to calc. average)
 DWORD dwNumBytesRead=0;

 // read frame by frame
 while( GetNextFrameHeader( bin,&sFrameHeader,nNextSearch) )
  {
   if (m_nFrames < 1)
    {
     // first read the MPEG version
     switch (sFrameHeader.mpegver)
     {
      case 0: m_enMPEGVersion = MPEGVER_25; break;
      case 1: m_enMPEGVersion = MPEGVER_NA; break;
      case 2: m_enMPEGVersion = MPEGVER_2; break;
      case 3: m_enMPEGVersion = MPEGVER_1; break;
     }

     // next, read the MPEG layer description
     switch (sFrameHeader.mpeglayer)
     {
      case 0: m_nMPEGLayer = 0; break;
      case 1: m_nMPEGLayer = 3; break;
      case 2: m_nMPEGLayer = 2; break;
      case 3: m_nMPEGLayer = 1; break;
     }

     // read the bit for CRC or no CRC
     m_bHasCRC = sFrameHeader.hascrc;
    }

   // read the bitrate, based on the mpeg layer and version
   if( m_nMPEGLayer > 0 )
    {
     if( m_enMPEGVersion == MPEGVER_1 )
      {
       switch(m_nMPEGLayer)
       {
        case 1: nFrameBR = g_nMP3BitRate[0][sFrameHeader.bitrate]; break;
        case 2: nFrameBR = g_nMP3BitRate[1][sFrameHeader.bitrate]; break;
        case 3: nFrameBR = g_nMP3BitRate[2][sFrameHeader.bitrate]; break;
       }
      }
     else
      {
       switch (m_nMPEGLayer)
       {
        case 1: nFrameBR = g_nMP3BitRate[3][sFrameHeader.bitrate]; break;
        case 2: nFrameBR = g_nMP3BitRate[4][sFrameHeader.bitrate]; break;
        case 3: nFrameBR = g_nMP3BitRate[5][sFrameHeader.bitrate]; break;
       }
      }
    }

   // if nFrameBR is 0 or -1 then the bitrate is either free or bad
   if(nFrameBR > 0)
    nTotalBR += nFrameBR;

   // read sample rate
   if(m_enMPEGVersion == MPEGVER_1)
    switch(sFrameHeader.samplerate)
    {
     case 0: m_nSampleRate = 44100; break;
     case 1: m_nSampleRate = 48000; break;
     case 2: m_nSampleRate = 32000; break;
    }
   else if (m_enMPEGVersion == MPEGVER_2)
    switch(sFrameHeader.samplerate)
    {
     case 0: m_nSampleRate = 22050; break;
     case 1: m_nSampleRate = 24000; break;
     case 2: m_nSampleRate = 16000; break;
    }
   else if(m_enMPEGVersion == MPEGVER_25)
    switch(sFrameHeader.samplerate)
    {
     case 0: m_nSampleRate = 11025; break;
     case 1: m_nSampleRate = 12000; break;
     case 2: m_nSampleRate = 8000; break;
    }

   if(!m_nSampleRate)
    break;

   // read channel mode
   switch(sFrameHeader.chanmode)
   {
    case 0: m_enChannelMode = MP3CM_STEREO; break;
    case 1: m_enChannelMode = MP3CM_JOINT_STEREO; break;
    case 2: m_enChannelMode = MP3CM_DUAL_CHANNEL; break;
    case 3: m_enChannelMode = MP3CM_SINGLE_CHANNEL; break;
   }

   // read the copyright and original bits
   m_bCopyrighted = sFrameHeader.copyright;
   m_bOriginal = sFrameHeader.original;

   // read the emphasis
   switch (sFrameHeader.emphasis)
   {
    case 0: m_enEmphasis = MP3EM_NONE; break;
    case 1: m_enEmphasis = MP3EM_50_15_MS; break;
    case 2: m_enEmphasis = MP3EM_RESERVED; break;
    case 3: m_enEmphasis = MP3EM_CCIT_J17; break;
   }

   // don't read the CRC -- maybe in a future version
   // nNextSearch = frame length, in bytes
   if(m_nMPEGLayer == 1)
    nNextSearch = (12000 * nFrameBR / m_nSampleRate + sFrameHeader.padding) * 4;
   else
    nNextSearch = 144000 * nFrameBR / m_nSampleRate + sFrameHeader.padding;

   nNextSearch -= 4; // the frame header was already read

   m_nFrames++;

   // calculate the length in seconds of this frame and add it to total
   if(nFrameBR)
    dLength += (double)(nNextSearch + 4) * 8 / (nFrameBR * 1000);
  }

 // if at least one frame was read, the MP3 is considered valid
 if(m_nFrames > 0)
  {
   m_dwValidity |= MP3VLD_DATA_VALID;
   m_nBitRate = nTotalBR / m_nFrames; // average the bitrate
   m_nLength = (int)dLength;
  }

 // read the ID3 tag

 // set up a structure for reading the ID3 version 1 tag
 MP3ID3V1TAG sID3V1;

 bin.seekp( -128, SEEK_END );
 dwNumBytesRead = bin.read( &sID3V1, 128 );

 if( dwNumBytesRead == 128 && memcmp(sID3V1.ident,"TAG",3) == 0)
  {
   char strTemp[31]; strTemp[30] = 0; // make a temporary null-terminated buffer

   memcpy(strTemp,sID3V1.title,30);  m_strTitle  = strTemp; m_strTitle.trim();
   memcpy(strTemp,sID3V1.artist,30); m_strArtist = strTemp; m_strArtist.trim();
   memcpy(strTemp,sID3V1.album,30);  m_strAlbum  = strTemp; m_strAlbum.trim();

   strTemp[4] = 0; memcpy(strTemp,sID3V1.year,4); m_strYear = strTemp; m_strYear.trim();

   // now, depending on the reserved byte, the comment is 28 bytes or 30 bytes
   if(sID3V1.reserved)
    {
     // NOTE: even if sID3V1.album is of size 28, the reserved and tracknum
     // are right after, so they'll be included in the comment, which is what
     // we want
     memcpy(strTemp,sID3V1.comment,30); m_strComment = strTemp; m_strComment.trim();
    }
   else
    {
     memcpy(strTemp,sID3V1.comment,28); m_strComment = strTemp; m_strComment.trim();
     m_nTrack = sID3V1.tracknum;
     m_nGenre = sID3V1.genre;
    }

   m_dwValidity |= MP3VLD_ID3V1_VALID;
  }

 return true;
}


void CMP3Info::Clear()
{
 m_dwValidity = MP3VLD_INVALID;

 m_nTrack = 0;
 m_nGenre = 255;

 m_nFrames = 0;
 m_nLength = 0;
 m_enMPEGVersion = MPEGVER_NA;
 m_nMPEGLayer = 0;
 m_bHasCRC = FALSE;
 m_nBitRate = 0;
 m_nSampleRate = 0;
 m_enChannelMode = MP3CM_STEREO;
 m_enEmphasis = MP3EM_NONE;
 m_bCopyrighted = FALSE;
 m_bOriginal = FALSE;
}

// functions
FString CMP3Info::GetGenreString(int nIndex)
{
 if( nIndex > g_nMP3GenreCount )
  return "";
	
 return g_arrMP3Genre[nIndex];
}

FString CMP3Info::GetLengthString(int nSeconds)
{
 int nMin = nSeconds / 60;
 int nSec = nSeconds % 60;

 FString str;
 str = to_str(nMin).c_str();
 str += ":";
 str += to_str(nSec).c_str();

 return str;
}


// helper functions
void CMP3Info::ChangeEndian(void* pBuffer, int nBufSize)
{
 if(!pBuffer || !nBufSize)
  return;

 char temp;
 for( int i = 0; i<nBufSize/2; i++ )
  {
   temp = ((char*)pBuffer)[i];
   ((char*)pBuffer)[i] = ((char*)pBuffer)[nBufSize - i - 1];
   ((char*)pBuffer)[nBufSize - i - 1] = temp;
  }

 return;
}
