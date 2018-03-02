#include <stdio.h>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <boost/regex.hpp>

#include <lem/console_streams.h>
#include <lem/date_time.h>
#include <lem/xml_parser.h>
#include <lem/solarix/res_pack.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/PartOfSpeech.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/MorphologyModels.h>
#include <lem/solarix/print_variator.h>
#include <lem/solarix/la_autom.h>


#if defined LEM_WINDOWS
#include <windows.h>
#endif

#include "SentenceEOL.h"
#include "ParsingResults_XMLStream.h"
#include "ConsoleParser.h"

using namespace Solarix;


ConsoleParser::ConsoleParser() : ParserEngineBase()
{}


int ConsoleParser::Run(int argc, char * argv[])
{
    // По умолчанию предполагаем, что файл конфига словаря лежит в текущем каталоге.
    lem::Path dict_path("dictionary.xml");

    // если входной файл содержит список входных файлов и файлов результата (пакетный режим)
    bool input_is_joblist = false;
    lem::Path input_path;
    lem::Path out_path;
    int start_index = 0;
    int max_count = lem::int_max;

    bool emit_morph = false;
    bool render_tree = false;

    // По умолчанию парсер сегментирует входной текст на предложения с использованием
    // набора правил и эвристик. Если же предложения уже выделены и размещаются
    // на отдельных строках текстового файла, можно упростиь эту часть разбора, указав -eol
    bool eol = false;

    for (int i = 1; i < argc; ++i)
    {
        if (strlen(argv[i]) > 1 && argv[i][0] == '-')
        {
            const char * opt = argv[i] + 1;
            if (opt[0] == '-')
                opt = opt + 1;

            try
            {
                if (strcmp(opt, "dict") == 0)
                {
                    dict_path = lem::Path(argv[++i]);
                }
                else if (strcmp(opt, "start_index") == 0)
                {
                    start_index = lem::to_int(argv[++i]);
                }
                else if (strcmp(opt, "max_count") == 0)
                {
                    max_count = lem::to_int(argv[++i]);
                }
                else if (strcmp(opt, "output") == 0)
                {
                    out_path = lem::Path(argv[++i]);
                }
                else if (strcmp(opt, "lang") == 0)
                {
                    language_name = argv[++i];
                }
                else if (strcmp(opt, "input") == 0)
                {
                    input_path = lem::Path(argv[++i]);
                }
                else if (strcmp(opt, "beam") == 0)
                {
                    beam_size = lem::to_int(argv[++i]);
                }
                else if (strcmp(opt, "parser") == 0)
                {
                    parser_type = lem::to_int(argv[++i]);
                    if (parser_type < -1 || parser_type>2)
                    {
                        throw E_BaseException(lem::format_str("Unknown parser=%d, only [-1,0,1,2] are allowed", parser_type));
                    }
                }
                else if (strcmp(opt, "tagger") == 0)
                {
                    tagger_type = lem::to_int(argv[++i]);
                    if (tagger_type < -1 || tagger_type>1)
                    {
                        throw E_BaseException(lem::format_str("Unknown tagger_type=%d, only [-1,0] are allowed", tagger_type));
                    }
                }
                else if (strcmp(opt, "lemmatizer") == 0)
                {
                    lemmatizer_type = lem::to_int(argv[++i]);
                }
                else if (strcmp(opt, "render_tree") == 0)
                {
                    render_tree = lem::to_int(argv[++i]) == 1;
                }
                else if (strcmp(opt, "verbose") == 0)
                {
                    verbose = true;
                }
                else if (strcmp(opt, "eol") == 0)
                {
                    eol = true;
                }
                else if (strcmp(opt, "emit_morph") == 0)
                {
                    emit_morph = lem::to_int(argv[++i]) == 1;
                }
                else if (strcmp(opt, "fuzzy_wordrecog") == 0)
                {
                    allow_primary_fuzzy_word_recog = lem::to_int(argv[++i]) == 1;
                }
                else if (strcmp(opt, "d") == 0)
                {
                    dict_path = lem::Path(argv[++i]);
                }
                else if (strcmp(opt, "o") == 0)
                {
                    out_path = lem::Path(argv[++i]);
                }
                else if (strcmp(opt, "i") == 0)
                {
                    input_path = lem::Path(argv[++i]);
                }
                else if (strcmp(opt, "joblist") == 0)
                {
                    input_is_joblist = true;
                }
                else if (strcmp(opt, "v") == 0)
                {
                    verbose = true;
                }
                else
                {
                    throw E_BaseException(lem::format_str("Unknown option %s", argv[i]));
                }
            }
            catch (const E_BaseException & e)
            {
                throw E_BaseException(lem::format_str(L"Command line option %s parsing error: %ws", argv[i], e.what()));
            }
            catch (std::exception & e)
            {
                throw E_BaseException(lem::format_str("Command line option %s parsing error: %s", argv[i], e.what()));
            }
            catch (...)
            {
                throw E_BaseException(lem::format_str("Command line option %s parsing error", argv[i]));
            }
        }
        else if (input_path.empty())
        {
            input_path = lem::Path(argv[i]);
        }
        else
        {
            throw E_BaseException(lem::format_str("Unknown option [%s]", argv[i]));
        }
    }


    dict_path = dict_path.GetAbsolutePath();

    if (verbose)
    {
        lem::mout->printf("Loading dictionary from [%us]...\n", dict_path.GetUnicode().c_str());
    }
    LoadDictionary(dict_path);

    LoadModels(dict_path);

    std::vector< std::pair<lem::Path, lem::Path> > input_ouput_filenames;
    if (input_is_joblist)
    {
        lem::TextReader rdr(input_path);

        while (!rdr.eof())
        {
            lem::FString line = rdr.read_till_eol();

            int tab_pos = line.search('\t');
            if (tab_pos != -1)
            {
                lem::FString filepath1 = lem::trim(lem::left(line, tab_pos));
                lem::FString filepath2 = lem::trim(lem::right(line, line.length() - tab_pos - 1));

                input_ouput_filenames.push_back(std::make_pair(lem::Path(filepath1), lem::Path(filepath2)));
            }
        }
    }
    else
    {
        input_ouput_filenames.push_back(std::make_pair(input_path, out_path));
    }

    lem::ElapsedTime elapsed_time;
    elapsed_time.start();
    int counter = 0;
    bool print_progress = true;

    for (lem::Container::size_type ijob = 0; ijob < input_ouput_filenames.size(); ++ijob)
    {
        const lem::Path & input_path0 = input_ouput_filenames[ijob].first;
        const lem::Path & output_path0 = input_ouput_filenames[ijob].second;

        // ------------------------------------
        std::vector<lem::Path> filenames;
        if (input_path0.IsFolder())
        {
            input_path0.ListFiles(filenames, true);
        }
        else
        {
            filenames.push_back(input_path0);
        }

        lem::Ptr<lem::OFormatter> out_stream;
        if (output_path0.empty())
        {
            out_stream = lem::Ptr<OFormatter>(lem::mout, lem::null_deleter());
            print_progress = false;
        }
        else
        {
            out_stream = new lem::OUFormatter(output_path0);
            print_progress = true;
        }

        ParsingResults_XMLStream results(*out_stream);
        results.Start();


        try
        {
            for (int ifile = 0; ifile < filenames.size() && sent_count < max_count; ++ifile)
            {
                const lem::Path & input_file = filenames[ifile];

                if (filenames.size() > 1 && print_progress && verbose)
                {
                    lem::mout->printf("Parsing %d/%d [%us]...\n", ifile + 1, CastSizeToInt(filenames.size()), input_file.GetUnicode().c_str());
                }

                // Считаем, что входные файлы всегда в utf-8
                lem::Ptr<lem::Char_Stream::WideStream> reader = new lem::Char_Stream::UTF8_Reader(input_file); //lem::Char_Stream::WideStream::GetReader(input_path);
                SentenceBroker * segmenter = NULL;

                if (eol)
                {
                    segmenter = new SentenceEOL(reader, &dict, language_id);
                }
                else
                {
                    segmenter = new SentenceBroker(reader, &dict, language_id);
                }

                std::unique_ptr<SentenceBroker> segmenter_holder(segmenter);

                while (segmenter->Fetch())
                {
                    try
                    {
                        UFString sentence(segmenter->GetFetchedSentence());
                        sent_count++;
                        if (sent_count < start_index)
                            continue;

                        if (sent_count > max_count)
                            break;

                        if (!sentence.empty())
                        {
                            if (verbose)
                            {
                                lem::mout->printf("%d: %us\n", counter, sentence.c_str());
                            }

                            counter++;

                            sentence.trim();
                            int paragraph_id = segmenter->GetFetchedParagraphID();
                            ParseString(sentence, paragraph_id, emit_morph, render_tree, results);
                        }
                    }
                    catch (...)
                    {
                        out_stream->flush();
                        throw;
                    }
                }
            }
        }
        catch (...)
        {
            results.Flush();
            throw;
        }

        results.End();
        out_stream->close();
    }


    elapsed_time.stop();
    boost::posix_time::time_duration dt = elapsed_time.elapsed();

    if (print_progress && verbose)
    {
        lem::mout->printf("Done, sentence_count=%d, elapsed_time=%d sec, rate=%g words/sec\n", counter, dt.total_seconds(), (word_count*1000.0 / dt.total_milliseconds()));
    }

    return 0;
}
