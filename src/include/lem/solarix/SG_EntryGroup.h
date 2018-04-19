#if !defined SG_EntryGroup__H
#define SG_EntryGroup__H

#include <lem/containers.h>
#include <tuple>

namespace lem
{
    class OFormatter;
}

namespace Solarix
{
    // *********************************************************************
    // *       Детальки для алгоритма быстрого поиска словоформы           *
    // * Структура хранит информацию о тех статьях, у которых словоформы   *
    // * или имена (ежели словоформ нету) начинаются с определенной буквы. *
    // *********************************************************************

    struct SG_Interval
    {
        int from, n;

        SG_Interval() { from = UNKNOWN; n = 0; }

        inline void clear() { from = UNKNOWN; n = 0; }

        inline lem::Container::size_type size() const { return n; }

        inline bool empty() const { return !n; }

        inline int operator[](lem::Container::size_type i) const
        {
            LEM_CHECKIT_Z(from != UNKNOWN && i < static_cast<lem::Container::size_type>(n)); return CastSizeToInt(from + i);
        }
    };

    class SG_EntryGroup
    {
    public:
        //typedef lem::triple<wchar_t, wchar_t, wchar_t> KEY;
        using KEY = std::tuple<wchar_t, wchar_t, wchar_t>;

    private:
        KEY key;

        lem::IntCollect ientry; // Индексы словоформ, которые идут настолько вразброс,
                                // что не могут быть представлены как диапазон ОТ-ДО.

#if defined SOL_COMPILER
        void Compress(const lem::IntCollect& indeces);

        void Compress_Interval_1(lem::IntCollect& indeces);
        void Compress_Interval_2(lem::IntCollect& indeces);
        void Compress_Interval(lem::IntCollect& indeces, SG_Interval &range);
#endif

    protected:
        SG_Interval int1, int2;

    public:
        SG_EntryGroup();
        SG_EntryGroup(const KEY & k);
        SG_EntryGroup(const KEY & k, int from, int n);

#if defined SOL_COMPILER
        SG_EntryGroup(const KEY & k, const lem::IntCollect& indeces);
#endif

        SG_EntryGroup(const SG_EntryGroup& eg);

#if defined SOL_LOADBIN 
        SG_EntryGroup(lem::Stream& bin);
#endif

        void operator=(const SG_EntryGroup& eg);

        void clear();

#if defined SOL_SAVEBIN
        void SaveBin(lem::Stream& bin) const;
#endif

#if defined SOL_LOADBIN 
        void LoadBin(lem::Stream& bin);
#endif

        inline const KEY& GetKey() const { return key; }
        static KEY BuildKey(const lem::UCString &str);

        /***********************************************************************
         Возвращаем общее число хранимых индексов, с учетом возможного сжатого
         формата хранения.
        ************************************************************************/
        inline lem::IntCollect::size_type size() const
        {
            return ientry.size() + int1.size() + int2.size();
        }

        /**************************************************************************
         Так как хранящаяся информация может быть представлена и диапазоном,
         и вектором одновременно, то поступаем так: сначала извлекаются элементы
         вектора ientry, а потом возвращаются числа из хранящегося диапазона.
        ***************************************************************************/
        inline int operator[](lem::IntCollect::size_type i) const
        {
            return i >= ientry.size() ?
                (
                (i - ientry.size()) >= int1.size() ?
                    int2[i - int1.size() - ientry.size()]
                    :
                    int1[i - ientry.size()]
                    )
                :
                (int)ientry[i];
        }

        void Print(lem::OFormatter &txtfile) const;

#if defined SOL_LOADTXT
        void AddEntry(int ie) { ientry.push_back(ie); }
#endif

        int GetUnpackedListLength() const { return CastSizeToInt(ientry.size()); }
        int GetPackedListLength() const { return CastSizeToInt(int1.size() + int2.size()); }
    };

    class SG_DummyEntryGroup : public SG_EntryGroup
    {
    public:
        SG_DummyEntryGroup() :SG_EntryGroup(KEY(0, 0, 0), 0, 0) {}

        inline void Build(int nEntry) { int1.from = 0; int1.n = nEntry; }
    };

}

#endif
