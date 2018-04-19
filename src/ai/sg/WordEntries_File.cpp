#include <lem/logfile.h>
#include <lem/bit_array32.h>
#include <lem/solarix/exceptions.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/gg_autom.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/PartOfSpeech.h>
#include <lem/solarix/prefix_tree.h>
#include <lem/solarix/some_strings.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/PartOfSpeech.h>
#include <lem/solarix/WordEntryEnumerator_File.h>
#include <lem/solarix/WordFormEnumerator_File.h>
#include <lem/solarix/LexemeEnumerator_File.h>
#include <lem/solarix/Languages.h>
#include <lem/solarix/LanguageEnumerator.h>
#include <lem/solarix/SymbolEnumerator.h>
#include <lem/solarix/Symbols.h>
#include <lem/solarix/Symbol.h>
#include <lem/solarix/some_strings.h>
#include <lem/solarix/ExactWordEntryLocator.h>
#include <lem/solarix/AuxFormTypes.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/WordEntries_File.h>

using namespace Solarix;

WordEntries_File::WordEntries_File(SynGram * _sg, const Dictionary_Config &cfg)
    : sg(_sg)
    , ml_ref(cfg.ldsize)
#if defined SOL_LOADTXT && defined SOL_COMPILER
    , coord_ref(1024)
#endif
{
    max_ml_len = 1; // Максимальная лексемная длина мультилексем пока не известна,
                  // поэтому полагаем, что мультилексемы состоят максимум из
                  // 1 лексемы.

    lazy_load = false; // по умолчанию - загружаем лексикон сразу в оперативную память целиком. 

    for (int j = 0; j < (int)DIM_A(predefined_entry); j++)
        predefined_entry[j] = UNKNOWN;

    bogus_entry = nullptr;

    return;
}


WordEntries_File::~WordEntries_File()
{
    lem_rub_off(bogus_entry);
    ClearGroups();
    Delete_Entries();
    return;
}


void WordEntries_File::CreateDefaultEntries()
{
#if defined SOL_LOADTXT && defined SOL_COMPILER
    // Создаём особую словарную статью ?:?
    SG_Entry *uu = new SG_Entry(SOL_UNKNOWN_ENTRY_NAME, UNKNOWN_STATE, ml_ref);
    uu->SetKey(sg->GetDict().GetNextKey());
    uu->SetQuantor();
    AddAutoCreated(uu);
#endif

    bogus_entry = new SG_BogusEntry();
    return;
}


int WordEntries_File::CountEntries(int id_class, int id_language)
{
    if (
        (id_class == UNKNOWN || id_class == ANY_STATE) &&
        (id_language == UNKNOWN || id_language == ANY_STATE)
        )
    {
        // без фильтрации
        return CastSizeToInt(entry.size());
    }

    int n = 0;
    for (lem::Container::size_type i = 0; i < entry.size(); ++i)
    {
        const SG_Entry &e = GetWordEntry(i);
        if (id_class != UNKNOWN && id_class != ANY_STATE)
        {
            if (e.GetClass() != id_class)
                continue;
        }

        if (id_language != UNKNOWN && id_language != ANY_STATE)
        {
            int ic = e.GetClass();
            if (lem::is_quantor(ic))
                continue;

            const SG_Class & c = sg->GetClass(ic);
            if (c.GetLanguage() != id_language)
                continue;

            n++;
        }
    }

    return n;
}


int WordEntries_File::CountForms(int id_language)
{
    int n = 0;

    for (lem::Container::size_type i = 0; i < entry.size(); ++i)
    {
        const SG_Entry &e = GetWordEntry(i);

        if (id_language != UNKNOWN && id_language != ANY_STATE)
        {
            int ic = e.GetClass();
            if (lem::is_quantor(ic))
                continue;

            const SG_Class & c = sg->GetClass(ic);
            if (c.GetLanguage() != id_language)
                continue;

            n += CastSizeToInt(e.forms().size());
        }
    }

    return n;
}

bool WordEntries_File::IsWordForm(const Solarix::Lexem &lex)
{
    return ml_ref.Find(lex) != nullptr;
}


// ****************************************************************************
// Если лексема-аргумент может быть начальной лексемой для мультилексемы,
// то возвращается true и информация о максимальной длине такой мультилексемы.
// ****************************************************************************
bool WordEntries_File::IsMultilexemHead(const lem::UCString &word, MultiLexemInfo &info)
{
    int ret = 0;

    if (ML_fronts.find(word) != ML_fronts.end())
    {
        int i = ML_entry_lex_list.find(word);
        if (i != UNKNOWN)
        {
            lem::BitArray32 bits = ML_entry_pre_list[i];
            int x = bits.MaxBit();

            // Мультилексема, которая начинается с 'l', может быть длиной максимум x.
            // Сначала пытаемся упаковать самую длинную, постепенно переходя к коротким.
            if (x != -1)
                ret = x;//+1;
        }
    }

    info.maxlen = ret;
    return ret != 0;
}


int WordEntries_File::GetMaxMultilexemLen()
{
    return max_ml_len;
}



void WordEntries_File::PrepareForMerging()
{
    return;
}


bool WordEntries_File::IsMultilexemForm(const Solarix::Lexem &lex)
{
    if (ML_ML.empty())
    {
        for (lem::Container::size_type i = 0; i < ML_entry_key_list.size(); ++i)
        {
            const int ekey = ML_entry_key_list[i];
            const SG_Entry &e = GetEntryByKey(ekey);

            const int iform = e.FindForm(lex);
            if (iform != UNKNOWN)
                return true;
        }
    }
    else
    {
        return ML_ML.find(lex) != ML_ML.end();
    }

    return false;
}


WordEntryEnumerator* WordEntries_File::ListEntries()
{
    return new WordEntryEnumerator_File(this);
}


WordEntryEnumerator* WordEntries_File::ListEntries(const lem::UCString &name, int id_class)
{
    return new WordEntryEnumerator_File(this, name, id_class);
}




int WordEntries_File::FindEntry(const lem::UCString &word_name, int id_class)
{
#if defined SOL_LOADTXT && defined SOL_COMPILER

    if (id_class != ANY_STATE && id_class != UNKNOWN)
    {
        UCString uname = to_upper(word_name);
        std::multimap< std::pair<UCString, int>, int >::const_iterator it = entry_class_lookup.find(std::make_pair(uname, id_class));
        if (it != entry_class_lookup.end())
            return it->second;

        return UNKNOWN;
    }

#endif

    for (lem::Container::size_type i = 0; i < entry.size(); ++i)
        if (GetWordEntry(i).GetName().eqi(word_name))
        {
            if (id_class != UNKNOWN && id_class != ANY_STATE && GetWordEntry(i).GetClass() != id_class)
                continue;

            return GetWordEntry(i).GetKey();
        }

    return UNKNOWN;
}



