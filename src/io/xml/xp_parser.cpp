// -----------------------------------------------------------------------------
// File XP_PARSER.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Content:
// ����� Parser - �������������� ������ ���������� ������ XML. ������������
// ������ ����� (DOM).
//
// 27.05.2007 - ��� ���������� ���� ����� ���������� �������������� �����������
//              ���� &#NNN; � &name;
//
// 04.08.2007 - ��������� ������ ������ � ������ Xml::Parser
//
// 09.03.2008 - �������� ����� Parser::Get_By_Path ��� ��������� ��������� �� 
//              ���������. 
// 06.06.2008 - ��������� ��������� ����� <!-- ... --> � <![CDATA[ ... ]]>
// 26.01.2009 - ��������� ������ ������������� ����� ����������� � ������������
//              ����������� ���� <!----!>, � ���������� ���� ��� ���� XML �����
//              �������� � �����������.
// -----------------------------------------------------------------------------
//
// CD->20.11.2004
// LC->26.01.2009
// --------------

#include <lem/config.h>
#include <algorithm>
#include <lem/conversions.h>
#include <lem/xml_parser.h>

using namespace std;
using namespace lem;
using namespace lem::Xml;
using namespace lem::Char_Stream;


static lem::MCollect<lem::UFString> tags1;

static bool IsHtmlClosed(const lem::UFString &tag)
{
    if (tags1.empty())
    {
        const wchar_t* stags[] = { L"br", L"hr", L"link", L"meta", L"img", L"input",
                                   NULL
        };

        int i = 0;
        while (stags[i] != NULL)
            tags1.push_back(lem::UFString(stags[i++]));
    }

    for (lem::Container::size_type i = 0; i < tags1.size(); ++i)
    {
        const lem::UFString &t = tags1[i];
        if (tag.eq_begi(t) && (tag.length() == t.length() || tag[t.length()] == L' '))
            return true;
    }

    return false;
}


static lem::MCollect<lem::UFString> tags2;

static bool IsTextDelimiterTag(const UFString &tag)
{
    if (tags2.empty())
    {
        const wchar_t* stags[] = { L"p", L"br", L"table", L"td", L"tr", L"th",
                                   L"ol", L"ul", L"li", L"dd", L"input", L"frame", L"div",
                                   NULL
        };

        int i = 0;
        while (stags[i] != NULL)
            tags2.push_back(lem::UFString(stags[i++]));
    }

    for (lem::Container::size_type i = 0; i < tags2.size(); ++i)
    {
        const lem::UFString &t = tags2[i];
        if (tag.eq_begi(t) && (tag.length() == t.length() || tag[t.length()] == L' '))
            return true;
    }

    return false;
}



Parser::Parser(void) : doctype(Parser::UnknownDoc)
{}


void Parser::LoadString(const wchar_t *str)
{
    lem::Ptr<lem::Char_Stream::UTF16_MemReader> mem(new lem::Char_Stream::UTF16_MemReader(str));
    Load(mem.get());
    return;
}



void Parser::Load(const lem::Path &path)
{
    lem::Ptr<Stream> bin(new BinaryFile(path, true, false));
    Load(bin);
    return;
}



void Parser::Load(lem::Char_Stream::WideStream *reader)
{
    LEM_CHECKIT_Z(reader != NULL);
    Load_Content(reader);
    return;
}


