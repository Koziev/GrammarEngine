// CD->04.11.2008
// LC->02.04.2018

#ifndef SENTENCE_BROKER__H
#define SENTENCE_BROKER__H
#pragma once

#include <lem/config.h>
#include <lem/smart_pointers.h>
#include <lem/zeroed.h>
#include <lem/stack.h>
#include <lem/ustreams.h>
#include <lem/noncopyable.h>
#include <lem/ptr_container.h>
#include <lem/solarix/prefix_tree.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/LD_Seeker.h>


namespace Solarix
{
    class Dictionary;
    class LA_PreprocessorTrace;

    // **********************************************************************************
    // Модуль токенизации - программируемый делитель предложения на лексемы, учитывающий
    // особенности языка, например - сокращения с точками внутри и т.д.
    // **********************************************************************************
    class SentenceTokenizer : lem::NonCopyable
    {
    protected:
        int ilanguage;

    public:
        SentenceTokenizer(const Solarix::Dictionary &dict, int language);
        virtual ~SentenceTokenizer() {}

        virtual bool IsTokenDelimiter(wchar_t c) const = 0;

        virtual bool IsUnbreakableFront(wchar_t c) const = 0;
        virtual bool IsUnbreakableFront(const lem::UCString &s) const = 0;
        virtual bool IsMatched(const lem::UCString &s) const = 0;

        virtual int MatchLen(const lem::UFString & s, int i0) const = 0;

        virtual bool MatchAllLens(const lem::UFString & s, int i0, lem::MCollect<int> & lens) const;

        virtual void Tokenize(
            const Solarix::Dictionary & dict,
            const lem::UFString & s,
            lem::MCollect<UCString> & words,
            lem::PtrCollect<lem::UFString> & classes,
            std::map< int, lem::UFString > & tokenizer_flags,
            LA_PreprocessorTrace * trace
        ) const;
    };


    class EuroSentenceTokenizer : public SentenceTokenizer
    {
    public:
        class Pattern
        {
        public:
            Pattern() {}
            virtual ~Pattern() {}

            virtual bool MatchBegin(const lem::UCString &s) const = 0;
            virtual bool Match(const lem::UCString &s) const = 0;
            virtual wchar_t GetFrontChar(void) const = 0;
            virtual int Length(void) const = 0;
            virtual int MatchInplace(const lem::UFString & s, int i0) const = 0;

#if LEM_DEBUGGING==1
            virtual lem::UFString GetText(void) const { return L""; }
#endif
        };

    private:
        std::set<wchar_t> unbreakable_front;

        lem::PtrCollect<Pattern> unbreakable; // список особых случаев - лексемы, в состав которых
                                              // входят разделители, например "т.д."

        lem::UFString delimiters;

    public:
        EuroSentenceTokenizer(const Solarix::Dictionary &dict, int language);

        void AddSimplePattern(const lem::UFString &p, const Solarix::Dictionary &dict);
        void AddRxPattern(const lem::UFString &p, const Solarix::Dictionary &dict);

        virtual bool IsTokenDelimiter(wchar_t c) const override;

        void InitSpecialCases();

        virtual bool IsUnbreakableFront(wchar_t c) const override
        {
            return unbreakable_front.empty() || unbreakable_front.find(c) != unbreakable_front.end();
        }

        virtual bool IsUnbreakableFront(const lem::UCString &s) const override;
        virtual bool IsMatched(const lem::UCString &s) const override;

        virtual int MatchLen(const lem::UFString & s, int i0) const override;
    };


#if defined SOL_CAA
    class SegmentingSentenceTokenizer : public SentenceTokenizer
    {
    private:
        lem::Ptr<Solarix::CharNode> lookup;
        lem::Ptr<Solarix::LD_Seeker> seeker;
        lem::UFString delimiters;

    public:
        SegmentingSentenceTokenizer(const Solarix::Dictionary &dict, int language);

        virtual bool IsTokenDelimiter(wchar_t c) const override;
        virtual bool IsUnbreakableFront(wchar_t c) const override;
        virtual bool IsUnbreakableFront(const lem::UCString &s) const override;
        virtual bool IsMatched(const lem::UCString &s) const override;

        virtual int MatchLen(const lem::UFString & s, int i0) const override;
    };
#endif


    class ExternalTokenizer : public SentenceTokenizer
    {
    protected:
        lem::zbool can_define_classes;
        lem::Process::Dll dll;
        void *hSegmenter;

        typedef const wchar_t*(*get_property_func)(void *This, int iProperty, int iSubproperty);
        typedef bool(*set_property_func)(void *This, int iProperty, int iSubproperty, const wchar_t *Value);
        typedef wchar_t*(*segmentation_func)(void *This, const wchar_t *Text, wchar_t Delimiter, int Params);
        typedef wchar_t*(*syntacticanalysis_func)(void *This, const wchar_t *Text, wchar_t Delimiter, int Params);
        typedef void(*extraction_complete_func)(void *This, void *Context);
        typedef void*(*constructor_func)(const wchar_t * DataFolder, const wchar_t * Params);
        typedef void(*destructor_func)(void *This);
        typedef void(*free_func)(void *This, void *Ptr);
        typedef int(*get_error_func)(void *This);
        typedef int(*get_error_text_func)(void *This, wchar_t *Buffer, int BufferLen);