WordFormEnumerator* WordEntries_File::ListWordForms(const lem::UCString & form, bool allow_nonterminals)
{
    /*
     std::map< SG_EntryGroup::KEY, SG_EntryGroup* >::const_iterator it = group.find( SG_EntryGroup::BuildKey(form) );

     if( it!=group.end() )
      {
       return new WordFormEnumerator_File2(this,form,it->second);
      }
     else
      {
       return new WordFormEnumerator_File1( this, form );
      }
    */

    const int lexem_index = lookup_table.Findlexem(ml_ref, form);
    if (lexem_index == UNKNOWN)
    {
        // соответствий нет.
        return new WordFormEnumerator_File1(this, form);
    }
    else
    {
        return new WordFormEnumerator_File2(this, form, lookup_table.lexem_slot[lexem_index], lookup_table);
    }
}


/*
WordEntryEnumerator* WordEntries_File::ListEntries( const lem::triple<wchar_t,wchar_t,wchar_t> & prefix3 )
{
 std::map< SG_EntryGroup::KEY, SG_EntryGroup* >::const_iterator it = group.find( prefix3 );

 if( it!=group.end() )
  {
   return new WordEntryEnumerator_File_ByGroup(this,it->second);
  }

 // Поиск будет производиться по всему Лексикону.
 return ListEntries();
}
*/


WordFormEnumerator* WordEntries_File::ListWordForms(const lem::MCollect<lem::UCString> &forms)
{
    return new WordFormEnumerator_File3(this, forms);
}


WordFormEnumerator* WordEntries_File::ListWordForms_Fuzzy(const lem::UCString &word, float min_val)
{
    Solarix::Lexem uc_word(word);
    sg->GetDict().GetLexAuto().TranslateLexem(uc_word, true);
    return new WordFormEnumeratorFuzzy_File(this, uc_word, min_val);
}


WordFormEnumerator* WordEntries_File::ListWordForms_Globbing(const lem::UFString &mask)
{
    lem::UFString umask(mask);
    umask.to_upper();
    return new WordFormEnumeratorGlobbing_File(this, umask);
}




const SG_Entry& WordEntries_File::GetEntry(int ekey)
{
    const int ie = FindEntryIndexByKey(ekey);
    LEM_CHECKIT_Z(ie != UNKNOWN);
    return GetWordEntry(ie);
}

SG_Entry& WordEntries_File::GetEntryForChange(int ekey)
{
    const int ie = FindEntryIndexByKey(ekey);
    LEM_CHECKIT_Z(ie != UNKNOWN);
    return GetWordEntry(ie);
}



void WordEntries_File::SaveBin(lem::Stream &bin) const
{
#if defined SOL_SAVEBIN
    ml_ref.SaveBin(bin);

    coord_ref.SaveBin(bin);

    lookup_table.SaveBin(bin);
    /*
    // #if LEM_DEBUGGING==1
     lem::mout->eol();
     for( int kkk=0; kkk<lookup_table.lexem_slot.size(); ++kkk )
      {
       WordEntries_LookUpItem xxx = lookup_table.lexem_slot[kkk];
       lem::mout->printf( "x[%d]=%d,%d ", kkk, xxx.start_index, xxx.len );
      }
     lem::mout->eol();
    // #endif
    */

    ientry.SaveBin(bin);
    u_entry.SaveBin(bin);

    ML_entry_key_list.SaveBin(bin);
    ML_entry_lex_list.SaveBin(bin);
    ML_entry_pre_list.SaveBin(bin);

    bin.write(&max_ml_len, sizeof(max_ml_len));
    bin.write(predefined_entry, sizeof(predefined_entry));

    bin.write_int(CastSizeToInt(entry.size()));

    lem::Stream::pos_type p1 = bin.tellp();

    lem::Stream::pos_type epos_begin_pos = 0;
    lem::Stream::pos_type entries_begin_pos = 0;
    lem::Stream::pos_type end_pos = 0;

    bin.write(&epos_begin_pos, sizeof(epos_begin_pos)); // сюда впишем позицию списка позиций статей
    bin.write(&entries_begin_pos, sizeof(entries_begin_pos)); // а сюда - начало списка статей
    bin.write(&end_pos, sizeof(end_pos)); // а сюда - позицию после лексикона, чтобы другие модули могли продолжить загрузку из бинарного файла

    lem::MCollect<lem::Stream::pos_type> entry_pos_tmp;
    entry_pos_tmp.resize(entry.size());
    epos_begin_pos = bin.tellp();
    entry_pos_tmp.SaveBin(bin);

    lem::MCollect< std::pair<int, int> > key_to_index_tmp;
    key_to_index_tmp.reserve(key_to_index.size());
    for (std::map< int/*entry_key*/, int/*entry_index*/ >::const_iterator it = key_to_index.begin(); it != key_to_index.end(); ++it)
    {
        key_to_index_tmp.push_back(*it);
    }
    key_to_index_tmp.SaveBin(bin);

    lem::MCollect<Lexem> ML_fronts_tmp;
    ML_fronts_tmp.reserve(ML_fronts.size());
    for (std::set<Lexem>::const_iterator it = ML_fronts.begin(); it != ML_fronts.end(); ++it)
        ML_fronts_tmp.push_back(*it);
    ML_fronts_tmp.SaveBin(bin);


    lem::MCollect<Lexem> ML_ML_tmp;
    ML_ML_tmp.reserve(ML_ML.size());
    for (std::set<Lexem>::const_iterator it = ML_ML.begin(); it != ML_ML.end(); ++it)
        ML_ML_tmp.push_back(*it);
    ML_ML_tmp.SaveBin(bin);

    entries_begin_pos = bin.tellp();

    for (lem::Container::size_type i = 0; i < entry.size(); i++)
    {
        entry_pos_tmp[i] = bin.tellp();
        entry[i]->SaveBin(bin);
    }

    end_pos = bin.tellp();

    bin.seekp(p1);
    bin.write(&epos_begin_pos, sizeof(epos_begin_pos));
    bin.write(&entries_begin_pos, sizeof(entries_begin_pos));
    bin.write(&end_pos, sizeof(end_pos));
    entry_pos_tmp.SaveBin(bin);
    bin.seekp(end_pos);

#endif

    return;
}


