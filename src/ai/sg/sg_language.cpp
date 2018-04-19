// -----------------------------------------------------------------------------
// File SG_LANGUAGE.CPP
//
// (c) Koziev Elijah
//
// Content:
// SG_Language - language specification.
// -----------------------------------------------------------------------------
//
// CD->04.07.2005
// LC->16.04.2018
// --------------

#include <lem/macro_parser.h>

#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/gg_autom.h>
#include <lem/solarix/sg_autom.h>

using namespace lem;
using namespace Solarix;

SG_LanguageParam::SG_LanguageParam(const SG_LanguageParam &x)
    : name(x.name), values(x.values)
{}


void SG_LanguageParam::operator=(const SG_LanguageParam &x)
{
    name = x.name;
    values = x.values;
    return;
}

#if defined SOL_SAVEBIN
void SG_LanguageParam::SaveBin(lem::Stream &bin) const
{
    bin.write(&name, sizeof(name));
    values.SaveBin(bin);
    return;
}
#endif

#if defined SOL_LOADBIN
void SG_LanguageParam::LoadBin(lem::Stream &bin)
{
    bin.read(&name, sizeof(name));
    values.LoadBin(bin);
    return;
}
#endif


SG_Language::SG_Language()
{
    id = UNKNOWN;
}

SG_Language::SG_Language(const SG_Language &x)
    : id(x.id), name(x.name), alphabet(x.alphabet), lang_links(x.lang_links), params(x.params)
#if defined SOL_LOADTXT && defined SOL_COMPILER
    , c_name(x.c_name)
#endif
{}

void SG_Language::operator=(const SG_Language &x)
{
    id = x.id;
    name = x.name;
    alphabet = x.alphabet;
    lang_links = x.lang_links;
#if defined SOL_LOADTXT && defined SOL_COMPILER
    c_name = x.c_name;
#endif
    params = x.params;
    return;
}

void SG_Language::Copy_Definition(const SG_Language &x)
{
    alphabet = x.alphabet;
    lang_links = x.lang_links;
#if defined SOL_LOADTXT && defined SOL_COMPILER
    if (!x.c_name.empty())
        c_name = x.c_name;
#endif
    params = x.params;
    return;
}


