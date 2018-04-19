#if defined SOL_MYSQL_DICTIONARY_STORAGE

#include <lem/oformatter.h>
#include <lem/solarix/lexem.h>
#include <lem/solarix/StorageConnection_MySQL.h>
#include <lem/solarix/WordFormEnumerator_MySQL.h>
#include <lem/solarix/WordEntryEnumerator_MySQL.h>
#include <lem/solarix/LexemeEnumerator_MySQL.h>
#include <lem/solarix/LexiconStorage_MySQL.h>
#include <lem/solarix/LS_ResultSet_MySQL.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/MySQLCnx.h>
#include <lem/solarix/some_strings.h>
#include <lem/solarix/ExactWordEntryLocator.h>
#include <lem/solarix/AuxFormTypes.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/WordEntries_MySQL.h>

#if defined SOL_LOADTXT
#include <lem/solarix/dictionary.h>
#include <lem/solarix/la_autom.h>
#endif

using namespace Solarix;

WordEntries_MySQL::WordEntries_MySQL(
    SynGram &_sg,
    StorageConnection_MySQL *_cnx,
    const Dictionary_Config &_cfg
) : WordEntries_SQL(_sg, _cfg), cnx(_cnx)
{
    return;
}

WordEntries_MySQL::~WordEntries_MySQL()
{
    cnx->Release();
    return;
}


int WordEntries_MySQL::GetMaxMultilexemLen_Impl()
{
    MySQLCnx *c = cnx->GetDb();

#if defined LEM_THREADS
    lem::Process::CritSecLocker guard(&c->cs);
#endif

    std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

    int len = lem::mysql_select_int(c->mysql, "SELECT Coalesce(max(n_lexem),0) FROM multilexem");

    return len;
}





int WordEntries_MySQL::CountEntries(int id_class, int id_language)
{
    lem::MemFormatter mem;
    if (
        (id_class == UNKNOWN || id_class == ANY_STATE) &&
        (id_language == UNKNOWN || id_language == ANY_STATE)
        )
    {
        mem.printf("SELECT count(*) FROM sg_entry");
    }
    else if (id_class != UNKNOWN && id_class != ANY_STATE)
    {
        mem.printf("SELECT count(*) FROM sg_entry WHERE id_class=%d", id_class);
    }
    else
    {
        mem.printf("SELECT count(E.id) FROM sg_entry E, sg_class C"
            " WHERE C.id_lang=%d AND E.id_class=C.id", id_language);
    }

    lem::FString Select(lem::to_utf8(mem.string()));

    MySQLCnx *c = cnx->GetDb();
#if defined LEM_THREADS
    lem::Process::CritSecLocker guard(&c->cs);
#endif

    std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

    return lem::mysql_select_int(c->mysql, Select.c_str());
}


int WordEntries_MySQL::CountForms(int id_language)
{
    lem::MemFormatter mem;
    if (id_language == UNKNOWN || id_language == ANY_STATE)
    {
        mem.printf("SELECT count(*) FROM sg_form");
    }
    else
    {
        mem.printf("SELECT count(F.id) FROM sg_class C, sg_entry E, sg_form F"
            " WHERE C.id_lang=%d AND E.id_class=C.id AND E.id_entry=E.id", id_language);
    }

    MySQLCnx *c = cnx->GetDb();
#if defined LEM_THREADS
    lem::Process::CritSecLocker guard(&c->cs);
#endif

    std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

    lem::FString Select(lem::to_utf8(mem.string()));
    return lem::mysql_select_int(c->mysql, Select.c_str());
}


bool WordEntries_MySQL::IsWordForm(const Solarix::Lexem &lex)
{
    lem::UFString s(lex.c_str());
    lem::mysql_escape(s);

    lem::MemFormatter mem;
    mem.printf("SELECT id FROM sg_lexem WHERE name='%us'", s.c_str());

    MySQLCnx *c = cnx->GetDb();
#if defined LEM_THREADS
    lem::Process::CritSecLocker guard(&c->cs);
#endif

    lem::FString Select(lem::to_utf8(mem.string()));
    bool res = lem::mysql_select_int(c->mysql, Select.c_str()) != -1;

    return res;
}


bool WordEntries_MySQL::IsMultilexemHead_Impl(const lem::UCString &word, MultiLexemInfo &info)
{
    lem::UFString s(word.c_str());
    lem::mysql_escape(s);

    lem::MemFormatter mem;
    mem.printf("SELECT Coalesce(max(n_lexem),0) FROM multilexem WHERE headword='%us'",
        s.c_str());

    lem::FString Select(lem::to_utf8(mem.string()));

    bool ok = false;

    MySQLCnx *c = cnx->GetDb();
#if defined LEM_THREADS
    lem::Process::CritSecLocker guard2(&c->cs);
#endif

    std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

    int rc = mysql_query(c->mysql, Select.c_str());
    if (rc == 0)
    {
        MYSQL_RES *res = mysql_store_result(c->mysql);
        if (res != nullptr)
        {
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row)
            {
                info.maxlen = lem::mysql_column_int(row, 0);
                ok = info.maxlen > 1;
            }

            mysql_free_result(res);
        }
    }

    return ok;
}


