#if !defined TRANSLATION_HTTP__H
 #define TRANSLATION_HTTP__H

 #if defined SOL_TR_HTTPD

 #include <lem/solarix/TranslatorEngine.h>
 #include <lem/ufstring.h>
 #include <lem/fstring.h>
 #include <lem/process.h>
 #include <lem/httpd.h>

 namespace Solarix
 {
  class TranslatorEngine;

  // ******************************************
  // HTTP-сервер для доступа к переводчику
  // ******************************************
  class TrHttpServer : public lem::HttpServer
  {
   private:
    Solarix::TranslatorEngine *tr;
    lem::UFString query_form_body;
    bool use_get_method;
    int itag; // tramsl_category
    int default_yield_format;
    bool html_header, html_footer;

    lem::Process::InterlockedInt total_queries; // всего запросов
    lem::Process::InterlockedInt pending_queries; // текущие запросы
    lem::Process::InterlockedInt max_queries; // максимальное число одновременных запросов
    lem::Process::InterlockedInt total_chars; // сколько символов предложений обработано

    void QueryForm( lem::UFString &out );
    void TranslateQueryString(
                              const lem::FString &url_query,
                              lem::UFString &out,
                              char **content_type
                             );

    virtual void StartProcessingQuery( const char *url_query );
    virtual void EndProcessingQuery( const char *url_query );

    virtual void BeginHtml( lem::UFString &out, const wchar_t *PageTitle=NULL ) const;
    virtual void EndHtml( lem::UFString &out ) const;

    volatile bool listening;
    virtual void EnterWaitLoop(void);

   public:
    TrHttpServer( Solarix::TranslatorEngine *x );

    void UsePostMethod(void);
    void SetYieldFormat( int format );

    void Stop(void);

    virtual bool GenerateHtml(
                              const char *url,
                              const char *url_query,
                              lem::UFString &out,
                              char **content_type
                             );

    virtual bool ProcessPostRequest(
                                    const char *url,
                                    const char *url_query,
                                    const char *post_data,
                                    int post_data_len,
                                    lem::UFString &out,
                                    char **content_type
                                   );
  };

 } // namespace Solarix


 #endif

#endif
