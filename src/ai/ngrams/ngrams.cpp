#if !defined(SOL_NO_NGRAMS)

// Справочник N-грамм
//
// 03.02.2009 - добавлен аргумент "минимальная частота" при выборке N-грамм из базы.
// 05.02.2009 - введение поддержки FireBird в качестве storage engine
// 30.03.2009 - полная переделка работы читателя N-грамм.
// 26.07.2009 - для представления кол-ва записей используется int64
// 08.03.2010 - исправление ошибки с использованием sqlite3_column_text16 под Linux
// 07.06.2011 - добавлено перечисление записей для файлового хранилища N-грамм
//
// CD->09.01.2008
// LC->17.04.2018

#include <float.h>
#include <lem/sqlite_helpers.h>
#include <lem/streams.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/NGramHandler.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/LemmatizatorStorage.h>
#include <lem/solarix/_sg_api.h>
#include <lem/solarix/ngrams.h>
#include <lem/solarix/ngrams_hashing.h>

using namespace lem;
using namespace Solarix;


static lem::FString to_utf8(const lem::UCString &u)
{
    return lem::to_utf8(u.c_str());
}


// -------------------------------------------------------------

Ngrams::Cache2::~Cache2()
{
    delete[] marks_filepos;
    marks_filepos = nullptr;

    delete[] marks_n;
    marks_n = nullptr;

    delete[] search_buffer;
    search_buffer = nullptr;

    return;
}

lem::int64_t Ngrams::Cache2::LoadBin(const lem::Path &filename)
{
    lem::int64_t res = 0;

    if (filename.DoesExist())
    {
        bin = new lem::BinaryReader(filename);

        lem::int64_t handler_flags;
        bin->read(&handler_flags, sizeof(handler_flags));

        lem::int64_t marks_pos;
        bin->read(&marks_pos, sizeof(marks_pos));
        bin->read(&n, sizeof(n));
        bin->read(&max_freq, sizeof(max_freq));
        bin->read(&n_marks, sizeof(n_marks));

        bin->seekp64(marks_pos);

        marks_filepos = new lem::uint64_t[n_marks];
        marks_n = new lem::uint32_t[n_marks];
        bin->read(marks_filepos, sizeof(*marks_filepos)*n_marks);
        bin->read(marks_n, sizeof(*marks_n)*n_marks);

        int max_n = 0;
        for (int i = 0; i < n_marks; ++i)
            max_n = max(max_n, int(marks_n[i]));

        search_buffer = new Cached2Gram[max_n];

        res = n;
    }

    return res;
}

std::pair<int/*id*/, int/*w*/> Ngrams::Cache2::find(int x, int y) const
{
    const int i_block = ngram2hash(x, y) % n_marks;
    LEM_CHECKIT_Z(i_block >= 0 && i_block < n_marks);

    bin->seekp64(marks_filepos[i_block]);

    std::pair<int, int> ngram(x, y);

    if (marks_n[i_block] <= 10)
    {
        Cached2Gram rec;
        for (lem::uint32_t i = 0; i < marks_n[i_block]; ++i)
        {
            bin->read(&rec, sizeof(rec));
            if (rec.ngram == ngram)
                return std::make_pair(rec.id, rec.w);
        }
    }
    else
    {
        bin->read(search_buffer, sizeof(Cached2Gram)*marks_n[i_block]);

        int i_left = 0, i_right = marks_n[i_block] - 1;
        while ((i_right - i_left) > 1)
        {
            int i_mid = (i_right + i_left) / 2;

            if (search_buffer[i_mid].ngram == ngram)
                return std::make_pair(search_buffer[i_mid].id, search_buffer[i_mid].w);

            if (search_buffer[i_mid].ngram > ngram)
                i_left = i_mid;
            else
                i_right = i_mid;
        }

        if (search_buffer[i_left].ngram == ngram)
            return std::make_pair(search_buffer[i_left].id, search_buffer[i_left].w);

        if (search_buffer[i_right].ngram == ngram)
            return std::make_pair(search_buffer[i_right].id, search_buffer[i_right].w);
    }


    return std::make_pair(-1, -1);
}


void Ngrams::Cache2::ForEach(Ngrams *n, const lem::FString &db_suffix, const lem::FString &segment_name, Ngrams::raw *r, NGramHandler *handler)
{
    for (int i_block = 0; i_block < n_marks; ++i_block)
    {
        bin->seekp64(marks_filepos[i_block]);
        bin->read(search_buffer, sizeof(Cached2Gram)*marks_n[i_block]);

        for (int j = 0; j < marks_n[i_block]; ++j)
        {
            const int id_word1 = search_buffer[j].ngram.first;
            const int id_word2 = search_buffer[j].ngram.second;
            const int id_ngram = search_buffer[j].id;
            const int w = search_buffer[j].w;

            lem::UCString word1 = n->GetWord(db_suffix, segment_name, id_word1);
            lem::UCString word2 = n->GetWord(db_suffix, segment_name, id_word2);

            if (!handler->Do(*n, id_ngram, w, id_word1, id_word2, word1, word2))
                break;
        }
    }

    return;
}



// -------------------------------------------------------------


Ngrams::Cache3::~Cache3()
{
    delete[] marks_filepos;
    marks_filepos = nullptr;

    delete[] marks_n;
    marks_n = nullptr;

    delete[] search_buffer;
    search_buffer = nullptr;

    return;
}


lem::int64_t Ngrams::Cache3::LoadBin(const lem::Path &filename)
{
    lem::int64_t res = 0;

    if (filename.DoesExist())
    {
        bin = new lem::BinaryReader(filename);

        lem::int64_t handler_flags;
        bin->read(&handler_flags, sizeof(handler_flags));

        lem::int64_t marks_pos;
        bin->read(&marks_pos, sizeof(marks_pos));
        bin->read(&n, sizeof(n));
        bin->read(&max_freq, sizeof(max_freq));
        bin->read(&n_marks, sizeof(n_marks));

        bin->seekp64(marks_pos);

        marks_filepos = new lem::uint64_t[n_marks];
        marks_n = new lem::uint32_t[n_marks];
        bin->read(marks_filepos, sizeof(*marks_filepos)*n_marks);
        bin->read(marks_n, sizeof(*marks_n)*n_marks);

        int max_n = 0;
        for (int i = 0; i < n_marks; ++i)
            max_n = max(max_n, int(marks_n[i]));

        search_buffer = new Cached3Gram[max_n];

        res = n;
    }

    return res;
}

std::pair<int/*id*/, int/*w*/> Ngrams::Cache3::find(int x, int y, int z) const
{
    const int i_block = ngram3hash(x, y, z) % n_marks;
    LEM_CHECKIT_Z(i_block >= 0 && i_block < n_marks);

    bin->seekp64(marks_filepos[i_block]);

    lem::triple<int, int, int> ngram(x, y, z);

    if (marks_n[i_block] <= 10)
    {
        Cached3Gram rec;
        for (lem::uint32_t i = 0; i < marks_n[i_block]; ++i)
        {
            bin->read(&rec, sizeof(rec));
            if (rec.ngram == ngram)
                return std::make_pair(rec.id, rec.w);
        }
    }
    else
    {
        bin->read(search_buffer, sizeof(Cached3Gram)*marks_n[i_block]);

        int i_left = 0, i_right = marks_n[i_block] - 1;
        while ((i_right - i_left) > 1)
        {
            int i_mid = (i_right + i_left) / 2;

            if (search_buffer[i_mid].ngram == ngram)
                return std::make_pair(search_buffer[i_mid].id, search_buffer[i_mid].w);

            if (search_buffer[i_mid].ngram < ngram)
                i_right = i_mid;
            else
                i_left = i_mid;
        }

        if (search_buffer[i_left].ngram == ngram)
            return std::make_pair(search_buffer[i_left].id, search_buffer[i_left].w);

        if (search_buffer[i_right].ngram == ngram)
            return std::make_pair(search_buffer[i_right].id, search_buffer[i_right].w);
    }

    return std::make_pair(-1, -1);
}

void Ngrams::Cache3::ForEach(Ngrams *n, const lem::FString &db_suffix, const lem::FString &segment_name, Ngrams::raw *r, NGramHandler *handler)
{
    for (int i_block = 0; i_block < n_marks; ++i_block)
    {
        bin->seekp64(marks_filepos[i_block]);
        bin->read(search_buffer, sizeof(Cached3Gram)*marks_n[i_block]);

        for (int j = 0; j < marks_n[i_block]; ++j)
        {
            const int id_word1 = search_buffer[j].ngram.first;
            const int id_word2 = search_buffer[j].ngram.second;
            const int id_word3 = search_buffer[j].ngram.third;
            const int id_ngram = search_buffer[j].id;
            const int w = search_buffer[j].w;

            lem::UCString word1 = n->GetWord(db_suffix, segment_name, id_word1);
            lem::UCString word2 = n->GetWord(db_suffix, segment_name, id_word2);
            lem::UCString word3 = n->GetWord(db_suffix, segment_name, id_word3);

            if (!handler->Do(*n, id_ngram, w, id_word1, id_word2, id_word3, word1, word2, word3))
                break;
        }
    }

    return;
}


// -------------------------------------------------------------


Ngrams::Cache4::~Cache4()
{
    delete[] marks_filepos;
    marks_filepos = nullptr;

    delete[] marks_n;
    marks_n = nullptr;

    delete[] search_buffer;
    search_buffer = nullptr;

    return;
}


lem::int64_t Ngrams::Cache4::LoadBin(const lem::Path &filename)
{
    lem::int64_t res = 0;

    if (filename.DoesExist())
    {
        bin = new lem::BinaryReader(filename);

        lem::int64_t handler_flags;
        bin->read(&handler_flags, sizeof(handler_flags));

        lem::int64_t marks_pos;
        bin->read(&marks_pos, sizeof(marks_pos));
        bin->read(&n, sizeof(n));
        bin->read(&max_freq, sizeof(max_freq));
        bin->read(&n_marks, sizeof(n_marks));

        bin->seekp64(marks_pos);

        marks_filepos = new lem::uint64_t[n_marks];
        marks_n = new lem::uint32_t[n_marks];
        bin->read(marks_filepos, sizeof(*marks_filepos)*n_marks);
        bin->read(marks_n, sizeof(*marks_n)*n_marks);

        int max_n = 0;
        for (int i = 0; i < n_marks; ++i)
            max_n = max(max_n, int(marks_n[i]));

        search_buffer = new Cached4Gram[max_n];

        res = n;
    }

    return res;
}

