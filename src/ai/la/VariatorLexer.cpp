#include <lem/solarix/variator.h>
#include <lem/solarix/LexerTextPos.h>
#include <lem/solarix/PreparedLexer.h>

using namespace Solarix;


VariatorLexer::VariatorLexer(
    const VariatorLexerTokens & _var,
    int _start_token,
    Solarix::Dictionary * _dict,
    const TextRecognitionParameters & _params,
    TrTrace * _trace
)
    : BasicLexer(_dict, _params, _trace), var(_var), start_token(_start_token)
{
    const LexerTextPos * t = var.GetToken(start_token);
    begin_token = t;
    token2pos.insert(std::make_pair(t, start_token));
}


bool VariatorLexer::Fetch(const LexerTextPos * current, const TokenExpectation * unused, lem::MCollect<const LexerTextPos*> & next)
{
    std::map<const LexerTextPos*, const LexerTextPos*>::const_iterator it = t2next.find(current);
    if (it != t2next.end())
    {
        next.push_back(it->second);
        return true;
    }

    std::map<const LexerTextPos*, int>::const_iterator it_pos = token2pos.find(current);
    if (it_pos == token2pos.end())
        return false;

    const int current_pos = it_pos->second;

    if (current_pos + 1 < var.Size())
    {
        // —ледующа€ синтаксема становитс€ новым токеном.
        const LexerTextPos * next_token = var.GetToken(current_pos + 1);
        t2next.insert(std::make_pair(current, next_token));
        token2pos.insert(std::make_pair(next_token, current_pos + 1));
        next.push_back(next_token);
        return true;
    }
    else
    {
        // ѕравый край цепочки синтаксем, возвращаем терминатор.
        const LexerTextPos * t = var.GetRightTerminator();
        next.push_back(t);
        return false;
    }
}
