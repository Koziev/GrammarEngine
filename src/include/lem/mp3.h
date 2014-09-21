#ifndef LEM_MP3__H
#define LEM_MP3__H
#pragma once

 #include <lem/integer.h> 
 #include <lem/fstring.h>
 #include <lem/streams.h>
 
 namespace lem
 {
  namespace File_Factory
  {
   using lem::FString;

   // MP3FRAMEHEADER structure
   struct MP3FRAMEHEADER
   {
	unsigned emphasis : 2;			// M
	unsigned original : 1;			// L
	unsigned copyright : 1;			// K
	unsigned modeext : 2;			// J
	unsigned chanmode : 2;			// I
	unsigned privbit : 1;			// H
	unsigned padding : 1;			// G
	unsigned samplerate : 2;		// F
	unsigned bitrate : 4;			// E
	unsigned hascrc : 1;			// D
	unsigned mpeglayer : 2;			// C
	unsigned mpegver : 2;			// B
	unsigned framesync : 11;		// A
   };

   // MP3ID3V1TAG structure
   struct MP3ID3V1TAG
   {
	char ident[3]; // TAG
	char title[30];
	char artist[30];
	char album[30];
	char year[4];
	char comment[28];
	lem::uint8_t reserved;
	lem::uint8_t tracknum;
	lem::uint8_t genre;
   };

   // ENMPEGVER enumeration
   enum ENMPEGVER
   {
	MPEGVER_NA,		// reserved, N/A
	MPEGVER_25,		// 2.5
	MPEGVER_2,		// 2.0 (ISO/IEC 13818-3)
	MPEGVER_1		// 1.0 (ISO/IEC 11172-3)
   };

   // ENCHANNELMODE enumeration
   enum ENCHANNELMODE
   {
	MP3CM_STEREO,
	MP3CM_JOINT_STEREO,
	MP3CM_DUAL_CHANNEL,
	MP3CM_SINGLE_CHANNEL
   };

   // ENEMPHASIS enumeration
   enum ENEMPHASIS
   {
	MP3EM_NONE,
	MP3EM_50_15_MS,		// 50/15 ms
	MP3EM_RESERVED,
	MP3EM_CCIT_J17		// CCIT J.17
   };

   // bitmask of validity of files
   #define MP3VLD_INVALID     0x0000
   #define MP3VLD_ID3V1_VALID 0x0001
   #define MP3VLD_DATA_VALID  0x0002

   // CMP3Info class
   class CMP3Info
   {
    private:
     lem::uint32_t m_dwValidity;

     // MP3 frame information
     unsigned m_nFrames;
     unsigned m_nLength;					// in seconds
     ENMPEGVER m_enMPEGVersion;
     int m_nMPEGLayer;
     bool m_bHasCRC;
     int m_nBitRate;					// average if VBR, 0 if "free"
     int m_nSampleRate;
     ENCHANNELMODE m_enChannelMode;
     ENEMPHASIS m_enEmphasis;
     bool m_bCopyrighted;
     bool m_bOriginal;

    public:
     // ID3V1 information
     FString m_strArtist;
     FString m_strTitle;
     FString m_strAlbum;
     FString m_strComment;
     FString m_strYear;
     int m_nTrack;
     int m_nGenre;

    public:
     CMP3Info(void);

    // operations
    bool Open( lem::Stream &file );

	void Clear(void);

	DWORD GetValidity() const { return m_dwValidity; }

	const FString& GetArtist() const { return m_strArtist; }
	const FString& GetTitle() const { return m_strTitle; }
	const FString& GetAlbum() const { return m_strAlbum; }
	const FString& GetComment() const { return m_strComment; }
	const FString& GetYear() const { return m_strYear; }
	int GetTrack() const { return m_nTrack; }
	int GetGenreIndex() const { return m_nGenre; }

	unsigned GetNumFrames() const { return m_nFrames; }
	unsigned GetLength() const { return m_nLength; }
	ENMPEGVER GetMPEGVersion() const { return m_enMPEGVersion; }
	int GetMPEGLayer() const { return m_nMPEGLayer; }
	BOOL HasCRC() const { return m_bHasCRC; }
	int GetBitRate() const { return m_nBitRate; }
	int GetSampleRate() const { return m_nSampleRate; }
	ENCHANNELMODE GetChannelMode() const { return m_enChannelMode; }
	ENEMPHASIS GetEmphasis() const { return m_enEmphasis; }
	BOOL IsCopyrighted() const { return m_bCopyrighted; }
	BOOL IsOriginal() const { return m_bOriginal; }

    // functions
	static FString GetGenreString(int nIndex);
	static FString GetLengthString(int nSeconds);

    private:
    // helper functions
	bool GetNextFrameHeader( lem::Stream &bin, MP3FRAMEHEADER* pHeader, int nPassBytes = 0);
	void ChangeEndian(void* pBuffer, int nBufSize);
   };


 } // namespace 'File_Factory'

 } // namespace lem

#endif
