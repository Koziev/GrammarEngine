// -----------------------------------------------------------------------------
// File TREE_NODE.CPP
//
// (c) Koziev Elijah https://github.com/Koziev/GrammarEngine
//
// Content:
// Класс Tree_Node - узел сминтаксического графа. Используется для построения
// Синтаксических Деревьев, Результатных частей трансформант синтаксических
// правил. Общий случай ГРАММАТИЧЕСКИХ ДЕРЕВЬЕВ.
//
// 11.10.2011 - добавлена сериализация в XML
// -----------------------------------------------------------------------------
//
// CD->14.11.1995
// LC->02.04.2018
// --------------

#if !defined SOL_NO_AA

#include <lem/conversions.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/tree_node.h>

using namespace lem;
using namespace Solarix;


Tree_Node::Tree_Node(void)
{
#if defined SOL_CAA
    // label=UNKNOWN;
#endif
}

Tree_Node::Tree_Node(const Tree_Node& tn)
{
    Init(tn);
    return;
}


#if defined SOL_LOADBIN
Tree_Node::Tree_Node(lem::Stream &bin)
{
#if defined SOL_CAA
    // label=UNKNOWN;
#endif

    LoadBin(bin);
    return;
}
#endif


Tree_Node::Tree_Node(const Word_Form& s)
{
    node = new Word_Form(s);
    // org_node = new Word_Form(s);
#if defined SOL_CAA
// label=UNKNOWN;
#endif
    return;
}

Tree_Node::Tree_Node(Word_Form *s, bool dummy)
    : node(s)
{
    // org_node = new Word_Form(*s);
#if defined SOL_CAA
// label=UNKNOWN;
#endif
    return;
}


void Tree_Node::ForgetChild(int ichild)
{
    child.Forget(ichild);
    return;
}

void Tree_Node::ClearChildren(void)
{
    child.Clear();
    return;
}


void Tree_Node::operator=(const Tree_Node& tn)
{
    if (&tn == this)
        return;

    Init(tn);
    return;
}


void Tree_Node::Init(const Tree_Node& tn)
{
    LEM_CHECKIT_Z(&tn != nullptr);

    node = tn.node;
    // org_node = tn.org_node;
    ilink = tn.ilink;
    child = tn.child;
    dims = tn.dims;
    marks = tn.marks;
#if defined SOL_CAA
    // label    = tn.label;
#endif
    return;
}

Tree_Node* Tree_Node::DeepCopy(void) const
{
    Tree_Node *res = new Tree_Node();

    res->node = new Word_Form(GetNode(), true);

    // if( org_node.NotNull() )
    //  res->org_node = new Word_Form( *org_node, true );

    res->ilink = ilink;

    for (lem::Container::size_type i = 0; i < child.size(); ++i)
        res->child.Add(child[i].DeepCopy());

    res->dims = dims;
    res->marks = marks;
#if defined SOL_CAA
    // res->label    = label;
#endif

    return res;
}




#if defined SOL_CAA
/***********************************************************
 Отрезается ветка с индексом ichild, указатель на эту ветку
 освобождается и список указателей на ветки сжимается.
************************************************************/
void Tree_Node::Remove(int ichild)
{
    child.Remove(ichild);
    return;
}
#endif