std::pair<int/*id*/, int/*w*/> Ngrams::Cache4::find(int i1, int i2, int i3, int i4) const
{
    const int i_block = ngram4hash(i1, i2, i3, i4) % n_marks;
    LEM_CHECKIT_Z(i_block >= 0 && i_block < n_marks);

    bin->seekp64(marks_filepos[i_block]);

    lem::foursome<int, int, int, int> ngram(i1, i2, i3, i4);

    if (marks_n[i_block] <= 10)
    {
        Cached4Gram rec;
        for (lem::uint32_t i = 0; i < marks_n[i_block]; ++i)
        {
            bin->read(&rec, sizeof(rec));
            if (rec.ngram == ngram)
                return std::make_pair(rec.id, rec.w);
        }
    }
    else
    {
        bin->read(search_buffer, sizeof(Cached4Gram)*marks_n[i_block]);

        int i_left = 0, i_right = marks_n[i_block] - 1;
        while ((i_right - i_left) > 1)
        {
            int i_mid = (i_right + i_left) / 2;

            if (search_buffer[i_mid].ngram == ngram)
                return std::make_pair(search_buffer[i_mid].id, search_buffer[i_mid].w);

            if (search_buffer[i_mid].ngram < ngram)
                i_right = i_mid;
            else
                i_left = i_mid;
        }

        if (search_buffer[i_left].ngram == ngram)
            return std::make_pair(search_buffer[i_left].id, search_buffer[i_left].w);

        if (search_buffer[i_right].ngram == ngram)
            return std::make_pair(search_buffer[i_right].id, search_buffer[i_right].w);
    }

    return std::make_pair(-1, -1);
}


void Ngrams::Cache4::ForEach(Ngrams *n, const lem::FString &db_suffix, const lem::FString &segment_name, Ngrams::raw *r, NGramHandler *handler)
{
    for (int i_block = 0; i_block < n_marks; ++i_block)
    {
        bin->seekp64(marks_filepos[i_block]);
        bin->read(search_buffer, sizeof(Cached4Gram)*marks_n[i_block]);

        for (int j = 0; j < marks_n[i_block]; ++j)
        {
            const int id_word1 = search_buffer[j].ngram.first;
            const int id_word2 = search_buffer[j].ngram.second;
            const int id_word3 = search_buffer[j].ngram.third;
            const int id_word4 = search_buffer[j].ngram.fourth;
            const int id_ngram = search_buffer[j].id;
            const int w = search_buffer[j].w;

            lem::UCString word1 = n->GetWord(db_suffix, segment_name, id_word1);
            lem::UCString word2 = n->GetWord(db_suffix, segment_name, id_word2);
            lem::UCString word3 = n->GetWord(db_suffix, segment_name, id_word3);
            lem::UCString word4 = n->GetWord(db_suffix, segment_name, id_word4);

            if (!handler->Do(*n, id_ngram, w, id_word1, id_word2, id_word3, id_word4, word1, word2, word3, word4))
                break;
        }
    }

    return;
}


// -------------------------------------------------------------


Ngrams::Cache5::~Cache5()
{
    delete[] marks_filepos;
    marks_filepos = nullptr;

    delete[] marks_n;
    marks_n = nullptr;

    delete[] search_buffer;
    search_buffer = nullptr;

    return;
}


lem::int64_t Ngrams::Cache5::LoadBin(const lem::Path &filename)
{
    lem::int64_t res = 0;

    if (filename.DoesExist())
    {
        bin = new lem::BinaryReader(filename);

        lem::int64_t handler_flags;
        bin->read(&handler_flags, sizeof(handler_flags));

        lem::int64_t marks_pos;
        bin->read(&marks_pos, sizeof(marks_pos));
        bin->read(&n, sizeof(n));
        bin->read(&max_freq, sizeof(max_freq));
        bin->read(&n_marks, sizeof(n_marks));

        bin->seekp64(marks_pos);

        marks_filepos = new lem::uint64_t[n_marks];
        marks_n = new lem::uint32_t[n_marks];
        bin->read(marks_filepos, sizeof(*marks_filepos)*n_marks);
        bin->read(marks_n, sizeof(*marks_n)*n_marks);

        int max_n = 0;
        for (int i = 0; i < n_marks; ++i)
            max_n = max(max_n, int(marks_n[i]));

        search_buffer = new Cached5Gram[max_n];

        res = n;
    }

    return res;
}

std::pair<int/*id*/, int/*w*/> Ngrams::Cache5::find(int i1, int i2, int i3, int i4, int i5) const
{
    const int i_block = ngram5hash(i1, i2, i3, i4, i5) % n_marks;
    LEM_CHECKIT_Z(i_block >= 0 && i_block < n_marks);

    bin->seekp64(marks_filepos[i_block]);

    lem::tuple5<int, int, int, int, int> ngram(i1, i2, i3, i4, i5);

    if (marks_n[i_block] <= 10)
    {
        Cached5Gram rec;
        for (lem::uint32_t i = 0; i < marks_n[i_block]; ++i)
        {
            bin->read(&rec, sizeof(rec));
            if (rec.ngram == ngram)
                return std::make_pair(rec.id, rec.w);
        }
    }
    else
    {
        bin->read(search_buffer, sizeof(Cached5Gram)*marks_n[i_block]);

        int i_left = 0, i_right = marks_n[i_block] - 1;
        while ((i_right - i_left) > 1)
        {
            int i_mid = (i_right + i_left) / 2;

            if (search_buffer[i_mid].ngram == ngram)
                return std::make_pair(search_buffer[i_mid].id, search_buffer[i_mid].w);

            if (search_buffer[i_mid].ngram < ngram)
                i_right = i_mid;
            else
                i_left = i_mid;
        }

        if (search_buffer[i_left].ngram == ngram)
            return std::make_pair(search_buffer[i_left].id, search_buffer[i_left].w);

        if (search_buffer[i_right].ngram == ngram)
            return std::make_pair(search_buffer[i_right].id, search_buffer[i_right].w);
    }

    return std::make_pair(-1, -1);
}


void Ngrams::Cache5::ForEach(Ngrams *n, const lem::FString &db_suffix, const lem::FString &segment_name, Ngrams::raw *r, NGramHandler *handler)
{
    for (int i_block = 0; i_block < n_marks; ++i_block)
    {
        bin->seekp64(marks_filepos[i_block]);
        bin->read(search_buffer, sizeof(Cached5Gram)*marks_n[i_block]);

        for (int j = 0; j < marks_n[i_block]; ++j)
        {
            const int id_word1 = search_buffer[j].ngram.first;
            const int id_word2 = search_buffer[j].ngram.second;
            const int id_word3 = search_buffer[j].ngram.third;
            const int id_word4 = search_buffer[j].ngram.fourth;
            const int id_word5 = search_buffer[j].ngram.fifth;
            const int id_ngram = search_buffer[j].id;
            const int w = search_buffer[j].w;

            lem::UCString word1 = n->GetWord(db_suffix, segment_name, id_word1);
            lem::UCString word2 = n->GetWord(db_suffix, segment_name, id_word2);
            lem::UCString word3 = n->GetWord(db_suffix, segment_name, id_word3);
            lem::UCString word4 = n->GetWord(db_suffix, segment_name, id_word4);
            lem::UCString word5 = n->GetWord(db_suffix, segment_name, id_word5);

            if (!handler->Do(*n, id_ngram, w, id_word1, id_word2, id_word3, id_word4, id_word5, word1, word2, word3, word4, word5))
                break;
        }
    }

    return;
}

// ---------------------------------------------------------



Ngrams::raw::raw(const char *sfx) :suffix(sfx)
{
    clear();
    suffix.re_clear();
    return;
}

void Ngrams::raw::clear()
{
    max_w1 = max_w2 = max_w3 = max_w4 = max_w5 = 0.F;
    nraw1 = nraw2 = nraw3 = nraw4 = nraw5 = 0;
    cache2.clear();
    cache3.clear();
    cache4.clear();
    cache5.clear();
    return;
}





lem::int64_t Ngrams::raw::PreloadCachesFromFiles(const lem::Path &folder)
{
    cache2.clear();
    cache3.clear();
    cache4.clear();
    cache5.clear();

    lem::int64_t res = 0;

    for (lem::Container::size_type i = 0; i < segments.size(); ++i)
    {
        cache2.push_back(new Cache2);
        cache3.push_back(new Cache3);
        cache4.push_back(new Cache4);
        cache5.push_back(new Cache5);

        const lem::FString & segment = segments[i];

        lem::UFString filename2 = lem::format_str(L"NGRAM2%hs%hs", suffix.c_str(), segment.c_str());
        lem::Path p2(folder);
        p2.ConcateLeaf(filename2);

        if (p2.DoesExist())
        {
            nraw2 += cache2.back()->LoadBin(p2);
            max_w2 = std::max(max_w2, (float)cache2.back()->max_freq);
            res += nraw2;
        }

        lem::UFString filename3 = lem::format_str(L"NGRAM3%hs%hs", suffix.c_str(), segment.c_str());
        lem::Path p3(folder);
        p3.ConcateLeaf(filename3);
        if (p3.DoesExist())
        {
            nraw3 += cache3.back()->LoadBin(p3);
            max_w3 = std::max(max_w3, (float)cache3.back()->max_freq);
            res += nraw3;
        }

        lem::UFString filename4 = lem::format_str(L"NGRAM4%hs%hs", suffix.c_str(), segment.c_str());
        lem::Path p4(folder);
        p4.ConcateLeaf(filename4);
        if (p4.DoesExist())
        {
            nraw4 += cache4.back()->LoadBin(p4);
            max_w4 = std::max(max_w4, (float)cache4.back()->max_freq);
            res += nraw4;
        }

        lem::UFString filename5 = lem::format_str(L"NGRAM5%hs%hs", suffix.c_str(), segment.c_str());
        lem::Path p5(folder);
        p5.ConcateLeaf(filename5);
        if (p5.DoesExist())
        {
            nraw5 += cache5.back()->LoadBin(p5);
            max_w5 = std::max(max_w5, (float)cache5.back()->max_freq);
            res += nraw5;
        }
    }

    return res;
}



lem::int64_t Ngrams::cov::PreloadCachesFromFiles(const lem::Path &folder)
{
    cache2.clear(); cache2.resize(segments.size());

    lem::int64_t ret = 0;

    for (lem::Container::size_type i = 0; i < segments.size(); ++i)
    {
        cache2.push_back(new Cache2);

        const lem::FString & segment = segments[i];

        lem::UFString filename2 = lem::format_str(L"NGRAM2%hs%hs.cache", suffix.c_str(), segment.c_str());
        lem::Path p2(folder);
        p2.ConcateLeaf(filename2);
        ret += cache2.back()->LoadBin(p2);
    }

    return ret;
}



Ngrams::Ngrams(Solarix::Dictionary *d)
    : db_n_2_n("_n_2_n"), db_a_2_n("_a_2_n"), db_n_2_v("_n_2_v"), db_adv_2_v("_adv_2_v"),
    db_adv_2_a("_adv_2_a"), db_p_2_n("_p_2_n"), db_obj_2_v("_obj_2_v"),
    db_raw(""), db_literal("_literal")
{
    LEM_CHECKIT_Z(d);
    dict = d;
    db_raw.lemmatize = true;
    return;
}


Ngrams::~Ngrams()
{
    Delete();
    return;
}


void Ngrams::Delete()
{
    Delete(a_n);
    Delete(n_a);

    Delete(n_v);
    Delete(v_n);

    Delete(n_n);

    Delete(adv_a);
    Delete(a_adv);

    Delete(adv_v);
    Delete(v_adv);

    Delete(n_p);
    Delete(p_n);

    Delete(v_obj);
    Delete(obj_v);

    db_raw.clear();
    db_literal.clear();

    return;
}


void Ngrams::Delete(Ngrams::digram_type &table) const
{
    for (digram_type::const_iterator i1 = table.begin(); i1 != table.end(); i1++)
        delete i1->second;
    table.clear();

    return;
}


