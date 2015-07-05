<?php
include '_sg_api.php'
?>

<html>

<head runat="server">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
</head>

<body>

<?php

if (!extension_loaded("gren")) print "GREN is missing";

$SOL_GREN_LAZY_LEXICON = 1;

$hEngine = sol_CreateGrammarEngineEx8( "e:\mvoice\lem\bin-windows\dictionary.xml", $SOL_GREN_LAZY_LEXICON );

//echo "hEngine=", $hEngine, "\n";

echo "Engine version: ", sol_GetVersion($hEngine), "\n";
echo "Dictionary version:", sol_DictionaryVersion($hEngine), "\n";
echo "n_entry=", sol_CountEntries($hEngine), "\n";

echo "Testing segmenter...\n";
$Text = "А.С. Пушкин знал, что такое 3.141";
$hSegmenter = sol_CreateSentenceBrokerMem8( $hEngine, $Text, RUSSIAN_LANGUAGE );
echo "hSegmenter=", $hSegmenter, "\n";

while( sol_FetchSentence( $hSegmenter )>=0 )
 {
  $Sentence = sol_GetFetchedSentence8( $hSegmenter );
  echo "sentence=", $Sentence, "\n";
  echo "Tokens:\n";
  $hTokens = sol_Tokenize8( $hEngine, $Sentence, RUSSIAN_LANGUAGE );
  $token_count = sol_CountStrings( $hTokens );
  echo "Number of words=", $token_count, "\n";
  for( $i=0; $i<$token_count; $i++ )
   {
    $token = sol_GetString8( $hTokens, $i );
    echo "Token[", $i, "]=", $token, "\n";
   }

  echo "------\n";
  sol_DeleteStrings($hTokens);
 }

sol_DeleteSentenceBroker($hSegmenter);

echo "Testing the morphological analyzer...\n";

echo "Morphological analysis of words\n";

$word = "мыла";
$hProjs = sol_ProjectWord8( $hEngine, $word, 0 );
$ProjCount = sol_CountProjections( $hProjs );
echo "Word=", $word, " gives ", $ProjCount, " projections:\n";
for( $i=0; $i<$ProjCount; $i++ )
 {
  $id_entry = sol_GetIEntry( $hProjs, $i );
  $id_partofspeech = sol_GetEntryClass( $hEngine, $id_entry );
  $partofspeech = sol_GetClassName8( $hEngine, $id_partofspeech );
  echo "projection[", $i, "] id_entry=", $id_entry, " part-of-speech=", $partofspeech, "\n";
 }
sol_DeleteProjections( $hProjs );

echo "Morphological analysis of phrases\n";

$phrase = "Мама мыла раму";
$hRes = sol_MorphologyAnalysis8( $hEngine, $phrase, 0, 0, 0, RUSSIAN_LANGUAGE );
$WordCount = sol_CountRoots( $hRes, 0 );
echo "There are ", $WordCount, " words...\n";
for( $i=0; $i<$WordCount; $i++ )
 {
  $hNode = sol_GetRoot( $hRes, 0, $i );
  $word = sol_GetNodeContents8( $hNode );
  echo "word[", $i, "]=", $word;
  $id_entry = sol_GetNodeIEntry( $hEngine, $hNode );
  echo " id_entry=", $id_entry;

  $id_partofspeech = sol_GetEntryClass( $hEngine, $id_entry );
  $partofspeech = sol_GetClassName8( $hEngine, $id_partofspeech );
  echo " part-of-speech=", $partofspeech;

  $entry_name = sol_GetEntryName8( $hEngine, $id_entry );
  echo " entry-name=", $entry_name;
  echo "\n";
 }

echo "\n";
sol_DeleteResPack( $hRes );

echo "Deleting the engine...\n";

sol_DeleteGrammarEngine($hEngine);

?>

</body>
</html>
