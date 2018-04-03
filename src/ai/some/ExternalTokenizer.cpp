#define _WIN32_WINNT 0x0502

#include <lem/logfile.h>
#include <lem/solarix/dictionary.h>
#include <lem/xml_parser.h>
#include <lem/solarix/sentencebroker.h>

using namespace lem;
using namespace Solarix;

ExternalTokenizer::ExternalTokenizer(
    const lem::Path &dll_path,
    const lem::Path &data_path,
    const lem::UFString &params,
    const Solarix::Dictionary &dict,
    int language
)
    : SentenceTokenizer(dict, language)
{
    hSegmenter = NULL;

    //MessageBoxW( NULL, L"DEBUG 1", dll_path.GetUnicode().c_str(), MB_OK );

    lem::Path p(dll_path);

    if (lem::LogFile::IsOpen())
    {
        lem::LogFile::logfile->printf("ExternalTokenizer dll_path=%us\n", dll_path.GetUnicode().c_str());
    }

    if (p.DoesExist())
    {
        dll.Load(p, false);
    }
    else
    {
        UFString dllfn(dll_path.GetUnicode());

        lem::UFString ext(lem::Path::GetExtDelimiter());
        ext += lem::Process::Dll::StdExtension();

        if (lem::right(dllfn, 4) != ext)
        {
            dllfn += lem::Path::GetExtDelimiter();
            dllfn += lem::Process::Dll::StdExtension();
        }

        p = lem::Path(dllfn).GetAbsolutePath();

        if (p.DoesExist())
        {
            dll.Load(p, false);
        }
    }


    // --- DEBUG
    /*
    wchar_t cwd[1000];
    GetCurrentDirectoryW( 1000, cwd );
    MessageBoxW( NULL, cwd, L"GetCurrentDirectoryW", MB_OK );

    GetDllDirectoryW( 1000, cwd );
    MessageBoxW( NULL, cwd, L"GetDllDirectoryW", MB_OK );
    */
    // --- DEBUG


    if (!dll.IsLoaded())
    {
        lem::MemFormatter mem;

        if (!p.DoesExist())
        {
            mem.printf("Can not load segmenter [%us] - the file path does not exists or is not accessible", p.GetUnicode().c_str());
        }
        else
        {
            mem.printf("Can not load segmenter [%us], error message=%us", p.GetUnicode().c_str(), dll.Error());
        }

        lem::UFString err(mem.string());
        throw E_BaseException(err);
    }

    constructor_ptr = (constructor_func)dll.Import("Constructor");
    destructor_ptr = (destructor_func)dll.Import("Destructor");

    get_property_ptr = (get_property_func)dll.Import("GetSolarixPluginProperty");
    set_property_ptr = (set_property_func)dll.Import("SetSolarixPluginProperty");

    segmentation_ptr = (segmentation_func)dll.Import("Segmentation");
    // syntacticanalysis_ptr = (syntacticanalysis_func)dll.Import("SyntacticAnalysis");
    free_ptr = (free_func)dll.Import("SegmenterFreeString");

    get_error_ptr = (get_error_func)dll.Import("GetError");
    get_error_text_ptr = (get_error_text_func)dll.Import("GetErrorText");

    /*
     if( syntacticanalysis_ptr==NULL )
      {
       lem::MemFormatter mem;
       mem.printf( "Can not import function 'SyntacticAnalysis' from [%us]", dll.GetFilename().GetUnicode().c_str() );
       throw lem::E_BaseException( mem.string() );
      }
    */

    if (constructor_ptr != nullptr)
    {
        hSegmenter = constructor_ptr(data_path.GetUnicode().c_str(), params.c_str());

        if (hSegmenter == nullptr)
        {
            lem::MemFormatter mem;
            mem.printf("Can not initialize segmenter [%us], error=%us"
                , dll.GetFilename().GetUnicode().c_str(), GetErrorText().c_str());
            throw lem::E_BaseException(mem.string());
        }

        const wchar_t *s = get_property_ptr(hSegmenter, 10, -1);
        if (s != NULL && wcscmp(s, L"classes") == 0)
            can_define_classes = true;
    }
    else
    {
        lem::MemFormatter mem;
        mem.printf("Can not initialize segmenter [%us]", dll.GetFilename().GetUnicode().c_str());
        throw lem::E_BaseException(mem.string());
    }

    return;
}




ExternalTokenizer::~ExternalTokenizer(void)
{
    if (hSegmenter != nullptr)
    {
        LEM_CHECKIT_Z(destructor_ptr != nullptr);
        destructor_ptr(hSegmenter);
        hSegmenter = nullptr;
    }
}

bool ExternalTokenizer::IsTokenDelimiter(wchar_t c) const
{
    return false;
}

bool ExternalTokenizer::IsUnbreakableFront(wchar_t c) const
{
    return false;
}

bool ExternalTokenizer::IsUnbreakableFront(const lem::UCString &s) const
{
    return false;
}

