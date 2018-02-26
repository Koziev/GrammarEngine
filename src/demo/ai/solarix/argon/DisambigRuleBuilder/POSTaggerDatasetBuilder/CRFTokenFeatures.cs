using System.Collections.Generic;
using System;


class CRFTokenFeatures
{
    public string org_word; // в оригинальном виде
    public string word; // в нижнем регистре
    public string crf_word; // с заменой пробелов на _
    public string suffix;
    public string crf_normal_form; // инфинитив для глаголов, с заменой пробелов на _
    public int suffix_id = -1;
    public bool Aa;
    public int output_tag = -1; // такой тэг должен выбрать обученный POS Tagger
    public List<int> allform_tags = new List<int>(); // это список тегов для всех вариантов проекции слова

    public List<string> morph_tags;

    public string POS_N = "0"; // сущ
    public string POS_PRN = "0"; // местоим
    public string POS_PRN2 = "0"; // местоим_сущ
    public string POS_A = "0"; // прил
    public string POS_V = "0"; // гл
    public string POS_IMV = "0"; // безл. гл.
    public string POS_I = "0"; // инф
    public string POS_Y = "0"; // нареч
    public string POS_VY = "0"; // дееприч
    public string POS_D = "0"; // числительное
    public string POS_C = "0"; // число
    public string POS_P = "0"; // предлог
    public string POS_PX = "0"; // послелог
    public string POS_PP = "0"; // притяж_частица
    public string POS_MU = "0"; // единица_измерения
    public string POS_PCA = "0"; // ПРЕФИКС_СОСТАВ_ПРИЛ
    public string POS_PCN = "0"; // ПРЕФИКС_СОСТАВ_СУЩ

    public string POS_PCV = "0"; // ENG_COMPOUND_PREVERB
    public string POS_PCM = "0"; // ENG_COMPOUND_PREADV

    public List<string> semantic_tags; // семантические признаки

    public List<string> charshingles = new List<string>(); // символьные шинглы

    public bool IsBegin, IsEnd; // флажки для граничных токенов
}

