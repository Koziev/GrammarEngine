#ifndef LEM_HTTPD__H
#define LEM_HTTPD__H
#pragma once

 #include <lem/ufstring.h> 
 #include <lem/fstring.h> 
 #include <lem/mongoose.h>
 #include <lem/process.h> 
 #include <stdlib.h>
 #include <stdio.h>
 #include <list>
 #include <string>

 namespace lem
 {

  class HttpServer
  {
   private:
	struct mg_context *ctx;
    int port;
    lem::FString ip;
    lem::UFString server_url;

    char* urlDecode( const char *source, char *dest ) const;
    void htmlDecode( const char* abuf, wchar_t *wbuf ) const;

    static void HttpCallback(
                             struct mg_connection *conn,
                             const struct mg_request_info *request_info,
                             void *user_data
                            );

   protected: 
    int ExitCode;

    virtual void EnterWaitLoop(void);

    virtual void WriteHeader( struct mg_connection *conn, const char *content_type="text/html" );
    virtual void PageNotFound( struct mg_connection *conn );

    virtual void StartProcessingQuery( const char *url_query );
    virtual void EndProcessingQuery( const char *url_query );

    virtual void BeginHtml( lem::UFString &out, const wchar_t *PageTitle=NULL ) const;
    virtual void BeginHtml( lem::UFString &out, const wchar_t *PageTitle, const wchar_t *HeaderMeta ) const;
    virtual void EndHtml( lem::UFString &out ) const;
 
    void GetParams(
                   const char *query,
                   std::list< std::pair<std::string/*var*/,std::wstring/*value*/> > &list
                  ) const;

    void ReleaseResources(void);

   public:
    HttpServer(void);
    virtual ~HttpServer(void);

    virtual bool GenerateHtml(
                              const char * url,
                              const char * query,
                              char **outdata,
                              int *freer,
                              char **content_type
                             );

    virtual bool ProcessPostRequest(
                                    const char * url,
                                    const char * query,
                                    const char * post_data,
                                    int post_data_len,
                                    char **outdata,
                                    int *freer,
                                    char **content_type
                                   );

    // Производный класс может перегрузить этот метод для более простого
    // возврата строки веб-клиенту. Строка автоматически будет перекодирована в utf-8.
    virtual bool GenerateHtml(
                              const char * url,
                              const char * query,
                              lem::UFString &outdata,
                              char **content_type
                             );

    virtual bool ProcessPostRequest(
                                    const char *url,
                                    const char * query,
                                    const char * post_data,
                                    int post_data_len,
                                    lem::UFString &outdata,
                                    char **content_type
                                   );


    virtual void Run( const char *Addr, int Port );
    virtual int GetExitCode(void);

    int GetPort(void) const { return port; }
    const char* GetAddress(void) const { return ip.c_str(); }

    const lem::UFString& GetServerUrl(void) const { return server_url; }
  };

} // namespace lem

#endif
