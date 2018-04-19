#include <lem/macro_parser.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/LA_CropRule.h>

using namespace lem;
using namespace Solarix;

LA_CropRule::LA_CropRule()
    : id(UNKNOWN), id_language(UNKNOWN), src_location(UNKNOWN), rel(100)
{
}


LA_CropRule::LA_CropRule(
    int Id,
    const lem::UCString &Name,
    int Id_Lang,
    bool IsPrefix,
    bool IsAffix,
    bool IsCaseSensitive,
    bool IsRegex,
    const lem::UFString &Condition,
    const lem::UFString &Result,
    int SourceID,
    lem::Real1 Rel
)
    : id(Id), name(Name), id_language(Id_Lang), is_prefix(IsPrefix), is_affix(IsAffix), condition(Condition),
    result(Result.c_str()), rx_result(Result), case_sensitive(IsCaseSensitive), is_regex(IsRegex), src_location(SourceID), rel(Rel)
{
    LEM_CHECKIT_Z(id != UNKNOWN);
    LEM_CHECKIT_Z(id_language == UNKNOWN || id_language >= 0);
    LEM_CHECKIT_Z(!condition.empty());
    LEM_CHECKIT_Z(is_prefix || is_affix);

    if (is_regex)
    {
        if (case_sensitive)
            rx_condition = boost::wregex(condition.c_str());
        else
            rx_condition = boost::wregex(condition.c_str(), boost::regex_constants::icase);
    }

    return;
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
void LA_CropRule::CompileCondition(const lem::UFString &Condition)
{
    if (is_regex)
    {
        if (case_sensitive)
            rx_condition = boost::wregex(condition.c_str());
        else
            rx_condition = boost::wregex(condition.c_str(), boost::regex_constants::icase);
    }
    else if (Condition.front() == L'$')
    {
        // Отсечение префикса
        is_prefix = true;
        condition = Condition.c_str() + 1;
    }
    else if (Condition.back() == L'$')
    {
        // Отсечение аффикса
        is_affix = true;
        condition = lem::left(Condition, Condition.length() - 1);
    }
    else
    {
        LEM_STOPIT;
    }
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
void LA_CropRule::LoadTxt(lem::Iridium::Macro_Parser &txtfile, Dictionary &dict)
{
    src_location = dict.GetDebugSymbols().RegisterLocation(txtfile, txtfile.tellp());

    // опциональное имя
    while (!txtfile.eof())
    {
        lem::Iridium::BethToken t0 = txtfile.read();
        if (t0.GetToken() == B_OFIGPAREN)
        {
            break;
        }
        else if (t0.GetToken() == B_LANGUAGE)
        {
            // дальше идет наименование языка, в рамках которого действует правило.
            txtfile.read_it(B_EQUAL);
            lem::Iridium::BethToken t1 = txtfile.read();
            id_language = dict.GetSynGram().Find_Language(t1.string());
            if (id_language == UNKNOWN)
            {
                lem::Iridium::Print_Error(t1, txtfile);
                dict.GetIO().merr().printf("Unknown language name %us\n", t1.c_str());
                throw lem::E_BaseException();
            }

            txtfile.read_it(B_OFIGPAREN);
            break;
        }
        else if (name.empty())
        {
            // просто имя правила
            name = t0.string();
            name.strip_quotes();
        }
        else
        {
            lem::Iridium::Print_Error(t0, txtfile);
            dict.GetIO().merr().printf("Unexpected token %us\n", t0.c_str());
            throw lem::E_BaseException();
        }
    }

    txtfile.read_it(B_IF);

    case_sensitive = txtfile.probe(L"@");
    is_regex = txtfile.probe(L"~");

    lem::Iridium::BSourceState t_condition = txtfile.tellp();

    lem::UFString Condition = txtfile.read().GetFullStr();
    Condition.strip(L'"');
    CompileCondition(Condition);

    txtfile.read_it(B_THEN);

    lem::Iridium::BethToken rt = txtfile.read();
    result = rt.string();
    result.strip(L'"');
    rx_result = rt.GetFullStr();
    rx_result.strip(L'"');

    if (txtfile.probe(B_EQUAL))
    {
        // указана достоверность правила
        rel = lem::Real1(txtfile.read_int());
    }


    txtfile.read_it(B_CFIGPAREN);

    return;
}
#endif


bool LA_CropRule::Apply(const lem::UCString &word, lem::UCString &result_word) const
{
    bool res = false;

    if (is_regex)
    {
        std::wstring in(word.c_str());
        result_word = boost::regex_replace(in, rx_condition, rx_result.c_str(), boost::match_default | boost::format_all).c_str();
    }
    else if (is_prefix)
    {
        res = word.eq_begi(condition.c_str());
        if (res)
        {
            result_word = result + UCString(word.c_str() + condition.length());
        }
    }
    else if (is_affix)
    {
        res = word.eq_endi(condition.c_str());
        if (res)
        {
            result_word = lem::left(word, word.length() - condition.length()) + result;
        }
    }
    else
    {
        LEM_STOPIT;
    }

    return res;
}


LA_CropRule::HashType LA_CropRule::GetHash(void)
{
    return LA_CropRule::CalcHash(condition.c_str(), is_prefix, is_affix);
}


LA_CropRule::HashType LA_CropRule::CalcHash(const wchar_t *str, bool IsPrefix, bool IsAffix)
{
    if (IsPrefix)
        return lem::to_uupper(str[0]);
    else if (IsAffix)
        return lem::to_uupper(str[lem::lem_strlen(str) - 1]);
    else
    {
        LEM_STOPIT;
        return 0;
    }
}
