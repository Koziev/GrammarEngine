// Persistent Dictionary Library http://www.solarix.ru/for_developers/api/dictionary-orm.shtml

using System;
using System.Text;
using System.Data;
using System.Data.Common;
using System.Data.SqlClient;

namespace Solarix
{
 /// <summary>Слой доступа к словарю в MS SQL http://www.solarix.ru/orm/ru/dal.shtml#mssql</summary>
 /// <remarks>Подробнее о SQL-словаре http://www.solarix.ru/for_developers/docs/sql_dictionary.shtml</remarks>
 public class MSSQL_DataAccessLayer : IDataAccessLayer
 {
  private System.Data.SqlClient.SqlConnection cnx;

  public MSSQL_DataAccessLayer( System.Data.SqlClient.SqlConnection _cnx )
  {
   cnx = _cnx;
  } 

  public override bool SupportMultipleReaders() { return true; }

  public override void BeginTx()
  {
   if( tx==null )
    tx = cnx.BeginTransaction();
   else
    throw new System.ApplicationException( "Transaction is already started" );

   return;
  }

  public override string Nvl( string field_name, string null_value, bool quoted )
  {
   StringBuilder b = new StringBuilder();

   if( quoted )
    b.AppendFormat( "Coalesce({0},'{1}')", field_name, null_value );
   else
    b.AppendFormat( "Coalesce({0},{1})", field_name, null_value );

   return b.ToString();
  }


  private int LastInsertId()
  {
   return int.Parse(ReadItem("SELECT @@identity").ToString());
  }

  public override IDbCommand BuildCommand( string sql )
  {
   return new SqlCommand( sql, cnx, (SqlTransaction)tx );
  }

  public override IDataReader GetReader( string sql )
  {
   DbCommand cmd = new SqlCommand( sql, cnx, (SqlTransaction)tx );
   return cmd.ExecuteReader();
  }


  public override object ReadItem( string sql )
  {
   DbCommand cmd = new SqlCommand( sql, cnx, (SqlTransaction)tx );
   object obj = cmd.ExecuteScalar();
   cmd.Dispose();
   return obj;
  }


  public override System.Collections.ArrayList ReadItems( string sql )
  {
   DbCommand cmd = new SqlCommand( sql, cnx, (SqlTransaction)tx );
   DbDataReader rdr = cmd.ExecuteReader();
   rdr.Read();

   System.Collections.ArrayList res = new System.Collections.ArrayList();
 
   if( rdr.HasRows )
    {
     for( int i=0; i<rdr.FieldCount; ++i )
      {
       res.Add( rdr[i] );
      }
    }

   rdr.Close();
   
   return res;
  }

  public override string CaseInsensitivlyEquals( string field_name, string str_value )
  {
   StringBuilder b = new StringBuilder();
   b.AppendFormat( "Lower({0})='{1}'", field_name, str_value.ToLower() );
   return b.ToString();
  }

  public override string MatchesByPrefix( string field_name, string prefix )
  {
   StringBuilder b = new StringBuilder();
   b.AppendFormat( "{0} like '{1}%'", field_name, prefix.ToLower() );
   return b.ToString();
  }

  public override void Execute( string sql )
  {
   DbCommand cmd = new SqlCommand( sql, cnx, (SqlTransaction)tx );
   int rc = cmd.ExecuteNonQuery();
   cmd.Dispose();
   return;
  }

