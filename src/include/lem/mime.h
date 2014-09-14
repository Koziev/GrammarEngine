#ifndef LEM_MIME__H
#define LEM_MIME__H
#pragma once

 #include <string>

 namespace lem
 {
   // ********************************
   // Описатель формата документа.
   // ********************************
   struct MIMEType
   {
    std::string type;    // e.g. "text", "message", ...
    std::string subtype; // e.g. "plain", "html"
    std::string charset; // CHARSET parameter, e.g. "iso-8859-1"

    MIMEType(void);

    MIMEType( const MIMEType &x )
     : type(x.type), subtype(x.subtype), charset(x.charset) {}

    MIMEType( const std::string &Type, const std::string &SubType )
     : type(Type), subtype(SubType) {}

    // Конструктор разбирает композитное представление формата MimeStr на
    // элементы.
    MIMEType( const char *MimeStr );

    void operator=( const MIMEType &x )
    {
     type = x.type;
     subtype = x.subtype;
     charset = x.charset;
    }
 
    // Returns the composite MIME string e.q. "text/plain"
    std::string string(void) const;

    inline const std::string& GetType(void) const { return type; }
    inline const std::string& GetSubType(void) const { return subtype; }
    inline const std::string& GetCharset(void) const { return charset; }

    inline bool Empty(void) const { return type.empty(); }

    bool IsUTF8(void) const;

    static MIMEType GetTextPlain(void);
   };
 }

#endif
