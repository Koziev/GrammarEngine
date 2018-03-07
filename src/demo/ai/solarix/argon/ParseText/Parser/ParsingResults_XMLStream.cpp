#include "ParsingResults_XMLStream.h"


ParsingResults_XMLStream::ParsingResults_XMLStream(lem::OFormatter & stream)
    :out_stream(stream)
{}



lem::UFString ParsingResults_XMLStream::EncodeStrXml(const wchar_t * src) const
{
    lem::UFString res;

    if (res.find(L'&') != -1 || res.find(L'<') != -1 || res.find(L'>') != -1)
    {
        int i = 0;
        while (src[i] != 0)
        {
            if (src[i] == L'&')
                res += L"&amp;";
            else if (src[i] == L'<')
                res += L"&lt;";
            else if (src[i] == L'>')
                res += L"&gt;";
            else
                res += src[i];

            i++;
        }
    }
    else
    {
        res = src;
    }

    return res;
}


void ParsingResults_XMLStream::Start()
{
    out_stream.printf("<?xml version='1.0' encoding='utf-8' ?>\n<parsing>\n");
}

void ParsingResults_XMLStream::End()
{
    out_stream.printf("\n</parsing>");
    out_stream.close();
}

void ParsingResults_XMLStream::Flush()
{
    out_stream.flush();
}

void ParsingResults_XMLStream::StartSentence(const lem::UFString & sentence_str, int paragraph_id)
{
    lem::UFString xml_str = EncodeStrXml(sentence_str.c_str());
    out_stream.printf("\n\n<sentence paragraph_id='%d'>\n<text>%us</text>\n", paragraph_id, xml_str.c_str());
}


void ParsingResults_XMLStream::EndSentence()
{
    out_stream.printf("</sentence>\n");
}


void ParsingResults_XMLStream::StartChunking()
{
    out_stream.printf("\n<chunks>\n");
}

void ParsingResults_XMLStream::PrintChunking(int word_position, int chunk_label)
{
    out_stream.printf(" <token word_index='%d' is_chunk_starter='%d'/>\n", word_position, chunk_label);
}

void ParsingResults_XMLStream::EndChunking()
{
    out_stream.printf("</chunks>\n");
}


void ParsingResults_XMLStream::StartTokens()
{
    out_stream.printf("<tokens>\n");
}


void ParsingResults_XMLStream::StartToken()
{
    out_stream.printf("<token>\n");
}

void ParsingResults_XMLStream::EndToken()
{
    out_stream.printf("</token>\n");
}


void ParsingResults_XMLStream::PrintToken(
    bool known_word,
    const wchar_t * word,
    const wchar_t * lemma,
    int position,
    const wchar_t * part_of_speech)
{
    lem::UFString sword(EncodeStrXml(word));
    lem::UFString slemma(EncodeStrXml(lemma));

    out_stream.printf("<word%s>%us</word>\n", (known_word ? "" : " is_unknown='true'"), sword.c_str());
    out_stream.printf("<position>%d</position>\n", position);
    out_stream.printf("<lemma>%us</lemma>\n", slemma.c_str());
    out_stream.printf("<part_of_speech>%us</part_of_speech>\n", part_of_speech);
}


void ParsingResults_XMLStream::StartTags()
{
    out_stream.printf("<tags>");
}

void ParsingResults_XMLStream::EndTags()
{
    out_stream.printf("</tags>");
}


void ParsingResults_XMLStream::PrintTag(int tag_counter, const wchar_t * tag_name, const wchar_t * tag_value)
{
    if (tag_counter > 0)
    {
        out_stream.printf("|");
    }

    out_stream.printf("%us:%us", tag_name, tag_value);
}



void ParsingResults_XMLStream::EndTokens()
{
    out_stream.printf("</tokens>\n");
}

void ParsingResults_XMLStream::PrintTreeRendering(const wchar_t * tree_rendering)
{
    lem::UFString encoded_tree = EncodeStrXml(tree_rendering).subst_all('\r', ' ');
    out_stream.printf("<syntax_tree_rendering>\n<![CDATA[\n%us\n]]>\n</syntax_tree_rendering>\n", encoded_tree.c_str());
}


void ParsingResults_XMLStream::StartSyntaxTree()
{
    out_stream.printf("\n<syntax_tree>\n");
}

void ParsingResults_XMLStream::EndSyntaxTree()
{
    out_stream.printf("</syntax_tree>\n");
}


void ParsingResults_XMLStream::PrintSyntaxNode(
    bool is_root,
    bool is_orphant,
    const wchar_t * word,
    int word_pos,
    const wchar_t * edge_name,
    int parent_index,
    const wchar_t * parent_word_str
)
{
    lem::UFString node_word(EncodeStrXml(word));

    if (is_root)
    {
        out_stream.printf("<node is_root='true'><token>%d</token><word>%us</word><parent>-1</parent><link_type>ROOT</link_type></node>\n", word_pos, node_word.c_str());
    }
    else if (is_orphant)
    {
        out_stream.printf("<node is_orphant='true'><token>%d</token><word>%us</word><parent>-1</parent><link_type>UNKNOWN</link_type></node>\n", word_pos, node_word.c_str());
    }
    else
    {
        lem::UFString parent_word(EncodeStrXml(parent_word_str));
        out_stream.printf("<node><token>%d</token><word>%us</word><parent>%d</parent><parent_word>%us</parent_word><link_type>%us</link_type></node>\n", word_pos, node_word.c_str(), parent_index, parent_word.c_str(), edge_name);
    }
}