void WordEntries_File::LoadBin(lem::Stream &bin)
{
    ml_ref.LoadBin(bin);

    Delete_Entries();

    entry_pos.clear();

    coord_ref.LoadBin(bin);

    /*
     LEM_CHECKIT_Z( group.empty() );
     const int n_group = bin.read_int();
     for( int i=0; i<n_group; ++i )
      {
       SG_EntryGroup *g = new SG_EntryGroup(bin);
       group.insert( std::make_pair( g->GetKey(), g ) );
      }
    */
    lookup_table.LoadBin(bin);

    /*
    // #if LEM_DEBUGGING==1
     lem::mout->eol();
     for( int kkk=0; kkk<lookup_table.lexem_slot.size(); ++kkk )
      {
       WordEntries_LookUpItem xxx = lookup_table.lexem_slot[kkk];
       lem::mout->printf( "x[%d]=%d,%d ", kkk, xxx.start_index, xxx.len );
      }
     lem::mout->eol();
    // #endif
    */

    ientry.LoadBin(bin);

    u_entry.LoadBin(bin);

    ML_entry_key_list.LoadBin(bin);
    ML_entry_lex_list.LoadBin(bin);
    ML_entry_pre_list.LoadBin(bin);

    bin.read(&max_ml_len, sizeof(max_ml_len));
    bin.read(predefined_entry, sizeof(predefined_entry));

    const int n_entry = bin.read_int();
    entry.resize(n_entry);

    // загрузили все обязательные данные, теперь опциональная загрузка.
    lem::Stream::pos_type epos_begin_pos = 0;
    lem::Stream::pos_type entries_begin_pos = 0;
    lem::Stream::pos_type end_pos = 0;

    bin.read(&epos_begin_pos, sizeof(epos_begin_pos));
    bin.read(&entries_begin_pos, sizeof(entries_begin_pos));
    bin.read(&end_pos, sizeof(end_pos));

    if (lazy_load)
    {
        // статьи пока не загружаем.

        entry.Nullify();

        // прочитаем только список позиций начала каждой статьи.
        bin.seekp(epos_begin_pos);
        entry_pos.LoadBin(bin);

        lem::MCollect< std::pair<int, int> > key_to_index_tmp;
        key_to_index_tmp.LoadBin(bin);
        for (lem::Container::size_type i = 0; i < key_to_index_tmp.size(); ++i)
            key_to_index.insert(key_to_index_tmp[i]);

        lem::MCollect<Lexem> ML_tmp;
        ML_tmp.LoadBin(bin);
        for (lem::Container::size_type i = 0; i < ML_tmp.size(); ++i)
            ML_fronts.insert(ML_tmp[i]);

        ML_tmp.LoadBin(bin);
        for (lem::Container::size_type i = 0; i < ML_tmp.size(); ++i)
            ML_ML.insert(ML_tmp[i]);
    }
    else
    {
        bin.seekp(entries_begin_pos);

        entry_pos.clear();

        // список словарных статей загружаем сразу целиком в память.
        for (int i0 = 0; i0 < n_entry; i0++)
        {
            entry[i0] = new SG_Entry;
            entry[i0]->LoadBin(bin);

            if (entry[i0] != bogus_entry)
                entry[i0]->ReattachToRefs(*sg);
        }

        for (lem::Container::size_type ie = 0; ie < entry.size(); ie++)
        {
            key_to_index.insert(std::make_pair(entry[ientry[ie]]->GetKey(), ie));
        }

        coord_ref.AllAttached();

#if defined SOL_LOADTXT && defined SOL_COMPILER
        for (lem::Container::size_type k = 0; k < entry.size(); ++k)
        {
            const SG_Entry & e = GetWordEntry(k);
            entry_class_lookup.insert(std::make_pair(std::make_pair(lem::to_upper(e.GetName()), e.GetClass()), e.GetKey()));
    }
#endif

        for (lem::Container::size_type i = 0; i < ML_entry_key_list.size(); ++i)
        {
            const int ik = ML_entry_key_list[i];
            const SG_Entry &e = GetEntryByKey(ik);

            for (lem::Container::size_type j = 0; j < e.forms().size(); ++j)
            {
                const Lexem & form = e.forms()[j].name();

                if (form.Count_Lexems() > 1)
                {
                    UCStringSet list;
                    form.Split(list);
                    ML_fronts.insert(list.front());
                    ML_ML.insert(form);
                }
            }
        }
}

    bin.seekp(end_pos);

    return;
}



void WordEntries_File::Delete_Entries()
{
#if defined SOL_CAA
    for (lem::Container::size_type i = 0; i < entry.size(); i++)
        if (entry[i] != bogus_entry)
        {
            delete entry[i];
            entry[i] = nullptr;
        }

    ML_entry_key_list.clear();
    ientry.clear();
    u_entry.clear();
    key_to_index.clear();
    ML_entry_lex_list.clear();
    ML_fronts.clear();
    ML_ML.clear();

    entry.clear();

    entry_pos.clear();
    entries_bin.Delete();

#else
    entry.clear();
#endif

    ClearGroups();

    return;
}




SG_Entry& WordEntries_File::GetWordEntry(int index)
{
    LEM_CHECKIT_Z(index != UNKNOWN);
    const int raw_index = ientry[index];
    LoadEntry(raw_index);
    SG_Entry *e = entry[raw_index];
    return *e;
}

int WordEntries_File::GetPredefinedEntryKey(int index)
{
    LEM_CHECKIT_Z(index >= 0 && index < (int)DIM_A(predefined_entry));
    return predefined_entry[index];
}


int WordEntries_File::FindQuantorEntry(int id_class)
{
    const int nword = CastSizeToInt(entry.size());
    for (int ientry = 0; ientry < nword; ientry++)
    {
        const SG_Entry &entry = GetWordEntry(ientry);

        if (entry.GetClass() == id_class && entry.IsQuantor())
            return entry.GetKey();
    }

    // Найти не удалось.
    return UNKNOWN;
}


CharNode* WordEntries_File::GetPrefixTreeForAllLanguages()
{
    std::set<int> allowed_langs;
    lem::Ptr<LanguageEnumerator> lenum(sg->languages().Enumerate());
    while (lenum->Fetch())
        allowed_langs.insert(lenum->GetId());

    return GetPrefixTree(allowed_langs);
}