bool Tree_Node::DoesMatch(SynGram &sg, const Tree_Node& tn, bool strict_position) const
{
    if (
        child.size() != tn.child.size() ||
        !GetNode().DoesMatch(sg, tn.GetNode())
        )
        return false;

    for (lem::Container::size_type i = 0; i < child.size(); i++)
        if (!child[i].DoesMatch(sg, tn.child[i], strict_position))
        {
            // Обнаружилось несоответствие. Если разрешено сравнение без учета порядка
            // веток strict_position=false, то придется входить в тяжелый алгоритм.
            if (strict_position)
                return false;

            lem::MCollect<const Tree_Node*> this_nodes;
            for (lem::Container::size_type j = i; j < child.size(); j++)
                this_nodes.push_back(&child[j]);

            // Для каждой из оставшихся веток в tn надо искать соответствие в this_nodes.
            {
                for (lem::Container::size_type j = i; j < child.size(); j++)
                {
                    bool matched = false;
                    for (lem::Container::size_type k = 0; k < this_nodes.size(); ++k)
                    {
                        if (this_nodes[k]->DoesMatch(sg, tn.child[j], strict_position))
                        {
                            matched = true;
                            this_nodes.Remove(k);
                            break;
                        }
                    }

                    if (!matched)
                        return false;
                }
            }

            return true;
        }

    return true;
}

#if defined SOL_SAVEBIN
void Tree_Node::SaveBin(lem::Stream &bin) const
{
    bin.write(&ilink, sizeof(ilink));
    node->SaveBin(bin);
    child.SaveBin(bin);
    dims.SaveBin(bin);
    return;
}
#endif


#if defined SOL_LOADBIN
void Tree_Node::LoadBin(lem::Stream &bin)
{
    bin.read(&ilink, sizeof(ilink));

    Word_Form *wf = new Word_Form;
    wf->LoadBin(bin);
    node = boost::shared_ptr<Word_Form>(wf);

    child.LoadBin(bin);
    dims.LoadBin(bin);

    return;
}
#endif


// *********************************************************************
// Если такое измерение уже есть, то просто возвращает ссылку на него.
// Если нет - создает измерение и опять-таки возвращает ссылку на него.
// *********************************************************************
TreeDimension& Tree_Node::TouchDimension(const UCString &name)
{
    if (name.empty())
        return child;

    for (lem::Container::size_type i = 0; i < dims.size(); ++i)
        if (dims[i]->GetName() == name)
            return *dims[i];

    dims.push_back(new TreeDimension(name));
    return *dims.back();
}

const TreeDimension& Tree_Node::leafs(const UCString &name) const
{
    if (name.empty())
        return child;

    for (lem::Container::size_type i = 0; i < dims.size(); ++i)
        if (dims[i]->GetName() == name)
            return *dims[i];

    throw E_BaseException();
}


TreeDimension& Tree_Node::leafs(const UCString &name)
{
    if (name.empty())
        return child;

    for (lem::Container::size_type i = 0; i < dims.size(); ++i)
        if (dims[i]->GetName() == name)
            return *dims[i];

    throw E_BaseException();
}


/***********************************************************************
 Поиск ветки, подключенной к данной посредством связки типа ilink.
 Процедура вернет UNKNOWN, если поиск безрезультатен. Обрати внимание,
 что ищется только ОДНА ветка.
************************************************************************/
int Tree_Node::FindLinkedBy(Tree_Link ilink) const
{
    for (Container::size_type i = 0; i < child.size(); i++)
        if (ilink == GetLinkIndex(i))
            return i;

    return UNKNOWN;
}


