#include <windows.h>
#include <math.h>
#include <lem/keyboard.h>
#include <lem/startup.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/_sg_api.h>
#include <lem/solarix/WordLinkEnumerator.h>
#include <lem/solarix/ThesaurusStorage.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/PartOfSpeech.h>
#include <lem/solarix/PartsOfSpeech.h>
#include <lem/solarix/Thesaurus.h>
#include <lem/solarix/RenderThesaurusDiagram.h>

using namespace lem;
using namespace Solarix;


static UCString MakeCasing( const Solarix::Dictionary &dict, int ie )
{
 const Solarix::SG_Entry &e = dict.GetSynGram().GetEntry(ie);

 UCString w( lem::to_lower(e.GetName()) );

 bool use_casing=true;
 const int iclass=e.GetClass();
 if( !lem::is_quantor(iclass) )
  {
   if( dict.GetSynGram().GetClass(iclass).GetName().eqi(L"UnknownEntries") )
    use_casing=false; 
  }

 if( use_casing )
  {
   const int casing = e.GetAttrState( Solarix::GramCoordAdr( CharCasing ) );
   if( casing==FIRST_CAPITALIZED_CASED )
    w.to_Aa();
   else if( casing==EACH_LEXEM_CAPITALIZED_CASED )
    Solarix::MakeEachLexemAa(w);
   else if( casing==ALL_CAPITALIZED_CASED )
    w.to_upper();
   else
    w.to_lower();
   }

 return w;
}



struct DCluster
{
 lem::MCollect<UCString> words;
 lem::MCollect<int> iclass, ie;
 
 lem::zbool word0;
 lem::zint radius;

 lem::MCollect<DCluster*> link_cluster;
 lem::MCollect<int> link_type;

 lem::zint X,Y,w,h;

 bool MatchWords( const DCluster &x ) const
 {
  return ie==x.ie;
 }

 void Print( OFormatter &out ) const
 {
  for( lem::Container::size_type i=0; i<words.size(); ++i )
   {
    out.printf( "%us ", words[i].c_str() );
   }

  out.eol();  
  return;
 } 


 void Take( DCluster *src )
 {
  for( lem::Container::size_type i=0; i<src->ie.size(); ++i )
   {
    if( ie.find( src->ie[i] )==UNKNOWN )
     {
      words.push_back( src->words[i] );
      ie.push_back( src->ie[i] );
      iclass.push_back( src->iclass[i] ); 
     }
   }

  for( lem::Container::size_type i=0; i<src->link_cluster.size(); ++i )
   {
    bool found=false;
    for( lem::Container::size_type j=0; j<link_cluster.size(); ++j )
     {
      if( src->link_cluster[i] == link_cluster[j] )
       {
        found=true;
        break;
       }
     }

    if( !found )
     {
      link_cluster.push_back( src->link_cluster[i] );
      link_type.push_back( src->link_type[i] );
     }
   }

  return;
 }

 void ReplaceMerged( DCluster *oldc, DCluster *newc )
 {
  for( lem::Container::size_type j=0; j<link_cluster.size(); ++j )
   {
    if( oldc == link_cluster[j] )
     {
      link_cluster[j] = newc;
      break;
     }
   }

  return; 
 }
 

 bool IsLinkedTo( const DCluster *c ) const
 {
  for( lem::Container::size_type j=0; j<link_cluster.size(); ++j )
   {
    if( link_cluster[j] == c )
     return true;
   }

  return false;
 }

 
 void MergeLeafs( lem::PtrCollect<DCluster> & clusters )
 {
  // Сначала пусть укрупнятся ветки.
  for( lem::Container::size_type j=0; j<link_cluster.size(); ++j )
   link_cluster[j]->MergeLeafs(clusters);

  int i=0;
  while( i<CastSizeToInt(link_cluster.size()) )
   {
    DCluster *c1 = link_cluster[i];
    const int l1 = link_type[i];

    int j=i+1;
    while( j<CastSizeToInt(link_cluster.size()) )
     {
      const int l2 = link_type[j];
      if( l1==l2 )
       {
        DCluster *c2 = link_cluster[j];

        // Можем ли присоединить c2 к c1?
        bool can_merge=false;

        // 1. Если и у c1, и у c2 нет веток следующего уровня, и грамматические
        //    классы совпадают.
        if( c1->link_cluster.empty() && c2->link_cluster.empty() )
         {
          std::set<int> iclass1;
          for( lem::Container::size_type q=0; q<c1->iclass.size(); ++q )
           iclass1.insert( c1->iclass[q] );

          std::set<int> iclass2;
          for( lem::Container::size_type q=0; q<c2->iclass.size(); ++q )
           iclass2.insert( c1->iclass[q] );
          
          if( iclass1.size()==1 && iclass2.size()==1 && (*iclass1.begin())==(*iclass2.begin()) ) 
           can_merge = true;
         }
        else
         {
          // Либо набор связей полностью совпадает.
          can_merge = c1->link_type==c2->link_type;
          if( can_merge )
           {
            for( lem::Container::size_type q=0; q<c1->link_cluster.size(); ++q )
             {
              if( c1->link_cluster[q] != c2->link_cluster[q] )
               {
                can_merge = false;
                break;
               }
             }
           }
         }
                
        if( can_merge )
         {
          c1->Take(c2);
          
          for( lem::Container::size_type k=0; k<clusters.size(); ++k )
           {
            clusters[k]->ReplaceMerged(c2,c1);
           } 
         }  
       }
     } 
   }  

  return;
 }