bool WordEntries_MySQL::IsMultilexemForm_Impl(const Solarix::Lexem &lex)
{
    lem::MemFormatter mem;
    lem::UFString s(lex.c_str());
    lem::mysql_escape(s);

    mem.printf("SELECT id FROM multilexem WHERE txt='%us' LIMIT 1", s.c_str());

    lem::FString Select(lem::to_utf8(mem.string()));

    bool ok = false;

    MySQLCnx *c = cnx->GetDb();
#if defined LEM_THREADS
    lem::Process::CritSecLocker guard2(&c->cs);
#endif

    std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

    int rc = mysql_query(c->mysql, Select.c_str());
    if (rc == 0)
    {
        MYSQL_RES *res = mysql_store_result(c->mysql);
        if (res != nullptr)
        {
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row)
            {
                ok = true;
            }

            mysql_free_result(res);
        }
    }
    else
    {
        cnx->Error(Select);
    }

    return ok;
}





WordEntryEnumerator* WordEntries_MySQL::ListEntries()
{
    lem::FString Select("SELECT id FROM sg_entry");

    MySQLCnx *c = cnx->GetDb();
#if defined LEM_THREADS
    c->cs.Enter();
#endif

    std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

    int rc = mysql_query(c->mysql, Select.c_str());
    if (rc == 0)
    {
        MYSQL_RES *res = mysql_store_result(c->mysql);
        if (res != nullptr)
        {
            return new WordEntryEnumerator_MySQL(new LS_ResultSet_MySQL(c, res, read_tx.release()), this);
        }
    }

#if defined LEM_THREADS
    lem::Process::CritSecLocker guard2(&c->cs);
    c->cs.Leave();
#endif

    cnx->Error(Select);

    return nullptr;
}

/*
WordEntryEnumerator* WordEntries_MySQL::ListEntries( const lem::triple<wchar_t,wchar_t,wchar_t> & prefix3 )
{
 lem::MemFormatter mem;

 if( prefix3.second==0 )
  mem.printf( "SELECT distinct F.id_entry FROM sg_form F WHERE F.name='%uc'", prefix3.first );
 else if( prefix3.third==0 )
  mem.printf( "SELECT distinct F.id_entry FROM sg_form F WHERE F.name='%uc%uc'", prefix3.first, prefix3.second );
 else
  mem.printf( "SELECT distinct F.id_entry FROM sg_form F WHERE F.name LIKE '%uc%uc%uc%%'", prefix3.first, prefix3.second, prefix3.third );

 lem::FString Select( lem::to_utf8(mem.string()) );

 MySQLCnx *c = cnx->GetDb();
 #if defined LEM_THREADS
 c->cs.Enter();
 #endif

 std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

 int rc = mysql_query( c->mysql, Select.c_str() );
 if( rc==0 )
  {
   MYSQL_RES *res = mysql_store_result(c->mysql);
   if( res!=nullptr )
    {
     return new WordEntryEnumerator_MySQL( new LS_ResultSet_MySQL(c,res,read_tx.release()), this );
    }
  }

 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard2(&c->cs);
 c->cs.Leave();
 #endif

 cnx->Error(Select);
 return nullptr;
}
*/


WordEntryEnumerator* WordEntries_MySQL::ListEntries(const lem::UCString &name, int id_class)
{
    lem::MemFormatter mem;

    lem::UFString s(name.c_str());
    lem::mysql_escape(s);

    if (id_class == UNKNOWN || id_class == ANY_STATE)
        mem.printf("SELECT id FROM sg_entry WHERE name='%us'", s.c_str());
    else
        mem.printf("SELECT id FROM sg_entry WHERE name='%us' AND id_class=%d", s.c_str(), id_class);

    lem::FString Select(lem::to_utf8(mem.string()));

    MySQLCnx *c = cnx->GetDb();
#if defined LEM_THREADS
    c->cs.Enter();
#endif

    std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

    int rc = mysql_query(c->mysql, Select.c_str());
    if (rc == 0)
    {
        MYSQL_RES *res = mysql_store_result(c->mysql);
        if (res != nullptr)
        {
            return new WordEntryEnumerator_MySQL(new LS_ResultSet_MySQL(c, res, read_tx.release()), this);
        }
    }

#if defined LEM_THREADS
    lem::Process::CritSecLocker guard2(&c->cs);
    c->cs.Leave();
#endif

    cnx->Error(Select);
    return nullptr;
}


int WordEntries_MySQL::FindEntry_Impl(const lem::UCString &word_name, int id_class)
{
    lem::MemFormatter mem;

    lem::UFString s(word_name.c_str());
    lem::mysql_escape(s);

    if (id_class == UNKNOWN || id_class == ANY_STATE)
        mem.printf("SELECT id FROM sg_entry WHERE uname='%us'", s.c_str());
    else
        mem.printf("SELECT id FROM sg_entry WHERE uname='%us' AND id_class=%d", s.c_str(), id_class);

    lem::FString Select(lem::to_utf8(mem.string()));

    int ekey = UNKNOWN;

    MySQLCnx *c = cnx->GetDb();
#if defined LEM_THREADS
    lem::Process::CritSecLocker guard2(&c->cs);
#endif

    std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

    int rc = mysql_query(c->mysql, Select.c_str());
    if (rc == 0)
    {
        MYSQL_RES *res = mysql_store_result(c->mysql);
        if (res != nullptr)
        {
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row)
            {
                ekey = lem::mysql_column_int(row, 0);
            }

            mysql_free_result(res);
        }
    }
    else
    {
        cnx->Error(Select);
    }

    return ekey;
}