bool ExternalTokenizer::IsMatched(const lem::UCString &s) const
{
    return false;
}

int ExternalTokenizer::MatchLen(const lem::UFString & s, int i0) const
{
    return 0;
}

void ExternalTokenizer::Tokenize(
    const Solarix::Dictionary &dict,
    const lem::UFString &s,
    lem::MCollect<UCString> &words,
    lem::PtrCollect<lem::UFString> &classes,
    std::map< int, lem::UFString > & tokenizer_flags,
    LA_PreprocessorTrace *trace
) const
{
    LEM_CHECKIT_Z(segmentation_ptr != nullptr && free_ptr != nullptr);

    if (segmentation_ptr == nullptr)
    {
        lem::MemFormatter mem;
        mem.printf("Segmenter has not been loaded from [%us]", dll.GetFilename().GetUnicode().c_str());
        throw E_BaseException(mem.string());
    }

    if (!s.empty())
    {
        wchar_t *res = nullptr;

        if (can_define_classes)
        {
            // Внешний сегментатор умеет для каждого выделенного слова указать его
            // часть речи. Для этого будем получать результаты сегментации в XML формате.
            res = segmentation_ptr(hSegmenter, s.c_str(), 0, 1);

            if (get_error_ptr(hSegmenter) != 0)
            {
                throw lem::E_BaseException(GetErrorText());
            }

            if (res != nullptr)
            {
                lem::Xml::Parser xml;
                FString utf8(to_utf8(res));
                xml.Load(lem::Ptr<Stream>(new lem::MemReadStream(utf8.c_str())));

                const lem::Xml::Node *tokens = xml.Find_By_Path(L"tokens");
                if (tokens != nullptr)
                {
                    for (lem::Xml::ConstIterator it(tokens, L"token"); !it.eof(); it++)
                    {
                        const lem::Xml::Node & token = *it;

                        UFString lexem = token.Get_By_Path(L"lexem");
                        words.push_back(lexem.c_str());

                        UFString sclasses;
                        const lem::Xml::Node *cls = token.Find_By_Path(L"class");
                        if (cls != nullptr)
                        {
                            sclasses = cls->GetBody();
                        }

                        classes.push_back(new UFString(sclasses));
                    }
                }
            }


        }
        else
        {
            // Внешний сегментатор умеет только разбивать на слова.
            res = segmentation_ptr(hSegmenter, s.c_str(), L'\b', 0);

            UFString s2(res);

            int i0 = 0;
            while (i0 < s2.length())
            {
                int i1 = s2.search_from(L'\b', i0);
                if (i1 == UNKNOWN)
                    i1 = s2.length();

                const int wlen = i1 - i0;
                if (wlen > 0)
                {
                    const wchar_t *substr = s2.c_str() + i0;
                    UCString word;
                    for (int i = 0; i < wlen; i++)
                    {
                        word += substr[i];
                    }

                    if (!word.empty())
                        words.push_back(word);
                }

                i0 = i1 + 1;
            }
        }

        free_ptr(hSegmenter, res);
    }

    return;
}


lem::UFString ExternalTokenizer::GetErrorText(void) const
{
    lem::UFString res;

    if (get_error_ptr(hSegmenter) != 0)
    {
        int len = get_error_text_ptr(hSegmenter, nullptr, 0);
        wchar_t *buf = new wchar_t[len];
        get_error_text_ptr(hSegmenter, buf, len);
        res = buf;
        delete[] buf;
    }

    return res;
}

/*
bool ExternalTokenizer::SyntaxTreeEdges(
                                        const Solarix::Dictionary &dict,
                                        const lem::UFString &s,
                                        lem::MCollect< lem::triple<int,int,int> > &edges
                                       ) const
{
 wchar_t * xml = syntacticanalysis_ptr( hSegmenter,s.c_str(), 0, 1 );

 if( xml!=NULL )
  {
   lem::Xml::Parser parser;
   parser.LoadString(xml);

   const lem::Xml::Node *nx = parser.Find_By_Path(L"edges/edge");
   if( nx!=NULL )
    {
     const lem::MCollect<lem::Xml::Node*> & ex = nx->GetNodes();
     for( lem::Container::size_type i=0; i<ex.size(); ++i )
      {
       const lem::Xml::Node &edge = *ex[i];
       lem::UFString str_from_node = edge.GetAttr( L"from_node" );
       lem::UFString str_to_node = edge.GetAttr( L"to_node" );
       lem::UFString str_type = edge.GetAttr( L"edge_type" );

       lem::triple<int,int,int> t;
       t.first = lem::to_int( str_from_node );
       t.second = lem::to_int( str_to_node );
       t.third = lem::to_int( str_type );

       edges.push_back( t );
      }
    }

   free_ptr(hSegmenter,xml);
   return true;
  }
 else
  {
   return false;
  }
}
*/