 void FindLinks( SynGram &sg, lem::PtrCollect<DCluster> & clusters )
 {
  for( lem::Container::size_type j=0; j<words.size(); ++j )
   {
    const int ientry = ie[j];

    std::set<int> links_set;
    std::set< std::pair<int,int> > linked_type_ie;

    const int ekey1 = sg.GetEntry(ientry).GetKey();
    lem::Ptr<WordLinkEnumerator> links( sg.Get_Net().EnumerateWordLinks(ekey1) );

    while( links->Fetch() )
     {
      const int ekey2 = links->GetEntryKey2();

      const int l = links->GetLinkType();

      // Пропускаем гипонимы, так как они могут дать взрывной рост диаграммы
      if( l==MEMBER_link || l==CLASS_link )
       continue;
         
      const int ie2 = ekey2;//sg.FindEntryIndexByKey( ekey2 );

      if( ie.find(ie2)==UNKNOWN )
       {
        links_set.insert(l);
        linked_type_ie.insert( std::make_pair( l, ie2 ) );
       }
     }

    for( std::set< std::pair<int,int> >::const_iterator it=linked_type_ie.begin(); it!=linked_type_ie.end(); ++it )
     {
      DCluster * c = new DCluster;
      c->radius = radius+1;
      const int ie2 = it->second;
      const SG_Entry &e2 = sg.GetEntry(ie2);
      const int iclass2 = e2.GetClass();
      const UCString &ename2 = e2.GetName();    
      const UCString &class_name2 = sg.classes()[ iclass2 ].GetName();

      c->ie.push_back( ie2 );
      c->iclass.push_back( iclass2 );
      c->words.push_back( MakeCasing(sg.GetDict(),ie2) );

      bool found=false;
      for( lem::Container::size_type q=0; q<clusters.size(); ++q )
       {
        if( clusters[q]->MatchWords(*c) )
         {
          found=true;
 
          // если у него нет связи на нас...
          if( !clusters[q]->IsLinkedTo( this ) )
           {
            link_cluster.push_back(clusters[q]);
            link_type.push_back(it->first);
           }

          break;
         }
       }

      if( found )
       {
        lem_rub_off(c); 
       }
      else
       {
        mout->printf(
                     "%H Entry [%vfA%us%vn:%vfF%us%vn]: ientry=%vfE%d%vn key=%vfE%d%vn iclass=%vfE%d%vn\n"
                     , radius+1, class_name2.c_str(), ename2.c_str(), ie2, e2.GetKey(), iclass2
                    );

        clusters.push_back(c);
        link_cluster.push_back(c);
        link_type.push_back(it->first);

        // Строим сеть до радиуса 2 включительно.
        if( c->radius<2 )
         {
          c->FindLinks( sg, clusters );
         }
       } 
     }
   }

  return;
 }


 UFString GetText(void) const
 {
  UFString t;
  lem::MCollect<UCString> used;
  for( lem::Container::size_type i=0; i<words.size(); ++i )
   {
    if( used.find( words[i] )==UNKNOWN )
     {
      used.push_back(words[i]);

      if( !t.empty() )
       t += L"\r\n";

      t += words[i].c_str();
     }
   } 

  return t;
 }