Word_Coord WordEntries_MySQL::FindWordForm(const lem::UCString& name)
{
    lem::MemFormatter mem;

    lem::UFString s(name.c_str());
    lem::mysql_escape(s);

    mem.printf("SELECT F.id_entry, F.iform"
        " FROM sg_lexem L, sg_form F"
        " WHERE L.name='%us' AND F.id_lexem=L.id LIMIT 1", s.c_str());

    lem::FString Select(lem::to_utf8(mem.string()));

    Word_Coord ret(UNKNOWN, UNKNOWN);

    MySQLCnx *c = cnx->GetDb();
#if defined LEM_THREADS
    lem::Process::CritSecLocker guard(&c->cs);
#endif

    std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

    int rc = mysql_query(c->mysql, Select.c_str());
    if (rc == 0)
    {
        MYSQL_RES *res = mysql_store_result(c->mysql);
        if (res != nullptr)
        {
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row)
            {
                const int id_entry = lem::mysql_column_int(row, 0);
                const int iform = lem::mysql_column_int(row, 1);
                ret = Word_Coord(id_entry, iform);
            }

            mysql_free_result(res);
        }
    }
    else
    {
        cnx->Error(Select);
    }

    return ret;
}


WordFormEnumerator* WordEntries_MySQL::ListWordForms(const lem::UCString &form, bool allow_nonterminals)
{
    lem::MemFormatter mem;

    lem::UFString s(form.c_str());
    lem::mysql_escape(s);

    if (allow_nonterminals)
        mem.printf("SELECT F.id_entry, F.iform, L.name"
            " FROM sg_lexem L, sg_form F"
            " WHERE L.name='%us' AND F.id_lexem=L.id", s.c_str());
    else
        mem.printf("SELECT F.id_entry, F.iform, L.name"
            " FROM sg_lexem L, sg_form F, sg_entry E"
            " WHERE L.name='%us' AND F.id_lexem=L.id AND E.id=F.id_entry AND E.flags in (0,2)", s.c_str());

    lem::FString Select(lem::to_utf8(mem.string()));

    MySQLCnx *c = cnx->GetDb();
#if defined LEM_THREADS
    c->cs.Enter();
#endif

    std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

    int rc = mysql_query(c->mysql, Select.c_str());
    if (rc == 0)
    {
        MYSQL_RES *res = mysql_store_result(c->mysql);
        if (res != nullptr)
        {
            return new WordFormEnumerator_MySQL(new LS_ResultSet_MySQL(c, res, read_tx.release()), this);
        }
    }

#if defined LEM_THREADS
    lem::Process::CritSecLocker guard2(&c->cs);
    c->cs.Leave();
#endif

    cnx->Error(Select);
    return nullptr;
}


WordFormEnumerator* WordEntries_MySQL::ListWordForms(const lem::MCollect<lem::UCString> &forms)
{
    lem::MemFormatter mem;

    if (forms.size() == 1)
    {
        lem::UFString s(forms.front().c_str());
        lem::mysql_escape(s);

        mem.printf("SELECT F.id_entry, F.iform, L.name"
            " FROM sg_lexem L, sg_form F"
            " WHERE L.name='%us' AND F.id_lexem=L.id", s.c_str());
    }
    else
    {
        lem::UFString str;

        for (lem::Container::size_type i = 0; i < forms.size(); ++i)
        {
            if (!str.empty())
                str += L", ";

            str += L'\'';
            str += forms[i].c_str();
            str += L'\'';
        }

        mem.printf("SELECT F.id_entry, F.iform, L.name"
            " FROM sg_lexem L, sg_form F"
            " WHERE L.name in ( %us ) AND F.id_lexem=L.id", str.c_str());
    }

    lem::FString Select(lem::to_utf8(mem.string()));

    MySQLCnx *c = cnx->GetDb();
#if defined LEM_THREADS
    c->cs.Enter();
#endif

    std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

    int rc = mysql_query(c->mysql, Select.c_str());
    if (rc == 0)
    {
        MYSQL_RES *res = mysql_store_result(c->mysql);
        if (res != nullptr)
        {
            return new WordFormEnumerator_MySQL(new LS_ResultSet_MySQL(c, res, read_tx.release()), this, forms);
        }
    }

#if defined LEM_THREADS
    lem::Process::CritSecLocker guard(&c->cs);
    c->cs.Leave();
#endif

    cnx->Error(Select);

    return nullptr;
}



WordFormEnumerator* WordEntries_MySQL::ListWordForms_Fuzzy(const lem::UCString &word, float min_val)
{
    return ListWordForms(word, false);
}


