<script language="php">
function stem( $word )
{
$uword = strtolower($word);
$wordlen = strlen($word);
if($wordlen<3) return $uword;
$last_ch = substr($uword,$wordlen-1,1);
$prev_ch = substr($uword,$wordlen-2,1);
$sfx2=substr( $uword, $wordlen-2, 1 );
$sfx3=substr( $uword, $wordlen-3, 2 );
$sfx3_2=substr( $uword, $wordlen-3, 1 );
$sfx4=substr( $uword, $wordlen-4, 3 );
$sfx4_2=substr( $uword, $wordlen-4, 2 );
$sfx6=substr( $uword, $wordlen-6, 5 );
$sfx6_2=substr( $uword, $wordlen-6, 4 );
$sfx7=substr( $uword, $wordlen-7, 6 );
$sfx7_2=substr( $uword, $wordlen-7, 5 );
$sfx5=substr( $uword, $wordlen-5, 4 );
$sfx5_2=substr( $uword, $wordlen-5, 3 );
$sfx8=substr( $uword, $wordlen-8, 7 );
$sfx8_2=substr( $uword, $wordlen-8, 6 );
$sfx10=substr( $uword, $wordlen-10, 9 );
$sfx10_2=substr( $uword, $wordlen-10, 8 );
$sfx9=substr( $uword, $wordlen-9, 8 );
$sfx9_2=substr( $uword, $wordlen-9, 7 );
$sfx11=substr( $uword, $wordlen-11, 10 );
$sfx11_2=substr( $uword, $wordlen-11, 9 );

 if($last_ch=='м')
  {
 if( $prev_ch=='е' )
  {
   if( strcmp($sfx7_2,"очайш")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"йнейш")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"ьнейш")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx6_2,"нейш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"чайш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"рейш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"шайш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"бер")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ожж")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"обь")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"аст")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ожм")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"удн")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"опр")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ска")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"омн")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"дер")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"теч")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"оль")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"овь")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ейш")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"ка")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ен")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьн")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"яд")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"йц")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"яж")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"дн")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"да")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ха")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"за")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ов")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"им")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ер")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьц")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"йд")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"уд")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"йм")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"шл")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"га")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"я")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"е")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ю")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"б")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ц")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ч")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"о")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ж")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"д")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"и")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"у")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"н")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"а")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"р")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ш")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"в")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"л")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"щ")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"т")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"м")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='и' )
  {
   if( strcmp($sfx7_2,"йнейш")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"очайш")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"ьнейш")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx6_2,"шайш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"нейш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"чайш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"рейш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"гон")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ейш")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"ек")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"он")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"йк")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ок")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ст")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"дк")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьк")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"г")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"к")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"с")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"т")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"д")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"х")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"о")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"з")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ж")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"н")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ш")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='а' )
  {
   if( strcmp($sfx7_2,"ьмист")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx6_2,"утор")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"мст")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ист")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"ат")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"йц")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ен")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"йк")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ят")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьм")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьк")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьг")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ес")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьц")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ев")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьб")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"т")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"м")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"г")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"р")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"к")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ц")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"л")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"н")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='о' )
  {
   if( strcmp($sfx5_2,"онк")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"енк")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"дк")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьн")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"йк")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьк")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ек")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьц")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьм")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ок")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ин")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"йн")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"т")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"м")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"г")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"р")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ц")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"д")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"к")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"н")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"л")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"х")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='я' )
  {
   if( strcmp($sfx5_2,"ест")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"ст")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьн")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"чь")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"йн")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ер")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"зь")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"н")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"л")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"и")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"в")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"т")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='ы' )
  {
   if( strcmp($sfx4_2,"йн")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьн")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ин")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"д")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"н")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"р")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
 else
     {
      return substr($word,0,$wordlen-1);
 }
 }