#if defined SOL_CAA
void Ngrams::GenerateReverse(const Ngrams::digram_type &src, Ngrams::digram_type &dst)
{
    for (digram_type::const_iterator i = src.begin(); i != src.end(); ++i)
    {
        const lem::MCollect<std::pair<int/*ientry*/, float> > &linked = *i->second;
        for (lem::Container::size_type j = 0; j < linked.size(); ++j)
        {
            Add(dst, linked[j].first, i->first, linked[j].second);
        }
    }

    return;
}
#endif

void Ngrams::SetStorage(NGramsDBMS *_storage)
{
    db = _storage;
    available = db.NotNull();
    return;
}



#if defined SOL_LOADBIN
void Ngrams::Load(const lem::Path &_folder)
{
    Delete();
    folder = _folder;

    lem::Path dbfile(folder);

    if (dbfile.IsFolder())
    {
        dbfile.ConcateLeaf(L"NGRAMS");
    }

    dbfile = dbfile.GetAbsolutePath();


    if (db->IsRemote() || dbfile.DoesExist())
    {
        if (!db->IsRemote())
        {
            if (db->Connected())
                db->Disconnect();

            db->Connect(dbfile);
        }

        db->BeginReadTx();

        LoadCovalent();
        LoadRaw(db_raw);
        LoadRaw(db_literal);

#if LEM_DEBUGGING==1 && defined SOL_CAA

        // DumpRaw2(*mout);
        // DumpLiteral2(*mout);
        // DumpRaw3(*mout);
        // DumpLiteral3(*mout);

        lem::int64_t n1 = CountAdjsForNoun();
        lem::int64_t n2 = CountVerbsForNoun();
        lem::int64_t n3 = CountObjsForVerb();
        lem::int64_t n4 = CountNounsForNoun();
        lem::int64_t n5 = CountAdvsForAdj();
        lem::int64_t n6 = CountAdvsForVerb();
        lem::int64_t n7 = CountPreposForNoun();
        lem::int64_t n8 = CountRaw2();
        lem::int64_t n9 = CountRaw3();
        lem::int64_t n10 = CountRaw4();
        lem::int64_t n11 = CountRaw5();
        lem::int64_t n12 = CountLiteral2();
        lem::int64_t n13 = CountLiteral3();
        lem::int64_t n14 = CountLiteral4();
        lem::int64_t n15 = CountLiteral5();
#endif

        db->CommitReadTx();
        available = true;
    }

    if (!db->IsRemote() && !dbfile.DoesExist())
    {
        if (db->Connected())
            db->Disconnect();

        db->Connect(dbfile);
        available = true;
    }

    PreloadCachesFromFiles();

    return;
}
#endif




#if defined SOL_LOADBIN
void Ngrams::LoadCovalent()
{
    LoadCovalent(db_n_2_n);
    LoadCovalent(db_a_2_n);
    LoadCovalent(db_n_2_v);
    LoadCovalent(db_adv_2_v);
    LoadCovalent(db_adv_2_a);
    LoadCovalent(db_p_2_n);
    LoadCovalent(db_obj_2_v);

    return;
}


void Ngrams::LoadCovalent(Ngrams::cov &pdb)
{
#if defined LEM_THREADS
    lem::Process::CritSecLocker guard(&pdb.cs);
#endif

    pdb.n = 0;

    if (db->Connected())
    {
        if (pdb.segments.empty())
        {
            db->LoadSegments(pdb.suffix, pdb.segments);
        }

        pdb.max_w = 0;
        pdb.min_w = FLT_MIN;
        pdb.n = 0;

        for (lem::Container::size_type i = 0; i < pdb.segments.size(); ++i)
        {
            FString sgm = pdb.segments[i];
            sgm.re_clear();

            if (db->GetStat(2, pdb.suffix, sgm, pdb.min_w, pdb.max_w, pdb.n))
            {
                pdb.has = true;
            }
        }
    }

    return;
}

#endif


#if defined SOL_LOADBIN
void Ngrams::LoadRaw(Ngrams::raw &pdb)
{
#if defined LEM_THREADS
    lem::Process::CritSecLocker guard(&pdb.cs);
#endif

    if (db->Connected())
    {
        if (pdb.segments.empty())
        {
            db->LoadSegments(pdb.suffix, pdb.segments);
        }

        pdb.max_w1 = pdb.max_w2 = pdb.max_w3 = pdb.max_w4 = pdb.max_w5 = 0;
        pdb.nraw2 = pdb.nraw3 = pdb.nraw4 = pdb.nraw5 = 0;
        float dummy_minw = 0;

        for (lem::Container::size_type i = 0; i < pdb.segments.size(); ++i)
        {
            lem::FString sgm = pdb.segments[i];
            sgm.re_clear();

            if (db->GetStat(1, pdb.suffix, sgm, dummy_minw, pdb.max_w1, pdb.nraw1))
            {
                pdb.has1 = true;
            }

            if (db->GetStat(2, pdb.suffix, sgm, dummy_minw, pdb.max_w2, pdb.nraw2))
            {
                pdb.has2 = true;
            }

            if (db->GetStat(3, pdb.suffix, sgm, dummy_minw, pdb.max_w3, pdb.nraw3))
            {
                pdb.has3 = true;
            }

            if (db->GetStat(4, pdb.suffix, sgm, dummy_minw, pdb.max_w4, pdb.nraw4))
            {
                pdb.has4 = true;
            }

            if (db->GetStat(5, pdb.suffix, sgm, dummy_minw, pdb.max_w5, pdb.nraw5))
            {
                pdb.has5 = true;
            }
        }
    }

    return;
}
#endif


#if defined SOL_CAA
void Ngrams::FindLeftWords(
    Ngrams::cov & pdb,
    int ie_right,
    lem::MCollect<std::pair<int/*ientry*/, float> > & reslist,
    int min_freq
)
{
    LEM_CHECKIT_Z(ie_right != UNKNOWN);

    if (db.NotNull() && db->Connected() && pdb.has)
    {
        std::map< int, float > reslist2;

        for (lem::Container::size_type k = 0; k < pdb.segments.size(); ++k)
        {
            lem::FString sgm = pdb.segments[k];
            sgm.re_clear();
            db->FindLeftWords(pdb.suffix.c_str(), sgm.c_str(), ie_right, reslist2, pdb.min_w, pdb.max_w, min_freq);
        }

        std::copy(reslist2.begin(), reslist2.end(), std::back_inserter(reslist));
    }

    return;
}
#endif


#if defined SOL_CAA
void Ngrams::FindRightWords(
    Ngrams::cov & pdb,
    int ie_left,
    lem::MCollect<std::pair<int/*ientry*/, float> > & reslist,
    int min_freq
)
{
    LEM_CHECKIT_Z(ie_left != UNKNOWN);

    if (db.NotNull() && db->Connected() && pdb.has)
    {
        std::map< int, float > reslist2;

        for (lem::Container::size_type k = 0; k < pdb.segments.size(); ++k)
        {
            lem::FString sgm = pdb.segments[k];
            sgm.re_clear();
            db->FindRightWords(pdb.suffix.c_str(), sgm.c_str(), ie_left, reslist2, pdb.min_w, pdb.max_w, min_freq);
        }

        std::copy(reslist2.begin(), reslist2.end(), std::back_inserter(reslist));
    }

    return;
}
#endif

#if defined SOL_CAA
void Ngrams::FindAdjsForNoun(int ie_noun, lem::MCollect<std::pair<int/*ientry*/, float> > & res, int min_freq)
{
    FindLeftWords(db_a_2_n, ie_noun, res, min_freq);

    digram_type::const_iterator p = n_a.find(ie_noun);
    if (p != n_a.end())
    {
        const lem::MCollect<std::pair<int/*ientry*/, float> > * a = p->second;
        std::copy(a->begin(), a->end(), std::back_inserter(res));
    }

    return;
}
#endif


#if defined SOL_CAA
void Ngrams::FindNounsForAdj(int ie_adj, lem::MCollect<std::pair<int/*ientry*/, float> > & res, int min_freq)
{
    FindRightWords(db_a_2_n, ie_adj, res, min_freq);

    digram_type::const_iterator p = a_n.find(ie_adj);
    if (p != a_n.end())
    {
        const lem::MCollect<std::pair<int/*ientry*/, float> > * a = p->second;
        std::copy(a->begin(), a->end(), std::back_inserter(res));
    }

    return;
}
#endif

#if defined SOL_CAA
void Ngrams::FindVerbsForNoun(int ie_noun, lem::MCollect<std::pair<int/*ientry*/, float> > & res, int min_freq)
{
    FindLeftWords(db_n_2_v, ie_noun, res, min_freq);

    digram_type::const_iterator p = n_v.find(ie_noun);
    if (p != n_v.end())
    {
        const lem::MCollect<std::pair<int/*ientry*/, float> > * a = p->second;
        std::copy(a->begin(), a->end(), std::back_inserter(res));
    }

    return;
}
#endif


#if defined SOL_CAA
void Ngrams::FindNounsForVerb(int ie_verb, lem::MCollect<std::pair<int/*ientry*/, float> > & res, int min_freq)
{
    FindRightWords(db_n_2_v, ie_verb, res, min_freq);

    digram_type::const_iterator p = v_n.find(ie_verb);
    if (p != v_n.end())
    {
        const lem::MCollect<std::pair<int/*ientry*/, float> > * a = p->second;
        std::copy(a->begin(), a->end(), std::back_inserter(res));
    }

    return;
}
#endif


#if defined SOL_CAA
void Ngrams::FindNounsForNoun(int ie_noun, lem::MCollect<std::pair<int/*ientry*/, float> > & res, int min_freq)
{
    FindRightWords(db_n_2_n, ie_noun, res, min_freq);

    digram_type::const_iterator p = n_n.find(ie_noun);
    if (p != n_n.end())
    {
        const lem::MCollect<std::pair<int/*ientry*/, float> > * a = p->second;
        std::copy(a->begin(), a->end(), std::back_inserter(res));
    }

    return;
}
#endif


#if defined SOL_CAA
void Ngrams::FindAdvsForAdj(int ie_adj, lem::MCollect<std::pair<int/*ientry*/, float> > & res, int min_freq)
{
    FindLeftWords(db_adv_2_a, ie_adj, res, min_freq);

    digram_type::const_iterator p = a_adv.find(ie_adj);
    if (p != a_adv.end())
    {
        const lem::MCollect<std::pair<int/*ientry*/, float> > * a = p->second;
        std::copy(a->begin(), a->end(), std::back_inserter(res));
    }

    return;
}
#endif

#if defined SOL_CAA
void Ngrams::FindAdjsForAdv(int ie_adv, lem::MCollect<std::pair<int/*ientry*/, float> > & res, int min_freq)
{
    FindRightWords(db_adv_2_a, ie_adv, res, min_freq);

    digram_type::const_iterator p = adv_a.find(ie_adv);
    if (p != adv_a.end())
    {
        const lem::MCollect<std::pair<int/*ientry*/, float> > * a = p->second;
        std::copy(a->begin(), a->end(), std::back_inserter(res));
    }

    return;
}
#endif