WordFormEnumerator* WordEntries_MySQL::ListWordForms_Globbing(const lem::UFString &mask)
{
    lem::MemFormatter mem;

    lem::UFString s(mask.c_str());
    s.subst_all(L'?', L'_');
    s.subst_all(L'*', L'%');

    mem.printf("SELECT F.id_entry, F.iform, L.name"
        " FROM sg_lexem L, sg_form F"
        " WHERE L.name LIKE '%us' AND F.id_lexem=L.id", s.c_str());

    lem::FString Select(lem::to_utf8(mem.string()));

    MySQLCnx *c = cnx->GetDb();
#if defined LEM_THREADS
    c->cs.Enter();
#endif

    std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

    int rc = mysql_query(c->mysql, Select.c_str());
    if (rc == 0)
    {
        MYSQL_RES *res = mysql_store_result(c->mysql);
        if (res != nullptr)
        {
            return new WordFormEnumerator_MySQL(new LS_ResultSet_MySQL(c, res, read_tx.release()), this);
        }
    }

#if defined LEM_THREADS
    lem::Process::CritSecLocker guard(&c->cs);
    c->cs.Leave();
#endif

    cnx->Error(Select);
    return nullptr;
}


int WordEntries_MySQL::FindEntryOmonym(const Lexem& lname, int id_class, const Solarix::GramCoordPair &p)
{
    lem::MemFormatter mem;

    lem::UFString s(lname.c_str());
    lem::mysql_escape(s);

    mem.printf("SELECT id"
        " FROM sg_entry E, sg_entry_coord EC"
        " WHERE name='%us' AND id_class=%d AND"
        " EC.id_entry=E.id AND EC.icoord=%d AND EC.istate=%d"
        , s.c_str(), id_class, p.GetCoord().GetIndex(), p.GetState());

    lem::FString Select(lem::to_utf8(mem.string()));

    int ekey = UNKNOWN;

    MySQLCnx *c = cnx->GetDb();
#if defined LEM_THREADS
    lem::Process::CritSecLocker guard(&c->cs);
#endif

    std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

    int rc = mysql_query(c->mysql, Select.c_str());
    if (rc == 0)
    {
        MYSQL_RES *res = mysql_store_result(c->mysql);
        if (res != nullptr)
        {
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row)
            {
                ekey = lem::mysql_column_int(row, 0);
            }

            mysql_free_result(res);
        }
    }
    else
    {
        cnx->Error(Select);
    }

    return ekey;
}






int WordEntries_MySQL::FindEntryOmonym(
    const Lexem& lname,
    int id_class,
    const lem::MCollect<Solarix::GramCoordPair> &p
)
{
    lem::MemFormatter mem;

    lem::UFString s(lname.c_str());
    lem::mysql_escape(s);

    lem::UFString from_s, where_s;

    for (lem::Container::size_type i = 0; i < p.size(); ++i)
    {
        from_s += lem::format_str(L", sg_entry_coord EC%d", CastSizeToInt(i));

        where_s += lem::format_str(L" AND EC%d.id_entry=E.id AND EC%d.icoord=%d AND EC%d.istate=%d",
            CastSizeToInt(i), CastSizeToInt(i), p[i].GetCoord().GetIndex(), CastSizeToInt(i), p[i].GetState());
    }

    mem.printf("SELECT id"
        " FROM sg_entry E %us"
        " WHERE name='%us' AND id_class=%d %us"
        , from_s.c_str(), s.c_str(), id_class, where_s.c_str());

    lem::FString Select(lem::to_utf8(mem.string()));

    int ekey = UNKNOWN;

    MySQLCnx *c = cnx->GetDb();
#if defined LEM_THREADS
    lem::Process::CritSecLocker guard(&c->cs);
#endif

    std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

    int rc = mysql_query(c->mysql, Select.c_str());
    if (rc == 0)
    {
        MYSQL_RES *res = mysql_store_result(c->mysql);
        if (res != nullptr)
        {
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row)
            {
                ekey = lem::mysql_column_int(row, 0);
            }

            mysql_free_result(res);
        }
    }
    else
    {
        cnx->Error(Select);
    }

    return ekey;
}