else  if($last_ch=='е')
  {
 if( $prev_ch=='т' )
  {
   if( strcmp($sfx6_2,"омне")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"гони")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"омни")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"ожги")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"йдем")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"стим")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"теки")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"тече")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"ожже")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"опре")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"асте")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"опри")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"асти")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"овье")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"зжай")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"скай")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"бере")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"бери")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"дери")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"обье")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"дере")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"скае")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"олье")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"ожми")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"ожме")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"ове")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"оне")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ови")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"хай")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"бей")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"шим")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"жем")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ере")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ери")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"удь")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"уде")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"зай")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"зае")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"они")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ьем")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ним")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"шли")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"шле")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"гае")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"тьи")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"гай")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"вай")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"чем")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ядь")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"яди")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"йди")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"дем")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"нем")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"сти")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"кай")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"кае")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"яжи")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"дим")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"хае")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"йми")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"яже")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"име")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"дае")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"лей")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"тим")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"йде")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ими")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"вей")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"йме")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"им")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"де")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ре")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ай")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"не")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"зь")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ле")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ди")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"яе")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"уе")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"жь")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"уй")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"же")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"жи")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"си")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ти")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ее")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ье")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"шь")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ей")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ае")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"би")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"бе")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ши")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ги")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ой")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ое")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ми")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ме")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"юй")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"зи")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"сь")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"юе")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ри")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ни")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ще")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ве")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ви")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"дь")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ть")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"чь")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"яг")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"че")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ем")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ше")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ки")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"нь")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"щи")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"те")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"чи")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ли")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"д")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"з")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"й")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"и")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"е")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"а")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='и' )
  {
   if( strcmp($sfx7_2,"очайш")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"йнейш")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"ьнейш")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx6_2,"нейш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"рейш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"чайш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"шайш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"ейш")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"дк")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьк")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"йк")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ок")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ек")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"г")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"к")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"н")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"о")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"х")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='о' )
  {
   if( strcmp($sfx4_2,"дк")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьк")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьн")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"йк")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ок")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ек")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"йн")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"г")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"д")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"н")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"к")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"р")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"х")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='е' )
  {
   if( strcmp($sfx7_2,"очайш")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"йнейш")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"ьнейш")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx6_2,"нейш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"чайш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"шайш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"рейш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"ейш")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"ьн")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"йн")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"н")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"р")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='н' )
  {
   if( strcmp($sfx6_2,"усот")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx4_2,"уд")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"й")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"и")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"д")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='ы' )
  {
   if( strcmp($sfx4_2,"ьн")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ин")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"йн")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"д")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"н")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"р")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='к' )
  {
   if( strcmp($sfx4_2,"ен")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"он")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"й")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='ш' )
  {
   if( strcmp($sfx4_2,"ей")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='ц' )
  {
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"й")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='г' )
  {
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='ч' )
  {
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='м' )
  {
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='б' )
  {
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
 }
else  if( $prev_ch=='щ' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='ь' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='ж' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='р' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='л' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
      return substr($word,0,$wordlen-1);
 }
 }
else  if($last_ch=='й')
  {
 if( $prev_ch=='е' )
  {
   if( strcmp($sfx7_2,"йнейш")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"очайш")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"усотн")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"ьнейш")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx6_2,"шайш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"чайш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"нейш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"рейш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"ест")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ейш")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"ст")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьн")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ов")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ер")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"йн")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"б")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"з")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"л")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"н")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"о")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"в")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"т")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"р")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='и' )
  {
   if( strcmp($sfx7_2,"йнейш")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"очайш")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"ьнейш")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx6_2,"нейш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"чайш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"рейш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"шайш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"явш")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ивш")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ейш")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"дк")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьк")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"йк")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ок")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ек")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"вш")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"ш")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"к")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"г")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"н")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='о' )
  {
   if( strcmp($sfx4_2,"ек")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьм")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьн")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"йн")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ин")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"йк")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьг")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьк")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ок")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьб")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"дк")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"л")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"г")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"д")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"н")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"к")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"х")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"р")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='а' )
  {
   if( strcmp($sfx4_2,"ск")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"зж")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"к")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"г")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"з")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"х")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"в")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='ы' )
  {
   if( strcmp($sfx4_2,"ьн")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"йн")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"н")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"р")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='ю' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='у' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
      return substr($word,0,$wordlen-1);
 }
 }
