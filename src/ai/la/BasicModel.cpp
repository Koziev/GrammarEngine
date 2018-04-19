#include <lem/streams.h>
#include <lem/solarix/LexerTextPos.h>
#include <lem/solarix/word_form.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/BasicLexer.h>
#include <lem/solarix/_sg_api.h>
#include <lem/solarix/ElapsedTimeConstraint.h>
#include <lem/solarix/MorphologyModels.h>


using namespace Solarix;


BasicModel::BasicModel() : available(false), codebook(nullptr), loaded(false),
EMIT_FORM_TAGS(false), EMIT_FORMTAGS_FOR_CONTEXT(false), EMIT_POS_TAGS(false), EMIT_SEMANTIC_TAGS(false)
{
}


BasicModel::~BasicModel()
{
    delete codebook;
}

bool BasicModel::IsAvailable()
{
    Load();
    return available;
}



ModelTokenFeatures::ModelTokenFeatures()
{
    suffix_id = UNKNOWN;
    Aa = false;
    IsBegin = IsEnd = false;

    POS_N = "0"; // сущ
    POS_PRN = "0"; // местоим
    POS_PRN2 = "0"; // местоим_сущ
    POS_A = "0"; // прил
    POS_V = "0"; // гл
    POS_I = "0"; // инф
    POS_IMV = "0"; // безл. гл.
    POS_Y = "0"; // нареч
    POS_VY = "0"; // дееприч
    POS_D = "0"; // числительное
    POS_C = "0"; // число
    POS_P = "0"; // предлог
    POS_PX = "0"; // послелог
    POS_PP = "0"; // притяж_частица
    POS_MU = "0"; // единицы измерения
    POS_PCA = "0"; // ПРЕФИКС_СОСТАВ_ПРИЛ
    POS_PCN = "0"; // ПРЕФИКС_СОСТАВ_СУЩ

    POS_PCV = "0"; // ENG_COMPOUND_PREVERB
    POS_PCM = "0"; // ENG_COMPOUND_PREADV
}



ModelTokenFeatures* BasicModel::Get_START_Features() const
{
    ModelTokenFeatures * f = new ModelTokenFeatures();
    f->suffix_id = codebook->GetSTART_suffix();
    f->IsBegin = true;

    if (EMIT_FORM_TAGS)
        f->allform_tags.push_back(codebook->GetSTART_Tag());

    return f;
}

ModelTokenFeatures* BasicModel::Get_END_Features() const
{
    ModelTokenFeatures * f = new ModelTokenFeatures();
    f->suffix_id = codebook->GetEND_suffix();
    f->IsEnd = true;

    if (EMIT_FORM_TAGS)
        f->allform_tags.push_back(codebook->GetEND_Tag());

    return f;
}


namespace {
    static std::string POS_Prob(int n_pos, int n_tot)
    {
        if (n_pos == 0)
            return "0";
        else if (n_pos == n_tot)
            return "2";
        else
            return "1";
    }
}