int WordEntries_MySQL::FindEntryOmonym(
    const Lexem& lname,
    int id_class,
    const ExactWordEntryLocator &locator
)
{
    lem::MemFormatter mem;

    lem::UFString s(lname.c_str());
    lem::mysql_escape(s);

    lem::UFString from_s, where_s;

    for (lem::Container::size_type i = 0; i < locator.pairs.size(); ++i)
    {
        if (locator.pairs[i].GetState() == 0 && sg.coords()[locator.pairs[i].GetCoord().GetIndex()].IsBistable())
        {
            // Задано состояние 0 бистабильной координаты, это равнозначно проверке, что такой координаты вообще нет в списке пар статьи.
            where_s += lem::format_str(L" AND NOT EXIST ( SELECT * FROM sg_entry_coord EC%d WHERE EC%d.id_entry=E.id AND EC%d.icoord=%d AND EC%d.istate=1 ) ",
                CastSizeToInt(i), CastSizeToInt(i), locator.pairs[i].GetCoord().GetIndex(), CastSizeToInt(i));
        }
        else
        {
            from_s += lem::format_str(L", sg_entry_coord EC%d", CastSizeToInt(i));
            where_s += lem::format_str(L" AND EC%d.id_entry=E.id AND EC%d.icoord=%d AND EC%d.istate=%d",
                CastSizeToInt(i), CastSizeToInt(i), locator.pairs[i].GetCoord().GetIndex(), CastSizeToInt(i), locator.pairs[i].GetState());
        }
    }

    mem.printf("SELECT id"
        " FROM sg_entry E %us"
        " WHERE name='%us' AND id_class=%d %us"
        , from_s.c_str(), s.c_str(), id_class, where_s.c_str());

    lem::FString Select(lem::to_utf8(mem.string()));

    int ekey = UNKNOWN;

    MySQLCnx *c = cnx->GetDb();
#if defined LEM_THREADS
    lem::Process::CritSecLocker guard(&c->cs);
#endif

    std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

    int rc = mysql_query(c->mysql, Select.c_str());
    if (rc == 0)
    {
        MYSQL_RES *res = mysql_store_result(c->mysql);
        if (res != nullptr)
        {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res)) != nullptr)
            {
                int id = lem::mysql_column_int(row, 0);

                if (locator.HasAuxSelector())
                {
                    const int aux_type = sg.GetAuxFormTypes()[locator.aux_type];
                    if (aux_type == UNKNOWN)
                    {
                        lem::MemFormatter mem;
                        mem.printf("Unknown aux type [%us]", locator.aux_type.c_str());
                        throw E_BaseException(mem.string());
                    }

                    lem::UFString aux_data;
                    int aux_id = sg.GetStorage().GetAuxEntryData(ekey, aux_type, aux_data);
                    if (aux_id != UNKNOWN && aux_data == locator.aux_value.c_str())
                    {
                        ekey = id;
                        break;
                    }
                }
                else
                {
                    ekey = id;
                    break;
                }
            }

            mysql_free_result(res);
        }
    }
    else
    {
        cnx->Error(Select);
    }

    return ekey;
}





int WordEntries_MySQL::CountLexemes()
{
    MySQLCnx *c = cnx->GetDb();
#if defined LEM_THREADS
    lem::Process::CritSecLocker guard(&c->cs);
#endif

    return lem::mysql_select_int(c->mysql, "SELECT count(*) FROM sg_lexem");
}



LexemeEnumerator* WordEntries_MySQL::ListLexemes()
{
    lem::FString Select("SELECT name FROM sg_lexem");

    MySQLCnx *c = cnx->GetDb();
#if defined LEM_THREADS
    c->cs.Enter();
#endif

    std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

    int rc = mysql_query(c->mysql, Select.c_str());
    if (rc == 0)
    {
        MYSQL_RES *res = mysql_store_result(c->mysql);
        if (res != nullptr)
        {
            return new LexemeEnumerator_MySQL(this, new LS_ResultSet_MySQL(c, res, read_tx.release()));
        }
    }

#if defined LEM_THREADS
    lem::Process::CritSecLocker guard(&c->cs);
    c->cs.Leave();
#endif

    cnx->Error(Select);
    return nullptr;
}





