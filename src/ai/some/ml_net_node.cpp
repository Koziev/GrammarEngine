// -----------------------------------------------------------------------------
// File ML_NET_NODE.CPP
//
// (c) Koziev Elijah
//
// Content:
// Представление узла Сети Потока Распознавания для Лексического Автомата.
// Используется при начале анализа входной фразы, а именно - при составлении
// предполагаемых мультилексем.
// -----------------------------------------------------------------------------
//
// CD->12.04.1996
// LC->02.04.2018
// --------------

#if defined SOL_CAA

#include <lem/stl.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/tree_node.h>
#include <lem/solarix/ml_projections.h>

using namespace lem;
using namespace Solarix;



MLNetNode::MLNetNode(
    const MLNetNode* prev,
    int ifrom,
    int nword,
    int tot_len,
    const MCollect<MLProjJob*> &proj,
    const MCollect<MLProjList*> &job_list,
    const MCollect<int> &word_job,
    const MCollect<Lexem> &words,
    Dictionary &dict
)
{
    // Наш узел описывает мультилексемы, начнающиеся с позиции ifrom и
    // содержащие nword лексем.
    previous = prev;
    from = ifrom;
    n = nword;

    const int njob = CastSizeToInt(job_list.size());

    // Собираем пробные мультилексемы, начиная с позиции from предложения.
    // Общая длина предложения задана как tot_len, максимальная длина
    // создаваемых мультилексем равна max_ml_len. Информация о пробных
    // мультилексемах будет хранится в подключаемых узлах.
    const int iFrom = ifrom + nword; // Индекс начала следующих мультилексем.

    if (iFrom == tot_len)
        return;

    int IPROJ_found = UNKNOWN;
    bool PROJ_found = false;

    int max_ml_len = dict.GetSynGram().IsMultiLexemBegin(words[iFrom]);
    if (max_ml_len <= 0)
        max_ml_len = 1;

    Lexem ml;

    SynGram &sg = dict.GetSynGram();

    for (int len = 1; len <= max_ml_len && (iFrom + len) <= tot_len; len++)
    {
        if (len == 1)
        {
            PROJ_found = true;

            const int m0 = tot_len - iFrom;
            const int m1 = std::min(m0, max_ml_len);
            if (m1 == 2)
            {
                if (!sg.IsWordForm(words[iFrom]))
                {
                    ml = words[iFrom];
                    ml.Add(words[iFrom + 1]);
                    if (sg.IsMultiLexem(ml))
                        continue;
                }
                else if (!sg.IsWordForm(words[iFrom + 1]))
                {
                    ml = words[iFrom];
                    ml.Add(words[iFrom + 1]);
                    if (sg.IsMultiLexem(ml))
                        continue;
                }
            }
            else if (m1 == 3)
            {
                ml = words[iFrom];
                ml.Add(words[iFrom + 1]);
                ml.Add(words[iFrom + 2]);
                if (sg.IsMultiLexem(ml))
                {
                    ml = words[iFrom + 1];
                    ml.Add(words[iFrom + 2]);
                    if (!sg.IsMultiLexem(ml))
                    {
                        if (!sg.IsWordForm(words[iFrom + 1]) || !sg.IsWordForm(words[iFrom + 2]))
                            continue;
                    }
                }
            }
        }
        else
        {
            PROJ_found = false;
            IPROJ_found = UNKNOWN;

            ml.clear();
            for (int ii = 0; ii < len; ii++)
                ml.Add(words[iFrom + ii]);

            if (dict.GetSynGram().IsMultiLexem(ml))
            {
                // Если в списке job_list заданий на проекцию мультилексем фразоблока
                // удастся найти задание для нашей мультилексемы и эта мультилексема
                // хоть раз спроецирована, то имеет смысл продолжать построение сети
                // далее.
                for (int ijob = 0; ijob < njob; ijob++)
                {
                    if (
                        *(job_list[ijob]->GetContent()) == ml &&
                        job_list[ijob]->IsProjected()
                        )
                    {
                        PROJ_found = true;
                        IPROJ_found = ijob;
                        break;
                    }
                }
            }
        }

        if (!PROJ_found)
            continue;

        MLNetNode *to_add = new MLNetNode(
            this,
            iFrom,
            len,
            tot_len,
            proj,
            job_list,
            word_job,
            words,
            dict
        );

        child.push_back(to_add);

        // Выставим для узла to_add значение достоверности и индекса задания на
        // проекцию.
        if (len == 1)
        {
            const MLProjJob &prj = *proj[word_job[iFrom]];
            to_add->val = prj.GetVal();
            to_add->proj_job_i = prj.GetiJob();

            //mout.printf( "ml=%us val=%f\n",  proj[word_job[iFrom]].GetContent()->string().c_str(), prj.GetVal().GetFloat() );
        }
        else
        {
            Real1 VAL(100);
            to_add->val = VAL;
            to_add->proj_job_i = IPROJ_found;
        }
    }

    return;
}


void MLNetNode::Delete()
{
    ZAP_A(child);
    previous = nullptr;
}


/*****************************************************************************
 Ищем вершины Сети и добавляем их в список finitees. Эта процедура вызываетс
 после построения Сети при подготовке фразоблока к проекции. Нам нужно
 заполнить список finitees - конечные узлы (листья). Стартуя из корня Сети,
 мы продвигаемся по каждой ветке, достигая конца. Внимание: не все найденные
 таким образом листья являются правильными: дело в том, что построение Сети
 для некоторых веток может обрываться алгоритмом, и нужно уметь обнаруживать,
 что лист не заканчивает на самом деле ветку. Это легко сделать, зная общее
 число слов в исходном предложении nword и параметры каждого узла Сети.
******************************************************************************/
void MLNetNode::FindFinitees(
    MCollect<const MLNetNode*> &finitees,
    int nword
) const
{
    // Если данный узел не имеет прикрепленных к нему последующих,
    // то мы нашли один из конечных узлов Сети Потока Распознования.
    const int nchild = GetnChild();
    if (!nchild)
    {
        if (from + n == nword)
            // Истинный лист - ветка доведена до конца предложения.
            finitees.push_back(this);

        return;
    }

    // Рекурсивно перепоручим последующим узлам найти конечные.
    for (int i = 0; i < nchild; i++)
    {
        GetChild(i).FindFinitees(finitees, nword);
    }

    return;
}

#endif // defined SOL_CAA