CharNode* WordEntries_File::GetPrefixTree(const std::set<int>& allowed_langs)
{
    CharNode * nodes_root = new CharNode;
    CharNode * tree = nodes_root;

    for (lem::Container::size_type i = 0; i < entry.size(); i++)
    {
        const Solarix::SG_Entry &e = GetWordEntry(CastSizeToInt(i));

        if (!e.IsTerminal())
            continue;

        const int iclass = e.GetClass();
        if (lem::is_quantor(iclass))
            continue;

        if (allowed_langs.find(sg->GetClass(iclass).GetLanguage()) == allowed_langs.end())
            continue;

        for (lem::Container::size_type j = 0; j < e.forms().size(); ++j)
        {
            const lem::UCString &f = e.forms()[j].name();

            CharNode *cur_ptr = nodes_root;

            const int fl = f.length();
            for (int k = 0; k < fl; ++k)
            {
                const wchar_t c = f[k];

                CharNode* leaf = cur_ptr->find(c, true);

                if (k == fl - 1)
                {
                    if (leaf->entries.empty() || (leaf->entries.back() != &e && leaf->entries.find(&e) == UNKNOWN))
                        leaf->entries.push_back(&e);
                }

                cur_ptr = leaf;
            }
        }
    }

    return tree;
}


void WordEntries_File::AddAutoCreated(SG_Entry *e)
{
#if defined SOL_LOADTXT && defined SOL_COMPILER
    e->GenerateForms(*sg);
    AddEntry(e);
#endif

    return;
}

int WordEntries_File::AddEntry(SG_Entry *e)
{
#if LEM_DEBUGGING==1
    UCString ename = e->GetName();
    int cls = e->GetClass();
#endif

    LEM_CHECKIT_Z(key_to_index.find(e->GetKey()) == key_to_index.end());
    key_to_index.insert(std::make_pair(e->GetKey(), ientry.size()));

    ientry.push_back(CastSizeToInt(entry.size()));
    entry.push_back(e);

    if (e->GetFlags2() != UNKNOWN)
        // Специальная ПРЕДОПРЕДЕЛЁННАЯ СТАТЬЯ.
        predefined_entry[e->GetFlags2()] = e->GetKey();

#if defined SOL_COMPILER
    entry_class_lookup.insert(std::make_pair(std::make_pair(lem::to_upper(e->GetName()), e->GetClass()), e->GetKey()));
#endif

    for (lem::Container::size_type j = 0; j < e->forms().size(); ++j)
    {
        const Lexem & form = e->forms()[j].name();

        if (form.Count_Lexems() > 1)
        {
            UCStringSet list;
            form.Split(list);
            ML_fronts.insert(list.front());
            ML_ML.insert(form);
        }
    }

    return e->GetKey();
}


void WordEntries_File::ReplaceEntry(int ekey, SG_Entry *dummy)
{
    const int ie = FindEntryIndexByKey(ekey);
    const int i = ientry[ie];
    delete entry[i];
    entry[i] = dummy;

    if (dummy->GetFlags2() != UNKNOWN)
        // Специальная ПРЕДОПРЕДЕЛЁННАЯ СТАТЬЯ.
        predefined_entry[dummy->GetFlags2()] = dummy->GetKey();

    return;
}


void WordEntries_File::PostRead(Macro_Parser &txtfile, const Binarization_Options &options)
{
#if defined SOL_COMPILER
    const int nword = entry.size();
    for (int iword = 0; iword < nword; iword++)
        entry[iword]->ProcessNetSection(txtfile, *sg, options);
#endif

    return;
}


Word_Coord WordEntries_File::FindWordForm(const UCString& name)
{
    for (lem::Container::size_type i = 0; i < entry.size(); i++)
    {
        SG_Entry &e = GetWordEntry(CastSizeToInt(i));

        for (lem::Container::size_type j = 0; j < e.forms().size(); j++)
        {
            if (e.forms()[j].name() == name)
                return Word_Coord(e.GetKey(), CastSizeToInt(j));
        }
    }

    // Найти не удалось.
    return Word_Coord(UNKNOWN, UNKNOWN);
}



void WordEntries_File::DetailedReport(OFormatter &txtfile)
{
    txtfile.printf("\n%80h-\nLexical LookUp Table:\n");
    /*
     for( std::map< SG_EntryGroup::KEY, SG_EntryGroup* >::const_iterator it=group.begin(); it!=group.end(); ++it )
      {
       it->second->Print(txtfile);
       txtfile.eol();
      }
    */

    txtfile.printf("\n\n%10h- MULTILEXEM DICTIONARY %10h-\n\n");

    txtfile.printf(
        "Multilexem dictionary contains %d unique items\n"
        , ml_ref.get_list().size()
    );

    int n_real = 0; // счетчик реально многолексемных
    int max_len = 0;
    for (lem::Container::size_type i = 0; i < ml_ref.get_list().size(); i++)
    {
        if (ml_ref.get_list()[i].Count_Lexems() > 1)
            n_real++;

        max_len = std::max(max_len, ml_ref.get_list()[i].length());
    }


    txtfile.printf("%d of them have more than 1 lexem:\n", n_real);

    txtfile.printf("Max length of a lexem=%d\n", max_len);

    for (lem::Container::size_type i4 = 0; i4 < ml_ref.get_list().size(); i4++)
        if (ml_ref.get_list()[i4].Count_Lexems() > 1)
            txtfile.printf("%us\n", ml_ref.get_list()[i4].c_str());

    txtfile.printf("%10h- END OF MULTILEXEM DICTIONARY %10h-\n");

    return;
}