#if defined SOL_LOADTXT
int WordEntries_MySQL::LoadEntry(lem::StrParser<lem::UFString> &txt)
{
    // считываем шапку статьи - ее имя и класс
    // entry имя : класс
    txt.read_it(L"entry");

    lem::UFString ename2;
    while (!txt.eof())
    {
        lem::UFString t = txt.read();
        if (t == L':')
            break;

        if (!ename2.empty())
        {
            ename2 += Solarix::Lexem::DelimiterChar;
        }

        ename2 += t;
    }

    ename2.strip(L'"');
    Lexem entry_name(ename2.c_str());
    sg.GetDict().GetLexAuto().TranslateLexem(entry_name, false);
    entry_name.Translate(sg.GetDict().GetGraphGram(), 2);

    lem::UFString cname = txt.read();
    int id_class = sg.FindClass(cname.c_str());
    if (id_class == UNKNOWN)
        return -2;

    // проверка на переопределение
    if (FindEntry(entry_name, id_class) != UNKNOWN)
    {
        throw E_BaseException(L"Entry redefinition");
    }

    // создаем статью
    SG_Entry *e = new SG_Entry(entry_name, id_class, ml_ref);

    // загружаем грамматические формы
    e->LoadBody(sg, txt);

    e->PrepareAfterLoad(sg.GetDict().GetGraphGram(), sg);

    // -----------------------------
    // сохраняем статью в БД
    // -----------------------------

    UFString s = e->GetName().c_str();
    int e_flags = 0;

    if (e->IsNonterminal())
        e_flags = e_flags | SOL_SG_NONTERMINAL_ENTRY;

    if (e->IsSilent())
        e_flags = e_flags | SOL_SG_SILENT_ENTRY;

    if (e->IsQuantor())
        e_flags = e_flags | SOL_SG_QUANTOR_ENTRY;

    UFString us(lem::to_upper(s));

    s = encode_str_to_sql(s);
    us = encode_str_to_sql(us);

    // сохраняем в БД шапку статьи
    lem::MemFormatter out;
    out.printf(
        "INSERT INTO sg_entry( name, uname, id_class, freq, exportable, flags ) VALUES( '%us', '%us', %d, %d, 1, %d );\n"
        , s.c_str()
        , us.c_str()
        , e->GetClass()
        , e->GetFreq()
        , e_flags
    );

    lem::FString sql1 = to_utf8(out.string());

    MySQLCnx *c = cnx->GetDb();
#if defined LEM_THREADS
    lem::Process::CritSecLocker guard(&c->cs);
#endif

    cnx->Execute(sql1);
    const int ekey = cnx->GetLastId();
    e->SetKey(ekey);

    // сохраняем список атрибутов
    for (lem::Container::size_type j = 0; j < e->attrs().size(); ++j)
    {
        const int icoord = e->attrs()[j].GetCoord().GetIndex();
        const int istate = e->attrs()[j].GetState();

        if (istate != ANY_STATE)
        {
            out.printf("INSERT INTO sg_entry_coord( id_entry, icoord, istate ) VALUES ( %d, %d, %d );\n",
                ekey, icoord, istate);

            lem::FString sql1 = to_utf8(out.string());
            cnx->Execute(sql1);
        }
    }


    // сохраняем грамматические формы
    lem::UFString form_dims, str_form_dims;
    for (lem::Container::size_type j = 0; j < e->forms().size(); j++)
    {
        const SG_EntryForm &form = e->forms()[j];

        const int id_lexem = RegisterLexemeInDatabase(form.name());

        form_dims.clear();
        sg.ComposeFormDims(*e, form, form_dims, true);
        form_dims.re_clear();

        str_form_dims.clear();
        sg.ComposeFormDims(*e, form, str_form_dims, false);
        str_form_dims.re_clear();

        const int id_dims = RegisterCoordPairsInDatabase(form_dims, str_form_dims);

        UFString fs(form.name().c_str());
        fs = encode_str_to_sql(fs);

        out.printf(
            "INSERT INTO sg_form( id_entry, iform, id_lexem, name, id_dims ) VALUES( %ud, %d, %d, '%us', %d );\n"
            , ekey
            , j
            , id_lexem
            , fs.c_str()
            , id_dims
        );

        cnx->Execute(lem::to_utf8(out.string()));

        for (lem::Container::size_type k = 0; k < form.coords().size(); ++k)
        {
            out.printf("INSERT INTO sg_form_coord( id_entry, iform, icoord, istate ) "
                " VALUES ( %d, %d, %d, %d );\n", ekey, j, form.coords()[k].GetCoord().GetIndex(), form.coords()[k].GetState()
            );

            cnx->Execute(lem::to_utf8(out.string()));
        }
    }

    // проверим наличие многолексемных форм
    for (lem::Container::size_type j = 0; j < e->forms().size(); ++j)
    {
        const Lexem & form = e->forms()[j].name();

        const int n_lexem = CastSizeToInt(form.Count_Lexems());
        if (n_lexem > 1)
        {
            UCStringSet list;
            form.Split(list);
            const UCString & headword = list.front();

            out.printf("INSERT INTO multilexem( txt, headword, n_lexem ) VALUES ( '%us', '%us', %d );\n"
                , form.c_str(), headword.c_str(), n_lexem);

            cnx->Execute(lem::to_utf8(out.string()));

#if defined LEM_THREADS
            lem::Process::RW_UniqueGuard rlock(cs_multilexem);
#endif

            max_multilexem_len = std::max(max_multilexem_len, n_lexem);

            std::map<lem::UCString, Solarix::MultiLexemInfo>::iterator it = multilexem_head.find(form);
            if (it == multilexem_head.end())
            {
                Solarix::MultiLexemInfo minfo;
                minfo.maxlen = n_lexem;
                multilexem_head.insert(std::make_pair(form, minfo));
            }

            multilexems.insert(form);
        }
    }

#if defined LEM_THREADS
    lem::Process::RW_UniqueGuard guard2(cs_entries);
#endif

    entries_map.insert(std::make_pair(ekey, e));
    entries.push_back(e);
    enames.push_back(new Solarix::Lexem(entry_name));
    enames_map.insert(std::make_pair(entry_name, ekey));

    return e->GetKey();
}
#endif






int WordEntries_MySQL::RegisterLexemeInDatabase(const UCString & lex)
{
    lem::UFString fs(lex.c_str());

    int id_lexem = UNKNOWN;
    lem::MemFormatter out;
    out.printf("SELECT id FROM sg_lexem WHERE name='%us'", fs.c_str());
    lem::FString Select(to_utf8(out.string()));

    MySQLCnx *c = cnx->GetDb();
#if defined LEM_THREADS
    lem::Process::CritSecLocker guard(&c->cs);
#endif

    int rc = mysql_query(c->mysql, Select.c_str());
    if (rc == 0)
    {
        MYSQL_RES *res = mysql_store_result(c->mysql);
        if (res != nullptr)
        {
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row)
            {
                id_lexem = lem::mysql_column_int(row, 0);
            }

            mysql_free_result(res);
        }
    }
    else
    {
        cnx->Error(Select);
    }

    if (id_lexem == UNKNOWN)
    {
        out.printf("INSERT INTO sg_lexem( name ) VALUES ( '%us' )", fs.c_str());

        lem::FString insert_sql = to_utf8(out.string());
        cnx->Execute(insert_sql);
        id_lexem = cnx->GetLastId();;
    }

    return id_lexem;
}