void Parser::Load(lem::Ptr<Stream> bin)
{
    // �������� ���������� ����� ��������.
    static FString UTF8_1("utf8");
    static FString UTF8_2("utf-8");

    // ��������� ���������� ������� ��������.
    // ��� ����� ��������� ������ 512 ������ ��������, � ���������
    // � ��� ����� charset=xxx
    const int BLOCK_SIZE = 512;
    boost::scoped_array<char> block(new char[BLOCK_SIZE + 1]);
    Stream::pos_type rd = bin->read(block.get(), 511);
    int z = std::max(std::min(int(rd), BLOCK_SIZE) - 1, 0);
    LEM_CHECKIT_Z(z >= 0);
    block[z] = 0;

    bool utf8 = false;
    const lem::CodeConverter *cp = NULL;
    bool icu = false;

    const char tag1[] = "charset=";
    const char tag2[] = "encoding=";

    int i0 = lem_find(block.get(), tag1);
    int tag_len = 8;

    if (i0 == UNKNOWN)
    {
        // � XML ������������ ������� encoding=XXX
        i0 = lem_find(block.get(), tag2);
        tag_len = 9;
    }

    if (i0 != UNKNOWN)
    {
        // �������� �������� ���������
        FString coding;

        int i = i0 + tag_len;

        // � XML ��������� ����������� ���: encoding="windows-1251"
        //                                           ^------------^
        //
        // � � HTML ������ ���:             charset=windows1251

        // ���������� �������
        while (i < BLOCK_SIZE)
            if (lem::is_space(block[i]))
                i++;
            else
                break;

        if (block[i] == '"' || block[i] == '\'')
            i++;

        while (block[i])
        {
            if (strchr(" \"'>\r\n", block[i]) != NULL)
                break;

            coding += to_lower(block[i++]);
        }

        coding.trim();

        if (coding == UTF8_1 || coding == UTF8_2)
        {
            utf8 = true;
            charset = L"utf8";
        }
        else
        {
            try
            {
                cp = lem::CodeConverter::getConverter(coding.c_str());
                charset = to_unicode(coding);
            }
            catch (...)
            {
                // ������������� ������ ���������� ���������� ����������� ��������� ��� 
                // ���������. ������� ��������� ���������� - ����� ���������� ������������
                // ��������� ������� ����������.
            }

            if (!cp)
            {
#if defined LEM_ICU
                // ����� ������������ ����� �������������, �� ����� ����������� �����
                // � �������������� ���������� IBM ICU
                icu = true;
#else
                throw E_BaseException(wstring(L"Unknown encoding of XML document: ") + to_wstr(coding.c_str()));
#endif  
            }
        }
    }

    bin->seekp(0);


    WideStream *rdr = NULL;
    if (utf8)
    {
        rdr = new lem::Char_Stream::UTF8_Reader(bin);
    }
    else
    {
        lem::Char_Stream::Char_Reader *chr = new lem::Char_Stream::Char_Reader(bin);
        chr->SetEncoding(cp);
        rdr = chr;
    }

    std::unique_ptr<WideStream> reader(rdr);
    Load_Content(&*reader);
    return;
}


void Parser::Load_Content(WideStream *reader)
{
    LEM_CHECKIT_Z(reader != NULL);

    // ��������� ������ ����������� ���, ������� ������ �������� ��������
    lem::Stream::pos_type doc_beg = reader->tellp();
    wchar_t c = reader->wget();
    if (c != L'<')
    {
        // ������ � ������ utf-8 ����� ���������� BOM, ��� ��� XML �����
        // �������� ���������� �������, �� �� �� ����� ��������...
        if (c == 0xfeff)
        {
            c = reader->wget();
            if (c != L'<')
                throw Invalid_Format();
        }
        else
            throw Invalid_Format();
    }

    // ��� XML ���������� ������ ��� ����������
    // ��� HTML �������� ��������, ������ ���� ������ ��� ��� <html>,
    // �� ��� ���� ����� ��������� ���������� �������, ��� ���
    // �� �������� � ���� ��� ������ ���� ��������� � ����� �����������
    // </html>, � ������� �� <?xml> � <!DOCTYPE

    // <?xml version="1.0"?>
    //  ^^^^^^^^^^^^^^^^^^^
    Read_Tag(reader, header);

    if (header.eq_begi(L"?xml"))
    {
        doctype = Parser::XmlDoc;
    }
    else if (header.eq_begi(L"!DOCTYPE html"))
    {
        doctype = Parser::HtmlDoc;
    }
    else if (header.eq_begi(L"html"))
    {
        doctype = Parser::HtmlDoc;
        reader->seekp(doc_beg);
    }
    else
    {
        doctype = Parser::UnknownDoc;
        reader->seekp(doc_beg);
    }

    if (charset.empty())
    {
        // ��������� ������ ���������
        Collect< pair<UFString/*name*/, UFString/*value*/> > attrs;
        UFString dummy, dummy2;
        Break_Tag(header, dummy, attrs, dummy2);

        // � ������ ��������� ����� ��������� �������� �����
        // ����������� ������� ��������
        // <?xml version="1.0" encoding="windows-1251"?>

        for (Container::size_type i = 0; i < attrs.size(); i++)
            if (attrs[i].first == L"encoding")
            {
                charset = attrs[i].second;
                break;
            }

        if (charset.empty())
        {
            // ��������� �� ����������. �������� ���������� �� ����.

            if (reader->GetType() == SET_UTF16)
                charset = L"utf16";
            else if (reader->GetType() == SET_UTF16)
                charset = L"utf16";
            else
                charset = L"windows-1251";
        }
    }

    // ������ ���������.
    // ������ ���� �������� ����.
    try
    {
        root = Load_Node(reader);
    }
    catch (...)
    {
        throw;
    }

    if (!root)
    {
        throw Invalid_Format();
    }

    // ���, ����������, � ���.
    return;
}