        constructor_func constructor_ptr;
        destructor_func destructor_ptr;

        get_property_func get_property_ptr;
        set_property_func set_property_ptr;

        segmentation_func segmentation_ptr;
        syntacticanalysis_func syntacticanalysis_ptr;
        free_func free_ptr;

        get_error_func get_error_ptr;
        get_error_text_func get_error_text_ptr;

        lem::UFString GetErrorText() const;


    public:
        ExternalTokenizer(
            const lem::Path &dll_path,
            const lem::Path &data_path,
            const lem::UFString &params,
            const Solarix::Dictionary &dict,
            int language
        );

        virtual ~ExternalTokenizer();

        virtual bool IsTokenDelimiter(wchar_t c) const override;

        virtual bool IsUnbreakableFront(wchar_t c) const override;
        virtual bool IsUnbreakableFront(const lem::UCString &s) const override;
        virtual bool IsMatched(const lem::UCString &s) const override;
        virtual int MatchLen(const lem::UFString & s, int i0) const override;

        virtual void Tokenize(
            const Solarix::Dictionary &dict,
            const lem::UFString &s,
            lem::MCollect<UCString> &words,
            lem::PtrCollect<lem::UFString> &classes,
            std::map< int, lem::UFString > & tokenizer_flags,
            LA_PreprocessorTrace *trace
        ) const override;
    };


    class Dictionary;

    // ****************************************
    // Модуль деления текста на предложения.
    // ****************************************
    class SentenceBroker : lem::NonCopyable
    {
    public:
        int max_sentence_length;
        lem::Ptr<SentenceTokenizer> tokenizer;

    protected:
        lem::MCollect<lem::UCString> sent_delims; // символы-разделители предложений
        lem::MCollect<wchar_t> sent_delims1;

        lem::zbool use_lexicon; // использовать поиск слов в лексиконе для определения ситуации
                                // "слово"+".", то есть точка после полной словоформы безусловно
                                // отделяет предложение.
        lem::zint min_wordform_len; // минимальная длина словоформы для того, чтобы следующая после нее
                                    // точка принималась как безусловный делитель предложения.

        lem::MCollect<lem::UCString> casing_sent_delim; // левые части пар токенов, делящих предложение
                                                        // в контексте "и т.д. Новое предложение"

        int CharCasingCoord, LowerCasingState;

        lem::Ptr<Solarix::LD_Seeker> seeker;
        Solarix::LexicalAutomat *la;
        Solarix::SynGram *sg;

        int LanguageID;

        lem::Ptr<lem::Char_Stream::WideStream> stream; // источник символов
        lem::zbool eof;
        lem::zint count; // кол-во извлеченных предложений

        int cur_paragraph_id; // номер абзаца для последнего извлеченного предложения

        lem::UFString last_sentence; // Буфер для последнего извлеченного предложения
        int last_paragraph_id; // номер абзаца для последнего извлеченного предложения

        lem::Stack<wchar_t> chars;
        wchar_t GetChar();
        wchar_t PeekChar();
        void UngetChar(wchar_t);
        bool ReadCharsUntilClosingParen(lem::UFString & line);
        void ReadCharOrUnbreakable(wchar_t first_char, lem::UCString &buffer);

        std::set<wchar_t> upper_chars, lower_chars;
        lem::zbool chars_loaded;
        void LoadUpperAndLowerChars(void);
        bool IsUpperChar(wchar_t c);
        bool IsLowerChar(wchar_t c);

        lem::UCString PickNextToken(void);

        bool IsTokenDelimiter(wchar_t c) const;

        void Prepare(Dictionary * dict, int language);

        static bool IsEndOfSentenceMarker(wchar_t c);
        static bool IsEndOfParagraphMarker(wchar_t c);


    public:
        SentenceBroker();
        SentenceBroker(Solarix::Dictionary &dict, int language);
        SentenceBroker(lem::Char_Stream::WideStream &stream /*non-deleteable*/, Dictionary * dict, int language);
        SentenceBroker(lem::Ptr<lem::Char_Stream::WideStream> stream, Dictionary * dict, int language);
        SentenceBroker(const lem::UFString &text, Dictionary * dict, int language);
        SentenceBroker(const wchar_t *text, Dictionary * dict, int language);

        void Open(lem::Char_Stream::WideStream &stream /*non-deleteable*/);
        void Open(lem::Ptr<lem::Char_Stream::WideStream> stream);

        // Извлекаем очередное предложение в буфер
        virtual bool Fetch(lem::UFString & buffer, int & line_paragraph_id);
        virtual bool Fetch();

        virtual int GetFetchedParagraphID() { return last_paragraph_id; }

        const lem::UFString & GetFetchedSentence() const { return last_sentence; }

        // Достигнут конец потока?
        bool Eof() const;
        int Count() const;
    };

}

#endif