ModelTokenFeatures* BasicModel::GetFeatures(const LexerTextPos * token, Dictionary & dict) const
{
    ModelTokenFeatures * f = new ModelTokenFeatures();

#if defined SOL_CAA
    f->suffix_id = codebook->GetSuffixId(token);
    f->Aa = codebook->DetectAa(token);

    // Таблица опознания частей речи.
    std::set<int> ekeys;
    std::set<int> ekeys_N;
    std::set<int> ekeys_V;
    std::set<int> ekeys_IMV;
    std::set<int> ekeys_A;
    std::set<int> ekeys_I;
    std::set<int> ekeys_Y;
    std::set<int> ekeys_VY;
    std::set<int> ekeys_D;
    std::set<int> ekeys_C;
    std::set<int> ekeys_P;
    std::set<int> ekeys_PX;
    std::set<int> ekeys_PRN;
    std::set<int> ekeys_PRN2;
    std::set<int> ekeys_PP;
    std::set<int> ekeys_MU;
    std::set<int> ekeys_PCA;
    std::set<int> ekeys_PCN;
    std::set<int> ekeys_PCV;
    std::set<int> ekeys_PCM;


    for (int i = 0; i < token->GetWordform()->VersionCount(); ++i)
    {
        if (EMIT_FORM_TAGS || EMIT_FORMTAGS_FOR_CONTEXT)
        {
            const Solarix::Word_Form * version_form = token->GetWordform()->GetVersion(i);
            const Solarix::ModelTagMatcher * tag_match = codebook->Match(version_form, dict);
            if (tag_match == NULL)
            {
#if LEM_DEBUGGING==1
                //codebook->PrintTags( *lem::mout, dict );
#endif

                lem::MemFormatter mem;
                mem.printf("Can not match tag for wordform: ");
                version_form->Print(mem, &(dict.GetSynGram()), true);
                lem::UFString str_err = mem.string();
                throw E_BaseException(str_err);
            }
            else
            {
                const int form_tag = tag_match->GetId();
                if (f->allform_tags.find(form_tag) == UNKNOWN)
                    f->allform_tags.push_back(form_tag);
            }
        }

        if (EMIT_POS_TAGS)
        {
            int k = token->GetWordform()->GetVersion(i)->GetEntryKey();

            if (ekeys.find(k) == ekeys.end())
            {
                ekeys.insert(k);

                const int id_class1 = dict.GetSynGram().GetEntry(k).GetClass();
                switch (id_class1)
                {
                case NOUN_ru: ekeys_N.insert(k); break;
                case VERB_ru: ekeys_V.insert(k); break;
                case IMPERSONAL_VERB_ru: ekeys_IMV.insert(k); break;
                case ADJ_ru: ekeys_A.insert(k); break;
                case INFINITIVE_ru: ekeys_I.insert(k); break;
                case ADVERB_ru: ekeys_Y.insert(k); break;
                case GERUND_2_ru: ekeys_VY.insert(k); break;
                case NUMBER_CLASS_ru: ekeys_D.insert(k); break;
                case NUM_WORD_CLASS: ekeys_C.insert(k); break;
                case PREPOS_ru: ekeys_P.insert(k); break;
                case POSTPOS_ru: ekeys_PX.insert(k); break;
                case PRONOUN_ru: ekeys_PRN.insert(k); break;
                case PRONOUN2_ru: ekeys_PRN2.insert(k); break;
                case MEASURE_UNIT: ekeys_MU.insert(k); break;
                case COMPOUND_ADJ_PREFIX: ekeys_PCA.insert(k); break;
                case COMPOUND_NOUN_PREFIX: ekeys_PCN.insert(k); break;

                case NOUN_en: ekeys_N.insert(k); break;
                case VERB_en: ekeys_V.insert(k); break;
                case ADJ_en: ekeys_A.insert(k); break;
                case ADV_en: ekeys_Y.insert(k); break;
                case NUMERAL_en: ekeys_D.insert(k); break;
                case PREP_en: ekeys_P.insert(k); break;
                    //case POSTPOS_en: ekeys_PX.insert( k ); break;
                case PRONOUN_en: ekeys_PRN.insert(k); break;
                case POSESS_PARTICLE: ekeys_PP.insert(k); break;
                case COMPOUND_PRENOUN_en: ekeys_PCA.insert(k); break;
                case COMPOUND_PREADJ_en: ekeys_PCN.insert(k); break;
                case COMPOUND_PREVERB_en: ekeys_PCV.insert(k); break;
                case COMPOUND_PREADV_en: ekeys_PCM.insert(k); break;
                }
            }
        }
    }


    const int n_tot = ekeys.size();

    if (EMIT_POS_TAGS)
    {
        f->POS_N = POS_Prob(ekeys_N.size(), n_tot);
        f->POS_V = POS_Prob(ekeys_V.size(), n_tot);
        f->POS_IMV = POS_Prob(ekeys_IMV.size(), n_tot);
        f->POS_A = POS_Prob(ekeys_A.size(), n_tot);
        f->POS_PRN = POS_Prob(ekeys_PRN.size(), n_tot);
        f->POS_PRN2 = POS_Prob(ekeys_PRN2.size(), n_tot);
        f->POS_I = POS_Prob(ekeys_I.size(), n_tot);
        f->POS_Y = POS_Prob(ekeys_Y.size(), n_tot);
        f->POS_VY = POS_Prob(ekeys_VY.size(), n_tot);
        f->POS_C = POS_Prob(ekeys_C.size(), n_tot);
        f->POS_D = POS_Prob(ekeys_D.size(), n_tot);
        f->POS_P = POS_Prob(ekeys_P.size(), n_tot);
        f->POS_PX = POS_Prob(ekeys_PX.size(), n_tot);
        f->POS_PP = POS_Prob(ekeys_PP.size(), n_tot);
        f->POS_MU = POS_Prob(ekeys_MU.size(), n_tot);
        f->POS_PCA = POS_Prob(ekeys_PCA.size(), n_tot);
        f->POS_PCN = POS_Prob(ekeys_PCN.size(), n_tot);

        f->POS_PCV = POS_Prob(ekeys_PCV.size(), n_tot);
        f->POS_PCM = POS_Prob(ekeys_PCM.size(), n_tot);
    }

    if (EMIT_SEMANTIC_TAGS)
    {
        codebook->GetSemanticTags(dict, token, f->semantic_tags);
    }

#endif

    return f;
}