  public override void Store( Solarix.LinkTags x, Solarix.LinkTagAndValue y )
  {
   bool commit = !InTransaction();
   if( !InTransaction() )
    { 
     BeginTx();
    }

   StringBuilder b = new StringBuilder();

   if( x.ForWords() )
    {
     b.Length=0;
     b.AppendFormat( "INSERT INTO SG_LINK_TAG( id_link, id_tag, ivalue )" );
     b.AppendFormat( " VALUES ( {0}, {1}, {2} )", x.id, y.id_tag, y.id_value );

     DbCommand cmd3 = new SqlCommand( b.ToString(), cnx, (SqlTransaction)tx );
     cmd3.ExecuteNonQuery();
     cmd3.Dispose();

     y.id = LastInsertId();
    }
   else if( x.ForPhrases() )
    {
     b.Length=0;
     b.AppendFormat( "INSERT INTO SG_TLINK_TAG( tlt_tl_id, tlt_id_tag, tlt_ivalue )" );
     b.AppendFormat( " VALUES ( {0}, {1}, {2} )", x.id, y.id_tag, y.id_value );

     DbCommand cmd3 = new SqlCommand( b.ToString(), cnx, (SqlTransaction)tx );
     cmd3.ExecuteNonQuery();
     cmd3.Dispose();

     y.id=LastInsertId();
    } 

   if( commit )
    CommitTx();

   return;
  }


  public override void Store( Solarix.WordLink x )
  {
   bool commit = !InTransaction();
   if( !InTransaction() )
    { 
     BeginTx();
    }

   if( x.id==-1 )
    {
     StringBuilder b = new StringBuilder();

     foreach( LinkTagAndValue y in x.tags.list )
      {
       if( b.Length>0 ) b.Append( ' ' );
       b.AppendFormat( "{0} {1}", y.id_tag, y.id_value );
      }

     int id_tags=RegisterTagSet(b.ToString());
     b.Length=0;

     b.AppendFormat( "INSERT INTO sg_link( id_entry1, id_entry2, icoord, istate, tags ) VALUES ( {0}, {1}, 0, {2}, {3} )",
      x.left.id, x.right.id, x.type, id_tags );

     DbCommand cmd2 = new SqlCommand( b.ToString(), cnx, (SqlTransaction)tx );
     cmd2.ExecuteNonQuery();
     cmd2.Dispose();

     x.id = LastInsertId();

     // Если заданы теги, то их тоже сразу сохраним.
     if( x.tags.list.Count>0 )
      {
       foreach( LinkTagAndValue y in x.tags.list )
        {
         b.Length=0;
         b.AppendFormat( "INSERT INTO SG_LINK_TAG( id_link, id_tag, ivalue )" );
         b.AppendFormat( " VALUES ( {0}, {1}, {2} )", x.id, y.id_tag, y.id_value );

         DbCommand cmd4 = new SqlCommand( b.ToString(), cnx, (SqlTransaction)tx );
         cmd4.ExecuteNonQuery();
         cmd4.Dispose();

         y.id=LastInsertId(); 
        }
      } 
    }
   else
    {
     StringBuilder b = new StringBuilder();
     b.AppendFormat( "UPDATE sg_link SET id_entry1={0}, id_entry2={1}, istate={2} WHERE id={3}",
      x.left.id, x.right.id, x.type, x.id );

     DbCommand cmd3 = new SqlCommand( b.ToString(), cnx, (SqlTransaction)tx );
     cmd3.ExecuteNonQuery();
     cmd3.Dispose();
    }

   if( commit )
    CommitTx();

   return;
  }