else  if($last_ch=='и')
  {
 if( $prev_ch=='м' )
  {
   if( strcmp($sfx8_2,"очайши")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"ьнейши")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"ьмиста")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"йнейши")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx7_2,"шайши")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"мяста")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"утора")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"чайши")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"ьюста")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"нейши")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"рейши")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx6_2,"иста")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"естя")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"ейши")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"йка")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"дки")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ины")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ька")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"йки")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"еса")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ьба")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ата")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ьки")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"чья")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ева")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ята")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ьма")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ерь")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"йца")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ьня")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"стя")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"оки")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ьны")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"еки")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ена")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"йны")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"зья")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"йня")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"еря")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ьца")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ьга")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"га")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ки")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ия")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ла")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ца")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ка")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"хи")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ои")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ры")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ны")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ма")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ья")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьи")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"та")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ги")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ра")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"тя")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ля")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ды")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ня")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ни")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ож")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"на")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"вя")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"й")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"я")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"а")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ы")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"и")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='л' )
  {
   if( strcmp($sfx6_2,"огна")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"одра")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"обра")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"сте")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ожг")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ска")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"сла")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ева")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"пер")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"сти")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ова")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ста")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"тек")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"ка")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ди")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ви")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"си")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"на")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ти")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ег")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"га")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ли")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ос")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"да")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"се")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"би")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"за")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"зи")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ня")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ша")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"те")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ва")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"жа")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ра")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ха")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ер")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"та")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ну")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"са")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"де")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"мя")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"б")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ы")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"е")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ш")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"я")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"г")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"и")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"а")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"у")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"к")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"о")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='т' )
  {
   if( strcmp($sfx9_2,"ьмидеся")==0 )
 return substr($word,0,$wordlen-9);
   if( strcmp($sfx7_2,"идеся")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx4_2,"ес")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ас")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"с")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"й")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"д")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='н' )
  {
   if( strcmp($sfx5_2,"сот")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"го")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ом")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"й")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"е")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"о")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='к' )
  {
   if( strcmp($sfx4_2,"те")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"е")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"й")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"о")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"д")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='р' )
  {
   if( strcmp($sfx4_2,"оп")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"бе")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"де")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"е")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='г' )
  {
   if( strcmp($sfx4_2,"ож")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='в' )
  {
   if( strcmp($sfx3_2,"о")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='д' )
  {
   if( strcmp($sfx3_2,"й")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='ь' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='х' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='ш' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='ч' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='б' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='з' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='ж' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='и' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='с' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='щ' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
      return substr($word,0,$wordlen-1);
 }
 }
else  if($last_ch=='х')
  {
 if( $prev_ch=='а' )
  {
   if( strcmp($sfx7_2,"ьмист")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx6_2,"утор")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"хст")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ист")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"йц")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ен")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"йк")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ят")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьм")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьк")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьг")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ес")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьц")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьб")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ев")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ат")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"г")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"т")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"м")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"р")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"к")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ц")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"л")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"н")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"в")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='и' )
  {
   if( strcmp($sfx7_2,"йнейш")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"очайш")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"ьнейш")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx6_2,"нейш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"шайш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"чайш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"рейш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"ейш")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"ек")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"йк")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ок")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"дк")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьк")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"г")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"к")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"х")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"о")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"н")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='я' )
  {
   if( strcmp($sfx5_2,"ест")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"ст")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьн")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"чь")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"йн")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ер")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"зь")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"н")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"л")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"и")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"в")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"т")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='ы' )
  {
   if( strcmp($sfx4_2,"йн")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьн")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ин")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"д")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"н")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"р")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='е' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
      return substr($word,0,$wordlen-1);
 }
 }
else  if($last_ch=='о')
  {
 if( $prev_ch=='л' )
  {
   if( strcmp($sfx6_2,"огна")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"одра")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"обра")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"сте")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ожг")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ска")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"сла")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ева")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"сти")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"пер")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ова")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ста")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"тек")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"си")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ди")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ка")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ви")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ег")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"на")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ти")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"га")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ос")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"да")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"се")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"би")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"за")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ха")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ра")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"зи")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ня")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ша")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"те")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ва")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"жа")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"де")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ер")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"та")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ну")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"са")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ли")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"мя")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"б")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ш")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ы")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"е")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"я")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"и")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"а")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"у")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"к")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"о")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"г")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='г' )
  {
   if( strcmp($sfx9_2,"бочайше")==0 )
 return substr($word,0,$wordlen-9);
   if( strcmp($sfx8_2,"ьнейше")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"йнейше")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"очайше")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx7_2,"рейше")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"чайше")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"шайше")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"нейше")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx6_2,"ейше")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"ино")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ько")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"дко")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"йко")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"йно")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"око")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"еко")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ьно")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"ро")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ко")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"но")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"не")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"хо")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ое")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ье")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"го")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"до")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"о")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"е")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='к' )
  {
   if( strcmp($sfx3_2,"е")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"д")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"й")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"о")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='н' )
  {
   if( strcmp($sfx3_2,"й")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"и")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='ц' )
  {
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='м' )
  {
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
 }