// **********************************************************
// ��������� ��� - ��� ������� ����� < >.
// ����������� ������� ������ ��� �������!
// **********************************************************
void Parser::Read_Tag(WideStream *reader, UFString &tag) const
{
    tag.clear();
    int count = 0;

    while (!reader->eof())
    {
        wchar_t c = reader->wget();

        if (c == L'>')
            break;

        if (!count && c == L'!')
        {
            // ��� �����������   <!-- ... -->
            // ��� ���� ����     <![CDATA[ ... ]]>
            // ��� ��������� ��� <!DOCTYPE

            tag += c;
            count++;

            wchar_t c = reader->wget();
            if (c == L'-')
            {
                // �����������...
                tag += c;
                count++;
                while (!reader->eof())
                {
                    wchar_t c = reader->wget();
                    if (c == WEOF)
                        break;

                    if (count > 3 && c == L'>')
                    {
                        // ����������� ������������� �� -->
                        if (tag.back() == L'-' && tag[tag.length() - 2] == L'-')
                        {
                            goto tag_complete;
                        }
                    }

                    tag += c;
                    count++;
                }

                // ���� ����������� �� �������� ���������, �� ������ ���� ������ 
                throw Invalid_Format();
            }
            else if (c == L'D')
            {
                // <!DOCTYPE ...>
                // ��������� ��� ������� ���
                tag += c;
                count++;
                continue;
            }
            else if (c == '[')
            {
                // <![CDATA[ ���������� ���������...
                tag += c;
                count++;
                continue;
            }
            else
            {
                // ����������� ���, ��� HTML ������������� ������
                if (doctype == Parser::HtmlDoc)
                {
                    tag += c;
                    count++;
                }
                else
                {
                    throw Invalid_Format();
                }
            }
        }
        else if (count == 7 && c == L'[' && tag == L"![CDATA")
        {
            // ���� ���� ����� <![CDATA[

            tag += c;
            count++;

            while (!reader->eof())
            {
                wchar_t c = reader->wget();
                if (c == WEOF)
                    break;

                if (count > 8 && c == L'>')
                {
                    // ���� ���� ������������� �� ]]>
                    if (tag.back() == L']' && tag[tag.length() - 2] == L']')
                    {
                        goto tag_complete;
                    }
                }

                tag += c;
                count++;
            }

            if (doctype != Parser::HtmlDoc)
                throw Invalid_Format();
        }

        if (c == WEOF || reader->eof())
            break;

        tag += c;
        count++;
    }

tag_complete:

    return;
}



