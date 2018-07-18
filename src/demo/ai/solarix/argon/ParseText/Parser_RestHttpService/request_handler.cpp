//
// request_handler.cpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2017 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <fstream>
#include <sstream>
#include <string>
#include <codecvt>
#include <regex>
#include <boost/algorithm/string.hpp>

#include "request_handler.hpp"
#include "mime_types.hpp"
#include "reply.hpp"
#include "request.hpp"

#include "../Parser/Parser_API.h"
#include "../Parser/ParsingResults_API.h"

namespace http {
    namespace server {

        request_handler::request_handler(Parser_API & parser)
            : parser_(parser)
        {
        }

        void request_handler::handle_request(const request& req, reply& rep)
        {
            // Decode url to path.
            std::string request_path;
            if (!url_decode(req.uri, request_path))
            {
                rep = reply::stock_reply(reply::bad_request);
                return;
            }

            std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
            //std::wstring wurl = conv.from_bytes(request_path);

            //std::wregex ex(L"(/[^ ?]+)\\x3f(.*)");
            std::regex ex("/tag1\\x3f(.*)");
            std::cmatch matching;
            if (std::regex_match(request_path.c_str(), matching, ex, std::regex_constants::match_default))
            {
                //std::wstring path(matching[1].first, matching[1].second);
                std::string query(matching[1].first, matching[1].second);

                std::vector<std::string> query_params;
                boost::split(query_params, query, boost::is_any_of("&"));

                std::map<std::string, std::string> param2value;
                for (auto query_param : query_params)
                {
                    std::vector<std::string> tx;
                    boost::split(tx, query_param, boost::is_any_of("="));
                    param2value[tx[0]] = tx[1];
                }

                std::wstring sentence = conv.from_bytes(param2value["sent"]);
                bool emit_morph = false;
                if (param2value.find("emit_morph") != param2value.end())
                {
                    auto pvalue = param2value["emit_morph"];
                    emit_morph = boost::iequals(pvalue, "true") || boost::iequals(pvalue, "1");
                }

                bool allow_fuzzy_recognition = false;
                if (param2value.find("fuzzy") != param2value.end())
                {
                    auto pvalue = param2value["fuzzy"];
                    allow_fuzzy_recognition = boost::iequals(pvalue, "true") || boost::iequals(pvalue, "1");
                }

                std::unique_ptr<ParsingResults_API> res(parser_.TagSentence(sentence.c_str(), emit_morph, allow_fuzzy_recognition));

                const ParsingResult_Sentence & sent = res->GetSentence();

                // TODO: перенести формирование JSON в класс ParsingResult_Sentence или во вспомогательную функцию.
                std::stringstream buf;
                buf << "{\n";

                buf << " \"tokens\":[";

                for (auto it = sent.tokens.begin(); it != sent.tokens.end(); ++it)
                {
                    if (it != sent.tokens.begin())
                    {
                        buf << ",\n";
                    }

                    buf << "  { ";
                    const ParsingResult_Token & token = *it;

                    buf << "\"word\": \"" << conv.to_bytes(token.word) << "\", ";
                    buf << "\"lemma\": \"" << conv.to_bytes(token.lemma) << "\", ";
                    buf << "\"part_of_speech\": \"" << conv.to_bytes(token.part_of_speech) << "\", ";

                    buf << "\"tags\": [ ";

                    for (auto jt = token.tags.begin(); jt != token.tags.end(); ++jt)
                    {
                        if (jt != token.tags.begin())
                        {
                            buf << ", ";
                        }
                        buf << "\"" << conv.to_bytes(jt->tag_name) << "\": \"" << conv.to_bytes(jt->tag_value) << "\"";
                    }

                    buf << " ]";

                    buf << " }";
                }

                buf << "\n ],\n";

                // ¬ывод ребер синтаксического дерева.
                buf << " \"edges\":[";
                for (auto it = sent.edges.begin(); it != sent.edges.end(); ++it)
                {
                    if (it != sent.edges.begin())
                    {
                        buf << ",\n";
                    }

                    auto &edge = *it;
                    buf << "  {";

                    buf << "\"word_pos\": " << edge.word_pos << ", ";
                    buf << "\"word\": \"" << conv.to_bytes(edge.word) << "\",";
                    buf << "\"edge_name\": \"" << conv.to_bytes(edge.edge_name) << "\", ";
                    buf << "\"is_root\": " << edge.is_root << ", ";
                    buf << "\"is_orphant\": " << edge.is_orphant << ", ";
                    buf << "\"parent_index\": " << edge.parent_index << ", ";
                    buf << "\"parent_word\": \"" << conv.to_bytes(edge.parent_word_str) << "\" ";

                    buf << "}";
                }
                buf << " ]\n";


                buf << "}";

                rep.status = reply::ok;
                rep.content = buf.str();
                rep.headers.resize(2);
                rep.headers[0].name = "Content-Length";
                rep.headers[0].value = std::to_string(rep.content.size());
                rep.headers[1].name = "Content-Type";
                rep.headers[1].value = "application/json";//mime_types::extension_to_type(extension);
                return;
            }


            rep = reply::stock_reply(reply::bad_request);
            return;

        }

        bool request_handler::url_decode(const std::string& in, std::string& out)
        {
            out.clear();
            out.reserve(in.size());
            for (std::size_t i = 0; i < in.size(); ++i)
            {
                if (in[i] == '%')
                {
                    if (i + 3 <= in.size())
                    {
                        int value = 0;
                        std::istringstream is(in.substr(i + 1, 2));
                        if (is >> std::hex >> value)
                        {
                            out += static_cast<char>(value);
                            i += 2;
                        }
                        else
                        {
                            return false;
                        }
                    }
                    else
                    {
                        return false;
                    }
                }
                else if (in[i] == '+')
                {
                    out += ' ';
                }
                else
                {
                    out += in[i];
                }
            }
            return true;
        }

    } // namespace server
} // namespace http