#if defined SOL_COMPILER
/*************************************************************************
   Приведем имена статей и словоформ синтаксической грамматики к такому
 виду, чтобы строки содержали символы-имена статей графической грамматики.
 Для каждого исходного символа сохраняем также индекс его буквоформы в
 соответствующей статье Алфавита, и флаги ударности и проч. В итоге, мы
 будем способны распознавать входные лексемы вне зависимости от регистра,
 в котором набраны буквы. Хотя можно определить и требования именно
 определенного регистра для отдельных букв!

   Аналогичную операцию производим для Таблиц Склонений, которые по
 внутреннему представлению очень близки к словарным статьям.
*************************************************************************/
void WordEntries_File::ProcessSynEntries()
{
    // Теперь обрабатываем словарные статьи. Одновременно вычисляем
    // максимальное число лексем в мультилексемах.
    max_ml_len = 1;
    const int nword = CastSizeToInt(entry.size());

    if (!nword)
        return;

    const int dbg = true;
    if (dbg > 0)
    {
        // Длительная операция: сообщаем пользователю.
        sg->GetIO().mecho().printf("%vfESG%vn: preparing entries->");
        sg->GetIO().mecho().flush();
    }

    lem::BitArray32 presence;
    const int perc = nword / 10;

    for (int i = nword - 1; i >= 0; i--)
    {
        if (dbg > 0 && !(i%perc))
        {
            sg->GetIO().mecho().printf("%d.", i / perc);
            sg->GetIO().mecho().flush();
        }

        SG_Entry &e = GetWordEntry(i);

        e.Prepare(sg->GetDict().GetGraphGram(), *sg);

        const int len = e.GetMaxMLLen();
        max_ml_len = std::max(max_ml_len, len);

        if (len > 1)
        {
            // Статья имеет по крайней мере одну многолексемную форму, поэтому
            // ключ статьи запоминаем в векторе.
            ML_entry_key_list.push_back(e.GetKey());

            // Ещё нам придётся просмотреть все формы этой статьи и для лексемы
            // из многолексемных добавить в ещё один список (без повторов).
            const int nform = e.forms().size();

            for (int iform = 0; iform < nform; iform++)
            {
                const Lexem &form_name = e.forms()[iform].name();
                const int npart = form_name.Count_Lexems();

                if (npart > 1)
                {
                    // Да, эта словоформа имеет многолексемное имя.

                    UCStringSet parts;
                    form_name.Split(parts);

                    int nlex, ilex;
                    bool found;

                    for (int iname = 0; iname < npart; iname++)
                    {
                        const UCString &l = parts[iname];

                        nlex = ML_entry_lex_list.size();
                        found = false;

                        for (ilex = 0; ilex < nlex; ilex++)
                            if (ML_entry_lex_list[ilex] == l)
                            {
                                // Данная однолексема присутствует и в мультилексеме
                                // длины == npart 
                                ML_entry_pre_list[ilex].Set(npart);
                                found = true;
                                break;
                            }

                        // Эта лексема уникальная для списка, поэтому добавляем.
                        if (!found)
                        {
                            ML_entry_lex_list.push_back(l);
                            presence.SetData(0);
                            presence.Set(npart);
                            ML_entry_pre_list.push_back(presence);
                        }
                    } // for цикл по лексемам имени словоформы
                } // if оператор словоформа многолексемна
            } // for цикл по словоформам статьи
        } // if оператор статья содержит многолексемные формы.
    } // for цикл по всем статьям в Лексиконе

  /*
  // ---- DEBUG
  lem::mout->printf( "ML_entry_lex_list size=%d\n", ML_entry_lex_list.size() );
  for( int q=0; q<ML_entry_lex_list.size(); ++q )
   {
    if( ML_entry_lex_list[q].eqi(L"LISTEN") )
     {
      lem::CString s;
      for( int k=1; k<32; ++k )
       if( ML_entry_pre_list[q].Get(k) )
        s += '1';
       else
        s += '-';

      lem::mout->printf( "%us %s\n", ML_entry_lex_list[q].c_str(), s.c_str() );
     }
   }
  // ---- DEBUG
  */

  /*
   // Теперь выполним ещё один проход по всем статьям, и сделаем в каждой
   // пометку об участии лексем из форм этой статьи в многолексемных формах.
   // Эта информация потребуется для LA, чтобы ускорить проецирование
   // мультилексем на Лексикон.
   for( int i3=nword-1; i3>=0; i3-- )
    {
     GetWordEntry(i3).PrepareMLPresence( *sg, ML_entry_lex_list, ML_entry_pre_list );
    }
  */

    if (dbg > 0)
    {
        sg->GetIO().mecho().printf("%vfAOK%vn\n");
        sg->GetIO().mecho().flush();
    }

    return;
}
#endif


#if defined SOL_COMPILER
/****************************************************************************
   Сортировка словарных статей в алфавитном порядке, согласно расположению
 букв в Графической Грамматике, методом Шелла (быстрая сортировка).

   Доступ к статьям Синтаксической Грамматики идет через специальную
 индексную таблицу:

       таблица ientry             таблица entry
    ЪДДДДДДДДДДДДДДДДДї        ЪДДДДДДДДДДДДДДДДДї
    і±±±±±±±±±±±±±±±±±і   ЪДДД>і°°°°°статья°°°°°°і
    ГДДДДДДДДДДДДДДДДДґ   і    ГДДДДДДДДДДДДДДДДДґ
    і±±±±±±±±±±±±±±±±±іДДДЕї   і±±±±±±±±±±±±±±±±±і
    ГДДДДДДДДДДДДДДДДДґ   іі   ГДДДДДДДДДДДДДДДДДґ
 ДД>і°°индекс°статьи°°іДДДЩі   і±±±±±±±±±±±±±±±±±і
    ГДДДДДДДДДДДДДДДДДґ    і   ГДДДДДДДДДДДДДДДДДґ
    і±±±±±±±±±±±±±±±±±і    АДД>і±±±±±±±±±±±±±±±±±і
    АДДДДДДДДДДДДДДДДДЩ        АДДДДДДДДДДДДДДДДДЩ

   При сортировке таблица ientry, первоначально содержащая линейно растущие
 индексы, группируется таким образом, чтобы доступ через нее к таблице
 entry происходил так, как будто статьи отсортированы по алфавиту.
 Расположение статей в списке entry определяется порядком их чтения и не
 изменяется Транслятором, так это приведет к существенной трате ресурсов
 процессора и фрагментации ОЗУ.
******************************************************************************/

void WordEntries_File::SortUp()
{
    if (!entry.empty())
    {
        // Длительная операция: сообщаем пользователю.
        sg->GetIO().mecho().printf("%vfESG%vn: sorting up the word entries->");
        sg->GetIO().mecho().flush();
    }

    int i, j;

    int gap;
    const int N = CastSizeToInt(entry.size());

    // Сначала собираем полный список имен статей в отдельном списке
    MCollect<UCString> e_name;
    e_name.reserve(N);
    for (i = 0; i < N; i++)
        e_name.push_back(GetWordEntry(i).GetName());

    // Теперь сортируем с использованием индексного списка. Алгоритм Шелла.

    for (gap = N / 2; gap > 0; gap /= 2)
    {
        // Индикация прогресса...
        sg->GetIO().mecho().printf('.');
        sg->GetIO().mecho().flush();

        for (i = gap; i < N; i++)
            for (j = i - gap; j >= 0; j -= gap)
            {
                if (e_name[ientry[j + gap]] < e_name[ientry[j]])
                    break;

                const int idummy = ientry[j];
                ientry[j] = ientry[j + gap];
                ientry[j + gap] = idummy;
            }
    }


    key_to_index.clear();
    for (lem::Container::size_type ie = 0; ie < entry.size(); ie++)
        key_to_index.insert(std::make_pair(GetWordEntry(ie).GetKey(), ie));

    // Сортировка закончена.

    sg->GetIO().mecho().printf("%vfAOk%vn\n");
    sg->GetIO().mecho().flush();

    return;
}
#endif


void WordEntries_File::ClearGroups()
{
    /*
     for( std::map< SG_EntryGroup::KEY, SG_EntryGroup* >::iterator it=group.begin(); it!=group.end(); ++it )
      delete it->second;

     group.clear();
    */
    lookup_table.Clear();

    return;
}