#if defined SOL_CAA
void Ngrams::FindAdvsForVerb(int ie_verb, lem::MCollect<std::pair<int/*ientry*/, float> > & res, int min_freq)
{
    FindLeftWords(db_adv_2_v, ie_verb, res, min_freq);

    digram_type::const_iterator p = v_adv.find(ie_verb);
    if (p != v_adv.end())
    {
        const lem::MCollect<std::pair<int/*ientry*/, float> > * a = p->second;
        std::copy(a->begin(), a->end(), std::back_inserter(res));
    }

    return;
}
#endif

#if defined SOL_CAA
void Ngrams::FindVerbsForAdv(int ie_adv, lem::MCollect<std::pair<int/*ientry*/, float> > & res, int min_freq)
{
    FindRightWords(db_adv_2_v, ie_adv, res, min_freq);

    digram_type::const_iterator p = adv_v.find(ie_adv);
    if (p != adv_v.end())
    {
        const lem::MCollect<std::pair<int/*ientry*/, float> > * a = p->second;
        std::copy(a->begin(), a->end(), std::back_inserter(res));
    }

    return;
}
#endif


#if defined SOL_CAA
lem::int64_t Ngrams::CountAdjsForNoun() const
{
    lem::int64_t n = db_a_2_n.n;
    n += CastSizeToInt(a_n.size());
    return n;
}
#endif


#if defined SOL_CAA
lem::int64_t Ngrams::CountVerbsForNoun() const
{
    lem::int64_t n = db_n_2_v.n;
    n += CastSizeToInt(n_v.size());
    return n;
}
#endif


#if defined SOL_CAA
lem::int64_t Ngrams::CountObjsForVerb() const
{
    lem::int64_t n = db_obj_2_v.n;
    n += CastSizeToInt(v_obj.size());
    return n;
}
#endif



#if defined SOL_CAA
lem::int64_t Ngrams::CountNounsForNoun() const
{
    lem::int64_t n = db_n_2_n.n;
    n += CastSizeToInt(n_n.size());
    return n;
}
#endif

#if defined SOL_CAA
lem::int64_t Ngrams::CountAdvsForAdj() const
{
    lem::int64_t n = db_adv_2_a.n;
    n += CastSizeToInt(adv_a.size());
    return n;
}
#endif

#if defined SOL_CAA
lem::int64_t Ngrams::CountAdvsForVerb() const
{
    lem::int64_t n = db_adv_2_v.n;
    n += CastSizeToInt(adv_v.size());
    return n;
}
#endif


#if defined SOL_CAA
lem::int64_t Ngrams::CountPreposForNoun() const
{
    lem::int64_t n = db_p_2_n.n;
    n += CastSizeToInt(n_p.size());
    return n;
}
#endif

#if defined SOL_CAA
// ******************************************************
// Заполняет список всех связанных слов для данного ie.
// ******************************************************
void Ngrams::FindLinkedWords(int ie, lem::MCollect<std::pair<int/*ientry*/, float> > &res, int min_freq)
{
    LEM_CHECKIT_Z(ie != UNKNOWN);

    FindAdjsForNoun(ie, res, min_freq);
    FindNounsForAdj(ie, res, min_freq);

    FindVerbsForNoun(ie, res, min_freq);
    FindNounsForVerb(ie, res, min_freq);

    FindNounsForNoun(ie, res, min_freq);

    FindAdvsForAdj(ie, res, min_freq);
    FindAdjsForAdv(ie, res, min_freq);

    FindAdvsForVerb(ie, res, min_freq);
    FindVerbsForAdv(ie, res, min_freq);

    FindPreposForNoun(ie, res, min_freq);

    FindObjsForVerb(ie, res, min_freq);
    FindVerbsForObj(ie, res, min_freq);

    return;
}
#endif


#if defined SOL_CAA
lem::int64_t Ngrams::CountRaw1() const
{
    return db_raw.nraw1;
}
#endif


#if defined SOL_CAA
lem::int64_t Ngrams::CountRaw2() const
{
    return db_raw.nraw2;
}
#endif

#if defined SOL_CAA
lem::int64_t Ngrams::CountRaw3() const
{
    return db_raw.nraw3;
}
#endif

#if defined SOL_CAA
lem::int64_t Ngrams::CountRaw4() const
{
    return db_raw.nraw4;
}
#endif

#if defined SOL_CAA
lem::int64_t Ngrams::CountRaw5() const
{
    return db_raw.nraw5;
}
#endif

#if defined SOL_CAA
lem::int64_t Ngrams::CountLiteral1() const
{
    return db_literal.nraw1;
}
#endif

#if defined SOL_CAA
lem::int64_t Ngrams::CountLiteral2() const
{
    return db_literal.nraw2;
}
#endif

#if defined SOL_CAA
lem::int64_t Ngrams::CountLiteral3() const
{
    return db_literal.nraw3;
}
#endif

#if defined SOL_CAA
lem::int64_t Ngrams::CountLiteral4() const
{
    return db_literal.nraw4;
}
#endif


#if defined SOL_CAA
lem::int64_t Ngrams::CountLiteral5() const
{
    return db_literal.nraw5;
}
#endif

#if defined SOL_CAA
lem::int64_t Ngrams::CountRaw() const
{
    return CountRaw1() + CountRaw2() + CountRaw3() + CountRaw4() + CountRaw5();
}
#endif

#if defined SOL_CAA
lem::int64_t Ngrams::CountLiteral() const
{
    return CountLiteral1() + CountLiteral2() + CountLiteral3() + CountLiteral4() + CountLiteral5();
}
#endif

#if defined SOL_CAA
lem::int64_t Ngrams::CountCovalent() const
{
    lem::int64_t n = 0;

    n += CountAdjsForNoun();
    n += CountVerbsForNoun();
    n += CountNounsForNoun();
    n += CountAdvsForAdj();
    n += CountAdvsForVerb();
    n += CountPreposForNoun();
    n += CountObjsForVerb();

    return n;
}
#endif


#if defined SOL_CAA
// ***********************************
// Общее кол-во записей в базе.
// ***********************************
lem::int64_t Ngrams::TotalCount() const
{
    return CountCovalent() + CountRaw() + CountLiteral();
}
#endif



#if defined SOL_CAA
bool Ngrams::FindRawNGrams(
    Ngrams::raw & pdb,
    const lem::UCString &_left,
    float &w,
    int &iw
)
{
    return FindRawNGramsID(pdb, _left, w, iw) != UNKNOWN;
}

int Ngrams::FindRawNGramsID(
    Ngrams::raw & pdb,
    const lem::UCString &_left,
    float &w,
    int &iw
)
{
    LEM_CHECKIT_Z(!_left.empty());

    w = 0.F;
    iw = 0;
    int id = UNKNOWN;

    if (db.NotNull() && db->Connected() && pdb.has1)
    {
        UCString left(_left);

        if (pdb.lemmatize)
        {
            Normalize(left);
        }
        else
        {
            left.to_upper();
        }

        db->BeginReadTx();

        int sum_f = 0;

        for (lem::Container::size_type k = 0; k < pdb.segments.size(); ++k)
        {
            lem::FString sgm = pdb.segments[k];
            sgm.re_clear();

            std::pair<int, int> r = db->FindRawNGramsID(pdb.suffix, sgm, left);
            const int f = r.first;
            if (f > 0)
            {
                sum_f += f;
                id = r.second;
            }
        }

        db->CommitReadTx();

        if (sum_f > 0)
        {
            w = float(sum_f) / pdb.max_w1;
            iw = sum_f;
        }
    }

    return id;
}
#endif



#if defined SOL_CAA
bool Ngrams::FindRawNGrams(
    Ngrams::raw & pdb,
    const lem::UCString &_left,
    const lem::UCString &_right,
    float &w,
    int &iw
)
{
    return FindRawNGramsID(pdb, _left, _right, w, iw) != UNKNOWN;
}

int Ngrams::FindRawNGramsID(
    Ngrams::raw & pdb,
    const lem::UCString &_left,
    const lem::UCString &_right,
    float &w,
    int &iw
)
{
    LEM_CHECKIT_Z(!_left.empty());
    LEM_CHECKIT_Z(!_right.empty());

    w = 0.F;
    iw = 0;
    int id = UNKNOWN;

    if (_left.empty() || _right.empty())
        return id;

    if (db.NotNull() && db->Connected() && pdb.has2)
    {
        UCString left(_left), right(_right);

        if (pdb.lemmatize)
        {
            Normalize(left);
            Normalize(right);
        }
        else
        {
            left.to_upper();
            right.to_upper();
        }

        db->BeginReadTx();

        int sum_f = 0;

        for (lem::Container::size_type k = 0; k < pdb.segments.size(); ++k)
        {
            lem::FString sgm = pdb.segments[k];
            sgm.re_clear();

            if (!pdb.cache2.empty() && !pdb.cache2[k]->empty())
            {
                const int i1 = db->FindWord(pdb.suffix, sgm, left);
                if (i1 == -1) continue;

                const int i2 = db->FindWord(pdb.suffix, sgm, right);
                if (i2 == -1) continue;

                std::pair<int /*id*/, int /*w*/> r = pdb.cache2[k]->find(i1, i2);
                id = r.first;
                const int f = r.second;
                sum_f += f;
            }
            else
            {
                std::pair<int, int> r = db->FindRawNGramsID(pdb.suffix, sgm, left, right);
                const int f = r.first;
                if (f > 0)
                {
                    sum_f += f;
                    id = r.second;
                }
            }
        }

        db->CommitReadTx();

        if (sum_f > 0)
        {
            w = float(sum_f) / pdb.max_w2;
            iw = sum_f;
        }
    }

    return id;
}
#endif


#if defined SOL_CAA
bool Ngrams::FindRawNGrams(
    Ngrams::raw & pdb,
    const lem::UCString &_w1,
    const lem::UCString &_w2,
    const lem::UCString &_w3,
    float &w,
    int &iw
)
{
    return FindRawNGramsID(pdb, _w1, _w2, _w3, w, iw) != UNKNOWN;
}


int Ngrams::FindRawNGramsID(
    Ngrams::raw & pdb,
    const lem::UCString &_w1,
    const lem::UCString &_w2,
    const lem::UCString &_w3,
    float &w,
    int &iw
)
{
    LEM_CHECKIT_Z(!_w1.empty());
    LEM_CHECKIT_Z(!_w2.empty());
    LEM_CHECKIT_Z(!_w3.empty());

    w = 0.F;
    iw = 0;
    int id = UNKNOWN;

    if (_w1.empty() || _w2.empty() || _w3.empty())
        return id;

    if (db.NotNull() && db->Connected() && pdb.has3)
    {
        UCString w1(_w1), w2(_w2), w3(_w3);

        if (pdb.lemmatize)
        {
            Normalize(w1);
            Normalize(w2);
            Normalize(w3);
        }
        else
        {
            w1.to_upper();
            w2.to_upper();
            w3.to_upper();
        }

        db->BeginReadTx();
        int sum_f = 0;

        for (lem::Container::size_type k = 0; k < pdb.segments.size(); ++k)
        {
            lem::FString sgm = pdb.segments[k];
            sgm.re_clear();

            if (!pdb.cache3.empty() && !pdb.cache3[k]->empty())
            {
                const int i1 = db->FindWord(pdb.suffix, sgm, w1);
                if (i1 == -1) continue;

                const int i2 = db->FindWord(pdb.suffix, sgm, w2);
                if (i2 == -1) continue;

                const int i3 = db->FindWord(pdb.suffix, sgm, w3);
                if (i3 == -1) continue;

                std::pair<int /*id*/, int /*w*/> r = pdb.cache3[k]->find(i1, i2, i3);
                id = r.first;
                const int f = r.second;
                sum_f += f;
            }
            else
            {
                std::pair<int, int> r = db->FindRawNGramsID(pdb.suffix, sgm, w1, w2, w3);
                const int f = r.first;
                if (f > 0)
                {
                    sum_f += f;
                    id = r.second;
                }
            }
        }

        db->CommitReadTx();

        if (sum_f > 0)
        {
            w = float(sum_f) / pdb.max_w3;
            iw = sum_f;
        }
    }

    return id;
}
#endif