else  if( $prev_ch=='т' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='х' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='р' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='д' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
      return substr($word,0,$wordlen-1);
 }
 }
else  if($last_ch=='у')
  {
 if( $prev_ch=='м' )
  {
   if( strcmp($sfx8_2,"ьнейше")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"йнейше")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"очайше")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx7_2,"рейше")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"чайше")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"шайше")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"нейше")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx6_2,"ейше")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"йко")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"око")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ько")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"дко")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ино")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"еко")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"йно")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ьно")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"хо")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ое")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"но")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ро")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ко")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"не")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"до")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"го")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ье")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ож")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"й")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"и")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"о")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"е")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='к' )
  {
   if( strcmp($sfx4_2,"те")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ен")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"он")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"й")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='р' )
  {
   if( strcmp($sfx4_2,"оп")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"бе")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"де")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"е")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='г' )
  {
   if( strcmp($sfx4_2,"ож")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"я")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='д' )
  {
   if( strcmp($sfx3_2,"й")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"я")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"у")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='н' )
  {
   if( strcmp($sfx4_2,"ом")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"и")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='ц' )
  {
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"й")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='т' )
  {
   if( strcmp($sfx4_2,"ас")==0 )
 return substr($word,0,$wordlen-4);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='б' )
  {
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='в' )
  {
   if( strcmp($sfx3_2,"о")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='ж' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='щ' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='ч' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='ш' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='л' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
      return substr($word,0,$wordlen-1);
 }
 }
else  if($last_ch=='а')
  {
 if( $prev_ch=='л' )
  {
   if( strcmp($sfx6_2,"огна")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"одра")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"обра")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"ева")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"сте")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ожг")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ска")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"сла")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"сти")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ста")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ова")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"тек")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"пер")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"ка")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ди")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"си")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ви")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"на")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ег")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ти")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"га")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ос")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"да")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"се")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"би")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"за")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ша")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"зи")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ха")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ня")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"те")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ва")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"жа")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ра")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"де")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ер")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"та")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ну")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"са")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ли")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"мя")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"б")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ш")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ы")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"е")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"я")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"и")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"а")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"у")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"к")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"г")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"о")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='к' )
  {
   if( strcmp($sfx4_2,"он")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ен")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"е")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"о")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"д")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"й")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='н' )
  {
   if( strcmp($sfx7_2,"удюжи")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx3_2,"й")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"и")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"е")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='т' )
  {
   if( strcmp($sfx6_2,"ьмис")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx4_2,"ис")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"а")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"с")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"я")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='р' )
  {
   if( strcmp($sfx5_2,"уто")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"то")==0 )
 return substr($word,0,$wordlen-4);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='ц' )
  {
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"й")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='м' )
  {
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='г' )
  {
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='с' )
  {
   if( strcmp($sfx3_2,"е")==0 )
 return substr($word,0,$wordlen-3);
 }
else  if( $prev_ch=='б' )
  {
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
 }
else  if( $prev_ch=='в' )
  {
   if( strcmp($sfx3_2,"е")==0 )
 return substr($word,0,$wordlen-3);
 }
else  if( $prev_ch=='х' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='д' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
      return substr($word,0,$wordlen-1);
 }
 }