 void CalculateRect( HDC hdc, HFONT fNormal, HFONT fBold )
 {
  UFString txt = GetText();

  if( word0 )
   SelectObject( hdc, fBold );
  else
   SelectObject( hdc, fNormal );


  RECT r;
  r.left=r.right=0; r.top=r.bottom=0;
  DrawTextW( hdc, txt.c_str(), txt.length(), &r, DT_CALCRECT | DT_TOP | DT_LEFT );

  w = r.right-r.left;
  h = r.bottom-r.top;

  w = w+10;
  h = h+10;

  return;
 }

 void Draw( HDC hdc, HFONT fNormal, HFONT fBold )
 {
  if( word0 )
   SelectObject( hdc, fBold );
  else
   SelectObject( hdc, fNormal );

  COLORREF clrBG=RGB(220,220,220);
  COLORREF clrBord=RGB(0,0,0);
  COLORREF clrTxt=RGB(0,0,0);

  if( word0 )
   {
    clrBG=RGB(255,186,186);
    clrBord=RGB(255,0,0);
    clrTxt=RGB(255,0,0);
   }


  HBRUSH hbr = CreateSolidBrush( clrBG );
  HPEN hp = CreatePen( PS_SOLID, 1, clrBord );
  HBRUSH hb2 = (HBRUSH)SelectObject( hdc, hbr );
  HPEN hp2 = (HPEN)SelectObject( hdc, hp );
  Rectangle( hdc, X-w/2, Y-h/2, X+w/2, Y+h/2 );
  SelectObject( hdc, hp2 );
  SelectObject( hdc, hb2 );
  DeleteObject( hbr );
  DeleteObject( hp );

  UFString txt = GetText();

  int old_mode = SetBkMode( hdc, TRANSPARENT );
  SetTextColor( hdc, clrTxt );

  RECT r;
  r.left=X-w/2;
  r.right=X+w/2;
  r.top=Y-h/2;
  r.bottom=Y+h/2;
  DrawTextW( hdc, txt.c_str(), txt.length(), &r, DT_CENTER | DT_VCENTER );

  SetBkMode( hdc, old_mode );

  return;
 }

 void DrawLinks( HDC hdc )
 {
  for( lem::Container::size_type j=0; j<link_cluster.size(); ++j )
   {
    DCluster *c2 = link_cluster[j];
    int ilink = link_type[j];

    COLORREF pclr;
    int pw=1;
    int pstyle=PS_DOT;

    int dist = abs(radius-c2->radius);
    if( radius==0 && dist==1 )
     {
      pstyle=PS_SOLID;
      pw=2;
      pclr = RGB(0,0,0);
     }
    else if( dist==1 )
     {
      pstyle=PS_DOT;
      pw=1;
      pclr = RGB(150,150,150);
     }
    else
     {
      pstyle=PS_DOT;
      pw=1;
      pclr = RGB(230,230,230);
     }
        
    HPEN hp = CreatePen( pstyle, 1, pclr );
    HPEN hp2 = (HPEN)SelectObject( hdc, hp );
    MoveToEx( hdc, X, Y, NULL );
    LineTo( hdc, c2->X, c2->Y ); 

    SelectObject( hdc, hp2 );
    DeleteObject( hp );
   }

  return;
 }


 void PrintLinks( OFormatter &html )
 {
  for( lem::Container::size_type j=0; j<link_cluster.size(); ++j )
   {
    DCluster *c2 = link_cluster[j];
    int ilink = link_type[j];

    int dist = abs(radius-c2->radius);
    if( dist==0 )
     {
     }
    else if( dist==1 )
     {
     }
    else
     {
     }
        
    html.printf( "<v:line from=\"%d,%d\" to=\"%d,%d\"></v:line>"
     , X.value, Y.value, c2->X.value, c2->Y.value ); 
   }

  return;
 }


