#if defined SOL_EXPORT_SQL

#include <lem/solarix/dictionary.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/version.h>

using namespace lem;
using namespace Solarix;


void Dictionary::Save_SQL(
                          OFormatter &txt,
                          OFormatter &txt2,
                          const SQL_Production &sql_version
                         )
{
 txt.printf(
            "%s This SQL script is generated [%us] by DECOMPILER ver. %s for '%s' RDBMS\n"
            "%s (c) by Elijah Koziev\n"
            "%s More info at http://www.solarix.ru/for_developers/docs/sql_dictionary.shtml\n"
            , sql_version.Get_Comment().c_str()
            , timestamp().c_str()
            , sol_get_version().c_str()
            , sql_version.Get_Version().c_str()
            , sql_version.Get_Comment().c_str()
            , sql_version.Get_Comment().c_str()
           );


 // Список таблиц, которые надо удалить перед созданием нового словаря. Порядок важен!
 const char* table_names[]={
                            "kb_argument_point",
                            "kb_fact",
                            "kb_facts",
                            "kb_fact_index1",
                            "kb_fact_index2",
                            "generic_tree_scorer",
                            "ts_predicate",
                            "ts_head_word",
                            "ts_head_lemma",
                            "ts_point",
                            "ts_group",
                            "ts_group2root",
                            "word_assoc",
                            "predicate_template",
                            "crop_rule",
                            "recog_rule",
                            "tr_functions",
                            "ph_rule",
                            "word_entry_set",
                            "unbreakable",
                            "SynPatternTree",
                            "src_filename",
                            "src_location",
                            "word_set",
                            "wordform_set",
                            "wordform_set_coords",
                            "wordform_set_item",
                            "collocation_set_item",
                            "collocation_headword",
                            "collocation_set",
                            "lang_usage",
                            "omonym",
                            "metaentry",
                            "metaentry_item",
                            "abc_operation_item",
                            "abc_operation",
                            "slb_result_point",
                            "slb_condition_point",
                            "slb_rule",
                            "endings",
                            "ending_stat",
                            "wordform_frequency",
                            "misspelling",
                            "aux_form",
                            "aux_entry_data",
                            "aux_form_types",
                            "aux_word",
                            "tnotes",
                            "sg_tlink_flag",
                            "cplx_left",
                            "sg_tlink_tag",
                            "sg_tlink",
                            "sg_tentry",
                            "sg_link_tag",
                            "sg_link",
                            "sg_entry_coord",
                            "sg_form_coord",
                            "sg_class_coord",
                            "class_attr_def",
                            "sg_form",
                            "unknown_entries",
                            "predef_entries",
                            "sg_entry",
                            "sg_lexem",
                            "lang_alphabet",
                            "lang_link",
                            "lang_param",
                            "sg_state",
                            "sg_coord",
                            "sg_tag_value",
                            "sg_tag",
                            "coord_pairs",
                            "multilexem",
                            "tag_set",
                            "paradigma_name",
                            "paradigma_form",
                            "paradigma",
                            "sg_class",
                            "sg_language",
                            "sg_criterion",
                            "abc_class_coord",
                            "abc_form",
                            "abc_entry",
                            "abc_class",
                            "abc_pair",
                            "abc_pairs",
                            "abc_state",
                            "abc_coord",
                            "abc_alphabet",
                            "abc_criterion",
                            NULL };


 if( !sql_version.noschema )
  {
   // СОЗДАНИЕ ТАБЛИЦ

   if( sql_version.type==SQL_Production::Oracle )
    {
     txt.printf( "SET AUTOCOMMIT OFF;\n" );

     const int lexlen = lem::UCString::max_len*2+2;

     int itable=0;
     while( table_names[itable]!=NULL )
     {
      txt.printf( "%us\n", sql_version.DropTable( table_names[itable] ).c_str() );
      itable++;
     }


     txt.printf(
                "drop sequence g_sg_lexem;\n"
               );

     txt.printf(
                "drop sequence g_sg_entry;\n"
                "drop sequence g_sg_link;\n"
                "drop sequence g_sg_link_tag;\n"
                "drop sequence g_sg_tlink;\n"
                "drop sequence g_sg_tlink_tag;\n"
                "drop sequence g_sg_tlink_flag;\n"
                "drop sequence g_sg_tentry;\n"
                "drop sequence g_tnotes;\n"
                "drop sequence g_cplx_left;\n"
                "drop sequence g_multilexem;\n"
                "drop sequence g_coord_pairs;\n"
                "drop sequence g_tag_set;\n"
                "commit;\n"
                "\n"
               );

     if( !sql_version.IsDemo() )
      {
       txt.printf(
                  "drop sequence g_aux_form_types;\n"
                  "drop sequence g_aux_form;\n"
                  "drop sequence g_aux_entry_data;\n"
                  "commit;\n"
                  "\n"
                 );
       }

     txt.printf(
                "create table endings( id number not null, ending nvarchar2(40) not null, id_language number not null, nform number not null, sumfreq number not null, constraint pk_endings primary key(id) );\n"
                "create table ending_stat( id_language number not null, max_len number not null, constraint pk_ending_stat primary key(id_language) );\n"
                "create table wordform_frequency( id number not null, id_entry number not null, iform number not null, freq number not null, constraint pk_wordform_frequency primary key(id) );\n"

                "create table misspelling( id number not null, id_language number not null, original_word nvarchar2(64) not null, substitution nvarchar2(64) not null, constraint pk_misspelling primary key(id) );\n"

                "create table coord_pairs( id number not null, pairs nvarchar2(1000), str_pairs nvarchar2(1000), constraint pk_coord_pairs primary key(id) );\n"
                "create table tag_set( id number not null, tags nvarchar2(1000), constraint pk_tag_set primary key(id) );\n"

                "create table sg_language( id number not null, name nvarchar2(64) not null unique, constraint pk_sg_language primary key (id) );\n"
                "create table lang_alphabet( id number not null, id_language number not null, id_alphabet number not null, ordering number not null, constraint pk_lang_alphabet primary key (id) );\n"
                "create table lang_link( id number not null, id_language number not null, id_state number not null, id_language2 number not null, constraint pk_lang_link primary key (id) );\n"
                "create table lang_param( id number not null, id_language number not null, param_name varchar2(32) not null, param_value varchar2(200) default '', ordering number not null, constraint pk_lang_param primary key (id) );\n"
                "create table sg_lexem( id number(11) not null, name nvarchar2(64) not null, constraint pk_sg_lexem primary key (id) );\n"
                "create table sg_coord( id number not null, name nvarchar2(64) not null, bistable number not null, constraint pk_sg_coord primary key (id) );\n"
                "create table sg_state( id number not null, id_coord number not null, name nvarchar2(64) not null, id_parent number not null, weight number not null, constraint pk_sg_state primary key (id,id_coord) );\n"
                "create table sg_class( id number not null, name nvarchar2(64) not null, name_aliase nvarchar2(64), id_lang number, weight number not null, closed_class number not null, constraint pk_sg_class primary key (id) );\n"
                "create table sg_entry( id number(11) not null, name nvarchar2(64) not null, uname nvarchar2(64) not null, id_class number not null, freq number, exportable number, flags number default 0 not null, dic_div char(4) default '', constraint pk_sg_entry primary key (id) );\n"
                "create table unknown_entries( id number(11) not null, constraint pk_unknown_entries primary key (id) );\n"
                "create table predef_entries( id number not null, id_entry number(11) not null, constraint pk_predef_entries primary key (id) );\n"
                "create table sg_form( id_entry number(11) not null, iform number(11) not null, name nvarchar2(64) not null, id_lexem number(11) not null, id_dims number(11), constraint pk_sg_form primary key (id_entry,iform) );\n"
                "create table sg_link( id number not null, id_entry1 number(11) not null, id_entry2 number(11) not null, icoord number not null, istate number not null, tags number, dic_div char(4) default '', constraint pk_sg_link primary key (id) );\n"
                "create table sg_entry_coord( id_entry number(11) not null, icoord number not null, istate number not null );\n"
                "create table sg_form_coord( id_entry number(11) not null, iform number(11) not null, icoord number not null, istate number not null );\n"

                "create table sg_class_coord( id_class number not null, id_coord number not null, coord_type number not null );\n"
                "create table class_attr_def( id number not null, id_class number not null, id_coord number not null, default_state number not null );\n"

                "create table sg_tag( id number not null, name nvarchar2(64) not null unique, constraint pk_sg_tag primary key (id) );\n"
                "create table sg_tag_value( id_tag number not null, ivalue number not null, name nvarchar2(64) not null, constraint pk_sg_tag_value primary key (id_tag,ivalue) );\n"
                "create table sg_link_tag( id number not null, id_link number not null, id_tag number not null, ivalue number not null );\n"
                "create table sg_tentry( te_id number not null, te_text nvarchar2(2000) not null, te_utxt nvarchar2(2000) not null, te_text32 nvarchar2(32), te_id_language number, te_id_class number, te_syntax_flags number, dic_div char(4) default '', constraint pk_sg_tentry primary key (te_id) );\n"
                "create table sg_tlink( tl_id number not null, tl_te_id1 number not null, tl_te_id2 number not null, tl_icoord number not null, tl_istate number not null, tl_tags number, dic_div char(4) default '', constraint pk_sg_tlink primary key (tl_id) );\n"
                "create table sg_tlink_tag( tlt_id number not null, tlt_tl_id number not null, tlt_id_tag number not null, tlt_ivalue number not null, constraint pk_sg_tlink_tag primary key (tlt_id) );\n"
                "create table cplx_left( cl_id number not null, cl_headword nvarchar2(64) not null, cl_minlen number not null, cl_maxlen number not null, constraint pk_cplx_left primary key(cl_id) );\n"
                "create table tnotes( tn_id number not null, tn_te_id number not null, tn_type number not null, tn_format number not null, tn_data nvarchar2(1000) not null, constraint pk_tnotes primary key(tn_id) );\n"
                "create table sg_tlink_flag( tlf_id number not null, tlf_tl_id number not null, tlt_flag nvarchar2(32) not null, tlf_value nvarchar2(32) not null, constraint pk_sg_tlink_flag primary key (tlf_id) );\n"
               );


     txt.printf(
                "create table aux_form_types( id number not null, name nvarchar2(32) not null, constraint pk_aux_form_types primary key(id) );\n"
                "create table aux_form( id number not null, id_entry number not null, iform number not null, data_type number not null, data_text nvarchar2(200), constraint pk_aux_form primary key(id) );\n"
                "create table aux_entry_data( id number not null, id_entry number not null, data_type number not null, data_text nvarchar2(200) not null, constraint pk_aux_entry_data primary key(id) );\n"
               );

     txt.printf(
                "CREATE TABLE aux_word(\n"
                "id number PRIMARY KEY,\n"
                "aux_type number NOT NULL,\n"
                "src nvarchar2(30),\n"
                "res nvarchar2(200)\n"
                ");\n\n"
               );


     txt.printf(
                "create table multilexem( id number(11) not null, txt nvarchar2(64) not null, headword nvarchar2(64) not null, n_lexem number not null, constraint pk_multilexem primary key (id) );\n"
                "create table sg_criterion( id number(10) not null, name nvarchar2(64) not null, strval nvarchar2(100) not null, constraint pk_sg_criterion primary key (id) );\n"
                "\n"
               );

     txt.printf(
                "CREATE TABLE paradigma( "
                " id number NOT NULL,"
                " front_name nvarchar2(32),"
                " r_condition nvarchar2(256),"
                " id_class number,"
                " attrs nvarchar2(100),"
                " constraint pk_paradigma primary key (id)"
                ");\n\n"
  
                "CREATE TABLE paradigma_name( "
                " id number NOT NULL,"
                " id_paradigma number not null,"
                " name nvarchar2(32),"
                " uname nvarchar2(32),"
                " constraint pk_paradigma_name primary key (id)"
                ");\n\n"
  
                "CREATE TABLE paradigma_form( "
                " id number NOT NULL,"
                " id_paradigma number NOT NULL,"
                " rx_condition nvarchar2(100),"
                " flexer_flags nvarchar2(100),"
                " lexem_generator nvarchar2(100),"
                " dims nvarchar2(256),"
                " constraint pk_paradigma_form primary key (id)"
                ");\n\n"
               );


     txt.printf(
                "CREATE TABLE word_entry_set( "
                " id number not null,"
                " name nvarchar2(32) NOT NULL,"
                " ies CLOB,"
                " constraint pk_word_entry_set primary key (id)"
                ");\n\n"

                "CREATE TABLE word_set( "
                " id number NOT NULL,"
                " name nvarchar2(32) NOT NULL,"
                " case_sensitive number NOT NULL,"
                " words BLOB NOT NULL,"
                " constraint pk_word_set primary key (id)"
                ");\n\n"

                "CREATE TABLE collocation_set( "
                " id number NOT NULL,"
                " name nvarchar2(32) NOT NULL,"
                " case_sensitive number NOT NULL,"
                " constraint pk_collocation_set primary key (id)"
                ");\n\n"

                "CREATE TABLE collocation_set_item( "
                " id number NOT NULL,"
                " id_set number NOT NULL,"
                " words nvarchar2(250) NOT NULL,"
                " n_word number NOT NULL,"
                " headword nvarchar2(30) NOT NULL,"
                " constraint pk_collocation_set_item primary key (id)"
                ");\n\n"

                "CREATE TABLE collocation_headword( "
                " id number NOT NULL,"
                " headword nvarchar2(32) NOT NULL,"
                " min_len number NOT NULL,"
                " max_len number NOT NULL,"
                " constraint pk_collocation_headword primary key (id)"
                ");\n\n"


                "CREATE TABLE kb_facts(\n"
                " id number PRIMARY KEY NOT NULL,\n"
                " id_language number NOT NULL,\n"
                " name nvarchar2(100) NOT NULL,\n"
                " n_arg number NOT NULL,\n"
                " n_ret number NOT NULL,\n"
                " ret_type number NOT NULL,\n"
                " query_mode number NOT NULL,\n"
                " violation_score number NOT NULL,\n"
                " violation_handler number NOT NULL\n"
                ");\n\n"


                "CREATE TABLE kb_fact(\n"
                " id number PRIMARY KEY NOT NULL,\n"
                " id_group number NOT NULL,\n"
                " boolean_return number,\n"
                " false_score number,\n"
                " integer_return number\n"
                ");\n\n"

                "CREATE TABLE kb_fact_index1(\n"
                " id number PRIMARY KEY NOT NULL,\n"
                " id_group number NOT NULL,\n"
                " id_fact number NOT NULL,\n"
                " word1 nvarchar2(32),\n"
                " word2 nvarchar2(32),\n"
                " word3 nvarchar2(32),\n"
                " word4 nvarchar2(32),\n"
                " word5 nvarchar2(32)\n"
                ");\n\n"


                "CREATE TABLE kb_fact_index2(\n"
                " id number PRIMARY KEY NOT NULL,\n"
                " id_group number NOT NULL,\n"
                " id_fact number NOT NULL,\n"
                " id_entry1 number,\n"
                " id_entry2 number,\n"
                " id_entry3 number,\n"
                " id_entry4 number,\n"
                " id_entry5 number\n"
                ");\n\n"


                "CREATE TABLE kb_argument_point( \n"
                " id number PRIMARY KEY NOT NULL,\n"
                " id_fact number,\n"
                " argument_index number NOT NULL,\n"
                " word_text nvarchar2(100),\n"
                " id_entry number,\n"
                " id_class number,\n"
                " is_regex number NOT NULL,\n"
                " case_sensitive number NOT NULL,\n"
                " id_metaentry number NOT NULL,\n"
                " wordentryset_name varchar(100),\n"
                " wordset_name nvarchar2(100),\n"
                " n_coords number,\n"
                " id_coord1 number,\n"
                " id_state1 number,\n"
                " affirm1 number,\n"
                " id_coord2 number,\n"
                " id_state2 number,\n"
                " affirm2 number,\n"
                " id_coord3 number,\n"
                " id_state3 number,\n"
                " affirm3 number,\n"
                " id_coord4 number,\n"
                " id_state4 number,\n"
                " affirm4 number,\n"
                " thesauruscheck_link number,\n"
                " thesauruscheck_entry number,\n"
                "  is_positive number NOT NULL\n"
                " );\n\n"

                "CREATE TABLE wordform_set( "
                " id number PRIMARY KEY NOT NULL,"
                " name nvarchar2(32) NOT NULL"
                ");\n"
 
                "CREATE TABLE wordform_set_item( "
                " id number PRIMARY KEY NOT NULL,"
                " id_set number NOT NULL,"
                " word nvarchar2(32) NOT NULL,"
                " id_entry number NOT NULL,"
                " id_coords number NOT NULL"
                ");\n"
 
                "CREATE TABLE wordform_set_coords( "
                " id number PRIMARY KEY NOT NULL,"
                " coords varchar2(200) NOT NULL"
                ");\n\n"
               );


     txt.printf(
                "CREATE TABLE generic_tree_scorer(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_head_point integer NOT NULL,\n"
                " id_group integer NOT NULL,\n"
                " score_expr varchar2(100),\n"
                " score_type integer NOT NULL\n"
                ");\n\n"

                "CREATE TABLE ts_predicate(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_point integer NOT NULL,\n"
                " func_name varchar(20) NOT NULL,\n"
                " narg integer NOT NULL,\n"
                " id_class1 integer NOT NULL\n"
                ");\n\n"
               );


     txt.printf(
                "create table abc_alphabet( id number(10) not null, name nvarchar2(32) not null unique, constraint pk_abc_alphabet primary key (id) );\n"
                "create table abc_coord( id number(10) not null, name nvarchar2(32) not null unique, bistable int, constraint pk_abc_coord primary key (id) );\n"
                "create table abc_state( id int not null, id_coord int not null, name nvarchar2(32) not null );\n"
                "create table abc_class( id number(10) not null, name nvarchar2(32) not null unique, constraint pk_abc_class primary key (id) );\n"
                "create table abc_class_coord( id_class int not null, id_coord int not null, coord_type int not null );\n"
                "create table abc_entry( id number(10) not null, name nvarchar2(4) not null, id_class number(10) not null, id_alphabet number(10) not null, id_pairs number(10) not null, code number(10) not null, constraint pk_abc_entry primary key (id) );\n"
                "create table abc_form( id number(10) not null, ordnum number(10) not null, id_entry int not null, id_pairs int not null, name nvarchar2(4) not null, code number(10) not null, constraint pk_abc_form primary key (id) );\n"
                "create table abc_pairs( id number(10) not null, str_pairs nvarchar2(60) not null unique, constraint pk_abc_pairs primary key (id) );\n"
                "create table abc_pair( id number(10) not null, id_pairs number(10) not null, id_coord number(10) not null, id_state number(10) not null, constraint pk_abc_pair primary key (id) );\n"
                "create table abc_criterion( id number(10) not null, name nvarchar2(64) not null unique, strval nvarchar2(100) not null, constraint pk_abc_criterion primary key (id) );\n"
               );

     txt.printf(
                "CREATE TABLE lang_usage( "
                " id_language number not null,"
                " is_input number not null,"
                " is_output number not null,"
                " is_default number not null"
                ");\n\n"
               );


     if( !sql_version.norules )
      {
       txt.printf(
                  "CREATE TABLE abc_operation( "
                  " id number number not null,"
                  " name varchar2(32) NOT NULL,"
                  " constraint pk_abc_operation primary key(id) );\n\n"
     
                  "CREATE TABLE abc_operation_item( "
                  " id number not null,"
                  " id_operation number NOT NULL,"
                  " src_char_ucs4 number NOT NULL,"
                  " res_char_ucs4 number NOT NULL,"
                  " src_char varchar2(2) NOT NULL,"
                  " res_char varchar2(2) NOT NULL,"
                  " constraint pk_abc_operation_item primary key(id)"
                  ");\n\n"
     
                  "CREATE TABLE tr_functions( "
                  " marker varchar2(3) NOT NULL,"
                  " bin CLOB"
                  ");\n\n"
     
     
                  "CREATE TABLE unbreakable( "
                  " id number NOT NULL,"
                  " name varchar2(32) NOT NULL,"
                  " id_language number NOT NULL,"
                  " id_src number,"
                  " pattern varchar2(100) NOT NULL,"
                  " is_regex number NOT NULL"
                  ");\n\n"
     
                  "CREATE TABLE recog_rule( "
                  " id number NOT NULL,"
                  " name varchar2(32) NOT NULL,"
                  " id_language number NOT NULL,"
                  " id_src number,"
                  " is_regex number not null,"
                  " is_syllab number not null,"
                  " is_prefix number not null,"
                  " is_affix number not null,"
                  " r_condition varchar(100) not null,"
                  " case_sensitive integer not null,"
                  " word varchar(100),"
                  " id_entry number not null,"
                  " rel number not null,"
                  " coords varchar2(300) not null"
                  ");\n\n"
     
                  "CREATE TABLE ph_rule( "
                  " id number NOT NULL,"
                  " name varchar2(32) NOT NULL,"
                  " id_language number NOT NULL,"
                  " id_src number,"
                  " r_condition varchar(30) not null,"
                  " r_result varchar2(30) not null,"
                  " is_prefix number not null,"
                  " is_affix number not null,"
                  " rel number not null"
                  ");\n\n"
     
     
                  "CREATE TABLE SynPatternTree( "
                  " id number NOT NULL,"
                  " id_tree NUMBER NOT NULL,"
                  " id_language NUMBER NOT NULL,"
                  " name varchar2(32) NOT NULL,"
                  " uname varchar2(32) NOT NULL,"
                  " pattern_type NUMBER NOT NULL,"
                  " bin CBLOB"
                  ");\n\n"
     
                  "CREATE TABLE src_filename( "
                  " id number NOT NULL,"
                  " filepath varchar2(2000) NOT NULL,"
                  " filepath0 varchar2(2000) NOT NULL"
                  ");\n\n"
     
                  "CREATE TABLE src_location( "
                  " id number NOT NULL,"
                  " id_filename number NOT NULL,"
                  " line_no number NOT NULL,"
                  " column_no number NOT NULL"
                  ");\n\n"
     
                  "\n"
                 );
     
     
       txt.printf(
                  "CREATE TABLE slb_rule(\n"
                  "id number PRIMARY KEY NOT NULL,\n"
                  "name nvarchar2(32) NOT NULL UNIQUE,\n"
                  "id_src number NOT NULL,\n"
                  "id_language number NOT NULL,\n"
                  "cursor_shift number NOT NULL,\n"
                  "constraint pk_slb_rule key (id)\n"
                  ");\n\n"
     
                  "CREATE TABLE slb_condition_point(\n"
                  " id number PRIMARY KEY NOT NULL,\n"
                  " id_rule number NOT NULL,\n"
                  " point_index number NOT NULL,\n"
                  " n_char number NOT NULL,\n"
                  " char_text nvarchar2(30) NOT NULL,\n"
                  " char_ucs4 nvarchar2(30) NOT NULL,\n"
                  " id_class number NOT NULL,\n"
                  " id_entry number NOT NULL,\n"
                  " n_coord number NOT NULL,\n"
                  " id_coord0 number NOT NULL,\n"
                  " id_state0 number NOT NULL,\n"
                  " is_left_boundary number NOT NULL,\n"
                  " is_right_boundary number NOT NULL,\n"
                  " is_positive number NOT NULL,\n"
                  " constraint pk_slb_condition_point primary key (id)\n"
                  ");\n\n"
     
                  "CREATE TABLE slb_result_point(\n"
                  " id number PRIMARY KEY NOT NULL,\n"
                  " id_rule number NOT NULL,\n"
                  " point_index number NOT NULL,\n"
                  " copy_index number NOT NULL,\n"
                  " merge_index0 number NOT NULL,\n"
                  " merge_count number NOT NULL,\n"
                  "constraint pk_slb_result_point primary key (id)\n"
                  ");\n\n"
                 );
     
     
       txt.printf(
                  " CREATE TABLE ts_head_word( \n"
                  " id number PRIMARY KEY NOT NULL,\n"
                  " word nvarchar2(100) NOT NULL,\n"
                  " id_head_point number NOT NULL,\n"
                  " score_type number NOT NULL,\n"
                  " score_expr nvarchar2(100),\n"
                  " root_node number NOT NULL,"
                  " id_group number NOT NULL\n"
                  " );\n"
     
                  "CREATE TABLE ts_head_lemma( \n"
                  " id number PRIMARY KEY NOT NULL,\n"
                  " id_entry number NOT NULL,\n"
                  " id_head_point number NOT NULL,\n"
                  " score_type number NOT NULL,\n"
                  " score_expr nvarchar2(100),\n"
                  " root_node number NOT NULL,\n"
                  " id_group number NOT NULL\n"
                  ");\n"
     
                  "CREATE TABLE ts_point( \n"
                  " id number PRIMARY KEY NOT NULL,\n"
                  " id_parent number,\n"
                  " id_group number,\n"
                  " word_text nvarchar2(100),\n"
                  " id_entry number NOT NULL,\n"
                  " id_metaentry number NOT NULL,\n"
                  " id_class number NOT NULL,\n"
                  " wordentryset_name nvarchar2(100),\n"
                  " wordset_name nvarchar2(100),\n"
                  " wordformset_name nvarchar2(100),\n"
                  " n_coords number NOT NULL,\n"
                  " id_coord1 number,\n"
                  " id_state1 number,\n"
                  " affirm1 number,\n"
                  " id_coord2 number,\n"
                  " id_state2 number,\n"
                  " affirm2 number,\n"
                  " id_coord3 number,\n"
                  " id_state3 number,\n"
                  " affirm3 number,\n"
                  " id_coord4 number,\n"
                  " id_state4 number,\n"
                  " affirm4 number,\n"
                  " thesauruscheck_link number NOT NULL,\n"
                  " thesauruscheck_entry number NOT NULL,\n"
                  " is_positive number NOT NULL,\n"
                  " children_quantification_min_count number NOT NULL,\n"
                  " children_quantification_max_count number NOT NULL,\n"
                  " n_setcheckers number NOT NULL,\n"
                  " set_name1 nvarchar2(50),\n"
                  " set_type1 number NOT NULL,\n"
                  " set_affirm1 number NOT NULL,\n"
                  " set_name2 nvarchar2(50),\n"
                  " set_type2 number NOT NULL,\n"
                  " set_affirm2 number NOT NULL,\n"
                  " set_name3 nvarchar2(50),\n"
                  " set_type3 number NOT NULL,\n"
                  " set_affirm3 number NOT NULL,\n"
                  " link_type number NOT NULL,\n"
                  " relative_position number NOT NULL,\n"
                  " quantification_min_count number NOT NULL,\n"
                  " quantification_max_count number NOT NULL,\n"
                  " marker nvarchar2(30),"
                  " n_backref number NOT NULL,"
     
                  " br_affirm_0 number,\n"
                  " br_coord0_0 number,\n"
                  " br_marker_0 nvarchar2(30),\n"
                  " br_coord1_0 number,\n"
                  " br_for_group_0 number,\n"
     
                  " br_affirm_1 number,\n"
                  " br_coord0_1 number,\n"
                  " br_marker_1 nvarchar2(30),\n"
                  " br_coord1_1 number,\n"
                  " br_for_group_1 number,\n"
     
                  " br_affirm_2 number,\n"
                  " br_coord0_2 number,\n"
                  " br_marker_2 nvarchar2(30),\n"
                  " br_coord1_2 number,\n"
                  " br_for_group_2 number,\n"
     
                  " id_src number\n"
                  ");\n"
                 );
     
     
       txt.printf(
                  "CREATE TABLE ts_group(\n"
                  " id number PRIMARY KEY NOT NULL,\n"
                  " name nvarchar(30) NOT NULL,\n"
                  " allow_unmatched_children number NOT NULL\n"
                  ");\n\n"
     
                  "CREATE TABLE ts_group2root(\n"
                  " id number PRIMARY KEY NOT NULL,\n"
                  " id_group number NOT NULL,\n"
                  " id_root number NOT NULL\n"
                  ");\n\n"
                 );

       txt.printf(
                  "CREATE TABLE word_assoc(\n"
                  " id number PRIMARY KEY NOT NULL,\n"
                  " id_src number,\n"
                  " id_entry number NOT NULL,\n"
                  " id_entry1 number,\n"
                  " word1 nvarchar2(40),\n"
                  " id_metaentry1 number,\n"
                  " id_entry2 number,\n"
                  " word2 nvarchar2(40),\n"
                  " id_metaentry2 number,\n"
                  " link_type number,\n"
                  " link_entry number,\n"
                  " set_name nvarchar2(40),\n"
                  " set_type number,\n"
                  " score number NOT NULL\n"
                  ");\n\n"
                 );
     
       txt.printf(
                  "CREATE TABLE predicate_template(\n"
                  " id number PRIMARY KEY NOT NULL,\n"
                  " id_src number,\n"
                  " src nvarchar2(250) NOT NULL,\n"
                  " params number(100)\n"
                  ");\n"
                 );

      }

     txt.printf(
                " CREATE TABLE metaentry( \n"
                " id number PRIMARY KEY NOT NULL,\n"
                " id_class number not null,\n"
                " name nvarchar2(100) NOT NULL\n"
                " );\n" );

     txt.printf(
                " CREATE TABLE metaentry_item( \n"
                " id number PRIMARY KEY NOT NULL,\n"
                " id_metaentry number not null,\n"
                " id_entry number not null\n"
                " );\n" );

     txt.printf(
                "CREATE TABLE omonym(\n"
                " id number PRIMARY KEY NOT NULL,\n"
                " entry_name nvarchar2(100) NOT NULL,\n"
                " id_class number NOT NULL\n"
                ");\n"
               );

     txt.printf( "COMMIT;\n\n" );
    }
   else if( sql_version.type==SQL_Production::MySql )
    {
     if( sql_version.IsUtf8() )
      txt.printf( "set names 'utf8';\n" );

     txt.printf( "set session sql_mode='NO_AUTO_VALUE_ON_ZERO';\n" );     

     int itable=0;
     while( table_names[itable]!=NULL )
     {
      txt.printf( "%us\n", sql_version.DropTable( table_names[itable] ).c_str() );
      itable++;
     }

     txt.printf(
                "create table endings( id int NOT NULL PRIMARY KEY AUTO_INCREMENT, ending varchar(40) not null, id_language int not null, nform int not null, sumfreq int not null );\n"
                "create table ending_stat( id_language int not null, max_len int not null );\n"

                "create table wordform_frequency( id int NOT NULL PRIMARY KEY AUTO_INCREMENT, id_entry int unsigned not null, iform int not null, freq int not null );\n"

                "create table misspelling( id int NOT NULL PRIMARY KEY AUTO_INCREMENT, id_language int not null, original_word varchar(64) not null, substitution varchar(64) not null );\n"

                "create table coord_pairs( id int NOT NULL PRIMARY KEY AUTO_INCREMENT, pairs varchar(1000) not null, str_pairs varchar(1000) not null );\n"
                "create table tag_set( id int NOT NULL PRIMARY KEY AUTO_INCREMENT, tags varchar(1000) not null );\n"

                "create table sg_language( id int NOT NULL PRIMARY KEY AUTO_INCREMENT, name varchar(32) not null );\n"
                "create table lang_alphabet( id int NOT NULL PRIMARY KEY AUTO_INCREMENT, id_language int not null, id_alphabet int not null, ordering int not null );\n"
                "create table lang_link( id int NOT NULL PRIMARY KEY AUTO_INCREMENT, id_language int not null, id_state int not null, id_language2 int not null );\n"
                "create table lang_param( id int NOT NULL PRIMARY KEY AUTO_INCREMENT, id_language int not null, param_name varchar(32) not null, param_value varchar(200) not null, ordering int not null );\n"
                "create table sg_lexem( id int unsigned NOT NULL PRIMARY KEY, name varchar(32) not null );\n"
                "create table sg_coord( id int NOT NULL PRIMARY KEY, name varchar(32) not null, bistable integer );\n"
                "create table sg_state( id int NOT NULL, id_coord integer not null, name varchar(32) not null, id_parent int, weight int );\n"
                "create table sg_class( id int NOT NULL PRIMARY KEY, name varchar(32) not null, name_aliase varchar(32), id_lang int, weight int not null, closed_class int not null );\n"
                "create table unknown_entries( id int unsigned NOT NULL PRIMARY KEY );\n"
                "create table predef_entries( id int NOT NULL PRIMARY KEY, id_entry int unsigned not null );\n"
                "create table sg_entry( id int unsigned NOT NULL PRIMARY KEY, name varchar(32) not null, uname varchar(32) not null, id_class int not null, freq int, exportable int not null, flags int not null default 0, dic_div char(4) not null DEFAULT '', modifier char(4), modified timestamp );\n"
                "create table sg_form( id_entry int unsigned not null, iform int not null, name varchar(32) not null, id_lexem int unsigned not null, id_dims int );\n"
                "create table sg_link( id int NOT NULL PRIMARY KEY, id_entry1 int unsigned not null, id_entry2 int unsigned not null, icoord int not null, istate int not null, tags int, modifier char(4), modified timestamp, dic_div char(4) not null DEFAULT '' );\n"
                "create table sg_entry_coord( id_entry int unsigned not null, icoord int not null, istate int not null );\n"
                "create table sg_form_coord( id_entry int unsigned not null, iform int not null, icoord int not null, istate int not null );\n"
                "create table sg_class_coord( id_class int not null, id_coord int not null, coord_type int not null );\n"
                "create table class_attr_def( id int not null, id_class int not null, id_coord int not null, default_state int not null );\n"

                "create table sg_tag( id int NOT NULL PRIMARY KEY, name varchar(32) not null );\n"
                "create table sg_tag_value( id_tag int not null, ivalue int not null, name varchar(32) not null );\n"
                "create table sg_link_tag( id int NOT NULL PRIMARY KEY, id_link int not null, id_tag int not null, ivalue int not null );\n"
                "create table sg_tentry( te_id int NOT NULL PRIMARY KEY, te_text varchar(2000), te_utxt varchar(2000), te_text32 varchar(32), te_id_language integer, te_id_class integer, te_syntax_flags integer, te_modifier char(4), te_modified timestamp, dic_div char(4) not null DEFAULT '' );\n"
                "create table sg_tlink( tl_id int NOT NULL PRIMARY KEY, tl_te_id1 int not null, tl_te_id2 int not null, tl_icoord int not null, tl_istate int not null, tl_tags int, tl_modifier char(4), tl_modified timestamp, dic_div char(4) not null DEFAULT '' );\n"
                "create table sg_tlink_tag( tlt_id int NOT NULL PRIMARY KEY, tlt_tl_id int not null, tlt_id_tag int not null, tlt_ivalue int not null );\n"
                "create table sg_tlink_flag( tlf_id int NOT NULL PRIMARY KEY, tlf_tl_id int not null, tlf_flag varchar(32) not null, tlf_value varchar(32) not null );\n"
                "create table cplx_left( cl_id int NOT NULL PRIMARY KEY, cl_headword varchar(32) not null, cl_minlen int not null, cl_maxlen int not null );\n"
                "create table tnotes( tn_id int NOT NULL PRIMARY KEY, tn_te_id int not null, tn_type int not null, tn_format int not null, tn_data varchar(4000) not null );\n"
               );


     txt.printf(
                "create table aux_form_types( id int NOT NULL PRIMARY KEY, name varchar(32) not null );\n"
                "create table aux_form( id int not null PRIMARY KEY AUTO_INCREMENT, id_entry int unsigned not null, iform int not null, data_type int not null, data_text varchar(200) not null );\n"
                "create table aux_entry_data( id int NOT NULL PRIMARY KEY AUTO_INCREMENT, id_entry int unsigned not null, data_type int not null, data_text varchar(200) not null );\n"
               );

     txt.printf(
                "CREATE TABLE aux_word(\n"
                "id integer PRIMARY KEY AUTO_INCREMENT,\n"
                "aux_type INTEGER NOT NULL,\n"
                "src varchar(30),\n"
                "res varchar(200)\n"
                ");\n\n"
               );

     txt.printf(
                "create table multilexem( id int not null PRIMARY KEY AUTO_INCREMENT, txt varchar(64) not null, headword varchar(64) not null, n_lexem int not null );\n"
                "create table sg_criterion( id int not null PRIMARY KEY AUTO_INCREMENT, name varchar(64) not null, strval varchar(100) not null );\n"
                "\n" 
               );

     txt.printf(
                "CREATE TABLE paradigma( "
                " id integer NOT NULL PRIMARY KEY AUTO_INCREMENT,"
                " front_name varchar(32),"
                " r_condition varchar(256),"
                " id_class integer,"
                " attrs VARCHAR(100)"
                ");\n\n"
  
                "CREATE TABLE paradigma_name( "
                " id integer NOT NULL PRIMARY KEY AUTO_INCREMENT,"
                " id_paradigma integer not null,"
                " name varchar(32),"
                " uname varchar(32)"
                ");\n\n"
  
                "CREATE TABLE paradigma_form( "
                " id integer NOT NULL PRIMARY KEY AUTO_INCREMENT,"
                " id_paradigma integer NOT NULL,"
                " rx_condition VARCHAR(100),"
                " flexer_flags VARCHAR(100),"
                " lexem_generator varchar(100) NOT NULL,"
                " dims varchar(256)"
                ");\n\n"
               );

     txt.printf(
                "CREATE TABLE word_entry_set( "
                " id integer NOT NULL PRIMARY KEY AUTO_INCREMENT,"
                " name varchar(32) NOT NULL,"
                " ies varchar(1000000) NOT NULL"
                ");\n\n"

                "CREATE TABLE word_set( "
                " id integer NOT NULL PRIMARY KEY AUTO_INCREMENT,"
                " name varchar(32) NOT NULL,"
                " case_sensitive integer NOT NULL,"
                " words varchar(10000) NOT NULL"
                ");\n\n"

                "CREATE TABLE collocation_set( "
                " id integer NOT NULL PRIMARY KEY AUTO_INCREMENT,"
                " name varchar(32) NOT NULL,"
                " case_sensitive integer NOT NULL"
                ");\n\n"

                "CREATE TABLE collocation_set_item( "
                " id integer NOT NULL PRIMARY KEY AUTO_INCREMENT,"
                " id_set integer NOT NULL,"
                " words varchar(250) NOT NULL,"
                " n_word integer NOT NULL,"
                " headword varchar(30) NOT NULL"
                ");\n\n"

                "CREATE TABLE collocation_headword( "
                " id integer NOT NULL PRIMARY KEY AUTO_INCREMENT,"
                " headword varchar(32) NOT NULL,"
                " min_len integer NOT NULL,"
                " max_len integer NOT NULL"
                ");\n\n"

                "CREATE TABLE wordform_set( "
                " id integer PRIMARY KEY NOT NULL AUTO_INCREMENT,"
                " name varchar(32) NOT NULL"
                ");\n"
 
                "CREATE TABLE wordform_set_item( "
                " id integer PRIMARY KEY NOT NULL AUTO_INCREMENT,"
                " id_set integer NOT NULL,"
                " word varchar(32) NOT NULL,"
                " id_entry integer NOT NULL,"
                " id_coords integer NOT NULL"
                ");\n"
 
                "CREATE TABLE wordform_set_coords( "
                " id integer PRIMARY KEY NOT NULL AUTO_INCREMENT,"
                " coords varchar(200) NOT NULL"
                ");\n\n"

               );

     txt.printf(
                "create table abc_alphabet( id integer not null primary key, name varchar(32) not null unique );\n"
                "create table abc_coord( id integer not null primary key, name varchar(32) not null unique, bistable int );\n"
                "create table abc_state( id int not null, id_coord int not null, name varchar(32) not null );\n"
                "create table abc_class( id integer not null primary key, name varchar(32) not null unique );\n"
                "create table abc_class_coord( id_class int not null, id_coord int not null, coord_type int not null );\n"
                "create table abc_entry( id integer not null primary key, name varchar(4) not null, id_class integer not null, id_alphabet integer not null, id_pairs integer not null, code integer not null );\n"
                "create table abc_form( id integer not null primary key, ordnum integer not null, id_entry int not null, id_pairs int not null, name char(1) not null, code integer not null );\n"
                "create table abc_pairs( id integer not null primary key, str_pairs varchar(60) not null unique );\n"
                "create table abc_pair( id integer not null primary key, id_pairs integer not null, id_coord integer not null, id_state integer not null );\n"
                "create table abc_criterion( id int not null PRIMARY KEY AUTO_INCREMENT, name varchar(64) not null, strval varchar(100) not null );\n"
               );


     txt.printf(
                "CREATE TABLE abc_operation( "
                " id integer NOT NULL PRIMARY KEY AUTO_INCREMENT,"
                " name varchar(32) NOT NULL UNIQUE"
                ");\n\n"

                "CREATE TABLE abc_operation_item( "
                " id integer NOT NULL PRIMARY KEY AUTO_INCREMENT,"
                " id_operation integer NOT NULL,"
                " src_char_ucs4 integer NOT NULL,"
                " res_char_ucs4 integer NOT NULL,"
                " src_char varchar(2) NOT NULL,"
                " res_char varchar(2) NOT NULL"
                ");\n\n"

                "CREATE TABLE tr_functions( "
                " marker varchar(3) NOT NULL,"
                " bin LONGTEXT NOT NULL"
                ");\n\n"


                "CREATE TABLE unbreakable( "
                " id integer NOT NULL PRIMARY KEY AUTO_INCREMENT,"
                " name varchar(32) NOT NULL,"
                " id_language integer NOT NULL,"
                " id_src integer,"
                " pattern varchar(100) NOT NULL,"
                " is_regex integer NOT NULL"
                ");\n\n"

                "CREATE TABLE crop_rule( "
                " id integer NOT NULL PRIMARY KEY AUTO_INCREMENT,"
                " name varchar(32),"
                " r_condition varchar(256) NOT NULL,"
                " r_result varchar(256) NOT NULL,"
                " id_language integer NOT NULL,"
                " is_prefix integer NOT NULL,"
                " is_affix integer NOT NULL,"
                " is_regex integer NOT NULL,"
                " id_src integer,"
                " case_sensitive integer NOT NULL,"
                " rel integer NOT NULL"
                ");\n\n"

                "CREATE TABLE recog_rule( "
                " id integer NOT NULL PRIMARY KEY AUTO_INCREMENT,"
                " name varchar(32) NOT NULL,"
                " id_language integer NOT NULL,"
                " id_src integer,"
                " is_regex integer not null,"
                " is_syllab integer not null,"
                " is_prefix integer not null,"
                " is_affix integer not null,"
                " r_condition varchar(100) not null,"
                " case_sensitive integer not null,"
                " word varchar(100),"
                " id_entry integer unsigned not null,"
                " rel integer not null,"
                " coords varchar(300) not null"
                ");\n\n"


                "CREATE TABLE ph_rule( "
                " id integer NOT NULL PRIMARY KEY AUTO_INCREMENT,"
                " name varchar(32) NOT NULL,"
                " id_language integer NOT NULL,"
                " id_src integer,"
                " r_condition varchar(30) not null,"
                " r_result varchar(30) not null,"
                " is_prefix integer not null,"
                " is_affix integer not null,"
                " rel integer not null"
                ");\n\n"

                "CREATE TABLE SynPatternTree( "
                " id integer NOT NULL PRIMARY KEY AUTO_INCREMENT,"
                " id_tree integer NOT NULL,"
                " id_language integer NOT NULL,"
                " name varchar(32) NOT NULL,"
                " uname varchar(32) NOT NULL,"
                " pattern_type integer NOT NULL,"
                " bin MEDIUMBLOB"
                ");\n\n"


                "CREATE TABLE lang_usage( "
                " id_language integer not null,"
                " is_input integer not null,"
                " is_output integer not null,"
                " is_default integer not null"
                ");\n\n"

                "CREATE TABLE src_filename( "
                " id integer NOT NULL PRIMARY KEY AUTO_INCREMENT,"
                " filepath varchar(2000) NOT NULL,"
                " filepath0 varchar(2000) NOT NULL"
                ");\n\n"
  
                "CREATE TABLE src_location( "
                " id integer NOT NULL PRIMARY KEY AUTO_INCREMENT,"
                " id_filename integer NOT NULL,"
                " line_no integer NOT NULL,"
                " column_no integer NOT NULL"
                ");\n\n"

                "\n" 
               );

     txt.printf(
                "CREATE TABLE kb_facts(\n"
                " id integer PRIMARY KEY NOT NULL AUTO_INCREMENT,\n"
                " id_language integer NOT NULL,\n"
                " name varchar(100) NOT NULL,\n"
                " n_arg integer NOT NULL,\n"
                " n_ret integer NOT NULL,\n"
                " ret_type integer NOT NULL,\n"
                " query_mode integer NOT NULL,\n"
                " violation_score integer NOT NULL,\n"
                " violation_handler integer NOT NULL\n"
                ");\n\n"

                "CREATE TABLE kb_fact(\n"
                " id integer PRIMARY KEY NOT NULL AUTO_INCREMENT,\n"
                " id_group integer NOT NULL,\n"
                " boolean_return integer,\n"
                " false_score integer,\n"
                " integer_return integer\n"
                ");\n\n"

                "CREATE TABLE kb_argument_point( \n"
                " id integer PRIMARY KEY NOT NULL AUTO_INCREMENT,\n"
                " id_fact integer,\n"
                " argument_index integer NOT NULL,\n"
                " word_text varchar(100),\n"
                " id_entry integer,\n"
                " id_class integer,\n"
                " is_regex integer NOT NULL,\n"
                " case_sensitive integer NOT NULL,\n"
                " id_metaentry integer NOT NULL,\n"
                " wordentryset_name varchar(100),\n"
                " wordset_name varchar(100),\n"
                " n_coords integer,\n"
                " id_coord1 integer,\n"
                " id_state1 integer,\n"
                " affirm1 integer,\n"
                " id_coord2 integer,\n"
                " id_state2 integer,\n"
                " affirm2 integer,\n"
                " id_coord3 integer,\n"
                " id_state3 integer,\n"
                " affirm3 integer,\n"
                " id_coord4 integer,\n"
                " id_state4 integer,\n"
                " affirm4 integer,\n"
                " thesauruscheck_link integer,\n"
                " thesauruscheck_entry integer,\n"
                "  is_positive integer NOT NULL\n"
                " );\n\n"
              );


     txt.printf(
                "CREATE TABLE kb_fact_index1(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_group integer NOT NULL,\n"
                " id_fact integer NOT NULL,\n"
                " word1 varchar(32),\n"
                " word2 varchar(32),\n"
                " word3 varchar(32),\n"
                " word4 varchar(32),\n"
                " word5 varchar(32)\n"
                ");\n\n"


                "CREATE TABLE kb_fact_index2(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_group integer NOT NULL,\n"
                " id_fact integer NOT NULL,\n"
                " id_entry1 integer,\n"
                " id_entry2 integer,\n"
                " id_entry3 integer,\n"
                " id_entry4 integer,\n"
                " id_entry5 integer\n"
                ");\n\n"

                "CREATE TABLE generic_tree_scorer(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_head_point integer NOT NULL,\n"
                " id_group integer NOT NULL,\n"
                " score_expr varchar(100),\n"
                " score_type integer NOT NULL\n"
                ");\n\n"

                "CREATE TABLE ts_predicate(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_point integer NOT NULL,\n"
                " func_name varchar(20) NOT NULL,\n"
                " narg integer NOT NULL,\n"
                " id_class1 integer NOT NULL\n"
                ");\n\n"
               );



     txt.printf(
                "CREATE TABLE slb_rule(\n"
                "id integer NOT NULL PRIMARY KEY AUTO_INCREMENT,\n"
                "name varchar(32) NOT NULL UNIQUE,\n"
                "id_src integer NOT NULL,\n"
                "id_language integer NOT NULL,\n"
                "cursor_shift integer NOT NULL\n"
                ");\n\n"

                "CREATE TABLE slb_condition_point(\n"
                " id integer NOT NULL PRIMARY KEY AUTO_INCREMENT,\n"
                " id_rule integer NOT NULL,\n"
                " point_index integer NOT NULL,\n"
                " n_char integer NOT NULL,\n"
                " char_text varchar(30) NOT NULL,\n"
                " char_ucs4 varchar(30) NOT NULL,\n"
                " id_class integer NOT NULL,\n"
                " id_entry integer NOT NULL,\n"
                " n_coord integer NOT NULL,\n"
                " id_coord0 integer NOT NULL,\n"
                " id_state0 integer NOT NULL,\n"
                " is_left_boundary integer NOT NULL,\n"
                " is_right_boundary integer NOT NULL,\n"
                " is_positive integer NOT NULL\n"
                ");\n\n"

                "CREATE TABLE slb_result_point(\n"
                " id integer NOT NULL PRIMARY KEY AUTO_INCREMENT,\n"
                " id_rule integer NOT NULL,\n"
                " point_index integer NOT NULL,\n"
                " copy_index integer NOT NULL,\n"
                " merge_index0 integer NOT NULL,\n"
                " merge_count integer NOT NULL\n"
                ");\n\n"
               );

     txt.printf(
                " CREATE TABLE ts_head_word(\n"
                " id integer NOT NULL PRIMARY KEY AUTO_INCREMENT,\n"
                " word varchar(100) NOT NULL,\n"
                " id_head_point integer NOT NULL,\n"
                " score_type integer NOT NULL,\n"
                " score_expr varchar(100),"
                " root_node integer NOT NULL,\n"
                " id_group integer NOT NULL\n"
                " );\n\n"

                "CREATE TABLE ts_head_lemma(\n"
                " id integer NOT NULL PRIMARY KEY AUTO_INCREMENT,\n"
                " id_entry integer NOT NULL,\n"
                " id_head_point integer NOT NULL,\n"
                " score_type integer NOT NULL,\n"
                " score_expr varchar(100),"
                " root_node integer NOT NULL\n,"
                " id_group integer NOT NULL\n"
                ");\n\n"

                "CREATE TABLE ts_point(\n"
                " id integer NOT NULL PRIMARY KEY AUTO_INCREMENT,\n"
                " id_parent integer,\n"
                " id_group integer,\n"
                " word_text varchar(100),\n"
                " id_entry integer NOT NULL,\n"
                " id_metaentry integer NOT NULL,\n"
                " id_class integer,\n"
                " wordentryset_name varchar(100),\n"
                " wordset_name varchar(100),\n"
                " wordformset_name varchar(100),\n"
                " n_coords integer NOT NULL,\n"
                " id_coord1 integer,\n"
                " id_state1 integer,\n"
                " affirm1 integer,\n"
                " id_coord2 integer,\n"
                " id_state2 integer,\n"
                " affirm2 integer,\n"
                " id_coord3 integer,\n"
                " id_state3 integer,\n"
                " affirm3 integer,\n"
                " id_coord4 integer,\n"
                " id_state4 integer,\n"
                " affirm4 integer,\n"
                " thesauruscheck_link integer NOT NULL,\n"
                " thesauruscheck_entry integer NOT NULL,\n"
                " is_positive integer NOT NULL,\n"
                " children_quantification_min_count integer NOT NULL,\n"
                " children_quantification_max_count integer NOT NULL,\n"
                " n_setcheckers integer NOT NULL,\n"
                " set_name1 varchar(50),\n"
                " set_type1 integer NOT NULL,\n"
                " set_affirm1 integer NOT NULL,\n"
                " set_name2 varchar(50),\n"
                " set_type2 integer NOT NULL,\n"
                " set_affirm2 integer NOT NULL,\n"
                " set_name3 varchar(50),\n"
                " set_type3 integer NOT NULL,\n"
                " set_affirm3 integer NOT NULL,\n"
                " link_type integer NOT NULL,\n"
                " relative_position integer NOT NULL,\n"
                " quantification_min_count integer NOT NULL,\n"
                " quantification_max_count integer NOT NULL,\n"
                " marker varchar(30),"
                " n_backref integer NOT NULL,"
                " br_affirm_0 integer,\n"
                " br_coord0_0 integer,\n"
                " br_marker_0 varchar(30),\n"
                " br_coord1_0 integer,\n"
                " br_for_group_0 integer,\n"

                " br_affirm_1 integer,\n"
                " br_coord0_1 integer,\n"
                " br_marker_1 varchar(30),\n"
                " br_coord1_1 integer,\n"
                " br_for_group_1 integer,\n"

                " br_affirm_2 integer,\n"
                " br_coord0_2 integer,\n"
                " br_marker_2 varchar(30),\n"
                " br_coord1_2 integer,\n"
                " br_for_group_2 integer,\n"

                " id_src integer\n"
                ");\n\n"
               );

     txt.printf(
                "CREATE TABLE ts_group(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " name varchar(30) NOT NULL,\n"
                " allow_unmatched_children integer NOT NULL\n"
                ");\n\n"

                "CREATE TABLE ts_group2root(\n"
                " id integer PRIMARY KEY NOT NULL AUTO_INCREMENT,\n"
                " id_group integer NOT NULL,\n"
                " id_root integer NOT NULL\n"
                ");\n\n"
               );

     txt.printf(
                " CREATE TABLE metaentry( \n"
                " id integer NOT NULL PRIMARY KEY AUTO_INCREMENT,\n"
                " id_class integer not null,\n"
                " name varchar(100) NOT NULL\n"
                " );\n" );

     txt.printf(
                " CREATE TABLE metaentry_item( \n"
                " id integer NOT NULL PRIMARY KEY AUTO_INCREMENT,\n"
                " id_metaentry integer not null,\n"
                " id_entry integer not null\n"
                " );\n\n" );

     txt.printf(
                "CREATE TABLE omonym(\n"
                " id integer PRIMARY KEY NOT NULL AUTO_INCREMENT,\n"
                " entry_name varchar(100) NOT NULL,\n"
                " id_class integer NOT NULL\n"
                ");\n"
               );

     txt.printf(
                "CREATE TABLE word_assoc(\n"
                " id integer PRIMARY KEY NOT NULL AUTO_INCREMENT,\n"
                " id_src integer,\n"
                " id_entry integer NOT NULL,\n"
                " id_entry1 integer,\n"
                " word1 varchar(40),\n"
                " id_metaentry1 integer,\n"
                " id_entry2 integer,\n"
                " word2 varchar(40),\n"
                " id_metaentry2 integer,\n"
                " link_type integer,\n"
                " link_entry integer,\n"
                " set_name varchar(40),\n"
                " set_type integer,\n"
                " score integer NOT NULL\n"
                ");\n\n"
               );

     txt.printf(
                "CREATE TABLE predicate_template(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_src integer,\n"
                " src varchar(250) NOT NULL,\n"
                " params varchar(100)\n"
                ");\n"
               );
    }
   else if( sql_version.type==SQL_Production::SQLite )
    {
     int itable=0;
     while( table_names[itable]!=NULL )
     {
      txt.printf( "%us\n", sql_version.DropTable( table_names[itable] ).c_str() );
      itable++;
     }


     txt.printf(
                "create table endings( id int PRIMARY KEY, ending varchar(40) not null, id_language int not null, nform int not null, sumfreq int not null );\n"
                "create table ending_stat( id_language int not null, max_len int not null );\n"
                "create table wordform_frequency( id int PRIMARY KEY, id_entry int not null, iform int not null, freq int not null );\n"
                "create table misspelling( id int PRIMARY KEY, id_language int not null, original_word varchar(64) not null, substitution varchar(64) not null );\n"

                "create table coord_pairs( id int not null PRIMARY KEY, pairs varchar(1000) not null, str_pairs varchar(1000) not null );\n"
                "create table tag_set( id int not null PRIMARY KEY, tags varchar(1000) not null );\n"

                "CREATE TABLE sg_language( ID int NOT NULL, NAME varchar(32) NOT NULL, CONSTRAINT PK_LANGUAGE PRIMARY KEY(ID) );\n"
                "create table lang_alphabet( id int not null PRIMARY KEY, id_language int not null, id_alphabet int not null, ordering int not null );\n"
                "create table lang_link( id int not null PRIMARY KEY, id_language int not null, id_state int not null, id_language2 int not null );\n"
                "create table lang_param( id int not null PRIMARY KEY, id_language int not null, param_name varchar(32) not null, param_value varchar(200) not null, ordering int not null );\n"
                "CREATE TABLE sg_lexem( ID int unsigned, NAME varchar(32) NOT NULL, CONSTRAINT PK_LEXEM PRIMARY KEY(ID) );\n"
                "CREATE TABLE sg_coord( ID integer NOT NULL, NAME varchar(32) NOT NULL, BISTABLE integer NOT NULL, CONSTRAINT PK_COORD PRIMARY KEY(ID) );\n"
                "CREATE TABLE sg_state( ID integer NOT NULL, ID_COORD integer NOT NULL, NAME varchar(32) NOT NULL, id_parent int not null, weight int not null, CONSTRAINT PK_COORD PRIMARY KEY(ID,ID_COORD) );\n"
                "CREATE TABLE sg_class( ID int, NAME varchar(32) NOT NULL, NAME_ALIASE varchar(32), ID_LANG int, weight int not null, closed_class int not null, CONSTRAINT PK_CLASS PRIMARY KEY(ID) );\n"
                "create table unknown_entries( id integer unsigned not null );\n"
                "create table predef_entries( id integer not null, id_entry integer unsigned not null );\n"
                "CREATE TABLE sg_entry( ID integer unsigned NOT NULL, NAME varchar(32) NOT NULL, UNAME varchar(32) NOT NULL, ID_CLASS int NOT NULL, FREQ int, exportable int, flags int not null default 0, dic_div char(4), CONSTRAINT PK_ENTRY PRIMARY KEY(ID) );\n"
                "CREATE TABLE sg_form( ID_ENTRY int NOT NULL, IFORM int NOT NULL, NAME varchar(32) NOT NULL, ID_LEXEM int unsigned NOT NULL, id_dims int, CONSTRAINT PK_FORM PRIMARY KEY(ID_ENTRY,IFORM) );\n"
                "CREATE TABLE sg_link( ID int not null, ID_ENTRY1 int NOT NULL, ID_ENTRY2 int NOT NULL, ICOORD int NOT NULL, ISTATE int NOT NULL, tags int, CONSTRAINT PK_LINK PRIMARY KEY(ID) );\n"
                "CREATE TABLE sg_entry_coord( ID_ENTRY int NOT NULL, ICOORD int NOT NULL, ISTATE int NOT NULL );\n"
                "CREATE TABLE sg_form_coord( ID_ENTRY int NOT NULL, IFORM int NOT NULL, ICOORD int NOT NULL, ISTATE int NOT NULL );\n"
                "CREATE TABLE sg_class_coord( ID_CLASS int NOT NULL, ID_COORD int NOT NULL, COORD_TYPE int NOT NULL );\n"
                "create table class_attr_def( id int not null, id_class int not null, id_coord int not null, default_state int not null );\n"
                "CREATE TABLE sg_tag( ID int NOT NULL, NAME varchar(32) NOT NULL, CONSTRAINT PK_TAG PRIMARY KEY(ID) );\n"
                "CREATE TABLE sg_tag_value( ID_TAG int NOT NULL, IVALUE int NOT NULL, NAME varchar(32) NOT NULL, CONSTRAINT PK_TAG_VALUE PRIMARY KEY(ID_TAG,IVALUE) );\n"
                "CREATE TABLE sg_link_tag( ID int NOT NULL, ID_LINK int NOT NULL, ID_TAG int NOT NULL, IVALUE int NOT NULL, CONSTRAINT PK_LINK_TAG PRIMARY KEY(ID) );\n"
                "CREATE TABLE sg_tentry( TE_ID int NOT NULL, TE_TEXT varchar(2000) NOT NULL, TE_UTXT varchar(2000) NOT NULL, TE_TEXT32 varchar(32), TE_ID_LANGUAGE int, TE_ID_CLASS int, te_syntax_flags integer, dic_div char(4), CONSTRAINT PK_TENTRY PRIMARY KEY(te_id) );\n"
                "CREATE TABLE sg_tlink( TL_ID int NOT NULL, TL_TE_ID1 int NOT NULL, TL_TE_ID2 int NOT NULL, TL_ICOORD int NOT NULL, TL_ISTATE int NOT NULL, TL_TAGS int, CONSTRAINT PK_TLINK PRIMARY KEY(TL_ID) );\n"
                "CREATE TABLE sg_tlink_tag( TLT_ID int NOT NULL, TLT_TL_ID int NOT NULL, TLT_ID_TAG int NOT NULL, TLT_IVALUE int NOT NULL, CONSTRAINT PK_TLINK_TAG PRIMARY KEY(TLT_ID) );\n"
                "CREATE TABLE sg_tlink_flag( TLF_ID int NOT NULL, TLF_TL_ID int NOT NULL, TLF_FLAG varchar(32) NOT NULL, TLF_VALUE varchar(32) NOT NULL, CONSTRAINT PK_TLINK_FLAG PRIMARY KEY(TLF_ID) );\n"
                "create table cplx_left( cl_id int not null, cl_headword varchar(32), cl_minlen int, cl_maxlen int, CONSTRAINT PK_cplx_left PRIMARY KEY(cl_id) );\n"
                "create table tnotes( tn_id int, tn_te_id int, tn_type int, tn_format int, tn_data varchar(1000), CONSTRAINT PK_TNOTES PRIMARY KEY(tn_id) );\n"
               );

     txt.printf(
                "create table aux_form_types( id int NOT NULL PRIMARY KEY, name varchar(32) NOT NULL );\n"
                "create table aux_form( id int NOT NULL PRIMARY KEY, id_entry int NOT NULL, iform int NOT NULL, data_type int NOT NULL, data_text varchar(200) NOT NULL );\n"
                "create table aux_entry_data( id int NOT NULL PRIMARY KEY, id_entry int NOT NULL, data_type int NOT NULL, data_text varchar(200) NOT NULL );\n"
               );


     txt.printf(
                "CREATE TABLE aux_word(\n"
                "id integer PRIMARY KEY,\n"
                "aux_type INTEGER NOT NULL,\n"
                "src varchar(30),\n"
                "res varchar(200)\n"
                ");\n\n"
               );

     txt.printf(
                "create table multilexem( id int not null primary key, txt varchar(64) not null, headword varchar(64) not null, n_lexem int not null );\n"
                "create table sg_criterion( id int not null PRIMARY KEY, name varchar(64) not null, strval varchar(100) not null );\n"
                "\n" 
               );

     txt.printf(
                "CREATE TABLE paradigma( "
                " id integer PRIMARY KEY NOT NULL,"
                " front_name varchar(32),"
                " r_condition varchar(256),"
                " id_class integer,"
                " attrs VARCHAR(100)"
                ");\n\n"
  
                "CREATE TABLE paradigma_name( "
                " id integer PRIMARY KEY NOT NULL,"
                " id_paradigma integer not null,"
                " name varchar(32),"
                " uname varchar(32)"
                ");\n\n"
  
                "CREATE TABLE paradigma_form( "
                " id integer PRIMARY KEY NOT NULL,"
                " id_paradigma integer NOT NULL,"
                " rx_condition VARCHAR(100),"
                " flexer_flags VARCHAR(100),"
                " lexem_generator varchar(100) NOT NULL,"
                " dims varchar(256)"
                ");\n\n"
               );


     txt.printf(
                "CREATE TABLE word_entry_set( "
                " id integer PRIMARY KEY NOT NULL,"
                " name varchar(32) NOT NULL,"
                " ies varchar(1000000) NOT NULL"
                ");\n\n"

                "CREATE TABLE word_set( "
                " id integer PRIMARY KEY NOT NULL,"
                " name varchar(32) NOT NULL,"
                " case_sensitive integer NOT NULL,"
                " words text NOT NULL"
                ");\n\n"

                "CREATE TABLE collocation_set( "
                " id integer PRIMARY KEY NOT NULL,"
                " name varchar(32) NOT NULL,"
                " case_sensitive integer NOT NULL"
                ");\n\n"

                "CREATE TABLE collocation_set_item( "
                " id integer PRIMARY KEY NOT NULL,"
                " id_set integer NOT NULL,"
                " words varchar(250) NOT NULL,"
                " n_word integer NOT NULL,"
                " headword varchar(30) NOT NULL"
                ");\n\n"

                "CREATE TABLE collocation_headword( "
                " id integer PRIMARY KEY NOT NULL,"
                " headword varchar(32) NOT NULL,"
                " min_len integer NOT NULL,"
                " max_len integer NOT NULL"
                ");\n\n"


                "CREATE TABLE wordform_set( "
                " id integer PRIMARY KEY NOT NULL,"
                " name varchar(32) NOT NULL"
                ");\n"
 
                "CREATE TABLE wordform_set_item( "
                " id integer PRIMARY KEY NOT NULL,"
                " id_set integer NOT NULL,"
                " word varchar(32) NOT NULL,"
                " id_entry integer NOT NULL,"
                " id_coords integer NOT NULL"
                ");\n"
 
                "CREATE TABLE wordform_set_coords( "
                " id integer PRIMARY KEY NOT NULL,"
                " coords varchar(200) NOT NULL"
                ");\n\n"

               );


     txt.printf(
                "create table abc_alphabet( id integer primary key not null, name varchar(32) not null unique );\n"
                "create table abc_coord( id integer primary key not null, name varchar(32) not null unique, bistable int );\n"
                "create table abc_state( id int not null, id_coord int not null, name varchar(32) not null );\n"
                "create table abc_class( id integer primary key not null, name varchar(32) not null unique );\n"
                "create table abc_class_coord( id_class int not null, id_coord int not null, coord_type int not null );\n"
                "create table abc_entry( id integer primary key not null, name varchar(4) not null, id_class integer not null, id_alphabet integer not null, id_pairs integer not null, code integer not null );\n"
                "create table abc_form( id integer primary key not null, ordnum integer not null, id_entry int not null, id_pairs int not null, name char(1) not null, code integer not null );\n"
                "create table abc_pairs( id integer primary key not null, str_pairs varchar(60) not null unique );\n"
                "create table abc_pair( id integer primary key not null, id_pairs integer not null, id_coord integer not null, id_state integer not null );\n"
                "create table abc_criterion( id int not null PRIMARY KEY, name varchar(64) not null, strval varchar(100) not null );\n"
               );

     txt.printf(
                "CREATE TABLE abc_operation( "
                " id integer PRIMARY KEY NOT NULL,"
                " name varchar(32) NOT NULL UNIQUE"
                ");\n\n"
  
                "CREATE TABLE abc_operation_item( "
                " id integer PRIMARY KEY NOT NULL,"
                " id_operation integer NOT NULL,"
                " src_char_ucs4 integer NOT NULL,"
                " res_char_ucs4 integer NOT NULL,"
                " src_char varchar(2) NOT NULL,"
                " res_char varchar(2) NOT NULL"
                ");\n\n"

                "CREATE TABLE tr_functions( "
                " segment_no integer,"
                " marker varchar(3) NOT NULL,"
                " bin varchar(100000) NOT NULL"
                ");\n\n"

  
                "CREATE TABLE crop_rule( "
                " id integer PRIMARY KEY NOT NULL,"
                " name varchar(32),"
                " r_condition varchar(256) NOT NULL,"
                " r_result varchar(256) NOT NULL,"
                " id_language integer NOT NULL,"
                " is_prefix integer NOT NULL,"
                " is_affix integer NOT NULL,"
                " is_regex integer NOT NULL,"
                " id_src integer,"
                " case_sensitive integer NOT NULL,"
                " rel integer NOT NULL"
                ");\n\n"


                "CREATE TABLE unbreakable( "
                " id integer PRIMARY KEY NOT NULL,"
                " name varchar(32) NOT NULL,"
                " id_src integer,"
                " id_language integer NOT NULL,"
                " pattern varchar(100) NOT NULL,"
                " is_regex integer NOT NULL"
                ");\n\n"

                "CREATE TABLE recog_rule( "
                " id integer PRIMARY KEY NOT NULL,"
                " name varchar(32) NOT NULL,"
                " id_src integer,"
                " id_language integer NOT NULL,"
                " is_regex integer not null,"
                " is_syllab integer not null,"
                " is_prefix integer not null,"
                " is_affix integer not null,"
                " r_condition varchar(100) not null,"
                " case_sensitive integer not null,"
                " word varchar(100),"
                " id_entry integer not null,"
                " rel integer not null,"
                " coords varchar(300) not null"
                ");\n\n"

                "CREATE TABLE ph_rule( "
                " id integer PRIMARY KEY NOT NULL,"
                " name varchar(32) NOT NULL,"
                " id_src integer,"
                " id_language integer NOT NULL,"
                " r_condition varchar(30) not null,"
                " r_result varchar(30) not null,"
                " is_prefix integer not null,"
                " is_affix integer not null,"
                " rel integer not null"
                ");\n\n"

                "CREATE TABLE SynPatternTree( "
                " id integer PRIMARY KEY NOT NULL,"
                " id_tree integer NOT NULL,"
                " id0 integer,"
                " segment_no integer,"
                " id_language integer NOT NULL,"
                " name varchar(32) NOT NULL,"
                " uname varchar(32) NOT NULL,"
                " pattern_type integer NOT NULL,"
                " bin BLOB NOT NULL"
                ");\n\n"

                "CREATE TABLE lang_usage( "
                " id_language integer not null,"
                " is_input integer not null,"
                " is_output integer not null,"
                " is_default integer not null"
                ");\n\n"

                "CREATE TABLE src_filename( "
                " id integer PRIMARY KEY NOT NULL,"
                " filepath varchar(2000) NOT NULL,"
                " filepath0 varchar(2000) NOT NULL"
                ");\n\n"
  
                "CREATE TABLE src_location( "
                " id integer PRIMARY KEY NOT NULL,"
                " id_filename integer NOT NULL,"
                " line_no integer NOT NULL,"
                " column_no integer NOT NULL"
                ");\n\n"

                "\n" 
               );

     txt.printf(
                "CREATE TABLE kb_facts(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_language integer NOT NULL,\n"
                " name varchar(100) NOT NULL,\n"
                " n_arg integer NOT NULL,\n"
                " n_ret integer NOT NULL,\n"
                " ret_type integer NOT NULL,\n"
                " query_mode integer NOT NULL,\n"
                " violation_score integer NOT NULL,\n"
                " violation_handler integer NOT NULL\n"
                ");\n\n"

                "CREATE TABLE kb_fact(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_group integer NOT NULL,\n"
                " boolean_return integer,\n"
                " false_score integer,\n"
                " integer_return integer\n"
                ");\n\n"

                "CREATE TABLE kb_argument_point( \n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_fact integer,\n"
                " argument_index integer NOT NULL,\n"
                " word_text varchar(100),\n"
                " id_entry integer,\n"
                " id_class integer,\n"
                " is_regex integer NOT NULL,\n"
                " case_sensitive integer NOT NULL,\n"
                " id_metaentry integer NOT NULL,\n"
                " wordentryset_name varchar(100),\n"
                " wordset_name varchar(100),\n"
                " n_coords integer,\n"
                " id_coord1 integer,\n"
                " id_state1 integer,\n"
                " affirm1 integer,\n"
                " id_coord2 integer,\n"
                " id_state2 integer,\n"
                " affirm2 integer,\n"
                " id_coord3 integer,\n"
                " id_state3 integer,\n"
                " affirm3 integer,\n"
                " id_coord4 integer,\n"
                " id_state4 integer,\n"
                " affirm4 integer,\n"
                " thesauruscheck_link integer,\n"
                " thesauruscheck_entry integer,\n"
                "  is_positive integer NOT NULL\n"
                " );\n\n"
               );


     txt.printf(
                "CREATE TABLE kb_fact_index1(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_group integer NOT NULL,\n"
                " id_fact integer NOT NULL,\n"
                " word1 varchar(32),\n"
                " word2 varchar(32),\n"
                " word3 varchar(32),\n"
                " word4 varchar(32),\n"
                " word5 varchar(32)\n"
                ");\n\n"


                "CREATE TABLE kb_fact_index2(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_group integer NOT NULL,\n"
                " id_fact integer NOT NULL,\n"
                " id_entry1 integer,\n"
                " id_entry2 integer,\n"
                " id_entry3 integer,\n"
                " id_entry4 integer,\n"
                " id_entry5 integer\n"
                ");\n\n"

                "CREATE TABLE generic_tree_scorer(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_head_point integer NOT NULL,\n"
                " id_group integer NOT NULL,\n"
                " score_expr varchar(100),\n"
                " score_type integer NOT NULL\n"
                ");\n\n"

                "CREATE TABLE ts_predicate(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_point integer NOT NULL,\n"
                " func_name varchar(20) NOT NULL,\n"
                " narg integer NOT NULL,\n"
                " id_class1 integer NOT NULL\n"
                ");\n\n"
               );

     txt.printf(
                "CREATE TABLE slb_rule(\n"
                "id integer PRIMARY KEY NOT NULL,\n"
                "name varchar(32) NOT NULL UNIQUE,\n"
                "id_src integer NOT NULL,\n"
                "id_language integer NOT NULL,\n"
                "cursor_shift integer NOT NULL\n"
                ");\n\n"

                "CREATE TABLE slb_condition_point(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_rule integer NOT NULL,\n"
                " point_index integer NOT NULL,\n"
                " n_char integer NOT NULL,\n"
                " char_text varchar(30) NOT NULL,\n"
                " char_ucs4 varchar(30) NOT NULL,\n"
                " id_class integer NOT NULL,\n"
                " id_entry integer NOT NULL,\n"
                " n_coord integer NOT NULL,\n"
                " id_coord0 integer NOT NULL,\n"
                " id_state0 integer NOT NULL,\n"
                " is_left_boundary integer NOT NULL,\n"
                " is_right_boundary integer NOT NULL,\n"
                " is_positive integer NOT NULL\n"
                ");\n\n"

                "CREATE TABLE slb_result_point(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_rule integer NOT NULL,\n"
                " point_index integer NOT NULL,\n"
                " copy_index integer NOT NULL,\n"
                " merge_index0 integer NOT NULL,\n"
                " merge_count integer NOT NULL\n"
                ");\n\n"
               );

     txt.printf(
                " CREATE TABLE ts_head_word(\n"
                "  id integer NOT NULL PRIMARY KEY,\n"
                "  word varchar(100) NOT NULL,\n"
                "  id_head_point integer NOT NULL,\n"
                " score_type integer NOT NULL,\n"
                " score_expr varchar(100),"
                " root_node integer NOT NULL,\n"
                " id_group integer NOT NULL\n"
                " );\n\n"

                "CREATE TABLE ts_head_lemma(\n"
                " id integer NOT NULL PRIMARY KEY,\n"
                " id_entry integer NOT NULL,\n"
                " id_head_point integer NOT NULL,\n"
                " score_type integer NOT NULL,\n"
                " score_expr varchar(100),"
                " root_node integer NOT NULL,\n"
                " id_group integer NOT NULL\n"
                ");\n\n"

                "CREATE TABLE ts_point(\n"
                " id integer NOT NULL PRIMARY KEY,\n"
                " id_parent integer,\n"
                " id_group integer,\n"
                " word_text varchar(100),\n"
                " id_entry integer NOT NULL,\n"
                " id_metaentry integer NOT NULL,\n"
                " id_class integer NOT NULL,\n"
                " wordentryset_name varchar(100),\n"
                " wordset_name varchar(100),\n"
                " wordformset_name varchar(100),\n"
                " n_coords integer NOT NULL,\n"
                " id_coord1 integer,\n"
                " id_state1 integer,\n"
                " affirm1 integer,\n"
                " id_coord2 integer,\n"
                " id_state2 integer,\n"
                " affirm2 integer,\n"
                " id_coord3 integer,\n"
                " id_state3 integer,\n"
                " affirm3 integer,\n"
                " id_coord4 integer,\n"
                " id_state4 integer,\n"
                " affirm4 integer,\n"
                " thesauruscheck_link integer NOT NULL,\n"
                " thesauruscheck_entry integer NOT NULL,\n"
                " is_positive integer NOT NULL,\n"
                " children_quantification_min_count integer NOT NULL,\n"
                " children_quantification_max_count integer NOT NULL,\n"
                " n_setcheckers integer NOT NULL,\n"
                " set_name1 varchar(50),\n"
                " set_type1 integer NOT NULL,\n"
                " set_affirm1 integer NOT NULL,\n"
                " set_name2 varchar(50),\n"
                " set_type2 integer NOT NULL,\n"
                " set_affirm2 integer NOT NULL,\n"
                " set_name3 varchar(50),\n"
                " set_type3 integer NOT NULL,\n"
                " set_affirm3 integer NOT NULL,\n"
                " link_type integer NOT NULL,\n"
                " relative_position integer NOT NULL,\n"
                " quantification_min_count integer NOT NULL,\n"
                " quantification_max_count integer NOT NULL,\n"
                " marker varchar(30),"
                " n_backref integer NOT NULL,"

                " br_affirm_0 integer,\n"
                " br_coord0_0 integer,\n"
                " br_marker_0 varchar(30),\n"
                " br_coord1_0 integer,\n"
                " br_for_group_0 integer,\n"

                " br_affirm_1 integer,\n"
                " br_coord0_1 integer,\n"
                " br_marker_1 varchar(30),\n"
                " br_coord1_1 integer,\n"
                " br_for_group_1 integer,\n"

                " br_affirm_2 integer,\n"
                " br_coord0_2 integer,\n"
                " br_marker_2 varchar(30),\n"
                " br_coord1_2 integer,\n"
                " br_for_group_2 integer,\n"

                " id_src integer\n"
                ");\n\n"
               );

     txt.printf(
                "CREATE TABLE ts_group(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " name varchar(30) NOT NULL,\n"
                " allow_unmatched_children integer NOT NULL\n"
                ");\n\n"

                "CREATE TABLE ts_group2root(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_group integer NOT NULL,\n"
                " id_root integer NOT NULL\n"
                ");\n\n"
               );

     txt.printf(
                " CREATE TABLE metaentry( \n"
                " id integer NOT NULL PRIMARY KEY,\n"
                " id_class integer not null,\n"
                " name varchar(100) NOT NULL\n"
                " );\n" );

     txt.printf(
                " CREATE TABLE metaentry_item( \n"
                " id integer NOT NULL PRIMARY KEY,\n"
                " id_metaentry integer not null,\n"
                " id_entry integer not null\n"
                " );\n\n" );

     txt.printf(
                "CREATE TABLE omonym(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " entry_name varchar(100) NOT NULL,\n"
                " id_class integer NOT NULL\n"
                ");\n"
               );

     txt.printf(
                "CREATE TABLE word_assoc(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_src integer,\n"
                " id_entry integer NOT NULL,\n"
                " id_entry1 integer,\n"
                " word1 varchar(40),\n"
                " id_metaentry1 integer,\n"
                " id_entry2 integer,\n"
                " word2 varchar(40),\n"
                " id_metaentry2 integer,\n"
                " link_type integer,\n"
                " link_entry integer,\n"
                " set_name varchar(40),\n"
                " set_type integer,\n"
                " score integer NOT NULL\n"
                ");\n\n"
               );


     txt.printf(
                "CREATE TABLE predicate_template(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_src integer,\n"
                " src varchar(250) NOT NULL,\n"
                " params varchar(100)\n"
                ");\n"
               );
    }
   else if( sql_version.type==SQL_Production::Postgres )
    {
     if( sql_version.IsUtf8() )
      txt.printf( "set client_encoding='utf8';\n\n" );
     else
      txt.printf( "set client_encoding='win1251';\n\n" );

     int itable=0;
     while( table_names[itable]!=NULL )
     {
      txt.printf( "%us\n", sql_version.DropTable( table_names[itable] ).c_str() );
      itable++;
     }

     txt.printf(
                "create table coord_pairs( id int not null PRIMARY KEY, pairs varchar(1000) not null, str_pairs varchar(1000) not null );\n"
                "create table tag_set( id int not null PRIMARY KEY, tags varchar(1000) not null );\n"
                "CREATE TABLE sg_language( ID int NOT NULL, NAME varchar(32) NOT NULL, CONSTRAINT PK_LANGUAGE PRIMARY KEY(ID) );\n"
                "create table lang_alphabet( id int not null PRIMARY KEY, id_language int not null, id_alphabet int not null, ordering int not null );\n"
                "create table lang_link( id int not null PRIMARY KEY, id_language int not null, id_state int not null, id_language2 int not null );\n"
                "create table lang_param( id int not null PRIMARY KEY, id_language int not null, param_name varchar(32) not null, param_value varchar(200) not null, ordering int not null );\n"
                "CREATE TABLE sg_lexem( ID int , NAME varchar(32) NOT NULL, CONSTRAINT PK_LEXEM PRIMARY KEY(ID) );\n"
                "CREATE TABLE sg_coord( ID integer NOT NULL, NAME varchar(32) NOT NULL, BISTABLE integer NOT NULL, CONSTRAINT PK_SG_COORD PRIMARY KEY(ID) );\n"
                "CREATE TABLE sg_state( ID integer NOT NULL, ID_COORD integer NOT NULL, NAME varchar(32) NOT NULL, id_parent int not null, weight int not null, CONSTRAINT PK_COORD PRIMARY KEY(ID,ID_COORD) );\n"
                "CREATE TABLE sg_class( ID int, NAME varchar(32) NOT NULL, NAME_ALIASE varchar(32), ID_LANG int, weight int not null, closed_class int not null, CONSTRAINT PK_CLASS PRIMARY KEY(ID) );\n"
                "CREATE TABLE sg_entry( ID integer  NOT NULL, NAME varchar(32) NOT NULL, UNAME varchar(32) NOT NULL, ID_CLASS int NOT NULL, FREQ int, exportable int, flags int not null default 0, dic_div char(4), CONSTRAINT PK_ENTRY PRIMARY KEY(ID) );\n"
                "CREATE TABLE sg_form( ID_ENTRY int NOT NULL, IFORM int NOT NULL, NAME varchar(32) NOT NULL, ID_LEXEM int  NOT NULL, id_dims int, CONSTRAINT PK_FORM PRIMARY KEY(ID_ENTRY,IFORM) );\n"
                "CREATE TABLE sg_link( ID int not null, ID_ENTRY1 int NOT NULL, ID_ENTRY2 int NOT NULL, ICOORD int NOT NULL, ISTATE int NOT NULL, tags int, CONSTRAINT PK_LINK PRIMARY KEY(ID) );\n"
                "CREATE TABLE sg_entry_coord( ID_ENTRY int NOT NULL, ICOORD int NOT NULL, ISTATE int NOT NULL );\n"
                "CREATE TABLE sg_form_coord( ID_ENTRY int NOT NULL, IFORM int NOT NULL, ICOORD int NOT NULL, ISTATE int NOT NULL );\n"
                "CREATE TABLE sg_class_coord( ID_CLASS int NOT NULL, ID_COORD int NOT NULL, COORD_TYPE int NOT NULL );\n"
                "create table class_attr_def( id int not null, id_class int not null, id_coord int not null, default_state int not null );\n"
                "CREATE TABLE sg_tag( ID int NOT NULL, NAME varchar(32) NOT NULL, CONSTRAINT PK_TAG PRIMARY KEY(ID) );\n"
                "CREATE TABLE sg_tag_value( ID_TAG int NOT NULL, IVALUE int NOT NULL, NAME varchar(32) NOT NULL, CONSTRAINT PK_TAG_VALUE PRIMARY KEY(ID_TAG,IVALUE) );\n"
                "CREATE TABLE sg_link_tag( ID int NOT NULL, ID_LINK int NOT NULL, ID_TAG int NOT NULL, IVALUE int NOT NULL, CONSTRAINT PK_LINK_TAG PRIMARY KEY(ID) );\n"
                "CREATE TABLE sg_tentry( TE_ID int NOT NULL, TE_TEXT varchar(2000) NOT NULL, TE_UTXT varchar(2000) NOT NULL, TE_TEXT32 varchar(32), TE_ID_LANGUAGE int, TE_ID_CLASS int, te_syntax_flags integer, dic_div char(4), CONSTRAINT PK_TENTRY PRIMARY KEY(te_id) );\n"
                "CREATE TABLE sg_tlink( TL_ID int NOT NULL, TL_TE_ID1 int NOT NULL, TL_TE_ID2 int NOT NULL, TL_ICOORD int NOT NULL, TL_ISTATE int NOT NULL, TL_TAGS int, CONSTRAINT PK_TLINK PRIMARY KEY(TL_ID) );\n"
                "CREATE TABLE sg_tlink_tag( TLT_ID int NOT NULL, TLT_TL_ID int NOT NULL, TLT_ID_TAG int NOT NULL, TLT_IVALUE int NOT NULL, CONSTRAINT PK_TLINK_TAG PRIMARY KEY(TLT_ID) );\n"
                "CREATE TABLE sg_tlink_flag( TLF_ID int NOT NULL, TLF_TL_ID int NOT NULL, TLF_FLAG varchar(32) NOT NULL, TLF_VALUE varchar(32) NOT NULL, CONSTRAINT PK_TLINK_FLAG PRIMARY KEY(TLF_ID) );\n"
                "create table aux_form_types( id int NOT NULL PRIMARY KEY, name varchar(32) NOT NULL );\n"
                "create table aux_form( id int NOT NULL PRIMARY KEY, id_entry int NOT NULL, iform int NOT NULL, data_type int NOT NULL, data_text varchar(200) NOT NULL );\n"
                "create table aux_entry_data( id int NOT NULL PRIMARY KEY, id_entry int NOT NULL, data_type int NOT NULL, data_text varchar(200) NOT NULL );\n"
               );

     txt.printf(
                "CREATE TABLE aux_word(\n"
                "id integer PRIMARY KEY,\n"
                "aux_type INTEGER NOT NULL,\n"
                "src varchar(30),\n"
                "res varchar(200)\n"
                ");\n\n"
               );

     txt.printf(
                "create table multilexem( id int not null primary key, txt varchar(64) not null, headword varchar(64) not null, n_lexem int not null );\n"
                "create table sg_criterion( id int not null PRIMARY KEY, name varchar(64) not null, strval varchar(100) not null );\n"
                "\n" 
               );

     txt.printf(
                "CREATE TABLE paradigma( "
                " id integer PRIMARY KEY NOT NULL,"
                " front_name varchar(32),"
                " r_condition varchar(256),"
                " id_class integer,"
                " attrs VARCHAR(100)"
                ");\n\n"
  
                "CREATE TABLE paradigma_name( "
                " id integer PRIMARY KEY NOT NULL,"
                " id_paradigma integer not null,"
                " name varchar(32),"
                " uname varchar(32)"
                ");\n\n"
  
                "CREATE TABLE paradigma_form( "
                " id integer PRIMARY KEY NOT NULL,"
                " id_paradigma integer NOT NULL,"
                " rx_condition VARCHAR(100),"
                " flexer_flags VARCHAR(100),"
                " lexem_generator varchar(100) NOT NULL,"
                " dims varchar(256)"
                ");\n\n"
               );

     txt.printf(
                "create table abc_alphabet( id integer primary key not null, name varchar(32) not null unique );\n"
                "create table abc_coord( id integer primary key not null, name varchar(32) not null unique, bistable int );\n"
                "create table abc_state( id int not null, id_coord int not null, name varchar(32) not null );\n"
                "create table abc_class( id integer primary key not null, name varchar(32) not null unique );\n"
                "create table abc_class_coord( id_class int not null, id_coord int not null, coord_type int not null );\n"
                "create table abc_entry( id integer primary key not null, name varchar(4) not null, id_class integer not null, id_alphabet integer not null, id_pairs integer not null, code integer not null );\n"
                "create table abc_form( id integer primary key not null, ordnum integer not null, id_entry int not null, id_pairs int not null, name char(1) not null, code integer not null );\n"
                "create table abc_pairs( id integer primary key not null, str_pairs varchar(60) not null unique );\n"
                "create table abc_pair( id integer primary key not null, id_pairs integer not null, id_coord integer not null, id_state integer not null );\n"
                "create table abc_criterion( id int not null PRIMARY KEY, name varchar(64) not null, strval varchar(100) not null );\n"
               );

     txt.printf(
                "CREATE TABLE metaentry( \n"
                "id integer NOT NULL PRIMARY KEY,\n"
                "id_class integer not null,\n"
                "name varchar(100) NOT NULL\n"
                ");\n" );

     txt.printf(
                "CREATE TABLE metaentry_item( \n"
                "id integer NOT NULL PRIMARY KEY,\n"
                "id_metaentry integer not null,\n"
                "id_entry integer not null\n"
                ");\n\n" );

     txt.printf(
                "CREATE TABLE omonym(\n"
                "id integer PRIMARY KEY NOT NULL,\n"
                "entry_name varchar(100) NOT NULL,\n"
                "id_class integer NOT NULL\n"
                ");\n"
               );

     txt.printf(
                "create table unknown_entries( id integer not null );\n"
                "create table predef_entries( id integer not null, id_entry integer not null );\n"
                "create table endings( id int PRIMARY KEY, ending varchar(40) not null, id_language int not null, nform int not null, sumfreq int not null );\n"
                "create table wordform_frequency( id int PRIMARY KEY, id_entry int not null, iform int not null, freq int not null );\n"
                "create table ending_stat( id_language int not null, max_len int not null );\n"
               );


     // ---
/*
     txt.printf(
                "create table misspelling( id int PRIMARY KEY, id_language int not null, original_word varchar(64) not null, substitution varchar(64) not null );\n"
                "create table cplx_left( cl_id int not null, cl_headword varchar(32), cl_minlen int, cl_maxlen int, CONSTRAINT PK_cplx_left PRIMARY KEY(cl_id) );\n"
                "create table tnotes( tn_id int, tn_te_id int, tn_type int, tn_format int, tn_data varchar(1000), CONSTRAINT PK_TNOTES PRIMARY KEY(tn_id) );\n"
               );


     txt.printf(
                "CREATE TABLE word_entry_set( "
                " id integer PRIMARY KEY NOT NULL,"
                " name varchar(32) NOT NULL,"
                " ies varchar(1000000) NOT NULL"
                ");\n\n"

                "CREATE TABLE word_set( "
                " id integer PRIMARY KEY NOT NULL,"
                " name varchar(32) NOT NULL,"
                " case_sensitive integer NOT NULL,"
                " words text NOT NULL"
                ");\n\n"

                "CREATE TABLE collocation_set( "
                " id integer PRIMARY KEY NOT NULL,"
                " name varchar(32) NOT NULL,"
                " case_sensitive integer NOT NULL"
                ");\n\n"

                "CREATE TABLE collocation_set_item( "
                " id integer PRIMARY KEY NOT NULL,"
                " id_set integer NOT NULL,"
                " words varchar(250) NOT NULL,"
                " n_word integer NOT NULL,"
                " headword varchar(30) NOT NULL"
                ");\n\n"

                "CREATE TABLE collocation_headword( "
                " id integer PRIMARY KEY NOT NULL,"
                " headword varchar(32) NOT NULL,"
                " min_len integer NOT NULL,"
                " max_len integer NOT NULL"
                ");\n\n"


                "CREATE TABLE wordform_set( "
                " id integer PRIMARY KEY NOT NULL,"
                " name varchar(32) NOT NULL"
                ");\n"
 
                "CREATE TABLE wordform_set_item( "
                " id integer PRIMARY KEY NOT NULL,"
                " id_set integer NOT NULL,"
                " word varchar(32) NOT NULL,"
                " id_entry integer NOT NULL,"
                " id_coords integer NOT NULL"
                ");\n"
 
                "CREATE TABLE wordform_set_coords( "
                " id integer PRIMARY KEY NOT NULL,"
                " coords varchar(200) NOT NULL"
                ");\n\n"
               );

     txt.printf(
                "CREATE TABLE abc_operation( "
                " id integer PRIMARY KEY NOT NULL,"
                " name varchar(32) NOT NULL UNIQUE"
                ");\n\n"
  
                "CREATE TABLE abc_operation_item( "
                " id integer PRIMARY KEY NOT NULL,"
                " id_operation integer NOT NULL,"
                " src_char_ucs4 integer NOT NULL,"
                " res_char_ucs4 integer NOT NULL,"
                " src_char varchar(2) NOT NULL,"
                " res_char varchar(2) NOT NULL"
                ");\n\n"

                "CREATE TABLE tr_functions( "
                " segment_no integer,"
                " marker varchar(3) NOT NULL,"
                " bin varchar(100000) NOT NULL"
                ");\n\n"

  
                "CREATE TABLE crop_rule( "
                " id integer PRIMARY KEY NOT NULL,"
                " name varchar(32),"
                " r_condition varchar(256) NOT NULL,"
                " r_result varchar(256) NOT NULL,"
                " id_language integer NOT NULL,"
                " is_prefix integer NOT NULL,"
                " is_affix integer NOT NULL,"
                " is_regex integer NOT NULL,"
                " id_src integer,"
                " case_sensitive integer NOT NULL,"
                " rel integer NOT NULL"
                ");\n\n"


                "CREATE TABLE unbreakable( "
                " id integer PRIMARY KEY NOT NULL,"
                " name varchar(32) NOT NULL,"
                " id_src integer,"
                " id_language integer NOT NULL,"
                " pattern varchar(100) NOT NULL,"
                " is_regex integer NOT NULL"
                ");\n\n"

                "CREATE TABLE recog_rule( "
                " id integer PRIMARY KEY NOT NULL,"
                " name varchar(32) NOT NULL,"
                " id_src integer,"
                " id_language integer NOT NULL,"
                " is_regex integer not null,"
                " is_syllab integer not null,"
                " is_prefix integer not null,"
                " is_affix integer not null,"
                " r_condition varchar(100) not null,"
                " case_sensitive integer not null,"
                " word varchar(100),"
                " id_entry integer not null,"
                " rel integer not null,"
                " coords varchar(300) not null"
                ");\n\n"

                "CREATE TABLE ph_rule( "
                " id integer PRIMARY KEY NOT NULL,"
                " name varchar(32) NOT NULL,"
                " id_src integer,"
                " id_language integer NOT NULL,"
                " r_condition varchar(30) not null,"
                " r_result varchar(30) not null,"
                " is_prefix integer not null,"
                " is_affix integer not null,"
                " rel integer not null"
                ");\n\n"

                "CREATE TABLE SynPatternTree( "
                " id integer PRIMARY KEY NOT NULL,"
                " id_tree integer NOT NULL,"
                " id0 integer,"
                " segment_no integer,"
                " id_language integer NOT NULL,"
                " name varchar(32) NOT NULL,"
                " uname varchar(32) NOT NULL,"
                " pattern_type integer NOT NULL,"
                " bin BLOB NOT NULL"
                ");\n\n"

                "CREATE TABLE lang_usage( "
                " id_language integer not null,"
                " is_input integer not null,"
                " is_output integer not null,"
                " is_default integer not null"
                ");\n\n"

                "CREATE TABLE src_filename( "
                " id integer PRIMARY KEY NOT NULL,"
                " filepath varchar(2000) NOT NULL,"
                " filepath0 varchar(2000) NOT NULL"
                ");\n\n"
  
                "CREATE TABLE src_location( "
                " id integer PRIMARY KEY NOT NULL,"
                " id_filename integer NOT NULL,"
                " line_no integer NOT NULL,"
                " column_no integer NOT NULL"
                ");\n\n"

                "\n" 
               );

     txt.printf(
                "CREATE TABLE kb_facts(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_language integer NOT NULL,\n"
                " name varchar(100) NOT NULL,\n"
                " n_arg integer NOT NULL,\n"
                " n_ret integer NOT NULL,\n"
                " ret_type integer NOT NULL,\n"
                " query_mode integer NOT NULL,\n"
                " violation_score integer NOT NULL,\n"
                " violation_handler integer NOT NULL\n"
                ");\n\n"

                "CREATE TABLE kb_fact(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_group integer NOT NULL,\n"
                " boolean_return integer,\n"
                " false_score integer,\n"
                " integer_return integer\n"
                ");\n\n"

                "CREATE TABLE kb_argument_point( \n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_fact integer,\n"
                " argument_index integer NOT NULL,\n"
                " word_text varchar(100),\n"
                " id_entry integer,\n"
                " id_class integer,\n"
                " is_regex integer NOT NULL,\n"
                " case_sensitive integer NOT NULL,\n"
                " id_metaentry integer NOT NULL,\n"
                " wordentryset_name varchar(100),\n"
                " wordset_name varchar(100),\n"
                " n_coords integer,\n"
                " id_coord1 integer,\n"
                " id_state1 integer,\n"
                " affirm1 integer,\n"
                " id_coord2 integer,\n"
                " id_state2 integer,\n"
                " affirm2 integer,\n"
                " id_coord3 integer,\n"
                " id_state3 integer,\n"
                " affirm3 integer,\n"
                " id_coord4 integer,\n"
                " id_state4 integer,\n"
                " affirm4 integer,\n"
                " thesauruscheck_link integer,\n"
                " thesauruscheck_entry integer,\n"
                "  is_positive integer NOT NULL\n"
                " );\n\n"
               );


     txt.printf(
                "CREATE TABLE kb_fact_index1(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_group integer NOT NULL,\n"
                " id_fact integer NOT NULL,\n"
                " word1 varchar(32),\n"
                " word2 varchar(32),\n"
                " word3 varchar(32),\n"
                " word4 varchar(32),\n"
                " word5 varchar(32)\n"
                ");\n\n"


                "CREATE TABLE kb_fact_index2(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_group integer NOT NULL,\n"
                " id_fact integer NOT NULL,\n"
                " id_entry1 integer,\n"
                " id_entry2 integer,\n"
                " id_entry3 integer,\n"
                " id_entry4 integer,\n"
                " id_entry5 integer\n"
                ");\n\n"

                "CREATE TABLE generic_tree_scorer(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_head_point integer NOT NULL,\n"
                " id_group integer NOT NULL,\n"
                " score_expr varchar(100),\n"
                " score_type integer NOT NULL\n"
                ");\n\n"

                "CREATE TABLE ts_predicate(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_point integer NOT NULL,\n"
                " func_name varchar(20) NOT NULL,\n"
                " narg integer NOT NULL,\n"
                " id_class1 integer NOT NULL\n"
                ");\n\n"
               );

     txt.printf(
                "CREATE TABLE slb_rule(\n"
                "id integer PRIMARY KEY NOT NULL,\n"
                "name varchar(32) NOT NULL UNIQUE,\n"
                "id_src integer NOT NULL,\n"
                "id_language integer NOT NULL,\n"
                "cursor_shift integer NOT NULL\n"
                ");\n\n"

                "CREATE TABLE slb_condition_point(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_rule integer NOT NULL,\n"
                " point_index integer NOT NULL,\n"
                " n_char integer NOT NULL,\n"
                " char_text varchar(30) NOT NULL,\n"
                " char_ucs4 varchar(30) NOT NULL,\n"
                " id_class integer NOT NULL,\n"
                " id_entry integer NOT NULL,\n"
                " n_coord integer NOT NULL,\n"
                " id_coord0 integer NOT NULL,\n"
                " id_state0 integer NOT NULL,\n"
                " is_left_boundary integer NOT NULL,\n"
                " is_right_boundary integer NOT NULL,\n"
                " is_positive integer NOT NULL\n"
                ");\n\n"

                "CREATE TABLE slb_result_point(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_rule integer NOT NULL,\n"
                " point_index integer NOT NULL,\n"
                " copy_index integer NOT NULL,\n"
                " merge_index0 integer NOT NULL,\n"
                " merge_count integer NOT NULL\n"
                ");\n\n"
               );


     txt.printf(
                " CREATE TABLE ts_head_word(\n"
                "  id integer NOT NULL PRIMARY KEY,\n"
                "  word varchar(100) NOT NULL,\n"
                "  id_head_point integer NOT NULL,\n"
                " score_type integer NOT NULL,\n"
                " score_expr varchar(100),"
                " root_node integer NOT NULL,\n"
                " id_group integer NOT NULL\n"
                " );\n\n"

                "CREATE TABLE ts_head_lemma(\n"
                " id integer NOT NULL PRIMARY KEY,\n"
                " id_entry integer NOT NULL,\n"
                " id_head_point integer NOT NULL,\n"
                " score_type integer NOT NULL,\n"
                " score_expr varchar(100),"
                " root_node integer NOT NULL,\n"
                " id_group integer NOT NULL\n"
                ");\n\n"

                "CREATE TABLE ts_point(\n"
                " id integer NOT NULL PRIMARY KEY,\n"
                " id_parent integer,\n"
                " id_group integer,\n"
                " word_text varchar(100),\n"
                " id_entry integer NOT NULL,\n"
                " id_metaentry integer NOT NULL,\n"
                " id_class integer NOT NULL,\n"
                " wordentryset_name varchar(100),\n"
                " wordset_name varchar(100),\n"
                " wordformset_name varchar(100),\n"
                " n_coords integer NOT NULL,\n"
                " id_coord1 integer,\n"
                " id_state1 integer,\n"
                " affirm1 integer,\n"
                " id_coord2 integer,\n"
                " id_state2 integer,\n"
                " affirm2 integer,\n"
                " id_coord3 integer,\n"
                " id_state3 integer,\n"
                " affirm3 integer,\n"
                " id_coord4 integer,\n"
                " id_state4 integer,\n"
                " affirm4 integer,\n"
                " thesauruscheck_link integer NOT NULL,\n"
                " thesauruscheck_entry integer NOT NULL,\n"
                " is_positive integer NOT NULL,\n"
                " children_quantification_min_count integer NOT NULL,\n"
                " children_quantification_max_count integer NOT NULL,\n"
                " n_setcheckers integer NOT NULL,\n"
                " set_name1 varchar(50),\n"
                " set_type1 integer NOT NULL,\n"
                " set_affirm1 integer NOT NULL,\n"
                " set_name2 varchar(50),\n"
                " set_type2 integer NOT NULL,\n"
                " set_affirm2 integer NOT NULL,\n"
                " set_name3 varchar(50),\n"
                " set_type3 integer NOT NULL,\n"
                " set_affirm3 integer NOT NULL,\n"
                " link_type integer NOT NULL,\n"
                " relative_position integer NOT NULL,\n"
                " quantification_min_count integer NOT NULL,\n"
                " quantification_max_count integer NOT NULL,\n"
                " marker varchar(30),"
                " n_backref integer NOT NULL,"

                " br_affirm_0 integer,\n"
                " br_coord0_0 integer,\n"
                " br_marker_0 varchar(30),\n"
                " br_coord1_0 integer,\n"
                " br_for_group_0 integer,\n"

                " br_affirm_1 integer,\n"
                " br_coord0_1 integer,\n"
                " br_marker_1 varchar(30),\n"
                " br_coord1_1 integer,\n"
                " br_for_group_1 integer,\n"

                " br_affirm_2 integer,\n"
                " br_coord0_2 integer,\n"
                " br_marker_2 varchar(30),\n"
                " br_coord1_2 integer,\n"
                " br_for_group_2 integer,\n"

                " id_src integer\n"
                ");\n\n"
               );

     txt.printf(
                "CREATE TABLE ts_group(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " name varchar(30) NOT NULL,\n"
                " allow_unmatched_children integer NOT NULL\n"
                ");\n\n"

                "CREATE TABLE ts_group2root(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_group integer NOT NULL,\n"
                " id_root integer NOT NULL\n"
                ");\n\n"
               );

     txt.printf(
                "CREATE TABLE word_assoc(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_src integer,\n"
                " id_entry integer NOT NULL,\n"
                " id_entry1 integer,\n"
                " word1 varchar(40),\n"
                " id_metaentry1 integer,\n"
                " id_entry2 integer,\n"
                " word2 varchar(40),\n"
                " id_metaentry2 integer,\n"
                " link_type integer,\n"
                " link_entry integer,\n"
                " set_name varchar(40),\n"
                " set_type integer,\n"
                " score integer NOT NULL\n"
                ");\n\n"
               );


     txt.printf(
                "CREATE TABLE predicate_template(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_src integer,\n"
                " src varchar(250) NOT NULL,\n"
                " params varchar(100)\n"
                ");\n"
               );
      */
    } // end of PostgresSQL
   else if( sql_version.type==SQL_Production::FireBird )
    {
     const int lexlen = lem::UCString::max_len*6+1; // for utf8 encoding

     int itable=0;
     while( table_names[itable]!=NULL )
     {
      txt.printf( "%us\n", sql_version.DropTable( table_names[itable] ).c_str() );
      itable++;
     }

     const char* seq_names[]={
                              "g_sg_lexem",
                              "g_aux_form_types",
                              "g_aux_form",
                              "g_aux_entry_data",
                              "g_sg_entry",
                              "g_sg_link",
                              "g_sg_link_tag",
                              "g_sg_tlink",
                              "g_sg_tlink_tag",
                              "g_sg_tlink_flag",
                              "g_sg_tentry",
                              "g_tnotes",
                              "g_cplx_left",
                              "g_multilexem",
                              "g_coord_pairs",
                              "g_tag_set",
                              NULL };

     int iseq=0;
     while( seq_names[iseq]!=NULL )
     {
      txt.printf( "%us\n", sql_version.DropSequence( seq_names[iseq] ).c_str() );
      iseq++;
     }


     txt.printf( "commit;\n\n" );


     txt.printf(
                "create table endings( id integer not null, ending varchar(%d) not null, id_language integer not null, nform integer not null, sumfreq integer not null );\n"
                , lexlen
               );

     txt.printf(
                "create table ending_stat( id_language integer not null, max_len integer not null );\n"
                "create table wordform_frequency( id integer not null, id_entry integer not null, iform integer not null, freq integer not null );\n"
                "create table misspelling( id integer not null, id_language integer not null, original_word varchar(%d) not null, substitution varchar(%d) not null );\n"
                , lexlen
                , lexlen
               );
                

     txt.printf(
                "create table coord_pairs( id integer not null, pairs varchar(1000) not null, str_pairs varchar(1000) not null );\n"
                "create table tag_set( id integer not null, tags varchar(1000) not null );\n"
                "CREATE TABLE SG_LANGUAGE( ID integer not null, NAME varchar(%d) NOT NULL );\n"
                , lexlen
               );

     txt.printf(
                "create table lang_alphabet( id integer not null, id_language integer not null, id_alphabet integer not null, ordering int not null );\n"
                "create table lang_link( id integer not null, id_language integer not null, id_state integer not null, id_language2 integer not null );\n"
                "create table lang_param( id integer not null, id_language integer not null, param_name varchar(%d) not null, param_value varchar(200) not null, ordering integer not null );\n"
                , lexlen
               );

     txt.printf(
                "CREATE TABLE SG_LEXEM( ID bigint not null, NAME varchar(%d) );\n"
                "CREATE TABLE SG_COORD( ID integer not null, NAME varchar(%d) NOT NULL, BISTABLE integer );\n"
                "CREATE TABLE SG_STATE( ID integer not null, ID_COORD integer not null, NAME varchar(%d) NOT NULL, id_parent integer, weight integer );\n"
                "CREATE TABLE SG_CLASS( ID integer not null, NAME varchar(%d) not null, NAME_ALIASE varchar(%d), ID_LANG integer, weight integer not null, closed_class integer not null );\n"
                "create table unknown_entries( id bigint not null );\n"
                "create table predef_entries( id integer not null, id_entry bigint not null );\n"
                "CREATE TABLE SG_ENTRY( ID bigint not null, NAME varchar(%d), UNAME varchar(%d), ID_CLASS integer, FREQ integer, exportable integer, flags integer default 0 not null, dic_div char(4) DEFAULT '' NOT NULL );\n"
                , lexlen
                , lexlen
                , lexlen
                , lexlen
                , lexlen
                , lexlen
                , lexlen
               );
    
     txt.printf(
                "CREATE TABLE SG_FORM( ID_ENTRY bigint not null, IFORM int not null, NAME varchar(%d), ID_LEXEM bigint, ID_DIMS int );\n"
                "CREATE TABLE SG_LINK( ID integer not null, ID_ENTRY1 bigint, ID_ENTRY2 bigint, ICOORD int, ISTATE int, tags int );\n"
                "CREATE TABLE SG_ENTRY_COORD( ID_ENTRY bigint, ICOORD int, ISTATE int );\n"
                "CREATE TABLE SG_FORM_COORD( ID_ENTRY bigint, IFORM int, ICOORD int, ISTATE int );\n"
                "CREATE TABLE SG_CLASS_COORD( ID_CLASS integer NOT NULL, ID_COORD integer NOT NULL, COORD_TYPE integer NOT NULL );\n"
                "create table class_attr_def( id integer not null, id_class integer not null, id_coord integer not null, default_state integer not null );\n"
                "CREATE TABLE SG_TAG( ID integer not null, NAME varchar(%d) );\n"
                "CREATE TABLE SG_TAG_VALUE( ID_TAG integer not null, IVALUE integer not null, NAME varchar(%d) );\n"
                "CREATE TABLE SG_LINK_TAG( ID integer not null, ID_LINK integer, ID_TAG integer, IVALUE int );\n"
                "CREATE TABLE SG_TENTRY( TE_ID integer not null, TE_TEXT varchar(2000), TE_UTXT varchar(2000), TE_TEXT32 char(32), TE_ID_LANGUAGE integer, TE_ID_CLASS integer, te_syntax_flags integer, dic_div char(4) DEFAULT '' NOT NULL );\n"
                "CREATE TABLE SG_TLINK( TL_ID integer not null, TL_TE_ID1 integer, TL_TE_ID2 integer, TL_ICOORD integer, TL_ISTATE integer, tl_tags integer );\n"
                "CREATE TABLE SG_TLINK_TAG( TLT_ID integer not null, TLT_TL_ID integer, TLT_ID_TAG integer, TLT_IVALUE integer );\n"
                "CREATE TABLE SG_TLINK_FLAG( TLF_ID integer not null, TLF_TL_ID integer, TLF_FLAG char(32), TLF_VALUE char(32) );\n"
                "create table cplx_left( cl_id integer not null, cl_headword varchar(%d), cl_minlen integer, cl_maxlen integer );\n"
                "create table tnotes( tn_id integer not null, tn_te_id integer, tn_type integer, tn_format integer, tn_data varchar(1000) );\n"
                , lexlen
                , lexlen
                , lexlen
                , lexlen
               );

     txt.printf(
                "create table aux_form_types( id integer NOT NULL, name varchar(%d) NOT NULL );\n"
                "create table aux_form( id integer NOT NULL, id_entry bigint NOT NULL, iform int NOT NULL, data_type int NOT NULL, data_text varchar(200) NOT NULL );\n"
                "create table aux_entry_data( id integer NOT NULL, id_entry bigint NOT NULL, data_type int NOT NULL, data_text varchar(200) NOT NULL );\n"
                , lexlen
               );


     txt.printf(
                "CREATE TABLE aux_word(\n"
                "id integer PRIMARY KEY,\n"
                "aux_type INTEGER NOT NULL,\n"
                "src varchar(30),\n"
                "res varchar(200)\n"
                ");\n\n"
               );

     txt.printf(
                "create table multilexem( id integer not null, txt varchar(%d) not null, headword varchar(%d) not null, n_lexem integer not null );\n"
                "create table sg_criterion( id integer not null, name varchar(%d) not null, strval varchar(100) not null );\n"
                "COMMIT;\n"
                "\n",
                lexlen, lexlen, lexlen
               );

     txt.printf(
                "CREATE TABLE paradigma( "
                " id integer NOT NULL,"
                " front_name varchar(32),"
                " r_condition varchar(256),"
                " id_class integer,"
                " attrs VARCHAR(100)"
                ");\n\n"
  
                "CREATE TABLE paradigma_name( "
                " id integer NOT NULL,"
                " id_paradigma integer not null,"
                " name varchar(32),"
                " uname varchar(32)"
                ");\n\n"
  
                "CREATE TABLE paradigma_form( "
                " id integer NOT NULL,"
                " id_paradigma integer NOT NULL,"
                " rx_condition VARCHAR(100),"
                " flexer_flags VARCHAR(100),"
                " lexem_generator varchar(100) NOT NULL,"
                " dims varchar(256)"
                ");\n\n"

                "COMMIT;\n\n"
               );


     if( !sql_version.norules )
      {
       txt.printf(
                  "CREATE TABLE word_entry_set( "
                  " id integer NOT NULL,"
                  " name varchar(32) NOT NULL,"
                  " ies blob sub_type 1 NOT NULL"
                  ");\n\n"
    
                  "CREATE TABLE word_set( "
                  " id integer NOT NULL,"
                  " name varchar(32) NOT NULL,"
                  " case_sensitive integer NOT NULL,"
                  " words blob sub_type 1 NOT NULL"
                  ");\n\n"
    
                  "CREATE TABLE collocation_set( "
                  " id integer NOT NULL,"
                  " name varchar(32) NOT NULL,"
                  " case_sensitive integer NOT NULL"
                  ");\n\n"
    
                  "CREATE TABLE collocation_set_item( "
                  " id integer NOT NULL,"
                  " id_set integer NOT NULL,"
                  " words varchar(250) NOT NULL,"
                  " n_word integer NOT NULL,"
                  " headword varchar(30) NOT NULL"
                  ");\n\n"
    
                  "CREATE TABLE collocation_headword( "
                  " id integer NOT NULL,"
                  " headword varchar(32) NOT NULL,"
                  " min_len integer NOT NULL,"
                  " max_len integer NOT NULL"
                  ");\n\n"
    
                  "CREATE TABLE wordform_set( "
                  " id integer PRIMARY KEY NOT NULL,"
                  " name varchar(32) NOT NULL"
                  ");\n"
    
                  "CREATE TABLE wordform_set_item( "
                  " id integer PRIMARY KEY NOT NULL,"
                  " id_set integer NOT NULL,"
                  " word varchar(32) NOT NULL,"
                  " id_entry integer NOT NULL,"
                  " id_coords integer NOT NULL"
                  ");\n"
    
                  "CREATE TABLE wordform_set_coords( "
                  " id integer PRIMARY KEY NOT NULL,"
                  " coords varchar(200) NOT NULL"
                  ");\n\n"
    
                  "COMMIT;\n\n"
                 );
      }

     txt.printf(
                "create table abc_alphabet( id integer not null, name varchar(100) not null unique );\n"
                "create table abc_coord( id integer not null, name varchar(100) not null unique, bistable int );\n"
                "create table abc_state( id int not null, id_coord int not null, name varchar(100) not null );\n"
                "create table abc_class( id integer not null, name varchar(100) not null unique );\n"
                "create table abc_class_coord( id_class int not null, id_coord int not null, coord_type int not null );\n"
                "create table abc_entry( id integer not null, name varchar(10) not null, id_class integer not null, id_alphabet integer not null, id_pairs integer not null, code integer not null );\n"
                "create table abc_form( id integer not null, ordnum integer not null, id_entry int not null, id_pairs int not null, name varchar(10) not null, code integer not null );\n"
                "create table abc_pairs( id integer not null, str_pairs varchar(60) not null unique );\n"
                "create table abc_pair( id integer not null, id_pairs integer not null, id_coord integer not null, id_state integer not null );\n"
                "create table abc_criterion( id integer not null, name varchar(64) not null, strval varchar(100) not null );\n"
                "COMMIT;\n"
                "\n"
               );


     txt.printf(
                "CREATE TABLE abc_operation( "
                " id integer NOT NULL,"
                " name varchar(32) NOT NULL"
                ");\n\n"
  
                "CREATE TABLE abc_operation_item( "
                " id integer NOT NULL,"
                " id_operation integer NOT NULL,"
                " src_char_ucs4 integer NOT NULL,"
                " res_char_ucs4 integer NOT NULL,"
                " src_char varchar(2) NOT NULL,"
                " res_char varchar(2) NOT NULL"
                ");\n"
                "COMMIT;\n\n"
               );

     if( !sql_version.norules )
      {
       txt.printf(
                  "CREATE TABLE tr_functions( "
                  " marker varchar(3) NOT NULL,"
                  " bin blob sub_type 1"
                  ");\n\n"
    
    
                  "CREATE TABLE unbreakable( "
                  " id integer NOT NULL,"
                  " name varchar(32) NOT NULL,"
                  " id_language integer NOT NULL,"
                  " id_src integer,"
                  " pattern varchar(100) NOT NULL,"
                  " is_regex integer NOT NULL"
                  ");\n\n"
    
                  "CREATE TABLE recog_rule( "
                  " id integer NOT NULL,"
                  " name varchar(32) NOT NULL,"
                  " id_language integer NOT NULL,"
                  " id_src integer,"
                  " is_regex integer not null,"
                  " is_syllab integer not null,"
                  " is_prefix integer not null,"
                  " is_affix integer not null,"
                  " r_condition varchar(100) not null,"
                  " case_sensitive integer not null,"
                  " word varchar(100),"
                  " id_entry integer not null,"
                  " rel integer not null,"
                  " coords varchar(300) not null"
                  ");\n\n"
    
                  "CREATE TABLE ph_rule( "
                  " id integer NOT NULL,"
                  " name varchar(32) NOT NULL,"
                  " id_language integer NOT NULL,"
                  " id_src integer,"
                  " r_condition varchar(30) not null,"
                  " r_result varchar(30) not null,"
                  " is_prefix integer not null,"
                  " is_affix integer not null,"
                  " rel integer not null"
                  ");\n\n"
    
   
                  "CREATE TABLE SynPatternTree( "
                  " id integer NOT NULL,"
                  " id_tree integer NOT NULL,"
                  " id_language integer NOT NULL,"
                  " name varchar(32) NOT NULL,"
                  " uname varchar(32) NOT NULL,"
                  " pattern_type integer NOT NULL,"
                  " bin blob sub_type 1"
                  ");\n\n"
    
                  "CREATE TABLE lang_usage( "
                  " id_language integer not null,"
                  " is_input integer not null,"
                  " is_output integer not null,"
                  " is_default integer not null"
                  ");\n\n"
    
    
                  "CREATE TABLE src_filename( "
                  " id integer not null,"
                  " filepath varchar(2000) NOT NULL,"
                  " filepath0 varchar(2000) NOT NULL"
                  ");\n\n"
    
                  "CREATE TABLE src_location( "
                  " id integer not null,"
                  " id_filename integer NOT NULL,"
                  " line_no integer NOT NULL,"
                  " column_no integer NOT NULL"
                  ");\n\n"
    
                  "COMMIT;\n"
                  "\n"
                 );
    
    
       txt.printf(
                  "CREATE TABLE crop_rule( "
                  " id integer NOT NULL PRIMARY KEY,"
                  " name varchar(32),"
                  " r_condition varchar(256) NOT NULL,"
                  " r_result varchar(256) NOT NULL,"
                  " id_language integer NOT NULL,"
                  " is_prefix integer NOT NULL,"
                  " is_affix integer NOT NULL,"
                  " is_regex integer NOT NULL,"
                  " id_src integer,"
                  " case_sensitive integer NOT NULL,"
                  " rel integer NOT NULL"
                  ");\n\n"
    
                  "COMMIT;\n"
                  "\n"
                 );
    
    
       txt.printf(
                  "CREATE TABLE kb_facts(\n"
                  " id integer PRIMARY KEY NOT NULL,\n"
                  " id_language integer NOT NULL,\n"
                  " name varchar(100) NOT NULL,\n"
                  " n_arg integer NOT NULL,\n"
                  " n_ret integer NOT NULL,\n"
                  " ret_type integer NOT NULL,\n"
                  " query_mode integer NOT NULL,\n"
                  " violation_score integer NOT NULL,\n"
                  " violation_handler integer NOT NULL\n"
                  ");\n\n"
    
                  "CREATE TABLE kb_fact(\n"
                  " id integer PRIMARY KEY NOT NULL,\n"
                  " id_group integer NOT NULL,\n"
                  " boolean_return integer,\n"
                  " false_score integer,\n"
                  " integer_return integer\n"
                  ");\n\n"
    
                  "CREATE TABLE kb_argument_point( \n"
                  " id integer PRIMARY KEY NOT NULL,\n"
                  " id_fact integer,\n"
                  " argument_index integer NOT NULL,\n"
                  " word_text varchar(100),\n"
                  " id_entry integer,\n"
                  " id_class integer,\n"
                  " is_regex integer NOT NULL,\n"
                  " case_sensitive integer NOT NULL,\n"
                  " id_metaentry integer NOT NULL,\n"
                  " wordentryset_name varchar(100),\n"
                  " wordset_name varchar(100),\n"
                  " n_coords integer,\n"
                  " id_coord1 integer,\n"
                  " id_state1 integer,\n"
                  " affirm1 integer,\n"
                  " id_coord2 integer,\n"
                  " id_state2 integer,\n"
                  " affirm2 integer,\n"
                  " id_coord3 integer,\n"
                  " id_state3 integer,\n"
                  " affirm3 integer,\n"
                  " id_coord4 integer,\n"
                  " id_state4 integer,\n"
                  " affirm4 integer,\n"
                  " thesauruscheck_link integer,\n"
                  " thesauruscheck_entry integer,\n"
                  "  is_positive integer NOT NULL\n"
                  " );\n\n"
                );
    
    
    
       txt.printf(
                  "CREATE TABLE kb_fact_index1(\n"
                  " id integer PRIMARY KEY NOT NULL,\n"
                  " id_group integer NOT NULL,\n"
                  " id_fact integer NOT NULL,\n"
                  " word1 varchar(32),\n"
                  " word2 varchar(32),\n"
                  " word3 varchar(32),\n"
                  " word4 varchar(32),\n"
                  " word5 varchar(32)\n"
                  ");\n\n"
    
    
                  "CREATE TABLE kb_fact_index2(\n"
                  " id integer PRIMARY KEY NOT NULL,\n"
                  " id_group integer NOT NULL,\n"
                  " id_fact integer NOT NULL,\n"
                  " id_entry1 integer,\n"
                  " id_entry2 integer,\n"
                  " id_entry3 integer,\n"
                  " id_entry4 integer,\n"
                  " id_entry5 integer\n"
                  ");\n\n"
    
                  "CREATE TABLE generic_tree_scorer(\n"
                  " id integer PRIMARY KEY NOT NULL,\n"
                  " id_head_point integer NOT NULL,\n"
                  " id_group integer NOT NULL,\n"
                  " score_expr varchar(100),\n"
                  " score_type integer NOT NULL\n"
                  ");\n\n"
    
                  "CREATE TABLE ts_predicate(\n"
                  " id integer PRIMARY KEY NOT NULL,\n"
                  " id_point integer NOT NULL,\n"
                  " func_name varchar(20) NOT NULL,\n"
                  " narg integer NOT NULL,\n"
                  " id_class1 integer NOT NULL\n"
                  ");\n\n"
                 );
      }

     txt.printf(
                "CREATE TABLE slb_rule(\n"
                "id integer PRIMARY KEY NOT NULL,\n"
                "name varchar(32) NOT NULL UNIQUE,\n"
                "id_src integer NOT NULL,\n"
                "id_language integer NOT NULL,\n"
                "cursor_shift integer NOT NULL\n"
                ");\n\n"

                "CREATE TABLE slb_condition_point(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_rule integer NOT NULL,\n"
                " point_index integer NOT NULL,\n"
                " n_char integer NOT NULL,\n"
                " char_text varchar(30) NOT NULL,\n"
                " char_ucs4 varchar(30) NOT NULL,\n"
                " id_class integer NOT NULL,\n"
                " id_entry integer NOT NULL,\n"
                " n_coord integer NOT NULL,\n"
                " id_coord0 integer NOT NULL,\n"
                " id_state0 integer NOT NULL,\n"
                " is_left_boundary integer NOT NULL,\n"
                " is_right_boundary integer NOT NULL,\n"
                " is_positive integer NOT NULL\n"
                ");\n\n"

                "CREATE TABLE slb_result_point(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_rule integer NOT NULL,\n"
                " point_index integer NOT NULL,\n"
                " copy_index integer NOT NULL,\n"
                " merge_index0 integer NOT NULL,\n"
                " merge_count integer NOT NULL\n"
                ");\n\n"
               );



     if( !sql_version.norules )
      {
       txt.printf(
                  "CREATE TABLE ts_head_word(\n"
                  " id integer NOT NULL PRIMARY KEY,\n"
                  " word varchar(100) NOT NULL,\n"
                  " id_head_point integer NOT NULL,\n"
                  " score_type integer NOT NULL,\n"
                  " score_expr varchar(100),"
                  " root_node integer NOT NULL,\n"
                  " id_group integer NOT NULL\n"
                  " );\n\n"
    
                  "CREATE TABLE ts_head_lemma(\n"
                  " id integer NOT NULL PRIMARY KEY,\n"
                  " id_entry integer NOT NULL,\n"
                  " id_head_point integer NOT NULL,\n"
                  " score_type integer NOT NULL,\n"
                  " score_expr varchar(100),"
                  " root_node integer NOT NULL,\n"
                  " id_group integer NOT NULL\n"
                  ");\n\n"
    
                  "CREATE TABLE ts_point(\n"
                  " id integer NOT NULL PRIMARY KEY,\n"
                  " id_parent integer,\n"
                  " id_group integer,\n"
                  " word_text varchar(100),\n"
                  " id_entry integer NOT NULL,\n"
                  " id_metaentry integer NOT NULL,\n"
                  " id_class integer NOT NULL,\n"
                  " wordentryset_name varchar(100),\n"
                  " wordset_name varchar(100),\n"
                  " wordformset_name varchar(100),\n"
                  " n_coords integer NOT NULL,\n"
                  " id_coord1 integer,\n"
                  " id_state1 integer,\n"
                  " affirm1 integer,\n"
                  " id_coord2 integer,\n"
                  " id_state2 integer,\n"
                  " affirm2 integer,\n"
                  " id_coord3 integer,\n"
                  " id_state3 integer,\n"
                  " affirm3 integer,\n"
                  " id_coord4 integer,\n"
                  " id_state4 integer,\n"
                  " affirm4 integer,\n"
                  " thesauruscheck_link integer NOT NULL,\n"
                  " thesauruscheck_entry integer NOT NULL,\n"
                  " is_positive integer NOT NULL,\n"
                  " children_quantification_min_count integer NOT NULL,\n"
                  " children_quantification_max_count integer NOT NULL,\n"
                  " n_setcheckers integer NOT NULL,\n"
                  " set_name1 varchar(50),\n"
                  " set_type1 integer NOT NULL,\n"
                  " set_affirm1 integer NOT NULL,\n"
                  " set_name2 varchar(50),\n"
                  " set_type2 integer NOT NULL,\n"
                  " set_affirm2 integer NOT NULL,\n"
                  " set_name3 varchar(50),\n"
                  " set_type3 integer NOT NULL,\n"
                  " set_affirm3 integer NOT NULL,\n"
                  " link_type integer NOT NULL,"
                  " relative_position integer NOT NULL,\n"
                  " quantification_min_count integer NOT NULL,\n"
                  " quantification_max_count integer NOT NULL,\n"
                  " marker varchar(30),"
                  " n_backref integer NOT NULL,"

                  " br_affirm_0 integer,\n"
                  " br_coord0_0 integer,\n"
                  " br_marker_0 varchar(30),\n"
                  " br_coord1_0 integer,\n"
                  " br_for_group_0 integer,\n"

                  " br_affirm_1 integer,\n"
                  " br_coord0_1 integer,\n"
                  " br_marker_1 varchar(30),\n"
                  " br_coord1_1 integer,\n"
                  " br_for_group_1 integer,\n"

                  " br_affirm_2 integer,\n"
                  " br_coord0_2 integer,\n"
                  " br_marker_2 varchar(30),\n"
                  " br_coord1_2 integer,\n"
                  " br_for_group_2 integer,\n"

                  " id_src integer\n"
                  ");\n\n"
                 );
    
       txt.printf(
                  "CREATE TABLE ts_group(\n"
                  " id integer PRIMARY KEY NOT NULL,\n"
                  " name varchar(30) NOT NULL,\n"
                  " allow_unmatched_children integer NOT NULL\n"
                  ");\n\n"
    
                  "CREATE TABLE ts_group2root(\n"
                  " id integer PRIMARY KEY NOT NULL,\n"
                  " id_group integer NOT NULL,\n"
                  " id_root integer NOT NULL\n"
                  ");\n\n"
                 );
      }


     txt.printf(
                " CREATE TABLE metaentry( \n"
                " id integer NOT NULL PRIMARY KEY,\n"
                " id_class integer not null,\n"
                " name varchar(100) NOT NULL\n"
                " );\n" );

     txt.printf(
                " CREATE TABLE metaentry_item( \n"
                " id integer NOT NULL PRIMARY KEY,\n"
                " id_metaentry integer not null,\n"
                " id_entry integer not null\n"
                " );\n\n" );

     txt.printf(
                "CREATE TABLE omonym(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " entry_name varchar(100) NOT NULL,\n"
                " id_class integer NOT NULL\n"
                ");\n"
                "COMMIT;\n\n"
               );

     if( !sql_version.norules )
      {
       txt.printf(
                  "CREATE TABLE word_assoc(\n"
                  " id integer PRIMARY KEY NOT NULL,\n"
                  " id_src integer,\n"
                  " id_entry integer NOT NULL,\n"
                  " id_entry1 integer,\n"
                  " word1 varchar(40),\n"
                  " id_metaentry1 integer,\n"
                  " id_entry2 integer,\n"
                  " word2 varchar(40),\n"
                  " id_metaentry2 integer,\n"
                  " link_type integer,\n"
                  " link_entry integer,\n"
                  " set_name varchar(40),\n"
                  " set_type integer,\n"
                  " score integer NOT NULL\n"
                  ");\n\n"
                 );
    
       txt.printf(
                  "CREATE TABLE predicate_template(\n"
                  " id integer PRIMARY KEY NOT NULL,\n"
                  " id_src integer,\n"
                  " src varchar(250) NOT NULL,\n"
                  " params varchar(100)\n"
                  ");\n"
                 );
      }
    }
   else if( sql_version.type==SQL_Production::MsSql )
    {
     txt.printf(
                "BEGIN TRANSACTION\n"
               );

     int itable=0;
     while( table_names[itable]!=NULL )
     {
      txt.printf( "%us\n", sql_version.DropTable( table_names[itable] ).c_str() );
      itable++;
     }


     txt.printf(
                "CREATE TABLE abc_operation( "
                " id int NOT NULL primary key,"
                " name varchar(32) NOT NULL UNIQUE"
                ");\n\n"
  
                "CREATE TABLE abc_operation_item( "
                " id int NOT NULL primary key,"
                " id_operation int NOT NULL,"
                " src_char_ucs4 int NOT NULL,"
                " res_char_ucs4 int NOT NULL,"
                " src_char varchar(2) NOT NULL,"
                " res_char varchar(2) NOT NULL"
                ");\n\n"

                "CREATE TABLE tr_functions( "
                " marker varchar(3) NOT NULL,"
                " bin varchar(max)"
                ");\n\n"


 
                "CREATE TABLE word_entry_set( "
                " id integer NOT NULL primary key,"
                " name varchar(32) NOT NULL,"
                " ies varchar(max) NOT NULL"
                ");\n\n"

                "CREATE TABLE wordform_set( "
                " id integer NOT NULL PRIMARY KEY ,"
                " name varchar(32) NOT NULL"
                ");\n"
 
                "CREATE TABLE wordform_set_item( "
                " id integer NOT NULL PRIMARY KEY ,"
                " id_set integer NOT NULL,"
                " word varchar(32) NOT NULL,"
                " id_entry integer NOT NULL,"
                " id_coords integer NOT NULL"
                ");\n"
 
                "CREATE TABLE wordform_set_coords( "
                " id integer NOT NULL PRIMARY KEY,"
                " coords varchar(200) NOT NULL"
                ");\n"


                "CREATE TABLE unbreakable( "
                " id integer NOT NULL primary key,"
                " name varchar(32) NOT NULL,"
                " id_language integer NOT NULL,"
                " id_src integer,"
                " pattern varchar(100) NOT NULL,"
                " is_regex integer NOT NULL"
                ");\n\n"

                "CREATE TABLE recog_rule( "
                " id integer NOT NULL PRIMARY KEY,"
                " name varchar(32) NOT NULL,"
                " id_language integer NOT NULL,"
                " id_src integer,"
                " is_regex integer not null,"
                " is_syllab integer not null,"
                " is_prefix integer not null,"
                " is_affix integer not null,"
                " r_condition varchar(100) not null,"
                " case_sensitive integer not null,"
                " word varchar(100),"
                " id_entry integer not null,"
                " rel integer not null,"
                " coords varchar(300) not null"
                ");\n\n"

                "CREATE TABLE ph_rule( "
                " id integer NOT NULL PRIMARY KEY,"
                " name varchar(32) NOT NULL,"
                " id_language integer NOT NULL,"
                " id_src integer,"
                " r_condition varchar(30) not null,"
                " r_result varchar(30) not null,"
                " is_prefix integer not null,"
                " is_affix integer not null,"
                " rel integer not null"
                ");\n\n"

                "CREATE TABLE SynPatternTree( "
                " id integer NOT NULL PRIMARY KEY,"
                " id_tree integer NOT NULL,"
                " id_language integer NOT NULL,"
                " name varchar(32) NOT NULL,"
                " uname varchar(32) NOT NULL,"
                " pattern_type integer NOT NULL,"
                " bin varchar(max)"
                ");\n\n"

                "CREATE TABLE lang_usage( "
                " id_language integer not null,"
                " is_input integer not null,"
                " is_output integer not null,"
                " is_default integer not null"
                ");\n\n"

                "CREATE TABLE src_filename( "
                " id integer not null PRIMARY KEY,"
                " filepath varchar(2000) NOT NULL,"
                " filepath0 varchar(2000) NOT NULL"
                ");\n\n"
  
                "CREATE TABLE src_location( "
                " id integer not null PRIMARY KEY,"
                " id_filename integer NOT NULL,"
                " line_no integer NOT NULL,"
                " column_no integer NOT NULL"
                ");\n\n"

                "COMMIT\n"
                "GO\n"
                "\n"
               );


     txt.printf(
                "BEGIN TRANSACTION\n"

                "create table endings( id int not null identity(1,1) primary key, ending nvarchar(40) not null, id_language int not null, nform int not null, sumfreq int not null );\n"
                "create table ending_stat( id_language int not null primary key, max_len int not null );\n"

                "create table wordform_frequency( id int not null identity(1,1) primary key, id_entry int not null, iform int not null, freq int not null );\n"
                "create table misspelling( id int not null identity(1,1) primary key, id_language int not null, original_word nvarchar(64) not null, substitution nvarchar(64) not null );\n"

                "create table coord_pairs( id int not null identity(1,1) primary key, pairs nvarchar(1000) not null, str_pairs nvarchar(1000) not null );\n"
                "create table tag_set( id int not null identity(1,1) primary key, tags nvarchar(400) not null unique );\n"
                "create table sg_language( id int not null primary key, name nvarchar(32) not null unique );\n"
                "create table lang_alphabet( id int not null primary key, id_language int not null, id_alphabet int not null, ordering int not null );\n"
                "create table lang_link( id int not null primary key, id_language int not null, id_state int not null, id_language2 int not null );\n"
                "create table lang_param( id int not null primary key, id_language int not null, param_name varchar(32) not null, param_value varchar(200) not null, ordering int not null );\n"
                "create table sg_lexem( id bigint identity(1,1) primary key, name nvarchar(32) not null );\n"
                "create table sg_coord( id int not null primary key, name nvarchar(32) not null, bistable int not null );\n"
                "create table sg_state( id int not null, id_coord int not null, name nvarchar(32) not null, id_parent int not null, weight int not null );\n"
                "create table sg_class( id int primary key, name nvarchar(32) not null, name_aliase nvarchar(32), id_lang int, weight int not null, closed_class int not null );\n"
                "create table sg_entry( id int not null identity(1,1) primary key, name nvarchar(32) not null, uname nvarchar(32) not null, id_class int not null, freq int, exportable int, flags int not null default 0, dic_div char(4) DEFAULT '' NOT NULL );\n"
                "create table unknown_entries( id int not null primary key );\n"
                "create table predef_entries( id int not null primary key, id_entry int not null );\n"
                "create table sg_form( id_entry int not null, iform int not null, name nvarchar(32) not null, id_lexem bigint not null, id_dims int );\n"
                "create table sg_link( id int not null identity(1,1) primary key, id_entry1 int not null, id_entry2 int not null, icoord int not null, istate int not null, tags int );\n"
                "create table sg_entry_coord( id_entry int not null, icoord int not null, istate int not null );\n"
                "create table sg_form_coord( id_entry int not null, iform int not null, icoord int not null, istate int not null );\n"
                "create table sg_class_coord( id_class int not null, id_coord int not null, coord_type int not null );\n"
                "create table class_attr_def( id int not null, id_class int not null, id_coord int not null, default_state int not null );\n"
                "create table sg_tag( id int not null primary key, name nvarchar(32) not null unique );\n"
                "create table sg_tag_value( id_tag int not null, ivalue int not null, name nvarchar(32) not null );\n"
                "create table sg_link_tag( id int not null identity(1,1) primary key, id_link int not null, id_tag int not null, ivalue int not null );\n"
                "create table sg_tentry( te_id int not null identity(1,1) primary key, te_text nvarchar(2000) not null, te_utxt nvarchar(2000) not null, te_text32 nvarchar(32) not null, te_id_language int, te_id_class int, te_syntax_flags int, dic_div char(4) DEFAULT '' NOT NULL );\n"
                "create table sg_tlink( tl_id int not null identity(1,1) primary key, tl_te_id1 int not null, tl_te_id2 int not null, tl_icoord int not null, tl_istate int not null, tl_tags int );\n"
                "create table sg_tlink_tag( tlt_id int not null identity(1,1) primary key, tlt_tl_id int not null, tlt_id_tag int not null, tlt_ivalue int not null );\n"
                "create table sg_tlink_flag( tlf_id int not null identity(1,1) primary key, tlf_tl_id int not null, tlf_flag nvarchar(32) not null, tlf_value nvarchar(32) not null );\n"
                "create table cplx_left( cl_id int not null identity(1,1) primary key, cl_headword nvarchar(32) unique, cl_minlen int not null, cl_maxlen int not null );\n"
                "create table tnotes( tn_id int not null identity(1,1) primary key, tn_te_id int not null, tn_type int, tn_format int not null, tn_data varchar(max) );\n"

                "create table aux_form_types( id int not null identity(1,1) primary key, name nvarchar(32) NOT NULL unique );\n"
                "create table aux_form( id int not null identity(1,1) primary key, id_entry int NOT NULL, iform int NOT NULL, data_type int NOT NULL, data_text nvarchar(200) NOT NULL );\n"
                "create table aux_entry_data( id int not null identity(1,1) primary key, id_entry int NOT NULL, data_type int NOT NULL, data_text nvarchar(200) NOT NULL );\n"
               );

     txt.printf(
                "CREATE TABLE aux_word(\n"
                "id integer not null identity(1,1) primary key,\n"
                "aux_type INTEGER NOT NULL,\n"
                "src varchar(30),\n"
                "res varchar(200)\n"
                ");\n\n"
               );

     txt.printf(
                "create table multilexem( id int not null identity(1,1) primary key, txt nvarchar(32) not null, headword nvarchar(32) not null, n_lexem integer not null );\n"
                "create table sg_criterion( id integer not null primary key, name varchar(64) not null unique, strval varchar(100) not null );\n"
               );

     txt.printf(
                "CREATE TABLE paradigma( "
                " id integer PRIMARY KEY NOT NULL,"
                " front_name nvarchar(32),"
                " r_condition nvarchar(256),"
                " id_class integer,"
                " attrs nvarchar(100)"
                ");\n\n"
  
                "CREATE TABLE paradigma_name( "
                " id integer PRIMARY KEY NOT NULL,"
                " id_paradigma integer not null,"
                " name nvarchar(32),"
                " uname nvarchar(32)"
                ");\n\n"
  
                "CREATE TABLE paradigma_form( "
                " id integer PRIMARY KEY NOT NULL,"
                " id_paradigma integer NOT NULL,"
                " rx_condition nvarchar(100),"
                " flexer_flags nvarchar(100),"
                " lexem_generator nvarchar(100) NOT NULL,"
                " dims nvarchar(256)"
                ");\n\n"
               );


     txt.printf(
                "CREATE TABLE word_set( "
                " id integer PRIMARY KEY NOT NULL,"
                " name nvarchar(32) NOT NULL,"
                " case_sensitive integer NOT NULL,"
                " words nvarchar(max) NOT NULL"
                ");\n\n"

                "CREATE TABLE collocation_set( "
                " id integer PRIMARY KEY NOT NULL,"
                " name nvarchar(32) NOT NULL,"
                " case_sensitive integer NOT NULL"
                ");\n\n"

                "CREATE TABLE collocation_set_item( "
                " id integer PRIMARY KEY NOT NULL,"
                " id_set integer NOT NULL,"
                " words nvarchar(250) NOT NULL,"
                " n_word integer NOT NULL,"
                " headword nvarchar(30) NOT NULL"
                ");\n\n"

                "CREATE TABLE collocation_headword( "
                " id integer PRIMARY KEY NOT NULL,"
                " headword nvarchar(32) NOT NULL,"
                " min_len integer NOT NULL,"
                " max_len integer NOT NULL"
                ");\n\n"
               );


     txt.printf(
                "create table abc_alphabet( id integer not null primary key, name nvarchar(32) not null unique );\n"
                "create table abc_coord( id integer not null primary key, name nvarchar(32) not null unique, bistable int not null );\n"
                "create table abc_state( id int not null, id_coord int not null, name nvarchar(32) not null );\n"
                "create table abc_class( id integer not null primary key, name nvarchar(32) not null unique );\n"
                "create table abc_class_coord( id_class int not null, id_coord int not null, coord_type int not null );\n"
                "create table abc_entry( id integer not null primary key, name nvarchar(4) not null, id_class integer not null, id_alphabet integer not null, id_pairs integer not null, code integer not null );\n"
                "create table abc_form( id integer not null primary key, ordnum integer not null, id_entry int not null, id_pairs int not null, name nvarchar(2) not null, code integer not null );\n"
                "create table abc_pairs( id integer not null primary key, str_pairs nvarchar(60) not null unique );\n"
                "create table abc_pair( id integer not null primary key, id_pairs integer not null, id_coord integer not null, id_state integer not null );\n"
                "create table abc_criterion( id integer not null primary key, name nvarchar(64) not null unique, strval nvarchar(100) not null );\n"
                "\n"
               );

     txt.printf(
                "COMMIT\n"
                "GO\n"
                "\n"
                "BEGIN TRANSACTION\n\n"
               );

     txt.printf(
                "CREATE TABLE kb_facts(\n"
                " id integer not null primary key,\n"
                " id_language integer NOT NULL,\n"
                " name nvarchar(100) NOT NULL,\n"
                " n_arg integer NOT NULL,\n"
                " n_ret integer NOT NULL,\n"
                " ret_type integer NOT NULL,\n"
                " query_mode integer NOT NULL,\n"
                " violation_score integer NOT NULL,\n"
                " violation_handler integer NOT NULL\n"
                ");\n\n"

                "CREATE TABLE kb_fact(\n"
                " id integer not null primary key,\n"
                " id_group integer NOT NULL,\n"
                " boolean_return integer,\n"
                " false_score integer,\n"
                " integer_return integer\n"
                ");\n\n"

                "CREATE TABLE kb_argument_point( \n"
                " id integer not null primary key,\n"
                " id_fact integer,\n"
                " argument_index integer NOT NULL,\n"
                " word_text nvarchar(100),\n"
                " id_entry integer,\n"
                " id_class integer,\n"
                " is_regex integer NOT NULL,\n"
                " case_sensitive integer NOT NULL,\n"
                " id_metaentry integer NOT NULL,\n"
                " wordentryset_name nvarchar(100),\n"
                " wordset_name nvarchar(100),\n"
                " n_coords integer,\n"
                " id_coord1 integer,\n"
                " id_state1 integer,\n"
                " affirm1 integer,\n"
                " id_coord2 integer,\n"
                " id_state2 integer,\n"
                " affirm2 integer,\n"
                " id_coord3 integer,\n"
                " id_state3 integer,\n"
                " affirm3 integer,\n"
                " id_coord4 integer,\n"
                " id_state4 integer,\n"
                " affirm4 integer,\n"
                " thesauruscheck_link integer,\n"
                " thesauruscheck_entry integer,\n"
                "  is_positive integer NOT NULL\n"
                " );\n\n"
              );

     txt.printf(
                "CREATE TABLE kb_fact_index1(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_group integer NOT NULL,\n"
                " id_fact integer NOT NULL,\n"
                " word1 varchar(32),\n"
                " word2 varchar(32),\n"
                " word3 varchar(32),\n"
                " word4 varchar(32),\n"
                " word5 varchar(32)\n"
                ");\n\n"


                "CREATE TABLE kb_fact_index2(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_group integer NOT NULL,\n"
                " id_fact integer NOT NULL,\n"
                " id_entry1 integer,\n"
                " id_entry2 integer,\n"
                " id_entry3 integer,\n"
                " id_entry4 integer,\n"
                " id_entry5 integer\n"
                ");\n\n"

                "CREATE TABLE generic_tree_scorer(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_head_point integer NOT NULL,\n"
                " id_group integer NOT NULL,\n"
                " score_expr varchar(100),\n"
                " score_type integer NOT NULL\n"
                ");\n\n"

                "CREATE TABLE ts_predicate(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_point integer NOT NULL,\n"
                " func_name varchar(20) NOT NULL,\n"
                " narg integer NOT NULL,\n"
                " id_class1 integer NOT NULL\n"
                ");\n\n"
               );

     txt.printf(
                "CREATE TABLE slb_rule(\n"
                "id integer NOT NULL PRIMARY KEY,\n"
                "name nvarchar(32) NOT NULL UNIQUE,\n"
                "id_src integer NOT NULL,\n"
                "id_language integer NOT NULL,\n"
                "cursor_shift integer NOT NULL\n"
                ");\n\n"

                "CREATE TABLE slb_condition_point(\n"
                " id integer NOT NULL PRIMARY KEY,\n"
                " id_rule integer NOT NULL,\n"
                " point_index integer NOT NULL,\n"
                " n_char integer NOT NULL,\n"
                " char_text nvarchar(30) NOT NULL,\n"
                " char_ucs4 nvarchar(30) NOT NULL,\n"
                " id_class integer NOT NULL,\n"
                " id_entry integer NOT NULL,\n"
                " n_coord integer NOT NULL,\n"
                " id_coord0 integer NOT NULL,\n"
                " id_state0 integer NOT NULL,\n"
                " is_left_boundary integer NOT NULL,\n"
                " is_right_boundary integer NOT NULL,\n"
                " is_positive integer NOT NULL\n"
                ");\n\n"

                "CREATE TABLE slb_result_point(\n"
                " id integer NOT NULL PRIMARY KEY,\n"
                " id_rule integer NOT NULL,\n"
                " point_index integer NOT NULL,\n"
                " copy_index integer NOT NULL,\n"
                " merge_index0 integer NOT NULL,\n"
                " merge_count integer NOT NULL\n"
                ");\n\n"
               );

     txt.printf(
                " CREATE TABLE ts_head_word(\n"
                "  id integer NOT NULL PRIMARY KEY,\n"
                "  word nvarchar(100) NOT NULL,\n"
                "  id_head_point integer NOT NULL,\n"
                " score_type integer NOT NULL,\n"
                " score_expr varchar(100),"
                " root_node integer NOT NULL,\n"
                " id_group integer NOT NULL\n"
                " );\n\n"

                "CREATE TABLE ts_head_lemma(\n"
                " id integer NOT NULL PRIMARY KEY,\n"
                " id_entry integer NOT NULL,\n"
                " id_head_point integer NOT NULL,\n"
                " score_type integer NOT NULL,\n"
                " score_expr varchar(100),"
                " root_node integer NOT NULL,\n"
                " id_group integer NOT NULL\n"
                ");\n\n"

                "CREATE TABLE ts_point(\n"
                " id integer NOT NULL PRIMARY KEY,\n"
                " id_parent integer,\n"
                " id_group integer,\n"
                " word_text nvarchar(100),\n"
                " id_entry integer NOT NULL,\n"
                " id_metaentry integer NOT NULL,\n"
                " id_class integer NOT NULL,\n"
                " wordentryset_name nvarchar(100),\n"
                " wordset_name nvarchar(100),\n"
                " wordformset_name nvarchar(100),\n"
                " n_coords integer NOT NULL,\n"
                " id_coord1 integer,\n"
                " id_state1 integer,\n"
                " affirm1 integer,\n"
                " id_coord2 integer,\n"
                " id_state2 integer,\n"
                " affirm2 integer,\n"
                " id_coord3 integer,\n"
                " id_state3 integer,\n"
                " affirm3 integer,\n"
                " id_coord4 integer,\n"
                " id_state4 integer,\n"
                " affirm4 integer,\n"
                " thesauruscheck_link integer,\n"
                " thesauruscheck_entry integer,\n"
                " is_positive integer NOT NULL,\n"
                " children_quantification_min_count integer NOT NULL,\n"
                " children_quantification_max_count integer NOT NULL,\n"
                " n_setcheckers integer NOT NULL,\n"
                " set_name1 nvarchar(50),\n"
                " set_type1 integer NOT NULL,\n"
                " set_affirm1 integer NOT NULL,\n"
                " set_name2 nvarchar(50),\n"
                " set_type2 integer NOT NULL,\n"
                " set_affirm2 integer NOT NULL,\n"
                " set_name3 nvarchar(50),\n"
                " set_type3 integer NOT NULL,\n"
                " set_affirm3 integer NOT NULL,\n"
                " link_type integer NOT NULL,\n"
                " relative_position integer NOT NULL,\n"
                " quantification_min_count integer NOT NULL,\n"
                " quantification_max_count integer NOT NULL,\n"
                " marker varchar(30),"
                " n_backref integer NOT NULL,"

                " br_affirm_0 integer,\n"
                " br_coord0_0 integer,\n"
                " br_marker_0 varchar(30),\n"
                " br_coord1_0 integer,\n"
                " br_for_group_0 integer,\n"

                " br_affirm_1 integer,\n"
                " br_coord0_1 integer,\n"
                " br_marker_1 varchar(30),\n"
                " br_coord1_1 integer,\n"
                " br_for_group_1 integer,\n"

                " br_affirm_2 integer,\n"
                " br_coord0_2 integer,\n"
                " br_marker_2 varchar(30),\n"
                " br_coord1_2 integer,\n"
                " br_for_group_2 integer,\n"

                " id_src integer\n"
                ");\n\n"
               );

     txt.printf(
                "CREATE TABLE ts_group(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " name varchar(30) NOT NULL,\n"
                " allow_unmatched_children integer NOT NULL\n"
                ");\n\n"

                "CREATE TABLE ts_group2root(\n"
                " id integer NOT NULL identity(1,1) PRIMARY KEY,\n"
                " id_group integer NOT NULL,\n"
                " id_root integer NOT NULL\n"
                ");\n\n"
               );

     txt.printf(
                "CREATE TABLE metaentry( \n"
                " id integer NOT NULL PRIMARY KEY,\n"
                " id_class integer not null,\n"
                " name varchar(100) NOT NULL\n"
                " );\n" );

     txt.printf(
                "CREATE TABLE metaentry_item( \n"
                " id integer NOT NULL PRIMARY KEY,\n"
                " id_metaentry integer not null,\n"
                " id_entry integer not null\n"
                " );\n\n" );

     txt.printf(
                "CREATE TABLE omonym(\n"
                " id integer NOT NULL identity(1,1) PRIMARY KEY,\n"
                " entry_name varchar(100) NOT NULL,\n"
                " id_class integer NOT NULL\n"
                ");\n"
               );



     txt.printf(
                "CREATE TABLE word_assoc(\n"
                " id integer NOT NULL identity(1,1) PRIMARY KEY,\n"
                " id_src integer,\n"
                " id_entry integer NOT NULL,\n"
                " id_entry1 integer,\n"
                " word1 varchar(40),\n"
                " id_metaentry1 integer,\n"
                " id_entry2 integer,\n"
                " word2 varchar(40),\n"
                " id_metaentry2 integer,\n"
                " link_type integer,\n"
                " link_entry integer,\n"
                " set_name varchar(40),\n"
                " set_type integer,\n"
                " score integer NOT NULL\n"
                ");\n\n"
               );


     txt.printf(
                "CREATE TABLE predicate_template(\n"
                " id integer PRIMARY KEY NOT NULL,\n"
                " id_src integer,\n"
                " src varchar(250) NOT NULL,\n"
                " params varchar(100)\n"
                ");\n"
               );


     txt.printf(
                "COMMIT\n"
                "GO\n"
                "\n"
               );
    }
  }


 for( int i=0; i<SOL_N_AUTOMATA; i++ )
  if( auto_list[i] )
   auto_list[i]->Save_SQL(txt,txt2,sql_version);

 txt.printf( "\n%s\n", sql_version.BeginTx().c_str() );

 if( sql_version.type==SQL_Production::Oracle )
  {
   if( !sql_version.noschema )
    {
     txt2.printf(
                 "create unique index endings_idx1 on endings(ending,id_language);\n"
                 "create unique index wordform_frequency_idx1 on wordform_frequency(id_entry,iform);\n"
                 "CREATE UNIQUE INDEX word_entry_set_idx1 ON word_entry_set(name);\n"
                 "CREATE UNIQUE INDEX word_set_idx1 ON word_set(name);\n"
                 "CREATE UNIQUE INDEX collocation_set_idx1 ON collocation_set(name);\n"
                 "CREATE UNIQUE INDEX collocation_headword_idx1 ON collocation_headword(headword);\n"
                 "CREATE INDEX collocation_set_item_idx1 ON collocation_set_item(headword,id_set);\n"
                 "CREATE UNIQUE INDEX collocation_set_item_idx2 ON collocation_set_item(words,id_set);\n"
                 "CREATE UNIQUE INDEX omonym_idx1 ON omonym(entry_name,id_class);\n"

                 "create index sg_tentry_idx1 on sg_tentry(te_text32);\n"
                 "create index sg_form_idx1 on sg_form(id_entry);\n"
                 "create index sg_entry_coord_idx1 on sg_entry_coord(id_entry);\n"
                 "create index sg_entry_coord_idx2 on sg_entry_coord(id_entry,icoord);\n"
                 "create index aux_form_idx1 on aux_form(id_entry,iform);\n"
                 "create index aux_entry_data_idx1 on aux_entry_data(id_entry);\n"
                 "CREATE INDEX aux_word_idx1 ON aux_word(aux_type,src);\n\n"

                 "create unique index multilexem_idx1 on multilexem(txt);\n"
                 "create index multilexem_idx2 on multilexem(headword);\n"
               
                 "create index abc_entry_idx2 on abc_entry(code);\n"
                 "create index abc_form_idx2 on abc_form(code);\n"

                 "create unique index misspelling_idx1 on misspelling(original_word,id_language);\n"
                 "create unique index misspelling_idx2 on misspelling(original_word);\n"
               
                 "CREATE UNIQUE INDEX wordform_set_idx1 ON wordform_set(name);\n"
                 "CREATE INDEX wordform_set_item_idx1 ON wordform_set_item(id_set,word,id_entry);\n"
                 "CREATE UNIQUE INDEX wordform_set_coords_idx1 ON wordform_set_coords(coords);\n"

                 "\n"
                );

     txt2.printf(
                // ABC_STATE
                "ALTER TABLE ABC_STATE ADD PRIMARY KEY (ID_COORD, ID) ENABLE VALIDATE;\n"
                "ALTER TABLE ABC_STATE ADD UNIQUE (ID_COORD, NAME) ENABLE VALIDATE;\n"
                "ALTER TABLE ABC_STATE ADD FOREIGN KEY (ID_COORD) REFERENCES ABC_COORD (ID) ENABLE VALIDATE;\n"
               );

     txt2.printf(
                // ABC_PAIR
                "ALTER TABLE ABC_PAIR ADD FOREIGN KEY (ID_PAIRS) REFERENCES ABC_PAIRS (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE ABC_PAIR ADD FOREIGN KEY (ID_COORD) REFERENCES ABC_COORD (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE ABC_PAIR ADD FOREIGN KEY (ID_COORD, ID_STATE) REFERENCES ABC_STATE (ID_COORD, ID) ENABLE VALIDATE;\n"
               );

     txt2.printf(
                // ABC_CLASS_COORD
                "ALTER TABLE ABC_CLASS_COORD ADD FOREIGN KEY (ID_CLASS) REFERENCES ABC_CLASS (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE ABC_CLASS_COORD ADD FOREIGN KEY (ID_COORD) REFERENCES ABC_COORD (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE ABC_CLASS_COORD ADD ( CHECK (COORD_TYPE IN (0,1)));\n"
               );

     txt2.printf(
                // ABC_ENTRY
                "ALTER TABLE ABC_ENTRY ADD FOREIGN KEY (ID_CLASS) REFERENCES ABC_CLASS (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE ABC_ENTRY ADD FOREIGN KEY (ID_ALPHABET) REFERENCES ABC_ALPHABET (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE ABC_ENTRY ADD FOREIGN KEY (ID_PAIRS) REFERENCES ABC_PAIRS (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE ABC_ENTRY ADD UNIQUE (ID_ALPHABET, CODE) ENABLE VALIDATE;\n"
               );

     txt2.printf(
                // ABC_FORM
                "ALTER TABLE ABC_FORM ADD FOREIGN KEY (ID_ENTRY) REFERENCES ABC_ENTRY (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE ABC_FORM ADD FOREIGN KEY (ID_PAIRS) REFERENCES ABC_PAIRS (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE ABC_FORM ADD UNIQUE (ID_ENTRY, CODE) ENABLE VALIDATE;\n"
                "ALTER TABLE ABC_FORM ADD UNIQUE (ID_ENTRY, ORDNUM) ENABLE VALIDATE;\n"
               );


     txt2.printf(
                // AUX_ENTRY_DATA
                "ALTER TABLE AUX_ENTRY_DATA ADD FOREIGN KEY (DATA_TYPE) REFERENCES AUX_FORM_TYPES (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE AUX_ENTRY_DATA ADD FOREIGN KEY (ID_ENTRY) REFERENCES SG_ENTRY (ID) ENABLE VALIDATE;\n"
               );

     txt2.printf(
                // AUX_FORM
                "ALTER TABLE AUX_FORM ADD FOREIGN KEY (ID_ENTRY) REFERENCES SG_ENTRY (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE AUX_FORM ADD FOREIGN KEY (ID_ENTRY, IFORM) REFERENCES SG_FORM (ID_ENTRY, IFORM) ENABLE VALIDATE;\n"
               );

     txt2.printf(
                // CLASS_ATTR_DEF
                "ALTER TABLE CLASS_ATTR_DEF ADD PRIMARY KEY (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE CLASS_ATTR_DEF ADD FOREIGN KEY (ID_CLASS) REFERENCES SG_CLASS (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE CLASS_ATTR_DEF ADD FOREIGN KEY (ID_COORD) REFERENCES SG_COORD (ID) ENABLE VALIDATE;\n"
               );

     txt2.printf(
                // COORD_PAIRS
                "ALTER TABLE COORD_PAIRS ADD UNIQUE (PAIRS) ENABLE VALIDATE;\n"
                "ALTER TABLE COORD_PAIRS ADD UNIQUE (STR_PAIRS) ENABLE VALIDATE;\n"
               );

     txt2.printf(
                "ALTER TABLE CPLX_LEFT ADD UNIQUE (CL_HEADWORD) ENABLE VALIDATE;\n"
                "ALTER TABLE LANG_ALPHABET ADD FOREIGN KEY (ID_LANGUAGE) REFERENCES SG_LANGUAGE (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE LANG_ALPHABET ADD FOREIGN KEY (ID_ALPHABET) REFERENCES ABC_ALPHABET (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE LANG_LINK ADD FOREIGN KEY (ID_LANGUAGE) REFERENCES SG_LANGUAGE (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE LANG_LINK ADD FOREIGN KEY (ID_LANGUAGE2) REFERENCES SG_LANGUAGE (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE LANG_PARAM ADD FOREIGN KEY (ID_LANGUAGE) REFERENCES SG_LANGUAGE (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE LANG_PARAM ADD UNIQUE (ID_LANGUAGE, PARAM_NAME, ORDERING) ENABLE VALIDATE;\n"
                "ALTER TABLE MULTILEXEM ADD UNIQUE (TXT) ENABLE VALIDATE;\n"
                "ALTER TABLE PREDEF_ENTRIES ADD FOREIGN KEY (ID_ENTRY) REFERENCES SG_ENTRY (ID) ENABLE VALIDATE;\n"
                "CREATE UNIQUE INDEX IDX_SG_CLASS_1 ON SG_CLASS(NAME);\n"
                "ALTER TABLE SG_CLASS_COORD ADD FOREIGN KEY (ID_CLASS) REFERENCES SG_CLASS (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE SG_CLASS_COORD ADD FOREIGN KEY (ID_COORD) REFERENCES SG_COORD (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE SG_CLASS_COORD ADD CHECK (COORD_TYPE IN (0,1,2)) ENABLE VALIDATE;\n"
                "ALTER TABLE SG_COORD ADD CHECK (BISTABLE IN (0,1)) ENABLE VALIDATE;\n"
                "ALTER TABLE SG_COORD ADD UNIQUE (NAME) ENABLE VALIDATE;\n"
                "ALTER TABLE SG_CRITERION ADD UNIQUE (NAME) ENABLE VALIDATE;\n"
                "ALTER TABLE SG_ENTRY ADD FOREIGN KEY (ID_CLASS) REFERENCES SG_CLASS (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE SG_ENTRY ADD CHECK (EXPORTABLE IN (0,1)) ENABLE VALIDATE;\n"
                "CREATE INDEX SG_ENTRY_IDX1 ON SG_ENTRY(UNAME);\n"
                "ALTER TABLE SG_ENTRY_COORD ADD FOREIGN KEY (ID_ENTRY) REFERENCES SG_ENTRY (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE SG_ENTRY_COORD ADD FOREIGN KEY (ICOORD) REFERENCES SG_COORD (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE SG_ENTRY_COORD ADD FOREIGN KEY (ISTATE, ICOORD) REFERENCES SG_STATE (ID, ID_COORD) ENABLE VALIDATE;\n"
                "ALTER TABLE SG_FORM ADD FOREIGN KEY (ID_ENTRY) REFERENCES SG_ENTRY (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE SG_FORM ADD FOREIGN KEY (ID_LEXEM) REFERENCES SG_LEXEM (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE SG_FORM_COORD ADD FOREIGN KEY (ID_ENTRY) REFERENCES SG_ENTRY (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE SG_FORM_COORD ADD FOREIGN KEY (ICOORD) REFERENCES SG_COORD (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE SG_FORM_COORD ADD FOREIGN KEY (ID_ENTRY, IFORM) REFERENCES SG_FORM (ID_ENTRY, IFORM) ENABLE VALIDATE;\n"
                "ALTER TABLE SG_FORM_COORD ADD FOREIGN KEY (ISTATE, ICOORD) REFERENCES SG_STATE (ID, ID_COORD) ENABLE VALIDATE;\n"
                "CREATE INDEX SG_LINK_IDX1 ON SG_LINK(ID_ENTRY1);\n"
                "CREATE INDEX SG_LINK_IDX2 ON SG_LINK(ID_ENTRY2);\n"
                "ALTER TABLE SG_LINK ADD FOREIGN KEY (ID_ENTRY1) REFERENCES SG_ENTRY (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE SG_LINK ADD FOREIGN KEY (ID_ENTRY2) REFERENCES SG_ENTRY (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE SG_LINK ADD FOREIGN KEY (ICOORD) REFERENCES SG_COORD (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE SG_LINK ADD FOREIGN KEY (ISTATE, ICOORD) REFERENCES SG_STATE (ID, ID_COORD) ENABLE VALIDATE;\n"
                "ALTER TABLE SG_LINK_TAG ADD PRIMARY KEY (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE SG_LINK_TAG ADD FOREIGN KEY (ID_LINK) REFERENCES SG_LINK (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE SG_LINK_TAG ADD FOREIGN KEY (ID_TAG) REFERENCES SG_TAG (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE SG_LINK_TAG ADD FOREIGN KEY (ID_TAG, IVALUE) REFERENCES SG_TAG_VALUE (ID_TAG, IVALUE) ENABLE VALIDATE;\n"
                "CREATE INDEX SG_LINK_TAG ON SG_LINK_TAG(ID_LINK);\n"
                "ALTER TABLE SG_STATE ADD FOREIGN KEY (ID_COORD) REFERENCES SG_COORD (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE SG_STATE ADD FOREIGN KEY (ID_PARENT, ID_COORD) REFERENCES SG_STATE (ID, ID_COORD) ENABLE VALIDATE;\n"
                "ALTER TABLE SG_STATE ADD UNIQUE (ID_COORD, NAME) ENABLE VALIDATE;\n"
                "ALTER TABLE SG_STATE ADD CHECK (WEIGHT BETWEEN 0 AND 100) ENABLE VALIDATE;\n"
                "ALTER TABLE SG_TAG_VALUE ADD FOREIGN KEY (ID_TAG) REFERENCES SG_TAG (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE SG_TAG_VALUE ADD UNIQUE (ID_TAG, NAME) ENABLE VALIDATE;\n"
                "ALTER TABLE SG_TENTRY ADD FOREIGN KEY (TE_ID_LANGUAGE) REFERENCES SG_LANGUAGE (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE SG_TENTRY ADD FOREIGN KEY (TE_ID_CLASS) REFERENCES SG_CLASS (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE SG_TLINK ADD FOREIGN KEY (TL_TE_ID2) REFERENCES SG_TENTRY (TE_ID) ENABLE VALIDATE;\n"
                "ALTER TABLE SG_TLINK ADD FOREIGN KEY (TL_ICOORD, TL_ISTATE) REFERENCES SG_STATE (ID_COORD, ID) ENABLE VALIDATE;\n"
                "CREATE INDEX SG_TLINK_IDX1 ON SG_TLINK(TL_TE_ID1);\n"
                "CREATE INDEX SG_TLINK_IDX2 ON SG_TLINK(TL_TE_ID2);\n"
                "ALTER TABLE SG_TLINK_FLAG ADD FOREIGN KEY (TLF_TL_ID) REFERENCES SG_TLINK (TL_ID) ENABLE VALIDATE;\n"
                "ALTER TABLE SG_TLINK_TAG ADD FOREIGN KEY (TLT_TL_ID) REFERENCES SG_TLINK (TL_ID) ENABLE VALIDATE;\n"
                "ALTER TABLE SG_TLINK_TAG ADD FOREIGN KEY (TLT_ID_TAG) REFERENCES SG_TAG (ID) ENABLE VALIDATE;\n"
                "ALTER TABLE SG_TLINK_TAG ADD FOREIGN KEY (TLT_ID_TAG, TLT_IVALUE) REFERENCES SG_TAG_VALUE (ID_TAG, IVALUE) ENABLE VALIDATE;\n"
                "ALTER TABLE TNOTES ADD FOREIGN KEY (TN_TE_ID) REFERENCES SG_TENTRY (TE_ID) ENABLE VALIDATE;\n"
                "ALTER TABLE UNKNOWN_ENTRIES ADD FOREIGN KEY (ID) REFERENCES SG_ENTRY (ID) ENABLE VALIDATE;\n"
               );

     if( !sql_version.norules )
      txt2.printf(
                  "CREATE INDEX kb_fact_idx1 ON kb_fact(id_group);\n"
                  "CREATE INDEX kb_argument_point_idx1 ON kb_argument_point(id_fact);\n"
                 );

     txt2.printf(
                 "CREATE INDEX slb_condition_point_idx1 ON slb_condition_point(id_rule);\n"
                 "CREATE INDEX slb_result_point_idx1 ON slb_result_point(id_rule);\n"
                );

     if( !sql_version.norules )
      {
       txt2.printf(
                   "CREATE INDEX ts_head_lemma_idx1 ON ts_head_lemma(id_entry,id_group);\n"
                   "CREATE INDEX ts_head_word_idx1 ON ts_head_word(word,id_group);\n"
                   "CREATE INDEX ts_point_idx1 ON ts_point(id_parent);\n\n"
                   "CREATE INDEX ts_group2root_idx1 ON ts_group2root(id_group);\n\n"
                  );
       txt2.printf("CREATE INDEX word_assoc_idx1 ON word_assoc(id_entry);\n");
      }

     txt2.printf( "CREATE UNIQUE INDEX metaentry_idx1 ON metaentry(id_class,name);\n");
     txt2.printf("CREATE INDEX metaentry_item_idx1 ON metaentry_item(id_metaentry);\n");
     txt2.printf("CREATE UNIQUE INDEX metaentry_item_idx2 ON metaentry_item(id_metaentry,id_entry);\n");
    }

   txt.printf(
              "EXIT\n"  
              "\n" 
             ); 

   txt2.printf(
               "COMMIT;\n"
               "EXIT\n"  
               "\n" 
              ); 
  }
 else if( sql_version.type==SQL_Production::FireBird )
  {
   if( !sql_version.noschema )
    {
     txt.printf(
                "alter table tnotes add constraint pk_tnotes primary key(tn_id);\n"
                "alter table cplx_left add constraint pk_cplx_left primary key(cl_id);\n"
                "alter table sg_coord add constraint pk_sg_coord primary key(id);\n"
                "alter table sg_state add constraint pk_sg_state primary key(id,id_coord);\n"
                "alter table sg_language add constraint pk_sg_language primary key(id);\n"
                "alter table sg_entry add constraint pk_sg_entry primary key(id);\n"
                "alter table sg_lexem add constraint pk_sg_lexem primary key(id);\n"
                "alter table sg_class add constraint pk_sg_class primary key(id);\n"
                "alter table sg_form add constraint pk_sg_form primary key(id_entry,iform);\n"
                "alter table sg_link add constraint pk_sg_link primary key(id);\n"
                "alter table sg_tag add constraint pk_sg_tag primary key(id);\n"
                "alter table sg_tag_value add constraint pk_sg_tag_value primary key(id_tag,ivalue);\n"
                "alter table sg_tentry add constraint pk_sg_tentry primary key (te_id);\n"
                "alter table sg_link_tag add constraint pk_sg_link_tag primary key(id);\n"
                "alter table sg_tlink add constraint pk_sg_tlink primary key (tl_id);\n"
                "alter table sg_tlink_tag add constraint pk_sg_tlink_tag primary key(tlt_id);\n"
                "alter table sg_tlink_flag add constraint pk_sg_tlink_flag primary key(tlf_id);\n"
                "alter table aux_form_types add constraint pk_aux_form_types primary key(id);\n"
                "alter table aux_form add constraint pk_aux_form primary key(id);\n"
                "alter table aux_entry_data add constraint pk_aux_entry_data primary key(id);\n"
                "alter table SG_CRITERION add constraint PK_SG_CRITERION primary key (ID);\n"
                "alter table CLASS_ATTR_DEF add constraint PK_CLASS_ATTR_DEF primary key (ID);\n"
                "alter table COORD_PAIRS add constraint PK_COORD_PAIRS primary key (ID);\n"
                "alter table LANG_ALPHABET add constraint PK_LANG_ALPHABET primary key (ID);\n"
                "alter table LANG_LINK add constraint PK_LANG_LINK primary key (ID);\n"
                "alter table LANG_PARAM add constraint PK_LANG_PARAM primary key (ID);\n"
                "alter table MULTILEXEM add constraint PK_MULTILEXEM primary key (ID);\n"
                "alter table PREDEF_ENTRIES add constraint PK_PREDEF_ENTRIES primary key (ID);\n"
                "alter table TAG_SET add constraint PK_TAG_SET primary key (ID);\n"

                "alter table wordform_frequency add constraint PK_WORDFORM_FREQUENC primary key (ID);\n"
                "alter table misspelling add constraint PK_MISSPELLING primary key (ID);\n"

                "alter table abc_class add constraint pk_abc_class primary key (id);\n"
                "alter table abc_alphabet add constraint pk_abc_alphabet primary key (id);\n"
                "alter table abc_coord add constraint pk_abc_coord primary key (id);\n"
                "alter table abc_state add constraint pk_abc_state primary key (id,id_coord);\n"
                "alter table abc_pairs add constraint pk_abc_pairs primary key (id);\n"
                "alter table abc_pair add constraint pk_abc_pair primary key (id);\n"
                "alter table abc_entry add constraint pk_abc_entry primary key (id);\n"
                "alter table abc_form add constraint pk_abc_form primary key (id);\n"
                "alter table abc_criterion add constraint pk_abc_criterion primary key (id);\n"
                "alter table unknown_entries add constraint PK_UNKNOWN_ENTRIES primary key (ID);\n"

                "create unique index endings_idx1 on endings(ending,id_language);\n"
                "create unique index wordform_frequency_idx1 on wordform_frequency(id_entry,iform);\n"

                "create index misspelling_idx1 on misspelling(original_word,id_language);\n"
                "create index misspelling_idx2 on misspelling(original_word);\n"



                "create index tnotes_idx1 on tnotes(tn_te_id);\n"
                "create unique index cplx_left_idx1 on cplx_left(cl_headword);\n"
                "create index sg_entry_idx2 on sg_entry (uname);\n"
                "create unique index sg_lexem_2 on sg_lexem(name);\n"
                "create unique index miltilexem_1 on multilexem(txt);\n"
                "create index miltilexem_2 on multilexem(headword);\n"
                "create index sg_tlink_flag2 on sg_tlink_flag(tlf_tl_id);\n"

                "create index sg_tentry_idx5 on sg_tentry(te_text32);\n"
                "create index sg_entry_coord_idx1 on sg_entry_coord(id_entry);\n"
                "create index sg_entry_coord_idx2 on sg_entry_coord(id_entry,icoord);\n"
                "create index sg_link_1 on sg_link(icoord, istate);\n"
                "create index sg_link_2 on sg_link(id_entry1);\n"
                "create index sg_link_3 on sg_link(id_entry2);\n"
                "create index sg_tlink_1 on sg_tlink(tl_icoord, tl_istate);\n"
                "create index sg_tlink_2 on sg_tlink(tl_te_id1);\n"
                "create index sg_tlink_3 on sg_tlink(tl_te_id2);\n"
                "create index sg_class_coord_idx1 on sg_class_coord(id_class);\n"
                "create index sg_class_coord_idx2 on sg_class_coord(id_coord);\n"
                "create unique index sg_class_idx1 on sg_class(name);\n"
                "create index sg_class_idx2 on sg_class(id_lang);\n"
                "create index sg_form_idx1 on sg_form(id_lexem);\n"
                "create index sg_form_idx2 on sg_form(name);\n"
                "create index sg_form_idx4 on sg_form(id_entry);\n"
                "create index sg_link_tag_idx1 on sg_link_tag (id_link);\n"
               );
 

    if( !sql_version.norules )
     txt.printf(
                "CREATE UNIQUE INDEX word_entry_set_idx1 ON word_entry_set(name);\n"
                "CREATE UNIQUE INDEX word_set_idx1 ON word_set(name);\n"
                "CREATE UNIQUE INDEX collocation_set_idx1 ON collocation_set(name);\n"
                "CREATE UNIQUE INDEX collocation_headword_idx1 ON collocation_headword(headword);\n"
                "CREATE INDEX collocation_set_item_idx1 ON collocation_set_item(headword,id_set);\n"
                "CREATE UNIQUE INDEX collocation_set_item_idx2 ON collocation_set_item(words,id_set);\n"
                "CREATE UNIQUE INDEX wordform_set_idx1 ON wordform_set(name);\n"
                "CREATE INDEX wordform_set_item_idx1 ON wordform_set_item(id_set,word,id_entry);\n"
                "CREATE UNIQUE INDEX wordform_set_coords_idx1 ON wordform_set_coords(coords);\n"
               );

     if( !sql_version.IsDemo() )
      txt.printf(
                 "create index aux_form_idx1 on aux_form(id_entry,iform);\n"
                 "create index aux_entry_data_idx1 on aux_entry_data(id_entry);\n"
                 "CREATE INDEX aux_word_idx1 ON aux_word(aux_type,src);\n"

                 "alter table AUX_ENTRY_DATA add constraint FK_AUX_ENTRY_DATA_1 foreign key (ID_ENTRY) references SG_ENTRY(ID);\n"
                 "alter table AUX_FORM add constraint FK_AUX_FORM_1 foreign key (ID_ENTRY) references SG_ENTRY(ID);\n"
                 "alter table AUX_FORM add constraint FK_AUX_FORM_2 foreign key (ID_ENTRY,IFORM) references SG_FORM(ID_ENTRY,IFORM);\n"
                 "alter table AUX_FORM add constraint FK_AUX_FORM_3 foreign key (DATA_TYPE) references AUX_FORM_TYPES(ID);\n"
                );

     txt.printf(
                "alter table AUX_FORM_TYPES add constraint UNQ1_AUX_FORM_TYPES unique (NAME);\n"
                "alter table CLASS_ATTR_DEF add constraint FK_CLASS_ATTR_DEF_1 foreign key (ID_CLASS) references SG_CLASS(ID);\n"
                "alter table CLASS_ATTR_DEF add constraint FK_CLASS_ATTR_DEF_2 foreign key (ID_COORD) references SG_COORD(ID);\n"
                "alter table COORD_PAIRS add constraint UNQ1_COORD_PAIRS unique (PAIRS);\n"
                "alter table COORD_PAIRS add constraint UNQ2_COORD_PAIRS unique (STR_PAIRS);\n"
                "alter table CPLX_LEFT add constraint UNQ1_CPLX_LEFT unique (CL_HEADWORD);\n"
                "alter table LANG_ALPHABET add constraint FK_LANG_ALPHABET_1 foreign key (ID_LANGUAGE) references SG_LANGUAGE(ID);\n"
                "alter table LANG_ALPHABET add constraint FK_LANG_ALPHABET_2 foreign key (ID_ALPHABET) references ABC_ALPHABET(ID);\n"
                "alter table LANG_LINK add constraint FK_LANG_LINK_1 foreign key (ID_LANGUAGE) references SG_LANGUAGE(ID);\n"
                "alter table LANG_LINK add constraint FK_LANG_LINK_2 foreign key (ID_LANGUAGE2) references SG_LANGUAGE(ID);\n"
                "alter table LANG_PARAM add constraint FK_LANG_PARAM_1 foreign key (ID_LANGUAGE) references SG_LANGUAGE(ID);\n"
                "alter table MULTILEXEM add constraint UNQ1_MULTILEXEM unique (TXT);\n"
                "alter table MULTILEXEM add constraint CHK1_MULTILEXEM check (N_LEXEM>1);\n"
               );

     if( !sql_version.IsDemo() )
      txt.printf(
                 "alter table PREDEF_ENTRIES add constraint FK_PREDEF_ENTRIES_1 foreign key (ID_ENTRY) references SG_ENTRY(ID);\n"
                );

     txt.printf(
                "alter table SG_ENTRY add constraint FK_SG_ENTRY_1 foreign key (ID_CLASS) references SG_CLASS(ID);\n"
                "alter table SG_ENTRY add constraint CHK1_SG_ENTRY check (EXPORTABLE IN (0,1));\n"
                "alter table SG_ENTRY_COORD add constraint FK_SG_ENTRY_COORD_1 foreign key (ID_ENTRY) references SG_ENTRY(ID);\n"
                "alter table SG_ENTRY_COORD add constraint FK_SG_ENTRY_COORD_2 foreign key (ICOORD) references SG_COORD(ID);\n"
                 "alter table SG_ENTRY_COORD add constraint FK_SG_ENTRY_COORD_3 foreign key (ISTATE,ICOORD) references SG_STATE(ID,ID_COORD);\n"
               );

     if( !sql_version.IsDemo() )
      txt.printf(
                 "alter table SG_FORM add constraint FK_SG_FORM_1 foreign key (ID_ENTRY) references SG_ENTRY(ID);\n"
                 "alter table sg_form add constraint fk_sg_form_2 foreign key (id_lexem) references sg_lexem (id);\n"
                );

     txt.printf(
                "alter table sg_form add constraint fk_sg_form_3 foreign key (id_dims) references coord_pairs (id);\n"
                "alter table SG_FORM_COORD add constraint FK_SG_FORM_COORD_1 foreign key (ID_ENTRY) references SG_ENTRY(ID);\n"
                "alter table SG_FORM_COORD add constraint FK_SG_FORM_COORD_2 foreign key (ID_ENTRY,IFORM) references SG_FORM(ID_ENTRY,IFORM);\n"
                "alter table SG_FORM_COORD add constraint FK_SG_FORM_COORD_3 foreign key (ICOORD) references SG_COORD(ID);\n"
                "alter table SG_FORM_COORD add constraint FK_SG_FORM_COORD_4 foreign key (ISTATE,ICOORD) references SG_STATE(ID,ID_COORD);\n"
                "alter table SG_LANGUAGE add constraint UNQ1_SG_LANGUAGE unique (NAME);\n"
                "alter table SG_LINK add constraint FK_SG_LINK_1 foreign key (ID_ENTRY1) references SG_ENTRY(ID);\n"
                "alter table SG_LINK add constraint FK_SG_LINK_2 foreign key (ID_ENTRY2) references SG_ENTRY(ID);\n"
                "alter table SG_LINK add constraint FK_SG_LINK_3 foreign key (ISTATE,ICOORD) references SG_STATE(ID,ID_COORD);\n"
                "alter table TAG_SET add constraint UNQ1_TAG_SET unique (TAGS);\n"
                "alter table SG_LINK add constraint FK_SG_LINK_4 foreign key (TAGS) references TAG_SET(ID);\n"
                "alter table SG_CLASS_COORD add constraint CHK1_SG_CLASS_COORD check (COORD_TYPE IN (0,1,2));\n"
                "alter table SG_CLASS add constraint UNQ1_SG_CLASS unique (NAME);\n"
                "alter table SG_CLASS add constraint FK_SG_CLASS_1 foreign key (ID_LANG) references SG_LANGUAGE(ID);\n"
                "alter table SG_CLASS add constraint CHK1_SG_CLASS check (WEIGHT BETWEEN 0 AND 100);\n"
                "alter table SG_CLASS_COORD add constraint FK_SG_CLASS_COORD_1 foreign key (ID_CLASS) references SG_CLASS(ID);\n"
                "alter table SG_CLASS_COORD add constraint FK_SG_CLASS_COORD_2 foreign key (ID_COORD) references SG_COORD(ID);\n"
                "alter table SG_COORD add constraint UNQ1_SG_COORD unique (NAME);\n"
                "alter table SG_COORD add constraint CHK1_SG_COORD check (BISTABLE IN (0,1));\n"

                "create index abc_entry_idx2 on abc_entry(code);\n"
                "create index abc_form_idx2 on abc_form(code);\n"

                "alter table ABC_ENTRY add constraint FK_ABC_ENTRY_1 foreign key (ID_CLASS) references ABC_CLASS(ID);\n"
                "alter table ABC_ENTRY add constraint FK_ABC_ENTRY_2 foreign key (ID_ALPHABET) references ABC_ALPHABET(ID);\n"
                "alter table ABC_ENTRY add constraint FK_ABC_ENTRY_3 foreign key (ID_PAIRS) references ABC_PAIRS(ID);\n"
                "alter table ABC_FORM add constraint FK_ABC_FORM_1 foreign key (ID_ENTRY) references ABC_ENTRY(ID);\n"
                "alter table ABC_FORM add constraint FK_ABC_FORM_2 foreign key (ID_PAIRS) references ABC_PAIRS(ID);\n"
                "alter table ABC_PAIR add constraint FK_ABC_PAIR_1 foreign key (ID_PAIRS) references ABC_PAIRS(ID);\n"
                "alter table ABC_PAIR add constraint FK_ABC_PAIR_2 foreign key (ID_COORD) references ABC_COORD(ID);\n"
                "alter table ABC_PAIR add constraint FK_ABC_PAIR_3 foreign key (ID_STATE,ID_COORD) references ABC_STATE(ID,ID_COORD);\n"
                "alter table ABC_STATE add constraint FK_ABC_STATE_1 foreign key (ID_COORD) references ABC_COORD(ID);\n"
                "alter table ABC_CLASS_COORD add constraint FK_ABC_CLASS_COORD_1 foreign key (ID_CLASS) references ABC_CLASS(ID);\n"
                "alter table ABC_CLASS_COORD add constraint FK_ABC_CLASS_COORD_2 foreign key (ID_COORD) references ABC_COORD(ID);\n"
                "alter table ABC_CLASS_COORD add constraint CHK1_ABC_CLASS_COORD check (coord_type in (0,1));\n"
                "alter table ABC_COORD add constraint CHK1_ABC_COORD check (BISTABLE IN (0,1));\n"
                "alter table SG_TAG add constraint UNQ1_SG_TAG unique (NAME);\n"
                "alter table SG_TAG_VALUE add constraint FK_SG_TAG_VALUE_1 foreign key (ID_TAG) references SG_TAG(ID);\n"
                "alter table SG_TAG_VALUE add constraint UNQ1_SG_TAG_VALUE unique (ID_TAG,NAME);\n"
                "alter table SG_STATE add constraint UNQ1_SG_STATE unique (ID_COORD,NAME);\n"
                "alter table SG_STATE add constraint FK_SG_STATE_1 foreign key (ID_COORD) references SG_COORD(ID);\n"
                "alter table SG_STATE add constraint FK_SG_STATE_2 foreign key (ID_PARENT,ID_COORD) references SG_STATE(ID,ID_COORD);\n"
                "alter table SG_STATE add constraint CHK1_SG_STATE check (WEIGHT BETWEEN 0 AND 100);\n"
                "alter table SG_TENTRY add constraint FK_SG_TENTRY_1 foreign key (TE_ID_LANGUAGE) references SG_LANGUAGE(ID);\n"
                "alter table SG_TENTRY add constraint FK_SG_TENTRY_2 foreign key (TE_ID_CLASS) references SG_CLASS(ID);\n"
                "alter table SG_TLINK add constraint FK_SG_TLINK_1 foreign key (TL_TE_ID1) references SG_TENTRY(TE_ID);\n"
                "alter table SG_TLINK add constraint FK_SG_TLINK_2 foreign key (TL_TE_ID2) references SG_TENTRY(TE_ID);\n"
                "alter table SG_TLINK add constraint FK_SG_TLINK_3 foreign key (TL_ICOORD) references SG_COORD(ID);\n"
                "alter table SG_TLINK add constraint FK_SG_TLINK_4 foreign key (TL_ISTATE,TL_ICOORD) references SG_STATE(ID,ID_COORD);\n"
                "alter table SG_TLINK add constraint FK_SG_TLINK_5 foreign key (TL_TAGS) references TAG_SET(ID);\n"
                "alter table SG_TLINK_FLAG add constraint FK_SG_TLINK_FLAG_1 foreign key (TLF_TL_ID) references SG_TLINK(TL_ID);\n"
                "alter table SG_TLINK_TAG add constraint FK_SG_TLINK_TAG_1 foreign key (TLT_TL_ID) references SG_TLINK(TL_ID);\n"
                "alter table SG_TLINK_TAG add constraint FK_SG_TLINK_TAG_2 foreign key (TLT_ID_TAG) references SG_TAG(ID);\n"
                "alter table SG_TLINK_TAG add constraint FK_SG_TLINK_TAG_3 foreign key (TLT_ID_TAG,TLT_IVALUE) references SG_TAG_VALUE(ID_TAG,IVALUE);\n"
                "alter table TNOTES add constraint FK_TNOTES_1 foreign key (TN_TE_ID) references SG_TENTRY(TE_ID);\n"
                "alter table SG_LINK_TAG add constraint FK_SG_LINK_TAG_1 foreign key (ID_LINK) references SG_LINK(ID);\n"
                "alter table SG_LINK_TAG add constraint FK_SG_LINK_TAG_2 foreign key (ID_TAG) references SG_TAG(ID);\n"
                "alter table SG_LINK_TAG add constraint FK_SG_LINK_TAG_3 foreign key (ID_TAG,IVALUE) references SG_TAG_VALUE(ID_TAG,IVALUE);\n"
               );
     txt.printf( "%s\n", sql_version.CommitTx().c_str() );

     txt.printf( "%s\n", sql_version.BeginTx().c_str() );
     txt.printf(
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'ID_ENTRY') and (RDB$RELATION_NAME = 'SG_ENTRY_COORD');\n"
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'ICOORD') and (RDB$RELATION_NAME = 'SG_ENTRY_COORD');\n"
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'ISTATE') and (RDB$RELATION_NAME = 'SG_ENTRY_COORD');\n"
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'NAME') and (RDB$RELATION_NAME = 'SG_FORM');\n"
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'ID_LEXEM') and (RDB$RELATION_NAME = 'SG_FORM');\n"
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'NAME') and (RDB$RELATION_NAME = 'SG_ENTRY');\n"
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'UNAME') and (RDB$RELATION_NAME = 'SG_ENTRY');\n"
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'NAME') and (RDB$RELATION_NAME = 'SG_LEXEM');\n"
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'ID_ENTRY') and (RDB$RELATION_NAME = 'SG_FORM_COORD');\n"
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'IFORM') and (RDB$RELATION_NAME = 'SG_FORM_COORD');\n"
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'ICOORD') and (RDB$RELATION_NAME = 'SG_FORM_COORD');\n"
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'ISTATE') and (RDB$RELATION_NAME = 'SG_FORM_COORD');\n"
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'NAME') and (RDB$RELATION_NAME = 'SG_TAG');\n"
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'NAME') and (RDB$RELATION_NAME = 'SG_TAG_VALUE');\n"
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'TE_TEXT') and (RDB$RELATION_NAME = 'SG_TENTRY');\n"
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'TE_UTXT') and (RDB$RELATION_NAME = 'SG_TENTRY');\n"
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'TL_TE_ID1') and (RDB$RELATION_NAME = 'SG_TLINK');\n"
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'TL_TE_ID2') and (RDB$RELATION_NAME = 'SG_TLINK');\n"
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'TL_ICOORD') and (RDB$RELATION_NAME = 'SG_TLINK');\n"
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'TL_ISTATE') and (RDB$RELATION_NAME = 'SG_TLINK');\n"
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'TLF_TL_ID') and (RDB$RELATION_NAME = 'SG_TLINK_FLAG');\n"
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'TLF_FLAG') and (RDB$RELATION_NAME = 'SG_TLINK_FLAG');\n"
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'TLF_VALUE') and (RDB$RELATION_NAME = 'SG_TLINK_FLAG');\n"
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'TLT_TL_ID') and (RDB$RELATION_NAME = 'SG_TLINK_TAG');\n"
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'TLT_ID_TAG') and (RDB$RELATION_NAME = 'SG_TLINK_TAG');\n"
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'TLT_IVALUE') and (RDB$RELATION_NAME = 'SG_TLINK_TAG');\n"
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'TN_TE_ID') and (RDB$RELATION_NAME = 'TNOTES');\n"
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'TN_TYPE') and (RDB$RELATION_NAME = 'TNOTES');\n"
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'TN_FORMAT') and (RDB$RELATION_NAME = 'TNOTES');\n"
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'TN_DATA') and (RDB$RELATION_NAME = 'TNOTES');\n"
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'ID_LINK') and (RDB$RELATION_NAME = 'SG_LINK_TAG');\n"
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'ID_TAG') and (RDB$RELATION_NAME = 'SG_LINK_TAG');\n"
                "update RDB$RELATION_FIELDS set RDB$NULL_FLAG = 1 where (RDB$FIELD_NAME = 'IVALUE') and (RDB$RELATION_NAME = 'SG_LINK_TAG');\n"
                "\n"
               );
     txt.printf( "%s\n", sql_version.CommitTx().c_str() );

     txt.printf( "%s\n", sql_version.BeginTx().c_str() );
     if( !sql_version.norules )
      { 
       txt.printf(
                  "CREATE INDEX kb_fact_idx1 ON kb_fact(id_group);\n"
                  "CREATE INDEX kb_argument_point_idx1 ON kb_argument_point(id_fact);\n"
                 );
      }

     txt.printf(
                "CREATE INDEX slb_condition_point_idx1 ON slb_condition_point(id_rule);\n"
                "CREATE INDEX slb_result_point_idx1 ON slb_result_point(id_rule);\n"
               );
     txt.printf( "%s\n", sql_version.CommitTx().c_str() );


     txt.printf( "%s\n", sql_version.BeginTx().c_str() );
     if( !sql_version.noformcoords )
      {
       txt.printf(
                  "create index sg_form_coord_idx1 on sg_form_coord (id_entry,iform);\n"
                  "create index sg_form_coord_idx2 on sg_form_coord (istate,icoord);\n"
                  "\n"
                 );
      }

     if( !sql_version.norules )
      txt.printf(
                 "CREATE INDEX ts_head_lemma_idx1 ON ts_head_lemma(id_entry,id_group);\n"
                 "CREATE INDEX ts_head_word_idx1 ON ts_head_word(word,id_group);\n"
                 "CREATE INDEX ts_point_idx1 ON ts_point(id_parent);\n"
                 "CREATE INDEX ts_group2root_idx1 ON ts_group2root(id_group);\n"
                 "CREATE INDEX word_assoc_idx1 ON word_assoc(id_entry);\n\n"
                );

     txt.printf( "CREATE UNIQUE INDEX metaentry_idx1 ON metaentry(id_class,name);\n");
     txt.printf("CREATE INDEX metaentry_item_idx1 ON metaentry_item(id_metaentry);\n");
     txt.printf("CREATE UNIQUE INDEX metaentry_item_idx2 ON metaentry_item(id_metaentry,id_entry);\n");
     txt.printf( "%s\n", sql_version.CommitTx().c_str() );
    }
  }
 else if( sql_version.type==SQL_Production::MySql )
  {
   if( !sql_version.noschema )
    {
     txt.printf(
                "alter table tnotes modify column tn_id int not null auto_increment;\n"
                "alter table tnotes add index tnotes_idx1(tn_te_id);\n"
                "alter table tnotes add index tnotes_idx2(tn_data);\n"
                "alter table sg_tlink_flag modify column tlf_id int not null auto_increment;\n"
                "alter table sg_tlink_flag add index sg_tlink_flag2(tlf_tl_id);\n"
                "alter table cplx_left modify column cl_id int not null auto_increment;\n"
                "alter table cplx_left add unique index cplx_left_idx1(cl_headword);\n"
                "alter table sg_entry modify column id int unsigned not null auto_increment;\n"
                "alter table sg_entry add index sg_entry_1(uname);\n"
                "alter table sg_entry add index sg_entry_3(id_class);\n"
                "alter table sg_class add unique index sg_class_idx2(name);\n"
                "alter table sg_class add index sg_class_idx3(id_lang);\n"
                "alter table sg_class_coord add index sg_class_coord_1(id_class);\n"
                "alter table sg_class_coord add index sg_class_coord_2(id_coord);\n"
                "alter table sg_coord add index sg_coord_1(id);\n"
                "alter table sg_entry_coord add index sg_entry_coord_1(id_entry);\n"
                "alter table sg_entry_coord add index sg_entry_coord_2(id_entry,icoord);\n"
                "alter table sg_form add primary key (id_entry, iform);\n"
                "alter table sg_form add index sg_form_idx2(name);\n"
                "alter table sg_form add index sg_form_idx3(id_lexem);\n"
                "alter table sg_form add index sg_form_idx4(id_entry);\n"
                "alter table sg_lexem modify column id int unsigned not null auto_increment;\n"

                "alter table sg_lexem add unique index sg_lexem_2(name);\n"
                "alter table multilexem add unique index multilexem_1(txt);\n"
                "alter table multilexem add index multilexem_2(headword);\n"

                "alter table misspelling add index misspelling_idx1(original_word,id_language);\n"
                "alter table misspelling add index misspelling_idx2(original_word);\n"

                "alter table sg_link_tag modify column id int not null auto_increment;\n"
                "alter table sg_link_tag add index sg_link_tag_2(id_link);\n"
                "alter table sg_state add primary key (id, id_coord);\n"
                "alter table sg_tag_value add primary key (id_tag, ivalue);\n"
                "alter table sg_tentry modify column te_id int not null auto_increment;\n"
                "alter table sg_tentry add index sg_tentry_idx5(te_text32);\n"
                "alter table sg_tlink modify column tl_id int not null auto_increment;\n"
                "alter table sg_tlink add index sg_tlink_te1(tl_te_id1);\n"
                "alter table sg_tlink add index sg_tlink_te2(tl_te_id2);\n"
                "alter table sg_tlink add index sg_tlink_3(tl_icoord, tl_istate);\n"
                "alter table sg_tlink_tag modify column tlt_id int not null auto_increment;\n"
                "alter table sg_tlink_tag add index sg_tlink_tag_2(tlt_tl_id);\n"
                "alter table sg_link modify column id int not null auto_increment;\n"
                "alter table sg_link add index sg_link_e1(id_entry1);\n"
                "alter table sg_link add index sg_link_e2(id_entry2);\n"
                "alter table sg_link add index sg_link_3(icoord, istate);\n"

                "alter table endings add unique index endings_idx1(ending,id_language);\n"
                "alter table wordform_frequency add unique index wordform_frequency_idx1(id_entry,iform);\n"

                "alter table aux_form_types modify column id int not null auto_increment;\n"

                "alter table aux_form modify column id int not null auto_increment;\n"
                "alter table aux_form add index aux_form_idx1(id_entry,iform);\n"

                "alter table aux_entry_data modify column id int not null auto_increment;\n"
                "alter table aux_entry_data add index aux_entry_data_idx1(id_entry);\n"

                "ALTER TABLE abc_entry ADD INDEX abc_entry_idx2(code);\n"
                "ALTER TABLE abc_form ADD INDEX abc_form_idx2(code);\n"

                "CREATE UNIQUE INDEX word_entry_set_idx1 ON word_entry_set(name);\n"
                "CREATE UNIQUE INDEX word_set_idx1 ON word_set(name);\n"
                "CREATE UNIQUE INDEX collocation_set_idx1 ON collocation_set(name);\n"
                "CREATE UNIQUE INDEX collocation_headword_idx1 ON collocation_headword(headword);\n"
                "CREATE INDEX collocation_set_item_idx1 ON collocation_set_item(headword,id_set);\n"
                "CREATE UNIQUE INDEX collocation_set_item_idx2 ON collocation_set_item(words,id_set);\n"

                "CREATE INDEX kb_fact_idx1 ON kb_fact(id_group);\n"
                "CREATE INDEX kb_argument_point_idx1 ON kb_argument_point(id_fact);\n"

                "CREATE UNIQUE INDEX wordform_set_idx1 ON wordform_set(name);\n"
                "CREATE INDEX wordform_set_item_idx1 ON wordform_set_item(id_set,word,id_entry);\n"
                "CREATE UNIQUE INDEX wordform_set_coords_idx1 ON wordform_set_coords(coords);\n"

                "CREATE UNIQUE INDEX omonym_idx1 ON omonym(entry_name,id_class);\n"
                "\n"
               );

     if( !sql_version.norules )
      {
       txt.printf(
                  "CREATE INDEX SynPatternTree_idx1 ON SynPatternTree(id_tree);\n"
                  "CREATE INDEX kb_fact_index_idx1 ON kb_fact_index1(id_group,word1,word2);\n"
                  "CREATE INDEX kb_fact_index_idx2 ON kb_fact_index1(id_group,word1,word2,word3);\n"
                  "CREATE INDEX kb_fact_index_idx3 ON kb_fact_index2(id_group,id_entry1,id_entry2);\n"
                  "CREATE INDEX kb_fact_index_idx4 ON kb_fact_index2(id_group,id_entry1,id_entry2,id_entry3);\n"
                  "CREATE INDEX generic_tree_scorer_idx1 ON generic_tree_scorer(id_group);\n"
                  "CREATE INDEX ts_predicate_idx1 ON ts_predicate(id_point);\n"
                 );
      }
 
     if( !sql_version.noformcoords )
      {
       txt.printf(
                  "alter table sg_form_coord add index sg_form_coord_1(id_entry, iform, icoord);\n"
                 );
      }


 txt2.printf(
 "ALTER TABLE class_attr_def ADD CONSTRAINT class_attr_def_FK1 FOREIGN KEY class_attr_def_FK1 (id_class) REFERENCES sg_class (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE class_attr_def ADD CONSTRAINT class_attr_def_FK2 FOREIGN KEY class_attr_def_FK2 (id_coord) REFERENCES sg_coord (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE crop_rule ADD CONSTRAINT crop_rule_FK1 FOREIGN KEY crop_rule_FK1 (id_language) REFERENCES sg_language (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE ending_stat ADD CONSTRAINT ending_stat_FK1 FOREIGN KEY ending_stat_FK1 (id_language) REFERENCES sg_language (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE endings ADD CONSTRAINT FK_endings_1 FOREIGN KEY FK_endings_1 (id_language) REFERENCES sg_language (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE lang_alphabet ADD CONSTRAINT FK_lang_alphabet_1 FOREIGN KEY FK_lang_alphabet_1 (id_language) REFERENCES sg_language (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE lang_alphabet ADD CONSTRAINT FK_lang_alphabet_2 FOREIGN KEY FK_lang_alphabet_2 (id_alphabet) REFERENCES abc_alphabet (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE lang_link ADD CONSTRAINT FK_lang_link_1 FOREIGN KEY FK_lang_link_1 (id_language) REFERENCES sg_language (id) ON DELETE CASCADE ON UPDATE RESTRICT;\n"
 "ALTER TABLE lang_link ADD CONSTRAINT FK_lang_link_2 FOREIGN KEY FK_lang_link_2 (id_language2) REFERENCES sg_language (id) ON DELETE CASCADE ON UPDATE RESTRICT;\n"
 "ALTER TABLE lang_param ADD CONSTRAINT FK_lang_param_1 FOREIGN KEY FK_lang_param_1 (id_language) REFERENCES sg_language (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE lang_usage ADD CONSTRAINT FK_lang_usage_1 FOREIGN KEY FK_lang_usage_1 (id_language) REFERENCES sg_language (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE misspelling ADD CONSTRAINT FK_misspelling_1 FOREIGN KEY FK_misspelling_1 (id_language) REFERENCES sg_language (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE paradigma ADD CONSTRAINT FK_paradigma_1 FOREIGN KEY FK_paradigma_1 (id_class) REFERENCES sg_class (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE paradigma_form ADD CONSTRAINT FK_paradigma_form_1 FOREIGN KEY FK_paradigma_form_1 (id_paradigma) REFERENCES paradigma (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE paradigma_name ADD CONSTRAINT FK_paradigma_name_1 FOREIGN KEY FK_paradigma_name_1 (id_paradigma) REFERENCES paradigma (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE ph_rule ADD CONSTRAINT FK_ph_rule_1 FOREIGN KEY FK_ph_rule_1 (id_language) REFERENCES sg_language (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE predef_entries ADD CONSTRAINT FK_predef_entries_1 FOREIGN KEY FK_predef_entries_1 (id_entry) REFERENCES sg_entry (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE recog_rule ADD CONSTRAINT FK_recog_rule_1 FOREIGN KEY FK_recog_rule_1 (id_language) REFERENCES sg_language (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE recog_rule ADD CONSTRAINT FK_recog_rule_2 FOREIGN KEY FK_recog_rule_2 (id_entry) REFERENCES sg_entry (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE collocation_set_item ADD CONSTRAINT collocation_set_item_FK1 FOREIGN KEY collocation_set_item_FK1 (id_set) REFERENCES collocation_set (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE sg_class ADD CONSTRAINT FK_sg_class_1 FOREIGN KEY FK_sg_class_1 (id_lang) REFERENCES sg_language (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE sg_class_coord ADD CONSTRAINT FK_sg_class_coord_1 FOREIGN KEY FK_sg_class_coord_1 (id_class) REFERENCES sg_class (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE sg_class_coord ADD CONSTRAINT FK_sg_class_coord_2 FOREIGN KEY FK_sg_class_coord_2 (id_coord) REFERENCES sg_coord (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE sg_entry ADD CONSTRAINT FK_sg_entry_1 FOREIGN KEY FK_sg_entry_1 (id_class) REFERENCES sg_class (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE sg_coord ADD UNIQUE INDEX sg_coord_idx2(name);\n"
 "ALTER TABLE sg_criterion ADD UNIQUE INDEX sg_criterion_idx2(name);\n"
 "ALTER TABLE sg_entry_coord ADD CONSTRAINT FK_sg_entry_coord_1 FOREIGN KEY FK_sg_entry_coord_1 (id_entry) REFERENCES sg_entry (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE sg_entry_coord ADD CONSTRAINT FK_sg_entry_coord_2 FOREIGN KEY FK_sg_entry_coord_2 (icoord) REFERENCES sg_coord (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE sg_form ADD CONSTRAINT FK_sg_form_1 FOREIGN KEY FK_sg_form_1 (id_entry) REFERENCES sg_entry (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE sg_form ADD CONSTRAINT FK_sg_form_2 FOREIGN KEY FK_sg_form_2 (id_lexem) REFERENCES sg_lexem (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE sg_form ADD CONSTRAINT FK_sg_form_3 FOREIGN KEY FK_sg_form_3 (id_dims) REFERENCES coord_pairs (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE sg_language ADD UNIQUE INDEX sg_language_idx1(name);\n"
 "ALTER TABLE sg_link ADD CONSTRAINT FK_sg_link_1 FOREIGN KEY FK_sg_link_1 (id_entry1) REFERENCES sg_entry (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE sg_link ADD CONSTRAINT FK_sg_link_2 FOREIGN KEY FK_sg_link_2 (id_entry2) REFERENCES sg_entry (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE sg_link ADD CONSTRAINT FK_sg_link_3 FOREIGN KEY FK_sg_link_3 (icoord) REFERENCES sg_coord (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE sg_link ADD CONSTRAINT FK_sg_link_4 FOREIGN KEY FK_sg_link_4 (istate, icoord) REFERENCES sg_state (id, id_coord) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE sg_link_tag ADD CONSTRAINT FK_sg_link_tag_1 FOREIGN KEY FK_sg_link_tag_1 (id_link) REFERENCES sg_link (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE sg_link_tag ADD CONSTRAINT FK_sg_link_tag_2 FOREIGN KEY FK_sg_link_tag_2 (id_tag) REFERENCES sg_tag (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE sg_link_tag ADD CONSTRAINT FK_sg_link_tag_3 FOREIGN KEY FK_sg_link_tag_3 (id_tag, ivalue) REFERENCES sg_tag_value (id_tag, ivalue) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE sg_state ADD CONSTRAINT FK_sg_state_1 FOREIGN KEY FK_sg_state_1 (id_coord) REFERENCES sg_coord (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE sg_tag ADD UNIQUE INDEX sg_tag_idx1(name);\n"
 "ALTER TABLE sg_tag_value ADD CONSTRAINT FK_sg_tag_value_1 FOREIGN KEY FK_sg_tag_value_1 (id_tag) REFERENCES sg_tag (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE sg_tag_value ADD UNIQUE INDEX sg_tag_value(id_tag, name);\n"
 "ALTER TABLE sg_state ADD UNIQUE INDEX sg_state_idx2(id_coord, name);\n"
 "ALTER TABLE sg_tentry ADD CONSTRAINT FK_sg_tentry_1 FOREIGN KEY FK_sg_tentry_1 (te_id_language) REFERENCES sg_language (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE sg_tentry ADD CONSTRAINT FK_sg_tentry_2 FOREIGN KEY FK_sg_tentry_2 (te_id_class) REFERENCES sg_class (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE sg_tlink ADD CONSTRAINT FK_sg_tlink_1 FOREIGN KEY FK_sg_tlink_1 (tl_te_id1) REFERENCES sg_tentry (te_id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE sg_tlink ADD CONSTRAINT FK_sg_tlink_2 FOREIGN KEY FK_sg_tlink_2 (tl_te_id2) REFERENCES sg_tentry (te_id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE sg_tlink ADD CONSTRAINT FK_sg_tlink_3 FOREIGN KEY FK_sg_tlink_3 (tl_icoord) REFERENCES sg_coord (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE sg_tlink ADD CONSTRAINT FK_sg_tlink_4 FOREIGN KEY FK_sg_tlink_4 (tl_istate, tl_icoord) REFERENCES sg_state (id, id_coord) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE sg_tlink ADD CONSTRAINT FK_sg_tlink_5 FOREIGN KEY FK_sg_tlink_5 (tl_tags) REFERENCES tag_set (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE sg_tlink_flag ADD CONSTRAINT FK_sg_tlink_flag_1 FOREIGN KEY FK_sg_tlink_flag_1 (tlf_tl_id) REFERENCES sg_tlink (tl_id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE sg_tlink_tag ADD CONSTRAINT FK_sg_tlink_tag_1 FOREIGN KEY FK_sg_tlink_tag_1 (tlt_tl_id) REFERENCES sg_tlink (tl_id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE sg_tlink_tag ADD CONSTRAINT FK_sg_tlink_tag_2 FOREIGN KEY FK_sg_tlink_tag_2 (tlt_id_tag) REFERENCES sg_tag (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE sg_tlink_tag ADD CONSTRAINT FK_sg_tlink_tag_3 FOREIGN KEY FK_sg_tlink_tag_3 (tlt_id_tag, tlt_ivalue) REFERENCES sg_tag_value (id_tag, ivalue) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE SynPatternTree ADD CONSTRAINT FK_synpatterntree_1 FOREIGN KEY FK_synpatterntree_1 (id_language) REFERENCES sg_language (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE SynPatternTree ADD INDEX synpatterntree_idx2(uname);\n"
 "ALTER TABLE tnotes ADD CONSTRAINT FK_tnotes_1 FOREIGN KEY FK_tnotes_1 (tn_te_id) REFERENCES sg_tentry (te_id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE unbreakable ADD CONSTRAINT FK_unbreakable_1 FOREIGN KEY FK_unbreakable_1 (id_language) REFERENCES sg_language (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE unknown_entries ADD CONSTRAINT FK_unknown_entries_1 FOREIGN KEY FK_unknown_entries_1 (id) REFERENCES sg_entry (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE wordform_frequency ADD CONSTRAINT FK_wordform_frequency_1 FOREIGN KEY FK_wordform_frequency_1 (id_entry) REFERENCES sg_entry (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE wordform_frequency ADD CONSTRAINT FK_wordform_frequency_2 FOREIGN KEY FK_wordform_frequency_2 (id_entry, iform) REFERENCES sg_form (id_entry, iform) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE aux_entry_data ADD CONSTRAINT FK_aux_entry_data_1 FOREIGN KEY FK_aux_entry_data_1 (id_entry) REFERENCES sg_entry (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE aux_form ADD CONSTRAINT FK_aux_form_1 FOREIGN KEY FK_aux_form_1 (id_entry) REFERENCES sg_entry (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE aux_form ADD CONSTRAINT FK_aux_form_2 FOREIGN KEY FK_aux_form_2 (id_entry, iform) REFERENCES sg_form (id_entry, iform) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE aux_form_types ADD UNIQUE INDEX aux_form_types_idx1(name);\n"
 "ALTER TABLE abc_class_coord ADD CONSTRAINT FK_abc_class_coord_1 FOREIGN KEY FK_abc_class_coord_1 (id_class) REFERENCES abc_class (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE abc_class_coord ADD CONSTRAINT FK_abc_class_coord_2 FOREIGN KEY FK_abc_class_coord_2 (id_coord) REFERENCES abc_coord (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE abc_entry ADD CONSTRAINT FK_abc_entry_1 FOREIGN KEY FK_abc_entry_1 (id_class) REFERENCES abc_class (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE abc_entry ADD CONSTRAINT FK_abc_entry_2 FOREIGN KEY FK_abc_entry_2 (id_alphabet) REFERENCES abc_alphabet (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE abc_entry ADD CONSTRAINT FK_abc_entry_3 FOREIGN KEY FK_abc_entry_3 (id_pairs) REFERENCES abc_pairs (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE abc_operation_item ADD CONSTRAINT FK_abc_operation_item_1 FOREIGN KEY FK_abc_operation_item_1 (id_operation) REFERENCES abc_operation (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE abc_state ADD INDEX abc_state_idx1(id_coord);\n"
 "ALTER TABLE abc_state ADD CONSTRAINT FK_abc_state_1 FOREIGN KEY FK_abc_state_1 (id_coord) REFERENCES abc_coord (id) ON DELETE RESTRICT ON UPDATE RESTRICT;\n"
 "ALTER TABLE abc_state ADD UNIQUE INDEX abc_state_idx2(name, id_coord);\n"
);


     txt2.printf(
                 "CREATE INDEX slb_condition_point_idx1 ON slb_condition_point(id_rule);\n"
                 "CREATE INDEX slb_result_point_idx1 ON slb_result_point(id_rule);\n"
                );

     if( !sql_version.norules )
      txt2.printf(
                  "CREATE INDEX ts_head_lemma_idx1 ON ts_head_lemma(id_entry,id_group);\n"
                  "CREATE INDEX ts_head_word_idx1 ON ts_head_word(word,id_group);\n"
                  "CREATE INDEX ts_point_idx1 ON ts_point(id_parent);\n"
                  "CREATE INDEX ts_group2root_idx1 ON ts_group2root(id_group);\n"
                  "CREATE INDEX word_assoc_idx1 ON word_assoc(id_entry);\n\n"
                 );

     txt2.printf( "CREATE UNIQUE INDEX metaentry_idx1 ON metaentry(id_class,name);\n");
     txt2.printf("CREATE INDEX metaentry_item_idx1 ON metaentry_item(id_metaentry);\n");
     txt2.printf("CREATE UNIQUE INDEX metaentry_item_idx2 ON metaentry_item(id_metaentry,id_entry);\n");
    }
  }
 else if( sql_version.type==SQL_Production::MsSql )
  {
   if( !sql_version.noschema )
    {
     txt.printf(
                "create index tnotes_idx1 on tnotes(tn_te_id);\n"
                "create index sg_entry_idx2 on sg_entry(uname);\n"
                "create unique index sg_state_idx1 on sg_state(id,id_coord);\n"
                "create unique index sg_form_idx1 on sg_form(id_entry,iform);\n"
                "create index sg_form_idx2 on sg_form(id_entry);\n"
                "create unique index cplx_left_idx1 on cplx_left(cl_headword);\n"
                "create index sg_entry_coord_idx1 on sg_entry_coord(id_entry);\n"
                "create index sg_entry_coord_idx2 on sg_entry_coord(id_entry,icoord);\n"
                "create index sg_tlink_flag_idx1 on sg_tlink_flag(tlf_tl_id);\n"
                "create index aux_form_idx1 on aux_form(id_entry,iform);\n"
                "CREATE INDEX aux_word_idx1 ON aux_word(aux_type,src);\n"
                "create index aux_entry_data_idx1 on aux_entry_data(id_entry);\n"
                "create index abc_entry_idx2 on abc_entry(code);\n"
                "create index abc_form_idx2 on abc_form(code);\n"

                "create index misspelling_idx1 on misspelling(original_word,id_language);\n"
                "create index misspelling_idx2 on misspelling(original_word);\n"

                "create unique index endings_idx1 on endings(ending,id_language);\n"
                "create unique index wordform_frequency_idx1 on wordform_frequency(id_entry,iform);\n"

                "CREATE UNIQUE INDEX word_entry_set_idx1 ON word_entry_set(name);\n"
                "CREATE UNIQUE INDEX word_set_idx1 ON word_set(name);\n"
                "CREATE UNIQUE INDEX collocation_set_idx1 ON collocation_set(name);\n"
                "CREATE UNIQUE INDEX collocation_headword_idx1 ON collocation_headword(headword);\n"
                "CREATE INDEX collocation_set_item_idx1 ON collocation_set_item(headword,id_set);\n"
                "CREATE UNIQUE INDEX collocation_set_item_idx2 ON collocation_set_item(words,id_set);\n"

                "CREATE INDEX kb_fact_idx1 ON kb_fact(id_group);\n"
                "CREATE INDEX kb_argument_point_idx1 ON kb_argument_point(id_fact);\n"

                "CREATE UNIQUE INDEX wordform_set_idx1 ON wordform_set(name);\n"
                "CREATE INDEX wordform_set_item_idx1 ON wordform_set_item(id_set,word,id_entry);\n"
                "CREATE UNIQUE INDEX wordform_set_coords_idx1 ON wordform_set_coords(coords);\n"

                "\n"
               );

     txt.printf(
                "CREATE INDEX kb_fact_index_idx1 ON kb_fact_index1(id_group,word1,word2);\n"
                "CREATE INDEX kb_fact_index_idx2 ON kb_fact_index1(id_group,word1,word2,word3);\n"
                "CREATE INDEX kb_fact_index_idx3 ON kb_fact_index2(id_group,id_entry1,id_entry2);\n"
                "CREATE INDEX kb_fact_index_idx4 ON kb_fact_index2(id_group,id_entry1,id_entry2,id_entry3);\n"
                "CREATE INDEX generic_tree_scorer_idx1 ON generic_tree_scorer(id_group);\n"
                "CREATE INDEX ts_predicate_idx1 ON ts_predicate(id_point);\n"
               );


     if( !sql_version.IsDemo() )
      txt.printf(
                 "create index sg_tentry_idx5 on sg_tentry(te_text32);\n"
                 "\n"
                );

      txt.printf(
                 // ABC_STATE
                 "ALTER TABLE abc_state ADD CONSTRAINT pk_abc_state PRIMARY KEY (id_coord,id);\n"
                 "create unique index idx_abc_state1 on abc_state( id_coord, name );\n"
                 "alter table ABC_STATE with check add constraint fk_abc_state_1 foreign key(id_coord) references abc_coord(id);\n"
                 "alter table ABC_STATE check constraint fk_abc_state_1;\n"

                 // ABC_PAIR
                 "alter table ABC_PAIR with check add constraint fk_abc_pair_1 foreign key(id_pairs) references abc_pairs(id);\n"
                 "alter table ABC_PAIR check constraint fk_abc_pair_1;\n"
                 "alter table ABC_PAIR with check add constraint fk_abc_pair_2 foreign key(id_coord) references abc_coord(id);\n"
                 "alter table ABC_PAIR check constraint fk_abc_pair_2;\n"
                 "alter table ABC_PAIR with check add constraint fk_abc_pair_3 foreign key(id_coord,id_state) references abc_state(id_coord,id);\n"
                 "alter table ABC_PAIR check constraint fk_abc_pair_3;\n"

                 // ABC_CLASS_COORD
                 "alter table ABC_CLASS_COORD with check add constraint fk_abc_class_coord_1 foreign key(id_class) references abc_class(id);\n"
                 "alter table ABC_CLASS_COORD check constraint fk_abc_class_coord_1;\n"
                 "alter table ABC_CLASS_COORD with check add constraint fk_abc_class_coord_2 foreign key(id_coord) references abc_coord(id);\n"
                 "alter table ABC_CLASS_COORD check constraint fk_abc_class_coord_2;\n"
                 "ALTER TABLE ABC_CLASS_COORD ADD CONSTRAINT ck_abc_class_coord1 CHECK ( coord_type in (0,1,2) );\n"

                 // ABC_ENTRY
                 "create unique index idx_abc_entry on abc_entry( code, id_alphabet );\n"
                 "alter table ABC_ENTRY with check add constraint fk_abc_entry_1 foreign key(id_class) references abc_class(id);\n"
                 "alter table ABC_ENTRY check constraint fk_abc_entry_1;\n"
                 "alter table ABC_ENTRY with check add constraint fk_abc_entry_2 foreign key(id_alphabet) references abc_alphabet(id);\n"
                 "alter table ABC_ENTRY check constraint fk_abc_entry_2;\n"
                 "alter table ABC_ENTRY with check add constraint fk_abc_entry_3 foreign key(id_pairs) references abc_pairs(id);\n"
                 "alter table ABC_ENTRY check constraint fk_abc_entry_3;\n"

                 // ABC_FORM
                 "create index idx_abc_form1 on abc_form( code );\n"
                 "create unique index idx_abc_form2 on abc_form( code, id_entry );\n"
                 "alter table ABC_FORM with check add constraint fk_abc_form_1 foreign key(id_entry) references abc_entry(id);\n"
                 "alter table ABC_FORM check constraint fk_abc_form_1;\n"
                 "alter table ABC_FORM with check add constraint fk_abc_form_2 foreign key(id_pairs) references abc_pairs(id);\n"
                 "alter table ABC_FORM check constraint fk_abc_form_2;\n"
                );

     txt.printf( "CREATE UNIQUE NONCLUSTERED INDEX IDX_SG_COORD ON SG_COORD( NAME ASC );\n" );
     txt.printf( "CREATE UNIQUE NONCLUSTERED INDEX IDX_SG_LEXEM ON SG_LEXEM( NAME ASC );\n" );

     txt.printf( "CREATE UNIQUE NONCLUSTERED INDEX IDX_MULTILEXEM ON MULTILEXEM( TXT ASC );\n" );
     txt.printf( "CREATE INDEX IDX2_MULTILEXEM ON MULTILEXEM( HEADWORD ASC );\n" );

     txt.printf( "ALTER TABLE SG_CLASS WITH CHECK ADD CONSTRAINT FK_SG_CLASS_SG_LANGUAGE FOREIGN KEY(ID_LANG) REFERENCES SG_LANGUAGE(ID);\n" );
     txt.printf( "ALTER TABLE SG_CLASS CHECK CONSTRAINT FK_SG_CLASS_SG_LANGUAGE;\n" );
 
     txt.printf( "ALTER TABLE sg_state ADD CONSTRAINT pk_sg_state PRIMARY KEY (id_coord,id);\n" );
     txt.printf( "ALTER TABLE SG_STATE WITH CHECK ADD  CONSTRAINT FK_SG_STATE_SG_COORD FOREIGN KEY(ID_COORD) REFERENCES SG_COORD(ID);\n" );
     txt.printf( "ALTER TABLE SG_STATE CHECK CONSTRAINT FK_SG_STATE_SG_COORD;\n" );
 
     txt.printf( "alter table sg_class_coord add constraint pk_sg_class_coord primary key (id_class,id_coord);\n" );
     txt.printf( "ALTER TABLE SG_CLASS_COORD  WITH CHECK ADD  CONSTRAINT FK_SG_CLASS_COORD_SG_CLASS FOREIGN KEY(ID_CLASS) REFERENCES SG_CLASS(ID);\n" );
     txt.printf( "ALTER TABLE SG_CLASS_COORD CHECK CONSTRAINT FK_SG_CLASS_COORD_SG_CLASS;\n" );
     txt.printf( "ALTER TABLE SG_CLASS_COORD  WITH CHECK ADD  CONSTRAINT FK_SG_CLASS_COORD_SG_COORD FOREIGN KEY(ID_COORD) REFERENCES SG_COORD(ID);\n" );
     txt.printf( "ALTER TABLE SG_CLASS_COORD CHECK CONSTRAINT FK_SG_CLASS_COORD_SG_COORD;\n" );
 
     txt.printf( "CREATE NONCLUSTERED INDEX IDX_SG_ENTRY ON SG_ENTRY( NAME ASC );\n" );
     txt.printf( "CREATE NONCLUSTERED INDEX IDX_SG_ENTRY2 ON SG_ENTRY( UNAME ASC );\n" );
     txt.printf( "ALTER TABLE SG_ENTRY  WITH CHECK ADD  CONSTRAINT FK_SG_ENTRY_SG_CLASS FOREIGN KEY(ID_CLASS) REFERENCES SG_CLASS(ID);\n" );
     txt.printf( "ALTER TABLE SG_ENTRY CHECK CONSTRAINT FK_SG_ENTRY_SG_CLASS;\n" );
 
     txt.printf( "ALTER TABLE SG_ENTRY_COORD  WITH CHECK ADD  CONSTRAINT FK_SG_ENTRY_COORD_SG_COORD FOREIGN KEY(ICOORD) REFERENCES SG_COORD(ID);\n" );
     txt.printf( "ALTER TABLE SG_ENTRY_COORD CHECK CONSTRAINT FK_SG_ENTRY_COORD_SG_COORD;\n" );
     txt.printf( "ALTER TABLE SG_ENTRY_COORD  WITH CHECK ADD  CONSTRAINT FK_SG_ENTRY_COORD_SG_STATE FOREIGN KEY(ICOORD,ISTATE) REFERENCES SG_STATE(ID_COORD,ID);\n" );
     txt.printf( "ALTER TABLE SG_ENTRY_COORD CHECK CONSTRAINT FK_SG_ENTRY_COORD_SG_STATE;\n" );
     txt.printf( "ALTER TABLE SG_ENTRY_COORD  WITH CHECK ADD  CONSTRAINT FK_SG_ENTRY_COORD_SG_ENTRY FOREIGN KEY(ID_ENTRY) REFERENCES SG_ENTRY(ID);\n" );
     txt.printf( "ALTER TABLE SG_ENTRY_COORD CHECK CONSTRAINT FK_SG_ENTRY_COORD_SG_ENTRY;\n" );
     txt.printf( "ALTER TABLE sg_entry_coord ADD CONSTRAINT pk_sg_entry_coord PRIMARY KEY (id_entry,icoord,istate);\n" );
 
     txt.printf( "ALTER TABLE sg_form ADD CONSTRAINT pk_sg_form PRIMARY KEY(id_entry,iform);\n" );
     txt.printf( "ALTER TABLE SG_FORM  WITH CHECK ADD  CONSTRAINT FK_SG_FORM_SG_ENTRY FOREIGN KEY(ID_ENTRY) REFERENCES SG_ENTRY(ID);\n" );
     txt.printf( "ALTER TABLE SG_FORM CHECK CONSTRAINT FK_SG_FORM_SG_ENTRY;\n" );
     txt.printf( "ALTER TABLE SG_FORM  WITH CHECK ADD  CONSTRAINT FK_SG_FORM_SG_LEXEM FOREIGN KEY(ID_LEXEM) REFERENCES SG_LEXEM(ID);\n" );
     txt.printf( "ALTER TABLE SG_FORM CHECK CONSTRAINT FK_SG_FORM_SG_LEXEM;\n" );
     txt.printf( "CREATE NONCLUSTERED INDEX IDX_SG_FORM ON SG_FORM( NAME ASC );\n" );

     txt.printf( "ALTER TABLE sg_tag_value ADD CONSTRAINT pk_sg_tag_value PRIMARY KEY (id_tag,ivalue);\n" );
     txt.printf( "ALTER TABLE SG_TAG_VALUE  WITH CHECK ADD  CONSTRAINT FK_SG_TAG_VALUE_SG_TAG FOREIGN KEY(ID_TAG) REFERENCES SG_TAG(ID);\n" );
     txt.printf( "ALTER TABLE SG_TAG_VALUE CHECK CONSTRAINT FK_SG_TAG_VALUE_SG_TAG;\n" );
 
     txt.printf( "ALTER TABLE SG_TENTRY  WITH CHECK ADD  CONSTRAINT FK_SG_TENTRY_SG_CLASS FOREIGN KEY(TE_ID_CLASS) REFERENCES SG_CLASS(ID);\n" );
     txt.printf( "ALTER TABLE SG_TENTRY CHECK CONSTRAINT FK_SG_TENTRY_SG_CLASS;\n" );
     txt.printf( "ALTER TABLE SG_TENTRY  WITH CHECK ADD  CONSTRAINT FK_SG_TENTRY_SG_LANGUAGE FOREIGN KEY(TE_ID_LANGUAGE) REFERENCES SG_LANGUAGE(ID);\n" );
     txt.printf( "ALTER TABLE SG_TENTRY CHECK CONSTRAINT FK_SG_TENTRY_SG_LANGUAGE;\n" );

     txt.printf( "CREATE NONCLUSTERED INDEX IDX_SG_LINK_ENTRY1 ON SG_LINK( ID_ENTRY1 ASC );\n" );
     txt.printf( "CREATE NONCLUSTERED INDEX IDX_SG_LINK_ENTRY2 ON SG_LINK( ID_ENTRY2 ASC );\n" );
     txt.printf( "ALTER TABLE SG_LINK  WITH CHECK ADD  CONSTRAINT FK_SG_LINK_SG_COORD FOREIGN KEY(ICOORD) REFERENCES SG_COORD(ID);\n" );
     txt.printf( "ALTER TABLE SG_LINK CHECK CONSTRAINT FK_SG_LINK_SG_COORD;\n" );
     txt.printf( "ALTER TABLE SG_LINK  WITH CHECK ADD  CONSTRAINT FK_SG_LINK_SG_STATE FOREIGN KEY(ICOORD,ISTATE) REFERENCES SG_STATE(ID_COORD,ID);\n" );
     txt.printf( "ALTER TABLE SG_LINK CHECK CONSTRAINT FK_SG_LINK_SG_STATE;\n" );

     txt.printf( "ALTER TABLE SG_LINK  WITH CHECK ADD  CONSTRAINT FK_SG_LINK_SG_ENTRY FOREIGN KEY(ID_ENTRY1) REFERENCES SG_ENTRY(ID);\n" );
     txt.printf( "ALTER TABLE SG_LINK CHECK CONSTRAINT FK_SG_LINK_SG_ENTRY;\n" );
     txt.printf( "ALTER TABLE SG_LINK  WITH CHECK ADD  CONSTRAINT FK_SG_LINK_SG_ENTRY1 FOREIGN KEY(ID_ENTRY2) REFERENCES SG_ENTRY(ID);\n" );
     txt.printf( "ALTER TABLE SG_LINK CHECK CONSTRAINT FK_SG_LINK_SG_ENTRY1;\n" );

     txt.printf( "ALTER TABLE SG_LINK_TAG  WITH CHECK ADD  CONSTRAINT FK_SG_LINK_TAG_SG_LINK FOREIGN KEY(ID_LINK) REFERENCES SG_LINK(ID);\n" );
     txt.printf( "ALTER TABLE SG_LINK_TAG CHECK CONSTRAINT FK_SG_LINK_TAG_SG_LINK;\n" );
     txt.printf( "ALTER TABLE SG_LINK_TAG  WITH CHECK ADD  CONSTRAINT FK_SG_LINK_TAG_SG_TAG FOREIGN KEY(ID_TAG) REFERENCES SG_TAG(ID);\n" );
     txt.printf( "ALTER TABLE SG_LINK_TAG CHECK CONSTRAINT FK_SG_LINK_TAG_SG_TAG;\n" );
     txt.printf( "ALTER TABLE SG_LINK_TAG  WITH CHECK ADD  CONSTRAINT FK_SG_LINK_TAG_SG_TAG_VALUE FOREIGN KEY(ID_TAG,IVALUE) REFERENCES SG_TAG_VALUE(ID_TAG,IVALUE);\n" );
     txt.printf( "ALTER TABLE SG_LINK_TAG CHECK CONSTRAINT FK_SG_LINK_TAG_SG_TAG_VALUE;\n" );
 
     txt.printf( "CREATE NONCLUSTERED INDEX IDX_SG_TLINK_ENTRY1 ON SG_TLINK( TL_TE_ID1 ASC );\n" );
     txt.printf( "CREATE NONCLUSTERED INDEX IDX_SG_TLINK_ENTRY2 ON SG_TLINK( TL_TE_ID1 ASC );\n" );

     txt.printf( "ALTER TABLE SG_TLINK  WITH CHECK ADD  CONSTRAINT FK_SG_TLINK_SG_COORD FOREIGN KEY(TL_ICOORD) REFERENCES SG_COORD(ID);\n" );
     txt.printf( "ALTER TABLE SG_TLINK CHECK CONSTRAINT FK_SG_TLINK_SG_COORD;\n" );
     txt.printf( "ALTER TABLE SG_TLINK  WITH CHECK ADD  CONSTRAINT FK_SG_TLINK_SG_STATE FOREIGN KEY(TL_ICOORD,TL_ISTATE) REFERENCES SG_STATE(ID_COORD,ID);\n" );
     txt.printf( "ALTER TABLE SG_TLINK CHECK CONSTRAINT FK_SG_TLINK_SG_COORD;\n" );
     txt.printf( "ALTER TABLE SG_TLINK  WITH CHECK ADD  CONSTRAINT FK_SG_TLINK_SG_TENTRY FOREIGN KEY(TL_TE_ID1) REFERENCES SG_TENTRY(TE_ID);\n" );
     txt.printf( "ALTER TABLE SG_TLINK CHECK CONSTRAINT FK_SG_TLINK_SG_TENTRY;\n" );
     txt.printf( "ALTER TABLE SG_TLINK  WITH CHECK ADD  CONSTRAINT FK_SG_TLINK_SG_TENTRY1 FOREIGN KEY(TL_TE_ID2) REFERENCES SG_TENTRY(TE_ID);\n" );
     txt.printf( "ALTER TABLE SG_TLINK CHECK CONSTRAINT FK_SG_TLINK_SG_TENTRY1;\n" );
 
     txt.printf( "ALTER TABLE SG_TLINK_TAG  WITH CHECK ADD  CONSTRAINT FK_SG_TLINK_TAG_SG_TAG FOREIGN KEY(TLT_ID_TAG) REFERENCES SG_TAG(ID);\n" );
     txt.printf( "ALTER TABLE SG_TLINK_TAG CHECK CONSTRAINT FK_SG_TLINK_TAG_SG_TAG;\n" );
     txt.printf( "ALTER TABLE SG_TLINK_TAG  WITH CHECK ADD  CONSTRAINT FK_SG_TLINK_TAG_SG_TAG_VALUE FOREIGN KEY(TLT_ID_TAG,TLT_IVALUE) REFERENCES SG_TAG_VALUE(ID_TAG,IVALUE);\n" );
     txt.printf( "ALTER TABLE SG_TLINK_TAG CHECK CONSTRAINT FK_SG_TLINK_TAG_SG_TAG_VALUE;\n" );
     txt.printf( "ALTER TABLE SG_TLINK_TAG  WITH CHECK ADD  CONSTRAINT FK_SG_TLINK_TAG_SG_TLINK FOREIGN KEY(TLT_TL_ID) REFERENCES SG_TLINK(TL_ID);\n" );
     txt.printf( "ALTER TABLE SG_TLINK_TAG CHECK CONSTRAINT FK_SG_TLINK_TAG_SG_TLINK;\n" );

     txt.printf( "ALTER TABLE tnotes WITH CHECK ADD CONSTRAINT FK_tnotes_SG_TENTRY FOREIGN KEY(tn_te_id) REFERENCES SG_TENTRY(TE_ID);\n" );
     txt.printf( "ALTER TABLE tnotes CHECK CONSTRAINT FK_tnotes_SG_TENTRY;\n" );

     txt.printf( "ALTER TABLE sg_tlink_flag WITH CHECK ADD CONSTRAINT FK_tlink_flag1 FOREIGN KEY(tlf_tl_id) REFERENCES SG_TLINK(TL_ID);\n" );

     if( !sql_version.noformcoords )
      {
       txt.printf( "ALTER TABLE SG_FORM_COORD  WITH CHECK ADD  CONSTRAINT FK_SG_FORM_COORD_SG_COORD FOREIGN KEY(ICOORD) REFERENCES SG_COORD(ID);\n" );
       txt.printf( "ALTER TABLE SG_FORM_COORD CHECK CONSTRAINT FK_SG_FORM_COORD_SG_COORD;\n" );
       txt.printf( "ALTER TABLE SG_FORM_COORD  WITH CHECK ADD  CONSTRAINT FK_SG_FORM_COORD_SG_ENTRY FOREIGN KEY(ID_ENTRY) REFERENCES SG_ENTRY(ID);\n" );
       txt.printf( "ALTER TABLE SG_FORM_COORD CHECK CONSTRAINT FK_SG_FORM_COORD_SG_ENTRY;\n" );
       txt.printf( "ALTER TABLE SG_FORM_COORD  WITH CHECK ADD  CONSTRAINT FK_SG_FORM_COORD_SG_STATE FOREIGN KEY(ICOORD,ISTATE) REFERENCES SG_STATE(ID_COORD,ID);\n" );
       txt.printf( "ALTER TABLE SG_FORM_COORD CHECK CONSTRAINT FK_SG_FORM_COORD_SG_STATE;\n" );
       txt.printf( "ALTER TABLE sg_form_coord ADD CONSTRAINT pk_sg_form_coord PRIMARY KEY (id_entry,iform,icoord,istate);\n" );
      }


     if( !sql_version.IsDemo() )
      {
       // AUX_FORM
       txt.printf( "ALTER TABLE aux_form WITH CHECK ADD CONSTRAINT FK_aux_form_1 FOREIGN KEY(data_type) REFERENCES aux_form_types(ID);\n" );
       txt.printf( "ALTER TABLE aux_form CHECK CONSTRAINT FK_aux_form_1;\n" );
       txt.printf( "ALTER TABLE aux_form WITH CHECK ADD CONSTRAINT FK_aux_form_2 FOREIGN KEY(id_entry) REFERENCES sg_entry(ID);\n" );
       txt.printf( "ALTER TABLE aux_form CHECK CONSTRAINT FK_aux_form_2;\n" );
       txt.printf( "ALTER TABLE aux_form WITH CHECK ADD CONSTRAINT FK_aux_form_3 FOREIGN KEY(id_entry,iform) REFERENCES sg_form(ID_ENTRY,IFORM);\n" );
       txt.printf( "ALTER TABLE aux_form CHECK CONSTRAINT FK_aux_form_3;\n" );
    
       // AUX_ENTRY_DATA
       txt.printf( "ALTER TABLE aux_entry_data WITH CHECK ADD CONSTRAINT fk_aux_entry_data_1 FOREIGN KEY(data_type) REFERENCES aux_form_types(ID);\n" );
       txt.printf( "ALTER TABLE aux_entry_data CHECK CONSTRAINT fk_aux_entry_data_1;\n" );
       txt.printf( "ALTER TABLE aux_entry_data WITH CHECK ADD CONSTRAINT fk_aux_entry_data_2 FOREIGN KEY(id_entry) REFERENCES sg_entry(ID);\n" );
       txt.printf( "ALTER TABLE aux_entry_data CHECK CONSTRAINT fk_aux_entry_data_2;\n" );
      }

     txt.printf(
                // LANG_ALPHABET
                "alter table lang_alphabet with check add constraint fk_lang_alphabet_1 foreign key(id_language) references sg_language(id);\n"
                "alter table lang_alphabet check constraint fk_lang_alphabet_1;\n"
                "alter table lang_alphabet with check add constraint fk_lang_alphabet_2 foreign key(id_alphabet) references abc_alphabet(id);\n"
                "alter table lang_alphabet check constraint fk_lang_alphabet_2;\n"
               );    

     txt.printf(
                // LANG_LINK
                "alter table lang_link with check add constraint fk_lang_link_1 foreign key(id_language) references sg_language(id);\n"
                "alter table lang_link check constraint fk_lang_link_1;\n"
                "alter table lang_link with check add constraint fk_lang_link_2 foreign key(id_language2) references sg_language(id);\n"
                "alter table lang_link check constraint fk_lang_link_2;\n"
               );    

     txt.printf(
                // LANG_PARAM
                //"create unique index idx_lang_param on lang_param( id_language, param_name, ordering );\n"
                "alter table lang_param with check add constraint fk_lang_param_1 foreign key(id_language) references sg_language(id);\n"
                "alter table lang_param check constraint fk_lang_param_1;\n"
               );    


     if( !sql_version.IsDemo() )
      {
       txt.printf(
                  // PREDEF_ENTRIES
                  "alter table predef_entries with check add constraint fk_predef_entries_1 foreign key(id_entry) references sg_entry(id);\n"
                  "alter table predef_entries check constraint fk_predef_entries_1;\n"
                 );
      }

     txt.printf(
                // SG_ENTRY
                "ALTER TABLE sg_entry ALTER COLUMN exportable int NOT NULL;\n"
                "ALTER TABLE sg_entry ADD CONSTRAINT ck_sg_entry1 CHECK ( exportable in (0,1) );\n"
               ); 

     txt.printf(
                // SG_FORM
                "alter table sg_form with check add constraint fk_sg_form_1 foreign key(id_dims) references coord_pairs(id);\n"
                "alter table sg_form check constraint fk_sg_form_1;\n"
               );

     txt.printf(
                // SG_LINK
                "alter table sg_link with check add constraint fk_sg_link_1 foreign key(tags) references tag_set(id);\n"
                "alter table sg_link check constraint fk_sg_link_1;\n"
               );

     txt.printf(
                // SG_STATE
                "create unique index idx_sg_state_1 on sg_state( id_coord, name );\n"
                "alter table sg_state with check add constraint fk_sg_state_1 foreign key(id_coord,id_parent) references sg_state(id_coord,id);\n"
                "alter table sg_state check constraint fk_sg_state_1;\n"
               );

     txt.printf(
                // SG_TAG_VALUE
                "create unique index idx_sg_tag_value_1 on sg_tag_value( id_tag, name );\n"
               );

     txt.printf(
                // SG_TLINK
                "alter table sg_tlink with check add constraint fk_sg_tlink_1 foreign key(tl_tags) references tag_set(id);\n"
                "alter table sg_tlink check constraint fk_sg_tlink_1;\n"
               );

     txt.printf(
                // SG_CLASS_COORD
                "ALTER TABLE sg_class_coord ADD CONSTRAINT ck_sg_class_coord_1 CHECK ( coord_type in (0,1,2) );\n"
               );

     txt.printf(
                "CREATE INDEX slb_condition_point_idx1 ON slb_condition_point(id_rule);\n"
                "CREATE INDEX slb_result_point_idx1 ON slb_result_point(id_rule);\n"
               );

     if( !sql_version.norules )
      txt.printf(
                 "CREATE INDEX ts_head_lemma_idx1 ON ts_head_lemma(id_entry,id_group);\n"
                 "CREATE INDEX ts_head_word_idx1 ON ts_head_word(word,id_group);\n"
                 "CREATE INDEX ts_point_idx1 ON ts_point(id_parent);\n"
                 "CREATE INDEX ts_group2root_idx1 ON ts_group2root(id_group);\n"
                 "CREATE INDEX word_assoc_idx1 ON word_assoc(id_entry);\n\n"
                );

     txt.printf( "CREATE UNIQUE INDEX metaentry_idx1 ON metaentry(id_class,name);\n");
     txt.printf("CREATE INDEX metaentry_item_idx1 ON metaentry_item(id_metaentry);\n");
     txt.printf("CREATE UNIQUE INDEX metaentry_item_idx2 ON metaentry_item(id_metaentry,id_entry);\n");
     txt.printf( "CREATE UNIQUE INDEX omonym_idx1 ON omonym(entry_name,id_class);\n" );
    }

   txt.printf( "\n%s\n", sql_version.CommitTx().c_str() );

   txt.printf(
              "EXIT\n"
              "\n" 
             ); 
  }
 else if( sql_version.type==SQL_Production::SQLite )
  {
   if( !sql_version.noschema )
    {
     txt.printf(
                "create index sg_tlink_flag_idx1 on sg_tlink_flag(tlf_tl_id);\n"
                "create index tnotes_idx1 on tnotes(tn_te_id);\n"
                "create index tnotes_idx2 on tnotes(tn_data);\n"
                "create index sg_entry_idx2 on sg_entry(uname);\n"
                "create unique index sg_lexem_2 on sg_lexem(name);\n"
                "create index sg_entry_coord_idx1 on sg_entry_coord(id_entry);\n" 
                "create index sg_entry_coord_idx2 on sg_entry_coord(id_entry,icoord);\n" 
                "create index idx_sg_class_coord on sg_class_coord(id_class);\n" 
                "create unique index cplx_left_idx1 on cplx_left(cl_id);\n"
                "create unique index cplx_left_idx2 on cplx_left(cl_headword);\n"
                "create index sg_tentry_idx5 on sg_tentry(te_text32);\n"
                "create index sg_form_idx4 on sg_form(id_entry);\n"
                "create index sg_form_idx5 on sg_form(id_lexem);\n"
                "create index aux_form_idx1 on aux_form(id_entry,iform);\n"
                "CREATE INDEX aux_word_idx1 ON aux_word(aux_type,src);\n"
                "create index aux_entry_data_idx1 on aux_entry_data(id_entry);\n"
                "create index abc_form_idx1 on abc_form(code);\n"
                "create unique index endings_idx1 on endings(ending,id_language);\n"
                "create unique index wordform_frequency_idx1 on wordform_frequency(id_entry,iform);\n"
                "create index misspelling_idx1 on misspelling(original_word,id_language);\n"
                "create index misspelling_idx2 on misspelling(original_word);\n"

                "CREATE UNIQUE INDEX word_entry_set_idx1 ON word_entry_set(name);\n"
                "CREATE UNIQUE INDEX word_set_idx1 ON word_set(name);\n"
                "CREATE UNIQUE INDEX collocation_set_idx1 ON collocation_set(name);\n"
                "CREATE UNIQUE INDEX collocation_headword_idx1 ON collocation_headword(headword);\n"
                "CREATE INDEX collocation_set_item_idx1 ON collocation_set_item(headword,id_set);\n"
                "CREATE UNIQUE INDEX collocation_set_item_idx2 ON collocation_set_item(words,id_set);\n"
               );

     txt.printf(
                "CREATE INDEX kb_fact_index_idx1 ON kb_fact_index1(id_group,word1,word2);\n"
                "CREATE INDEX kb_fact_index_idx2 ON kb_fact_index1(id_group,word1,word2,word3);\n"
                "CREATE INDEX kb_fact_index_idx3 ON kb_fact_index2(id_group,id_entry1,id_entry2);\n"
                "CREATE INDEX kb_fact_index_idx4 ON kb_fact_index2(id_group,id_entry1,id_entry2,id_entry3);\n"
                "CREATE INDEX generic_tree_scorer_idx1 ON generic_tree_scorer(id_group);\n"
                "CREATE INDEX ts_predicate_idx1 ON ts_predicate(id_point);\n"
               );


     if( !sql_version.norules )
      {
       txt.printf(
                  "CREATE INDEX kb_fact_idx1 ON kb_fact(id_group);\n"
                  "CREATE INDEX kb_argument_point_idx1 ON kb_argument_point(id_fact);\n"
    
                  "CREATE UNIQUE INDEX wordform_set_idx1 ON wordform_set(name);\n"
                  "CREATE INDEX wordform_set_item_idx1 ON wordform_set_item(id_set,word,id_entry);\n"
                  "CREATE UNIQUE INDEX wordform_set_coords_idx1 ON wordform_set_coords(coords);\n"
                  "CREATE UNIQUE INDEX omonym_idx1 ON omonym(entry_name,id_class);\n"
                 );
      }

     txt.printf(
                "CREATE INDEX slb_condition_point_idx1 ON slb_condition_point(id_rule);\n"
                "CREATE INDEX slb_result_point_idx1 ON slb_result_point(id_rule);\n"
               );

     if( !sql_version.norules )
      { 
       txt.printf(
                  "CREATE INDEX ts_head_lemma_idx1 ON ts_head_lemma(id_entry,id_group);\n"
                  "CREATE INDEX ts_head_word_idx1 ON ts_head_word(word,id_group);\n"
                  "CREATE INDEX ts_point_idx1 ON ts_point(id_parent);\n"
                  "CREATE INDEX ts_group2root_idx1 ON ts_group2root(id_group);\n"
                  "CREATE INDEX word_assoc_idx1 ON word_assoc(id_entry);\n\n"
                 );

        txt.printf("CREATE INDEX SynPatternTree_idx1 ON SynPatternTree(id_tree);\n");
       }

     txt.printf( "CREATE UNIQUE INDEX metaentry_idx1 ON metaentry(id_class,name);\n");
     txt.printf("CREATE INDEX metaentry_item_idx1 ON metaentry_item(id_metaentry);\n");
     txt.printf("CREATE UNIQUE INDEX metaentry_item_idx2 ON metaentry_item(id_metaentry,id_entry);\n");

     if( !sql_version.noformcoords )
      {
       txt.printf(
                  "create index idx_sg_form_coord on sg_form_coord(id_entry,iform);\n" 
                 );
      }
    }
 
   txt.printf( "\n%s\n", sql_version.CommitTx().c_str() );

   txt.printf(
              ".exit\n"  
              "\n" 
             ); 
  }


 return;
}