  public override void Store( Solarix.PhraseLink x )
  {
   bool commit = !InTransaction();
   if( !InTransaction() )
    { 
     BeginTx();
    }

   if( x.id==-1 )
    {
     StringBuilder b = new StringBuilder();
     foreach( LinkTagAndValue y in x.tags.list )
      {
       if( b.Length>0 ) b.Append( ' ' );
       b.AppendFormat( "{0} {1}", y.id_tag, y.id_value );
      }

     int id_tags=RegisterTagSet(b.ToString());
     b.Length=0;

     b.AppendFormat( "INSERT INTO sg_tlink( tl_te_id1, tl_te_id2, tl_icoord, tl_istate, tl_tags ) VALUES ( {0}, {1}, 0, {2}, {3} )",
      x.left.id, x.right.id, x.type, id_tags );

     DbCommand cmd2 = new SqlCommand( b.ToString(), cnx, (SqlTransaction)tx );
     cmd2.ExecuteNonQuery();
     cmd2.Dispose();

     x.id = LastInsertId();

     // Если заданы теги, то их тоже сразу сохраним.
     if( x.tags.list.Count>0 )
      {
       foreach( LinkTagAndValue y in x.tags.list )
        {
         b.Length=0;
         b.AppendFormat( "INSERT INTO SG_TLINK_TAG( tlt_tl_id, tlt_id_tag, tlt_ivalue )" );
         b.AppendFormat( " VALUES ( {0}, {1}, {2} )", x.id, y.id_tag, y.id_value );
          
         DbCommand cmd3 = new SqlCommand( b.ToString(), cnx, (SqlTransaction)tx );
         cmd3.ExecuteNonQuery();
         cmd3.Dispose();

         y.id=LastInsertId(); 
        }
      }
    }
   else
    {
     StringBuilder b = new StringBuilder();
     b.AppendFormat( "UPDATE sg_tlink SET tl_te_id1={0}, tl_te_id2={1}, tl_istate={2} WHERE id={3}",
      x.left.id, x.right.id, x.type, x.id );

     DbCommand cmd2 = new SqlCommand( b.ToString(), cnx, (SqlTransaction)tx );
     cmd2.ExecuteNonQuery();
     cmd2.Dispose();
    }

   if( commit )
    CommitTx();

   return;
  }


  public override void Store( Solarix.Phrase x )
  {
   bool commit = !InTransaction();
   if( !InTransaction() )
    { 
     BeginTx();
    }

   if( x.id==-1 )
    {
     StringBuilder b = new StringBuilder();
     b.AppendFormat( "INSERT INTO sg_tentry( te_text, te_utxt, te_text32, te_id_class, te_id_language )" );
     b.AppendFormat( " VALUES ( '{0}', '{1}', '{2}', {3}, {4} )",
      x.text,
      x.text.ToUpper(),
      x.text.Substring(0, Math.Min(32,x.text.Length) ).ToUpper(),
      x.id_class==-1 ? "NULL" : x.id_class.ToString(),
      x.id_language==-1 ? "NULL" : x.id_language.ToString() );

     DbCommand cmd2 = new SqlCommand( b.ToString(), cnx, (SqlTransaction)tx );
     cmd2.ExecuteNonQuery();
     cmd2.Dispose();

     x.id = LastInsertId();
    }
   else
    {
     StringBuilder b = new StringBuilder();
     b.AppendFormat( "UPDATE sg_tentry SET te_text='{0}', te_utxt='{1}', te_text32='{2}', te_id_class={3}, te_id_language={4} WHERE id={5}",
      x.text,
      x.text.ToUpper(),
      x.text.Substring(0,32).ToUpper(),
      x.id_class==-1 ? "NULL" : x.id_class.ToString(),
      x.id_language==-1 ? "NULL" : x.id_language.ToString(),
      x.id );

     DbCommand cmd2 = new SqlCommand( b.ToString(), cnx, (SqlTransaction)tx );
     cmd2.ExecuteNonQuery();
     cmd2.Dispose();
    }

   x.StoreNotes();

   if( commit )
    CommitTx();

   return;
  }


  public override void Store( Solarix.WordEntry e )
  {
   bool commit = !InTransaction();
   if( !InTransaction() )
    { 
     BeginTx();
    }

   if( e.id==-1 )
    {
     StringBuilder b = new StringBuilder();

     // создаем шапку словарной статьи
     b.AppendFormat( "INSERT INTO sg_entry( name, uname, id_class, freq, exportable )" );
     b.AppendFormat( " VALUES ( '{0}', '{1}', {2}, 0, 1 )", e.name, e.name.ToUpper(), e.partofspeech.id );
     SqlCommand cmd2 = new SqlCommand( b.ToString(), cnx, (SqlTransaction)tx );
     cmd2.ExecuteNonQuery();
     cmd2.Dispose();

     e.id = LastInsertId();

     // сохраняем атрибуты статьи
     foreach( CoordPair a in e.attrs.list )
      {
       b.Length=0;
       b.AppendFormat( "INSERT INTO sg_entry_coord( id_entry, icoord, istate )" );
       b.AppendFormat( " VALUES ( {0}, {1}, {2} )", e.id, a.id_coord, a.id_state );

       SqlCommand cmd3 = new SqlCommand( b.ToString(), cnx, (SqlTransaction)tx );
       cmd3.ExecuteNonQuery();
       cmd3.Dispose();
      }

     // теперь сохраняем грамматические формы
     foreach( EntryForm f in e.forms.list )
      {
       f.id_entry = e.id;
       Store(f);
      }
    } 
   else
    {
     // todo
    }

   if( commit )
    CommitTx();

   return;
  }