void Tree_Node::PrintXML(OFormatter &xml, SynGram &gram) const
{
    xml.printf("<node>");

    xml.printf("<wordform>");
    if (!node.IsNull())
        node->PrintXML(xml, gram);
    xml.printf("</wordform>");

    if (!child.Empty())
    {
        xml.printf("<leaves count=\"%d\">", CastSizeToInt(child.size()));
        for (Container::size_type i = 0; i < child.size(); i++)
        {
            int link_type_id = child[i].GetLink().GetState();
            lem::UCString link_name = link_type_id == UNKNOWN ? L"" : gram.GetLink(link_type_id);
            xml.printf("<leaf n=\"%d\" arc_type=\"%d\" arc_name=\"%us\">\n", CastSizeToInt(i), link_type_id, link_name.c_str());
            child[i].PrintXML(xml, gram);
            xml.printf("</leaf>\n");
        }
        xml.printf("</leaves>");
    }

    if (!dims.empty())
    {
        xml.printf("<dims count=\"%d\">", CastSizeToInt(dims.size()));
        for (lem::Container::size_type i = 0; i < dims.size(); ++i)
        {
            const TreeDimension &d = *dims[i];
            xml.printf("<dim n=\"%d\" name=\"%us\">\n", CastSizeToInt(i), d.GetName().c_str());
            d.PrintXML(xml, gram.GetDict());
            xml.printf("</dim>\n");
        }
        xml.printf("</dims>");
    }

    if (!marks.empty())
    {
        xml.printf("<marks count=\"%d\">", CastSizeToInt(marks.size()));
        for (lem::Container::size_type i = 0; i < marks.size(); ++i)
        {
            xml.printf("<mark n=\"%d\">\n", CastSizeToInt(i));
            marks[i]->PrintXML(xml, gram.GetDict());
            xml.printf("</mark>\n");
        }
        xml.printf("</marks>");
    }

    xml.printf("</node>");

    return;
}


void Tree_Node::Print(OFormatter &txtfile, SynGram &gram, int offset, bool detailed) const
{
    int Offset = offset;

    if (offset > 0)
        txtfile.printf("%H ", offset);

    ilink.Print(txtfile, gram);

    if (node.IsNull())
        txtfile.printf("%vfC(null)%vn");
    else
        node->Print(txtfile, &gram, detailed);

    if (!child.Empty())
    {
        if (detailed)
        {
            txtfile.printf('.');

            if (child.size() != 1)
                txtfile.printf('{');
        }

        if (Offset != -1)
        {
            txtfile.eol();
            Offset++;
        }

        for (Container::size_type i = 0; i < child.size(); i++)
        {
            if (Offset == -1 && i)
                txtfile.printf(' ');

            if (Offset != -1)
                txtfile.printf("%H ", Offset);

            child[i].Print(txtfile, gram, Offset, detailed);
        }

        if (detailed)
        {
            if (offset != -1)
                txtfile.printf("%H ", Offset - 1);

            if (child.size() != 1)
                txtfile.printf('}');
        }
    }

    if (!dims.empty())
    {
        for (lem::Container::size_type i = 0; i < dims.size(); ++i)
        {
            const TreeDimension &d = *dims[i];
            txtfile.printf(' ');
            d.Print(gram.GetDict(), txtfile, detailed);
        }
    }

    if (detailed && !marks.empty())
    {
        txtfile.printf(" %vf6marks={%vn");

        for (lem::Container::size_type i = 0; i < marks.size(); ++i)
        {
            txtfile.printf(' ');
            marks[i]->Print(gram.GetDict(), txtfile);
        }

        txtfile.printf(" %vf6}%vn");
    }

    if (Offset != -1)
        txtfile.eol();

    return;
}


void Tree_Node::PrintPlain(OFormatter &s, bool EntryKey) const
{
    GetNode().PrintPlain(s, EntryKey);

    if (!child.Empty())
    {
        s.printf(" ( ");
        for (Container::size_type i = 0; i < child.size(); i++)
        {
            if (i)
                s.printf(", ");

            child[i].PrintPlain(s, EntryKey);
        }

        s.printf(" ) ");
    }

    return;
}


#if defined SOL_SAVETXT
void Tree_Node::SaveTxt(
    OFormatter &txtfile,
    SynGram &gram,
    int Offset,
    bool detailed
) const
{
    int offset = Offset;

    ilink.SaveTxt(txtfile, gram);
    GetNode().SaveTxt(txtfile, gram, detailed);

    if (!child.Empty())
    {
        if (detailed)
        {
            txtfile << sol_get_token(B_DOT);

            if (child.size() != 1)
                txtfile << sol_get_token(B_OFIGPAREN);
        }

        if (offset != -1)
        {
            offset = txtfile.GetPos();
            txtfile.eol();
        }

        for (Container::size_type i = 0; i < child.size(); i++)
        {
            int of = offset;

            if (of == -1 && i)
                txtfile.printf(' ');

            if (of != -1)
                txtfile.printf("%H ", of);

            child[i].SaveTxt(txtfile, gram, of, detailed);
        }

        if (detailed)
        {
            if (offset != -1)
                txtfile.printf("%H ", offset - 1);

            if (child.size() != 1)
                txtfile << sol_get_token(B_CFIGPAREN);
        }
    }

    if (offset != -1)
        txtfile.eol();

    return;
}
#endif