int WordEntries_MySQL::RegisterCoordPairsInDatabase(
    const lem::UFString &int_pairs,
    const lem::UFString &str_pairs
)
{
    int id_dims = UNKNOWN;

    if (int_pairs.empty())
    {
        id_dims = 0;
    }
    else
    {
        lem::MemFormatter out;
        out.printf("SELECT id FROM coord_pairs WHERE pairs='%us'", int_pairs.c_str());
        FString Select(to_utf8(out.string()));

        MySQLCnx *c = cnx->GetDb();
#if defined LEM_THREADS
        lem::Process::CritSecLocker guard(&c->cs);
#endif

        int rc = mysql_query(c->mysql, Select.c_str());
        if (rc == 0)
        {
            MYSQL_RES *res = mysql_store_result(c->mysql);
            if (res != nullptr)
            {
                MYSQL_ROW row = mysql_fetch_row(res);
                if (row)
                {
                    id_dims = lem::mysql_column_int(row, 0);
                }

                mysql_free_result(res);
            }
        }
        else
        {
            cnx->Error(Select);
        }

        if (id_dims == UNKNOWN)
        {
            // такой записи в справочнике нет, внесем.
            out.printf("INSERT INTO coord_pairs( pairs, str_pairs ) VALUES ( '%us', '%us' )",
                int_pairs.c_str(), str_pairs.c_str());

            FString insert_sql = to_utf8(out.string());
            cnx->Execute(insert_sql);

            id_dims = cnx->GetLastId();
        }
    }

    return id_dims;
}



void WordEntries_MySQL::GetUEntries_Impl()
{
    lem::FString Select("SELECT id FROM unknown_entries");

    MySQLCnx *c = cnx->GetDb();
#if defined LEM_THREADS
    lem::Process::CritSecLocker guard(&c->cs);
#endif

    std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

    int rc = mysql_query(c->mysql, Select.c_str());
    if (rc == 0)
    {
        int ekey = UNKNOWN;

        MYSQL_RES *res = mysql_store_result(c->mysql);
        if (res != nullptr)
        {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res)) != nullptr)
            {
                int ekey = lem::mysql_column_int(row, 0);
                uentries.push_back(ekey);
            }

            mysql_free_result(res);
        }
    }
    else
    {
        cnx->Error(Select);
    }

    return;
}



int WordEntries_MySQL::GetPredefinedEntryKey_Impl(int index)
{
    lem::FString Select(lem::format_str("SELECT id_entry FROM predef_entries WHERE id=%d", index));

    int ret = UNKNOWN;

    MySQLCnx *c = cnx->GetDb();
#if defined LEM_THREADS
    lem::Process::CritSecLocker guard2(&c->cs);
#endif

    std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

    int rc = mysql_query(c->mysql, Select.c_str());
    if (rc == 0)
    {
        int ekey = UNKNOWN;

        MYSQL_RES *res = mysql_store_result(c->mysql);
        if (res != nullptr)
        {
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row != nullptr)
            {
                ret = lem::mysql_column_int(row, 0);
            }

            mysql_free_result(res);
        }
    }
    else
    {
        cnx->Error(Select);
    }

    return ret;
}


int WordEntries_MySQL::FindQuantorEntry_Impl(int id_class)
{
    lem::MemFormatter mem;
    mem.printf("SELECT id FROM unknown_entries U, sg_entry E"
        " WHERE E.id=U.id AND E.id_class=%d", id_class);

    lem::FString Select(lem::to_utf8(mem.string()));

    int ret = UNKNOWN;

    MySQLCnx *c = cnx->GetDb();
#if defined LEM_THREADS
    lem::Process::CritSecLocker guard2(&c->cs);
#endif

    std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

    int rc = mysql_query(c->mysql, Select.c_str());
    if (rc == 0)
    {
        int ekey = UNKNOWN;

        MYSQL_RES *res = mysql_store_result(c->mysql);
        if (res != nullptr)
        {
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row != nullptr)
            {
                ret = lem::mysql_column_int(row, 0);
            }

            mysql_free_result(res);
        }
    }
    else
    {
        cnx->Error(Select);
    }

    LEM_CHECKIT_Z(ret != UNKNOWN);
    return ret;
}