else  if($last_ch=='ю')
  {
 if( $prev_ch=='у' )
  {
   if( strcmp($sfx7_2,"ьнейш")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"очайш")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"йнейш")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx6_2,"шайш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"рейш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"нейш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"чайш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"ейш")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"ьк")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"йк")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"дк")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьн")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ек")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ок")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"йн")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"н")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"к")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"х")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"д")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"р")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"г")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='о' )
  {
   if( strcmp($sfx4_2,"ьм")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ин")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"дк")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьн")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ек")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"йк")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьг")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьб")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьк")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ок")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"йн")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"л")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"к")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"н")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"х")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"д")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"р")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"г")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='е' )
  {
   if( strcmp($sfx7_2,"ьнейш")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"очайш")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"йнейш")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx6_2,"шайш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"нейш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"чайш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"ейш")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"ьн")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"йн")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"л")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"н")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='ь' )
  {
   if( strcmp($sfx11_2,"емьюдесят")==0 )
 return substr($word,0,$wordlen-11);
   if( strcmp($sfx9_2,"ьюдесят")==0 )
 return substr($word,0,$wordlen-9);
   if( strcmp($sfx5_2,"ест")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"ол")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ст")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"об")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ов")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ер")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ем")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"т")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='а' )
  {
   if( strcmp($sfx4_2,"ск")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"д")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"к")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"х")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"г")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"з")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='н' )
  {
   if( strcmp($sfx4_2,"уд")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"го")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"й")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"д")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"о")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='ю' )
  {
   if( strcmp($sfx3_2,"н")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='л' )
  {
   if( strcmp($sfx3_2,"ш")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='и' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='т' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
      return substr($word,0,$wordlen-1);
 }
 }
else  if($last_ch=='ь')
  {
 if( $prev_ch=='с' )
  {
   if( strcmp($sfx8_2,"огнало")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"ольете")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"обрала")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"огнала")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"огнали")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"ожмете")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"берите")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"ожмите")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"обрало")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"обрали")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"берете")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"овьете")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"гоните")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"астете")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"астите")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"скаете")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"скайте")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"йдемте")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"нимите")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"нимете")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"обьете")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx7_2,"имете")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"евало")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"евали")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"йдете")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"евала")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"имите")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"ядьте")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"ымите")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"ымете")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"стите")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"вайте")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"скали")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"скала")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"скало")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"вейте")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"зайте")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"йдите")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"бейте")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"ядете")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"овало")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"стило")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"таете")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"стила")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"стили")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"ерите")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"овали")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"овала")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"ерете")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"тайте")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"удете")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"овите")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"симте")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"немте")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"лейте")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"овете")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"демте")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"удьте")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"ясите")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"заете")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"ясете")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"хаете")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"хайте")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"оните")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx6_2,"жете")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"ожму")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"зала")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"зали")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"имте")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"дило")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"бери")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"овью")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"рете")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"нали")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"беру")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"нало")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"жьте")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"нала")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"жите")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"ожми")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"зила")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"рите")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"зило")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"зили")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"скаю")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"олью")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"гоню")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"вила")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"ните")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"вили")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"чьте")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"емте")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"тело")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"еете")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"шьте")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"асти")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"зало")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"сите")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"вите")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"дила")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"дили")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"оете")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"зьте")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"гони")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"ойте")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"тите")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"сьте")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"вете")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"лило")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"лили")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"лила")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"тила")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"тили")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"тило")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"сала")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"кало")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"зите")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"кали")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"кала")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"сила")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"сили")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"сило")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"ньте")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"било")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"обью")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"ките")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"вали")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"вала")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"жала")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"жали")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"жало")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"била")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"шите")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"сали")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"сало")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"вало")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"щите")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"били")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"нете")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"няла")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"ерло")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"ерли")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"ерла")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"хали")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"хала")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"аете")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"хало")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"рала")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"рали")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"уйте")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"рало")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"уете")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"шете")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"няли")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"няло")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"дете")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"мете")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"мите")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"айте")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"тьте")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"ясти")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"дите")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"тала")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"тали")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"ними")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"ясли")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"лете")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"ниму")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"ясло")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"осла")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"осли")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"чете")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"осло")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"тели")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"тела")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"асту")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"тете")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"дели")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"дела")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"дело")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"гите")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"дьте")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"чите")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"асла")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"вило")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"ейте")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"тало")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"щете")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"ьете")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"яло")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"яли")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"яла")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ову")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"кли")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"кло")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"зте")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"яду")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"кла")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ови")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ыли")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ыло")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"гли")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ыла")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ыми")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ыму")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"гла")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"сти")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"йди")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ери")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ола")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"оло")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"оли")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"йду")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ими")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"гло")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"иму")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"заю")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"еру")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ело")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ели")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ела")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"йте")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"шла")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"йти")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"шли")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"шло")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ило")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"или")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ила")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"уду")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ула")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"уло")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ули")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ала")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"али")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ало")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"оню")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"они")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"яси")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ясу")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ьте")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"хаю")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ите")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ете")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"те")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"жу")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"лю")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ги")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ли")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ла")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ло")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"гу")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ки")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"аю")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"щи")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ку")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"чи")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ту")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ти")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ду")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"шу")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ую")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ми")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"му")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"си")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ну")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"чу")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"щу")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ши")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ни")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ою")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ву")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"зи")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ди")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ею")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ру")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ри")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"жи")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ви")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ью")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"й")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ю")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"и")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"у")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='ш' )
  {
   if( strcmp($sfx6_2,"омне")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"ожже")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"гони")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"опре")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"асте")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"обье")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"овье")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"бере")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"дере")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"тече")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"олье")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"ожме")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"скае")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"ове")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ере")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"уде")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"зае")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"яже")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"гае")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"шле")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"они")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"яде")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"кае")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"сти")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"хае")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"йде")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"дае")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"име")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"йме")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"де")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"си")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"не")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ре")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ае")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"яе")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ти")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ди")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"уе")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"же")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ле")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ши")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ее")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ье")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"зи")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ше")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"бе")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ое")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"жи")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ме")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"юе")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"те")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ще")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ве")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"че")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"и")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"е")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"а")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='т' )
  {
   if( strcmp($sfx10_2,"енствова")==0 )
 return substr($word,0,$wordlen-10);
   if( strcmp($sfx6_2,"огна")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"одра")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"пере")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"обра")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"сте")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ска")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"сла")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ере")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ева")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"сти")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ова")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ста")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"ти")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"си")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ди")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"на")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ка")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ви")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"га")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"да")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"се")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"би")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"за")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ша")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"та")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"зи")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ня")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"те")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ва")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"жа")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ра")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ха")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"де")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"са")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ес")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ну")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ли")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"мя")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"с")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ы")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"е")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"я")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"и")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"у")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"а")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"о")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='н' )
  {
   if( strcmp($sfx4_2,"де")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"е")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"о")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='ч' )
  {
   if( strcmp($sfx4_2,"те")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"же")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"е")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='д' )
  {
   if( strcmp($sfx3_2,"я")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"у")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='ж' )
  {
   if( strcmp($sfx3_2,"я")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='в' )
  {
   if( strcmp($sfx3_2,"о")==0 )
 return substr($word,0,$wordlen-3);
 }
else  if( $prev_ch=='м' )
  {
   if( strcmp($sfx3_2,"е")==0 )
 return substr($word,0,$wordlen-3);
 }
else  if( $prev_ch=='л' )
  {
   if( strcmp($sfx3_2,"е")==0 )
 return substr($word,0,$wordlen-3);
 }
else  if( $prev_ch=='з' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
      return substr($word,0,$wordlen-1);
 }
 }