// Проверяет полное владение указателем и если указатель разделяемый,
// то создает свою копию.
Word_Form& Tree_Node::GetUnique(void)
{
    if (!node.unique())
        node = lem::Ptr<Word_Form>(new Word_Form(*node));

    return *node;
}



void Tree_Node::Add(Tree_Node *to_add)
{
    LEM_CHECKIT_Z(to_add != nullptr);
    child.Add(to_add);
}


void Tree_Node::Add(const Tree_Node& to_add)
{
    child.Add(new Tree_Node(to_add));
}



bool Tree_Node::operator!=(const Tree_Node& tn) const
{
    return !operator==(tn);
}

bool Tree_Node::operator==(const Tree_Node& tn) const
{
    if (child.size() != tn.child.size() ||
        GetNode().GetEntryKey() != tn.GetNode().GetEntryKey() ||
        dims.size() != tn.dims.size()
        )
        return false;

    if (GetNode().CanMatch(tn.GetNode()))
        return false;

    if (ilink != tn.ilink)
        return false;

    for (lem::Container::size_type i = 0; i < child.size(); ++i)
    {
        if (!(child[i] == tn.child[i]))
            return false;
    }

    return true;
}

// *****************************************************************************
// Поиск измерения с указанным именем. Если не найдется, то возвращается nullptr
// *****************************************************************************
TreeDimension* Tree_Node::FindDimension(const UCString &name)
{
    if (name.empty())
        return &child;

    for (lem::Container::size_type i = 0; i < dims.size(); ++i)
        if (dims[i]->GetName().eqi(name))
            return dims[i];

    return nullptr;
}

const TreeDimension* Tree_Node::FindDimension(const UCString &name) const
{
    if (name.empty())
        return &child;

    for (lem::Container::size_type i = 0; i < dims.size(); ++i)
        if (dims[i]->GetName().eqi(name))
            return dims[i];

    return nullptr;
}


TreeMarks& Tree_Node::TouchMarks(const UCString &name)
{
    LEM_CHECKIT_Z(!name.empty());

    for (lem::Container::size_type i = 0; i < marks.size(); ++i)
        if (marks[i]->GetName().eqi(name))
            return *marks[i];

    marks.push_back(new TreeMarks(name));
    return *marks.back();
}


TreeMarks* Tree_Node::FindMarks(const UCString &name)
{
    LEM_CHECKIT_Z(!name.empty());

    for (lem::Container::size_type i = 0; i < marks.size(); ++i)
        if (marks[i]->GetName().eqi(name))
            return marks[i];

    return nullptr;
}

const TreeMarks* Tree_Node::FindMarks(const UCString &name) const
{
    LEM_CHECKIT_Z(!name.empty());

    for (lem::Container::size_type i = 0; i < marks.size(); ++i)
        if (marks[i]->GetName().eqi(name))
            return marks[i];

    return nullptr;
}


void Tree_Node::SetNode(Solarix::Word_Form *new_node)
{
    node = new_node;
    return;
}


Predef_Tree_Node::Predef_Tree_Node(
    int ientry_key,
    SynGram &gram,
    int FakePosition
)
    :Tree_Node()
{
    node = boost::shared_ptr<Word_Form>(new Predef_Word_Form(ientry_key, gram));
#if defined SOL_CAA
    node->SetOriginPos(FakePosition);
#endif
    return;
}

#endif
