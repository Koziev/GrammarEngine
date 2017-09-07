#include <lem/unicode.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/word_form.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/casing_coder.h>
#include "Lemmatizer2.h"

using namespace Solarix;

Lemmatizer2::Lemmatizer2()
{
    loaded = false;
}


Lemmatizer2::~Lemmatizer2()
{
    typedef XTAG2LEMMA_BUILDER::iterator IT;
    for(IT it = Xtag2lemma_builder.begin(); it != Xtag2lemma_builder.end(); ++it)
    {
        delete it->second;
    }


    return;
}


void Lemmatizer2::Load( const lem::Path & model_folder )
{
    loaded = true;

    // --------------------------------------------------------- 

    lem::Path codebook_file = model_folder;
    codebook_file.ConcateLeaf( L"lemmatizer.codebook" );

    lem::BinaryReader rdr_codebook( codebook_file );
    codebook.LoadBin( rdr_codebook );

    // --------------------------------------------------------- 

    lem::Path model_file = model_folder;
    model_file.ConcateLeaf( L"lemmatizer.model" );

    lem::BinaryReader rdr( model_file );

    lem::int32_t flags;
    rdr.read( &flags, sizeof( flags ) );
    LEM_CHECKIT( flags == 1 );

    //lem::int32_t total_strings_length;
    //rdr.read( &total_strings_length, sizeof(total_strings_length) );

    lem::int32_t n_tags;
    rdr.read( &n_tags, sizeof( n_tags ) );

    lem::int32_t tag;
    EndingMinMaxLen mm;
    for(int i = 0; i < n_tags; ++i)
    {
        rdr.read( &tag, sizeof( tag ) );
        rdr.read( &mm.min_len, sizeof( mm.min_len ) );
        rdr.read( &mm.max_len, sizeof( mm.max_len ) );
        Xtag2ending_len.insert( std::make_pair( tag, mm ) );
    }

    rdr.read( &n_tags, sizeof( n_tags ) );
    for(int i = 0; i < n_tags; ++i)
    {
        rdr.read( &tag, sizeof( tag ) );

        lem::int32_t n_pair;
        rdr.read( &n_pair, sizeof( n_pair ) );

        LEMMA_BUILDERS * mx = new LEMMA_BUILDERS;

        for(int j = 0; j < n_pair; ++j)
        {
            lem::UCString wordform_ending = LoadStr( rdr );
            lem::int32_t n_rules;
            rdr.read( &n_rules, sizeof( n_rules ) );

            lem::MCollect< lem::triple<lem::UCString/*wordform_prefix*/, lem::UCString/*lemma_prefix*/, lem::UCString/*lemma_ending*/> > rules;
            for(int irule = 0; irule < n_rules; ++irule)
            {
                lem::UCString wordform_prefix = LoadStr( rdr );
                lem::UCString lemma_prefix = LoadStr( rdr );
                lem::UCString lemma_ending = LoadStr( rdr );
                rules.push_back( lem::make_triple( wordform_prefix, lemma_prefix, lemma_ending ) );
            }

            mx->insert( std::make_pair( wordform_ending, rules ) );
        }

        Xtag2lemma_builder.insert( std::make_pair( tag, mx ) );
    }

    return;
}


lem::UCString Lemmatizer2::LoadStr( lem::BinaryReader & bin )
{
    lem::uint8_t utf8_len = 0;
    bin.read( &utf8_len, sizeof( utf8_len ) );

    lem::uint8_t buffer[lem::UCString::max_len * 6 + 1];
    bin.read( buffer, utf8_len );
    buffer[utf8_len] = 0;
    lem::FString utf8( (const char*)buffer );
    return lem::UCString( lem::from_utf8( utf8 ).c_str() );
}


static lem::UCString cut_prefix_ending( const lem::UCString & word, int prefix_len, int ending_len )
{
    int i1 = prefix_len;
    int i2 = word.length() - ending_len - 1;
    lem::UCString res;
    for(int i = i1; i <= i2; ++i)
    {
        res.Add_Dirty( word[i] );
    }

    res.calc_hash();
    return res;
}

void Lemmatizer2::Lemmatize( const Solarix::Word_Form & wordform, lem::UFString & lemma, Solarix::Dictionary & dict ) const
{
    const lem::UCString & word = *wordform.GetName();

    if(!loaded)
    {
        lemma = word.c_str();
        return;
    }


    if(lem::is_udigit( word.front() ) || lem::is_upunct( word.front() ))
    {
        lemma = word.c_str();
        return;
    }

    int id_entry = wordform.GetEntryKey();
    if(dict.GetSynGram().GetUEntries().find( id_entry ) == UNKNOWN)
    {
        const SG_Entry & e = dict.GetSynGram().GetEntry( id_entry );
        lemma = e.GetName().c_str();

        CasingCoder & cc = dict.GetLexAuto().GetCasingCoder();
        const int icasing = e.GetAttrState( Solarix::GramCoordAdr( cc.icoord_casing ) );
        cc.RestoreCasing( icasing, lemma, id_entry );

        return;
    }


    const ModelTagMatcher * tag = codebook.Match( &wordform, dict );
    if(tag == NULL)
    {
        lem::MemFormatter mem;
        mem.printf( "Can not match tag for wordform: " );
        wordform.Print( mem, &(dict.GetSynGram()), true );
        lem::UFString str_err = mem.string();
        throw E_BaseException( str_err );
    }

    lem::UCString u_wordform = lem::to_lower( word );

    const int tag_id0 = tag->GetId();

    for(int pass = 0; pass < 2; ++pass)
    {
        // Делаем два прохода по справочнику правил лемматизации.
        // Сначала пытаемся подобрать правило для тега словоформы.
        // Если не получилось - ищем среди всех правил без привязки к тегу.
        const int tag_id = pass == 0 ? tag_id0 : -1;

        XTAG2LEMMA_BUILDER::const_iterator it = Xtag2lemma_builder.find( tag_id );
        if(it != Xtag2lemma_builder.end())
        {
            const EndingMinMaxLen & range = Xtag2ending_len.find( tag_id )->second;

            for(int ending_len = range.max_len; ending_len >= range.min_len; --ending_len)
            {
                if(u_wordform.length() >= ending_len)
                {
                    lem::UCString wordform_ending = lem::right( u_wordform, ending_len );

                    LEMMA_BUILDERS::const_iterator it2 = it->second->find( wordform_ending );
                    if(it2 != it->second->end())
                    {
                        // Надо выбрать правило с учетом префикса.
                        for(lem::Container::size_type irule = 0; irule < it2->second.size(); ++irule)
                        {
                            const lem::UCString & wordform_prefix = it2->second[irule].first;
                            if(u_wordform.eq_beg( wordform_prefix ))
                            {
                                lemma = (
                                    it2->second[irule].second + // новый префикс леммы
                                    cut_prefix_ending( word, wordform_prefix.length(), ending_len ) + // отсекаем от словоформы приставку и окончание
                                    it2->second[irule].third
                                    ).c_str();
                                break;
                            }
                        }
                        return;
                    }
                }
            }
        }
    }

    lemma = word.c_str();

    return;
}