else  if($last_ch=='я')
  {
 if( $prev_ch=='с' )
  {
   if( strcmp($sfx8_2,"гонишь")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"огнать")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"ожмешь")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"берешь")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"астешь")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"овьешь")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"нимешь")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"скаешь")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"ольешь")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"обьешь")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"обрать")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx7_2,"евать")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"имешь")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"йдешь")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"ядешь")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"нимет")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"ымешь")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"нимут")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"нимем")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"скать")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"заешь")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"овьем")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"обьет")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"астет")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"обьют")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"астут")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"астем")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"ерешь")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"ереть")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"стить")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"таешь")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"овать")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"ожмут")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"ожмем")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"ожмет")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"удешь")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"обьем")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"ольем")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"стишь")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"овешь")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"ольют")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"ольет")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"скаем")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"скают")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"ясешь")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"онишь")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"берут")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"хаешь")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"гонит")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"гонят")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"скает")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"гоним")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"берем")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"берет")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"огнал")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"обрал")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"овьют")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"овьет")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx6_2,"жешь")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"зать")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"стим")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"стит")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"дить")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"стил")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"зает")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"нать")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"ерут")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"ерем")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"оним")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"онят")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"зишь")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"зить")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"онит")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"удут")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"удем")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"удет")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"скай")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"чешь")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"еешь")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"жишь")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"имте")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"дишь")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"вешь")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"стят")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"оешь")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"лить")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"ерет")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"кать")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"есть")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"ядем")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"ядят")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"сать")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"тить")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"ядет")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"нуть")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"сить")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"сишь")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"бить")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"жать")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"вать")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"нешь")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"аешь")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"овал")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"хаем")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"хают")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"таем")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"тает")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"уешь")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"решь")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"рать")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"хать")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"дешь")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"шешь")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"тишь")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"нять")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"мешь")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"овем")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"овет")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"овут")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"хает")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"лешь")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"ясет")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"имут")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"ясем")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"имет")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"ымем")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"ымут")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"тать")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"вить")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"ымет")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"имем")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"деть")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"йдут")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"тешь")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"зают")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"теть")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"заем")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"йдем")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"йдет")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"евал")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"скал")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"ьешь")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"щешь")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"ясут")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"дел")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"мем")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"тут")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"мут")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"тет")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"мет")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ают")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"шет")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"шут")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"шем")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ять")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"вай")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"сал")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"кут")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ядь")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"тем")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"гут")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"нял")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"вал")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"жал")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"кал")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"оют")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"оем")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"вут")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"оет")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"чут")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"тал")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"жим")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"лет")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"вем")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ыть")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"вет")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"лют")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"сть")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"нул")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"чем")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"жит")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ьют")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ьем")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ьет")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"аем")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"рем")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"оть")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"рет")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ает")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"еть")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"чет")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"тел")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"хал")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"зил")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"зим")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"рут")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"лем")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"зят")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"зит")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"зай")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ите")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"рал")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"лят")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"щут")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"вил")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"удь")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"шел")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"уть")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"щем")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"жет")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"очь")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"дет")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"щет")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ишь")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"тит")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"тят")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"еет")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"еют")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ить")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"вей")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"еем")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"тим")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"дем")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ует")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ать")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"тай")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"уют")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"дил")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ими")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"жут")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"сим")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"жем")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"зал")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"лил")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"дим")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"лей")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"дят")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"уем")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"дут")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"дит")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"нал")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ему")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"бей")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"нет")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"нем")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"хай")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"бил")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"нут")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"шат")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"тил")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"сил")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"сит")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"сят")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"его")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ечь")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ешь")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"их")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"чь")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ел")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ул")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ем")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ет")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"им")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ил")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ть")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ит")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ют")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ай")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ол")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"яс")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"жь")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"шь")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ос")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ут")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ей")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ст")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ят")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"дь")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ер")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"уй")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ал")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ял")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ег")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"нь")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ой")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"зь")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"сь")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ыл")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ие")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ат")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ий")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ее")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ею")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ая")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ую")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"к")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"г")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"й")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"л")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"з")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"м")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"т")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='а' )
  {
   if( strcmp($sfx7_2,"ьнейш")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"йнейш")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"очайш")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx6_2,"нейш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"шайш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"рейш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"чайш")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"ейш")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"ьк")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"йк")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"дк")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьн")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ек")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ок")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"йн")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"н")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"к")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"х")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"д")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"р")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"г")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='н' )
  {
   if( strcmp($sfx4_2,"уд")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"й")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"д")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='м' )
  {
   if( strcmp($sfx4_2,"уе")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"е")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
 }
