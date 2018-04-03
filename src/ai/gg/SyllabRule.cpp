#include <lem/macro_parser.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/AlphabetStorage.h>
#include <lem/solarix/SyllabRule.h>

using namespace Solarix;

SyllabRule::SyllabRule()
{
    id_src = id_language = UNKNOWN;
    return;
}


SyllabRule::SyllabRule(const lem::UCString &_name, int _id_src, int _id_language)
    : name(_name), id_src(_id_src), id_language(_id_language)
{
}



#if defined SOL_LOADTXT && defined SOL_COMPILER
void SyllabRule::LoadTxt(lem::Iridium::Macro_Parser &txtfile, Dictionary &dict)
{
    lem::Iridium::BSourceState point_begin = txtfile.tellp();
    id_src = dict.GetDebugSymbols().RegisterLocation(txtfile, point_begin);

    // шапка: syllab_rule XXXX language=YYY
    name = txtfile.read().string();
    txtfile.read_it(B_LANGUAGE);
    txtfile.read_it(B_EQUAL);
    lem::Iridium::BethToken lang = txtfile.read();
    id_language = dict.GetSynGram().Find_Language(lang.string());
    if (id_language == UNKNOWN)
    {
        lem::Iridium::Print_Error(lang, txtfile);
        dict.GetIO().merr().printf("Unknown language name %us\n", lang.c_str());
        throw lem::E_BaseException();
    }

    txtfile.read_it(B_OFIGPAREN);

    txtfile.read_it(B_IF);
    txtfile.read_it(B_CONTEXT);

    condition.LoadTxt(txtfile, dict);

    txtfile.read_it(B_THEN);
    txtfile.read_it(B_OFIGPAREN);
    txtfile.read_it(B_CONTEXT);

    result.LoadTxt(txtfile, dict, condition);

    txtfile.read_it(B_CFIGPAREN); // закрываем блок then { ... }

    txtfile.read_it(B_CFIGPAREN); // закрываем тело правила

    return;
}
#endif


void SyllabRule::Store(AlphabetStorage * storage) const
{
    const int id_rule = storage->StoreSyllabRule(GetName(), GetLanguage(), GetSource(), GetResult().GetShift());

    GetCondition().Store(storage, id_rule);
    GetResult().Store(storage, id_rule);

    return;
}