 void PrintVML( OFormatter &out ) const
 {
  UFString txt = GetText();
  int left=X-w/2, top=Y-h/2;

  if( word0 )
   {
    out.printf(
               "<v:rect "
               "fillcolor=#FFCC99 "
               "style=\"position:absolute;top:%d;left:%d;width:%d;height:%d\">\n"
               "</v:rect>\n",
               top, left, w.value, h.value
            );
   }
  else
   {
    out.printf(
               "<v:rect "
               "fillcolor=#EEEEFF "
               "style=\"position:absolute;top:%d;left:%d;width:%d;height:%d\">\n"
               "</v:rect>\n",
               top, left, w.value, h.value
            );
   }

  out.printf(
             "<div style=\"position:absolute;top:%d;left:%d;width:%d;height:%d;align:center;margin:5\">\n",
             top, left, w.value, h.value
            );

  out.printf( "<font size=1>" );

  if( word0 )
   {
    out.printf(
               "<b><a href=\"#ie%d\" style=\"text-decoration: none;color: rgb(255,0,0)\">%us</a></b>\n",
               ie.front(),
               txt.c_str()
              );
   }
  else
   {
    out.printf(
               "<a href=\"#ie%d\" style=\"text-decoration: none\">%us</a>\n",
               ie.front(),
               txt.c_str()
              );
   }

  out.printf( "</font>" );

  out.printf( "</div>\n" );

  return;
 } 

};


static bool r1_sorter( const std::pair<DCluster*,double> &x, const std::pair<DCluster*,double> &y )
{
 return x.second > y.second;
}

static bool r2_sorter( const std::pair<DCluster*,double> &x, const std::pair<DCluster*,double> &y )
{
 return x.second < y.second;
}



static void WriteBMPFile(HBITMAP bitmap, const wchar_t * filename, HDC hDC)
{
 BITMAP bmp;
 PBITMAPINFO pbmi;
 WORD cClrBits;
 HANDLE hf; // file handle
 BITMAPFILEHEADER hdr; // bitmap file-header
 PBITMAPINFOHEADER pbih; // bitmap info-header
 LPBYTE lpBits; // memory pointer
 DWORD dwTotal; // total count of bytes
 DWORD cb; // incremental count of bytes
 BYTE *hp; // byte pointer
 DWORD dwTmp;

 // create the bitmapinfo header information

 GetObject( bitmap, sizeof(BITMAP), (LPSTR)&bmp );

 // Convert the color format to a count of bits.
 cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel);
 if (cClrBits == 1)
  cClrBits = 1;
 else if (cClrBits <= 4)
  cClrBits = 4;
 else if (cClrBits <= 8)
  cClrBits = 8;
 else if (cClrBits <= 16)
  cClrBits = 16;
 else if (cClrBits <= 24)
  cClrBits = 24;
 else cClrBits = 32;
 
 // Allocate memory for the BITMAPINFO structure.
 if (cClrBits != 24)
  pbmi = (PBITMAPINFO) LocalAlloc(LPTR, sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * (1<< cClrBits));
 else
  pbmi = (PBITMAPINFO) LocalAlloc(LPTR, sizeof(BITMAPINFOHEADER));

 // Initialize the fields in the BITMAPINFO structure.
 pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
 pbmi->bmiHeader.biWidth = bmp.bmWidth;
 pbmi->bmiHeader.biHeight = bmp.bmHeight;
 pbmi->bmiHeader.biPlanes = bmp.bmPlanes;
 pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel;
 if (cClrBits < 24)
  pbmi->bmiHeader.biClrUsed = (1<<cClrBits);

 // If the bitmap is not compressed, set the BI_RGB flag.
 pbmi->bmiHeader.biCompression = BI_RGB;

 // Compute the number of bytes in the array of color
 // indices and store the result in biSizeImage.
 pbmi->bmiHeader.biSizeImage = (pbmi->bmiHeader.biWidth + 7) /8 * pbmi->bmiHeader.biHeight * cClrBits;
 // Set biClrImportant to 0, indicating that all of the
 // device colors are important.
 pbmi->bmiHeader.biClrImportant = 0;

 // now open file and save the data
 pbih = (PBITMAPINFOHEADER) pbmi;
 lpBits = (LPBYTE) GlobalAlloc( GMEM_FIXED, pbih->biSizeImage );

 if(!lpBits)
  {
   printf("writeBMP::Could not allocate memory");
   return;
  }

 // Retrieve the color table (RGBQUAD array) and the bits
 if(!GetDIBits(hDC, HBITMAP(bitmap), 0, (WORD) pbih->biHeight, lpBits, pbmi, DIB_RGB_COLORS))
  {
   printf("writeBMP::GetDIB error");
   return;
  }

// Create the .BMP file.
hf = CreateFileW(filename, GENERIC_READ | GENERIC_WRITE, (DWORD) 0,
NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,
(HANDLE) NULL);
if (hf == INVALID_HANDLE_VALUE){
printf("Could not create file for writing");
return;
}

