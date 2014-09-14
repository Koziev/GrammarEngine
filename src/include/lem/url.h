// CD->01.10.2005
// LC->17.06.2008
// --------------

#ifndef LEM_URL__H
#define LEM_URL__H
#pragma once

 #include <lem/config.h>
 #include <lem/zeroed.h>
 #include <list>
 #include <lem/fstring.h>
 #include <lem/cstring.h>

 namespace lem
 {
  // ѕолна€ информаци€ дл€ подключени€ к интернет-серверу, включа€
  // им€ пользовател€ и пароль
  class Url
  {
   public:
    enum { MAX_URL_LEN = 1024 };

    UFString full_address; // исходный полный адрес

    // »звлеченные из адреса элементы

    UFString login;     // логин и пароль дл€ подключени€
    UFString password;

    UCString protocol; // название протокола
    UFString adr;      // адрес - без протокола и порта
    UFString path;     // путь к документу
    int port;          // номер порта

    lem::zbool ok;     // ошибки при парсинге строки
  
   private:
    void HttpProtocol(void);
    void Parse( bool exception );
    void Canonize( bool exception );

   public:
    Url(void) { port=0; }

    Url( const UFString &Address, bool exception=true );

    Url( const Url &base, const UFString &doc, bool exception=true );

    Url( const Url &x )
     : full_address(x.full_address),
       login( x.login ),
       password( x.password ),
       protocol( x.protocol ),
       adr( x.adr ),
       path( x.path ),
       port( x.port ), ok(x.ok)
    {}

    inline void operator=( const Url &x )
    {
     full_address = x.full_address;
     login        = x.login;
     password     = x.password;
     protocol     = x.protocol;
     port         = x.port;
     path         = x.path;
     adr          = x.adr;
     ok           = x.ok;
    }

    inline const UFString& string(void) const { return full_address; }

    inline int length(void) const { return full_address.size(); }

    void SaveBin( lem::Stream &bin ) const;
    void LoadBin( lem::Stream &bin );

    // ¬ернет строку домена, в котором располагаетс€ документ с данным URL'ом
    // “о есть дл€ URL "http://solarix.ru/index.shtml вернет "http://solarix.ru"
    // ≈сли же URL указывает на домен или на каталог, то есть имеет вид
    // "http://solarix.ru/for_users", то вернет исходную строку
    const UFString GetDomainString(void) const;

    const UFString GetDocumentString(void) const;

    static bool IsUrl( const wchar_t *str );
  };


  extern void GetUrlParams(
                           const char *url,
                           std::list< std::pair<std::string/*var*/,std::wstring/*value*/> > &lst
                          );

 } // namespace lem

#endif
