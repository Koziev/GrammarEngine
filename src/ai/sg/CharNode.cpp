#include <lem/solarix/prefix_tree.h>
#include <lem/solarix/sg_autom.h>

using namespace std;
using namespace lem;
using namespace Solarix;

CharNode::~CharNode()
{
    for (auto k = leafs.begin(); k != leafs.end(); k++)
        delete k->second;

    return;
}

CharNode* CharNode::find(wchar_t c, bool add)
{
    auto k = leafs.find(c);
    if (k == leafs.end())
    {
        if (add)
        {
            CharNode* leaf = new CharNode;
            leafs.insert(std::make_pair(c, leaf));
            return leaf;
        }
        else
        {
            return nullptr;
        }
    }
    else
    {
        return k->second;
    }
}

const CharNode* CharNode::probe(wchar_t c) const
{
    auto k = leafs.find(c);
    return k == leafs.end() ? nullptr : k->second;
}


bool CharNode::match(const UCString &str) const
{
    const CharNode *n = this;
    int icur = 0;

    while (n != nullptr && icur < str.length())
    {
        n = n->probe(lem::to_uupper(str[icur++]));
    }

    return n != nullptr;
}


// ****************************************************************************
// Вернет максимальную длину лексемы, которую можно найти с начала строки str,
// и такую что в лексиконе есть такая словоформа.
// ****************************************************************************
int CharNode::match_len(const wchar_t * str) const
{
    const CharNode *n = this;
    int icur = 0;

    int lexem_len = 0;

    while (n != nullptr && str[icur] != 0)
    {
        const wchar_t c = lem::to_uupper(str[icur]);
        n = n->probe(c);
        if (n == nullptr)
            break;

        icur++;

        if (!n->entries.empty())
            lexem_len = icur;
    }

    return lexem_len;
}