void Dictionary::SaveRules_SQL(
                               OFormatter &txt,
                               OFormatter &txt2,
                               const SQL_Production &sql_version
                              )
{
 txt.printf(
            "%s This SQL script is generated [%us] by DECOMPILER ver. %s for '%s' RDBMS\n"
            "%s (c) by Elijah Koziev\n"
            "%s More info at http://www.solarix.ru/for_developers/docs/sql_dictionary.shtml\n"
            , sql_version.Get_Comment().c_str()
            , timestamp().c_str()
            , sol_get_version().c_str()
            , sql_version.Get_Version().c_str()
            , sql_version.Get_Comment().c_str()
            , sql_version.Get_Comment().c_str()
           );

 if( sql_version.norules )
  return;

 if( sql_version.type==SQL_Production::MySql )
  {
   txt.printf( "set session sql_mode='NO_AUTO_VALUE_ON_ZERO';\n" );     
  }


 if( sql_version.type==SQL_Production::SQLite )
  {
   lem::Ptr<LS_ResultSet> rs_fname( GetSynGram().GetStorage().ListSourceFilenames() );
   while( rs_fname->Fetch() )
    {
     int id = rs_fname->GetInt(0);
     lem::UFString filepath = rs_fname->GetUFString(1);
     txt.printf( "INSERT INTO src_filename( id, filepath, filepath0 ) VALUES ( %d, '%us', '%us' );\n"
      , id, sql_version.SqlStr(lem::to_upper(filepath)).c_str(), sql_version.SqlStr(filepath).c_str() );
    }
   rs_fname.Delete();

   txt.eol();
   
   lem::Ptr<LS_ResultSet> rs_loc( GetSynGram().GetStorage().ListSourceLocations() );
   while( rs_loc->Fetch() )
    {
     int id = rs_loc->GetInt(0);
     int id_filename = rs_loc->GetInt(1);
     int line_no = rs_loc->GetInt(2);
     int column_no = rs_loc->GetInt(3);

     txt.printf( "INSERT INTO src_location( id, id_filename, line_no, column_no ) VALUES ( %d, %d, %d, %d );\n",
      id, id_filename, line_no, column_no );
    }
   rs_loc.Delete();
  }


 for( int i=0; i<SOL_N_AUTOMATA; i++ )
  if( auto_list[i] )
   auto_list[i]->SaveRules_SQL(txt,txt2,sql_version);


 txt.printf( "\n%s\n", sql_version.BeginTx().c_str() );

 if( sql_version.type==SQL_Production::Oracle )
  {
   if( !sql_version.noschema )
    {
     txt2.printf(
                "create index abc_operation_item_idx1 on abc_operation_item(id_operation);\n"
                "\n"
               );
    }

   txt.printf(
              "EXIT\n"  
              "\n" 
             ); 

   txt2.printf(
               "COMMIT;\n"
               "EXIT\n"  
               "\n" 
              );
  }
 else if( sql_version.type==SQL_Production::FireBird )
  {
   if( !sql_version.noschema )
    {
     txt.printf(
                "alter table abc_operation add constraint pk_abc_operation primary key(id);\n"
                "alter table abc_operation_item add constraint pk_abc_operation_item primary key(id);\n"

                "COMMIT;\n"
                "\n"
               );
    }
  }
 else if( sql_version.type==SQL_Production::MySql )
  {
   if( !sql_version.noschema )
    {
     txt.printf(
                "ALTER TABLE abc_operation_item ADD INDEX abc_operation_item_idx1(id_operation);\n"
                "\n"
               );
    }
  }
 else if( sql_version.type==SQL_Production::MsSql )
  {
   if( !sql_version.noschema )
    {
     txt.printf(
                "create index abc_operation_item_idx1 on abc_operation_item(id_operation);\n"
                "\n"
               );
    }

   txt.printf( "\n%s\n", sql_version.CommitTx().c_str() );

   txt.printf(
              "EXIT\n"
              "\n" 
             ); 
  }
 else if( sql_version.type==SQL_Production::SQLite )
  {
   if( !sql_version.noschema )
    {
     txt.printf(
                "create index abc_operation_item_idx1 on abc_operation_item(id_operation);\n"
               );
    }
 
   txt.printf( "\n%s\n", sql_version.CommitTx().c_str() );

   txt.printf(
              ".exit\n"
              "\n" 
             );
  }

 return;
}

#endif