// ----------------------------------------------------

namespace
{
    static bool lexem_sorter2(const std::pair<const Lexem*, int> & x, const std::pair<const Lexem*, int> & y)
    {
        return (*x.first) > (*y.first);
    }
}

void WordEntries_LookUp::InitLexems(const LexemDictionary & lexems)
{
    const int n_lexem = CastSizeToInt(lexems.size());
    lexem_slot.resize(n_lexem);

    lem::MCollect< std::pair<const Lexem*, int> > lexem2index;
    lexem2index.reserve(n_lexem);

    for (lem::Container::size_type i = 0; i < lexems.size(); ++i)
    {
        const Lexem * lexem = &lexems[i];
        lexem2index.push_back(std::make_pair(lexem, CastSizeToInt(i)));
    }

    std::sort(lexem2index.begin(), lexem2index.end(), lexem_sorter2);

    // теперь вектор sorted_lexem_index позволит перебирать лексемы в общем справочнике в отсортированном порядке.
    sorted_lexem_index.reserve(lexem2index.size());
    for (lem::Container::size_type i = 0; i < lexem2index.size(); ++i)
        sorted_lexem_index.push_back(lexem2index[i].second);

    return;
}


int WordEntries_LookUp::Findlexem(const LexemDictionary & lexems, const lem::UCString & lexem) const
{
    if (!sorted_lexem_index.empty())
    {
        int ileft = 0, iright = CastSizeToInt(sorted_lexem_index.size()) - 1;
        while ((iright - ileft) > 1)
        {
            const int imid = (iright + ileft) / 2;
            const Lexem & l = lexems[sorted_lexem_index[imid]];
            if (lexem < l)
                ileft = imid;
            else if (lexem > l)
                iright = imid;
            else
                return imid;
        }

        if (lexems[sorted_lexem_index[ileft]] == lexem)
            return ileft;
        else if (lexems[sorted_lexem_index[iright]] == lexem)
            return iright;
        else
            return UNKNOWN;
    }
    else
    {
        return UNKNOWN;
    }
}


void WordEntries_LookUp::Clear()
{
    lexem_slot.clear();
    entry_index.clear();
    sorted_lexem_index.clear();
    return;
}

void WordEntries_LookUp::SaveBin(lem::Stream & bin) const
{
    sorted_lexem_index.SaveBin(bin);
    lexem_slot.SaveBin(bin);
    entry_index.SaveBin(bin);
    return;
}

void WordEntries_LookUp::LoadBin(lem::Stream & bin)
{
    sorted_lexem_index.LoadBin(bin);
    lexem_slot.LoadBin(bin);
    entry_index.LoadBin(bin);
    return;
}


// ----------------------------------------------------


#if defined SOL_COMPILER
/******************************************************************************
   Построение таблицы разбивки по группам статей Синтаксической Грамматики
 для алгоритма быстрого поиска лексем в Словаре.

 ВНИМАНИЕ!!! Статьи желательно предварительно отсортировать по алфавиту
 вызовом метода SortUp, дабы сократить расход памяти. Утверждение основано
 на факте, что в русском языке словоизменение происходит обычно через
 окончания слов. Поэтому словоформы одной статьи обычно начинаются с той же
 буквы, что и имя статьи (хотя есть исключения, которые корректно
 учитываются).
******************************************************************************/
void WordEntries_File::BuildLookUpTable()
{
    if (!entry.empty())
    {
        // Длительная операция: сообщаем пользователю.
        sg->GetIO().mecho().printf("%vfESG%vn: building lookup tables->");
        sg->GetIO().mecho().flush();
    }

    const GraphGram &gg = sg->GetDict().GetGraphGram();

    UCString uname(SOL_UNKNOWN_ENTRY_NAME);
    UCString uname2(SOL_UNKNOWN_ENTRY2);

    const int nword = CastSizeToInt(entry.size());

    for (int ientry = 0; ientry < nword; ientry++)
    {
        SG_Entry& e = GetWordEntry(ientry);

        // Найдена еще одна специальная статья.
        if (e.GetName() == uname || e.GetName() == uname2)
            u_entry.push_back(e.GetKey());
    }


    // -------

    lookup_table.Clear();
    lookup_table.InitLexems(ml_ref);

    lem::PtrCollect< lem::MCollect<int> > lexem2entries;
    lexem2entries.resize(ml_ref.size());
    lexem2entries.Nullify();

    for (int ientry = 0; ientry < nword; ientry++)
    {
        const SG_Entry& e = GetWordEntry(ientry);

        for (lem::Container::size_type j = 0; j < e.forms().size(); ++j)
        {
            const lem::UCString & fname = e.forms()[j].name();

            const int lexem_index = lookup_table.Findlexem(ml_ref, fname);
            LEM_CHECKIT_Z(lexem_index != UNKNOWN);

            lem::MCollect<int> * entries = lexem2entries[lexem_index];
            if (entries == nullptr)
            {
                entries = new lem::MCollect<int>();
                lexem2entries[lexem_index] = entries;
            }

            if (entries->find(e.GetKey()) == UNKNOWN)
                entries->push_back(e.GetKey());
        }
    }



    std::map< int, int > entry1;

    for (lem::Container::size_type i = 0; i < lexem2entries.size(); ++i)
    {
        const lem::MCollect<int> * entries = lexem2entries[i];
        if (entries != nullptr && entries->size() == 1)
        {
            const int entry_id = entries->front();
            std::map<int, int>::iterator it = entry1.find(entry_id);
            if (it == entry1.end())
            {
                const int entry_slot = CastSizeToInt(lookup_table.entry_index.size());
                lookup_table.entry_index.push_back(entry_id);
                entry1.insert(std::make_pair(entry_id, entry_slot));
            }
        }
    }

    for (lem::Container::size_type i = 0; i < lexem2entries.size(); ++i)
    {
        const lem::MCollect<int> * entries = lexem2entries[i];

        if (entries != nullptr)
        {
            lookup_table.lexem_slot[i].len = CastSizeToInt(entries->size());

            if (entries->size() == 1)
            {
                LEM_CHECKIT_Z(entry1.find(entries->front()) != entry1.end());
                lookup_table.lexem_slot[i].start_index = entry1.find(entries->front())->second;
            }
            else
            {
                lookup_table.lexem_slot[i].start_index = CastSizeToInt(lookup_table.entry_index.size());
                for (lem::Container::size_type j = 0; j < entries->size(); ++j)
                {
                    lookup_table.entry_index.push_back(entries->get(j));
                }
            }
        }
    }

    /*
     lem::Ptr<SymbolEnumerator> senum( gg.entries().Enumerate() );
     int max_id_char=0;
     while( senum->Fetch() )
      {
       const int id_char = senum->GetId();
       max_id_char = std::max( max_id_char, id_char );
      }

     ClearGroups();

     u_entry.clear();

     // По всем статьям Синтаксической Грамматики...

     std::set<SG_EntryGroup::KEY> pref_in_entry;
     lem::PtrCollect< lem::IntArray > tmp_entries;
     std::map< SG_EntryGroup::KEY, lem::IntArray* > tmp_prefix2entries;

     for( int ientry=0; ientry<nword; ientry++ )
      {
       SG_Entry& e = GetWordEntry(ientry);

       // Найдена еще одна специальная статья.
       if( e.GetName()==uname || e.GetName()==uname2 )
        u_entry.push_back( e.GetKey() );

       pref_in_entry.clear();
       for( lem::Container::size_type j=0; j<e.forms().size(); ++j )
        {
         const lem::UCString &fname = e.forms()[j].name();
         SG_EntryGroup::KEY prefix( SG_EntryGroup::BuildKey(fname) );
         pref_in_entry.insert(prefix);
        }

       for( std::set<SG_EntryGroup::KEY>::const_iterator it=pref_in_entry.begin(); it!=pref_in_entry.end(); ++it )
        {
         const SG_EntryGroup::KEY &prefix = *it;
         std::map< SG_EntryGroup::KEY, lem::IntArray* >::iterator it2 = tmp_prefix2entries.find(prefix);
         if( it2==tmp_prefix2entries.end() )
          {
           lem::IntArray *x = new lem::IntArray();
           x->push_back( ientry );
           tmp_entries.push_back(x);
           tmp_prefix2entries.insert( std::make_pair(prefix,x) );
          }
         else
          {
           it2->second->push_back( ientry );
          }
        }
      }

     int n_unpacked_entry_indeces=0;
     int n_packed_entry_indeces=0;
     for( std::map< SG_EntryGroup::KEY, lem::IntArray* >::const_iterator it=tmp_prefix2entries.begin(); it!=tmp_prefix2entries.end(); ++it )
      {
       const SG_EntryGroup::KEY & prefix = it->first;
       const lem::IntArray & ies = *it->second;

       SG_EntryGroup *g = new SG_EntryGroup( prefix, ies );

       n_unpacked_entry_indeces += g->GetUnpackedListLength();
       n_packed_entry_indeces += g->GetPackedListLength();

       group.insert( std::make_pair( g->GetKey(), g ) );
      }


     sg->GetIO().mecho().printf( " %vfA%d%vn prefixes, compression=%vfA%d/%d%vn ", CastSizeToInt(group.size()), n_unpacked_entry_indeces, n_packed_entry_indeces );
     sg->GetIO().mecho().flush();
    */

    sg->GetIO().mecho().printf("%vfAOK%vn\n");
    sg->GetIO().mecho().flush();

    return;
}
#endif


