#ifndef LEM_CARRAY__H
#define LEM_CARRAY__H
#pragma once

// -----------------------------------------------------------------------------
// File CONTAINERS.H
//
// (c) Koziev Elijah
//
// Content:
// Класс BaseCollect - универсальный шаблон-контейнер для однотипных элементов.
// Имеет для гибкости policy classes для шаблона, который определяет способы
// манипулирования векторами элементов - через побитовые операции (типа memcpy)
// или операторы копирования и т.д. ( operator=(...)).
//
// Это один из базовых контейнерных классов, многие (не все) другие контейнеры
// строятся как его наследники. Его главная задача - уметь динамически управлять
// числом хранимых элементов.
//
// Здесь же определяются несколько других контейнерных классов - Collect для
// хранения элементов с нетривиальными конструкторами копирования, MCollect
// для POD'ов.
//
// 09.10.2005 - container are based on std::vector for better conformance
//              with STL
//
// 25.04.2007 - bug fix: an iterator of empty std::vector<T> can not be
//              dereferenced (MSVC 2005 only).
//
// 24.03.2008 - fill( T t ) method added
// 03.04.2018 - code refactoring using C++11 features
// -----------------------------------------------------------------------------
//
// CD->01.07.1995
// LC->03.04.2018
// --------------

#include <lem/base_container.h>
#include <lem/streams.h>

// Чтобы макросы не мешали определять умные функции для контейнеров.
#undef max
#undef min

namespace lem
{
    // ****************************************
    // Forward declaration.
    // ****************************************

    // Just to simplify the syntax of code in THIS file. The macro should be
    // undef'ed in the end of file.
#undef BC
#define BC   BaseCollect<T>

#if defined LEM_GNUC
#define SZT typename BC::size_type
#else
#define SZT BC::size_type
#endif

// ***************************************************************************
// Класс Collect - универсальный шаблон-контейнер для однотипных элементов.
// Написан в предположении, что хранимые элементы имеют нетривиальные
// конструкторы копирования. Если для копирования элементов достаточно
// использовать memcpy, то разумнее применить версию этого контейнера с именем
// LemMCollect, располагающуюся в файле [LEM_MARR.H].
// ***************************************************************************
    template < class T >
    class Collect : public BaseCollect< T >
    {
    public:
#if defined LEM_GNUC
        typedef typename BaseCollect<T>::size_type size_type;
        typedef typename BaseCollect<T>::iterator iterator;
        typedef typename BaseCollect<T>::const_iterator const_iterator;
#else
        typedef BaseCollect<T>::size_type size_type;
#endif

#if defined LEM_GNUC
        inline typename lem::BaseCollect<T>::size_type size(void) const { return lem::BaseCollect<T>::size(); }
        inline bool empty(void) const { return lem::BaseCollect<T>::empty(); }
        inline void resize(typename BaseCollect<T>::size_type n) { lem::BaseCollect<T>::resize(n); }
        inline void clear(void) { lem::BaseCollect<T>::clear(); }

        inline typename lem::BaseCollect<T>::const_iterator begin(void) const { return lem::BaseCollect<T>::begin(); }
        inline typename lem::BaseCollect<T>::const_iterator end(void) const { return lem::BaseCollect<T>::end(); }
        inline typename lem::BaseCollect<T>::iterator begin(void) { return lem::BaseCollect<T>::begin(); }
        inline typename lem::BaseCollect<T>::iterator end(void) { return lem::BaseCollect<T>::end(); }

        inline const T& operator[](typename lem::BaseCollect<T>::size_type i) const { return BaseCollect<T>::operator[](i); }
        inline       T& operator[](typename lem::BaseCollect<T>::size_type i) { return BaseCollect<T>::operator[](i); }
#endif    

    public:
        Collect(size_type n0 = 0)
            : BaseCollect< T >(n0) {}

        Collect(const Collect<T> &x)
            : BaseCollect< T >(x) {}

        Collect(const T *Begin, const T *End)
            : BaseCollect< T >(Begin, End) {}

        Collect(Collect<T> && src) : BaseCollect<T>(src) {}

        const Collect<T> operator=(Collect<T> && src)
        {
            Collect<T>::operator=(std::move(src));
        }

        inline const Collect<T>& operator=(const Collect<T> &x)
        {
            return (const Collect<T>&)BaseCollect< T >
                :: operator=(x);
        }


        inline void SaveBin(lem::Stream &stream) const
        {
            stream.write_int(CastSizeToInt(size()));

            for (auto& item : *this)
                item.SaveBin(stream);

            return;
        }


        inline void LoadBin(lem::Stream &stream)
        {
            size_type ni = stream.read_int();
            resize(ni);
            if (ni)
            {
                for (auto& item : *this)
                    item.LoadBin(stream);
            }

            return;
        }

        void fill(T t) { std::fill(begin(), end(), t); }

        int find(const T & t) const
        {
            for (lem::Container::size_type i = 0; i < size(); ++i)
            {
                if (operator[](i) == t)
                    return CastSizeToInt(i);
            }

            return UNKNOWN;
        }
    };



    // ***********************************************************************
    // Basic container for POD-structs.
    // Класс MCollect - универсальный шаблон-контейнер для элементов, которые
    // могут копироваться без использования конструктора, с помощью memcpy.
    // ***********************************************************************
    template < class T >
    class MCollect : public BaseCollect< T >
    {
    protected:
#if defined __MINGW32__ || defined LEM_GNUC
        inline       T* get_Container(void) { return (T*)&*begin(); }
        inline const T* get_Container(void) const { return (T*)&*begin(); }
#endif