  public override int StoreLexem( string str )
  {
   string ustr = str.ToUpper();

   StringBuilder b = new StringBuilder();
   b.AppendFormat( "SELECT id FROM sg_lexem WHERE name='{0}'", ustr );
   SqlCommand cmd1 = new SqlCommand( b.ToString(), cnx, (SqlTransaction)tx );
   object obj = cmd1.ExecuteScalar();
   cmd1.Dispose();
   
   if( obj!=null && obj.ToString().Length>0 )
    {
     return int.Parse(obj.ToString());
    }

   b.Length=0;

   bool commit = !InTransaction();
   if( !InTransaction() )
    { 
     BeginTx();
    }

   b.AppendFormat( "INSERT INTO sg_lexem( name ) VALUES (  '{0}' )", ustr );   
   SqlCommand cmd3 = new SqlCommand( b.ToString(), cnx, (SqlTransaction)tx );
   cmd3.ExecuteNonQuery();
   cmd3.Dispose();

   int id = LastInsertId();

   if( commit )
    CommitTx();

   return id;
  }


  public override void Store( Solarix.EntryForm f )
  {
   bool commit = !InTransaction();
   if( !InTransaction() )
    { 
     BeginTx();
    }

   if( f.iform==-1 )
    {
     // первое сохранение грамматической формы.
     StringBuilder b = new StringBuilder();
     b.AppendFormat( "SELECT CASE count(*) WHEN 0 THEN 1 ELSE max(iform)+1 END FROM sg_form WHERE id_entry={0}", f.id_entry );
     SqlCommand cmd1 = new SqlCommand( b.ToString(), cnx, (SqlTransaction)tx );
     object obj = cmd1.ExecuteScalar();
     cmd1.Dispose();
     int iform = int.Parse( obj.ToString() );
     f.iform = iform;

     int id_lexem = StoreLexem( f.name );
     StringBuilder dims = new StringBuilder();

     foreach( CoordPair p in f.coords.list )
      {
       dims.AppendFormat( " {0}:{1}", p.id_coord, p.id_state );
      }

     dims.Append( " " );

     StringBuilder str_dims = new StringBuilder();
     str_dims.AppendFormat( " {0} ", f.coords.ToString() );

     int id_dims = RegisterCoordPairs(dims.ToString(),str_dims.ToString());
   

     b.Length = 0;
     b.AppendFormat( "INSERT INTO sg_form( id_entry, iform, name, id_lexem, id_dims )" );
     b.AppendFormat( " VALUES ( {0}, {1}, '{2}', {3}, {4} )",
                      f.id_entry, f.iform, f.name, id_lexem, id_dims );
     SqlCommand cmd2 = new SqlCommand( b.ToString(), cnx, (SqlTransaction)tx );
     cmd2.ExecuteNonQuery();
     cmd2.Dispose();

     // сохраняем измерения
     foreach( CoordPair dim in f.coords )
      {
       b.Length=0;
       b.AppendFormat( "INSERT INTO sg_form_coord( id_entry, iform, icoord, istate ) VALUES ( {0}, {1}, {2}, {3} )",
        f.id_entry, f.iform, dim.id_coord, dim.id_state );

       SqlCommand cmd3 = new SqlCommand( b.ToString(), cnx, (SqlTransaction)tx );
       cmd3.ExecuteNonQuery();
       cmd3.Dispose();
      }
    }
   else
    {
     // todo
    }

   if( commit )
    CommitTx();
  }