void BasicModel::PullFeatures1(
    lem::MCollect<lem::CString> & b,
    const lem::PtrCollect<ModelTokenFeatures> & token_features,
    int ifocus,
    int offset,
    bool rich_set,
    bool emit_Aa_feature
) const
{
    int iword = ifocus + offset;

    if (iword >= 0 && iword < token_features.size())
    {
        const ModelTokenFeatures & f = *token_features[iword];

        if (codebook->GetMaxSuffixLen() > 0)
            b.push_back(lem::format_str("sfx[%d]=%d", offset, f.suffix_id).c_str());

        if (emit_Aa_feature && f.Aa == true && !f.IsBegin && !f.IsEnd)
            b.push_back(lem::format_str("Aa[%d]=True", offset).c_str());

        // здесь можно вывести и другие свойства слова.
        if (rich_set && EMIT_POS_TAGS)
        {
            if (language_id == RUSSIAN_LANGUAGE)
            {
                b.push_back(lem::format_str("pos[%d,N]=%s", offset, f.POS_N.c_str()).c_str());
                b.push_back(lem::format_str("pos[%d,A]=%s", offset, f.POS_A.c_str()).c_str());
                b.push_back(lem::format_str("pos[%d,V]=%s", offset, f.POS_V.c_str()).c_str());
                b.push_back(lem::format_str("pos[%d,IMV]=%s", offset, f.POS_IMV.c_str()).c_str());
                b.push_back(lem::format_str("pos[%d,I]=%s", offset, f.POS_I.c_str()).c_str());
                b.push_back(lem::format_str("pos[%d,Y]=%s", offset, f.POS_Y.c_str()).c_str());
                b.push_back(lem::format_str("pos[%d,VY]=%s", offset, f.POS_VY.c_str()).c_str());
                b.push_back(lem::format_str("pos[%d,PRN]=%s", offset, f.POS_PRN.c_str()).c_str());
                b.push_back(lem::format_str("pos[%d,PRN2]=%s", offset, f.POS_PRN2.c_str()).c_str());
                b.push_back(lem::format_str("pos[%d,C]=%s", offset, f.POS_C.c_str()).c_str());
                b.push_back(lem::format_str("pos[%d,D]=%s", offset, f.POS_D.c_str()).c_str());
                b.push_back(lem::format_str("pos[%d,P]=%s", offset, f.POS_P.c_str()).c_str());
                b.push_back(lem::format_str("pos[%d,PX]=%s", offset, f.POS_PX.c_str()).c_str());
                b.push_back(lem::format_str("pos[%d,PP]=%s", offset, f.POS_PP.c_str()).c_str());
                b.push_back(lem::format_str("pos[%d,MU]=%s", offset, f.POS_MU.c_str()).c_str());
                b.push_back(lem::format_str("pos[%d,PCA]=%s", offset, f.POS_PCA.c_str()).c_str());
                b.push_back(lem::format_str("pos[%d,PCN]=%s", offset, f.POS_PCN.c_str()).c_str());
            }
            else if (language_id == ENGLISH_LANGUAGE)
            {
                b.push_back(lem::format_str("pos[%d,N]=%s", offset, f.POS_N.c_str()).c_str());
                b.push_back(lem::format_str("pos[%d,A]=%s", offset, f.POS_A.c_str()).c_str());
                b.push_back(lem::format_str("pos[%d,V]=%s", offset, f.POS_V.c_str()).c_str());
                b.push_back(lem::format_str("pos[%d,Y]=%s", offset, f.POS_Y.c_str()).c_str());
                b.push_back(lem::format_str("pos[%d,PRN]=%s", offset, f.POS_PRN.c_str()).c_str());
                b.push_back(lem::format_str("pos[%d,C]=%s", offset, f.POS_C.c_str()).c_str());
                b.push_back(lem::format_str("pos[%d,D]=%s", offset, f.POS_D.c_str()).c_str());
                b.push_back(lem::format_str("pos[%d,P]=%s", offset, f.POS_P.c_str()).c_str());
                b.push_back(lem::format_str("pos[%d,PX]=%s", offset, f.POS_PX.c_str()).c_str());
                b.push_back(lem::format_str("pos[%d,PP]=%s", offset, f.POS_PP.c_str()).c_str());
                b.push_back(lem::format_str("pos[%d,PCA]=%s", offset, f.POS_PCA.c_str()).c_str());
                b.push_back(lem::format_str("pos[%d,PCN]=%s", offset, f.POS_PCN.c_str()).c_str());
                b.push_back(lem::format_str("pos[%d,PCV]=%s", offset, f.POS_PCV.c_str()).c_str());
                b.push_back(lem::format_str("pos[%d,PCM]=%s", offset, f.POS_PCM.c_str()).c_str());
            }
            else
            {
                LEM_STOPIT;
            }
        }

        if (EMIT_FORMTAGS_FOR_CONTEXT && offset != 0)
        {
            for (int k = 0; k < f.allform_tags.size(); ++k)
            {
                b.push_back(lem::format_str("formtag[%d]=%d", offset, f.allform_tags[k]).c_str());
            }
        }

        if (EMIT_SEMANTIC_TAGS)
        {
            for (int k = 0; k < f.semantic_tags.size(); ++k)
            {
                b.push_back(lem::format_str("sem[%d]=%s", offset, lem::to_utf8(f.semantic_tags[k]).c_str()).c_str());
            }
        }
    }

    return;
}