#if defined SOL_CAA
bool Ngrams::FindRawNGrams(
    Ngrams::raw & pdb,
    const lem::UCString &_w1,
    const lem::UCString &_w2,
    const lem::UCString &_w3,
    const lem::UCString &_w4,
    float &w,
    int &iw
)
{
    return FindRawNGramsID(pdb, _w1, _w2, _w3, _w4, w, iw) != UNKNOWN;
}

int Ngrams::FindRawNGramsID(
    Ngrams::raw & pdb,
    const lem::UCString &_w1,
    const lem::UCString &_w2,
    const lem::UCString &_w3,
    const lem::UCString &_w4,
    float &w,
    int &iw
)
{
    LEM_CHECKIT_Z(!_w1.empty());
    LEM_CHECKIT_Z(!_w2.empty());
    LEM_CHECKIT_Z(!_w3.empty());
    LEM_CHECKIT_Z(!_w4.empty());

    w = 0.F;
    iw = 0;
    int id = UNKNOWN;

    if (_w1.empty() || _w2.empty() || _w3.empty() || _w4.empty())
        return id;

    if (db.NotNull() && db->Connected() && pdb.has4)
    {
        UCString w1(_w1), w2(_w2), w3(_w3), w4(_w4);

        if (pdb.lemmatize)
        {
            Normalize(w1);
            Normalize(w2);
            Normalize(w3);
            Normalize(w4);
        }
        else
        {
            w1.to_upper();
            w2.to_upper();
            w3.to_upper();
            w4.to_upper();
        }

        db->BeginReadTx();
        int sum_f = 0;

        for (lem::Container::size_type k = 0; k < pdb.segments.size(); ++k)
        {
            lem::FString sgm = pdb.segments[k];
            sgm.re_clear();

            if (!pdb.cache4.empty() && !pdb.cache4[k]->empty())
            {
                const int i1 = db->FindWord(pdb.suffix, sgm, w1);
                if (i1 == -1) continue;

                const int i2 = db->FindWord(pdb.suffix, sgm, w2);
                if (i2 == -1) continue;

                const int i3 = db->FindWord(pdb.suffix, sgm, w3);
                if (i3 == -1) continue;

                const int i4 = db->FindWord(pdb.suffix, sgm, w4);
                if (i4 == -1) continue;

                std::pair<int /*id*/, int /*w*/> r = pdb.cache4[k]->find(i1, i2, i3, i4);
                id = r.first;
                const int f = r.second;
                sum_f += f;
            }
            else
            {
                std::pair<int, int> r = db->FindRawNGramsID(pdb.suffix, sgm, w1, w2, w3, w4);
                const int f = r.first;
                if (f > 0)
                {
                    sum_f += f;
                    id = r.second;
                }
            }
        }

        db->CommitReadTx();

        if (sum_f > 0)
        {
            w = float(sum_f) / pdb.max_w4;
            iw = sum_f;
        }
    }

    return id;
}
#endif

#if defined SOL_CAA
bool Ngrams::FindRawNGrams(
    Ngrams::raw & pdb,
    const lem::UCString &_w1,
    const lem::UCString &_w2,
    const lem::UCString &_w3,
    const lem::UCString &_w4,
    const lem::UCString &_w5,
    float &w,
    int &iw
)
{
    return FindRawNGramsID(pdb, _w1, _w2, _w3, _w4, _w5, w, iw) != UNKNOWN;
}


int Ngrams::FindRawNGramsID(
    Ngrams::raw & pdb,
    const lem::UCString &_w1,
    const lem::UCString &_w2,
    const lem::UCString &_w3,
    const lem::UCString &_w4,
    const lem::UCString &_w5,
    float &w,
    int &iw
)
{
    LEM_CHECKIT_Z(!_w1.empty());
    LEM_CHECKIT_Z(!_w2.empty());
    LEM_CHECKIT_Z(!_w3.empty());
    LEM_CHECKIT_Z(!_w4.empty());
    LEM_CHECKIT_Z(!_w5.empty());

    w = 0.F;
    iw = 0;

    int id = UNKNOWN;

    if (db.NotNull() && db->Connected() && pdb.has5)
    {
        UCString w1(_w1), w2(_w2), w3(_w3), w4(_w4), w5(_w5);

        if (pdb.lemmatize)
        {
            Normalize(w1);
            Normalize(w2);
            Normalize(w3);
            Normalize(w4);
            Normalize(w5);
        }
        else
        {
            w1.to_upper();
            w2.to_upper();
            w3.to_upper();
            w4.to_upper();
            w5.to_upper();
        }

        db->BeginReadTx();
        int sum_f = 0;

        for (lem::Container::size_type k = 0; k < pdb.segments.size(); ++k)
        {
            lem::FString sgm = pdb.segments[k];
            sgm.re_clear();

            if (!pdb.cache5.empty() && !pdb.cache5[k]->empty())
            {
                const int i1 = db->FindWord(pdb.suffix, sgm, w1);
                if (i1 == -1) continue;

                const int i2 = db->FindWord(pdb.suffix, sgm, w2);
                if (i2 == -1) continue;

                const int i3 = db->FindWord(pdb.suffix, sgm, w3);
                if (i3 == -1) continue;

                const int i4 = db->FindWord(pdb.suffix, sgm, w4);
                if (i4 == -1) continue;

                const int i5 = db->FindWord(pdb.suffix, sgm, w5);
                if (i5 == -1) continue;

                std::pair<int /*id*/, int /*w*/> r = pdb.cache5[k]->find(i1, i2, i3, i4, i5);
                id = r.first;
                const int f = r.second;
                sum_f += f;
            }
            else
            {
                std::pair<int, int> r = db->FindRawNGramsID(pdb.suffix, sgm, w1, w2, w3, w4, w5);
                const int f = r.first;
                if (f > 0)
                {
                    sum_f += f;
                    id = r.second;
                }
            }
        }

        db->CommitReadTx();

        if (sum_f > 0)
        {
            w = float(sum_f) / pdb.max_w5;
            iw = sum_f;
        }
    }

    return id;
}
#endif




#if defined SOL_CAA
void Ngrams::FindRawNGrams(
    Ngrams::raw & pdb,
    const lem::UCString &_left,
    lem::MCollect<lem::UCString> &right,
    lem::MCollect<float> &w,
    int min_freq
)
{
    LEM_CHECKIT_Z(!_left.empty());

    if (db.NotNull() && db->Connected() && pdb.has2)
    {
        UCString left(_left);
        if (pdb.lemmatize)
            Normalize(left);
        else
            left.to_upper();

        std::map< lem::UCString, float > reslist;

        db->BeginReadTx();

        for (lem::Container::size_type k = 0; k < pdb.segments.size(); ++k)
        {
            lem::FString sgm = pdb.segments[k];
            sgm.re_clear();
            db->Find2GramsWithLeft(pdb.suffix, sgm, pdb.max_w2, left, min_freq, reslist);
        }

        for (std::map<UCString, float>::iterator it = reslist.begin(); it != reslist.end(); it++)
        {
            right.push_back(it->first);
            w.push_back(it->second);
        }

        db->CommitReadTx();
    }

    return;
}
#endif


#if defined SOL_CAA
void Ngrams::FindRawNGrams(
    Ngrams::raw & pdb,
    lem::MCollect<lem::UCString> &left,
    const lem::UCString &_right,
    lem::MCollect<float> &w,
    int min_freq
)
{
    LEM_CHECKIT_Z(!_right.empty());

    if (db.NotNull() && db->Connected() && pdb.has2)
    {
        UCString right(_right);
        if (pdb.lemmatize)
            Normalize(right);
        else
            right.to_upper();

        db->BeginReadTx();
        std::map< lem::UCString, float > reslist;

        for (lem::Container::size_type k = 0; k < pdb.segments.size(); ++k)
        {
            lem::FString sgm = pdb.segments[k];
            sgm.re_clear();
            db->Find2GramsWithRight(pdb.suffix, sgm, pdb.max_w2, right, min_freq, reslist);
        }

        for (std::map<UCString, float>::iterator it = reslist.begin(); it != reslist.end(); it++)
        {
            left.push_back(it->first);
            w.push_back(it->second);
        }

        db->CommitReadTx();
    }

    return;
}
#endif





#if defined SOL_CAA
void Ngrams::FindRawNGrams(
    Ngrams::raw & pdb,
    const lem::UCString &_left,
    lem::MCollect<lem::UCString> &right1,
    lem::MCollect<lem::UCString> &right2,
    lem::MCollect<float> &w,
    int min_freq
)
{
    LEM_CHECKIT_Z(!_left.empty());

    if (db.NotNull() && db->Connected() && pdb.has3)
    {
        UCString left(_left);

        if (pdb.lemmatize)
            Normalize(left);
        else
            left.to_upper();

        db->BeginReadTx();
        std::map< std::pair<lem::UCString, lem::UCString>, float > reslist;

        for (lem::Container::size_type k = 0; k < pdb.segments.size(); ++k)
        {
            lem::FString sgm = pdb.segments[k];
            sgm.re_clear();

            db->FindRaw3GramsWithLeft(
                pdb.suffix,
                sgm,
                pdb.max_w3,
                left,
                min_freq,
                reslist
            );
        }

        for (std::map<std::pair<UCString, UCString>, float>::iterator it = reslist.begin(); it != reslist.end(); it++)
        {
            right1.push_back(it->first.first);
            right2.push_back(it->first.second);
            w.push_back(it->second);
        }

        db->CommitReadTx();
    }

    return;
}
#endif


#if defined SOL_CAA
void Ngrams::FindRawNGrams(
    Ngrams::raw & pdb,
    lem::MCollect<lem::UCString> &left1,
    lem::MCollect<lem::UCString> &left2,
    const lem::UCString &_right,
    lem::MCollect<float> &w,
    int min_freq
)
{
    LEM_CHECKIT_Z(!_right.empty());

    if (db.NotNull() && db->Connected() && pdb.has3)
    {
        UCString right(_right);

        if (pdb.lemmatize)
            Normalize(right);
        else
            right.to_upper();

        db->BeginReadTx();
        std::map< std::pair<lem::UCString, lem::UCString>, float > reslist;

        for (lem::Container::size_type k = 0; k < pdb.segments.size(); ++k)
        {
            lem::FString sgm = pdb.segments[k];
            sgm.re_clear();

            db->FindRaw3GramsWithRight(
                pdb.suffix,
                sgm,
                pdb.max_w3,
                right,
                min_freq,
                reslist
            );
        }

        for (std::map<std::pair<UCString, UCString>, float>::iterator it = reslist.begin(); it != reslist.end(); it++)
        {
            left1.push_back(it->first.first);
            left2.push_back(it->first.second);
            w.push_back(it->second);
        }

        db->CommitReadTx();
    }

    return;
}
#endif


