// -----------------------------------------------------------------------------
// File GrammarEngineHolder.h
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// 09.10.2006 - рефакторинг, в именах процедур API убраны подчеркивани€ кроме
//              префикса "sol_"
//
// 09.10.2006 - начало интеграции расширенных регул€рных выражений (RegexEx)
//
// 12.10.2006 - введена процедура sol_TranslateToBase - слово преобразует к
//              базовой форме. 
//
// 15.10.2006 - компоненты грамматического и поискового движка объединены.
//
// 21.11.2006 - в процедуру sol_TranslateToBase добавлен вызов стеммера.
//
// 30.09.2007 - в API добавл€ютс€ процедуры дл€ параметризации запросов
//
// 13.09.2017 - рефакторинг: избавл€емс€ от следов поискового движка
// -----------------------------------------------------------------------------
//
// CD->20.06.2005
// LC->13.09.2017
// --------------

#ifndef GrammarEngineHolder__H
#define GrammarEngineHolder__H
#pragma once

#if defined DLL_EXPORTS || defined FAIND_IENGINES
#define GREN_EXPORTS
#else
#define GREN_IMPORTS
#endif

#include <lem/oformatter.h>
#include <lem/solarix/se_fuzzy_comparator.h>
#include <lem/solarix/form_table.h>
#include <lem/solarix/_sg_api.h>

namespace Solarix
{
    class Tree_Node;
    class SentenceBroker;
    class PhrasoBlock;
}

#define SOL_CREATE_GREN_DONT_INIT_SQLITE 0x00010000
#define SOL_CREATE_GREN_LAZY_LEXICON 0x00000001


namespace Solarix
{
    class Dictionary;
    class LD_Seeker;
    class SentenceBroker;

    class SynGram;

    // This class is highest-level wrapper for text search engine.
    class GrammarEngineHolder
    {
    public:
#if defined LEM_THREADS
        lem::Process::CriticalSection cs;
#endif
        lem::Ptr<Solarix::Dictionary> dict; // указатель на загруженный словарь
        lem::Ptr<Solarix::LD_Seeker> seeker; // быстрый поиск слов

#if defined SOLARIX_PRO
        lem::Ptr<Solarix::Search_Engine::Fuzzy_Comparator> fuzzy; // дл€ нечеткого поиска
#endif

        Solarix::SynGram *sg; // дл€ ускорени€ доступа к лексикону

        int n_lexicon_reserve;

        int DefaultLanguage; // Default language index

#if defined LEM_THREADS
        lem::Process::CriticalSection cs_error;
#endif
        lem::UFString error; // Error message if was any (non thread-safe!!!)
        void SetError(const lem::UFString & error_text);

        lem::OFormatter *nul_tty;
        lem::zbool ok;

    public:
        GrammarEngineHolder(void);

        virtual ~GrammarEngineHolder(void);

        void PostINI(void);

        bool Load(const wchar_t *DictionaryXml, bool LazyLexicon);
    };


    struct GREN_Strings
    {
        lem::MCollect<lem::UCString> list;
    };

    struct GREN_WordCoords
    {
        lem::MCollect<Solarix::Word_Coord> list;
        lem::Collect<Solarix::CP_Array> tags;
    };
}

#if !defined DLL_EXPORTS
#define GREN_INTERNAL_TYPES
#endif

#if defined GREN_INTERNAL_TYPES 
typedef Solarix::SentenceBroker* HGREN_SBROKER;
typedef Solarix::GrammarEngineHolder* HGREN;
typedef Solarix::GREN_Strings* HGREN_STR;
typedef lem::MCollect<int> *HGREN_INTARRAY;
typedef Solarix::GREN_WordCoords* HGREN_WCOORD;
typedef lem::UFString * HGREN_LONGSTRING;
typedef Solarix::Res_Pack* HGREN_RESPACK;
typedef const Solarix::Tree_Node* HGREN_TREENODE;
typedef Solarix::Variator* HGREN_LINKAGE;
#else
typedef void* HGREN;
typedef void* HGREN_STR;
typedef void* HGREN_RESPACK;
typedef const void* HGREN_TREENODE;
typedef void* HGREN_LINKAGE;
typedef void* HGREN_SBROKER;
#endif

inline Solarix::GREN_Strings* HandleStrList(HGREN_STR hStr)
{
    return (Solarix::GREN_Strings*)hStr;
}

inline Solarix::PhrasoBlock* HandlePack(HGREN_RESPACK hPack)
{
    return (Solarix::PhrasoBlock*)hPack;
}

inline const Solarix::Tree_Node* HandleNode(HGREN_TREENODE hNode)
{
    return (const Solarix::Tree_Node*)hNode;
}

inline Solarix::SentenceBroker* HandleBroker(HGREN_SBROKER hBroker)
{
    return (Solarix::SentenceBroker*)hBroker;
}

inline Solarix::GrammarEngineHolder* HandleEngine(HGREN hEngine)
{
    return (Solarix::GrammarEngineHolder*)hEngine;
}

#endif