SG_Entry* WordEntries_MySQL::LoadEntryFromDb_Impl(int ekey)
{
    // 1. загружаем из БД шапку статьи

    lem::MemFormatter mem;
    mem.printf("SELECT uname, id_class, flags, freq FROM sg_entry WHERE id=%d", ekey);

    lem::FString Select1(lem::to_utf8(mem.string()));

    MySQLCnx *c = cnx->GetDb();
#if defined LEM_THREADS
    lem::Process::CritSecLocker guard2(&c->cs);
#endif

    std::unique_ptr<TransactionGuard> read_tx(cnx->GetReadTx());

    SG_Entry *e = nullptr;

    int rc = mysql_query(c->mysql, Select1.c_str());
    if (rc == 0)
    {
        lem::Collect<lem::UFString> dim_toks, dim_toks2;

        MYSQL_RES *res1 = mysql_store_result(c->mysql);
        if (res1 != nullptr)
        {
            MYSQL_ROW row1 = mysql_fetch_row(res1);
            if (row1)
            {
                UCString ename = lem::mysql_column_ucstring(row1, 0);
                int id_class = lem::mysql_column_int(row1, 1);
                int flags = lem::mysql_column_int(row1, 2);
                int freq = lem::mysql_column_int(row1, 3);

                CP_Array attrs;

                mem.printf("SELECT icoord, istate FROM sg_entry_coord WHERE id_entry=%d", ekey);
                lem::FString Select2(lem::to_utf8(mem.string()));
                rc = mysql_query(c->mysql, Select2.c_str());
                if (rc == 0)
                {
                    MYSQL_RES *res2 = mysql_store_result(c->mysql);
                    if (res2 != nullptr)
                    {
                        MYSQL_ROW row2;
                        while ((row2 = mysql_fetch_row(res2)) != nullptr)
                        {
                            int id_coord = lem::mysql_column_int(row2, 0);
                            int id_state = lem::mysql_column_int(row2, 1);
                            attrs.push_back(Solarix::GramCoordPair(id_coord, id_state));
                        }
                    }
                    mysql_free_result(res2);
                }
                else
                {
                    cnx->Error(Select2);
                }

                const Lexem *ename_ptr = RegisterLexemeInCache(ename);
                e = new SG_Entry(ekey, ename_ptr, id_class, attrs, flags, freq);

                // загружаем список форм
                mem.printf("SELECT F.iform, L.name, Coalesce(P.id,-1), P.pairs"
                    " FROM sg_form F left join coord_pairs P on P.id=F.id_dims, sg_lexem L"
                    " WHERE F.id_entry=%d AND L.id=F.id_lexem"
                    " ORDER BY F.iform", ekey);

                lem::FString Select3(lem::to_utf8(mem.string()));
                rc = mysql_query(c->mysql, Select3.c_str());
                if (rc == 0)
                {
                    MYSQL_RES *res3 = mysql_store_result(c->mysql);
                    if (res3 != nullptr)
                    {
                        MYSQL_ROW row3;
                        while ((row3 = mysql_fetch_row(res3)) != nullptr)
                        {
                            int iform = lem::mysql_column_int(row3, 0);

                            Lexem fname = lem::mysql_column_ucstring(row3, 1);
                            const Lexem *fname_ptr = RegisterLexemeInCache(fname);

                            CP_Array dims(attrs);

                            int id_dims = lem::mysql_column_int(row3, 2);
                            if (id_dims != -1)
                            {
                                dim_toks.clear();
                                lem::UFString dims_str = lem::mysql_column_ufstring(row3, 3);
                                lem::parse(dims_str, dim_toks, L" ");
                                for (lem::Container::size_type k = 0; k < dim_toks.size(); ++k)
                                {
                                    const lem::UFString &s = dim_toks[k];
                                    dim_toks2.clear();
                                    lem::parse(s, dim_toks2, L":");
                                    LEM_CHECKIT_Z(dim_toks2.size() == 2)
                                        const int id_coord = lem::to_int(dim_toks2[0]);
                                    const int id_state = lem::to_int(dim_toks2[1]);
                                    dims.push_back(GramCoordPair(id_coord, id_state));
                                }
                            }
                            else
                            {
                                mem.printf("SELECT icoord, istate FROM sg_form_coord WHERE id_entry=%d AND iform=%d",
                                    ekey, iform);
                                lem::FString Select4(lem::to_utf8(mem.string()));
                                rc = mysql_query(c->mysql, Select4.c_str());
                                if (rc == 0)
                                {
                                    MYSQL_RES *res4 = mysql_store_result(c->mysql);
                                    if (res4 != nullptr)
                                    {
                                        MYSQL_ROW row4;
                                        while ((row4 = mysql_fetch_row(res4)) != nullptr)
                                        {
                                            int id_coord = lem::mysql_column_int(row4, 0);
                                            int id_state = lem::mysql_column_int(row4, 1);
                                            dims.push_back(GramCoordPair(id_coord, id_state));
                                        }
                                    }
                                    mysql_free_result(res4);
                                }
                                else
                                {
                                    cnx->Error(Select2);
                                }
                            }

                            const CP_Array *dims_ptr = RegisterCoordPairsInCache(dims);

                            SG_EntryForm f(fname_ptr, dims_ptr);
                            e->forms().push_back(f);
                        }
                    }

                    mysql_free_result(res3);
                }
                else
                {
                    cnx->Error(Select3);
                }
            }

            mysql_free_result(res1);
        }
    }
    else
    {
        cnx->Error(Select1);
    }

    if (e == nullptr)
    {
        lem::MemFormatter mem;
        mem.printf("Can not find entry with id=%d", ekey);
        throw lem::E_BaseException(mem.string());
    }

    return e;
}


#endif
