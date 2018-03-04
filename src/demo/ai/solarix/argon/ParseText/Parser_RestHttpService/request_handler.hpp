//
// request_handler.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2017 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HTTP_REQUEST_HANDLER_HPP
#define HTTP_REQUEST_HANDLER_HPP

#include <string>

class Parser_API;

namespace http {
    namespace server {

        struct reply;
        struct request;

        /// The common handler for all incoming requests.
        class request_handler
        {
        public:
            request_handler(const request_handler&) = delete;
            request_handler& operator=(const request_handler&) = delete;

            explicit request_handler(Parser_API &parser);

            /// Handle a request and produce a reply.
            void handle_request(const request& req, reply& rep);

        private:
            Parser_API & parser_;

            /// Perform URL-decoding on a string. Returns false if the encoding was
            /// invalid.
            static bool url_decode(const std::string& in, std::string& out);
        };

    } // namespace server
} // namespace http

#endif // HTTP_REQUEST_HANDLER_HPP