hdr.bfType = 0x4d42; // 0x42 = "B" 0x4d = "M"
// Compute the size of the entire file.
hdr.bfSize = (DWORD) (sizeof(BITMAPFILEHEADER) +
pbih->biSize + pbih->biClrUsed
* sizeof(RGBQUAD) + pbih->biSizeImage);
hdr.bfReserved1 = 0;
hdr.bfReserved2 = 0;

// Compute the offset to the array of color indices.
hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) +
pbih->biSize + pbih->biClrUsed
* sizeof (RGBQUAD);

// Copy the BITMAPFILEHEADER into the .BMP file.
if (!WriteFile(hf, (LPVOID) &hdr, sizeof(BITMAPFILEHEADER),
(LPDWORD) &dwTmp, NULL)) {
printf("Could not write in to file");
return;
}

// Copy the BITMAPINFOHEADER and RGBQUAD array into the file.
if (!WriteFile(hf, (LPVOID) pbih, sizeof(BITMAPINFOHEADER)
+ pbih->biClrUsed * sizeof (RGBQUAD),
(LPDWORD) &dwTmp, ( NULL))){
printf("Could not write in to file");
return;
}


// Copy the array of color indices into the .BMP file.
dwTotal = cb = pbih->biSizeImage;
hp = lpBits;
if (!WriteFile(hf, (LPSTR) hp, (int) cb, (LPDWORD) &dwTmp,NULL)){
printf("Could not write in to file");
return;
}

// Close the .BMP file.
if (!CloseHandle(hf)){
printf("Could not close file");
return;
}

 // Free memory.
 GlobalFree((HGLOBAL)lpBits);
 LocalFree(pbmi);
 return;
}

void Solarix::RenderThesaurusDiagram(
                                     Solarix::Dictionary &dict,
                                     const int ientry,
                                     lem::Path &html_file,
                                     lem::PtrCollect<lem::Path> &aux_files
                                    )
{
 lem::MCollect<int> ies;
 ies.push_back(ientry);
 RenderThesaurusDiagram( dict, ies, html_file, aux_files );
 return;
}