void Parser::Break_Tag(
    const UFString &tag,
    UFString &name,
    Collect< pair<UFString, UFString> > &attrs,
    UFString &body // ��� ![CDATA[ ... ]]
) const
{
    int i = 0;

    // ���������� �������
    while (tag[i])
    {
        if (
            tag[i] != L' '  &&
            tag[i] != L'\t' &&
            tag[i] != L'\r' &&
            tag[i] != L'\n'
            )
            break;

        i++;
    }

    if (tag.eq_beg(L"![CDATA["))
    {
        name = L"![CDATA[";
        body = lem::mid(tag, 8, tag.length() - 10);
        return;
    }

    // ���������� ��� ����
    while (tag[i])
    {
        if (
            tag[i] == L' ' ||
            tag[i] == L'\t' ||
            tag[i] == L'\r' ||
            tag[i] == L'\n' ||
            tag[i] == L'>'
            )
            break;

        name += tag[i];
        i++;
    }

    // ������ ��������

    while (tag[i])
    {
        // ������ ��������� ���� ���=��������

        // ���������� �������
        while (tag[i])
        {
            if (
                tag[i] != L' '  &&
                tag[i] != L'\t' &&
                tag[i] != L'\r' &&
                tag[i] != L'\n'
                )
                break;

            i++;
        }

        if (!tag[i] || tag[i] == '/' || tag[i] == '>')
            return;

        // ������ ��� �������� = �� ����� '=' ��� ������� ��� ����� ����
        UFString var, value;

        if (tag[i] == L'"')
        {
            // � ���������� - ������ ��� ���� �� ������� ���������
            i++;
            while (tag[i])
            {
                if (tag[i] == L'"')
                {
                    i++;
                    break;
                }

                if (tag[i] == L'\n' || tag[i] == '\r')
                    throw Invalid_Format();

                var += tag[i];
                i++;
            }
        }
        else
        {
            while (tag[i])
            {
                if (
                    tag[i] == L'=' ||
                    tag[i] == L'/' ||
                    tag[i] == L'>' ||
                    tag[i] == L' ' ||
                    tag[i] == L'\t' ||
                    tag[i] == L'\r' ||
                    tag[i] == L'\n'
                    )
                    break;

                var += tag[i];
                i++;
            }
        }

        // ����� ����� �������� �� ����� '=' ����� ���� ������� - ����������.
        while (tag[i])
        {
            if (
                tag[i] != L' '  &&
                tag[i] != L'\t' &&
                tag[i] != L'\r' &&
                tag[i] != L'\n'
                )
                break;

            i++;
        }


        if (tag[i] == L'=')
        {
            // ������ �������� �������� - �� ������� ��� ����� ����
            i++;

            // ���������� ��������� �������
            while (tag[i])
            {
                if (
                    tag[i] != L' '  &&
                    tag[i] != L'\t' &&
                    tag[i] != L'\r' &&
                    tag[i] != L'\n'
                    )
                    break;

                i++;
            }

            if (tag[i] == L'"')
            {
                // �������� �������� - � ����������, ������ ��� ����
                i++;
                while (tag[i])
                {
                    if (tag[i] == L'"')
                    {
                        i++;
                        break;
                    }

                    if (tag[i] == L'\n' || tag[i] == '\r')
                        throw Invalid_Format();

                    value += tag[i];
                    i++;
                }
            }
            else
            {
                while (tag[i])
                {
                    if (
                        tag[i] == L'=' ||
                        tag[i] == L'/' ||
                        tag[i] == L'>' ||
                        tag[i] == L' ' ||
                        tag[i] == L'\t' ||
                        tag[i] == L'\r' ||
                        tag[i] == L'\n'
                        )
                        break;

                    value += tag[i];
                    i++;
                }
            }
        }

        // ��������� ��������� �������
        attrs.push_back(make_pair(var, value));
    }

    return;
}