void WordEntries_File::CommitCompilation(lem::OFormatter &err)
{
#if defined SOL_COMPILER
    const int nentry = CastSizeToInt(entry.size());

    // Зарезервируем место во вспомогательных векторах на всякий случай,
    // чтобы потом быстро заполнять их.
    ML_entry_key_list.clear();
    ML_entry_lex_list.clear();
    ML_entry_pre_list.clear();
    ML_entry_key_list.reserve(nentry / 8);
    ML_entry_lex_list.reserve(nentry / 8);
    ML_entry_pre_list.reserve(nentry / 8);

    // Не должно быть unresolved ссылок на статьи, то есть для всех [extern entry]
    // операторов должны быть полные определения [entry].
    // Выводим весь список нереализоанных статей, а затем уже прерываем
    // работу программы.
    int n_unrealized = 0;
    lem::Ptr<WordEntryEnumerator> wenum(ListEntries());
    while (wenum->Fetch())
    {
        const SG_Entry &e = wenum->GetItem();
        if (!e.IsRealized())
        {
            const UCString& entry_name = e.GetName();
            const UCString &class_name = sg->GetClass(e.GetClass()).GetName();

            sg->GetIO().merr().printf(
                "%vfDEntry [%us:%us] not realized in Lexicon%vn\n"
                , class_name.c_str(), entry_name.c_str()
            );

            lem::LogFile::logfile->printf(
                "%vfDEntry [%us:%us] not realized in Lexicon%vn\n"
                , class_name.c_str(), entry_name.c_str()
            );
            n_unrealized++;
        }
    }

    if (n_unrealized)
    {
        sg->GetIO().merr().printf("There are %d unrealized entries\n", n_unrealized);
        lem::LogFile::logfile->flush();
        throw E_ParserError();
    }

    // Все предопределённые статьи должны быть описаны и их ключи - известны.
    for (int j = 0; j < DIM_A(predefined_entry); j++)
        if (predefined_entry[j] == UNKNOWN)
        {
            sg->GetIO().merr().printf(
                "%vfDPredefined entry with index %s is not described.%vn\n"
                , lem::to_str(j).c_str()
            );
            throw E_ParserError();
        }

    ProcessSynEntries();
    SortUp();
    BuildLookUpTable();
#endif

    return;
}


LD_Seeker* WordEntries_File::Get_Seeker()
{
    return ml_ref.Get_Seeker(*sg, &sg->GetDict().GetLexAuto());
}


#if defined SOL_LOADBIN
LD_Seeker* WordEntries_File::Load_Seeker(lem::Stream &bin)
{
    return ml_ref.Load_Seeker(bin, &sg->GetDict().GetLexAuto());
}
#endif

const Lexem* WordEntries_File::AddLexeme(const Solarix::Lexem &lex)
{
#if defined SOL_LOADTXT
    return ml_ref.Add(lex);
#else
    return nullptr;
#endif
}

const CP_Array* WordEntries_File::AddCoordPairs(const CP_Array &x)
{
    return coord_ref.Add(x);
}


const SG_Entry& WordEntries_File::GetEntryByKey(int key)
{
    return GetWordEntry(FindEntryIndexByKey(key));
}

int WordEntries_File::FindEntryIndexByKey(int key) const
{
#if LEM_DEBUGGING==1
    if (
        key == UNKNOWN ||
        !key_to_index.count(key) ||
        key_to_index.find(key) == key_to_index.end()
        )
        throw E_RunTime();
#endif

    return key_to_index.find(key)->second;
}

int WordEntries_File::size() const
{
    return CastSizeToInt(entry.size());
}