    public:
#if defined LEM_GNUC      
        typedef typename BaseCollect< T >::size_type size_type;
#else     
        typedef BaseCollect< T >::size_type size_type;
#endif      

#if defined LEM_GNUC
        inline size_type size() const { return lem::BaseCollect<T>::size(); }
        inline bool empty() const { return lem::BaseCollect<T>::empty(); }
        inline void resize(size_type n) { lem::BaseCollect<T>::resize(n); }
        inline void clear() { lem::BaseCollect<T>::clear(); }

        inline typename lem::BaseCollect<T>::const_iterator begin(void) const { return lem::BaseCollect<T>::begin(); }
        inline typename lem::BaseCollect<T>::const_iterator end(void) const { return lem::BaseCollect<T>::end(); }
        inline typename lem::BaseCollect<T>::iterator begin(void) { return lem::BaseCollect<T>::begin(); }
        inline typename lem::BaseCollect<T>::iterator end(void) { return lem::BaseCollect<T>::end(); }

        inline const T& operator[](size_type i) const { return BaseCollect<T>::operator[](i); }
        inline       T& operator[](size_type i) { return BaseCollect<T>::operator[](i); }
#endif    
    public:
        MCollect(size_type n0 = 0)
            : BaseCollect< T >(n0) {}

        MCollect(const MCollect<T> &x)
            : BaseCollect< T >(x) {}

        MCollect(const T *Begin, const T *End)
            : BaseCollect< T >(Begin, End) {}

        MCollect(MCollect<T> && src) : BaseCollect<T>(src) {}

        const MCollect<T>& operator=(MCollect<T> &&src)
        {
            BaseCollect<T>::operator=(std::move(src));
            return *this;
        }

        inline const MCollect<T>& operator=(const MCollect<T> &x)
        {
            return (const MCollect<T>&)BaseCollect< T >
                :: operator=(x);
        }


        inline void SaveBin(lem::Stream &stream) const
        {
            size_type ni = size();
            stream.write(&ni, sizeof(ni));
            if (!empty())
                stream.write(get_Container(), size() * sizeof(T));
            return;
        }


        inline void LoadBin(lem::Stream &stream)
        {
            size_type ni;
            stream.read(&ni, sizeof(ni));

#if !defined LEM_BORLAND && !defined LEM_GNUC
            LEM_CHECKIT_Z(ni >= 0);
#endif

            resize(ni);
            if (ni)
                stream.read(get_Container(), size() * sizeof(T));

            return;
        }

        // *******************************************************************
        // Быстро обнуляет содержимое вектора. Этот метод хорошо использовать
        // вместо поэлементного обнуления вектора.
        // *******************************************************************
        inline void Nullify(void) { std::fill(begin(), end(), static_cast<T>(0)); }
        void fill(T t) { std::fill(begin(), end(), t); }

        // **********************************************************************
        // Применим только для векторов базовых типов - установка битов во всех
        // байтах.
        // **********************************************************************
        //inline void SetBits(lem::uint8_t Bits)
        //{
        //    ::memset(get_Container(), (int)Bits, (size_t)size());
        //}
    };


    // ************************************************************
    // ************************************************************
    template < class T >
    inline lem::Stream& operator << (lem::Stream &stream, const BC &a)
    {
        a.SaveBin(stream);
        return stream;
    }


    // ************************************************************
    // ************************************************************
    template < class T >
    inline lem::Stream& operator >> (lem::Stream &stream, const BC &a)
    {
        a.LoadBin(stream);
        return stream;
    }


    // ****************************************************
    // Returns 'true' if any item of 'to_find' is in 'arr'
    // ****************************************************
    template <class T >
    inline bool find_any(const BC& arr, const BC& to_find)
    {
        for (auto& item1 : to_find)
        {
            for (auto& item2 : arr)
            {
                if (item2 == item1)
                    return true;
            }
        }

        return false;
    }



    // ************************************************************
    // ************************************************************
    template < class T >
    inline void minmax(const BC& a, T& amin, T &amax)
    {
        if (a.empty())
            return;

        amax = a.front(), amin = a.front();

        for (SZT i = 1; i < a.size(); i++)
        {
            amax = std::max(amax, a[i]);
            amin = std::min(amin, a[i]);
        }
    }



    // ************************************************************
    // ************************************************************
    template < class T >
    inline const T max(const BC& a)
    {
        T a_max = a.front();

        for (SZT i = 1; i < a.size(); i++)
            a_max < a[i] ? a_max = a[i] : a[i];

        return a_max;
    }



    // ************************************************************
    // ************************************************************
    template < class T >
    inline const T min(const BC& a)
    {
        T amin = a.front();

        for (SZT i = 1; i < a.size(); i++)
            amin > a[i] ? amin = a[i] : a[i];

        return amin;
    }



    // ************************************************************
    // ************************************************************
    template < class T >
    inline const T sum_up(const BC& a)
    {
        if (a.empty())
            return T(0); // null value returned.

        T s = a.front();

        for (SZT i = 1; i < a.size(); i++)
            s += a[i];

        return s;
    }

    template < class T >
    inline bool operator==(const BC &a, const BC &b)
    {
        if (a.size() != b.size())
            return false;

        for (SZT i = 0; i < a.size(); i++)
            if (a[i] != b[i])
                return false;

        return true;
    }

    // ********************************
    // collection of int's.
    // ********************************
    typedef MCollect<int> IntCollect;

    // Из-за известного бага с реализацией вектора bool'ов приходится
    // делать его через вектор int-ов. Из современных версий STL по
    // крайней мере GCC 4.x сильно жалуется на vector<bool>::operator[]=true
    typedef MCollect<int> BoolCollect;

} //end of namespace 'lem'


#undef BC 
#undef SZT

#endif