void BasicModel::PullFeatures2(lem::MCollect<lem::CString> & b, const lem::PtrCollect<ModelTokenFeatures> & token_features, int ifocus, int offset1, int offset2) const
{
    int iword1 = ifocus + offset1;
    int iword2 = ifocus + offset2;

    if (iword1 >= 0 && iword1 < token_features.size() && iword2 >= 0 && iword2 < token_features.size())
    {
        b.push_back(lem::format_str("sfx[%d,%d]=%d,%d", offset1, offset2, token_features[iword1]->suffix_id, token_features[iword2]->suffix_id).c_str());

        // здесь можно вывести и другие свойства слов.
        // ... TODO
    }

    return;
}



void BasicModel::PullFeatures3(lem::MCollect<lem::CString> & b, const lem::PtrCollect<ModelTokenFeatures> & token_features, int ifocus, int offset1, int offset2, int offset3) const
{
    int iword1 = ifocus + offset1;
    int iword2 = ifocus + offset2;
    int iword3 = ifocus + offset3;

    if (iword1 >= 0 && iword1 < token_features.size() && iword2 >= 0 && iword2 < token_features.size() && iword3 >= 0 && iword3 < token_features.size())
    {
        b.push_back(lem::format_str("sfx[%d,%d,%d]=%d,%d,%d", offset1, offset2, offset3, token_features[iword1]->suffix_id, token_features[iword2]->suffix_id, token_features[iword3]->suffix_id).c_str());

        // здесь можно вывести и другие свойства слов.
        // ... TODO
    }

    return;
}


void BasicModel::SetParamsAfterLoad()
{
    EMIT_POS_TAGS = codebook->FindModelParam(L"EMIT_POS_TAGS", L"false").eqi(L"true");
    EMIT_FORM_TAGS = codebook->FindModelParam(L"EMIT_FORM_TAGS", L"false").eqi(L"true");
    EMIT_FORMTAGS_FOR_CONTEXT = codebook->FindModelParam(L"EMIT_FORMTAGS_FOR_CONTEXT", L"false").eqi(L"true");
    EMIT_SEMANTIC_TAGS = codebook->FindModelParam(L"EMIT_SEMANTIC_TAGS", L"false").eqi(L"true");

    lem::UCString lang = codebook->FindModelParam(L"LANGUAGE", L"");
    if (lang.eqi(L"en"))
        language_id = ENGLISH_LANGUAGE;
    else
        language_id = RUSSIAN_LANGUAGE;

    return;
}