int WordEntries_File::FindEntryOmonym(const Lexem& lname, int iclass, const Solarix::GramCoordPair &p)
{
#if defined SOL_LOADTXT && defined SOL_COMPILER
    if (iclass != ANY_STATE && iclass != UNKNOWN)
    {
        UCString uname = to_upper(lname);

        typedef std::multimap< std::pair<UCString, int>, int >::const_iterator IT;
        std::pair<IT, IT> r = entry_class_lookup.equal_range(std::make_pair(uname, iclass));
        for (IT it = r.first; it != r.second; ++it)
        {
            // Найденный омоним имеет нужную координатную пару?
            const int ekey = it->second;

            const Solarix::SG_Entry &e = GetEntryByKey(ekey);

            const int istate = e.GetAttrState(Solarix::GramCoordAdr(p.GetCoord()));
            if (istate == p.GetState())
            {
                // да - возвращаем
                return ekey;
            }
        }
    }
#endif

    return UNKNOWN;
}


int WordEntries_File::FindEntryOmonym(const Lexem& lname, int iclass, const lem::MCollect<Solarix::GramCoordPair> &p)
{
#if defined SOL_LOADTXT && defined SOL_COMPILER
    if (iclass != ANY_STATE && iclass != UNKNOWN)
    {
        UCString uname = to_upper(lname);

        typedef std::multimap< std::pair<UCString, int>, int >::const_iterator IT;
        std::pair<IT, IT> r = entry_class_lookup.equal_range(std::make_pair(uname, iclass));
        for (IT it = r.first; it != r.second; ++it)
        {
            // Найденный омоним имеет нужную координатную пару?
            const int ekey = it->second;

            const Solarix::SG_Entry &e = GetEntryByKey(ekey);
            bool all = true;
            for (lem::Container::size_type k = 0; k < p.size(); ++k)
            {
                const int istate = e.GetAttrState(p[k].GetCoord());
                if (istate != p[k].GetState())
                {
                    all = false;
                    break;
                }
            }

            if (all)
            {
                // да - возвращаем
                return ekey;
            }
        }
    }
#endif

    return UNKNOWN;
}




int WordEntries_File::FindEntryOmonym(const Lexem& lname, int iclass, const ExactWordEntryLocator &locator)
{
#if defined SOL_LOADTXT && defined SOL_COMPILER
    if (iclass != ANY_STATE && iclass != UNKNOWN)
    {
        UCString uname = to_upper(lname);

        typedef std::multimap< std::pair<UCString, int>, int >::const_iterator IT;
        std::pair<IT, IT> r = entry_class_lookup.equal_range(std::make_pair(uname, iclass));
        for (IT it = r.first; it != r.second; ++it)
        {
            // Найденный омоним имеет нужную координатную пару?
            const int ekey = it->second;

            const Solarix::SG_Entry &e = GetEntryByKey(ekey);
            const bool all = locator.Check(e, *sg);

            if (all)
            {
                // да - возвращаем
                return ekey;
            }
        }
    }
#endif

    return UNKNOWN;
}




#if defined SOL_LOADTXT
int WordEntries_File::LoadEntry(lem::StrParser<lem::UFString> &txt)
{
    // считываем шапку статьи - ее имя и класс
    // entry имя : класс
    txt.read_it(L"entry");

    UFString ename2;
    while (!txt.eof())
    {
        UFString t = txt.read();
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
    sg->GetDict().GetLexAuto().TranslateLexem(entry_name, false);
    entry_name.Translate(sg->GetDict().GetGraphGram(), 2);

    lem::UFString cname = txt.read();
    int id_class = sg->FindClass(cname.c_str());
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
    e->LoadBody(*sg, txt);

    e->PrepareAfterLoad(sg->GetDict().GetGraphGram(), *sg);

    e->SetKey(sg->GetDict().GetNextKey());

    const int ie = CastSizeToInt(entry.size());
    ientry.push_back(ie);
    entry.push_back(e);

    // регистрируем новую статью в поисковых списках
    key_to_index.insert(std::make_pair(e->GetKey(), ie));

    // TODO ...
    LEM_STOPIT;
    /*
     SG_EntryGroup::KEY ek( SG_EntryGroup::BuildKey(entry_name) );
     std::map< SG_EntryGroup::KEY, SG_EntryGroup* >::const_iterator it = group.find( ek );
     if( it!=group.end() )
      {
       it->second->AddEntry(ie);
      }
     else
      {
       SG_EntryGroup *g = new SG_EntryGroup( ek );
       g->AddEntry(ie);
       group.insert( std::make_pair( ek, g ) );
      }
    */

    return e->GetKey();
}
#endif


int WordEntries_File::CreateEntry(const lem::UCString &ename, int id_class)
{
#if defined SOL_LOADTXT
    SG_Entry *e = new SG_Entry(ename, id_class, ml_ref);
    e->SetKey(sg->GetDict().GetNextKey());

    if (ename == SOL_UNKNOWN_ENTRY_NAME)
        e->SetQuantor();

    AddAutoCreated(e);
    return e->GetKey();
#else
    return UNKNOWN;
#endif
}

LexemeEnumerator* WordEntries_File::ListLexemes()
{
    return new LexemeEnumerator_File(this);
}


int WordEntries_File::CountLexemes()
{
    return CastSizeToInt(ml_ref.size());
}

const Lexem* WordEntries_File::ReattachLexeme(const Lexem *ptr)
{
    return ml_ref.reattach(ptr);
}

const CP_Array* WordEntries_File::ReattachCoordPairs(const CP_Array *ptr)
{
    return coord_ref.reattach(ptr);
}

const IntCollect& WordEntries_File::GetUEntries()
{
    return u_entry;
}


void WordEntries_File::LoadEntry(int index)
{
    if (!lazy_load)
        return;

#if defined LEM_THREADS
    lem::Process::CritSecLocker lock(&cs);
#endif

    if (entry[index] == nullptr)
    {
        if (entries_bin.IsNull())
            entries_bin = new lem::BinaryReader(entries_path);

        entries_bin->seekp(entry_pos[index]);
        SG_Entry *e = new SG_Entry();
        e->LoadBin(*entries_bin);

        if (e != bogus_entry)
            e->ReattachToRefs(*sg);

        entry[index] = e;
    }

    return;
}


void WordEntries_File::SetLazyLoad(const lem::Path & morphology_path)
{
    lazy_load = true;
    entries_path = morphology_path;
    return;
}

bool WordEntries_File::PreferPrefixSearch()
{
    return true;
}


int WordEntries_File::GetUnknownEntryKey()
{
    for (lem::Container::size_type i = 0; i < u_entry.size(); ++i)
    {
        const SG_Entry &e = GetEntryByKey(u_entry[i]);
        if (e.GetName() == SOL_UNKNOWN_ENTRY2)
            return u_entry[i];
    }

    LEM_STOPIT;
    return UNKNOWN;
}