void Solarix::RenderThesaurusDiagram(
                                     Solarix::Dictionary &dict,
                                     const lem::MCollect<int> &ies,
                                     lem::Path &html_file,
                                     lem::PtrCollect<lem::Path> &aux_files
                                    )
{
 LexicalAutomat &la  = dict.GetLexAuto();
 SynGram &sg = dict.GetSynGram();

 const SG_Entry &e = sg.GetEntry( ies.front() );
 const int iclass = e.GetClass();
 const UCString &class_name = sg.classes()[ iclass ].GetName();

 html_file = lem::Path::GetTmpFilename("html");

 lem::PtrCollect<DCluster> clusters;

 DCluster *org = new DCluster;
 org->word0 = true;

 for( lem::Container::size_type i=0; i<ies.size(); ++i )
  {
   org->words.push_back( MakeCasing(dict,ies[i]) );

   const SG_Entry &ex = sg.GetEntry( ies[i] );
   const int iclassx = e.GetClass();

   org->iclass.push_back(iclassx);
   org->ie.push_back(ies[i]);
  }

 clusters.push_back(org);
     
 org->FindLinks( sg, clusters );

 #if LEM_DEBUGGING==1 && defined LEM_CONSOLE
 mout->printf( "There are %d clusters\n", CastSizeToInt( clusters.size() ) );
 for( int r=0; r<3; ++r )
  {
   mout->printf( "\nRadius %d\n", r );
   for( lem::Container::size_type i=0; i<clusters.size(); ++i )
    if( clusters[i]->radius==r )
     {
      clusters[i]->Print( *mout );
     }
  }
 #endif

 // В отдельных векторах сформируем вектор кластеров на каждом радиусе
 lem::MCollect< std::pair<DCluster*,double> > r1_clusters, r2_clusters;

 // первый радиус
 for( lem::Container::size_type i=0; i<clusters.size(); ++i )
  {
   if( clusters[i]->radius==1 )
    r1_clusters.push_back( std::make_pair(clusters[i], double(CastSizeToInt(clusters[i]->link_cluster.size())) ) );
  }

 // Отсортируем кластеры на первом радиусе по убыванию кол-ва исходящих связей
 std::sort( r1_clusters.begin(), r1_clusters.end(), r1_sorter );

 #if LEM_DEBUGGING==1 && defined LEM_CONSOLE
/*
     mout->printf( "\n\nRADIUS 1:\n" );
     for( lem::Container::size_type i=0; i<r1_clusters.size(); ++i )
      {
       r1_clusters[i].first->Print( *mout );
       mout->printf( "w=%f\n", r1_clusters[i].second );
      }
*/
 #endif

 // второй радиус
 for( lem::Container::size_type i=0; i<clusters.size(); ++i )
  {
   if( clusters[i]->radius==2 )
    {
     // Среднее арифметическое позиций первого радиуса, которые ссылаются на данный кластер.
     double n1=0, v1=0;
     for( lem::Container::size_type j=0; j<r1_clusters.size(); ++j )
      {
       if( r1_clusters[j].first->radius==1 && r1_clusters[j].first->IsLinkedTo(clusters[i]) )
        {
         n1+=1.0;
         v1+=j;
        }
      }

     double av = n1==0 ? 0.0 : v1/n1;

     r2_clusters.push_back( std::make_pair(clusters[i],av) );
    }
  }

 std::sort( r2_clusters.begin(), r2_clusters.end(), r2_sorter );

 #if LEM_DEBUGGING==1 && defined LEM_CONSOLE
 mout->printf( "\n\nRADIUS 2:\n" );
 for( lem::Container::size_type i=0; i<r2_clusters.size(); ++i )
  {
   r2_clusters[i].first->Print( *mout );
   mout->printf( "w=%f\n", r2_clusters[i].second );
  }
 #endif

 // Get width and height of screen
 const int nWid = GetSystemMetrics(SM_CXSCREEN);
 const int nHt = GetSystemMetrics(SM_CYSCREEN);

 // Get a handle to the screen device context
 HDC hDesktopdc = GetWindowDC(HWND_DESKTOP);
 if(hDesktopdc)
  {
   // Create a compatible bitmap
   HBITMAP hScreenshot = CreateCompatibleBitmap(hDesktopdc,nWid,nHt);

   // Create compatible DC
   HDC hBitmapdc = CreateCompatibleDC(hDesktopdc);

   SetMapMode( hBitmapdc, MM_TEXT );

   const int Size = 12;
   const wchar_t *Facename = L"Arial"; 

   int h = -MulDiv( Size, GetDeviceCaps(hBitmapdc, LOGPIXELSY), 72);

   HFONT fNormal = CreateFontW(
                              h,
                              0,
                              0,
                              0,
                              400,
                              0,
                              0,
                              FALSE,
                              DEFAULT_CHARSET,
                              OUT_TT_PRECIS, // OUT_DEFAULT_PRECIS,
                              CLIP_TT_ALWAYS,
                              PROOF_QUALITY,
                              0,
                              Facename
                             );

   HFONT fBold = CreateFontW(
                              h,
                              0,
                              0,
                              0,
                              700,
                              0,
                              0,
                              FALSE,
                              DEFAULT_CHARSET,
                              OUT_TT_PRECIS, // OUT_DEFAULT_PRECIS,
                              CLIP_TT_ALWAYS,
                              PROOF_QUALITY,
                              0,
                              Facename
                             );

   if( fNormal==NULL || fBold==NULL )
    {
     printf( "Could not create font\n" );
     exit(1);
    }

   HFONT hf0 = (HFONT)SelectObject( hBitmapdc, fNormal );

   // Select Bitmap
   HBITMAP hOriginal = (HBITMAP)SelectObject( hBitmapdc, hScreenshot );

   // Сначала определим размеры прямоугольников под кластерами
   for( lem::Container::size_type i=0; i<clusters.size(); ++i )
    {
     clusters[i]->CalculateRect(hBitmapdc,fNormal,fBold);
    }


   SelectObject( hBitmapdc, hOriginal );
   DeleteObject(hScreenshot);

   // теперь определим общие размеры изображения.
   // Для этого надо определить размеры колец 1го и 2го радиусов, а также
   // размер центрального прямоуголника.
   const int r0 = std::max(org->w,org->h)/2;
   int sz1=0, sz2=0;
 
   for( lem::Container::size_type i=0; i<clusters.size(); ++i )
    if( clusters[i]->radius==1 )
     {
      int x = 1.4*std::max(clusters[i]->w,clusters[i]->h);
      sz1 = std::max( sz1, x );
     }  
    else if( clusters[i]->radius==2 )
     {
      int x = 1.4*std::max(clusters[i]->w,clusters[i]->h);
      sz2 = std::max( sz2, x );
     }  

   const int gap = 20;
   const int r1 = r0 + gap + sz1/2;
   const int r2 = r1 + 2*gap + sz2/2;

   const int field_sz = (r2+sz2/2)*2;
   HBITMAP hDiag = CreateCompatibleBitmap(hDesktopdc,field_sz,field_sz);
   hOriginal = (HBITMAP)SelectObject( hBitmapdc, hDiag );

   // Очистим белым цветом
   HBRUSH hbr = CreateSolidBrush( RGB(255,255,255) );
   HPEN hp = CreatePen( PS_NULL, 1, RGB(0,0,0) );
   HBRUSH hb2 = (HBRUSH)SelectObject( hBitmapdc, hbr );
   HPEN hp2 = (HPEN)SelectObject( hBitmapdc, hp );
   Rectangle( hBitmapdc, 0, 0, field_sz+1, field_sz+1 );
   SelectObject( hBitmapdc, hp2 );
   SelectObject( hBitmapdc, hb2 );
   DeleteObject( hbr );
   DeleteObject( hp );

   org->X = field_sz/2;
   org->Y = field_sz/2;

   OUFormatter html( html_file, false );
   html.printf(
               "<html xmlns:v=\"urn:schemas-microsoft-com:vml\">"
               "<meta content=\"text/html; charset=UTF-8\" http-equiv=\"content-type\">"
               "<style>v\\: * { behavior:url(#default#VML); display:inline-block }</style>"
               "<body>\n"
              );

   for( int ipass=0; ipass<2; ++ipass )
    {
     for( int r=1; r<=2; ++r )
      {
       const lem::MCollect< std::pair<DCluster*,double> > &rad = r==1 ? r1_clusters : r2_clusters;

       int n = CastSizeToInt(rad.size());
           
       double rr=0;
       if( r==1 )
        rr = r1;
       else if( r==2 )
        rr = r2; 

       double da = 6.28/n;
       double a = 0.0; //r==1 ? 0.0 : 0.6;

       if( r==2 && !r2_clusters.empty() )
        {
         double da2 = 6.28 / CastSizeToInt(r2_clusters.size());
         const int n0 = CastSizeToInt(r1_clusters.front().first->link_cluster.size());
         double minus_a = da2 * n0/2.0;
         a -= minus_a;
        }

       for( lem::Container::size_type i=0; i<rad.size(); ++i )
        {
         if( ipass==0 )
          { 
           int xc = field_sz/2 + rr*cos(a);
           int yc = field_sz/2 + rr*sin(a);

           rad[i].first->X = xc;
           rad[i].first->Y = yc;
          }
         else
          {
           //clusters[i]->Draw(hBitmapdc,fNormal,fBold);
          } 

         a += da;
        }
      }

     if( ipass==0 )
      {
       for( lem::Container::size_type i=0; i<clusters.size(); ++i )
        {
         DCluster *c1 = clusters[i];
         c1->DrawLinks(hBitmapdc);
         //c1->PrintLinks(html);
        }
      }
    }        

   org->Draw( hBitmapdc, fNormal, fBold );

   lem::Path diag=lem::Path::GetTmpFilename("bmp");
   aux_files.push_back( new lem::Path(diag) );

   // сохраняем нарисованную диаграмму
   WriteBMPFile( hDiag, diag.GetUnicode().c_str(), hBitmapdc );

   html.printf( 
               "<div style=\"position:absolute;top:0;left:0;width:%d;height:%d\">\n"
               "<img src=\"%us\">"
               "</div>\n", field_sz, field_sz, diag.GetUnicode().c_str()
              );
       
   for( lem::Container::size_type i=0; i<clusters.size(); ++i )
    {
     const DCluster *c = clusters[i];
     c->PrintVML(html);
    }

   html.printf( "</body></html>\n" );
   html.close();

   // финальная очистка
   SelectObject( hBitmapdc, hOriginal );
   DeleteObject( hDiag );

   SelectObject( hBitmapdc, hf0 );
   DeleteObject(fNormal);
   DeleteObject(fBold);

   DeleteDC(hBitmapdc);
   ReleaseDC(HWND_DESKTOP,hDesktopdc);
  }

 return;
} 

