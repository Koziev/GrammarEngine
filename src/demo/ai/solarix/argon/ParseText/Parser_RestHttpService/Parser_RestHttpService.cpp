#include "stdafx.h"

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "server.hpp"

#include <lem/startup.h>

#include "../Parser/Parser_API.h"


int main(int argc, char* argv[])
{
    lem::LemInit initer;

    try
    {
        /*
                // Check command line arguments.
                if (argc != 4)
                {
                    std::cerr << "Usage: http_server <address> <port> <doc_root>\n";
                    std::cerr << "  For IPv4, try:\n";
                    std::cerr << "    receiver 0.0.0.0 80 .\n";
                    std::cerr << "  For IPv6, try:\n";
                    std::cerr << "    receiver 0::0 80 .\n";
                    return 1;
                }

                // Initialise the server.
                http::server::server s(argv[1], argv[2], argv[3]);

                // Run the server until stopped.
                s.run();
        */


        lem::Path dict_path("dictionary.xml");

        bool emit_morph = false;
        bool allow_fuzzy_recognition = false;
        std::string language_name;

        int tagger_type = 0;
        int lemmatizer_type = 0;
        int parser_type = -1;

        std::string binding_address = "127.0.0.1";
        std::string binding_port = "10973";

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
                    else if (strcmp(opt, "lang") == 0)
                    {
                        language_name = argv[++i];
                    }
                    else if (strcmp(opt, "url") == 0)
                    {
                        binding_address = argv[++i];
                    }
                    else if (strcmp(opt, "port") == 0)
                    {
                        binding_port = argv[++i];
                    }
                    else if (strcmp(opt, "parser") == 0)
                    {
                        parser_type = lem::to_int(argv[++i]);
                        if (parser_type < -1 || parser_type>2)
                        {
                            throw lem::E_BaseException(lem::format_str("Unknown parser=%d, only [-1,0,1,2] are allowed", parser_type));
                        }
                    }
                    else if (strcmp(opt, "tagger") == 0)
                    {
                        tagger_type = lem::to_int(argv[++i]);
                        if (tagger_type < -1 || tagger_type>1)
                        {
                            throw lem::E_BaseException(lem::format_str("Unknown tagger_type=%d, only [-1,0] are allowed", tagger_type));
                        }
                    }
                    else if (strcmp(opt, "lemmatizer") == 0)
                    {
                        lemmatizer_type = lem::to_int(argv[++i]);
                    }
                    else if (strcmp(opt, "emit_morph") == 0)
                    {
                        emit_morph = lem::to_int(argv[++i]) == 1;
                    }
                    else if (strcmp(opt, "fuzzy_wordrecog") == 0)
                    {
                        allow_fuzzy_recognition = lem::to_int(argv[++i]) == 1;
                    }
                    else if (strcmp(opt, "d") == 0)
                    {
                        dict_path = lem::Path(argv[++i]);
                    }
                    else
                    {
                        throw lem::E_BaseException(lem::format_str("Unknown option %s", argv[i]));
                    }
                }
                catch (const lem::E_BaseException & e)
                {
                    throw lem::E_BaseException(lem::format_str(L"Command line option %s parsing error: %ws", argv[i], e.what()));
                }
                catch (std::exception & e)
                {
                    throw lem::E_BaseException(lem::format_str("Command line option %s parsing error: %s", argv[i], e.what()));
                }
                catch (...)
                {
                    throw lem::E_BaseException(lem::format_str("Command line option %s parsing error", argv[i]));
                }
            }
            else
            {
                throw lem::E_BaseException(lem::format_str("Unknown option [%s]", argv[i]));
            }
        }


        dict_path = dict_path.GetAbsolutePath();

        Parser_API parser(lemmatizer_type, parser_type);
        parser.Load(dict_path.GetUnicode().c_str());

        // Initialise the server.
        http::server::server s(binding_address, binding_port, parser);

        // Run the server until stopped.
        s.run();
    }
    catch (std::exception& e)
    {
        lem::mout->printf("Exception: %s\n", e.what());
    }
    catch (lem::E_BaseException& e)
    {
        lem::mout->printf("Exception: %us\n", e.what());
    }
    catch (...)
    {
        lem::mout->printf("Unknown exception\n");
    }

    return 0;
}