// ******************************************************
// ��������� ���� ������ �� ����� ��� ���������� ������.
// ******************************************************
Node* Parser::Load_Node(WideStream *reader) const
{
    if (reader->eof())
        return NULL;

    // ���������� �������.
    wchar_t c = 0;

    while (!reader->eof())
    {
        c = reader->wget();

        if (c == WEOF)
            return NULL;

        if (c != L' ' && c != L'\t' && c != L'\r' && c != L'\n')
            break;
    }

    // ������ ������ ���� '<'.

    if (reader->eof())
        return NULL;

    if (c != L'<')
        throw Invalid_Format();


    // ��������� ���.
    UFString tag;
    Read_Tag(reader, tag);

    if (tag.empty())
        throw Invalid_Format();

    Node *node = new Node;

    Break_Tag(tag, node->name, node->attrs, node->body);

    // ���� ������ ���� ����� - ��������� <abc/>, ����������� <abc>,
    // ����������� </abc>, ����������� <!--...-->, ���� <![CDATA[ ... ]>
    // ��� HTML ��������� ����� ����������� ��������� ����� <script>...</script>
    // � ��������� ���� <br>
    if (tag.back() == L'/')
    {
        // ��������� ���.
        node->SetClosed(true);
    }
    else if (node->name == L"![CDATA[")
    {
        node->node_type = Node::CDataNode;
        node->SetClosed(true);
    }
    // ��� HTML ���� ��������� ��������� ���� ���� <br>
    else if (doctype == HtmlDoc && IsHtmlClosed(tag))
    {
        // ��������� ���.
        node->SetClosed(true);
    }
    else if (tag.front() == L'/')
    {
        // ����������� ���.
        // � ����� ������� ������ '/'
        node->name = remove_char(node->name, L'/');

        node->SetClosing(true);
    }
    else if (tag.front() == L'!')
    {
        if (tag.length() >= 3 && tag.eq_beg(L"!--"))
        {
            // ����������� <!-- ... -->
            node->SetClosed(true);
            node->node_type = Node::CommentNode;
        }
        /*
           else if( tag.eq_beg( L"CDATA[") )
            {
             node->SetClosed(true);
             node->node_type = Node::CDataNode;
            }
        */
        else
        {
            if (doctype == Parser::XmlDoc)
            {
                delete node;
                throw Invalid_Format();
            }
            else
            {
                node->SetClosed(true);
                node->node_type = Node::InvalidNode;
            }
        }
    }
    else if (doctype == Parser::HtmlDoc && node->name.eqi(L"script"))
    {
        // ��� ���� ����� <script>...</script> ������� ������ - ���� �������� 
        // ������������ ������� ��������, �������� ��� ������ ����� � ���� ����.
        node->node_type = Node::ScriptNode;
        node->body.reserve(256);
        while (!reader->eof())
        {
            wchar_t c = reader->wget();
            if (c == WEOF || reader->eof())
                break;

            if (c == L'<')
            {
                // ����� ��� ������ ������������ ���� </script>
                lem::UFString tbuf;
                tbuf.reserve(32);
                tbuf = c;

                while (!reader->eof())
                {
                    wchar_t c2 = reader->wget();
                    if (c2 == WEOF || reader->eof())
                        break;

                    tbuf += c2;

                    if (c2 == L'>')
                        break;
                }

                if (tbuf.eqi(L"</script>"))
                {
                    node->SetClosed(true);
                    break;
                }
                else
                {
                    node->body += tbuf;
                }
            }
            else
            {
                node->body += c;
            }
        }
    }
    else
    {
        // ����������� ���.
        // ������ ����� ���� ���� ������ ��������� �����, ���� ������ - ����.

        wchar_t c = 0;

        // ��������� �������.
        while (!reader->eof())
        {
            c = reader->wget();

            if (c != L' ' && c != L'\t' && c != L'\n' && c != L'\r')
                // ��������� �������� ������!
                break;
        }

        if (c == L'<')
        {
            reader->unget(c);

            // ������ ���� ��������� ��� ��������� ���� � ��������� ������.
            while (!reader->eof())
            {
                Node *nested = Load_Node(reader);

                if (!nested)
                {
                    lem_rub_off(node);
                    throw Invalid_Format();
                }

                if (nested->IsComment())
                {
                    // ����������� �������.
                    lem_rub_off(nested);
                }
                else if (nested->IsCData())
                {
                    // ���� <[CData[ ... ]]> ��������� � ����
                    node->body += nested->body;
                    lem_rub_off(nested);
                }
                else if (nested->GetClosing())
                {
                    if (nested->GetName() != node->GetName())
                    {
                        lem_rub_off(node);
                        lem_rub_off(nested);
                        throw Invalid_Format();
                    }

                    // ������ ��������� ����� ��������.
                    node->SetClosed(true);
                    lem_rub_off(nested);
                    break;
                }
                else if (!nested->GetClosed())
                {
                    lem_rub_off(node);
                    lem_rub_off(nested);
                    throw Invalid_Format();
                }

                if (nested != NULL)
                {
                    node->GetNodes().push_back(nested);

                    if (doctype == Parser::HtmlDoc)
                    {
                        node->visible_text += nested->visible_text;
                    }

                    nested = NULL;
                }

                // ���� �� ���������� ����.
                // ��������� �������.
                while (!reader->eof())
                {
                    c = reader->wget();

                    if (c != L' ' && c != L'\t' && c != L'\n' && c != L'\r')
                    {
                        // ��������� �������� ������!
                        reader->unget(c);
                        break;
                    }
                }

                if (reader->eof())
                    break;

                if (c != L'<')
                {
                    if (doctype != Parser::HtmlDoc)
                    {
                        lem_rub_off(node);
                        // ���� ���� ����� ���� ���� ������ ��������� �����, ���� �������.
                        // � ��� ��� ���������� �����.
                        throw Invalid_Format();
                    }
                    else
                    {
                        reader->wget();
                        goto load_tag_body;
                    }
                }
            }
        }
        else
        {

        load_tag_body:

            // �������� ���� ���� - �� ������������.
            node->body.reserve(128);
            bool just_started = true;

            while (!reader->eof())
            {
                lem::Stream::pos_type tpos = reader->tellp();

                if (!just_started)
                    c = reader->wget();
                else
                    just_started = false;

                if (c == L'<')
                {
                    // ������ ������ ����

                    if (reader->wget() == L'/')
                    {
                        // ��� ����������� ���, �� ������ ��������� ������� ���.
                        reader->seekp(tpos);
                        break;
                    }
                    else
                    {
                        // ������������ ��������� ��� (HTML)
                        reader->seekp(tpos);
                        Node *nested = Load_Node(reader);
                        if (!nested || !nested->GetClosed())
                        {
                            throw Invalid_Format();
                        }
                        else if (nested->IsComment())
                        {
                            lem_rub_off(nested);
                        }
                        else if (nested->IsCData())
                        {
                            node->body += nested->body;
                            lem_rub_off(nested);
                        }

                        if (nested != NULL)
                        {
                            node->nodes.push_back(nested);

                            if (doctype == Parser::HtmlDoc)
                            {
                                node->visible_text += nested->visible_text;
                            }
                        }

                        continue;
                    }
                }

                if (c == L'&')
                {
                    // ����� ���� ���� ������������� ��� �������, ���� ��� �������� ���.
                    c = reader->wget();
                    if (c == L'#')
                    {
                        // ��������� hex ��� ������� �� ;
                        UFString hex; hex.reserve(6);
                        while (!reader->eof())
                        {
                            c = reader->wget();
                            if (c == L';' || c == WEOF)
                                break;
                            hex += c;
                        }

                        c = lem::to_int(hex);
                    }
                    else
                    {
                        FString char_name; char_name.reserve(8);
                        char_name += char(c);
                        while (!reader->eof())
                        {
                            c = reader->wget();
                            if (c == L';' || c == WEOF)
                                break;

                            char_name += char(c);
                        }

                        c = lem::CodeConverter::Sgml_2_Char(char_name);
                    }
                }

                node->body += c;

                if (doctype == Parser::HtmlDoc)
                {
                    node->visible_text += c;
                }
            }

            if (reader->wget() != L'<')
            {
                lem_rub_off(node);
                throw Invalid_Format();
            }

            // ������ ������ ���� ����������� ���!
            UFString close_tag;
            Read_Tag(reader, close_tag);

            UFString name2, body2;
            Collect< pair<UFString, UFString> > attrs2;
            Break_Tag(close_tag, name2, attrs2, body2);

            if (doctype == Parser::HtmlDoc && !remove_char(name2, L'/').eqi(node->name))
            {
                lem_rub_off(node);
                throw Invalid_Format();
            }
            else if (remove_char(name2, L'/') != node->name)
            {
                lem_rub_off(node);
                throw Invalid_Format();
            }

            node->SetClosed(true);
        }
    }


    if (doctype == Parser::HtmlDoc)
    {
        // ��������� ���� ����� � HTML ���������� ������ � ����� �����������.
        if (IsTextDelimiterTag(node->GetName()))
        {
            node->visible_text += L' ';
        }
    }

    return node;
}



void Parser::Split_Path(
    const UFString &path,
    Collect<UFString> &steps
)
{
    int i = 0;
    UFString new_step;
    while (true)
    {
        if (path[i] == L'.' || path[i] == 0)
        {
            if (!new_step.empty())
                steps.push_back(new_step);

            new_step.clear();

            if (i >= path.length())
                break;
        }
        else
        {
            new_step += path[i];
        }

        i++;
    }

    return;
}


const Node* Parser::Find_By_Path(const UFString &Path) const
{
    Collect<UFString> steps;
    steps.reserve(16);
    Split_Path(Path, steps);
    return Find_By_Path(steps);
}

lem::UFString Parser::Get_By_Path(const UFString &Path) const
{
    const Node *n = Find_By_Path(Path);
    return n == NULL ? UFString() : n->GetBody();
}



const Node* Parser::Find_By_Path(const Collect<UFString> &Steps) const
{
    if (Steps.empty())
        return NULL;

    if (root->GetName() != Steps.front())
        return NULL;

    const Node *cur = &*root;
    for (Collect<UFString>::const_iterator i = Steps.begin() + 1; i != Steps.end(); i++)
    {
        cur = cur->GetNode(*i);
        if (!cur)
            return NULL;
    }

    return cur;
}


