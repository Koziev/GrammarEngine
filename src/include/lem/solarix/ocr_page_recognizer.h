#if !defined OCR_PAGE_RECOGNIZER__H
 #define OCR_PAGE_RECOGNIZER__H

#include <lem/console_streams.h>
#include <lem/xml_parser.h>
#include <lem/conversions.h>
#include <lem/system_config.h>
#include <lem/render/dc0.h>
#include <lem/render/bmp.h>
#include <lem/render/rgb.h>
#include <lem/solarix/ocr.h>

#include <lem/solarix/ocr_page_recognizer.h>


//#include ".\Ocrad\Common.h"
//#include ".\Ocrad\bitmap.h"


 namespace Solarix
 {
  namespace Ocr
  {
 
struct PixelChar
{
 double rel;
 wchar_t c;

 PixelChar(void) : rel(0), c(0) {}
};


struct PixelChars : lem::NonCopyable
{
 lem::PtrCollect<PixelChar> chars;

 PixelChars(void) {}

 void Add( wchar_t c, double r );

 wchar_t Best(void) const;
};



// **********************************************
// Текстовый блок - соответствует одному слову
// **********************************************
struct Text_Block : lem::NonCopyable
{
 lem::Render::Rect2di rect; // координаты блока на исходном изображении

 Text_Block(void) {}
 Text_Block( const lem::Render::Rect2di &x ) : rect(x) {}
};


// ************************************
// Группа блоков (слов) в одной строке
// ************************************
struct Text_Line
{
 int max_thickness; // максимальная толщина строки
 int min_y, max_y; // границы строки по Y 

 // блоки в составе строки
 std::map< int, const Text_Block* > blocks;
 lem::MCollect<const Text_Block*> block_list; 

 Text_Line(void);

 void AddBlock( const Text_Block* block );

 lem::Render::Rect2di GetBounds(void) const;
};





struct Text_Block_Recognition : lem::NonCopyable
{
 const Text_Block *block;
 lem::PtrCollect< lem::MCollect<double> > recog_traces;

 lem::Ptr_NC_Collect< PixelChars > pixel_chars;

 lem::UFString plain_text;


 Text_Block_Recognition(void) : block(NULL) {}

 void PrintTracesCSV( lem::OFormatter &aperture_csv ) const;

 lem::UFString GetPlainText(void) const;
};


// ********************************
// Распознаваемая страница
// ********************************
class TextPage
{
 public:
  lem::PtrCollect<Text_Block> blocks; // отдельные блоки (по 1 или больше символу)
  lem::PtrCollect<Text_Line> lines; // строки текста
  lem::zint avegare_line_h;

  // Результаты распознавания
  lem::PtrCollect<Text_Block_Recognition> block_recogs;
  std::map< const Text_Block*, Text_Block_Recognition* > text_block_res;

  TextPage(void);

  void AddBlock( Text_Block *block );
};


// ***************************************************************************
// Слои изображения - исходная картинка и различные слои с результатами
// анализа.
// ***************************************************************************
class PerceptionArea
{
 public:

 lem::Ptr<lem::Render::Image> bmp; // исходная картинка
 TextPage page; // Результат сегментации
 lem::Ptr<lem::FMatrix> image_matrix;
 lem::UFString yield_text; // Результат распознавания

 PerceptionArea(void) {}
 PerceptionArea( lem::Ptr<lem::Render::Image> img );

 bool LoadImage( const lem::Path &filename );
 void Segmentation(void);
 void ShowSegmentation( const lem::Path &folder );
};



class PageRecognizer
{
 private:
  lem::PtrCollect<LetterRecognizer> char_net;
  lem::MCollect< std::pair<int,int> > char_net_wh; // размеры загруженных распознавателей
  int n_outs; // общее число выходов всех распознавателей

  std::map<lem::UCString,lem::UCString> corrections; // подстановки слов для коррекции i-l-1
  lem::MCollect<lem::UCString> wordforms;
  void Correct( lem::UFString &str ) const; 
  bool FindWordform( lem::UFString &str ) const; 

  struct GroupInfo
  {
   int max_det_w, max_det_h;
   GroupInfo(void) : max_det_w(0), max_det_h(0) {}
  };

  void RecognizeBlock( PerceptionArea &area, const Text_Block *block );
  void Recognize( PerceptionArea &area );

 public:
  lem::zbool detach_on_dtor; // если в деструкторе нельзя удалять объекты в det_groups.
  lem::Ptr_NC_Collect<MaskDetectors> det_groups;
  lem::MCollect<GroupInfo> grp_info;

 public:
  lem::zbool use_ocrad;

  PageRecognizer(void);
  PageRecognizer( MaskDetectors & mask_detectors );
  ~PageRecognizer(void);

  void LoadNeuronet( const lem::Path &p );
  void LoadMasks( const lem::Path &p );
  void LoadXml( const lem::Path &p );
  void Recognize( PerceptionArea &area, const lem::Path &image_path );
  void ShowResults( PerceptionArea &area, const lem::Path &folder );
  void LoadCorrections( const lem::Path &corrections_path );
  void LoadWordforms( const lem::Path &wordforms_path );

  lem::UFString Recognize( lem::Ptr<lem::Render::Image> img );
  void PrepareArea( PerceptionArea &area );
  lem::UFString RecognizeArea( PerceptionArea &area );


  bool PointWord( lem::Path &filename, int Xc, int Yc, lem::Render::Rect2di & rect ) const;

};


struct DetectedFeature : lem::NonCopyable
{
 float v; // достоверность фиксации
 lem::MCollect<lem::Render::Point2di> hit_points;
 const Solarix::Ocr::FeatureDetector *detector;
 int xmin, xmax; 

 DetectedFeature(void);
};


static bool hit_sorter( const DetectedFeature *a, const DetectedFeature *b )
{
 return a->xmin < b->xmin;
}


struct DetectedFeatures : lem::NonCopyable
{
 int w,h; 
 lem::Ptr_NC_Collect<DetectedFeature> hits;
 lem::Ptr_NC_Collect< lem::MCollect<DetectedFeature*> > pixels;

 lem::MCollect< DetectedFeature* > final_hits; 

 DetectedFeatures( const lem::Render::Image *img );

 bool Add( DetectedFeature *x );

 void Sort(void);
};


  } // namespace Ocr
 } // namespace Solarix


#endif
