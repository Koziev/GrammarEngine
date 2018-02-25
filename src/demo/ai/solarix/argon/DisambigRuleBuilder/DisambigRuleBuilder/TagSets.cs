using System;
using System.Collections.Generic;
using System.Text;


class TagSets
{
 private Solarix.Dictionary dict;

 private Dictionary<int,CoordSet> sets;

 public TagSets( Solarix.Dictionary _dict )
 {
  sets = new Dictionary<int,CoordSet>();

  // Эти координаты не будут участвовать в генерации наборов тегов.
  List<int> ignore_coords = new List<int>();
  ignore_coords.Add( SolarixGrammarEngineNET.GrammarEngineAPI.CharCasing );

  Dictionary< int, List<Solarix.CoordPairs> > pos2coords = new Dictionary<int,List<Solarix.CoordPairs>>();

  foreach( Solarix.PartOfSpeech p in dict.partsofspeech )
  {
   pos2coords.Add( p.id, new List<Solarix.CoordPairs>() );
  }


  foreach( Solarix.WordEntry e in dict.entries.All() )
  {
   foreach( Solarix.EntryForm f in e.forms )
   {
    Solarix.CoordPairs pairs = new Solarix.CoordPairs( e.attrs, f.coords );
    pairs.Sort();

    List<Solarix.CoordPairs> pos_pairs = pos2coords[ e.partofspeech.id ];

    if( pos_pairs.IndexOf( pairs )==-1 )
     {
      pos_pairs.Add(pairs);
     }
   }
  }

  // Прочистим списки пар, удалив из них координаты из списка ignore_coords и сохранив уникальность.

  Dictionary< int, List< List<Solarix.CoordPair> > > pos2coords2 = new Dictionary<int,List<List<Solarix.CoordPair>>>();

  foreach( var x in pos2coords )
  {
   List< List<Solarix.CoordPair> > list2 = new List< List<Solarix.CoordPair> >();

   foreach( Solarix.CoordPairs px in x.Value )
    {
     bool found_any_ignorable=false;
     foreach( int id_ignore in ignore_coords )
     {
      if( px.IndexOfCoord(id_ignore)!=-1 )
       {
        found_any_ignorable=true;
        break;
       }
     }

     List<Solarix.CoordPair> clean_px = new List<Solarix.CoordPair>();
   
     if( found_any_ignorable )
      {
       clean_px = new List<Solarix.CoordPair>();

       foreach( var p in px.list )
        if( ignore_coords.IndexOf(p.coord.id)==-1 )
         clean_px.Add(p);

       clean_px.Sort();
      }
     else
      {
       clean_px = new List<Solarix.CoordPair>( px.list );
      }

     if( list2.IndexOf(clean_px)==-1 )
      list2.Add( clean_px );

    }

   pos2coords2.Add( x.Key, list2 );

   Console.WriteLine( "PartOfSpeech: {0} Number of tagsets: {1}", dict.partsofspeech[x.Key].name, list2.Count );
  }

  dict=_dict;
  return;
 }
}
