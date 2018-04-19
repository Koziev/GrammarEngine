#if !defined LexerTextPos__H
#define LexerTextPos__H

#include <lem/containers.h>

namespace Solarix {

    class Word_Form;

    // ����������� �� ������ �����.
    class LexerTextPos
    {
    private:
        int start_position; // ������ ������� �������.
        int token_length; // ����� ������ � ������� ��������. ��-�� �������� ������������� ����� ���������� �� ����� ����� � wordform.

        const Word_Form * wordform;

        int score; // ����������� ������ (-) ��� ��������� (+) �� ������ �����������.
        const LexerTextPos * previous;
        int WordIndex; // �������� ���������� ������ ����� - ���������� ��� ������� � �����. ���������� � 0.

        const LexerTextPos * next_chained; // ���� �� ���� ������� �� 1 �����, � ����� �������
                                           // ����������������, �� ��� ������� �������� ����� ����
                                           // next_chained.

    protected:
        lem::int16_t token_flags; // 0=������� �����
                         // 1=��������� ����� - ������ ������� �����������.
                         // 2=��������� ���������� ����������� ��-�� ������������� �������� ��������� �����
                         // 3=����� �� ������ ��������
                         // 4=��������� ����� - ����� �������
                         // 5=��������� ����� ����������

        lem::int16_t creat_flags; // ���. ����� ��� ������� - ������� �������� ������

    public:
        LexerTextPos(
            const LexerTextPos * _previous,
            const Word_Form * _wordform,
            int _score,
            int _start,
            int _length,
            int _wordindex
        );

        void SetNextChained(const LexerTextPos * next) { next_chained = next; }

        int GetWordIndex() const { return WordIndex; }

        const LexerTextPos * GetNextChained() const { return next_chained; }

        int GetNextCharPos() const
        {
            if (next_chained != nullptr)
                return next_chained->start_position;
            else
                return start_position + token_length;
        }

        const LexerTextPos* GetPrev() const { return previous; }

        int GetWordLength() const;

        const Word_Form * GetWordform() const { return wordform; }
        void ReplaceWordform(const Word_Form * new_wordform);

        void CollectPathToLeft(int count, lem::MCollect<const Word_Form*> & org) const;

        // ����� - ������� �����.
        bool IsRealWord() const { return token_flags == 0; }

        // ����� - ������ �������
        bool IsEnd() const { return token_flags == 1; }

        // ����� - ����� �������
        bool IsBegin() const { return token_flags == 4; }

        // ����� ��� �������� ���������� ����������� ���������� ����������� ��� ������������� ������
        bool IsTerminator() const { return token_flags == 2; }

        // ����� ��� ����������� ��������� �� ������ �������.
        bool IsBeyondRight() const { return token_flags == 3; }

        void Reconstructed() { creat_flags |= 0x0001; }
        bool IsReconstructed() const { return (creat_flags & 1) == 1; }

        // �� �������� ������ ��������� ����� ������ �� ������ left_boundary � �������� ���������� ������, ������� ������� � inverted_path.
        void Collect_Right2Left(const LexerTextPos *left_boundary, lem::MCollect<const LexerTextPos*> & inverted_path) const;

        // �� �������� ������ ���������� ����� �������� �� count ������� � �������� ������, ������������� �� ���� ����, � inverted_path.
        void Collect_Right2Left(int count, lem::MCollect<const LexerTextPos*> & inverted_path) const;

        int GetStartPosition() const { return start_position; }

        int GetScore() const { return score; }
    };


    class LexerTextPos_BeyondLeft : public LexerTextPos
    {
    public:
        LexerTextPos_BeyondLeft(const Word_Form * wf);
    };


    class LexerTextPos_Begin : public LexerTextPos
    {
    public:
        LexerTextPos_Begin(const LexerTextPos_BeyondLeft * left_margin, const Word_Form * wf);
    };


    class LexerTextPos_End : public LexerTextPos
    {
    public:
        LexerTextPos_End(const LexerTextPos * previous, const Word_Form * wf);
    };


    class LexerTextPos_Terminator : public LexerTextPos
    {
    public:
        LexerTextPos_Terminator();
    };


    class LexerTextPos_BeyondRight : public LexerTextPos
    {
    public:
        LexerTextPos_BeyondRight(const LexerTextPos * previous, const Word_Form * wf);
    };


}
#endif
