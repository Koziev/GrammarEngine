#include <lem/startup.h>
#include "ConsoleParser.h"


int main(int argc, char *argv[])
{
    lem::LemInit initer;

    bool show_usage = argc==1;
    for (int i = 1; i < argc; ++i)
    {
        if (argv[i][0] == '?' ||
            (argv[i][0] == '-' || argv[i][0] == '/') && (strcmp(argv[i]+1, "help")==0 || strcmp(argv[i]+1,"h")==0 || argv[i][1] == '?'))
        {
            show_usage = true;
            break;
        }
    }

    if (show_usage)
    {
        lem::mout->printf("Usage: parser [-lemmatizer LEMMATIZER] [-tagger TAGGER] [-parser PARSER] [-lang LANGUAGE] [-v] [-eol] [-emit_morph 0|1] [-render_tree 0|1] [-d <dictionary_path>] -i <input_text_file> [-o <output_xml_file>]\n\n");
        lem::mout->printf("LEMMATIZER:\n    -1 none (default)\n    0  part-of-speech based lemmatizer\n\n");
        lem::mout->printf("TAGGER:\n    -1 no part-of-speech tagging\n    0  CRF-based model (default)\n\n");
        lem::mout->printf("PARSER:\n    -1 none (default)\n    0  fast shift-reduce bottom-up parser\n    1  slow top-down Earley parser\n    2  chunker\n\n");
        lem::mout->printf("LANGUAGE:\n russian | english\n\n");
        lem::mout->printf("Other options:\n");
        lem::mout->printf("    -emit_morph 0|1   do print morphological tags in output xml (performance degradation if possible), default=1\n");
        lem::mout->printf("    -eol              each line in input file contains a sentence\n");
        lem::mout->printf("    -v                be verbose\n");
        lem::mout->printf("    -render_tree      do print dependency trees\n");
        lem::mout->printf("    -fuzzy_wordrecog  0|1  do allow fuzzy recognition of words, default=0\n");
        lem::mout->printf("    -beam 20          beam size for top-down syntax parser, 20 is default value\n");

        lem::mout->printf("\nExamples:\n");
        lem::mout->printf("parser -verbose -eol -d ../ru/dictionary.xml -i ../input/input.txt -o ../output/output.xml");

        return 0;
    }


    ConsoleParser parser_engine;
    try
    {
        parser_engine.Run(argc, argv);
    }
    catch (const lem::E_BaseException & e)
    {
        lem::merr->printf("Error:\n%us", e.what());
        return 1;
    }
    catch (std::exception & e)
    {
        lem::merr->printf("Error:\n%s", e.what());
        return 1;
    }
    catch (...)
    {
        lem::merr->printf("Undefined error");
        return 1;
    }

    return 0;
}