bool SG_Language::IsMainAlphabet(int id_alphabet) const
{
    return alphabet.find(id_alphabet) == 0;
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
void SG_Language::LoadTxt(int Id, Macro_Parser& txt, GraphGram& gram)
{
    // Store the beginning of language specification
    BSourceState beg = txt.tellp();

    id = Id;

    name = txt.read().string();

    const bool Me = gram.GetDict().GetDebugLevel_ir() >= 3;
    if (Me)
    {
        // Эхо-сообщение: начали трансляцию языка.
        gram.GetIO().mecho().printf(
            "%us [%vfE%us%vn]->",
            sol_get_token(B_LANGUAGE).c_str(),
            name.c_str()
        );
    }


    BethToken t = txt.read();
    if (t.GetToken() == B_AS)
    {
        c_name = txt.read().string();
        t = txt.read();
    }

    if (t.GetToken() != B_OFIGPAREN)
    {
        // Пустое объявление языка.
        txt.seekp(t.GetBegin());
    }
    else
    {
        // Load the list of alphabets, allowed for the language. Also do load other
        // language parameters.
        while (!txt.eof())
        {
            BethToken t = txt.read();

            if (t.GetToken() == B_CFIGPAREN)
                break;

            if (t.GetToken() == B_ALPHABET)
            {
                // Add the valid alphabet name for this language

                BethToken abc_name = txt.read();
                int id_abc = gram.Find_Alphabet(abc_name.string());

                if (id_abc == UNKNOWN)
                {
                    lem::Iridium::Print_Error(abc_name, txt);
                    gram.GetIO().merr().printf("Unknown alphabet [%us] used in in language [%us] specification\n", abc_name.string().c_str(), name.c_str());
                    throw E_ParserError();
                }

                alphabet.push_back(id_abc);
                continue;
            }
            else if (t.GetToken() == B_LINK)
            {
                Tree_Link l;
                l.LoadTxt(txt, gram.GetDict().GetSynGram());

                txt.read_it(B_LANGUAGE);
                BethToken lang_name = txt.read();

                int id_lang = gram.GetDict().GetSynGram().Find_Language(lang_name);
                if (id_lang == UNKNOWN)
                {
                    lem::Iridium::Print_Error(lang_name, txt);
                    gram.GetIO().merr().printf("Unknown language [%us] used in in language [%us] specification\n", lang_name.string().c_str(), name.c_str());
                    throw E_ParserError();
                }

                lang_links.push_back(std::make_pair(l, id_lang));
                continue;
            }
            else
            {
                // Синтаксис задания параметра: 
                // 1. скалярный param_name = value
                // 2. векторный param_name = { value1 values2 ... }

                if (txt.pick().GetToken() == B_EQUAL)
                {
                    txt.read_it(B_EQUAL);
                    SG_LanguageParam *param = new SG_LanguageParam;
                    param->name = t;

                    if (txt.pick().GetToken() == B_OFIGPAREN)
                    {
                        txt.read_it(B_OFIGPAREN);

                        while (!txt.eof())
                        {
                            if (txt.pick().GetToken() == B_CFIGPAREN)
                            {
                                txt.read_it(B_CFIGPAREN);
                                break;
                            }

                            UFString v = txt.read().GetFullStr();
                            v.strip(L'"');
                            v.trim();
                            param->values.push_back(v);
                        }
                    }
                    else
                    {
                        param->values.push_back(lem::trim(lem::UFString(txt.read().GetFullStr())));
                    }

                    params.push_back(param);

                    continue;
                }
            }

            lem::Iridium::Print_Error(t, txt);
            gram.GetIO().merr().printf("Invalid token in language [%us] specification\n", name.c_str());
            throw E_ParserError();
        }
    }

    if (Me)
    {
        // Эхо-сообщение: закончили трансляцию.
        gram.GetIO().mecho().printf("%vfAOK%vn\n");
    }

    return;
}
#endif


#if defined SOL_SAVEBIN
void SG_Language::SaveBin(lem::Stream &bin) const
{
    bin.wr(&id);
    bin.wr(&name);
    alphabet.SaveBin(bin);
    lang_links.SaveBin(bin);
    params.SaveBin(bin);

    return;
}
#endif

#if defined SOL_LOADBIN
void SG_Language::LoadBin(lem::Stream &bin)
{
    bin.rd(&id);
    bin.rd(&name);
    alphabet.LoadBin(bin);
    lang_links.LoadBin(bin);
    params.LoadBin(bin);

    return;
}
#endif


#if defined SOL_COMPILER
void SG_Language::SubstParadigmPattern(lem::UFString &pattern) const
{
    for (lem::Container::size_type i = 0; i < params.size(); ++i)
    {
        if (params.get(i)->name.eqi(L"ParadigmSubst"))
        {
            if (params[i]->values.size() != 2)
            {
                const Solarix::SG_LanguageParam & p = *params[i];
                // ...
                LEM_STOPIT;
            }

            const UFString &from = params[i]->values.front();
            const UFString &to = params[i]->values.back();
            pattern.subst_all(from, to);
        }
    }

    return;
}
#endif


int SG_Language::FindParam(const UCString & name, int ifrom) const
{
    for (lem::Container::size_type i = ifrom; i < params.size(); ++i)
    {
        if (params[i]->name.eqi(name))
            return CastSizeToInt(i);
    }

    return UNKNOWN;
}


int SG_Language::FindLastParam(const UCString & name) const
{
    for (int i = CastSizeToInt(params.size()) - 1; i >= 0; --i)
    {
        if (params[i]->name.eqi(name))
            return CastSizeToInt(i);
    }

    return UNKNOWN;
}
