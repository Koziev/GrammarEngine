#include <string>
#include <boost/python.hpp>

#include <boost/python/tuple.hpp>
#include "../Parser/Parser_API.h"


using namespace boost::python;


class PyParser //: public Parser_API
{
private:
    Parser_API * parser;

public:
    PyParser()
    {
        parser = NULL;
    }

    ~PyParser()
    {
        delete parser;
        parser = 0;
    }

    void Load(const std::wstring & dictionary_path)
    {
        parser = new Parser_API();
        parser->Load(dictionary_path.c_str());
    }

    boost::python::list Tag1(const std::wstring & sentence, bool emit_morph)
    {
        std::unique_ptr<ParsingResults_API> res(parser->TagSentence(sentence.c_str(), emit_morph));

        const ParsingResult_Sentence & sent = res->GetSentence();
        boost::python::list res_list;

        for (int i = 0; i < sent.tokens.size(); ++i)
        {
            const ParsingResult_Token & token = sent.tokens[i];

            boost::python::list tags;
            if (emit_morph)
            {
                for (int j = 0; j < token.tags.size(); ++j)
                {
                    auto tag = boost::python::make_tuple(token.tags[j].tag_name, token.tags[j].tag_value);
                    tags.append(tag);
                }
            }

            auto token_info = boost::python::make_tuple( token.word, token.lemma, token.part_of_speech, tags);

            res_list.append(token_info);
        }

        return res_list;
    }
};


BOOST_PYTHON_MODULE(pyparser)
{
    class_<PyParser>("PyParser") //, init<>() 
        .def("load", &PyParser::Load)
        .def("tag1", &PyParser::Tag1)
        ;
}