#if defined SOL_CAA
void Ngrams::FindRawNGrams(
    Ngrams::raw & pdb,
    lem::MCollect<lem::UCString> &left,
    const lem::UCString &_center,
    lem::MCollect<lem::UCString> &right,
    lem::MCollect<float> &w,
    int min_freq
)
{
    LEM_CHECKIT_Z(!_center.empty());

    if (db.NotNull() && db->Connected() && pdb.has3)
    {
        UCString center(_center);

        if (pdb.lemmatize)
            Normalize(center);
        else
            center.to_upper();

        db->BeginReadTx();
        std::map< std::pair<lem::UCString, lem::UCString>, float > reslist;

        for (lem::Container::size_type k = 0; k < pdb.segments.size(); ++k)
        {
            lem::FString sgm = pdb.segments[k];
            sgm.re_clear();
            db->FindRaw3GramsWithCenter(
                pdb.suffix,
                sgm,
                pdb.max_w3,
                center,
                min_freq,
                reslist
            );
        }

        for (std::map<std::pair<UCString, UCString>, float>::iterator it = reslist.begin(); it != reslist.end(); it++)
        {
            left.push_back(it->first.first);
            right.push_back(it->first.second);
            w.push_back(it->second);
        }

        db->CommitReadTx();
    }

    return;
}
#endif



#if defined SOL_CAA
void Ngrams::Add(const Dictionary& dict, int ie1, int ie2, float v)
{
    LEM_CHECKIT_Z(ie1 != UNKNOWN);
    LEM_CHECKIT_Z(ie2 != UNKNOWN);

    const int ic1 = dict.GetSynGram().GetEntry(ie1).GetClass();
    const int ic2 = dict.GetSynGram().GetEntry(ie2).GetClass();

    if (ic1 == ADJ_ru && ic2 == NOUN_ru)
    {
        Add(a_n, ie1, ie2, v);
        Add(n_a, ie2, ie1, v);
        return;
    }

    if (ic1 == NOUN_ru && ic2 == ADJ_ru)
    {
        Add(n_a, ie1, ie2, v);
        Add(a_n, ie2, ie1, v);
        return;
    }

    if (ic1 == ADVERB_ru && ic2 == ADJ_ru)
    {
        Add(adv_a, ie1, ie2, v);
        Add(a_adv, ie2, ie1, v);
        return;
    }

    if (ic1 == ADJ_ru && ic2 == ADVERB_ru)
    {
        Add(a_adv, ie1, ie2, v);
        Add(adv_a, ie2, ie1, v);
        return;
    }

    if (ic1 == ADVERB_ru && ic2 == VERB_ru)
    {
        Add(adv_v, ie1, ie2, v);
        Add(v_adv, ie2, ie1, v);
        return;
    }

    if (ic1 == VERB_ru && ic2 == ADVERB_ru)
    {
        Add(v_adv, ie1, ie2, v);
        Add(adv_v, ie2, ie1, v);
        return;
    }

    // КОШКА СПИТ - актор и действие
    if (ic1 == NOUN_ru && ic2 == VERB_ru)
    {
        Add(n_v, ie1, ie2, v);
        Add(v_n, ie2, ie1, v);
        return;
    }

    // ВИДИТ СНЫ - глагол и дополнение
    if (ic1 == VERB_ru && ic2 == NOUN_ru)
    {
        Add(v_obj, ie1, ie2, v);
        Add(obj_v, ie2, ie1, v);
        return;
    }


    if (ic1 == PREPOS_ru && ic2 == NOUN_ru)
    {
        Add(n_p, ie2, ie1, v);
        Add(p_n, ie1, ie2, v);
        return;
    }


    return;
}
#endif


#if defined SOL_CAA
void Ngrams::Add(Ngrams::digram_type &table, int ie1, int ie2, float v)
{
    digram_type::iterator i = table.find(ie1);

    if (i == table.end())
    {
        lem::MCollect<std::pair<int/*ientry*/, float> > *arr = new lem::MCollect<std::pair<int/*ientry*/, float> >();
        arr->push_back(std::make_pair(ie2, v));
        table.insert(std::make_pair(ie1, arr));
    }
    else
    {
        i->second->push_back(std::make_pair(ie2, v));
    }

    return;
}
#endif



#if defined SOL_CAA
void Ngrams::FindPreposForNoun(int ie_noun, lem::MCollect<std::pair<int/*ientry*/, float> > & res, int min_freq)
{
    FindLeftWords(db_p_2_n, ie_noun, res, min_freq);

    digram_type::const_iterator p = n_p.find(ie_noun);
    if (p != n_p.end())
    {
        const lem::MCollect<std::pair<int/*ientry*/, float> > * a = p->second;
        std::copy(a->begin(), a->end(), std::back_inserter(res));
    }

    return;
}
#endif

#if defined SOL_CAA
void Ngrams::FindNounsForPrepos(int ie_prepos, lem::MCollect<std::pair<int/*ientry*/, float> > & res, int min_freq)
{
    FindRightWords(db_p_2_n, ie_prepos, res, min_freq);

    digram_type::const_iterator p = p_n.find(ie_prepos);
    if (p != p_n.end())
    {
        const lem::MCollect<std::pair<int/*ientry*/, float> > * a = p->second;
        std::copy(a->begin(), a->end(), std::back_inserter(res));
    }

    return;
}
#endif



#if defined SOL_CAA
void Ngrams::FindObjsForVerb(int ie_verb, lem::MCollect<std::pair<int/*ientry*/, float> > & res, int min_freq)
{
    FindLeftWords(db_obj_2_v, ie_verb, res, min_freq);

    digram_type::const_iterator p = v_obj.find(ie_verb);
    if (p != v_obj.end())
    {
        const lem::MCollect<std::pair<int/*ientry*/, float> > * a = p->second;
        std::copy(a->begin(), a->end(), std::back_inserter(res));
    }

    return;
}
#endif

#if defined SOL_CAA
void Ngrams::FindVerbsForObj(int ie_noun, lem::MCollect<std::pair<int/*ientry*/, float> > & res, int min_freq)
{
    FindRightWords(db_obj_2_v, ie_noun, res, min_freq);

    digram_type::const_iterator p = obj_v.find(ie_noun);
    if (p != obj_v.end())
    {
        const lem::MCollect<std::pair<int/*ientry*/, float> > * a = p->second;
        std::copy(a->begin(), a->end(), std::back_inserter(res));
    }

    return;
}
#endif





#if defined SOL_CAA
// Возвращает полный список монограмм и их частот
int Ngrams::Find1Grams(
    bool lemmatize,
    lem::MCollect<lem::UCString> &word,
    lem::MCollect<int> &iw,
    lem::MCollect<float> &w,
    int min_freq
)
{
    raw &db_x = lemmatize ? db_raw : db_literal;

    if (db.NotNull() && db->Connected() && db_x.has1)
    {
        db->BeginReadTx();

        std::map< UCString, std::pair<int, float> > reslist;

        for (lem::Container::size_type k = 0; k < db_x.segments.size(); ++k)
        {
            FString sgm = db_x.segments[k];
            sgm.re_clear();
            db->Find1Grams(db_x.suffix, sgm, db_x.max_w1, min_freq, reslist);
        }

        db->CommitReadTx();

        for (std::map<UCString, std::pair<int, float> >::const_iterator it = reslist.begin(); it != reslist.end(); it++)
        {
            word.push_back(it->first);
            iw.push_back(it->second.first);
            w.push_back(it->second.second);
        }
    }

    return CastSizeToInt(word.size());
}
#endif



void Ngrams::Dump(Ngrams::cov &pdb, lem::OFormatter &to)
{
    if (db.NotNull() && db->Connected() && pdb.has)
    {
        for (lem::Container::size_type k = 0; k < pdb.segments.size(); k++)
        {
            FString sgm = pdb.segments[k];
            sgm.re_clear();

            db->Dump2Grams_1(pdb.suffix, sgm, to);
        }
    }

    return;
}

void Ngrams::DumpRaw3(lem::OFormatter &to)
{
    DumpRaw3(db_raw, to);
    return;
}

void Ngrams::DumpLiteral3(lem::OFormatter &to)
{
    DumpRaw3(db_literal, to);
    return;
}


void Ngrams::DumpRaw2(lem::OFormatter &to)
{
    DumpRaw2(db_raw, to);
    return;
}

void Ngrams::DumpLiteral2(lem::OFormatter &to)
{
    DumpRaw2(db_literal, to);
    return;
}

void Ngrams::DumpRaw3(Ngrams::raw &pdb, lem::OFormatter &to)
{
    if (db.NotNull() && db->Connected() && pdb.has3)
    {
        for (lem::Container::size_type k = 0; k < pdb.segments.size(); k++)
        {
            FString sgm = pdb.segments[k];
            sgm.re_clear();
            db->Dump3Grams(pdb.suffix, sgm, to);
        }
    }

    return;
}



void Ngrams::DumpRaw2(Ngrams::raw &pdb, lem::OFormatter &to)
{
    if (db.NotNull() && db->Connected() && pdb.has2)
    {
        for (lem::Container::size_type k = 0; k < pdb.segments.size(); k++)
        {
            FString sgm = pdb.segments[k];
            sgm.re_clear();
            db->Dump2Grams(pdb.suffix, sgm, to);
        }
    }

    return;
}




int Ngrams::FindInWordTable(const lem::UCString &_word, bool lemmatized)
{
#if defined SOL_CAA
    if (db.NotNull() && db->Connected())
    {
        UCString word(_word);

        raw &db_x = lemmatized ? db_raw : db_literal;

        if (lemmatized)
            Normalize(word);
        else
            word.to_upper();

        for (lem::Container::size_type k = 0; k < db_x.segments.size(); k++)
        {
            FString sgm = db_x.segments[k];
            sgm.re_clear();
            int id = db->FindWord(
                lemmatized ? db_raw.suffix.c_str() : db_literal.suffix.c_str(),
                sgm.c_str(),
                word
            );

            if (id != -1)
                return id;
        }
    }
#endif

    return -1;
}

#if defined SOL_CAA
bool Ngrams::FindRawNGrams(const lem::UCString &left, float &w, int &iw)
{
    return FindRawNGrams(db_raw, left, w, iw);
}

int Ngrams::FindRawNGramsID(const lem::UCString &left, float &w, int &iw)
{
    return FindRawNGramsID(db_raw, left, w, iw);
}
#endif


#if defined SOL_CAA
bool Ngrams::FindRawNGrams(const lem::UCString &left, const lem::UCString &right, float &w, int &iw)
{
    return FindRawNGrams(db_raw, left, right, w, iw);
}

int Ngrams::FindRawNGramsID(const lem::UCString &left, const lem::UCString &right, float &w, int &iw)
{
    return FindRawNGramsID(db_raw, left, right, w, iw);
}
#endif


