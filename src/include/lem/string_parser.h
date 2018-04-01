// -----------------------------------------------------------------------------
// File STRING_PARSER.H
//
// (c) Koziev Elijah
//
// Content:
// �����-������ StrParser - ������� ��������� ������ ��������� �����.
// -----------------------------------------------------------------------------
//
// CD->17.05.2004
// LC->02.03.2008
// --------------

#ifndef LEM_SPAR__H
#define LEM_SPAR__H
#pragma once

 #include <lem/conversions.h>
 #include <algorithm>

 #undef min
 #undef max

 namespace lem
 {

 template < class STR >
 class StrParser
 {
  public:
   typedef typename STR::value_type char_type;
   typedef int pos_type;

   bool parse_sign_as_part_of_float;
   bool parse_float; // ��������� �� ����� � ��������� �������
   int err_context_span; // ����� �������� �� � ����� ����� ������ � ������ �����������

  protected:
   const STR &txt; // ������ ������, ������������ �������.

   STR spaces; // �����������: �������-�������
   STR delims; // �����������: �������-�����������

   int i_read; // ���������� ������ ������
   int i_backpos; // ������� ��� �������� �� ������ ��������� �������

   // *******************************************
   // ��� ���������� ������?
   // *******************************************
   inline bool sp( char_type ch ) const
   { return std::find( spaces.begin(), spaces.end(), ch )!=spaces.end(); }

   // *******************************************
   // ��� ������-�����������?
   // *******************************************
   inline bool delim( char_type ch ) const
   { return std::find( delims.begin(), delims.end(), ch )!=delims.end(); }

   // ******************************************************************
   // �������� ������� �������, ������� ������������ ����� � ���������
   // ������� � ������� +1111.2222e-444.
   // ���� ������� ����� �� �������, �� ������������ ������ ������.
   // ******************************************************************
   const STR read_floating( int &i_cur ) const
   {
    STR res;

    // ���� ��������
    #if defined LEM_GNUC
    const typename STR::value_type c = txt[i_cur];
    #else
    const STR::value_type c = txt[i_cur];
    #endif 

    if( c=='-' || c=='+' )
     {
      i_cur++;
      res = c;

      if( !parse_sign_as_part_of_float )
       {
        // ��������� ��������� ���� ����� ������, ��� ����� ���� ����� ���
        // ������ ������������� � �.�.
        return res;
       }
     }

    // ����� �� �����
    while( txt[i_cur] && is_udigit( txt[i_cur] ) )
     res += txt[i_cur++];

    if( txt[i_cur]!='.' && txt[i_cur] )
     {
      // ��� �� �����, ������ ����� ���������, ���� ������� �������
      // ������, � �������� ������ ������� ����� ���� 'd'
      if( txt[i_cur]!='e' && txt[i_cur]!='E' )
       {
        // ������ ���� �����������.
        if( delim( txt[i_cur] ) )
         return res;
        else
         // ������������ ������ �����
         return STR();
       }

      // ���� ������� �����  - ����� 'e'
      res += txt[i_cur++];
     }
    else
     {
      res += txt[i_cur++];
    
      // ����� ����� ����� - �� �������
      while( txt[i_cur] && is_udigit( txt[i_cur] ) )
       res += txt[i_cur++];

      if( txt[i_cur]!='E' && txt[i_cur]!='e' )
       // ������� �� �����
       return res;
     }

    res += txt[i_cur++];
    
    // ���� �������
    if( txt[i_cur] && ( txt[i_cur]!='+' && txt[i_cur]!='-' && !is_udigit(txt[i_cur]) ) )
     return STR();

    if( !is_udigit(txt[i_cur]) )
     res += txt[i_cur++];

    // �������.
    int n_exp=0;
    while( txt[i_cur] && is_udigit( txt[i_cur] ) )
     {
      res += txt[i_cur++];
      n_exp++;
     }
     
    if( !n_exp )
     {
      // ������� �� ��������� ���������.
      return STR();
     }

    return res;
   }


  public:   
   StrParser( const STR &Txt )
    : txt(Txt),
      spaces( " \t\r\n" ), 
      delims( "`~!@#$%^&*()-=+\\|[{]};:,<.>/?" )
   {
    i_read=0;
    parse_float=true;
    parse_sign_as_part_of_float=true;
    err_context_span=128;
    i_backpos = 0;
   }

   inline const STR& string(void) { return txt; }

   // ��������� �������������� ����������� ������.
   inline STR get_Spaces(void) { return spaces; }
   inline STR get_Delims(void) { return delims; }

   inline void set_Delims( const STR &s ) { delims=s; }
   inline void set_Spaces( const STR &s ) { spaces=s; }

   // *************************************************************************
   // ���������� ����� �������. i_cur - ������ ������ (����������� - ��� ������
   // ����� ���������� �� ������ ����� ����������� �������).
   // *************************************************************************
   inline const STR read(void) { i_backpos = i_read; return read(i_read); }

   inline bool probe( const STR & token )
   {
    if( read() == token )
     return true;

    back();
    return false;
   }

   // ******************************
   // ������� ��������
   // ******************************
   void skip_whites( int &i_cur ) const
   {
    while( txt[i_cur] && sp( txt[i_cur] ) ) i_cur++;
   }

   // *************************************************
   // ���������� ������ � ������� ��������
   // ������ � ������ ������ ���� �� ��������� �������.
   // �� ������ - �� ������� ����� ����������� �������.
   // *************************************************
   const STR read_quoted( int &i_cur ) const
   {
    STR lex;
    lex = txt[i_cur++];

    while( txt[i_cur] && txt[i_cur]!='"' )
    {
     if( txt[i_cur]=='\\' )
      lex += txt[++i_cur]; 
     else
      lex += txt[i_cur];

     i_cur++;
    } 

    if( txt[i_cur]=='"' )
     {
      i_cur++;
      lex += '"';
     }

    return lex;
   }

   const STR read_apostrophed( int &i_cur ) const
   {
    STR lex;
    lex = txt[i_cur++];

    while( txt[i_cur] && txt[i_cur]!='\'' )
    {
     lex += txt[i_cur];

     if( txt[i_cur]=='\\' )
      lex += txt[++i_cur];

     i_cur++;
    } 

    if( txt[i_cur]=='\'' )
     {
      i_cur++;
      lex += '\'';
     }

    return lex;
   }
   

   const STR read( int &i_cur ) const
   {
    int l = txt.length();
    if( i_cur>=l )
     return STR(); // ������� ������ �� ��������� ������ - ���������� ������ �������

    // ��������� �������
    skip_whites( i_cur );

    STR lex;

    if( txt[i_cur]=='"' )
     return read_quoted( i_cur );

    if( txt[i_cur]=='\'' )
     return read_apostrophed( i_cur );

    if( parse_float )
     {
      // ��������� ��������� ��� ����� � ��������� ������.
      int i_back = i_cur;

      STR f = read_floating(i_cur);
      if( !f.empty() )
       // ��, ����������.
       return f;  

      // ������� - ����� ��������� ��� ��� �������.
      i_cur = i_back;
     }


    if( delim( txt[i_cur] ) )
     {
      lex = txt[i_cur++];
     }
    else
     while(
           txt[i_cur] &&
           !sp(txt[i_cur]) &&
           !delim( txt[i_cur] )
          )
    {
     lex += txt[i_cur];
     i_cur++;
    } 

   return lex;  
  }

  // ********************************************************
  // ������ ��������� �����, ���� ��������� ������ ������� - 
  // ������������ ����������.
  // ********************************************************
  inline void read_it( const char_type *token ) { i_backpos = i_read; read_it(i_read,token); }

  void read_it( int &i_cur, const char_type *token ) const
  {
   if( read( i_cur ) != token )
    {
     // �������� ������ '���������' ������
     int i_from = std::max( 0, i_cur-err_context_span );
     int i_to = std::min( (int)txt.length(), i_cur+lem::lem_strlen(token)+err_context_span );
     STR context( txt.substr( i_from, i_to-i_from+1 ) ); //txt.begin()+i_from, txt.begin()+i_to-1 );

     throw ECheckFault(
                       to_wstr("Missing token ")+to_wstr(token)+
                       to_wstr( " in context " ) + to_wstr(context.c_str())
                     );
    }
  }

  // ��������� ����� ������?
  inline bool eof(void) const { return i_read >= txt.length(); }
  inline bool eof( int icur ) const { return icur >= txt.length(); }

  // ���������� ������� ������� ������� ������
  inline pos_type tellp(void) const { return i_read; }

  // ������������� ������� �������� ������� ������
  inline void seekp( pos_type x ) { i_read=x; }

  inline void back(void) { i_read = i_backpos; }
 };

 } // namespace lem

#endif
