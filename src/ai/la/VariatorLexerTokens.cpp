#include <lem/solarix/dictionary.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/variator.h>
#include <lem/solarix/LexerTextPos.h>
#include <lem/solarix/PreparedLexer.h>

using namespace Solarix;


VariatorLexerTokens::VariatorLexerTokens(const Variator & _var, Solarix::Dictionary * _dict)
    : var(_var)
{
    Refresh(_dict);
}


VariatorLexerTokens::~VariatorLexerTokens()
{
    for (auto token : tokens)
    {
        delete token;
    }

    return;
}

int VariatorLexerTokens::Size() const { return var.size(); }

void VariatorLexerTokens::Refresh(Solarix::Dictionary * dict)
{
    for (auto token : tokens)
    {
        delete token;
    }

    tokens.clear();
    word2token.clear();

    LexerTextPos * t0 = new LexerTextPos_BeyondLeft(nullptr);
    tokens.push_back(t0);

    const int END_KEY = dict->GetSynGram().I_END;

    const LexerTextPos * prev = t0;
    for (int i = 0; i < var.size(); ++i)
    {
        const Word_Form & wf = var.get(i).GetNode();

        if (i == var.size() - 1 && wf.GetEntryKey() == END_KEY)
        {
            LexerTextPos_End * t = new LexerTextPos_End(prev, &wf);
            tokens.push_back(t);
            word2token.push_back(t);
            prev = t;
        }
        else
        {
            LexerTextPos * t = new LexerTextPos(prev, &wf, 0, 0, wf.GetName()->length(), wf.GetOriginPos());
            tokens.push_back(t);
            word2token.push_back(t);
            prev = t;
        }
    }

    LexerTextPos * t = new LexerTextPos_Terminator();
    tokens.push_back(t);
    right_terminator = t;

    return;
}

void VariatorLexerTokens::Print(lem::OFormatter & out, Dictionary & dict) const
{
    for (int i = 0; i < var.size(); ++i)
    {
        out.printf("#%d: ", i);
        var.get(i).Print(out, dict.GetSynGram(), -1, false);
        out.eol();
    }

    return;
}