  public override void Store( int tlink_id, Solarix.LinkFlag f )
  {
   bool commit = !InTransaction();
   if( !InTransaction() )
    BeginTx();

   string sql = string.Format( "INSERT INTO sg_tlink_flag( tlf_tl_id, tlf_flag, tlf_value ) VALUES ( {0}, '{1}', '{2}' )"
    , tlink_id, f.name, f.value );
   SqlCommand cmd3 = new SqlCommand( sql, cnx, (SqlTransaction)tx );
   cmd3.ExecuteNonQuery();
   cmd3.Dispose();

   f.id = LastInsertId();

   if( commit )
    CommitTx();
   
   return;
  }

  public override void Store( int te_id, Solarix.PhraseNote note )
  {
   bool commit = !InTransaction();
   if( !InTransaction() )
    BeginTx();
 
   if( note.id==-1 )
    {
     string sql = string.Format( "INSERT INTO tnotes( tn_te_id, tn_type, tn_format, tn_data ) VALUES ( {0}, {1}, NULL, '{2}' )"
      , te_id, note.itype, note.text );
     SqlCommand cmd3 = new SqlCommand( sql, cnx, (SqlTransaction)tx );
     cmd3.ExecuteNonQuery();
     cmd3.Dispose();

     note.id = LastInsertId();
    }
   else
    {
     string sql = string.Format( "UPDATE tnotes SET tn_data={0} WHERE tn_id={1} AND tn_type={2}", note.text, note.id, note.itype );
     SqlCommand cmd3 = new SqlCommand( sql, cnx, (SqlTransaction)tx );
     cmd3.ExecuteNonQuery();
     cmd3.Dispose();
    } 


   if( commit )
    CommitTx();
      
   return;
  }



  public override int RegisterCoordPairs( string int_dims, string str_dims )
  {
   if( int_dims.Trim().Length==0 )
    return 0;

   StringBuilder b = new StringBuilder();
   b.AppendFormat( "SELECT id FROM coord_pairs WHERE pairs='{0}'", int_dims );
   SqlCommand cmd1 = new SqlCommand( b.ToString(), cnx, (SqlTransaction)tx );
   object obj = cmd1.ExecuteScalar();
   cmd1.Dispose();
   
   if( obj!=null && obj.ToString().Length>0 )
    {
     return int.Parse(obj.ToString());
    }

   b.Length=0;

   b.AppendFormat( "INSERT INTO coord_pairs( pairs, str_pairs ) VALUES ( '{0}', '{1}' )", int_dims, str_dims );   
   SqlCommand cmd3 = new SqlCommand( b.ToString(), cnx, (SqlTransaction)tx );
   cmd3.ExecuteNonQuery();
   cmd3.Dispose();

   int id_dims = this.LastInsertId();

   return id_dims;
  }


  public override int RegisterTagSet( string tags )
  {
   if( tags.Length==0 )
    return 0;

   StringBuilder b = new StringBuilder();
   b.AppendFormat( "SELECT id FROM tag_set WHERE tags='{0}'", tags );
   SqlCommand cmd1 = new SqlCommand( b.ToString(), cnx, (SqlTransaction)tx );
   object obj = cmd1.ExecuteScalar();
   cmd1.Dispose();
   
   if( obj!=null && obj.ToString().Length>0 )
    {
     return int.Parse(obj.ToString());
    }

   b.Length=0;

   b.AppendFormat( "INSERT INTO tag_set( tags ) VALUES ( '{0}' )", tags );   
   SqlCommand cmd3 = new SqlCommand( b.ToString(), cnx, (SqlTransaction)tx );
   cmd3.ExecuteNonQuery();
   cmd3.Dispose();

   int id_tags = this.LastInsertId();

   return id_tags;
  }

 }
}