else  if( $prev_ch=='ь' )
  {
   if( strcmp($sfx3_2,"з")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ч")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='я' )
  {
   if( strcmp($sfx3_2,"н")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='и' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='л' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='т' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
      return substr($word,0,$wordlen-1);
 }
 }
else  if($last_ch=='ы')
  {
 if( $prev_ch=='н' )
  {
   if( strcmp($sfx6_2,"дюжи")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx3_2,"й")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"и")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='ц' )
  {
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"й")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='р' )
  {
   if( strcmp($sfx4_2,"то")==0 )
 return substr($word,0,$wordlen-4);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='м' )
  {
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='б' )
  {
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
 }
else  if( $prev_ch=='т' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='д' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='л' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
      return substr($word,0,$wordlen-1);
 }
 }
else  if($last_ch=='т')
  {
 if( $prev_ch=='е' )
  {
   if( strcmp($sfx5_2,"ожж")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"обь")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"бер")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"аст")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ожм")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"опр")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"омн")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"дер")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"оль")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"овь")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ска")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"яд")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ка")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"яж")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"да")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ха")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"за")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ов")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"им")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ер")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"йд")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"уд")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"шл")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"га")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"йм")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"я")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"е")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ю")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"б")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ч")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"о")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ж")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"н")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"д")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"у")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"в")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"а")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ш")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"т")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"л")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"р")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"щ")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"м")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='у' )
  {
   if( strcmp($sfx5_2,"ожм")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ожг")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"аст")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"бер")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"опр")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"омн")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"дер")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"яд")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"яг")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ов")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"им")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"йд")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"уд")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ер")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"йм")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"б")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ч")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"г")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"д")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"н")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ж")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"в")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ш")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"к")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"т")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"щ")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"р")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"м")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='ю' )
  {
   if( strcmp($sfx5_2,"обь")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"оль")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"овь")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"ска")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"ка")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"да")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ха")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"за")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"шл")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"га")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"е")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ю")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"о")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"у")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"а")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"я")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"л")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='я' )
  {
   if( strcmp($sfx8_2,"емьдес")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx6_2,"ьдес")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"гон")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"он")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ст")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"л")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"с")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"т")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"д")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"з")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='и' )
  {
   if( strcmp($sfx5_2,"гон")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"он")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ст")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"т")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"с")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"д")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ж")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"з")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ш")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='о' )
  {
   if( strcmp($sfx6_2,"ьмис")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"емьс")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx4_2,"хс")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьс")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ис")==0 )
 return substr($word,0,$wordlen-4);
 }