#if defined SOL_CAA
bool Ngrams::FindRawNGrams(
    const lem::UCString &_w1,
    const lem::UCString &_w2,
    const lem::UCString &_w3,
    float &w,
    int &iw
)
{
    return FindRawNGrams(db_raw, _w1, _w2, _w3, w, iw);
}

int Ngrams::FindRawNGramsID(
    const lem::UCString &_w1,
    const lem::UCString &_w2,
    const lem::UCString &_w3,
    float &w,
    int &iw
)
{
    return FindRawNGramsID(db_raw, _w1, _w2, _w3, w, iw);
}
#endif


#if defined SOL_CAA
bool Ngrams::FindRawNGrams(
    const lem::UCString &_w1,
    const lem::UCString &_w2,
    const lem::UCString &_w3,
    const lem::UCString &_w4,
    float &w,
    int &iw
)
{
    return FindRawNGrams(db_raw, _w1, _w2, _w3, _w4, w, iw);
}

int Ngrams::FindRawNGramsID(
    const lem::UCString &_w1,
    const lem::UCString &_w2,
    const lem::UCString &_w3,
    const lem::UCString &_w4,
    float &w,
    int &iw
)
{
    return FindRawNGramsID(db_raw, _w1, _w2, _w3, _w4, w, iw);
}
#endif

#if defined SOL_CAA
bool Ngrams::FindRawNGrams(
    const lem::UCString &_w1,
    const lem::UCString &_w2,
    const lem::UCString &_w3,
    const lem::UCString &_w4,
    const lem::UCString &_w5,
    float &w,
    int &iw
)
{
    return FindRawNGrams(db_raw, _w1, _w2, _w3, _w4, _w5, w, iw);
}

int Ngrams::FindRawNGramsID(
    const lem::UCString &_w1,
    const lem::UCString &_w2,
    const lem::UCString &_w3,
    const lem::UCString &_w4,
    const lem::UCString &_w5,
    float &w,
    int &iw
)
{
    return FindRawNGramsID(db_raw, _w1, _w2, _w3, _w4, _w5, w, iw);
}
#endif

#if defined SOL_CAA
void Ngrams::FindRawNGrams(const lem::UCString &left, lem::MCollect<lem::UCString> &right, lem::MCollect<float> &w, int min_freq)
{
    FindRawNGrams(db_raw, left, right, w, min_freq);
}
#endif


#if defined SOL_CAA
void Ngrams::FindRawNGrams(lem::MCollect<lem::UCString> &left, const lem::UCString &right, lem::MCollect<float> &w, int min_freq)
{
    FindRawNGrams(db_raw, left, right, w, min_freq);
}
#endif

#if defined SOL_CAA
void Ngrams::FindRawNGrams(const lem::UCString &left, lem::MCollect<lem::UCString> &right1, lem::MCollect<lem::UCString> &right2, lem::MCollect<float> &w, int min_freq)
{
    FindRawNGrams(db_raw, left, right1, right2, w, min_freq);
}
#endif

#if defined SOL_CAA
void Ngrams::FindRawNGrams(lem::MCollect<lem::UCString> &left1, lem::MCollect<lem::UCString> &left2, const lem::UCString &right, lem::MCollect<float> &w, int min_freq)
{
    FindRawNGrams(db_raw, left1, left2, right, w, min_freq);
}
#endif

#if defined SOL_CAA
void Ngrams::FindRawNGrams(lem::MCollect<lem::UCString> &left, const lem::UCString &center, lem::MCollect<lem::UCString> &right, lem::MCollect<float> &w, int min_freq)
{
    FindRawNGrams(db_raw, left, center, right, w, min_freq);
}
#endif

#if defined SOL_CAA
bool Ngrams::FindLiteralNGrams(const lem::UCString &left, float &w, int &iw)
{
    return FindRawNGrams(db_literal, left, w, iw);
}
#endif

#if defined SOL_CAA
bool Ngrams::FindLiteralNGrams(const lem::UCString &left, const lem::UCString &right, float &w, int &iw)
{
    return FindRawNGrams(db_literal, left, right, w, iw);
}
#endif


#if defined SOL_CAA
bool Ngrams::FindLiteralNGrams(
    const lem::UCString &_w1,
    const lem::UCString &_w2,
    const lem::UCString &_w3,
    float &w,
    int &iw
)
{
    return FindRawNGrams(db_literal, _w1, _w2, _w3, w, iw);
}
#endif

#if defined SOL_CAA
bool Ngrams::FindLiteralNGrams(
    const lem::UCString &_w1,
    const lem::UCString &_w2,
    const lem::UCString &_w3,
    const lem::UCString &_w4,
    float &w,
    int &iw
)
{
    return FindRawNGrams(db_literal, _w1, _w2, _w3, _w4, w, iw);
}
#endif

#if defined SOL_CAA
bool Ngrams::FindLiteralNGrams(
    const lem::UCString &_w1,
    const lem::UCString &_w2,
    const lem::UCString &_w3,
    const lem::UCString &_w4,
    const lem::UCString &_w5,
    float &w,
    int &iw
)
{
    return FindRawNGrams(db_literal, _w1, _w2, _w3, _w4, _w5, w, iw);
}
#endif

#if defined SOL_CAA
void Ngrams::FindLiteralNGrams(const lem::UCString &left, lem::MCollect<lem::UCString> &right, lem::MCollect<float> &w, int min_freq)
{
    FindRawNGrams(db_literal, left, right, w, min_freq);
}
#endif

#if defined SOL_CAA
void Ngrams::FindLiteralNGrams(lem::MCollect<lem::UCString> &left, const lem::UCString &right, lem::MCollect<float> &w, int min_freq)
{
    FindRawNGrams(db_literal, left, right, w, min_freq);
}
#endif

#if defined SOL_CAA
void Ngrams::FindLiteralNGrams(const lem::UCString &left, lem::MCollect<lem::UCString> &right1, lem::MCollect<lem::UCString> &right2, lem::MCollect<float> &w, int min_freq)
{
    FindRawNGrams(db_literal, left, right1, right2, w, min_freq);
}
#endif

#if defined SOL_CAA
void Ngrams::FindLiteralNGrams(lem::MCollect<lem::UCString> &left1, lem::MCollect<lem::UCString> &left2, const lem::UCString &right, lem::MCollect<float> &w, int min_freq)
{
    FindRawNGrams(db_literal, left1, left2, right, w, min_freq);
}
#endif

#if defined SOL_CAA
void Ngrams::FindLiteralNGrams(lem::MCollect<lem::UCString> &left, const lem::UCString &center, lem::MCollect<lem::UCString> &right, lem::MCollect<float> &w, int min_freq)
{
    FindRawNGrams(db_literal, left, center, right, w, min_freq);
}
#endif



lem::int64_t Ngrams::PreloadCachesFromFiles()
{
    lem::int64_t res = 0;
    res += db_raw.PreloadCachesFromFiles(folder);
    res += db_literal.PreloadCachesFromFiles(folder);
    res += db_n_2_n.PreloadCachesFromFiles(folder);
    res += db_a_2_n.PreloadCachesFromFiles(folder);
    res += db_n_2_v.PreloadCachesFromFiles(folder);
    res += db_adv_2_v.PreloadCachesFromFiles(folder);
    res += db_adv_2_a.PreloadCachesFromFiles(folder);
    res += db_p_2_n.PreloadCachesFromFiles(folder);
    res += db_obj_2_v.PreloadCachesFromFiles(folder);
    return res;
}


#if defined SOL_CAA
void Ngrams::Normalize(lem::UCString &word) const
{
    if (&dict->GetLemmatizer() != nullptr)
    {
        dict->GetLemmatizer().Lemmatize(word, word);
    }
    else
    {
        dict->GetLexAuto().GetBaseForm(word, true);
    }

    return;
}
#endif


#if defined SOL_CAA
// ***********************************************************
// возвращает максимальный порядок имеющихся в базе N-грамм.
// ***********************************************************
int Ngrams::GetRawOrder() const
{
    if (CountRaw5() > 0)
        return 5;

    if (CountRaw4() > 0)
        return 4;

    if (CountRaw3() > 0)
        return 3;

    if (CountRaw2() > 0)
        return 2;

    if (CountRaw1() > 0)
        return 1;

    return 0;
}
#endif

#if defined SOL_CAA
// ***********************************************************
// возвращает максимальный порядок имеющихся в базе N-грамм.
// ***********************************************************
int Ngrams::GetLiteralOrder() const
{
    if (CountLiteral5() > 0)
        return 5;

    if (CountLiteral4() > 0)
        return 4;

    if (CountLiteral3() > 0)
        return 3;

    if (CountLiteral2() > 0)
        return 2;

    if (CountLiteral1() > 0)
        return 1;

    return 0;
}
#endif


#if defined SOL_CAA
bool Ngrams::FindNGrams(
    bool lemmatize,
    const lem::UCString &left,
    float &w,
    int &iw
)
{
    return lemmatize ?
        FindRawNGrams(left, w, iw) :
        FindLiteralNGrams(left, w, iw);
}
#endif

#if defined SOL_CAA
bool Ngrams::FindNGrams(
    bool lemmatize,
    const lem::UCString &left,
    const lem::UCString &right,
    float &w,
    int &iw
)
{
    return lemmatize ?
        FindRawNGrams(left, right, w, iw) :
        FindLiteralNGrams(left, right, w, iw);
}
#endif


#if defined SOL_CAA
bool Ngrams::FindNGrams(
    bool lemmatize,
    const lem::UCString &_w1,
    const lem::UCString &_w2,
    const lem::UCString &_w3,
    float &w,
    int &iw
)
{
    return lemmatize ?
        FindRawNGrams(_w1, _w2, _w3, w, iw) :
        FindLiteralNGrams(_w1, _w2, _w3, w, iw);
}
#endif


#if defined SOL_CAA
bool Ngrams::FindNGrams(
    bool lemmatize,
    const lem::UCString &_w1,
    const lem::UCString &_w2,
    const lem::UCString &_w3,
    const lem::UCString &_w4,
    float &w,
    int &iw
)
{
    return lemmatize ?
        FindRawNGrams(_w1, _w2, _w3, _w4, w, iw) :
        FindLiteralNGrams(_w1, _w2, _w3, _w4, w, iw);
}
#endif


#if defined SOL_CAA
bool Ngrams::FindNGrams(
    bool lemmatize,
    const lem::UCString &_w1,
    const lem::UCString &_w2,
    const lem::UCString &_w3,
    const lem::UCString &_w4,
    const lem::UCString &_w5,
    float &w,
    int &iw
)
{
    return lemmatize ?
        FindRawNGrams(_w1, _w2, _w3, _w4, _w5, w, iw) :
        FindLiteralNGrams(_w1, _w2, _w3, _w4, _w5, w, iw);
}
#endif



#if defined SOL_CAA
// Обход списка Nграмм заданного порядка
// sorting=0 без сортировки
//        =1 в порядке возрастания id
//        =2 в порядке возрастания w
//        =3 в порядке убывания w
void Ngrams::ForEachRaw(NGramHandler *handler, int order, bool lemmatized, int sorting)
{
    if (db.NotNull() && db->Connected())
    {
        if (order == 1)      ForEachRaw1(lemmatized, handler, sorting);
        else if (order == 2) ForEachRaw2(lemmatized, handler, sorting);
        else if (order == 3) ForEachRaw3(lemmatized, handler, sorting);
        else if (order == 4) ForEachRaw4(lemmatized, handler, sorting);
        else if (order == 5) ForEachRaw5(lemmatized, handler, sorting);
    }

    return;
}
#endif