else  if( $prev_ch=='а' )
  {
   if( strcmp($sfx3_2,"ш")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='с' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
      return substr($word,0,$wordlen-1);
 }
 }
else  if($last_ch=='в')
  {
 if( $prev_ch=='о' )
  {
   if( strcmp($sfx4_2,"ьц")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"йк")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьк")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"т")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"м")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ц")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"к")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"л")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"р")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='е' )
  {
   if( strcmp($sfx4_2,"чь")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ьц")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"йц")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"ь")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ц")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
 else
     {
 }
 }
else  if($last_ch=='л')
  {
 if( $prev_ch=='а' )
  {
   if( strcmp($sfx5_2,"обр")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"одр")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"огн")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"ск")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ев")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ов")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"ст")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"сл")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"т")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"х")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"в")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"з")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"с")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"н")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"д")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"к")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ж")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"р")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"г")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"ш")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='и' )
  {
   if( strcmp($sfx4_2,"ст")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"в")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"л")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"б")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"д")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"с")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"т")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"з")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='е' )
  {
   if( strcmp($sfx4_2,"ст")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"ш")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"д")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"с")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"т")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='я' )
  {
   if( strcmp($sfx3_2,"м")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"н")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='у' )
  {
   if( strcmp($sfx3_2,"н")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='ы' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='о' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
      return substr($word,0,$wordlen-1);
 }
 }
else  if($last_ch=='н')
  {
 if( $prev_ch=='е' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='я' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='и' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='о' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
 }
 }
else  if($last_ch=='к')
  {
 if( $prev_ch=='о' )
  {
   if( strcmp($sfx4_2,"ен")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"он")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"д")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='е' )
  {
   if( strcmp($sfx3_2,"т")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
 else
     {
      return substr($word,0,$wordlen-1);
 }
 }
else  if($last_ch=='ц')
  {
 if( $prev_ch=='е' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
 }
 }
else  if($last_ch=='г')
  {
 if( $prev_ch=='е' )
  {
   if( strcmp($sfx3_2,"ж")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='я' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
      return substr($word,0,$wordlen-1);
 }
 }
else  if($last_ch=='р')
  {
 if( $prev_ch=='е' )
  {
   if( strcmp($sfx3_2,"п")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='о' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
 }
 }
else  if($last_ch=='с')
  {
 if( $prev_ch=='е' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='о' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
 }
 }
else  if($last_ch=='д')
  {
      return substr($word,0,$wordlen-1);
 }
else  if($last_ch=='б')
  {
 if( $prev_ch=='е' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
      return substr($word,0,$wordlen-1);
 }
 }
return $uword;
}
</script>