#if defined SOL_CAA
// Итератация по всем монограммам
void Ngrams::ForEachRaw1(bool lemmatized, NGramHandler *handler, int sorting_type)
{
    raw &db_x = lemmatized ? db_raw : db_literal;

    if (db.NotNull() && db->Connected() && db_x.has1)
    {
        db->BeginReadTx();

        for (lem::Container::size_type k = 0; k < db_x.segments.size(); ++k)
        {
            FString sgm = db_x.segments[k];
            sgm.re_clear();
            db->ForEachRaw1(*this, db_x.suffix, sgm, handler, sorting_type);
        }

        db->CommitReadTx();
    }

    return;
}
#endif



#if defined SOL_CAA
// Итератация по всем 2-граммам
void Ngrams::ForEachRaw2(bool lemmatized, NGramHandler *handler, int sorting_type)
{
    raw &db_x = lemmatized ? db_raw : db_literal;

    if (db.NotNull() && db->Connected() && db_x.has2)
    {
        db->BeginReadTx();

        for (lem::Container::size_type k = 0; k < db_x.segments.size(); ++k)
        {
            FString sgm = db_x.segments[k];
            sgm.re_clear();
            db->ForEachRaw2(*this, db_x.suffix, sgm, handler, sorting_type);
        }

        db->CommitReadTx();
    }

    for (lem::Container::size_type k = 0; k < db_x.cache2.size(); ++k)
    {
        Cache2 * c2 = db_x.cache2[k];
        FString sgm = db_x.segments[k];
        sgm.re_clear();
        c2->ForEach(this, db_x.suffix, sgm, &db_x, handler);
    }

    return;
}
#endif



#if defined SOL_CAA
// Итератация по всем 3-граммам
void Ngrams::ForEachRaw3(bool lemmatized, NGramHandler *handler, int sorting_type)
{
    raw &db_x = lemmatized ? db_raw : db_literal;

    if (db.NotNull() && db->Connected() && db_x.has3)
    {
        db->BeginReadTx();

        for (lem::Container::size_type k = 0; k < db_x.segments.size(); ++k)
        {
            FString sgm = db_x.segments[k];
            sgm.re_clear();
            db->ForEachRaw3(*this, db_x.suffix, sgm, handler, sorting_type);
        }

        db->CommitReadTx();
    }

    for (lem::Container::size_type k = 0; k < db_x.cache3.size(); ++k)
    {
        Cache3 * c3 = db_x.cache3[k];
        FString sgm = db_x.segments[k];
        sgm.re_clear();
        c3->ForEach(this, db_x.suffix, sgm, &db_x, handler);
    }

    return;
}
#endif


#if defined SOL_CAA
// Итератация по всем 4-граммам
void Ngrams::ForEachRaw4(bool lemmatized, NGramHandler *handler, int sorting_type)
{
    raw &db_x = lemmatized ? db_raw : db_literal;

    if (db.NotNull() && db->Connected() && db_x.has4)
    {
        db->BeginReadTx();

        for (lem::Container::size_type k = 0; k < db_x.segments.size(); ++k)
        {
            FString sgm = db_x.segments[k];
            sgm.re_clear();
            db->ForEachRaw4(*this, db_x.suffix, sgm, handler, sorting_type);
        }

        db->CommitReadTx();
    }

    for (lem::Container::size_type k = 0; k < db_x.cache4.size(); ++k)
    {
        FString sgm = db_x.segments[k];
        sgm.re_clear();
        Cache4 * c4 = db_x.cache4[k];
        c4->ForEach(this, db_x.suffix, sgm, &db_x, handler);
    }

    return;
}
#endif


#if defined SOL_CAA
// Итератация по всем 5-граммам
void Ngrams::ForEachRaw5(bool lemmatized, NGramHandler *handler, int sorting_type)
{
    raw &db_x = lemmatized ? db_raw : db_literal;

    if (db.NotNull() && db->Connected() && db_x.has5)
    {
        db->BeginReadTx();

        for (lem::Container::size_type k = 0; k < db_x.segments.size(); ++k)
        {
            FString sgm = db_x.segments[k];
            sgm.re_clear();
            db->ForEachRaw5(*this, db_x.suffix, sgm, handler, sorting_type);
        }

        db->CommitReadTx();
    }

    for (lem::Container::size_type k = 0; k < db_x.cache5.size(); ++k)
    {
        Cache5 * c5 = db_x.cache5[k];
        FString sgm = db_x.segments[k];
        sgm.re_clear();
        c5->ForEach(this, db_x.suffix, sgm, &db_x, handler);
    }

    return;
}
#endif

#if defined SOL_CAA
// Получение суммы частот для всех N-грамм заданного типа
lem::int64_t Ngrams::SumFreq(int order, bool lemmatized)
{
    lem::int64_t res = 0;

    raw &pdb = lemmatized ? db_raw : db_literal;

    if (db.NotNull() && db->Connected())
    {
        bool ok = true;

        if (order == 1 && !pdb.has1)
            ok = false;
        else if (order == 2 && !pdb.has2)
            ok = false;
        else if (order == 3 && !pdb.has3)
            ok = false;
        else if (order == 4 && !pdb.has4)
            ok = false;
        else if (order == 5 && !pdb.has5)
            ok = false;

        if (ok)
        {
            db->BeginReadTx();

            for (lem::Container::size_type k = 0; k < pdb.segments.size(); ++k)
            {
                lem::FString sgm = pdb.segments[k];
                sgm.re_clear();

                lem::uint64_t f = db->SumFrequency(order, pdb.suffix, sgm);
                res += f;
            }

            db->CommitReadTx();
        }
    }

    return res;
}
#endif

void Ngrams::CreateTable_Words(const lem::FString &suffix)
{
    db->CreateTable_Words(suffix);
    return;
}

void Ngrams::CreateTable_NGrams1(const lem::FString &suffix)
{
    db->CreateTable_NGrams1(suffix);
    return;
}

void Ngrams::CreateTable_NGrams2(const lem::FString &suffix)
{
    db->CreateTable_NGrams2(suffix);
    return;
}

void Ngrams::CreateTable_NGrams3(const lem::FString &suffix)
{
    db->CreateTable_NGrams3(suffix);
    return;
}

void Ngrams::CreateTable_NGrams4(const lem::FString &suffix)
{
    db->CreateTable_NGrams4(suffix);
    return;
}

void Ngrams::CreateTable_NGrams5(const lem::FString &suffix)
{
    db->CreateTable_NGrams5(suffix);
    return;
}

int Ngrams::MaxBulkInsert()
{
    return db->MaxBulkInsert();
}


lem::FString Ngrams::StartBulkInsert(const lem::FString &suffix, int order)
{
    return db->StartBulkInsert(suffix, order);
}


lem::FString Ngrams::AppendBulkInsert(
    const lem::FString &suffix,
    int counter,
    int id,
    int id_word1,
    int w
)
{
    return db->AppendBulkInsert(suffix, counter, id, id_word1, w);
}


lem::FString Ngrams::AppendBulkInsert(
    const lem::FString &suffix,
    int counter,
    int id,
    int id_word1,
    int id_word2,
    int w
)
{
    return db->AppendBulkInsert(suffix, counter, id, id_word1, id_word2, w);
}


lem::FString Ngrams::AppendBulkInsert(
    const lem::FString &suffix,
    int counter,
    int id,
    int id_word1,
    int id_word2,
    int id_word3,
    int w
)
{
    return db->AppendBulkInsert(suffix, counter, id, id_word1, id_word2, id_word3, w);
}


lem::FString Ngrams::AppendBulkInsert(
    const lem::FString &suffix,
    int counter,
    int id,
    int id_word1,
    int id_word2,
    int id_word3,
    int id_word4,
    int w
)
{
    return db->AppendBulkInsert(suffix, counter, id, id_word1, id_word2, id_word3, id_word4, w);
}


lem::FString Ngrams::AppendBulkInsert(
    const lem::FString &suffix,
    int counter,
    int id,
    int id_word1,
    int id_word2,
    int id_word3,
    int id_word4,
    int id_word5,
    int w
)
{
    return db->AppendBulkInsert(suffix, counter, id, id_word1, id_word2, id_word3, id_word4, id_word5, w);
}


void Ngrams::UpdateNGrams(
    const lem::FString &suffix,
    int order,
    const lem::MCollect< std::pair<int, int> > & list
)
{
    db->UpdateNGrams(suffix, order, list);
}

std::pair<int/*id*/, int/*w*/> Ngrams::Find1Gram(const lem::FString &suffix, int id_word)
{
    return db->Find1Gram(suffix, id_word);
}

std::pair<int/*id*/, int/*w*/> Ngrams::Find2Gram(const lem::FString &suffix, int id_word1, int id_word2)
{
    return db->Find2Gram(suffix, id_word1, id_word2);
}

std::pair<int/*id*/, int/*w*/> Ngrams::Find3Gram(const lem::FString &suffix, int id_word1, int id_word2, int id_word3)
{
    return db->Find3Gram(suffix, id_word1, id_word2, id_word3);
}

std::pair<int/*id*/, int/*w*/> Ngrams::Find4Gram(const lem::FString &suffix, int id_word1, int id_word2, int id_word3, int id_word4)
{
    return db->Find4Gram(suffix, id_word1, id_word2, id_word3, id_word4);
}

std::pair<int/*id*/, int/*w*/> Ngrams::Find5Gram(const lem::FString &suffix, int id_word1, int id_word2, int id_word3, int id_word4, int id_word5)
{
    return db->Find5Gram(suffix, id_word1, id_word2, id_word3, id_word4, id_word5);
}

void Ngrams::FinishBulkInsert(const lem::FString &sql)
{
    db->FinishBulkInsert(sql);
    return;
}

void Ngrams::CreateIndeces1(const lem::FString &suffix, int order)
{
    db->CreateIndeces1(suffix, order);
    return;
}

void Ngrams::CreateIndeces2(const lem::FString &suffix, int order)
{
    db->CreateIndeces2(suffix, order);
    return;
}

void Ngrams::CreateIndecesWord2(const lem::FString &suffix)
{
    db->CreateIndecesWord2(suffix);
    return;
}


int Ngrams::FindWord(
    const lem::FString &suffix,
    const lem::UCString &word
)
{
    return db->FindWord(suffix, word);
}

void Ngrams::InsertWord(
    const lem::FString &suffix,
    int id_word,
    const lem::UCString &word
)
{
    return db->InsertWord(suffix, id_word, word);
}


void Ngrams::UpdateStatistics(const lem::FString &suffix, int order)
{
    return db->UpdateStatistics(suffix, order);
}

void Ngrams::EraseFreq1(const lem::FString &suffix, int order)
{
    return db->EraseFreq1(suffix, order);
}

void Ngrams::CreateTable_Segments()
{
    return db->CreateTable_Segments();
}


lem::UCString Ngrams::GetWord(const lem::FString &suffix, const lem::FString &segment, int id_word)
{
    return db->GetWord(suffix, segment, id_word);
}

#endif
