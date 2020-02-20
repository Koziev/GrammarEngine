// Связи русск-англ для многоязычного тезауруса
// http://www.solarix.ru/for_developers/docs/thesaurus.shtml
//
// CD->01.07.2005
// LC->07.04.2015
// --------------


// ***********************************************************
// These macros help to write compact traslations dictionary
// ***********************************************************


#define LINK_NOUN( Rus, Eng ) \
 #begin
 link СУЩЕСТВИТЕЛЬНОЕ:Rus{} <to_english> ENG_NOUN:Eng {}
 link ENG_NOUN:Eng{} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:Rus{}
 #end

#define LINK_NOUN2( Eng, Rus ) \
 #begin
 link СУЩЕСТВИТЕЛЬНОЕ:Rus{} <to_english> ENG_NOUN:Eng {}
 link ENG_NOUN:Eng{} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:Rus{}
 #end


#define LINK_ADJ( Rus, Eng ) \
 #begin
 link ПРИЛАГАТЕЛЬНОЕ:Rus{} <to_english> ENG_ADJECTIVE:Eng {}
 link ENG_ADJECTIVE:Eng{} <to_russian> ПРИЛАГАТЕЛЬНОЕ:Rus{}
 #end

#define LINK_ADJ2( Eng, Rus ) \
 #begin
 link ПРИЛАГАТЕЛЬНОЕ:Rus{} <to_english> ENG_ADJECTIVE:Eng {}
 link ENG_ADJECTIVE:Eng{} <to_russian> ПРИЛАГАТЕЛЬНОЕ:Rus{}
 #end


#define LINK_VERB( Rus, Eng ) \
 #begin

 link Инфинитив:Rus{} <to_english> ENG_VERB:Eng {}
 link Глагол:Rus{} <to_english> ENG_VERB:Eng {}

 link ENG_VERB:Eng {} <to_russian> Инфинитив:Rus{}
 link ENG_VERB:Eng {} <to_russian> Глагол:Rus{}
 
 #end

#define Imperfect( Rus, Eng ) \
 #begin

 link Инфинитив:Rus{ВИД:НЕСОВЕРШ} <to_english> ENG_VERB:Eng {}
 link Глагол:Rus{ВИД:НЕСОВЕРШ} <to_english> ENG_VERB:Eng {}

 link ENG_VERB:Eng {} <to_russian> Инфинитив:Rus{ВИД:НЕСОВЕРШ}
 link ENG_VERB:Eng {} <to_russian> Глагол:Rus{ВИД:НЕСОВЕРШ}
 
 #end




#define LINK_VERB2( Eng, Rus ) \
 #begin

 link Инфинитив:Rus{} <to_english> ENG_VERB:Eng {}
 link Глагол:Rus{} <to_english> ENG_VERB:Eng {}

 link ENG_VERB:Eng {} <to_russian> Инфинитив:Rus{}
 link ENG_VERB:Eng {} <to_russian> Глагол:Rus{}
 
 #end


#define LINK_PRONOUN( Rus, Eng ) \
 #begin
 link МЕСТОИМЕНИЕ:Rus{} <to_english> ENG_PRONOUN:Eng {}
 link ENG_PRONOUN:Eng {} <to_russian> МЕСТОИМЕНИЕ:Rus{}
 #end

#define LINK_PREP( Rus, Eng ) \
 #begin
 link ПРЕДЛОГ:Rus{} <to_english> ENG_PREP:Eng {}
 link ENG_PREP:Eng {} <to_russian> ПРЕДЛОГ:Rus{}
 #end

#define LINK_CONJ( Rus, Eng ) \
 #begin
 link СОЮЗ:Rus{} <to_english> ENG_CONJ:Eng {}
 link ENG_CONJ:Eng {} <to_russian> СОЮЗ:Rus{}
 #end

automat sg
{
 LINK_PRONOUN( Я, I )


 LINK_NOUN( бог, god  )
 LINK_NOUN( богиня, goddess  )
 
 LINK_NOUN( кошка, cat  )
 LINK_NOUN( кошечка, cat  )
 LINK_NOUN( кот, cat  )
 LINK_NOUN( котик, cat  )
 
 LINK_NOUN( собака, dog )
 LINK_NOUN( пёс, dog )
 LINK_NOUN( псина, dog )
 LINK_NOUN( собачка, dog )
 
 LINK_NOUN( мышь, mouse )
 LINK_NOUN( мышка, mouse )
 
 LINK_NOUN( стол, table )
 LINK_NOUN( СТУЛ, CHAIR )
 LINK_NOUN( РАСПОЛОЖЕНИЕ, LAYOUT )
 LINK_NOUN( ЦВЕТ, COLOR )
 LINK_NOUN( СЕТЬ, GRID )
// LINK_NOUN( НЕЧТО, SOMETHING )
 LINK_NOUN( УТРО, MORNING )
 LINK_NOUN( ДЕНЬ, DAY )
 LINK_NOUN( ВЕЧЕР, EVENING )
 LINK_NOUN( НОЧЬ, NIGHT )
 LINK_NOUN( НЕДЕЛЯ, WEEK )
// LINK_NOUN( НЕКТО, SOMEONE )


 LINK_VERB( МОЧЬ, CAN )
 LINK_VERB( МОЧЬ, MAY )
 LINK_VERB( ДОЛЖЕНСТВОВАТЬ, MUST )


 LINK_VERB( СПАТЬ, SLEEP )
 LINK_VERB( играть, play )

// LINK_VERB( ДРАТЬСЯ, FIGHT )
 LINK_VERB( ПРОХОДИТЬ, PASS  )
 LINK_VERB( СТАНОВИТЬСЯ, BECOME )
// LINK_VERB( КРУТИТЬСЯ, SPIN )
 LINK_VERB( ДАВАТЬ, GIVE )
 LINK_VERB( ПОДХОДИТЬ, FIT )
 LINK_VERB( БРАТЬ, TAKE )
 LINK_VERB( ДЕЛАТЬ, MAKE )
 LINK_VERB( ПОКУПАТЬ, BUY )
 LINK_VERB( ЛЕТАТЬ, FLY )
 LINK_VERB( БЕЖАТЬ, RUN )
// LINK_VERB( ЕСТЬ, EAT )
 LINK_VERB( ЗАПРЕЩАТЬ, FORBID )
 LINK_VERB( ПЛАТИТЬ, PAY )
 LINK_VERB( СПРАШИВАТЬ, ASK )
 LINK_VERB( ЗАБЫВАТЬ, FORGET )
// LINK_VERB( ОТСЕКАТЬ, CUT )
 LINK_VERB( ЛОВИТЬ, CATCH )
 LINK_VERB( ПАДАТЬ, FALL )
 LINK_VERB( БРОСАТЬ, THROW )
 LINK_VERB( ДОКАЗЫВАТЬ, PROVE )
 LINK_VERB( ВЕСТИ, LEAD )
 LINK_VERB( ПОНИМАТЬ, UNDERSTAND )
 LINK_VERB( ЧИТАТЬ, READ )
 LINK_VERB( ДУМАТЬ, THINK )
 LINK_VERB( БЫТЬ, BE )
 LINK_VERB( СТРЕЛЯТЬ, SHOOT )
 LINK_VERB( НОСИТЬ, WEAR )
 LINK_VERB( ПОКИДАТЬ, QUIT )
 LINK_VERB( ПОСЫЛАТЬ, SEND )
 LINK_VERB( ИДТИ, GO )
 LINK_VERB( ГОВОРИТЬ, SPEAK )
 LINK_VERB( ИСКАТЬ, FIND )
 LINK_VERB( СКРЫВАТЬ, HIDE )
 LINK_VERB( НАЧИНАТЬ, BEGIN )
 LINK_VERB( ПРИНОСИТЬ, BRING )
 LINK_VERB( СТРОИТЬ, BUILD )
 LINK_VERB( ПРИХОДИТЬ, COME )
 LINK_VERB( КОПАТЬ, DIG )
// LINK_VERB( ВЗРЫВАТЬ, BURST )
 LINK_VERB( ГОВОРИТЬ, SAY )
 LINK_VERB( ОШИБАТЬСЯ, MISTAKE )
// LINK_VERB( ТРАТИТЬ, SPEND )
 LINK_VERB( ЗНАЧИТЬ, MEAN )
// LINK_VERB( ГРЕЗИТЬ, DREAM )
 LINK_VERB( ПИТЬ, DRINK )
 LINK_VERB( ЗАКРЫВАТЬ, SHUT )
 LINK_VERB( СТОЯТЬ, STAND )
 LINK_VERB( ПОПАДАТЬ, HIT )
 LINK_VERB( РИСОВАТЬ, DRAW )
// LINK_VERB( УДЕРЖИВАТЬ, HOLD )

/*
 LINK_VERB( ТОНУТЬ, SINK )
 LINK_VERB( ДЕРЖАТЬ, KEEP )
 LINK_VERB( ЧУВСТВОВАТЬ, FEEL )
 LINK_VERB( ГОВОРИТЬ, TELL )
 LINK_VERB( ГОРЕТЬ, BURN )
 LINK_VERB( ЗАМОРАЖИВАТЬ, FREEZE  )
 LINK_VERB( СЛЫШАТЬ, HEAR )
 LINK_VERB( УДАРЯТЬ, STRIKE )
 LINK_VERB( ЗНАТЬ, KNOW )
 LINK_VERB( ЛЕЖАТЬ, LAY )
 LINK_VERB( ТРЯСТИ, SHAKE )
 LINK_VERB( ВЫИГРЫВАТЬ, WIN )
 LINK_VERB( ПИТАТЬ, FEED )
 LINK_VERB( ПОКАЗЫВАТЬ, SHOW )
 LINK_VERB( РАЗДЕЛЯТЬ, SPLIT )
 LINK_VERB( ГНУТЬ, BEND )
 LINK_VERB( ПЕРЕОДЕВАТЬ, CAST )
 LINK_VERB( ТОЛКАТЬ, THRUST )
 LINK_VERB( ПРОДАВАТЬ, SELL )
 LINK_VERB( SHAVE, БРИТЬ )
 LINK_VERB( БИТЬ, BEAT )
 LINK_VERB( СВЯЗЫВАТЬ, BIND  )
 LINK_VERB( ИЗУЧАТЬ, LEARN )
 LINK_VERB( ВОНЯТЬ, STINK )
 LINK_VERB( ПЕТЬ, SING )
 LINK_VERB( УЧИТЬ, TEACH )
 LINK_VERB( НЫРЯТЬ, DIVE )
 LINK_VERB( КУСАТЬ, BITE )
 LINK_VERB( ЖАЛИТЬ, STING )
 LINK_VERB( ПЛАВАТЬ, SWIM )
 LINK_VERB( СЖИМАТЬ, SHRINK )
 LINK_VERB( РАСПРЕДЕЛЯТЬ, SPREAD )
 LINK_VERB( ПРОЩАТЬ, FORGIVE )
 LINK_VERB( СКАНИРОВАТЬ, SCAN )
 LINK_VERB( ПРИСОЕДИНЯТЬ, JOINT )
 LINK_VERB( БРОСАТЬ, DROP )
 LINK_VERB( РАЗДЕВАТЬ, STRIP )
 LINK_VERB( ПЕЧАТАТЬ, TYPE )
 LINK_VERB( ПРЫГАТЬ, JUMP )
 LINK_VERB( ПИНАТЬ, KICK )
 LINK_VERB( ОБРАЩАТЬСЯ, HANDLE )
 LINK_VERB( ЗАРАБАТЫВАТЬ, EARN )
 LINK_VERB( ПУГАТЬ, FEAR )
 LINK_VERB( ЛЕЧИТЬ, CURE )
 LINK_VERB( ЦЕЛОВАТЬ, KISS )
 LINK_VERB( ТЕСТИРОВАТЬ, TEST )
 LINK_VERB( СТАРТОВАТЬ, START )
 LINK_VERB( ДЕЙСТВОВАТЬ, ACT )
 LINK_VERB( ТРЕБОВАТЬ, DEMAND )
 LINK_VERB( СТАЛКИВАТЬСЯ, FACE )
 LINK_VERB( ТОРМОЗИТЬ, DELAY  )
 LINK_VERB( ГАВКАТЬ, BARK )
 LINK_VERB( ЗАКЛИНАТЬ, SPELL )
 Imperfect( АКЦЕНТИРОВАТЬ, ACCENT )
 LINK_VERB( ЗАБОТИТЬСЯ, CARE )
 LINK_VERB( МЕТИТЬ, MARK )
 LINK_VERB( ВЫЗЫВАТЬ, CALL )
 LINK_VERB( ПОСЕЩАТЬ, VISIT )
 LINK_VERB( СВЕРЛИТЬ, DRILL )
 LINK_VERB( ВИСЕТЬ, HANG )
 LINK_VERB( РАБОТАТЬ, WORK )
 LINK_VERB( СВЯЗЫВАТЬ, LINK )
 LINK_VERB( ПОЛЗТИ, CREEP )
 LINK_VERB( СВЕТИТЬ, SHINE  )
 LINK_VERB( ПРЕРЫВАТЬ, BREAK  )
 LINK_VERB( СИДЕТЬ, SIT  )
 LINK_VERB( ВИДЕТЬ, SEE  )
*/

 
 LINK_ADJ( УЗКИЙ     , NARROW )
 LINK_ADJ( ТЯЖЕЛЫЙ   , HEAVY  )
 LINK_ADJ( МОЛОДОЙ   , YOUNG  )  
 LINK_ADJ( БЕЛЫЙ     , WHITE  )
 LINK_ADJ( БЛИЗКИЙ   , CLOSE  )
 LINK_ADJ( СУХОЙ     , DRY    )  
 LINK_ADJ( ЧЕРНЫЙ    , BLACK  )
 LINK_ADJ( СТАРЫЙ    , OLD    )
 LINK_ADJ( ГОРЯЧИЙ   , HOT    )
 LINK_ADJ( КОРОТКИЙ  , SHORT  )
 LINK_ADJ( ДОРОГОЙ   , DEAR   )
 LINK_ADJ( ВЕСЕЛЫЙ   , CHEERFUL  )
 LINK_ADJ( ОБЩИЙ     , COMMON )
 LINK_ADJ( ВЕЛИКИЙ   , GREAT  )
 LINK_ADJ( ЧИСТЫЙ    , CLEAN  )
 LINK_ADJ( ДЛИННЫЙ   , LONG   )
 LINK_ADJ( БОЛЬШОЙ   , BIG    )
 LINK_ADJ( МОКРЫЙ    , WET    )
 LINK_ADJ( СЛЕДУЮЩИЙ , NEXT   )
 LINK_ADJ( СИЛЬНЫЙ   , STRONG )
 LINK_ADJ( ТЕПЛЫЙ    , WARM   )
 LINK_ADJ( ГЛУХОЙ    , DEAF   )
 LINK_ADJ( МОГУЧИЙ   , MIGHTY )
 LINK_ADJ( ПРОЧИЙ    , OTHER  )    
 LINK_ADJ( НИЗКИЙ    , LOW    )
 LINK_ADJ( ГЛУБОКИЙ  , DEEP   )
 LINK_ADJ( ТИХИЙ     , SILENT )
 LINK_ADJ( ТЕМНЫЙ    , DARK   )
 LINK_ADJ( МЯГКИЙ    , SOFT   )
 LINK_ADJ( БУДУЩИЙ   , FUTURE )
 LINK_ADJ( ВЕСЬ      , WHOLE  )
 LINK_ADJ( ХОРОШИЙ   , GOOD   )

 LINK_ADJ( МИЛЫЙ     , PLEASANT )
 LINK_ADJ( МИЛЫЙ     , NICE   )

 LINK_ADJ( МАЛЫЙ     , SMALL  ) 
 LINK_ADJ( СПОКОЙНЫЙ , CALM   )
 LINK_ADJ( БЫСТРЫЙ   , FAST   )
 LINK_ADJ( НОВЫЙ     , NEW    )
 LINK_ADJ( ЭТОТ      , THIS   )     
 LINK_ADJ( САМЫЙ     , MOST   )
 LINK_ADJ( ДОБРЫЙ    , KIND   )
 LINK_ADJ( ШИРОКИЙ   , WIDE   )
 LINK_ADJ( ЗЛОЙ      , EVIL   )
 LINK_ADJ( НАСТОЯЩИЙ , REAL   )
 LINK_ADJ( ВСЯКИЙ    , EACH   )
 LINK_ADJ( ТАКОЙ     , SUCH   )
 LINK_ADJ( ПЕРВЫЙ    , FIRST  )

 LINK_ADJ( ДРУГОЙ    , ANOTHER )
 LINK_ADJ( ДРУГОЙ    , OTHER   )

 LINK_ADJ( РАННИЙ    , EARLY   )
 LINK_ADJ( ГУСТОЙ    , DENSE   )
 LINK_ADJ( КРАСНЫЙ   , RED     )
 LINK_ADJ( ХОЛОДНЫЙ  , COLD    )
 LINK_ADJ( ЗНАКОМЫЙ  , FAMILIAR )

 LINK_ADJ( ТОНКИЙ    , THIN     ) 
 LINK_ADJ( ТОНКИЙ    , SLENDER  )
 LINK_ADJ( ТОНКИЙ    , FINE     )
 LINK_ADJ( ТОНКИЙ    , DELICATE )
 LINK_ADJ( ТОНКИЙ    , SUBTLE   )
 LINK_ADJ( ТОНКИЙ    , SHARP    )

 LINK_ADJ( ЖЕЛТЫЙ    , YELLOW   )
 LINK_ADJ( ПОДОБНЫЙ  , SIMILAR  )

 LINK_ADJ( ЛЕГКИЙ    , LIGHT )
 LINK_ADJ( ЛЕГКИЙ    , EASY  )
 LINK_ADJ( ЛЕГКИЙ    , SLIGHT )

 LINK_ADJ( ЖИВОЙ     , ALIVE  )
 LINK_ADJ( ЖИВОЙ     , LIVE   )

 LINK_ADJ( ОГРОМНЫЙ  , ENORMOUS )
 LINK_ADJ( ЛЕВЫЙ     , LEFT     )

 LINK_ADJ( ГОЛЫЙ     , BARE     )

 LINK_ADJ( ТОЛСТЫЙ   , THICK    )
 LINK_ADJ( ТОЛСТЫЙ   , FAT      )

 LINK_ADJ( СТРАШНЫЙ  , TERRIBLE ) 
 LINK_ADJ( СТРАШНЫЙ  , AWFUL    ) 

 LINK_ADJ( НИЖНИЙ    , BOTTOM )

 LINK_ADJ( ТВЕРДЫЙ   , HARD )
 LINK_ADJ( ТВЕРДЫЙ   , SOLID )
 LINK_ADJ( ТВЕРДЫЙ   , FIRM )

 LINK_ADJ( ЧУЖОЙ     , ALIEN )
 LINK_ADJ( МЕРТВЫЙ   , DEAD  )
 LINK_ADJ( ЛЮБОЙ     , ANY   )
 LINK_ADJ( ЯРКИЙ     , BRIGHT )

 LINK_ADJ( ВЫСОКИЙ   , HIGH  )
 LINK_ADJ( ВЫСОКИЙ   , TALL  )
 LINK_ADJ( ВЫСОКИЙ   , GREAT )

 LINK_ADJ( ГЛУПЫЙ    , SILLY )
 LINK_ADJ( ПОСЛЕДНИЙ , LAST )
 LINK_ADJ( РАБОЧИЙ   , WORK )
 LINK_ADJ( ПОЛНЫЙ    , FULL )
 LINK_ADJ( РОДНОЙ    , NATIVE )

 LINK_ADJ( ИНОЙ      , OTHER )
 LINK_ADJ( ИНОЙ      , ANOTHER )

 LINK_ADJ( ПОХОЖИЙ   , SIMILAR )
 LINK_ADJ( РАЗНЫЙ    , DIFFERENT )
 LINK_ADJ( ЖЕСТКИЙ   , HARD )

 
 LINK_ADJ( ПРАВЫЙ    , RIGHT )
 LINK_ADJ( КАЖДЫЙ    , EACH  )
 LINK_ADJ( ГРОМКИЙ   , LOUD  )
 LINK_ADJ( ПРЯМОЙ    , DIRECT )
 LINK_ADJ( ПРОСТОЙ   , SIMPLE )

 LINK_ADJ( СОЗНАТЕЛЬНЫЙ, CONSCIOUS )
 LINK_ADJ( СОЗНАТЕЛЬНЫЙ, INTELLIGENT )
 LINK_ADJ( СОЗНАТЕЛЬНЫЙ, DELIBERATE )
 LINK_ADJ( СОЗНАТЕЛЬНЫЙ, INTENTIONAL )

 LINK_ADJ( ОСОБЫЙ    , SPECIAL )
 LINK_ADJ( ОСОБЫЙ    , PARTICULAR )

 LINK_ADJ( КРУГЛЫЙ, ROUND )

 LINK_ADJ( СМЕЛЫЙ, BRAVE )
 LINK_ADJ( СМЕЛЫЙ, AMBITIOUS )

 LINK_ADJ( МЕЛКИЙ, SMALL )
 LINK_ADJ( МЕЛКИЙ, SHALLOW )
 LINK_ADJ( МЕЛКИЙ, MINOR )

 LINK_ADJ( СЕРЫЙ, GREY )
 LINK_ADJ( ОТКРЫТЫЙ, OPEN )
 LINK_ADJ( ГОЛУБОЙ, BLUE )

 LINK_ADJ( РЕЗКИЙ, SHARP )
 LINK_ADJ( РЕЗКИЙ, HARSH )
 LINK_ADJ( РЕЗКИЙ, PUNGENT )
 LINK_ADJ( РЕЗКИЙ, ABRUPT )

 LINK_ADJ( ПЕРЕДНИЙ, FRONT )
 LINK_ADJ( БОЛЬНОЙ, ILL )
 LINK_ADJ( МАЛЕНЬКИЙ, SMALL )

 LINK_ADJ( СЧАСТЛИВЫЙ, HAPPY )
 LINK_ADJ( СОБСТВЕННЫЙ, OWN )
 LINK_ADJ( ДЕРЕВЯННЫЙ, WOODEN )
 LINK_ADJ( НЕПРИЯТНЫЙ, UNPLEASANT )
 LINK_ADJ( ДАЛЬНИЙ, FAR )
 LINK_ADJ( СЛАБЫЙ, WEAK )
 LINK_ADJ( СВЕЖИЙ, FRESH )
 LINK_ADJ( НЕЗНАКОМЫЙ, UNKNOWN )
 LINK_ADJ( НЕЛЕПЫЙ, STUPID )
 LINK_ADJ( НЕТЕРПЕЛИВЫЙ, IMPATIENT )
 LINK_ADJ( ГРЯЗНЫЙ, DIRTY )

 LINK_ADJ( УМНЫЙ, SMART )

 LINK_ADJ( НАДЕЖНЫЙ, RELIABLE )
 LINK_ADJ( НАДЕЖНЫЙ, SECURE )
 LINK_ADJ( НАДЕЖНЫЙ, SAFE )

 LINK_ADJ( СИНИЙ, BLUE )
 LINK_ADJ( РУССКИЙ, RUSSIAN )
 LINK_ADJ( СЕДОЙ, GREY )
 LINK_ADJ( ЖАРКИЙ, HOT )
 LINK_ADJ( ВИШНЕВЫЙ, CHERRY )

 LINK_ADJ( РУЧНОЙ, HAND )
 LINK_ADJ( РУЧНОЙ, TAME )

 LINK_ADJ( ЛИШНИЙ, EXTRA )
 LINK_ADJ( ЛИШНИЙ, SPARE )
 LINK_ADJ( ЛИШНИЙ, UNNECESARRY )

 LINK_ADJ( ПРОСТОРНЫЙ, ROOMY )
 LINK_ADJ( ДАЛЕКИЙ, FAR )
 LINK_ADJ( СКОРЫЙ, FAST )
 LINK_ADJ( ЖЕЛЕЗНЫЙ, IRON )
 LINK_ADJ( ПРОШЛЫЙ, LAST )
 LINK_ADJ( ПРОШЛЫЙ, PAST )

 LINK_ADJ( ОСТРЫЙ, SHARP )
 LINK_ADJ( ОСТРЫЙ, KIN )
 LINK_ADJ( ОСТРЫЙ, WITTY )
 LINK_ADJ( ОСТРЫЙ, PUNGENT )
 LINK_ADJ( ОСТРЫЙ, SPICY )
 LINK_ADJ( ОСТРЫЙ, ACUTE )

 LINK_ADJ( ПРЕЖНИЙ, FORMER )

 LINK_ADJ( СТРОГИЙ, STRICT )
 LINK_ADJ( СТРОГИЙ, SEVERE )
 LINK_ADJ( СТРОГИЙ, HARSH )

 LINK_ADJ( ЗЕЛЕНЫЙ,      GREEN )
 LINK_ADJ( ОБЩЕСТВЕННЫЙ, PUBLIC )
 LINK_ADJ( ЛУЧШИЙ,       GOOD )

 LINK_ADJ( ТОЛКОВЫЙ,   INTELLIGENT )
 LINK_ADJ( ТОЛКОВЫЙ,   CLEAR )

 LINK_ADJ( ДУРНОЙ,     NASTY )
 LINK_ADJ( ДУРНОЙ,     BAD )

 LINK_ADJ( БОГАТЫЙ,    REACH )
 LINK_ADJ( ПУСТОЙ,     SIMPLE )

 LINK_ADJ( ВЕРНЫЙ,     FAITHFUL )
 LINK_ADJ( ВЕРНЫЙ,     SURE )
 LINK_ADJ( ВЕРНЫЙ,     CORRECT )

 LINK_ADJ( ДОЛГИЙ,     LONG )
 LINK_ADJ( СМЕРТНЫЙ,   MORTAL )

 LINK_ADJ( СУРОВЫЙ,    BLEAK )
 LINK_ADJ( СУРОВЫЙ,    SEVERE )
 LINK_ADJ( СУРОВЫЙ,    TOUGH )
 LINK_ADJ( СУРОВЫЙ,    HARSH )
 LINK_ADJ( СУРОВЫЙ,    STERN )
 LINK_ADJ( СУРОВЫЙ,    COARSE )


 LINK_ADJ( ЦЕЛЫЙ,      WHOLE )
 LINK_ADJ( ЦЕЛЫЙ,      ENTIRE )
 LINK_ADJ( ЗОЛОТОЙ,    GOLDEN )
 LINK_ADJ( ПОЖИЛОЙ,    ELDERLY )
 LINK_ADJ( ПЛОХОЙ,     BAD )
 LINK_ADJ( БЕДНЫЙ,     POOR )
 LINK_ADJ( ВАЖНЫЙ,     IMPORTANT )
 LINK_ADJ( ВНУТРЕННИЙ, INTERNAL )
 LINK_ADJ( ЯСНЫЙ,      CLEAR )
 LINK_ADJ( РОЗОВЫЙ,    PINK )
 LINK_ADJ( ПРАВИЛЬНЫЙ, RIGHT )
 LINK_ADJ( ПРАВИЛЬНЫЙ, CORRECT )
 LINK_ADJ( ЛЕТНИЙ,     SUMMER )
 LINK_ADJ( ДНЕВНОЙ,    DAY )
 LINK_ADJ( НОЧНОЙ,     NIGHT )
 LINK_ADJ( СТАРЕНЬКИЙ, OLD )
 LINK_ADJ( СЛЕПОЙ,     BLIND )



 LINK_ADJ( ЛЮТЫЙ            , FIERCE )
 LINK_ADJ( ЛЮТЫЙ            , SEVERE )
 LINK_ADJ( НЕПОНЯТНЫЙ       , INCOMPREHENSIBLE )
 LINK_ADJ( ВЗРОСЛЫЙ         , ADULT )
 LINK_ADJ( ЖЕНСКИЙ          , FEMALE )
 LINK_ADJ( ПОТНЫЙ           , SWEATY )
 LINK_ADJ( БОСОЙ            , BAREFOOT )

 LINK_ADJ( БЛЕДНЫЙ          , PALE )
 LINK_ADJ( БЛЕДНЫЙ          , DULL ) 

 LINK_ADJ( ТЯЖКИЙ           , ARDUOUS )
 LINK_ADJ( ТЯЖКИЙ           , OPPRESSIVE )
 LINK_ADJ( ТЯЖКИЙ           , GRIM )
 LINK_ADJ( ТЯЖКИЙ           , GRAVE )

 LINK_ADJ( ДЕТСКИЙ          , CHILDISH )

 LINK_ADJ( ПЛОТНЫЙ          , DENSE )
 LINK_ADJ( ПЛОТНЫЙ          , THICK )

 LINK_ADJ( НЕЖНЫЙ           , TENDER )
 LINK_ADJ( НЕЖНЫЙ           , GENTLE )
 LINK_ADJ( ПОЗДНИЙ          , LATE )
 LINK_ADJ( УДОБНЫЙ          , COMFORTABLE )
 LINK_ADJ( ОБЫЧНЫЙ          , USUAL )
 LINK_ADJ( ОБЫЧНЫЙ          , ORDINARY )

 LINK_ADJ( КРЕПКИЙ          , STRONG )
 LINK_ADJ( КРЕПКИЙ          , HARD )

 LINK_ADJ( СЕРЕБРЯНЫЙ       , SILVER )
 LINK_ADJ( ПОЛИТИЧЕСКИЙ     , POLITICAL )

 LINK_ADJ( КРУТОЙ           , STEEP )
 LINK_ADJ( КРУТОЙ           , SHARP )
 LINK_ADJ( КРУТОЙ           , HARSH )

 LINK_ADJ( ЕДИНСТВЕННЫЙ     , ONLY )
 LINK_ADJ( ПОКОРНЫЙ         , SUBMISSIVE )
 LINK_ADJ( ПРИЯТНЫЙ         , PLEASANT )
 LINK_ADJ( ПРИЯТНЫЙ         , ENJOYABLE )
 LINK_ADJ( СЕРЬЕЗНЫЙ        , SERIOUS )

 LINK_ADJ( КРУПНЫЙ          , COARSE )
 LINK_ADJ( КРУПНЫЙ          , LARGE )
 LINK_ADJ( КРУПНЫЙ          , GREAT )
 LINK_ADJ( КРУПНЫЙ          , PROMINENT )
 LINK_ADJ( КРУПНЫЙ          , MAJOR )

 LINK_ADJ( ВЕСЕННИЙ         , SPRING )
 LINK_ADJ( СПЛОШНОЙ         , CONTINUOUS )
 LINK_ADJ( СПЛОШНОЙ         , UNIVERSAL  )
 LINK_ADJ( СПЛОШНОЙ         , UTTER      )


 LINK_ADJ( СЕЙ              , THIS )
 LINK_ADJ( СЫТЫЙ            , FULL )

 LINK_ADJ( ПРЕСНЫЙ          , FRESH )
 LINK_ADJ( ПРЕСНЫЙ          , BLAND )


 LINK_ADJ( СЕМЕЙНЫЙ         , FAMILY ) 
 LINK_ADJ( ГУСИНЫЙ          , GOOSE )
 LINK_ADJ( ТРУДНЫЙ          , DIFFICULT )
 LINK_ADJ( ДИКИЙ            , WILD )
 LINK_ADJ( НЕВИДИМЫЙ        , INVISIBLE )
 LINK_ADJ( ОКОННЫЙ          , WINDOW )
 LINK_ADJ( ДРЕВНИЙ          , ANCIENT )
 LINK_ADJ( ВИНОВАТЫЙ        , GUILTY )
 LINK_ADJ( ВИНОВАТЫЙ        , RESPONSIBLE )
 LINK_ADJ( СУМЕРЕЧНЫЙ       , TWILIGHT )
 LINK_ADJ( КОРИЧНЕВЫЙ       , BROWN )
 LINK_ADJ( ОТВАЖНЫЙ         , BRAVE )
 LINK_ADJ( ПРОПАЩИЙ         , HOPELESS )
 LINK_ADJ( ОБИДНЫЙ          , OFFENSIVE )
 LINK_ADJ( ЗИМНИЙ           , WINTER )
 LINK_ADJ( ВЛАЖНЫЙ          , WET )
 LINK_ADJ( РЫЖИЙ            , RED )

 LINK_ADJ( МУЖСКОЙ          , MASCULINE )
 LINK_ADJ( МУЖСКОЙ          , MALE )

 LINK_ADJ( ГОЛОДНЫЙ         , HUNGRY )
 LINK_ADJ( КУРИНЫЙ          , CHICKEN )
 LINK_ADJ( ВОЛЬНЫЙ          , FREE )

 LINK_ADJ( ЛИЧНЫЙ           , PERSONAL )
 LINK_ADJ( ЛИЧНЫЙ           , PRIVATE )

 LINK_ADJ( ЗАДНИЙ           , BACK )
 LINK_ADJ( ВСТРЕЧНЫЙ        , COUNTER )

 LINK_ADJ( СВЯТОЙ           , HOLY )
 LINK_ADJ( СВЯТОЙ           , SAINT )                       

 LINK_ADJ( ЕДИНЫЙ           , COMMON )
 LINK_ADJ( ЕДИНЫЙ           , SINGLE )

 LINK_ADJ( ФАКТИЧЕСКИЙ      , FACTUAL )
 LINK_ADJ( ФАКТИЧЕСКИЙ      , REAL    )
 LINK_ADJ( ФАКТИЧЕСКИЙ      , ACTUAL  )

 LINK_ADJ( НАИВНЫЙ          , NAIVE   )

 LINK_ADJ( БЕШЕНЫЙ          , FURIOUS )
 LINK_ADJ( БЕШЕНЫЙ          , VIOLENT )
 LINK_ADJ( БЕШЕНЫЙ          , CRAZY   )


 LINK_ADJ( ЯВНЫЙ            , EXPLICIT )
 LINK_ADJ( МИРОВОЙ          , WORLD    )
 LINK_ADJ( АНГЛИЙСКИЙ       , ENGLISH  )

 LINK_ADJ( КУЛЬТУРНЫЙ       , CULTURAL )

 LINK_ADJ( ЖАЛКИЙ           , PITIFUL )
 LINK_ADJ( ЖАЛКИЙ           , PATHETIC )
 LINK_ADJ( ЖАЛКИЙ           , SHABBY )


 LINK_ADJ( ОДИНОКИЙ         , SINGLE )
 LINK_ADJ( ОДИНОКИЙ         , LONELY )

 LINK_ADJ( СВЕТЛЫЙ          , BRIGHT )
 LINK_ADJ( СВЕТЛЫЙ          , LIGHT  ) 


 // ------------------------------------

 LINK_ADJ( РЯДОВОЙ          , ORDINARY )
 LINK_ADJ( ПОСТОЯННЫЙ       , CONSTANT )
 LINK_ADJ( НЕБОЛЬШОЙ        , SMALL    ) 
 LINK_ADJ( ОБЫКНОВЕННЫЙ     , USUAL    )

 LINK_ADJ( ТУСКЛЫЙ          , OPAQUE   )
 LINK_ADJ( ТУСКЛЫЙ          , MATT     )
 LINK_ADJ( ТУСКЛЫЙ          , DULL     )

 LINK_ADJ( НЕИЗВЕСТНЫЙ      , UNKNOWN  )

 LINK_ADJ( ПОСТОРОННИЙ      , STRANGE )
 LINK_ADJ( ПОСТОРОННИЙ      , OUTSIDE )
 LINK_ADJ( ПОСТОРОННИЙ      , IRRELEVANT )

 LINK_ADJ( ЕДИНОЛИЧНЫЙ      , INDIVIDUAL )
 LINK_ADJ( ВЫХОДНОЙ         , EXIT )       

 LINK_ADJ( ГОЛОВНОЙ         , HEAD )
 LINK_ADJ( ГОЛОВНОЙ         , FRONT )
 LINK_ADJ( ГОЛОВНОЙ         , MAIN )

 LINK_ADJ( ЗДОРОВЫЙ         , HEALTHY )
 LINK_ADJ( ЗДОРОВЫЙ         , WHOLESOME )
 LINK_ADJ( ЗДОРОВЫЙ         , HEFTY )

 LINK_ADJ( СОЛЕНЫЙ          , SALTY )
 LINK_ADJ( СОЛЕНЫЙ          , SALT  )
 
 LINK_ADJ( ЧЕРТОВЫЙ         , DAMN )
 LINK_ADJ( ЗАЖИТОЧНЫЙ       , PROSPEROUS )
 LINK_ADJ( ТОРЖЕСТВЕННЫЙ    , SPECIAL )
 LINK_ADJ( КРОХОТНЫЙ        , TINY )
 LINK_ADJ( ЖАДНЫЙ           , GREEDY )

 LINK_ADJ( СКУДНЫЙ          , MEAGRE )
 LINK_ADJ( СКУДНЫЙ          , MEAGER )
 LINK_ADJ( СКУДНЫЙ          , SPARSE )

 LINK_ADJ( ПОЛЬСКИЙ         , POLISH )

 LINK_ADJ( РЕДКИЙ           , RARE )
 LINK_ADJ( РЕДКИЙ           , OCCASIONAL )
 LINK_ADJ( РЕДКИЙ           , THIN )
 LINK_ADJ( РЕДКИЙ           , GAPPY )
 LINK_ADJ( РЕДКИЙ           , SPARSE )

 LINK_ADJ( НЕИСТОВЫЙ        , INTENSE ) 
 LINK_ADJ( НЕИСТОВЫЙ        , WILD ) 

 LINK_ADJ( ОТЧАЯННЫЙ        , DESPERATE )
 LINK_ADJ( ХУДОЙ            , THIN )
 LINK_ADJ( ХУДОЙ            , BAD )
 LINK_ADJ( ГРЕШНЫЙ          , SINFUL )

 LINK_ADJ( СОЛНЕЧНЫЙ        , SOLAR )
 LINK_ADJ( СОЛНЕЧНЫЙ        , SUNNY )

 LINK_ADJ( МНОГИЙ           , MANY )
 LINK_ADJ( ОПАСНЫЙ          , DANGEROUS )

 LINK_ADJ( ВЕЧНЫЙ           , ETERNAL )
 LINK_ADJ( ВЕЧНЫЙ           , INDEFINITE )
 LINK_ADJ( ВЕЧНЫЙ           , PERPETUAL )

 LINK_ADJ( НУЖНЫЙ           , NECESSARY )

 LINK_ADJ( МОЩНЫЙ           , POWERFUL )
 LINK_ADJ( МОЩНЫЙ           , MIGHTY )
 LINK_ADJ( МОЩНЫЙ           , VIGOROUS )
 LINK_ADJ( МОЩНЫЙ           , MASSIVE )

 LINK_ADJ( НЕОБЫЧНЫЙ        , UNUSUAL )
 LINK_ADJ( БУРЫЙ            , BROWN )

 LINK_ADJ( НЕДОБРЫЙ         , UNKIND )
 LINK_ADJ( НЕДОБРЫЙ         , ILL )
 LINK_ADJ( НЕДОБРЫЙ         , BAD )

 LINK_ADJ( ГОРОДСКОЙ        , URBAN )
 LINK_ADJ( ГОРОДСКОЙ        , MUNICIPAL )

 LINK_ADJ( ОТВЕТСТВЕННЫЙ    , RESPONSIBLE )
 LINK_ADJ( ОТВЕТСТВЕННЫЙ    , IMPORTANT )

 LINK_ADJ( ОТЛИЧНЫЙ         , EXCELLENT )




 // ----------------------------------------------------------------------

 link СУЩЕСТВИТЕЛЬНОЕ:ГЛАЗ {} <to_english> ENG_NOUN:EYE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВРЕМЯ {} <to_english> ENG_NOUN:TIME {}
 link СУЩЕСТВИТЕЛЬНОЕ:РУКА {} <to_english> ENG_NOUN:HAND {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЖИЗНЬ {} <to_english> ENG_NOUN:LIFE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЧЕЛОВЕК {} <to_english> ENG_NOUN:HUMAN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЧЕЛОВЕК {} <to_english> ENG_NOUN:MAN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДВЕРЬ {} <to_english> ENG_NOUN:DOOR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДЕЛО {} <to_english> ENG_NOUN:AFFAIR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДЕЛО {} <to_english> ENG_NOUN:BUSSINESS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДЕЛО {} <to_english> ENG_NOUN:BUSINESS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛИЦО { одуш:неодуш } <to_english> ENG_NOUN:FACE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЛОВО {} <to_english> ENG_NOUN:WORD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГОЛОВА {} <to_english> ENG_NOUN:HEAD {}
 link СУЩЕСТВИТЕЛЬНОЕ:МЕСТО {} <to_english> ENG_NOUN:PLACE {}
 link СУЩЕСТВИТЕЛЬНОЕ:люд {} <to_english> ENG_NOUN:PEOPLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДОМ {} <to_english> ENG_NOUN:HOUSE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДОМ {} <to_english> ENG_NOUN:HOME {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТОРОНА {} <to_english> ENG_NOUN:SIDE {}
 link СУЩЕСТВИТЕЛЬНОЕ:МЫСЛЬ {} <to_english> ENG_NOUN:THOUGHT {}
 link СУЩЕСТВИТЕЛЬНОЕ:МЫСЛЬ {} <to_english> ENG_NOUN:IDEA {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГОЛОС {} <to_english> ENG_NOUN:VOICE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗЕМЛЯ {} <to_english> ENG_NOUN:LAND {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗЕМЛЯ {} <to_english> ENG_NOUN:EARTH {}
 link СУЩЕСТВИТЕЛЬНОЕ:НОГА {} <to_english> ENG_NOUN:LEG {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДРУГ {} <to_english> ENG_NOUN:FRIEND {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДРУЖБА {} <to_english> ENG_NOUN:FRIENDSHIP {}
 link СУЩЕСТВИТЕЛЬНОЕ:СМЕРТЬ {} <to_english> ENG_NOUN:DEATH {}
 link СУЩЕСТВИТЕЛЬНОЕ:МИСС {} <to_english> ENG_NOUN:MISS {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТАЛЬ {} <to_english> ENG_NOUN:STEEL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОТ {} <to_english> ENG_NOUN:SWEAT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГОД {} <to_english> ENG_NOUN:YEAR {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТЕНА {} <to_english> ENG_NOUN:WALL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВОДА {} <to_english> ENG_NOUN:WATER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЧАСТЬ {} <to_english> ENG_NOUN:PART {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЧАСТОТА {} <to_english> ENG_NOUN:FREQUENCY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЧАЙ {} <to_english> ENG_NOUN:TEA {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЦИФРА {} <to_english> ENG_NOUN:DIGIT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЦИТАТА {} <to_english> ENG_NOUN:QUOTATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТЕЛО {} <to_english> ENG_NOUN:BODY {}
 link СУЩЕСТВИТЕЛЬНОЕ:СИЛА {} <to_english> ENG_NOUN:FORCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СИЛА {} <to_english> ENG_NOUN:FORCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛЕДИ {} <to_english> ENG_NOUN:LADY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГОРОД {} <to_english> ENG_NOUN:CITY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГОРОД {} <to_english> ENG_NOUN:TOWN {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОМНАТА {} <to_english> ENG_NOUN:ROOM {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОЛНЦЕ {} <to_english> ENG_NOUN:SUN {}
 link СУЩЕСТВИТЕЛЬНОЕ:СВЕТ {} <to_english> ENG_NOUN:LIGHT {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОНЕЦ {} <to_english> ENG_NOUN:END {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОРАБЛЬ {} <to_english> ENG_NOUN:SHIP {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЧАС {} <to_english> ENG_NOUN:HOUR {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАШИНА {} <to_english> ENG_NOUN:MACHINE {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАШИНА {} <to_english> ENG_NOUN:CAR {}
 link СУЩЕСТВИТЕЛЬНОЕ:КРОВЬ {} <to_english> ENG_NOUN:BLOOD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЖЕНЩИНА {} <to_english> ENG_NOUN:WOMAN {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОФЕ {} <to_english> ENG_NOUN:COFEE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВОПРОС {} <to_english> ENG_NOUN:QUESTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИМЯ {} <to_english> ENG_NOUN:NAME {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДОРОГА {} <to_english> ENG_NOUN:ROAD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДОРОГА {} <to_english> ENG_NOUN:WAY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВИД {} <to_english> ENG_NOUN:VIEW {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГРУДЬ {} <to_english> ENG_NOUN:BREAST {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАБОТА {} <to_english> ENG_NOUN:WORK {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВОЗМОЖНОСТЬ {} <to_english> ENG_NOUN:POSSIBILITY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЛ {} <to_english> ENG_NOUN:SEX {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВНИМАНИЕ {} <to_english> ENG_NOUN:ATTENTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:МИНУТА {} <to_english> ENG_NOUN:MINUTE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВОЗДУХ {} <to_english> ENG_NOUN:AIR {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАТЬ {} <to_english> ENG_NOUN:MOTHER {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЕРДЦЕ {} <to_english> ENG_NOUN:HEART {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЛАНЕТА {} <to_english> ENG_NOUN:PLANET {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОМОЩЬ {} <to_english> ENG_NOUN:HELP {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОКНО {} <to_english> ENG_NOUN:WINDOW {}
 link СУЩЕСТВИТЕЛЬНОЕ:МОРЕ {} <to_english> ENG_NOUN:SEA {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТЕНЬ {} <to_english> ENG_NOUN:SHADOW {}
 link СУЩЕСТВИТЕЛЬНОЕ:СВЯЗЬ {} <to_english> ENG_NOUN:LINK {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛЕТО {} <to_english> ENG_NOUN:SUMMER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛЕС {} <to_english> ENG_NOUN:FOREST {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАМЯТЬ {} <to_english> ENG_NOUN:MEMORY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИСТОРИЯ {} <to_english> ENG_NOUN:HISTORY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРАВО {} <to_english> ENG_NOUN:right {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТЕЦ {} <to_english> ENG_NOUN:FATHER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЛЕ {} <to_english> ENG_NOUN:FIELD {}
 link СУЩЕСТВИТЕЛЬНОЕ:МОМЕНТ {} <to_english> ENG_NOUN:MOMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДУША {} <to_english> ENG_NOUN:SOUL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДУША {} <to_english> ENG_NOUN:SURFACE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОВЕРХНОСТЬ {} <to_english> ENG_NOUN:SURFACE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЦЕЛЬ {} <to_english> ENG_NOUN:AIM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЦЕЛЬ {} <to_english> ENG_NOUN:TARGET {}
 link СУЩЕСТВИТЕЛЬНОЕ:КАМЕНЬ {} <to_english> ENG_NOUN:STOWN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТВЕТ {} <to_english> ENG_NOUN:ANSWER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДЕНЬГА {} <to_english> ENG_NOUN:MONEY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЛАСТЬ {} <to_english> ENG_NOUN:POWER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГУБА {} <to_english> ENG_NOUN:LIP {}
 link СУЩЕСТВИТЕЛЬНОЕ:УЛИЦА {} <to_english> ENG_NOUN:STREET {}
 link СУЩЕСТВИТЕЛЬНОЕ:БЕРЕГ {} <to_english> ENG_NOUN:SHORE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОРУЖИЕ {} <to_english> ENG_NOUN:ARM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГОРА {} <to_english> ENG_NOUN:MOUNTAIN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШАГ {} <to_english> ENG_NOUN:STEP {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛАДОНЬ {} <to_english> ENG_NOUN:PALM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРАВДА {} <to_english> ENG_NOUN:TRUTH {}
 link СУЩЕСТВИТЕЛЬНОЕ:МУЖЧИНА {} <to_english> ENG_NOUN:MAN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДЕРЕВО {} <to_english> ENG_NOUN:TREE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДЕВУШКА {} <to_english> ENG_NOUN:GIRL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛОШАДЬ {} <to_english> ENG_NOUN:HORSE {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАДАМ {} <to_english> ENG_NOUN:MADAM {}
 link СУЩЕСТВИТЕЛЬНОЕ:СПИНА {} <to_english> ENG_NOUN:BACK {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДВИЖЕНИЕ {} <to_english> ENG_NOUN:MOTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЕТЕР {} <to_english> ENG_NOUN:WIND {}
 link СУЩЕСТВИТЕЛЬНОЕ:КРОВАТЬ {} <to_english> ENG_NOUN:BED {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОГОНЬ {} <to_english> ENG_NOUN:FIRE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗВУК {} <to_english> ENG_NOUN:SOUND {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВОЙНА {} <to_english> ENG_NOUN:WAR {}
 link СУЩЕСТВИТЕЛЬНОЕ:КРЕСЛО {} <to_english> ENG_NOUN:CHAIR {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАЗГОВОР {} <to_english> ENG_NOUN:CONVERSATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗВЕЗДА {} <to_english> ENG_NOUN:STAR {}
 link СУЩЕСТВИТЕЛЬНОЕ:РЕКА {} <to_english> ENG_NOUN:RIVER {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАДИО {} <to_english> ENG_NOUN:RADIO {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОРОЛЬ {} <to_english> ENG_NOUN:KING {}
 link СУЩЕСТВИТЕЛЬНОЕ:УДАР {} <to_english> ENG_NOUN:STRIKE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТРАНА {} <to_english> ENG_NOUN:COUNTRY {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТРАНА {} <to_english> ENG_NOUN:STATE {}
 link СУЩЕСТВИТЕЛЬНОЕ:РЕБЕНОК {} <to_english> ENG_NOUN:CHILD {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОН {} <to_english> ENG_NOUN:DREAM {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОСТЬ {} <to_english> ENG_NOUN:BONE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СИСТЕМА {} <to_english> ENG_NOUN:SYSTEM {}
 link СУЩЕСТВИТЕЛЬНОЕ:СКОРОСТЬ {} <to_english> ENG_NOUN:SPEED {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТАКСИ {} <to_english> ENG_NOUN:TAXI {}
 link СУЩЕСТВИТЕЛЬНОЕ:МОЗГ {} <to_english> ENG_NOUN:BRAIN {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЕКУНДА {} <to_english> ENG_NOUN:SECOND {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФОРМА {} <to_english> ENG_NOUN:FORM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДОКТОР { род:муж } <to_english> ENG_NOUN:DOCTOR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЖИВОТНОЕ {} <to_english> ENG_NOUN:ANIMAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТЕМНОТА {} <to_english> ENG_NOUN:DARKNESS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОЧЕРЕДЬ {} <to_english> ENG_NOUN:QUEUE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЛОЖЕНИЕ {} <to_english> ENG_NOUN:SITUATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЖЕЛАНИЕ {} <to_english> ENG_NOUN:WISH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДЕЙСТВИЕ {} <to_english> ENG_NOUN:ACTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАЛЬЧИК {} <to_english> ENG_NOUN:BOY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВИНО {} <to_english> ENG_NOUN:WINE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЛОЩАДЬ {} <to_english> ENG_NOUN:SQUARE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЛИЦИЯ {} <to_english> ENG_NOUN:POLICE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЖЕНА {} <to_english> ENG_NOUN:WIFE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТОЧКА {} <to_english> ENG_NOUN:POINT {}
 link СУЩЕСТВИТЕЛЬНОЕ:РЕШЕНИЕ {} <to_english> ENG_NOUN:SOLUTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОСТРАНСТВО {} <to_english> ENG_NOUN:SPACE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГРУППА {} <to_english> ENG_NOUN:GROUP {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗДАНИЕ {} <to_english> ENG_NOUN:BUILDING {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЛАНШЕТ {} <to_english> ENG_NOUN:PLAN {}
 link СУЩЕСТВИТЕЛЬНОЕ:СКАЛА {} <to_english> ENG_NOUN:ROCK {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОРЯДОК {} <to_english> ENG_NOUN:ORDER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВОЛНА {} <to_english> ENG_NOUN:WAVE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЕК {} <to_english> ENG_NOUN:CENTURY {}
 link СУЩЕСТВИТЕЛЬНОЕ:КРИК {} <to_english> ENG_NOUN:SCREAM {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАРОД {} <to_english> ENG_NOUN:PEOPLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВСЕЛЕННАЯ {} <to_english> ENG_NOUN:UNIVERSE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПИСЬМО {} <to_english> ENG_NOUN:LETTER {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАДЕЖДА {} <to_english> ENG_NOUN:HOPE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЭР {} <to_english> ENG_NOUN:SIR {}
 link СУЩЕСТВИТЕЛЬНОЕ:СИТУАЦИЯ {} <to_english> ENG_NOUN:SITUATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЫН {} <to_english> ENG_NOUN:SON {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЫН {} <to_english> ENG_NOUN:LABORATORY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОБЛЕМА {} <to_english> ENG_NOUN:PROBLEM {}
 link СУЩЕСТВИТЕЛЬНОЕ:УЛЫБКА {} <to_english> ENG_NOUN:SMILE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СМЫСЛ {} <to_english> ENG_NOUN:MEANING {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГЛУБИНА {} <to_english> ENG_NOUN:DEPTH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТРАВА {} <to_english> ENG_NOUN:GRASS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВРАГ {} <to_english> ENG_NOUN:ENEMY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИГРА {} <to_english> ENG_NOUN:PLAY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИГРА {} <to_english> ENG_NOUN:GAME {}
 link СУЩЕСТВИТЕЛЬНОЕ:КРУГ {} <to_english> ENG_NOUN:CIRCLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗНАК {} <to_english> ENG_NOUN:SIGN {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОЖА {} <to_english> ENG_NOUN:SKIN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГОСТЬ {} <to_english> ENG_NOUN:GUEST {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАРА {} <to_english> ENG_NOUN:PAIR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЫЛЬ {} <to_english> ENG_NOUN:DUST {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАКОН {} <to_english> ENG_NOUN:LAW {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВОИН {} <to_english> ENG_NOUN:WARRIOR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛУНА {} <to_english> ENG_NOUN:MOON {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОПЕРАЦИЯ {} <to_english> ENG_NOUN:OPERATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВОРОТА {} <to_english> ENG_NOUN:GATE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФИГУРА {} <to_english> ENG_NOUN:FIGURE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШУМ {} <to_english> ENG_NOUN:NOISE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАПИСЬ {} <to_english> ENG_NOUN:RECORD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЦЕНТР {} <to_english> ENG_NOUN:CENTER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДЕВОЧКА {} <to_english> ENG_NOUN:GIRL {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОМАНДА {} <to_english> ENG_NOUN:COMMAND {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОМАНДА {} <to_english> ENG_NOUN:TEAM {}
 link СУЩЕСТВИТЕЛЬНОЕ:КИНО {} <to_english> ENG_NOUN:CINEMA {}
 link СУЩЕСТВИТЕЛЬНОЕ:КИНО {} <to_english> ENG_NOUN:FILM {}
 link СУЩЕСТВИТЕЛЬНОЕ:КИНО {} <to_english> ENG_NOUN:MOVIE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЦЕПЬ {} <to_english> ENG_NOUN:CHAIN {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЛУЖБА {} <to_english> ENG_NOUN:SERVICE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЫХОД {} <to_english> ENG_NOUN:EXIT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДОЖДЬ {} <synonym> ENG_NOUN:RAIN {}
 link СУЩЕСТВИТЕЛЬНОЕ:НОЖ {} <synonym> ENG_NOUN:KNIFE {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАСТЕР {} <synonym> ENG_NOUN:MASTER {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАССТОЯНИЕ {} <synonym> ENG_NOUN:DISTANCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:УБИЙСТВО {} <synonym> ENG_NOUN:MURDER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИКАЗ {} <synonym> ENG_NOUN:ORDER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБЛАСТЬ {} <synonym> ENG_NOUN:REGION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБЛАСТЬ {} <synonym> ENG_NOUN:AREA {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГОЛОВА {} <synonym> ENG_NOUN:HEAD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОФЕССОР {} <synonym> ENG_NOUN:PROFESSOR {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОНЬ {} <synonym> ENG_NOUN:HORSE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГОСПОДЬ {} <synonym> ENG_NOUN:GOD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛИЧНОСТЬ {} <synonym> ENG_NOUN:PERSON {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЛОВИНА {} <synonym> ENG_NOUN:HALF {}
 link СУЩЕСТВИТЕЛЬНОЕ:РЕЗУЛЬТАТ {} <synonym> ENG_NOUN:RESULT {}
 link СУЩЕСТВИТЕЛЬНОЕ:МНЕНИЕ {} <synonym> ENG_NOUN:OPINION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЦИВИЛИЗАЦИЯ {} <synonym> ENG_NOUN:CIVILISATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛОРД {} <synonym> ENG_NOUN:LORD {}


 // ----------------------------------------------------------

 link СУЩЕСТВИТЕЛЬНОЕ:ДНО {} <to_english> ENG_NOUN:BOTTOM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДЕТАЛЬ {} <to_english> ENG_NOUN:DETAIL {}
 link СУЩЕСТВИТЕЛЬНОЕ:КАБИНЕТ {} <to_english> ENG_NOUN:КАБИНЕТ {}
 link СУЩЕСТВИТЕЛЬНОЕ:УЧЕНЫЙ {} <to_english> ENG_NOUN:SCIENTIST {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЕСОК {} <to_english> ENG_NOUN:SAND {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАГИЯ {} <to_english> ENG_NOUN:MAGIC {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШКОЛА {} <to_english> ENG_NOUN:SCHOOL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФАКТ {} <to_english> ENG_NOUN:FACT {}
 link СУЩЕСТВИТЕЛЬНОЕ:СООБЩЕНИЕ {} <to_english> ENG_NOUN:MESSAGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СООБЩЕНИЕ {} <to_english> ENG_NOUN:KNOWLEDGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЧЕЛОВЕЧЕСТВО {} <to_english> ENG_NOUN:MANKIND {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДЕЙСТВИТЕЛЬНОСТЬ {} <to_english> ENG_NOUN:REALITY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЯЩИК {} <to_english> ENG_NOUN:BOX {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЯПОНИЯ {} <to_english> ENG_NOUN:JAPAN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЯЙЦО {} <to_english> ENG_NOUN:EGG {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЯЗЫК {} <to_english> ENG_NOUN:LANGUAGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЯЗЫК {} <to_english> ENG_NOUN:TONGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЯД {} <to_english> ENG_NOUN:POISON {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЯБЛОКО {} <to_english> ENG_NOUN:APPLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЮПИТЕР {} <to_english> ENG_NOUN:JUPITER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЮМОР {} <to_english> ENG_NOUN:HUMOR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЮГ {} <to_english> ENG_NOUN:SOUTH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЮБКА {} <to_english> ENG_NOUN:SKIRT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭХО {} <to_english> ENG_NOUN:ECHO {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭФФЕКТ {} <to_english> ENG_NOUN:EFFECT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭТАЖ {} <to_english> ENG_NOUN:FLOOR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭМОЦИЯ {} <to_english> ENG_NOUN:EMOTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭМИССИЯ {} <to_english> ENG_NOUN:EMISSION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭЛЕМЕНТ {} <to_english> ENG_NOUN:ELEMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭЛЕКТРОН {} <to_english> ENG_NOUN:ELECTRON {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭЛЕКТРИЧЕСТВО {} <to_english> ENG_NOUN:ELECTRICITY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭКСТРЕМУМ {} <to_english> ENG_NOUN:EXTREMUM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭКСПОРТ {} <to_english> ENG_NOUN:EXPORT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭКСПЕРТ {} <to_english> ENG_NOUN:EXPERT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭКСПЕРИМЕНТ {} <to_english> ENG_NOUN:EXPERIMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭВОЛЮЦИЯ {} <to_english> ENG_NOUN:EVOLUTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭВАКУАЦИЯ {} <to_english> ENG_NOUN:EVACUATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШУТОЧКА {} <to_english> ENG_NOUN:JOKE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШУТКА {} <to_english> ENG_NOUN:JOKE {}
 link СУЩЕСТВИТЕЛЬНОЕ:АБРИКОС {} <to_english> ENG_NOUN:APRICOT {}
 link СУЩЕСТВИТЕЛЬНОЕ:АВАРИЯ {} <to_english> ENG_NOUN:ACCIDENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:АВИАЦИЯ {} <to_english> ENG_NOUN:AVIATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:АВТОБУС {} <to_english> ENG_NOUN:BUS {}
 link СУЩЕСТВИТЕЛЬНОЕ:АВТОГРАФ {} <to_english> ENG_NOUN:AUTOGRAPH {}
 link СУЩЕСТВИТЕЛЬНОЕ:АВТОМОБИЛЬ {} <to_english> ENG_NOUN:AUTOMOBILE {}
 link СУЩЕСТВИТЕЛЬНОЕ:АВТОНОМИЯ {} <to_english> ENG_NOUN:AUTONOMY {}
 link СУЩЕСТВИТЕЛЬНОЕ:АВТОР {} <to_english> ENG_NOUN:AUTHOR {}
 link СУЩЕСТВИТЕЛЬНОЕ:АВТОРИТЕТ {} <to_english> ENG_NOUN:AUTHORITY {}
 link СУЩЕСТВИТЕЛЬНОЕ:АВТОРИТЕТ {} <to_english> ENG_NOUN:PRESTIGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:АГЕНТСТВО {} <to_english> ENG_NOUN:AGENCY {}
 link СУЩЕСТВИТЕЛЬНОЕ:АГИТАЦИЯ {} <to_english> ENG_NOUN:PROPAGANDA {}
 link СУЩЕСТВИТЕЛЬНОЕ:АГИТАТОР {} <to_english> ENG_NOUN:PROPAGANDIST {}
 link СУЩЕСТВИТЕЛЬНОЕ:АГРЕССИЯ {} <to_english> ENG_NOUN:AGGRESSION {}
 link СУЩЕСТВИТЕЛЬНОЕ:АГРЕССОР {} <to_english> ENG_NOUN:AGGRESSOR {}
 link СУЩЕСТВИТЕЛЬНОЕ:АГРОНОМ {} <to_english> ENG_NOUN:AGGRONOMIST {}
 link СУЩЕСТВИТЕЛЬНОЕ:АГРОНОМИЯ {} <to_english> ENG_NOUN:AGGRONOMY {}
 link СУЩЕСТВИТЕЛЬНОЕ:АД {} <to_english> ENG_NOUN:HELL {}
 link СУЩЕСТВИТЕЛЬНОЕ:АДВОКАТ {} <to_english> ENG_NOUN:LAWYER {}
 link СУЩЕСТВИТЕЛЬНОЕ:АДВОКАТ {} <to_english> ENG_NOUN:ADVOCATE {}
 link СУЩЕСТВИТЕЛЬНОЕ:АДВОКАТ {} <to_english> ENG_NOUN:BARRISTER {}
 link СУЩЕСТВИТЕЛЬНОЕ:АДВОКАТ {} <to_english> ENG_NOUN:ATTORNEY {}
 link СУЩЕСТВИТЕЛЬНОЕ:АДМИНИСТРАТОР {} <to_english> ENG_NOUN:ADMINISTRATOR {}
 link СУЩЕСТВИТЕЛЬНОЕ:АДМИНИСТРАЦИЯ {} <to_english> ENG_NOUN:ADMINISTRATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:АДМИРАЛ {} <to_english> ENG_NOUN:ADMIRAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:АЗБУКА {} <to_english> ENG_NOUN:abc {}
 link СУЩЕСТВИТЕЛЬНОЕ:АЗБУКА {} <to_english> ENG_NOUN:alphabet {}
 link СУЩЕСТВИТЕЛЬНОЕ:АДРЕС {} <to_english> ENG_NOUN:address {}
 link СУЩЕСТВИТЕЛЬНОЕ:АЗИЯ {} <to_english> ENG_NOUN:ASIA {}
 link СУЩЕСТВИТЕЛЬНОЕ:АЗОТ {} <to_english> ENG_NOUN:NITROGENE {}
 link СУЩЕСТВИТЕЛЬНОЕ:АИСТ {} <to_english> ENG_NOUN:STORK {}
 link СУЩЕСТВИТЕЛЬНОЕ:АКАДЕМИЯ {} <to_english> ENG_NOUN:ACADEMY {}
 link СУЩЕСТВИТЕЛЬНОЕ:АКВАЛАНГ {} <to_english> ENG_NOUN:SCUBA {}
 link СУЩЕСТВИТЕЛЬНОЕ:АКВАЛАНГ {} <to_english> ENG_NOUN:AQUALUNG {}
 link СУЩЕСТВИТЕЛЬНОЕ:АККОМПАНЕМЕНТ {} <to_english> ENG_NOUN:ACCOMPANIMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:АККОРДЕОН {} <to_english> ENG_NOUN:ACCORDION {}
 link СУЩЕСТВИТЕЛЬНОЕ:АКРОБАТ {} <to_english> ENG_NOUN:ACROBAT {}
 link СУЩЕСТВИТЕЛЬНОЕ:АКТ {} <to_english> ENG_NOUN:ACT {}
 link СУЩЕСТВИТЕЛЬНОЕ:АКТЕР {} <to_english> ENG_NOUN:ACTOR {}
 link СУЩЕСТВИТЕЛЬНОЕ:АКТИВНОСТЬ {} <to_english> ENG_NOUN:ACTIVITY {}
 link СУЩЕСТВИТЕЛЬНОЕ:АКТРИСА {} <to_english> ENG_NOUN:ACTRESS {}
 link СУЩЕСТВИТЕЛЬНОЕ:АКУЛА {} <to_english> ENG_NOUN:SHARK {}
 link СУЩЕСТВИТЕЛЬНОЕ:АКЦЕНТ {} <to_english> ENG_NOUN:ACCENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:АКЦИЯ {} <to_english> ENG_NOUN:SHARE {}
 link СУЩЕСТВИТЕЛЬНОЕ:АЛКОГОЛЬ {} <to_english> ENG_NOUN:ALCOHOL {}
 link СУЩЕСТВИТЕЛЬНОЕ:АЛЛЕЯ {} <to_english> ENG_NOUN:ALLEY {}
 link СУЩЕСТВИТЕЛЬНОЕ:АЛЛЕЯ {} <to_english> ENG_NOUN:AVENUE {}
 link СУЩЕСТВИТЕЛЬНОЕ:АЛМАЗ {} <to_english> ENG_NOUN:DIAMOND {}
 link СУЩЕСТВИТЕЛЬНОЕ:АЛТАРЬ {} <to_english> ENG_NOUN:ALTAR {}
 link СУЩЕСТВИТЕЛЬНОЕ:АЛФАВИТ {} <to_english> ENG_NOUN:ABC {}
 link СУЩЕСТВИТЕЛЬНОЕ:АЛФАВИТ {} <to_english> ENG_NOUN:ALPHABET {}
 link СУЩЕСТВИТЕЛЬНОЕ:АМНИСТИЯ {} <to_english> ENG_NOUN:AMNESTY {}
 link СУЩЕСТВИТЕЛЬНОЕ:АНАЛИЗ {} <to_english> ENG_NOUN:ANALYSIS {}
 link СУЩЕСТВИТЕЛЬНОЕ:АНАТОМИЯ {} <to_english> ENG_NOUN:ANATOMY {}
 link СУЩЕСТВИТЕЛЬНОЕ:АНГЕЛ {} <to_english> ENG_NOUN:ANGEL {}
 link СУЩЕСТВИТЕЛЬНОЕ:АНГИНА {} <to_english> ENG_NOUN:QUINSY {}
 link СУЩЕСТВИТЕЛЬНОЕ:АНГИНА {} <to_english> ENG_NOUN:ANGINA {}
 link СУЩЕСТВИТЕЛЬНОЕ:АНСАМБЛЬ {} <to_english> ENG_NOUN:ENSEMBLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:АПЕЛЬСИН {} <to_english> ENG_NOUN:ORANGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:АППАРАТ {} <to_english> ENG_NOUN:APPARATUS {}
 link СУЩЕСТВИТЕЛЬНОЕ:АППЕТИТ {} <to_english> ENG_NOUN:APPETITE {}
 link СУЩЕСТВИТЕЛЬНОЕ:АПРЕЛЬ {} <to_english> ENG_NOUN:APRIL {}
 link СУЩЕСТВИТЕЛЬНОЕ:АРАБ {} <to_english> ENG_NOUN:ARAB {}
 link СУЩЕСТВИТЕЛЬНОЕ:АРЕНА {} <to_english> ENG_NOUN:ARENA {}
 link СУЩЕСТВИТЕЛЬНОЕ:АРИЯ {} <to_english> ENG_NOUN:ARIA {}
 link СУЩЕСТВИТЕЛЬНОЕ:АРКА {} <to_english> ENG_NOUN:ARCH {}
 link СУЩЕСТВИТЕЛЬНОЕ:АРМИЯ {} <to_english> ENG_NOUN:ARMY {}
 link СУЩЕСТВИТЕЛЬНОЕ:АРТЕРИЯ {} <to_english> ENG_NOUN:ARTERY {}
 link СУЩЕСТВИТЕЛЬНОЕ:АРТИСТ {} <to_english> ENG_NOUN:ARTIST {}
 link СУЩЕСТВИТЕЛЬНОЕ:АРХЕОЛОГ {} <to_english> ENG_NOUN:ARCHAEOLOGIST {}
 link СУЩЕСТВИТЕЛЬНОЕ:АРХЕОЛОГИЯ {} <to_english> ENG_NOUN:ARCHAEOLOGY {}
 link СУЩЕСТВИТЕЛЬНОЕ:АРХИТЕКТУРА {} <to_english> ENG_NOUN:ARCHITECTURE {}
 link СУЩЕСТВИТЕЛЬНОЕ:АССАМБЛЕЯ {} <to_english> ENG_NOUN:ASSEMBLY {}
 link СУЩЕСТВИТЕЛЬНОЕ:АССИСТЕНТ {} <to_english> ENG_NOUN:ASSISTANT {}
 link СУЩЕСТВИТЕЛЬНОЕ:АССОЦИАЦИЯ {} <to_english> ENG_NOUN:ASSOCIATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:АСТРОНОМ {} <to_english> ENG_NOUN:ASTRONOMER {}
 link СУЩЕСТВИТЕЛЬНОЕ:АСТРОНОМИЯ {} <to_english> ENG_NOUN:ASTRONOMY {}
 link СУЩЕСТВИТЕЛЬНОЕ:АТАКА {} <to_english> ENG_NOUN:ATTACK {}
 link СУЩЕСТВИТЕЛЬНОЕ:АТЕИСТ {} <to_english> ENG_NOUN:ATHEIST {}
 link СУЩЕСТВИТЕЛЬНОЕ:АТЛАС {} <to_english> ENG_NOUN:ATLAS {}
 link СУЩЕСТВИТЕЛЬНОЕ:АТЛЕТ {} <to_english> ENG_NOUN:ATHLETE {}
 link СУЩЕСТВИТЕЛЬНОЕ:АТМОСФЕРА {} <to_english> ENG_NOUN:ATMOSPHERE {}
 link СУЩЕСТВИТЕЛЬНОЕ:АТОМ {} <to_english> ENG_NOUN:ATOM {}
 link СУЩЕСТВИТЕЛЬНОЕ:АУКЦИОН {} <to_english> ENG_NOUN:AUCTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:БАБОЧКА {} <to_english> ENG_NOUN:BUTTERFLY {}
 link СУЩЕСТВИТЕЛЬНОЕ:БАБУШКА {} <to_english> ENG_NOUN:GRANDMOTHER {}
 link СУЩЕСТВИТЕЛЬНОЕ:БАГАЖ {} <to_english> ENG_NOUN:LUGGAGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:БАГАЖ {} <to_english> ENG_NOUN:BUGGAGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:БАЗА {} <to_english> ENG_NOUN:BASE {}
 link СУЩЕСТВИТЕЛЬНОЕ:БАЗИС {} <to_english> ENG_NOUN:BASIS {}
 link СУЩЕСТВИТЕЛЬНОЕ:БАК {} <to_english> ENG_NOUN:TANK {}
 link СУЩЕСТВИТЕЛЬНОЕ:БАК {} <to_english> ENG_NOUN:CISTERN {}
 link СУЩЕСТВИТЕЛЬНОЕ:БАКТЕРИЯ {} <to_english> ENG_NOUN:BACTERIUM {}
 link СУЩЕСТВИТЕЛЬНОЕ:БАЛЕТ {} <to_english> ENG_NOUN:BALLET {}
 link СУЩЕСТВИТЕЛЬНОЕ:БАЛКОН {} <to_english> ENG_NOUN:BALCONY {}
 link СУЩЕСТВИТЕЛЬНОЕ:БАМПЕР {} <to_english> ENG_NOUN:FENDER {}
 link СУЩЕСТВИТЕЛЬНОЕ:БАМПЕР {} <to_english> ENG_NOUN:BUMPER {}
 link СУЩЕСТВИТЕЛЬНОЕ:БАНК {} <to_english> ENG_NOUN:BANK {}
 link СУЩЕСТВИТЕЛЬНОЕ:БАРАБАН {} <to_english> ENG_NOUN:DRUM {}
 link СУЩЕСТВИТЕЛЬНОЕ:БАНДА {} <to_english> ENG_NOUN:GANG {}
 link СУЩЕСТВИТЕЛЬНОЕ:БАРХАТ {} <to_english> ENG_NOUN:VELVET {}
 link СУЩЕСТВИТЕЛЬНОЕ:БАРЬЕР {} <to_english> ENG_NOUN:BARRIER {}
 link СУЩЕСТВИТЕЛЬНОЕ:БАС {} <to_english> ENG_NOUN:BASS {}
 link СУЩЕСТВИТЕЛЬНОЕ:БАССЕЙН {} <to_english> ENG_NOUN:BASIN {}
 link СУЩЕСТВИТЕЛЬНОЕ:БАССЕЙН {} <to_english> ENG_NOUN:POOL {}
 link СУЩЕСТВИТЕЛЬНОЕ:БАТОН {} <to_english> ENG_NOUN:LOAF {}
 link СУЩЕСТВИТЕЛЬНОЕ:БАШНЯ {} <to_english> ENG_NOUN:TOWER {}
 link СУЩЕСТВИТЕЛЬНОЕ:БЕГУН {} <to_english> ENG_NOUN:RUNNER {}
 link СУЩЕСТВИТЕЛЬНОЕ:БЕДРО {} <to_english> ENG_NOUN:HIP {}
 link СУЩЕСТВИТЕЛЬНОЕ:БЕЗОПАСНОСТЬ {} <to_english> ENG_NOUN:SAFETY {}
 link СУЩЕСТВИТЕЛЬНОЕ:БЕЗРАБОТИЦА {} <to_english> ENG_NOUN:UNEMPLOYMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:БЕКОН {} <to_english> ENG_NOUN:BACON {}
 link СУЩЕСТВИТЕЛЬНОЕ:БЕЛКА {} <to_english> ENG_NOUN:SQUIRREL {}
 link СУЩЕСТВИТЕЛЬНОЕ:БЕРЕГ {} <to_english> ENG_NOUN:BANK {}
 link СУЩЕСТВИТЕЛЬНОЕ:БЕРЕМЕННОСТЬ {} <to_english> ENG_NOUN:PREGNACY {}
 link СУЩЕСТВИТЕЛЬНОЕ:БЕРЕТ {} <to_english> ENG_NOUN:BERET {}
 link СУЩЕСТВИТЕЛЬНОЕ:БЕСЕДА {} <to_english> ENG_NOUN:TALK {}
 link СУЩЕСТВИТЕЛЬНОЕ:БЕСЕДА {} <to_english> ENG_NOUN:CONVERSATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:БЕСПОКОЙСТВО {} <to_english> ENG_NOUN:ANXIETY {}
 link СУЩЕСТВИТЕЛЬНОЕ:БЕСПОКОЙСТВО {} <to_english> ENG_NOUN:UNEASINESS {}
 link СУЩЕСТВИТЕЛЬНОЕ:БЕТОН {} <to_english> ENG_NOUN:CONCRETE {}
 link СУЩЕСТВИТЕЛЬНОЕ:БИБЛИОГРАФИЯ {} <to_english> ENG_NOUN:BIBLIOGRAPHY {}
 link СУЩЕСТВИТЕЛЬНОЕ:БИБЛИОТЕКА {} <to_english> ENG_NOUN:LIBRARY {}
 link СУЩЕСТВИТЕЛЬНОЕ:БИБЛИОТЕКАРЬ {} <to_english> ENG_NOUN:LIBRARIAN {}
 link СУЩЕСТВИТЕЛЬНОЕ:БИБЛИЯ {} <to_english> ENG_NOUN:BIBLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:БИЛЕТ {} <to_english> ENG_NOUN:TICKET {}
 link СУЩЕСТВИТЕЛЬНОЕ:БИНТ {} <to_english> ENG_NOUN:BANDAGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:БИОГРАФИЯ {} <to_english> ENG_NOUN:BIOGRAPHY {}
 link СУЩЕСТВИТЕЛЬНОЕ:БИОЛОГИЯ {} <to_english> ENG_NOUN:BIOLOGY {}
 link СУЩЕСТВИТЕЛЬНОЕ:БИРЖА {} <to_english> ENG_NOUN:EXCHANGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:БЛАГОДАРНОСТЬ {} <to_english> ENG_NOUN:GRATITUDE {}
 link СУЩЕСТВИТЕЛЬНОЕ:БЛАНК {} <to_english> ENG_NOUN:FORM {}
 link СУЩЕСТВИТЕЛЬНОЕ:БЛЕСК {} <to_english> ENG_NOUN:LUSTRE {}
 link СУЩЕСТВИТЕЛЬНОЕ:БЛЕСК {} <to_english> ENG_NOUN:BRILLIANCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:БЛОК {} <to_english> ENG_NOUN:BLOC {}
 link СУЩЕСТВИТЕЛЬНОЕ:БЛУЗКА {} <to_english> ENG_NOUN:BLOUSE {}
 link СУЩЕСТВИТЕЛЬНОЕ:БЛЮДО {} <to_english> ENG_NOUN:DISH {}
 link СУЩЕСТВИТЕЛЬНОЕ:БЛЮДО {} <to_english> ENG_NOUN:PLATTER {}
 link СУЩЕСТВИТЕЛЬНОЕ:БОЛЕЗНЬ {} <to_english> ENG_NOUN:ILLNESS {}
 link СУЩЕСТВИТЕЛЬНОЕ:БОЛЬ {} <to_english> ENG_NOUN:PAIN {}
 link СУЩЕСТВИТЕЛЬНОЕ:БОЛЬ {} <to_english> ENG_NOUN:ACHE {}
 link СУЩЕСТВИТЕЛЬНОЕ:БОЛЬНИЦА {} <to_english> ENG_NOUN:HOSPITAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:БОЛЬШИНСТВО {} <to_english> ENG_NOUN:MAJORITY {}
 link СУЩЕСТВИТЕЛЬНОЕ:БОМБА {} <to_english> ENG_NOUN:BOMB {}
 link СУЩЕСТВИТЕЛЬНОЕ:БОРОДА {} <to_english> ENG_NOUN:BEARD {}
 link СУЩЕСТВИТЕЛЬНОЕ:БОРТ {} <to_english> ENG_NOUN:BOARD {}
 link СУЩЕСТВИТЕЛЬНОЕ:БОРЩ {} <to_english> ENG_NOUN:BORSCH {}
 link СУЩЕСТВИТЕЛЬНОЕ:БОРЬБА {} <to_english> ENG_NOUN:STRUGGLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:БОТАНИК {} <to_english> ENG_NOUN:BOTANIST {}
 link СУЩЕСТВИТЕЛЬНОЕ:БОТАНИКА {} <to_english> ENG_NOUN:BOTANY {}
 link СУЩЕСТВИТЕЛЬНОЕ:БОТИНОК {} <to_english> ENG_NOUN:BOOT {}
 link СУЩЕСТВИТЕЛЬНОЕ:БОЧКА {} <to_english> ENG_NOUN:BARREL {}
 link СУЩЕСТВИТЕЛЬНОЕ:БРАТ {} <to_english> ENG_NOUN:BROTHER {}
 link СУЩЕСТВИТЕЛЬНОЕ:БРЕД {} <to_english> ENG_NOUN:DELIRIUM {}
 link СУЩЕСТВИТЕЛЬНОЕ:БРИГАДА {} <to_english> ENG_NOUN:TEAM {}
 link СУЩЕСТВИТЕЛЬНОЕ:БРИЛЛИАНТ {} <to_english> ENG_NOUN:DIAMOND {}
 link СУЩЕСТВИТЕЛЬНОЕ:БРИТВА {} <to_english> ENG_NOUN:RAZOR {}
 link СУЩЕСТВИТЕЛЬНОЕ:БРИТАНИЯ {} <to_english> ENG_NOUN:BRITAIN {}
 link СУЩЕСТВИТЕЛЬНОЕ:БРОСОК {} <to_english> ENG_NOUN:THROW {}
 link СУЩЕСТВИТЕЛЬНОЕ:БУКЕТ {} <to_english> ENG_NOUN:BOUQUET {}
 link СУЩЕСТВИТЕЛЬНОЕ:БУКВА {} <to_english> ENG_NOUN:LETTER {}
 link СУЩЕСТВИТЕЛЬНОЕ:БУЛАВКА {} <to_english> ENG_NOUN:PIN {}
 link СУЩЕСТВИТЕЛЬНОЕ:БУЛКА {} <to_english> ENG_NOUN:ROLL {}
 link СУЩЕСТВИТЕЛЬНОЕ:БУЛЬВАР {} <to_english> ENG_NOUN:BOULEVARD {}
 link СУЩЕСТВИТЕЛЬНОЕ:БУЛЬОН {} <to_english> ENG_NOUN:BOULLION {}
 link СУЩЕСТВИТЕЛЬНОЕ:БУЛЬОН {} <to_english> ENG_NOUN:BROTH {}
 link СУЩЕСТВИТЕЛЬНОЕ:БУМАГА {} <to_english> ENG_NOUN:PAPER {}
 link СУЩЕСТВИТЕЛЬНОЕ:БУМАЖНИК {} <to_english> ENG_NOUN:WALLET {}
 link СУЩЕСТВИТЕЛЬНОЕ:БУНТ {} <to_english> ENG_NOUN:RIOT {}
 link СУЩЕСТВИТЕЛЬНОЕ:БУНТ {} <to_english> ENG_NOUN:MUTINY {}
 link СУЩЕСТВИТЕЛЬНОЕ:БУРЯ {} <to_english> ENG_NOUN:STORM {}
 link СУЩЕСТВИТЕЛЬНОЕ:БУТЕРБРОД {} <to_english> ENG_NOUN:SANDWICH {}
 link СУЩЕСТВИТЕЛЬНОЕ:БУТОН {} <to_english> ENG_NOUN:BUD {}
 link СУЩЕСТВИТЕЛЬНОЕ:БУТЫЛКА {} <to_english> ENG_NOUN:BOTTLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:БУХТА {} <to_english> ENG_NOUN:BAY {}
 link СУЩЕСТВИТЕЛЬНОЕ:БЫК {} <to_english> ENG_NOUN:BULL {}
 link СУЩЕСТВИТЕЛЬНОЕ:БЮДЖЕТ {} <to_english> ENG_NOUN:BUDGET {}
 link СУЩЕСТВИТЕЛЬНОЕ:БЮЛЛЕТЕНЬ {} <to_english> ENG_NOUN:BULLETIN {}
 link СУЩЕСТВИТЕЛЬНОЕ:БЮРО {} <to_english> ENG_NOUN:BUREAU {}
 link СУЩЕСТВИТЕЛЬНОЕ:БЮРО {} <to_english> ENG_NOUN:OFFICE {}
 link СУЩЕСТВИТЕЛЬНОЕ:БЫТИЕ {} <to_english> ENG_NOUN:BEING {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЯНВАРЬ {} <to_english> ENG_NOUN:JANUARY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЯМА {} <to_english> ENG_NOUN:PIT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЯМА {} <to_english> ENG_NOUN:HOLLOW {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЯМКА {} <to_english> ENG_NOUN:HOLLOW {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЯМКА {} <to_english> ENG_NOUN:PIT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЯРКОСТЬ {} <to_english> ENG_NOUN:BRIGHTNESS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЯРОСТЬ {} <to_english> ENG_NOUN:FURY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЯХТА {} <to_english> ENG_NOUN:YACHT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЯВЛЕНИЕ {} <to_english> ENG_NOUN:PHENOMENON {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЧАСТЬ {} <to_english> ENG_NOUN:PART {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПУТЬ {} <to_english> ENG_NOUN:WAY {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАЧАЛО {} <to_english> ENG_NOUN:BEGINNING {}
 link СУЩЕСТВИТЕЛЬНОЕ:МИР {} <to_english> ENG_NOUN:PEACE {}
 link СУЩЕСТВИТЕЛЬНОЕ:МИР {} <to_english> ENG_NOUN:WORLD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЗГЛЯД {} <to_english> ENG_NOUN:GLANCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЗГЛЯД {} <to_english> ENG_NOUN:LOOK {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОСОЛ { ОДУШ:ОДУШ } <to_english> ENG_NOUN:AMBASSADOR {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОФЕ {} <to_english> ENG_NOUN:COFFEE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВИД {} <to_english> ENG_NOUN:VIEW {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТЕМА {} <to_english> ENG_NOUN:SUBJECT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТЕМА {} <to_english> ENG_NOUN:TOPIC {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТЕМА {} <to_english> ENG_NOUN:THEME {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЛЕЧО {} <to_english> ENG_NOUN:SHOULDER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЕЩЬ {} <to_english> ENG_NOUN:THING {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЛУЧАЙ {} <to_english> ENG_NOUN:OCCASION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАЛЕЦ {} <to_english> ENG_NOUN:FINGER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАЛЕЦ {} <to_english> ENG_NOUN:TOE {}
 link СУЩЕСТВИТЕЛЬНОЕ:КАМЕНЬ {} <to_english> ENG_NOUN:STONE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВОЛОС {} <to_english> ENG_NOUN:HAIR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОПАСНОСТЬ {} <to_english> ENG_NOUN:DANGER {}
 link СУЩЕСТВИТЕЛЬНОЕ:НЕБО {} <to_english> ENG_NOUN:SKY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОСТЕЛЬ {} <to_english> ENG_NOUN:BED {}
 link СУЩЕСТВИТЕЛЬНОЕ:МГНОВЕНИЕ {} <to_english> ENG_NOUN:MOMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШОССЕ {} <to_english> ENG_NOUN:HIGHWAY {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОЗНАНИЕ {} <to_english> ENG_NOUN:CONSCIOUSNESS {}
 link СУЩЕСТВИТЕЛЬНОЕ:РОТ {} <to_english> ENG_NOUN:MOUTH {}
 link СУЩЕСТВИТЕЛЬНОЕ:МЕЧ {} <to_english> ENG_NOUN:SWORD {}

 // ----------------------------------------------------------------------


 link СУЩЕСТВИТЕЛЬНОЕ:ВАГОН {} <to_english> ENG_NOUN:CARRIAGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВАЗА {} <to_english> ENG_NOUN:VASE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВАННАЯ {} <to_english> ENG_NOUN:BATH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЕДРО {} <to_english> ENG_NOUN:PAIL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЕДРО {} <to_english> ENG_NOUN:BUCKET {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЕКО {} <to_english> ENG_NOUN:EYELID {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЕЛИЧИНА {} <to_english> ENG_NOUN:SIZE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЕЛОСИПЕД {} <to_english> ENG_NOUN:BICYCLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЕНА { CharCasing:Lower } <to_english> ENG_NOUN:vein {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЕНА { CharCasing:FirstCapitalized } <to_english> ENG_NOUN:Vienna {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЕРА {одуш:неодуш} <to_english> ENG_NOUN:FAITH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЕРА {одуш:неодуш} <to_english> ENG_NOUN:BELIEF {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЕРАНДА {} <to_english> ENG_NOUN:PORCH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЕРАНДА {} <to_english> ENG_NOUN:VERANDA {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЕРЕВКА {} <to_english> ENG_NOUN:CORD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЕРЕВКА {} <to_english> ENG_NOUN:TWINE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЕРЕВКА {} <to_english> ENG_NOUN:ROPE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЕРЕВКА {} <to_english> ENG_NOUN:STRING {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЕРОЯТНОСТЬ {} <to_english> ENG_NOUN:PROBABILITY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЕРШИНА {} <to_english> ENG_NOUN:TOP {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЕРШИНА {} <to_english> ENG_NOUN:SUMMIT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЕРШИНА {} <to_english> ENG_NOUN:PEAK {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЕСНА {} <to_english> ENG_NOUN:SPRING {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЕСТИБЮЛЬ {} <to_english> ENG_NOUN:LOBBY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЕСТИБЮЛЬ {} <to_english> ENG_NOUN:HALL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЕТКА {} <to_english> ENG_NOUN:BRANCH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЕЩЕСТВО {} <to_english> ENG_NOUN:SUBSTANCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЗРЫВ {} <to_english> ENG_NOUN:EXPLOSION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЗРЫВ {} <to_english> ENG_NOUN:BURST {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЗЫСКАНИЕ {} <to_english> ENG_NOUN:PENALTY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЗЫСКАНИЕ {} <to_english> ENG_NOUN:PUNISHMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВИД {} <to_english> ENG_NOUN:APPEARANCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВИЗА {} <to_english> ENG_NOUN:VISA {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВИЗИТ {} <to_english> ENG_NOUN:VISIT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВИЗИТ {} <to_english> ENG_NOUN:CALL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВИЛКА {} <to_english> ENG_NOUN:FORK {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВИНА {} <to_english> ENG_NOUN:GUILT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВИНА {} <to_english> ENG_NOUN:FAULT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВИНТОВКА {} <to_english> ENG_NOUN:RIFLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВИСОК {} <to_english> ENG_NOUN:TEMPLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВКЛАД {} <to_english> ENG_NOUN:DEPOSIT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВКУС {} <to_english> ENG_NOUN:TASTE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЛАДЕЛЕЦ {} <to_english> ENG_NOUN:OWNER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВОЗВРАЩЕНИЕ {} <to_english> ENG_NOUN:RETURN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВОЗВЫШЕННОСТЬ {} <to_english> ENG_NOUN:HILL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВОЗВЫШЕННОСТЬ {} <to_english> ENG_NOUN:ELEVATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВОЗГЛАС {} <to_english> ENG_NOUN:EXCLAMATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВОЗЗВАНИЕ {} <to_english> ENG_NOUN:APPEAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВОЗЗВАНИЕ {} <to_english> ENG_NOUN:PROCLAMATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВОЗНАГРАЖДЕНИЕ {} <to_english> ENG_NOUN:REWARD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВОЗНАГРАЖДЕНИЕ {} <to_english> ENG_NOUN:REMUNERATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВОЗРАЖЕНИЕ {} <to_english> ENG_NOUN:OBJECTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВОКЗАЛ {} <to_english> ENG_NOUN:STATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВОКЗАЛ {} <to_english> ENG_NOUN:TERMINAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВОЛК {} <to_english> ENG_NOUN:WOLF {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВОЛЯ {} <to_english> ENG_NOUN:WILL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВООРУЖЕНИЕ {} <to_english> ENG_NOUN:ARMAMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВОР {} <to_english> ENG_NOUN:THIEF {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВОРОБЕЙ {} <to_english> ENG_NOUN:SPARROW {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВОРОНА {} <to_english> ENG_NOUN:CROW {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВОСКРЕСЕНИЕ {} <to_english> ENG_NOUN:SUNDAY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВОСПАЛЕНИЕ {} <to_english> ENG_NOUN:INFLAMMATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВОСПИТАНИЕ {} <to_english> ENG_NOUN:EDUCATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВОСТОК {} <to_english> ENG_NOUN:EAST {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВОСТОРГ {} <to_english> ENG_NOUN:RAPTURE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВОСХИЩЕНИЕ {} <to_english> ENG_NOUN:ADMIRATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВОСХОД {} <to_english> ENG_NOUN:RISE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВОСХОД {} <to_english> ENG_NOUN:SUNRISE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВОСХОЖДЕНИЕ {} <to_english> ENG_NOUN:ASCENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВРАТАРЬ {} <to_english> ENG_NOUN:GOALKEEPER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВРАЧ {} <to_english> ENG_NOUN:PHYSICIAN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВРЕД {} <to_english> ENG_NOUN:HARM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВРЕД {} <to_english> ENG_NOUN:INJURY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВРЕД {} <to_english> ENG_NOUN:DAMAGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВРУЧЕНИЕ {} <to_english> ENG_NOUN:DELIVERY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВСАДНИК {} <to_english> ENG_NOUN:HORSEMAN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВСТУПЛЕНИЕ {} <to_english> ENG_NOUN:INTRODUCTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВХОД {} <to_english> ENG_NOUN:ENTRANCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЪЕЗД {} <to_english> ENG_NOUN:ENTRANCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЫБОР {} <to_english> ENG_NOUN:CHOISE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЫБОР {} <to_english> ENG_NOUN:ELECTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЫВЕСКА {} <to_english> ENG_NOUN:SIGNBOARD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЫВОД {} <to_english> ENG_NOUN:CONCLUSION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЫВОЗ {} <to_english> ENG_NOUN:EXPORT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЫГОВОР {} <to_english> ENG_NOUN:REPRIMAND {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЫГОВОР {} <to_english> ENG_NOUN:PRONONCIATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЫДАЧА {} <to_english> ENG_NOUN:DELIVERY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЫДУМКА {} <to_english> ENG_NOUN:INVENTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЫЕЗД {} <to_english> ENG_NOUN:DEPARTURE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЫИГРЫШ {} <to_english> ENG_NOUN:PRIZE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЫИГРЫШ {} <to_english> ENG_NOUN:GAIN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЫПАД {} <to_english> ENG_NOUN:LUNGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЫПАД {} <to_english> ENG_NOUN:THRUST {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЫСОТА {} <to_english> ENG_NOUN:HEIGHT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЫСОТА {} <to_english> ENG_NOUN:ALTITUDE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЫСТАВКА {} <to_english> ENG_NOUN:EXHIBITION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЫСТРЕЛ {} <to_english> ENG_NOUN:SHOT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЫСТУПЛЕНИЕ {} <to_english> ENG_NOUN:ARTICLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЫСТУПЛЕНИЕ {} <to_english> ENG_NOUN:SPEECH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЫСТУПЛЕНИЕ {} <to_english> ENG_NOUN:PERFORMANCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЫСТУПЛЕНИЕ {} <to_english> ENG_NOUN:DEMONSTRATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЫХОД {} <to_english> ENG_NOUN:EXIT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЫШИВКА {} <to_english> ENG_NOUN:EMBROIDERY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГАВАНЬ {} <to_english> ENG_NOUN:HARBOUR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГАЗ {} <to_english> ENG_NOUN:GAS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГАЗЕТА {} <to_english> ENG_NOUN:NEWSPAPER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГАЗОН {} <to_english> ENG_NOUN:LAWN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГАЛЕРЕЯ {} <to_english> ENG_NOUN:GALLERY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГАЛКА {} <to_english> ENG_NOUN:DAW {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГАЛКА {} <to_english> ENG_NOUN:JACKDAW {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГАЛОП {} <to_english> ENG_NOUN:GALLOP {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГАМБИТ {} <to_english> ENG_NOUN:GAMBIT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГАНГСТЕР {} <to_english> ENG_NOUN:GANGSTER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГВОЗДИКА {} <to_english> ENG_NOUN:CARNATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГВОЗДИКА {} <to_english> ENG_NOUN:CLOVE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГВОЗДЬ {} <to_english> ENG_NOUN:NAIL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГЕРОЙ {} <to_english> ENG_NOUN:HERO {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГИГАНТ {} <to_english> ENG_NOUN:GIANT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГИМНАСТИКА {} <to_english> ENG_NOUN:GYMNASTICS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГЛАВА { одуш:неодуш } <to_english> ENG_NOUN:HEAD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГЛИНА {} <to_english> ENG_NOUN:CLAY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГЛОТОК {} <to_english> ENG_NOUN:GULP {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГЛОТОК {} <to_english> ENG_NOUN:SIP {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГЛУПОСТЬ {} <to_english> ENG_NOUN:FOOLISHNESS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГНЕВ {} <to_english> ENG_NOUN:ANGER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГНЕВ {} <to_english> ENG_NOUN:WRATH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГНЕТ {} <to_english> ENG_NOUN:OPPRESSION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГОБЕЛЕН {} <to_english> ENG_NOUN:GOBELIN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГОВЯДИНА {} <to_english> ENG_NOUN:BEEF {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГОЛОВА {} <to_english> ENG_NOUN:HEAD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГОЛОВОКРУЖЕНИЕ {} <to_english> ENG_NOUN:GIDDINESS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГОЛОВОЛОМКА {} <to_english> ENG_NOUN:PUZZLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГОЛОД {} <to_english> ENG_NOUN:HUNGER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГОЛОД {} <to_english> ENG_NOUN:FAMINE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГОЛОСОВАНИЕ {} <to_english> ENG_NOUN:VOTE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГОЛУБЬ {} <to_english> ENG_NOUN:PIGEON {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГОНОРАР {} <to_english> ENG_NOUN:FEE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГОНКА {} <to_english> ENG_NOUN:RACE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГОРДОСТЬ {} <to_english> ENG_NOUN:PRIDE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГОРЕ {} <to_english> ENG_NOUN:GRIEF {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГОРИЗОНТ {} <to_english> ENG_NOUN:HORIZON {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГОРЛО {} <to_english> ENG_NOUN:THROAT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГОРН {} <to_english> ENG_NOUN:BUGLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГОРОДОК {} <to_english> ENG_NOUN:TOWN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГОРОЖАНИН {} <to_english> ENG_NOUN:TOWNSMAN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГОРСТЬ {} <to_english> ENG_NOUN:HANDFUL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГОРЮЧЕЕ {} <to_english> ENG_NOUN:FUEL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГОСПОДСТВО {} <to_english> ENG_NOUN:SUPREMACY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГОСТИНИЦА {} <to_english> ENG_NOUN:HOTEL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГРАВЮРА {} <to_english> ENG_NOUN:ENGRAVING {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГРАВЮРА {} <to_english> ENG_NOUN:ETHCING {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГРАДУС {} <to_english> ENG_NOUN:DEGREE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГРАЖДАНКА {} <to_english> ENG_NOUN:CITIZEN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГРАЖДАНОЧКА {} <to_english> ENG_NOUN:CITIZEN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГРАЖДАНИН {} <to_english> ENG_NOUN:CITIZEN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГРАММ {} <to_english> ENG_NOUN:GRAM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГРАММ {} <to_english> ENG_NOUN:GRAMME {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГРАНАТ {} <to_english> ENG_NOUN:POMEGRANATE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГРАНИЦА {} <to_english> ENG_NOUN:BORDER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГРИПП {} <to_english> ENG_NOUN:INFLUENZA {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГРИПП {} <to_english> ENG_NOUN:GRIPPE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГРОЗА {} <to_english> ENG_NOUN:THUNDERSTORM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГРОХОТ {} <to_english> ENG_NOUN:CRASH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГРОХОТ {} <to_english> ENG_NOUN:RUMBLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГРОХОТ {} <to_english> ENG_NOUN:RATTLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГРУБОСТЬ {} <to_english> ENG_NOUN:RUDENESS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГРУДЬ {} <to_english> ENG_NOUN:CHEST {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГРУДЬ {} <to_english> ENG_NOUN:BOSOM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГРУЗ {} <to_english> ENG_NOUN:LOAD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГРУЗ {} <to_english> ENG_NOUN:CARGO {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГРУЗОВИК {} <to_english> ENG_NOUN:LORRY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГРУЗОВИК {} <to_english> ENG_NOUN:TRUCK {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГРЯЗЬ {} <to_english> ENG_NOUN:DIRT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГРЯЗЬ {} <to_english> ENG_NOUN:FILTH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГРЯЗЬ {} <to_english> ENG_NOUN:MUD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГУБКА {} <to_english> ENG_NOUN:SPONGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГУДОК {} <to_english> ENG_NOUN:HOOTER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГУДОК {} <to_english> ENG_NOUN:HORN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДАВЛЕНИЕ {} <to_english> ENG_NOUN:PRESSURE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДАРОВАНИЕ {} <to_english> ENG_NOUN:TALENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДАРОВАНИЕ {} <to_english> ENG_NOUN:GIFT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДАР {} <to_english> ENG_NOUN:GIFT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДВИГАТЕЛЬ {} <to_english> ENG_NOUN:ENGINE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДВИГАТЕЛЬ {} <to_english> ENG_NOUN:MOTOR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДВИЖЕНИЕ {} <to_english> ENG_NOUN:MOVEMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДВОР {} <to_english> ENG_NOUN:YARD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДВОР {} <to_english> ENG_NOUN:COURT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДВОРЕЦ {} <to_english> ENG_NOUN:PALACE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДЕЖУРСТВО {} <to_english> ENG_NOUN:DUTY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДЕЙСТВИЕ {} <to_english> ENG_NOUN:DEED {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДЕКРЕТ {} <to_english> ENG_NOUN:DECREE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДЕЛЕНИЕ {} <to_english> ENG_NOUN:DIVISION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДЕЛЬФИН {} <to_english> ENG_NOUN:DOLPHIN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДЕМОКРАТИЯ {} <to_english> ENG_NOUN:DEMOCRACY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДЕМОНСТРАЦИЯ {} <to_english> ENG_NOUN:PARADE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДЕМОНСТРАЦИЯ {} <to_english> ENG_NOUN:MARCH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДЕМОНСТРАЦИЯ {} <to_english> ENG_NOUN:MANIFESTATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДЕМОН {} <to_english> ENG_NOUN:DEMON {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДЕМОН {} <to_english> ENG_NOUN:SATAN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДЕПОЗИТ {} <to_english> ENG_NOUN:DEPOSIT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДЕРЕВНЯ {} <to_english> ENG_NOUN:VILLAGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДЕРЬМО {} <to_english> ENG_NOUN:SHIT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДЕТСТВО {} <to_english> ENG_NOUN:CHILDHOOD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДЖЕМ {} <to_english> ENG_NOUN:JAM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДИАГРАММА {} <to_english> ENG_NOUN:DIAGRAM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДИАЛЕКТ {} <to_english> ENG_NOUN:DIALECT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДИАМЕТР {} <to_english> ENG_NOUN:DIAMETER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДИРЕКТОР { род:муж } <to_english> ENG_NOUN:DIRECTOR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДИЕТА {} <to_english> ENG_NOUN:DIET {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДИКТАТУРА {} <to_english> ENG_NOUN:DICTATORSHIP {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДИПЛОМ {} <to_english> ENG_NOUN:DIPLOMA {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДИСК {} <to_english> ENG_NOUN:DISCUS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДИСКУССИЯ {} <to_english> ENG_NOUN:DISCUSSION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДИСПУТ {} <to_english> ENG_NOUN:DEBATE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДИСТАНЦИЯ {} <to_english> ENG_NOUN:DISTANCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДИССЕРТАЦИЯ {} <to_english> ENG_NOUN:THESIS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДИСЦИПЛИНА {} <to_english> ENG_NOUN:DISCIPLINE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДИЧЬ {} <to_english> ENG_NOUN:FOWL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДОВОД {} <to_english> ENG_NOUN:REASON {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДОГОВОР {} <to_english> ENG_NOUN:AGREEMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДОКАЗАТЕЛЬСТВО {} <to_english> ENG_NOUN:PROOF {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДОКЛАД {} <to_english> ENG_NOUN:REPORT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДОКУМЕНТ {} <to_english> ENG_NOUN:DOCUMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДОЛГ {} <to_english> ENG_NOUN:DUTY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДОЛГ {} <to_english> ENG_NOUN:DEPT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДОЛГОТА {} <to_english> ENG_NOUN:LONGITUDE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДОЛЖНОСТЬ {} <to_english> ENG_NOUN:POST {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДОЛЖНОСТЬ {} <to_english> ENG_NOUN:POSITION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДОЛЯ {} <to_english> ENG_NOUN:SHARE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДОПРОС {} <to_english> ENG_NOUN:INTERROGATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДОСАДА {} <to_english> ENG_NOUN:AGGRAVATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДОСКА {} <to_english> ENG_NOUN:BOARD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДОРОЖКА {} <to_english> ENG_NOUN:PATH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДОСТАВКА {} <to_english> ENG_NOUN:DELIVERY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДОСТИЖЕНИЕ {} <to_english> ENG_NOUN:ACHIVEMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДОСТОЯНИЕ {} <to_english> ENG_NOUN:PROPERTY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДОСТУП {} <to_english> ENG_NOUN:ACCESS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДОХОД {} <to_english> ENG_NOUN:INCOME {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДОЧЬ {} <to_english> ENG_NOUN:DAUGHTER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДРАГОЦЕННОСТЬ {} <to_english> ENG_NOUN:JEWELRY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДРАМА {} <to_english> ENG_NOUN:DRAMA {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДУБ {} <to_english> ENG_NOUN:OAK {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДУХ {} <to_english> ENG_NOUN:SPIRIT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДЫМ {} <to_english> ENG_NOUN:SMOKE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДЯДЯ {} <to_english> ENG_NOUN:UNCLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЕВРОПА {} <to_english> ENG_NOUN:EUROPE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЕВРЕЙ {} <to_english> ENG_NOUN:jew {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЕДА {} <to_english> ENG_NOUN:food {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЕДИНИЦА {} <to_english> ENG_NOUN:unit {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЖАЖДА {} <to_english> ENG_NOUN:THIRST {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЖАЛОБА {} <to_english> ENG_NOUN:COMPLAINT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЖАНР {} <to_english> ENG_NOUN:GENRE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЖАР {} <to_english> ENG_NOUN:HEAT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЖАР {} <to_english> ENG_NOUN:ARDOUR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЖЕЛАНИЕ {} <to_english> ENG_NOUN:DESIRE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЖЕЛЕЗО {} <to_english> ENG_NOUN:IRON {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЖЕЛТОК {} <to_english> ENG_NOUN:YOLK {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЖЕЛУДОК {} <to_english> ENG_NOUN:STOMACH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЖЕЛУДЬ {} <to_english> ENG_NOUN:ACORN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЖЕНИХ {} <to_english> ENG_NOUN:FIANCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЖЕНИХ {} <to_english> ENG_NOUN:BRIDEGROOM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЖЕРТВА { одуш:неодуш } <to_english> ENG_NOUN:SACRIFICE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЖЕРТВА { одуш:неодуш } <to_english> ENG_NOUN:VICTIM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЖЕСТ {} <to_english> ENG_NOUN:GESTURE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЖИВОТ {} <to_english> ENG_NOUN:STOMACH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЖИЛЕЦ {} <to_english> ENG_NOUN:TENANT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЖИЛЕЦ {} <to_english> ENG_NOUN:LODGER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЖИР {} <to_english> ENG_NOUN:GREASE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЖИТЕЛЬ {} <to_english> ENG_NOUN:INHABITANT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЖУК {} <to_english> ENG_NOUN:BEETLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЖУК {} <to_english> ENG_NOUN:BUG {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЖУРНАЛ {} <to_english> ENG_NOUN:MAGAZINE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЖУРНАЛ {} <to_english> ENG_NOUN:JOURNAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАБЛУЖДЕНИЕ {} <to_english> ENG_NOUN:ERROR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАБЛУЖДЕНИЕ {} <to_english> ENG_NOUN:MISTAKE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАБОЛЕВАНИЕ {} <to_english> ENG_NOUN:DISEASE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАБОР {} <to_english> ENG_NOUN:FENCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАБОТА {} <to_english> ENG_NOUN:CARE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАБОТА {} <to_english> ENG_NOUN:CONCERN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАВОД {} <to_english> ENG_NOUN:FACTORY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАГАДКА {} <to_english> ENG_NOUN:RIDDLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАГАДКА {} <to_english> ENG_NOUN:PUZZLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАВТРАК {} <to_english> ENG_NOUN:BREAKFAST {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАГАР {} <to_english> ENG_NOUN:TAN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАГАР {} <to_english> ENG_NOUN:SUNBURN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАГЛАВИЕ {} <to_english> ENG_NOUN:TITLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАГОВОР {} <to_english> ENG_NOUN:PLOT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАГОВОР {} <to_english> ENG_NOUN:CONSPIRACY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАГОЛОВОК {} <to_english> ENG_NOUN:HEADLINE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАДАНИЕ {} <to_english> ENG_NOUN:TASK {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАДАЧА {} <to_english> ENG_NOUN:TASK {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАДАЧА {} <to_english> ENG_NOUN:PROBLEM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАДЕРЖКА {} <to_english> ENG_NOUN:DELAY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАЕМ {} <to_english> ENG_NOUN:LOAN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАЖИГАЛКА {} <to_english> ENG_NOUN:LIGHTER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАКАЗ {} <to_english> ENG_NOUN:ORDER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАКАТ {} <to_english> ENG_NOUN:SUNSET {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАКЛЮЧЕНИЕ {} <to_english> ENG_NOUN:CONCLUSION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАКОЛКА {} <to_english> ENG_NOUN:HAIRPIN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАКОННОСТЬ {} <to_english> ENG_NOUN:LEGALITY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАЛ {} <to_english> ENG_NOUN:HALL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАЛИВ {} <to_english> ENG_NOUN:GULF {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАМЕТКА {} <to_english> ENG_NOUN:PARAGRAPH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАМЕТКА {} <to_english> ENG_NOUN:NOTE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАМЕЧАНИЕ {} <to_english> ENG_NOUN:OBSERVATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАМЕЧАНИЕ {} <to_english> ENG_NOUN:REMARK {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАМЫСЕЛ {} <to_english> ENG_NOUN:SCHEME {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАМЫСЕЛ {} <to_english> ENG_NOUN:INTENTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАПАС {} <to_english> ENG_NOUN:STOCK {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАПАС {} <to_english> ENG_NOUN:SUPPLY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАПИСКА {} <to_english> ENG_NOUN:NOTE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАПРЕЩЕНИЕ {} <to_english> ENG_NOUN:PROHIBITION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАПРОС {} <to_english> ENG_NOUN:INQUIRY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАРАЖЕНИЕ {} <to_english> ENG_NOUN:INFECTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАРЯ {} <to_english> ENG_NOUN:DAWN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАСТЕЖКА {} <to_english> ENG_NOUN:FASTENING {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАТМЕНИЕ {} <to_english> ENG_NOUN:ECLIPSE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАТОР {} <to_english> ENG_NOUN:JAM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАТРАТА {} <to_english> ENG_NOUN:EXPENSE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАТРАТА {} <to_english> ENG_NOUN:EXPENDITURE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАЩИТА {} <to_english> ENG_NOUN:DEFENCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАЩИТА {} <to_english> ENG_NOUN:PROTECTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАЩИТНИК {} <to_english> ENG_NOUN:DEFENDER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАЩИТНИК {} <to_english> ENG_NOUN:PROTECTOR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАЯВЛЕНИЕ {} <to_english> ENG_NOUN:STATEMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗАЯЦ {} <to_english> ENG_NOUN:HARE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗВАНИЕ {} <to_english> ENG_NOUN:RANK {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗВАНИЕ {} <to_english> ENG_NOUN:TITLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗВОНОК {} <to_english> ENG_NOUN:BELL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗДОРОВЬЕ {} <to_english> ENG_NOUN:HEALTH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗЕМЛЕДЕЛИЕ {} <to_english> ENG_NOUN:AGRICULTURE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗЕМЛЕДЕЛИЕ {} <to_english> ENG_NOUN:FARMING {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗЕМЛЯ {} <to_english> ENG_NOUN:SOIL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗЕМЛЯ {} <to_english> ENG_NOUN:GROUND {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗЕРКАЛО {} <to_english> ENG_NOUN:MIRROR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗИМА {} <to_english> ENG_NOUN:WINTER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗЛО {} <to_english> ENG_NOUN:EVIL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗЛО {} <to_english> ENG_NOUN:WRONG {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗНАК {} <to_english> ENG_NOUN:MARK {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗНАМЯ {} <to_english> ENG_NOUN:BANNER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗНАМЯ {} <to_english> ENG_NOUN:FLAG {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗНАНИЕ {} <to_english> ENG_NOUN:KNOWLEDGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗМЕЯ {} <to_english> ENG_NOUN:SNAKE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗНАТОК {} <to_english> ENG_NOUN:EXPERT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗНАТОК {} <to_english> ENG_NOUN:CONNOISEUR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗОЛОТО {} <to_english> ENG_NOUN:GOLD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗОНА {} <to_english> ENG_NOUN:ZONE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗОНА {} <to_english> ENG_NOUN:AREA {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗОНТ {} <to_english> ENG_NOUN:UMBRELLA {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗОНТ {} <to_english> ENG_NOUN:SUNSHADE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗОНТ {} <to_english> ENG_NOUN:PARASOL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗРЕНИЕ {} <to_english> ENG_NOUN:EYESIGHT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗРИТЕЛЬ {} <to_english> ENG_NOUN:SPECTATOR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗУБ {} <to_english> ENG_NOUN:TOOTH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЗООПАРК {} <to_english> ENG_NOUN:zoo {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИВА {} <to_english> ENG_NOUN:WILLOW {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИГЛА {} <to_english> ENG_NOUN:NEEDLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИГРА {} <to_english> ENG_NOUN:PLAY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИГРУШКА {} <to_english> ENG_NOUN:TOY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИГРУШКА {} <to_english> ENG_NOUN:PLAYTHING {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИГРОК {} <to_english> ENG_NOUN:PLAYER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИГРОК {} <to_english> ENG_NOUN:GAMBLER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИДЕЯ {} <to_english> ENG_NOUN:IDEA {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИЗБЫТОК {} <to_english> ENG_NOUN:EXCESS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИЗВЕСТНОСТЬ {} <to_english> ENG_NOUN:REPUTATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИЗВЕЩЕНИЕ {} <to_english> ENG_NOUN:NOTIFICATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИЗВИНЕНИЕ {} <to_english> ENG_NOUN:EXCUSE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИЗГОТОВЛЕНИЕ {} <to_english> ENG_NOUN:MANUFACTURE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИЗДАНИЕ {} <to_english> ENG_NOUN:PUBLICATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИЗДЕРЖКА {} <to_english> ENG_NOUN:EXPENSE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИЗМЕНА {} <to_english> ENG_NOUN:TREASON {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИЗМЕНА {} <to_english> ENG_NOUN:BETRAYAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИЗМЕНЕНИЕ {} <to_english> ENG_NOUN:CHANGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИЗМЕННИК {} <to_english> ENG_NOUN:TRAITOR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИЗМЕНЕНИЕ {} <to_english> ENG_NOUN:ALTERATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИЗМЫШЛЕНИЕ {} <to_english> ENG_NOUN:INVENTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИЗОБРАЖЕНИЕ {} <to_english> ENG_NOUN:PORTRAYAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИЗОБРАЖЕНИЕ {} <to_english> ENG_NOUN:PICTURE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИЗОБИЛИЕ {} <to_english> ENG_NOUN:ABUNDANCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИЗОБРЕТЕНИЕ {} <to_english> ENG_NOUN:INVENTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИЗУМРУД {} <to_english> ENG_NOUN:EMERALD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИЗУЧЕНИЕ {} <to_english> ENG_NOUN:STUDY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИКОНА {} <to_english> ENG_NOUN:ICON {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИКРА {} <to_english> ENG_NOUN:ROE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИКРА {} <to_english> ENG_NOUN:CAVIAR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИКРА {} <to_english> ENG_NOUN:CALF {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИМПОРТ {} <to_english> ENG_NOUN:IMPORT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИМПРЕССИОНИЗМ {} <to_english> ENG_NOUN:IMPRESSIONISM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИНВАЛИД {} <to_english> ENG_NOUN:INVALID {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИНДУСТРИЯ {} <to_english> ENG_NOUN:INDUSTRY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИНЖИР {} <to_english> ENG_NOUN:FIG {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИНИЦИАТИВА {} <to_english> ENG_NOUN:INITIATIVE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИНОСТРАНЕЦ {} <to_english> ENG_NOUN:FOREIGNER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИНСТИТУТ {} <to_english> ENG_NOUN:COLLEGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИНСТИТУТ {} <to_english> ENG_NOUN:INSTITUTE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИНСТРУКТОР {} <to_english> ENG_NOUN:INSTRUCTOR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИНСТРУКТОР {} <to_english> ENG_NOUN:COACH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИНСТРУКЦИЯ {} <to_english> ENG_NOUN:INSTRUCTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИНСТРУМЕНТ {} <to_english> ENG_NOUN:TOOL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИНТЕРЕС {} <to_english> ENG_NOUN:INTEREST {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИНФОРМАЦИЯ {} <to_english> ENG_NOUN:INFORMATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИНЦИДЕНТ {} <to_english> ENG_NOUN:INCIDENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИРОНИЯ {} <to_english> ENG_NOUN:IRONY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИСК {} <to_english> ENG_NOUN:ACTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИСК {} <to_english> ENG_NOUN:SUIT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИСКЛЮЧЕНИЕ {} <to_english> ENG_NOUN:EXCEPTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИСКУССТВО {} <to_english> ENG_NOUN:ART {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИСЛАМ {} <to_english> ENG_NOUN:islam {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИСПАНИЯ {} <to_english> ENG_NOUN:spain {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИСПОЛНЕНИЕ {} <to_english> ENG_NOUN:execution {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИСПОЛЬЗОВАНИЕ {} <to_english> ENG_NOUN:USE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИССЛЕДОВАНИЕ {} <to_english> ENG_NOUN:INVESTIGATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИСТИНА {} <to_english> ENG_NOUN:TRUTH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИЮНЬ {} <to_english> ENG_NOUN:JUNE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИЮЛЬ {} <to_english> ENG_NOUN:JULY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ИТОГ {} <to_english> ENG_NOUN:BALANCE {}

 // -------------------------------------------------------------------------

 link СУЩЕСТВИТЕЛЬНОЕ:КАБИНА {} <to_english> ENG_NOUN:CABIN {}
 link СУЩЕСТВИТЕЛЬНОЕ:КАБИНЕТ {} <to_english> ENG_NOUN:OFFICE {}
 link СУЩЕСТВИТЕЛЬНОЕ:КАДР {} <to_english> ENG_NOUN:FRAME {}
 link СУЩЕСТВИТЕЛЬНОЕ:КАМЕНЬ {} <to_english> ENG_NOUN:STONE {}
 link СУЩЕСТВИТЕЛЬНОЕ:КАМФОРА {} <to_english> ENG_NOUN:CAMPHOR {}
 link СУЩЕСТВИТЕЛЬНОЕ:КАНАВА {} <to_english> ENG_NOUN:DITCH {}
 link СУЩЕСТВИТЕЛЬНОЕ:КАНАЛ {} <to_english> ENG_NOUN:CHANNEL {}
 link СУЩЕСТВИТЕЛЬНОЕ:КАНАТ {} <to_english> ENG_NOUN:ROPE {}
 link СУЩЕСТВИТЕЛЬНОЕ:КАНИСТРА {} <to_english> ENG_NOUN:CANISTER {}
 link СУЩЕСТВИТЕЛЬНОЕ:КАПИТАЛ {} <to_english> ENG_NOUN:CAPITAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:КАПЛЯ {} <to_english> ENG_NOUN:DROP {}
 link СУЩЕСТВИТЕЛЬНОЕ:КАПРОН {} <to_english> ENG_NOUN:KAPRON {}
 link СУЩЕСТВИТЕЛЬНОЕ:КАПУСТА {} <to_english> ENG_NOUN:CABBAGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:КАРАНДАШ {} <to_english> ENG_NOUN:PENCIL {}
 link СУЩЕСТВИТЕЛЬНОЕ:КАРАНТИН {} <to_english> ENG_NOUN:QUARANTINE {}
 link СУЩЕСТВИТЕЛЬНОЕ:КАРИКАТУРА {} <to_english> ENG_NOUN:CARTOON {}
 link СУЩЕСТВИТЕЛЬНОЕ:КАРИКАТУРА {} <to_english> ENG_NOUN:CARICATURE {}
 link СУЩЕСТВИТЕЛЬНОЕ:КАРКАС {} <to_english> ENG_NOUN:FRAMEWORK {}
 link СУЩЕСТВИТЕЛЬНОЕ:КАРМАН {} <to_english> ENG_NOUN:POCKET {}
 link СУЩЕСТВИТЕЛЬНОЕ:КАРТИНА {} <to_english> ENG_NOUN:PICTURE {}
 link СУЩЕСТВИТЕЛЬНОЕ:КАРНИЗ {} <to_english> ENG_NOUN:CORNICE {}
 link СУЩЕСТВИТЕЛЬНОЕ:КАРТА {} <to_english> ENG_NOUN:MAP {}
 link СУЩЕСТВИТЕЛЬНОЕ:КАРТОН {} <to_english> ENG_NOUN:CARDBOARD {}
 link СУЩЕСТВИТЕЛЬНОЕ:КАРТОФЕЛЬ {} <to_english> ENG_NOUN:POTATO {}
 link СУЩЕСТВИТЕЛЬНОЕ:КАРЬЕРА {} <to_english> ENG_NOUN:CAREER {}
 link СУЩЕСТВИТЕЛЬНОЕ:КАТАЛОГ {} <to_english> ENG_NOUN:CATALOGUE {}
 link СУЩЕСТВИТЕЛЬНОЕ:КАТЕГОРИЯ {} <to_english> ENG_NOUN:CATEGORY {}
 link СУЩЕСТВИТЕЛЬНОЕ:КАФЕ {} <to_english> ENG_NOUN:CAFE {}
 link СУЩЕСТВИТЕЛЬНОЕ:КАТУШКА {} <to_english> ENG_NOUN:REEL {}
 link СУЩЕСТВИТЕЛЬНОЕ:КАТУШКА {} <to_english> ENG_NOUN:BOBBIN {}
 link СУЩЕСТВИТЕЛЬНОЕ:КАЧЕСТВО {} <to_english> ENG_NOUN:QUALITY {}
 link СУЩЕСТВИТЕЛЬНОЕ:КАША {} <to_english> ENG_NOUN:CEREAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:КАША {} <to_english> ENG_NOUN:PORRIDGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:КАШЕЛЬ {} <to_english> ENG_NOUN:COUGH {}
 link СУЩЕСТВИТЕЛЬНОЕ:КВАРТИРА {} <to_english> ENG_NOUN:FLAT {}
 link СУЩЕСТВИТЕЛЬНОЕ:КВАРТИРА {} <to_english> ENG_NOUN:APARTMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:КВАС {} <to_english> ENG_NOUN:KVAS {}
 link СУЩЕСТВИТЕЛЬНОЕ:КВОРУМ {} <to_english> ENG_NOUN:QUORUM {}
 link СУЩЕСТВИТЕЛЬНОЕ:КЕПКА {} <to_english> ENG_NOUN:CAP {}
 link СУЩЕСТВИТЕЛЬНОЕ:КЕФИР {} <to_english> ENG_NOUN:BUTTERMILK {}
 link СУЩЕСТВИТЕЛЬНОЕ:КИЛОГРАММ {} <to_english> ENG_NOUN:KILOGRAM {}
 link СУЩЕСТВИТЕЛЬНОЕ:КИЛОМЕТР {} <to_english> ENG_NOUN:KILOMETRE {}
 link СУЩЕСТВИТЕЛЬНОЕ:КИОСК {} <to_english> ENG_NOUN:STALL {}
 link СУЩЕСТВИТЕЛЬНОЕ:КИОСК {} <to_english> ENG_NOUN:STAND {}
 link СУЩЕСТВИТЕЛЬНОЕ:КИОСК {} <to_english> ENG_NOUN:BOOTH {}
 link СУЩЕСТВИТЕЛЬНОЕ:КИРПИЧ {} <to_english> ENG_NOUN:BRICK {}
 link СУЩЕСТВИТЕЛЬНОЕ:КИСЛОРОД {} <to_english> ENG_NOUN:OXYGENE {}
 link СУЩЕСТВИТЕЛЬНОЕ:КИТАЙ {} <to_english> ENG_NOUN:CHINA {}
 link СУЩЕСТВИТЕЛЬНОЕ:КИСТЬ {} <to_english> ENG_NOUN:HAND {}
 link СУЩЕСТВИТЕЛЬНОЕ:КИСТЬ {} <to_english> ENG_NOUN:CLUSTER {}
 link СУЩЕСТВИТЕЛЬНОЕ:КИСТЬ {} <to_english> ENG_NOUN:BUNCH {}
 link СУЩЕСТВИТЕЛЬНОЕ:КЛАВИША {} <to_english> ENG_NOUN:KEY {}
 link СУЩЕСТВИТЕЛЬНОЕ:КЛАССИК {} <to_english> ENG_NOUN:CLASSIC {}
 link СУЩЕСТВИТЕЛЬНОЕ:КЛЕВЕР {} <to_english> ENG_NOUN:CLOVER {}
 link СУЩЕСТВИТЕЛЬНОЕ:КЛЕВЕТА {} <to_english> ENG_NOUN:SLANDER {}
 link СУЩЕСТВИТЕЛЬНОЕ:КЛЕВЕТА {} <to_english> ENG_NOUN:CALUMNY {}
 link СУЩЕСТВИТЕЛЬНОЕ:КЛЕТКА {} <to_english> ENG_NOUN:CAGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:КЛЕТКА {} <to_english> ENG_NOUN:CELL {}
 link СУЩЕСТВИТЕЛЬНОЕ:КЛИМАТ {} <to_english> ENG_NOUN:CLIMATE {}
 link СУЩЕСТВИТЕЛЬНОЕ:КЛИНИКА {} <to_english> ENG_NOUN:CLINIC {}
 link СУЩЕСТВИТЕЛЬНОЕ:КЛЮКВА {} <to_english> ENG_NOUN:CRANBERRY {}
 link СУЩЕСТВИТЕЛЬНОЕ:КЛУБНИКА {} <to_english> ENG_NOUN:STRAWBERRY {}
 link СУЩЕСТВИТЕЛЬНОЕ:КЛЮЧ {} <to_english> ENG_NOUN:KEY {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОАЛИЦИЯ {} <to_english> ENG_NOUN:COALITION {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОВЕР {} <to_english> ENG_NOUN:CARPET {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОВЕР {} <to_english> ENG_NOUN:RUG {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОВРИК {} <to_english> ENG_NOUN:MAT {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОДЕКС {} <to_english> ENG_NOUN:CODE {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОЖА {} <to_english> ENG_NOUN:LEATHER {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОЗЕЛ {} <to_english> ENG_NOUN:GOAT {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОЗОЧКА {} <to_english> ENG_NOUN:GOAT {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОЗЫРЬ {} <to_english> ENG_NOUN:TRUMP {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОЛБАСА {} <to_english> ENG_NOUN:SAUSAGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОЛЕБАНИЕ {} <to_english> ENG_NOUN:OSCILLATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОЛЕНО {} <to_english> ENG_NOUN:KNEE {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОЛЕСО {} <to_english> ENG_NOUN:WHEEL {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОЛИЧЕСТВО {} <to_english> ENG_NOUN:QUANTITY {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОЛИЧЕСТВО {} <to_english> ENG_NOUN:AMOUNT {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОЛИЧЕСТВО {} <to_english> ENG_NOUN:NUMBER {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОЛЛЕКЦИЯ {} <to_english> ENG_NOUN:COLLECTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОЛОДА {} <to_english> ENG_NOUN:PACK {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОЛОДЕЦ {} <to_english> ENG_NOUN:WELL {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОЛОКОЛ {} <to_english> ENG_NOUN:BELL {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОЛОНИЯ {} <to_english> ENG_NOUN:COLONY {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОЛОННА {} <to_english> ENG_NOUN:PILLAR {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОЛОС {} <to_english> ENG_NOUN:EAR {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОЛОС {} <to_english> ENG_NOUN:SPIKE {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОЛЬЦО {} <to_english> ENG_NOUN:RING {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОЛЯСКА {} <to_english> ENG_NOUN:CARRIAGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОМАНДА {} <to_english> ENG_NOUN:CREW {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОМАР {} <to_english> ENG_NOUN:MOSQUITO {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОМИССИЯ {} <to_english> ENG_NOUN:COMMITTEE {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОММУНИЗМ {} <to_english> ENG_NOUN:COMUNISM {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОМНАТА {} <to_english> ENG_NOUN:ROOM {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОМПИЛЯТОР {} <to_english> ENG_NOUN:COMPILER {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОМПИЛЯЦИЯ {} <to_english> ENG_NOUN:COMPILATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОМПОЗИТОР {} <to_english> ENG_NOUN:COMPOSER {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОНВЕРТ {} <to_english> ENG_NOUN:ENVELOPE {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОНГРЕСС {} <to_english> ENG_NOUN:CONGRESS {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОНКУРС {} <to_english> ENG_NOUN:COMPETITION {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОНКУРЕНЦИЯ {} <to_english> ENG_NOUN:COMPETITION {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОНСТИТУЦИЯ {} <to_english> ENG_NOUN:CONSTITUTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОНСТРУКТОР {} <to_english> ENG_NOUN:DESIGNER {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОНТИНЕНТ {} <to_english> ENG_NOUN:CONTINENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОНТОРА {} <to_english> ENG_NOUN:OFFICE {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОНТРОЛЬ {} <to_english> ENG_NOUN:CONTROL {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОНСУЛЬТАНТ {} <to_english> ENG_NOUN:CONSULTANT {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОНСУЛЬТАЦИЯ {} <to_english> ENG_NOUN:CONSULTATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОНТРАСТ {} <to_english> ENG_NOUN:CONTRAST {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОНТЕЙНЕР {} <to_english> ENG_NOUN:CONTAINER {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОНТРОЛЬ {} <to_english> ENG_NOUN:INSPECTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОНЦЕРТ {} <to_english> ENG_NOUN:CONCERT {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОНЬЯК {} <to_english> ENG_NOUN:BRANDY {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОНЬЯК {} <to_english> ENG_NOUN:COGNAC {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОПИЯ {} <to_english> ENG_NOUN:COPY {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОПЬЕ {} <to_english> ENG_NOUN:SPEAR {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОРАБЛЬ {} <to_english> ENG_NOUN:VESSEL {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОРЕНЬ {} <to_english> ENG_NOUN:ROOT {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОРЗИНКА {} <to_english> ENG_NOUN:BASKET {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОРОНА {} <to_english> ENG_NOUN:CROWN {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОРРЕСПОНДЕНТ {} <to_english> ENG_NOUN:CORRESPONDENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОРОБКА {} <to_english> ENG_NOUN:BOX {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОСМОНАВТ {} <to_english> ENG_NOUN:SPACEMAN {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОСМОНАВТ {} <to_english> ENG_NOUN:ASTRONAUT {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОСМОНАВТ {} <to_english> ENG_NOUN:COSMONAUT {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОСТЮМ {} <to_english> ENG_NOUN:COSTUME {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОСТЮМ {} <to_english> ENG_NOUN:DRESS {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОТЛЕТА {} <to_english> ENG_NOUN:CHOP {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОТЛЕТА {} <to_english> ENG_NOUN:CUTLET {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОФТОЧКА {} <to_english> ENG_NOUN:BLOUSE {}
 link СУЩЕСТВИТЕЛЬНОЕ:КРАБ {} <to_english> ENG_NOUN:CRAB {}
 link СУЩЕСТВИТЕЛЬНОЕ:КРАЙ {} <to_english> ENG_NOUN:BRIM {}
 link СУЩЕСТВИТЕЛЬНОЕ:КРАЙ {} <to_english> ENG_NOUN:EDGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:КРАН {} <to_english> ENG_NOUN:TAP {}
 link СУЩЕСТВИТЕЛЬНОЕ:КРАН {} <to_english> ENG_NOUN:FAUCET {}
 link СУЩЕСТВИТЕЛЬНОЕ:КРАН {} <to_english> ENG_NOUN:CRANE {}
 link СУЩЕСТВИТЕЛЬНОЕ:КРАСКА {} <to_english> ENG_NOUN:PAINT {}
 link СУЩЕСТВИТЕЛЬНОЕ:КРЕМ {} <to_english> ENG_NOUN:CREAM {}
 link СУЩЕСТВИТЕЛЬНОЕ:КРЕДИТ {} <to_english> ENG_NOUN:CREDIT {}
 link СУЩЕСТВИТЕЛЬНОЕ:КРЕПОСТЬ {} <to_english> ENG_NOUN:STRONGHOLD {}
 link СУЩЕСТВИТЕЛЬНОЕ:КРЕПОСТЬ {} <to_english> ENG_NOUN:FORTRESS {}
 link СУЩЕСТВИТЕЛЬНОЕ:КРЕСТ {} <to_english> ENG_NOUN:CROSS {}
 link СУЩЕСТВИТЕЛЬНОЕ:КРИЗИС {} <to_english> ENG_NOUN:CRISIS {}
 link СУЩЕСТВИТЕЛЬНОЕ:КРИК {} <to_english> ENG_NOUN:SHOUT {}
 link СУЩЕСТВИТЕЛЬНОЕ:КРИК {} <to_english> ENG_NOUN:CRY {}
 link СУЩЕСТВИТЕЛЬНОЕ:КРИСТАЛЛ {} <to_english> ENG_NOUN:CRYSTAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:КРИСТАЛЛИК {} <to_english> ENG_NOUN:CRYSTAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:КРИТИКА {} <to_english> ENG_NOUN:CRITICISM {}
 link СУЩЕСТВИТЕЛЬНОЕ:КРОВАТЬ {} <to_english> ENG_NOUN:COT {}
 link СУЩЕСТВИТЕЛЬНОЕ:КРОЛИК {} <to_english> ENG_NOUN:RABBIT {}
 link СУЩЕСТВИТЕЛЬНОЕ:КРОШКА {} <to_english> ENG_NOUN:CRUMB {}
 link СУЩЕСТВИТЕЛЬНОЕ:КРУЖКА {} <to_english> ENG_NOUN:MUG {}
 link СУЩЕСТВИТЕЛЬНОЕ:КРЫЛО {} <to_english> ENG_NOUN:WING {}
 link СУЩЕСТВИТЕЛЬНОЕ:КРЫЛЬЦО {} <to_english> ENG_NOUN:PORCH {}
 link СУЩЕСТВИТЕЛЬНОЕ:КРЫША {} <to_english> ENG_NOUN:ROOF {}
 link СУЩЕСТВИТЕЛЬНОЕ:КРЫШКА {} <to_english> ENG_NOUN:LID {}
 link СУЩЕСТВИТЕЛЬНОЕ:КРЫШКА {} <to_english> ENG_NOUN:COVER {}
 link СУЩЕСТВИТЕЛЬНОЕ:КРЫШКА {} <to_english> ENG_NOUN:TOP {}
 link СУЩЕСТВИТЕЛЬНОЕ:КУБОК {} <to_english> ENG_NOUN:CUP {}
 link СУЩЕСТВИТЕЛЬНОЕ:КУЛЬТУРА {} <to_english> ENG_NOUN:CULTURE {}
 link СУЩЕСТВИТЕЛЬНОЕ:КУПЛЕТ {} <to_english> ENG_NOUN:STANZA {}
 link СУЩЕСТВИТЕЛЬНОЕ:КУПЛЕТ {} <to_english> ENG_NOUN:VERSE {}
 link СУЩЕСТВИТЕЛЬНОЕ:КУРИЛЬЩИК {} <to_english> ENG_NOUN:SMOKER {}
 link СУЩЕСТВИТЕЛЬНОЕ:КУРИЦА {} <to_english> ENG_NOUN:HEN {}
 link СУЩЕСТВИТЕЛЬНОЕ:КУРИЦА {} <to_english> ENG_NOUN:CHICKEN {}
 link СУЩЕСТВИТЕЛЬНОЕ:КУРТКА {} <to_english> ENG_NOUN:JACKET {}
 link СУЩЕСТВИТЕЛЬНОЕ:КУРЬЕР {} <to_english> ENG_NOUN:COURIER {}
 link СУЩЕСТВИТЕЛЬНОЕ:КУСОК {} <to_english> ENG_NOUN:PIECE {}
 link СУЩЕСТВИТЕЛЬНОЕ:КУСТ {} <to_english> ENG_NOUN:BUSH {}
 link СУЩЕСТВИТЕЛЬНОЕ:КУХНЯ {} <to_english> ENG_NOUN:KITCHEN {}
 link СУЩЕСТВИТЕЛЬНОЕ:КУШЕТКА {} <to_english> ENG_NOUN:COUCH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛАБОРАТОРИЯ {} <to_english> ENG_NOUN:LABORATORY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛАВКА {} <to_english> ENG_NOUN:SHOP {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛАВСАН {} <to_english> ENG_NOUN:LAVSAN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛАГЕРЬ {} <to_english> ENG_NOUN:CAMP {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛАЗЕР {} <to_english> ENG_NOUN:LASER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛАМПА {} <to_english> ENG_NOUN:LAMP {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛАМПОЧКА {} <to_english> ENG_NOUN:LAMP {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛАМПОЧКА {} <to_english> ENG_NOUN:BULB {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛАУРЕАТ {} <to_english> ENG_NOUN:LAUREATE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛЕБЕДЬ {} <to_english> ENG_NOUN:SWAN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛЕВ {CharCasing:Lower} <to_english> ENG_NOUN:LION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛЕГЕНДА {} <to_english> ENG_NOUN:LEGEND {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛЕД {} <to_english> ENG_NOUN:ICE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛЕЗВИЕ {} <to_english> ENG_NOUN:BLADE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛЕКТОР {} <to_english> ENG_NOUN:LECTURER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛЕКТОР {} <to_english> ENG_NOUN:READER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛЕКЦИЯ {} <to_english> ENG_NOUN:LECTURE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛЕСТНИЦА {} <to_english> ENG_NOUN:STAIRCASE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛЕТЧИК {} <to_english> ENG_NOUN:PILOT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛЕТЧИК {} <to_english> ENG_NOUN:FLIER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛИВЕНЬ {} <to_english> ENG_NOUN:SHOWER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛИВЕНЬ {} <to_english> ENG_NOUN:DOWNPOUR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛИМОН {} <to_english> ENG_NOUN:LEMON {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛИНИЯ {} <to_english> ENG_NOUN:LINE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛИПА {} <to_english> ENG_NOUN:LINDEN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛИСТ {} <to_english> ENG_NOUN:SHEET {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛИСТ {} <to_english> ENG_NOUN:LEAF {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛИТЕРАТУРА {} <to_english> ENG_NOUN:LITERATURE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛИТР {} <to_english> ENG_NOUN:LITRE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛИФТ {} <to_english> ENG_NOUN:LIFT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛИФТ {} <to_english> ENG_NOUN:ELEVATOR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛИХОРАДКА {} <to_english> ENG_NOUN:FEVER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛОБ {} <to_english> ENG_NOUN:FOREHEAD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛОДКА {} <to_english> ENG_NOUN:BOAT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛОДЫЖКА {} <to_english> ENG_NOUN:ANKLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛОЖКА {} <to_english> ENG_NOUN:SPOON {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛОЖЬ {} <to_english> ENG_NOUN:LIE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛОКОТЬ {} <to_english> ENG_NOUN:ELBOW {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛОМТИК {} <to_english> ENG_NOUN:SLICE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛОПАТА {} <to_english> ENG_NOUN:SHOVEL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛОПАТА {} <to_english> ENG_NOUN:SPADE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛОСОСЬ {} <to_english> ENG_NOUN:SALMON {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛУЖА {} <to_english> ENG_NOUN:PUDDLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛУК {} <to_english> ENG_NOUN:ONION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛУК {} <to_english> ENG_NOUN:BOW {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛУЧ {} <to_english> ENG_NOUN:RAY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛУЧ {} <to_english> ENG_NOUN:BEAM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛЮБИТЕЛЬ {} <to_english> ENG_NOUN:LOVER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛЮБИТЕЛЬ {} <to_english> ENG_NOUN:FAN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛЮБИТЕЛЬ {} <to_english> ENG_NOUN:AMATEUR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛЮБОВЬ { одуш:неодуш } <to_english> ENG_NOUN:LOVE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛЮСТРА {} <to_english> ENG_NOUN:CHANDELIER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЛЯГУШКА {} <to_english> ENG_NOUN:FROG {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАГИСТРАЛЬ {} <to_english> ENG_NOUN:HIGHWAY {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАЙ {} <to_english> ENG_NOUN:MAY {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАК {} <to_english> ENG_NOUN:POPPY {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАЛИНА {} <to_english> ENG_NOUN:RASPBERRY {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАМА {} <to_english> ENG_NOUN:MOTHER {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАМА {} <to_english> ENG_NOUN:MAMMA {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАМА {} <to_english> ENG_NOUN:MUMMY {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАНДАРИН {} <to_english> ENG_NOUN:MANDARIN {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАНДАРИН {} <to_english> ENG_NOUN:TANGERINE {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАНИПУЛИРОВАНИЕ {} <to_english> ENG_NOUN:MANUPULATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАРГАРИН {} <to_english> ENG_NOUN:MARGARINE {}

 // ----------

 link СУЩЕСТВИТЕЛЬНОЕ:МАССА {} <to_english> ENG_NOUN:MASS {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАСЛО {} <to_english> ENG_NOUN:BUTTER {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАСЛО {} <to_english> ENG_NOUN:OIL {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАСШТАБ {} <to_english> ENG_NOUN:SCALE {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАТЕМАТИК {} <to_english> ENG_NOUN:MATEMATICIAN {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАТЕМАТИКА {} <to_english> ENG_NOUN:MATEMATICS {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАТЕРИАЛИЗМ {} <to_english> ENG_NOUN:MATERIALISM {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАТЕРИАЛ {} <to_english> ENG_NOUN:MATERIAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАТЕРИАЛ {} <to_english> ENG_NOUN:STUFF {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАТЕРИАЛ {} <to_english> ENG_NOUN:CLOTH {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАТЕРИК {} <to_english> ENG_NOUN:CONTINENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАТЕРИЯ {} <to_english> ENG_NOUN:CLOTH {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАТЕРИЯ {} <to_english> ENG_NOUN:MATERIAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАТЕРИЯ {} <to_english> ENG_NOUN:STUFF {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАТЕРИЯ {} <to_english> ENG_NOUN:SUBSTANCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАТЕРИЯ {} <to_english> ENG_NOUN:MATTER {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАТРАС {} <to_english> ENG_NOUN:MATTRESS {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАТРОС {} <to_english> ENG_NOUN:SAILOR {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАТЧ {} <to_english> ENG_NOUN:MATCH {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАЧТА {} <to_english> ENG_NOUN:MAST {}
 link СУЩЕСТВИТЕЛЬНОЕ:МАШИНА {} <to_english> ENG_NOUN:ENGINE {}
 link СУЩЕСТВИТЕЛЬНОЕ:МЕДВЕДЬ {} <to_english> ENG_NOUN:BEAR {}
 link СУЩЕСТВИТЕЛЬНОЕ:МЕДИЦИНА {} <to_english> ENG_NOUN:MEDICINE {}
 link СУЩЕСТВИТЕЛЬНОЕ:МЕЛОДИЯ {} <to_english> ENG_NOUN:MELODY {}
 link СУЩЕСТВИТЕЛЬНОЕ:МЕНЮ {} <to_english> ENG_NOUN:MENU {}
 link СУЩЕСТВИТЕЛЬНОЕ:МЕРА {} <to_english> ENG_NOUN:MEASURE {}
 link СУЩЕСТВИТЕЛЬНОЕ:МЕРКА {} <to_english> ENG_NOUN:MEASURE {}
 link СУЩЕСТВИТЕЛЬНОЕ:МЕСТНОСТЬ {} <to_english> ENG_NOUN:LOCALITY {}
 link СУЩЕСТВИТЕЛЬНОЕ:МЕСТО {} <to_english> ENG_NOUN:SPOT {}
 link СУЩЕСТВИТЕЛЬНОЕ:МЕСТОНАХОЖДЕНИЕ {} <to_english> ENG_NOUN:LOCATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:МЕСТОПРЕБЫВАНИЕ {} <to_english> ENG_NOUN:RESIDENCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:МЕСЯЦ {} <to_english> ENG_NOUN:MONTH {}
 link СУЩЕСТВИТЕЛЬНОЕ:МЕТАЛЛ {} <to_english> ENG_NOUN:METAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:МЕТКА {} <to_english> ENG_NOUN:MARK {}
 link СУЩЕСТВИТЕЛЬНОЕ:МЕТР {} <to_english> ENG_NOUN:METRE {}
 link СУЩЕСТВИТЕЛЬНОЕ:МЕТРО {} <to_english> ENG_NOUN:UNDERGROUND {}
 link СУЩЕСТВИТЕЛЬНОЕ:МЕТРО {} <to_english> ENG_NOUN:SUBWAY {}
 link СУЩЕСТВИТЕЛЬНОЕ:МЕХ {} <to_english> ENG_NOUN:FUR {}
 link СУЩЕСТВИТЕЛЬНОЕ:МЕХАНИЗМ {} <to_english> ENG_NOUN:MECHANISM {}
 link СУЩЕСТВИТЕЛЬНОЕ:МЕХАНИЗМ {} <to_english> ENG_NOUN:GEAR {}
 link СУЩЕСТВИТЕЛЬНОЕ:МЕХАНИЗМ {} <to_english> ENG_NOUN:MACHINERY {}
 link СУЩЕСТВИТЕЛЬНОЕ:МЕЧТА {} <to_english> ENG_NOUN:DREAM {}
 link СУЩЕСТВИТЕЛЬНОЕ:МЕШОК {} <to_english> ENG_NOUN:SACK {}
 link СУЩЕСТВИТЕЛЬНОЕ:МЕШОК {} <to_english> ENG_NOUN:BAG {}
 link СУЩЕСТВИТЕЛЬНОЕ:МИГ {} <to_english> ENG_NOUN:INSTANT {}
 link СУЩЕСТВИТЕЛЬНОЕ:МИКРОФОН {} <to_english> ENG_NOUN:MICROPHONE {}
 link СУЩЕСТВИТЕЛЬНОЕ:МИКСТУРА {} <to_english> ENG_NOUN:MIXTURE {}
 link ЧИСЛИТЕЛЬНОЕ:МИЛЛИОН {} <to_english> ENG_NOUN:MILLION {}
 link ЧИСЛИТЕЛЬНОЕ:МИЛЛИАРД {} <to_english> ENG_NOUN:MILLIARD {}
 link ЧИСЛИТЕЛЬНОЕ:МИЛЛИАРД {} <to_english> ENG_NOUN:BILLION {}
 link СУЩЕСТВИТЕЛЬНОЕ:МИЛЯ {} <to_english> ENG_NOUN:MILE {}
 link СУЩЕСТВИТЕЛЬНОЕ:МИНИСТР {} <to_english> ENG_NOUN:MINISTER {}
 link СУЩЕСТВИТЕЛЬНОЕ:МИССИЯ {} <to_english> ENG_NOUN:MISSION {}
 link СУЩЕСТВИТЕЛЬНОЕ:МОГИЛА {} <to_english> ENG_NOUN:GRAVE {}
 link СУЩЕСТВИТЕЛЬНОЕ:МОДА {} <to_english> ENG_NOUN:FASHION {}
 link СУЩЕСТВИТЕЛЬНОЕ:МОДА {} <to_english> ENG_NOUN:VOGUE {}
 link СУЩЕСТВИТЕЛЬНОЕ:МОЛНИЯ {} <to_english> ENG_NOUN:LIGHTNING {}
 link СУЩЕСТВИТЕЛЬНОЕ:МОЛИТВА {} <to_english> ENG_NOUN:PRAYER {}
 link СУЩЕСТВИТЕЛЬНОЕ:МОЛОКО {} <to_english> ENG_NOUN:MILK {}
 link СУЩЕСТВИТЕЛЬНОЕ:МОЛОТ {} <to_english> ENG_NOUN:HAMMER {}
 link СУЩЕСТВИТЕЛЬНОЕ:МОЛОТОК {} <to_english> ENG_NOUN:HAMMER {}
 link СУЩЕСТВИТЕЛЬНОЕ:МОНАХ {} <to_english> ENG_NOUN:MONK {}
 link СУЩЕСТВИТЕЛЬНОЕ:МОНАШКА {} <to_english> ENG_NOUN:NUN {}
 link СУЩЕСТВИТЕЛЬНОЕ:МОНЕТА {} <to_english> ENG_NOUN:COIN {}
 link СУЩЕСТВИТЕЛЬНОЕ:МОНЕТКА {} <to_english> ENG_NOUN:COIN {}
 link СУЩЕСТВИТЕЛЬНОЕ:МОНИТОР {} <to_english> ENG_NOUN:MONITOR {}
 link СУЩЕСТВИТЕЛЬНОЕ:МОНИТОРИНГ {} <to_english> ENG_NOUN:MONITORING {}
 link СУЩЕСТВИТЕЛЬНОЕ:МОНУМЕНТ {} <to_english> ENG_NOUN:MONUMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:МОРКОВКА {} <to_english> ENG_NOUN:CARROT {}
 link СУЩЕСТВИТЕЛЬНОЕ:МОРОЗ {} <to_english> ENG_NOUN:FROST {}
 link СУЩЕСТВИТЕЛЬНОЕ:МОСТ {} <to_english> ENG_NOUN:BRIDGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:МОТИВ {} <to_english> ENG_NOUN:TUNE {}
 link СУЩЕСТВИТЕЛЬНОЕ:МОТОР {} <to_english> ENG_NOUN:ENGINE {}
 link СУЩЕСТВИТЕЛЬНОЕ:МОТОР {} <to_english> ENG_NOUN:MOTOR {}
 link СУЩЕСТВИТЕЛЬНОЕ:МОЩЬ {} <to_english> ENG_NOUN:MIGHT {}
 link СУЩЕСТВИТЕЛЬНОЕ:МРАМОР {} <to_english> ENG_NOUN:MARBLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:МУЖ {} <to_english> ENG_NOUN:HUSBAND {}
 link СУЩЕСТВИТЕЛЬНОЕ:МУЗЕЙ {} <to_english> ENG_NOUN:MUSEUM {}
 link СУЩЕСТВИТЕЛЬНОЕ:МУЗЫКАНТ {} <to_english> ENG_NOUN:MUSICIAN {}
 link СУЩЕСТВИТЕЛЬНОЕ:МУЗЫКА {} <to_english> ENG_NOUN:MUSIC {}
 link СУЩЕСТВИТЕЛЬНОЕ:МУСОР {} <to_english> ENG_NOUN:RUBBISH {}
 link СУЩЕСТВИТЕЛЬНОЕ:МУСОР {} <to_english> ENG_NOUN:GARBAGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:МУХА {} <to_english> ENG_NOUN:FLY {}
 link СУЩЕСТВИТЕЛЬНОЕ:МЫС {} <to_english> ENG_NOUN:CAPE {}
 link СУЩЕСТВИТЕЛЬНОЕ:МЫШКА {} <to_english> ENG_NOUN:MOUSE {}
 link СУЩЕСТВИТЕЛЬНОЕ:МЫШЦА {} <to_english> ENG_NOUN:MUSCLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:МЯСО {} <to_english> ENG_NOUN:FLESH {}
 link СУЩЕСТВИТЕЛЬНОЕ:МЯСО {} <to_english> ENG_NOUN:MEAT {}
 link СУЩЕСТВИТЕЛЬНОЕ:МЯЧ {} <to_english> ENG_NOUN:BALL {}

 // ----------------------------------------------------------

 link СУЩЕСТВИТЕЛЬНОЕ:НАБЛЮДАТЕЛЬ {} <to_english> ENG_NOUN:OBSERVER {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАБЛЮДЕНИЕ {} <to_english> ENG_NOUN:OBSERVATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАБОР {} <to_english> ENG_NOUN:ADMISSION {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАБОР {} <to_english> ENG_NOUN:SET {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАБОР {} <to_english> ENG_NOUN:KIT {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАВОДНЕНИЕ {} <to_english> ENG_NOUN:FLOOD {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАВОЗ {} <to_english> ENG_NOUN:MANURE {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАГЛОСТЬ {} <to_english> ENG_NOUN:IMPUDENCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАГРАДА {} <to_english> ENG_NOUN:REWARD {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАДПИСЬ {} <to_english> ENG_NOUN:INSCRIPTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАЗВАНИЕ {} <to_english> ENG_NOUN:NAME {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАЗНАЧЕНИЕ {} <to_english> ENG_NOUN:APPOINTMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАИМЕНОВАНИЕ {} <to_english> ENG_NOUN:NAME {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАИМЕНОВАНИЕ {} <to_english> ENG_NOUN:DENOMINATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАМЕК {} <to_english> ENG_NOUN:HINT {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАПАДЕНИЕ {} <to_english> ENG_NOUN:ATTACK {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАПИТОК {} <to_english> ENG_NOUN:DRINK {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАПИТОК {} <to_english> ENG_NOUN:BEVARAGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАПРАВЛЕНИЕ {} <to_english> ENG_NOUN:DIRECTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАПРЯЖЕНИЕ {} <to_english> ENG_NOUN:STRAIN {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАРУЖНОСТЬ {} <to_english> ENG_NOUN:APPEARANCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАРУШЕНИЕ {} <to_english> ENG_NOUN:BREACH {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАРУШЕНИЕ {} <to_english> ENG_NOUN:INFRINGEMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАРУШЕНИЕ {} <to_english> ENG_NOUN:VIOLATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАРУШЕНИЕ {} <to_english> ENG_NOUN:DISTURBANCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАРЫВ {} <to_english> ENG_NOUN:ABSCESS {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАРЯД {} <to_english> ENG_NOUN:DRESS {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАРЯД {} <to_english> ENG_NOUN:ATTIRE {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАСЕКОМОЕ {} <to_english> ENG_NOUN:INSECT {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАСЕЛЕНИЕ {} <to_english> ENG_NOUN:POPULATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАСМЕШКА {} <to_english> ENG_NOUN:MOCKERY {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАСОС {} <to_english> ENG_NOUN:PUMP {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАСТРОЕНИЕ {} <to_english> ENG_NOUN:MOOD {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАУКА {} <to_english> ENG_NOUN:SCIENCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАХОДКА {} <to_english> ENG_NOUN:FIND {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАЦИЯ {} <to_english> ENG_NOUN:NATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАЦИОНАЛЬНОСТЬ {} <to_english> ENG_NOUN:NATIONALITY {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАЧАЛО {} <to_english> ENG_NOUN:BEGINNING {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАЧАЛЬНИК {} <to_english> ENG_NOUN:CHIEF {}
 link СУЩЕСТВИТЕЛЬНОЕ:НАЧАЛЬНИК {} <to_english> ENG_NOUN:SUPERIOR {}
 link СУЩЕСТВИТЕЛЬНОЕ:НЕБО {} <to_english> ENG_NOUN:SKY {}
 link СУЩЕСТВИТЕЛЬНОЕ:НЕВЕСОМОСТЬ {} <to_english> ENG_NOUN:WEIGHTLESSNESS {}
 link СУЩЕСТВИТЕЛЬНОЕ:НЕВЕСТА {} <to_english> ENG_NOUN:FIANCEE {}
 link СУЩЕСТВИТЕЛЬНОЕ:НЕВЕСТА {} <to_english> ENG_NOUN:BRIDE {}
 link СУЩЕСТВИТЕЛЬНОЕ:НЕГОДОВАНИЕ {} <to_english> ENG_NOUN:INDIGNATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:НЕДОВЕРИЕ {} <to_english> ENG_NOUN:DISTRUST {}
 link СУЩЕСТВИТЕЛЬНОЕ:НЕДОРАЗУМЕНИЕ {} <to_english> ENG_NOUN:MISUNDERSTANDING {}
 link СУЩЕСТВИТЕЛЬНОЕ:НЕДОСМОТР {} <to_english> ENG_NOUN:OVERSIGHT {}
 link СУЩЕСТВИТЕЛЬНОЕ:НЕДОСТАТОК {} <to_english> ENG_NOUN:LACK {}
 link СУЩЕСТВИТЕЛЬНОЕ:НЕДОСТАТОК {} <to_english> ENG_NOUN:SHORTAGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:НЕЙЛОН {} <to_english> ENG_NOUN:NYLON {}
 link СУЩЕСТВИТЕЛЬНОЕ:НЕЙТРАЛИТЕТ {} <to_english> ENG_NOUN:NEUTRALITY {}
 link СУЩЕСТВИТЕЛЬНОЕ:НЕНАВИСТЬ {} <to_english> ENG_NOUN:HATRED {}
 link СУЩЕСТВИТЕЛЬНОЕ:НЕОДОБРЕНИЕ {} <to_english> ENG_NOUN:DISAPPROVAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:НЕОСТОРОЖНОСТЬ {} <to_english> ENG_NOUN:CARELESSNESS {}
 link СУЩЕСТВИТЕЛЬНОЕ:НЕПОНИМАНИЕ {} <to_english> ENG_NOUN:INCOMPREHENSION {}
 link СУЩЕСТВИТЕЛЬНОЕ:НЕПРАВДА {} <to_english> ENG_NOUN:FALSEHOOD {}
 link СУЩЕСТВИТЕЛЬНОЕ:НЕПРАВДА {} <to_english> ENG_NOUN:LIE {}
 link СУЩЕСТВИТЕЛЬНОЕ:НЕПРИКОСНОВЕННОСТЬ {} <to_english> ENG_NOUN:IMMUNITY {}
 link СУЩЕСТВИТЕЛЬНОЕ:НЕПРИЯТНОСТЬ {} <to_english> ENG_NOUN:TROUBLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:НЕРВ {} <to_english> ENG_NOUN:NERVE {}
 link СУЩЕСТВИТЕЛЬНОЕ:НЕСПРАВЕДЛИВОСТЬ {} <to_english> ENG_NOUN:INJUSTICE {}
 link СУЩЕСТВИТЕЛЬНОЕ:НЕТЕРПЕНИЕ {} <to_english> ENG_NOUN:IMPATIENCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:НЕУДАЧА {} <to_english> ENG_NOUN:FAILURE {}
 link СУЩЕСТВИТЕЛЬНОЕ:НЕФТЬ {} <to_english> ENG_NOUN:OIL {}
 link СУЩЕСТВИТЕЛЬНОЕ:НОГА {} <to_english> ENG_NOUN:FOOT {}
 link СУЩЕСТВИТЕЛЬНОЕ:НОГОТЬ {} <to_english> ENG_NOUN:NAIL {}
 link СУЩЕСТВИТЕЛЬНОЕ:НОЖНИЦЫ {} <to_english> ENG_NOUN:SCISSORS {}
 link СУЩЕСТВИТЕЛЬНОЕ:НОЛЬ {} <to_english> ENG_NOUN:ZERO {}
 link СУЩЕСТВИТЕЛЬНОЕ:НОМЕР {} <to_english> ENG_NOUN:NUMBER {}
 link СУЩЕСТВИТЕЛЬНОЕ:НОРМА {} <to_english> ENG_NOUN:QUOTA {}
 link СУЩЕСТВИТЕЛЬНОЕ:НОРМА {} <to_english> ENG_NOUN:RATE {}
 link СУЩЕСТВИТЕЛЬНОЕ:НОРМА {} <to_english> ENG_NOUN:STANDARD {}
 link СУЩЕСТВИТЕЛЬНОЕ:НОС {} <to_english> ENG_NOUN:NOSE {}
 link СУЩЕСТВИТЕЛЬНОЕ:НОСОК {} <to_english> ENG_NOUN:SOCK {}
 link СУЩЕСТВИТЕЛЬНОЕ:НОТА {} <to_english> ENG_NOUN:NOTE {}
 link СУЩЕСТВИТЕЛЬНОЕ:НОЯБРЬ {} <to_english> ENG_NOUN:NOVEMBER {}
 link СУЩЕСТВИТЕЛЬНОЕ:НЯНЬКА {} <to_english> ENG_NOUN:NURSE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБВИНЕНИЕ {} <to_english> ENG_NOUN:ACCUSATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБЕД {} <to_english> ENG_NOUN:LUNCH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБЕД {} <to_english> ENG_NOUN:DINNER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБЕЗЬЯНКА {} <to_english> ENG_NOUN:MONKEY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБЕЗЬЯНКА {} <to_english> ENG_NOUN:APE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБЕРТКА {} <to_english> ENG_NOUN:WRAPPER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБЕРТКА {} <to_english> ENG_NOUN:ENVELOPE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБЕСПЕЧЕНИЕ {} <to_english> ENG_NOUN:SECURITY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБЕЩАНИЕ {} <to_english> ENG_NOUN:PROMISE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБЗОР {} <to_english> ENG_NOUN:SURVEY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБЗОР {} <to_english> ENG_NOUN:REVIEW {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБИДА {} <to_english> ENG_NOUN:OFFENCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБИДА {} <to_english> ENG_NOUN:INSULT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБЛАКО {} <to_english> ENG_NOUN:CLOUD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБМАН {} <to_english> ENG_NOUN:FRAUD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБМАН {} <to_english> ENG_NOUN:DECEPTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБМАН {} <to_english> ENG_NOUN:HUMBUG {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБМЕН {} <to_english> ENG_NOUN:EXCHANGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБОЗРЕНИЕ {} <to_english> ENG_NOUN:REVIEW {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБОРОНА {} <to_english> ENG_NOUN:DEFENCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБОРУДОВАНИЕ {} <to_english> ENG_NOUN:EQUIPMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБОРУДОВАНИЕ {} <to_english> ENG_NOUN:MACHINERY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБРАЗ {} <to_english> ENG_NOUN:IMAGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБРАЗЕЦ {} <to_english> ENG_NOUN:MODEL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБРАЗЕЦ {} <to_english> ENG_NOUN:PATTERN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБРАЗЕЦ {} <to_english> ENG_NOUN:SAMPLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБРАЗЕЦ {} <to_english> ENG_NOUN:SPECIMEN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБРЫВ {} <to_english> ENG_NOUN:PRECIPICE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБСЕРВАТОРИЯ {} <to_english> ENG_NOUN:OBSERVATORY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБСЛУЖИВАНИЕ {} <to_english> ENG_NOUN:SERVICE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБСТАНОВКА {} <to_english> ENG_NOUN:FURNITURE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБСТАНОВКА {} <to_english> ENG_NOUN:SITUATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБСТАНОВКА {} <to_english> ENG_NOUN:CIRCUMSTANCES {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБСТОЯТЕЛЬСТВО {} <to_english> ENG_NOUN:CIRCUMSTANCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБСУЖДЕНИЕ {} <to_english> ENG_NOUN:DISCUSSION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБСУЖДЕНИЕ {} <to_english> ENG_NOUN:DEBATE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБУВЬ {} <to_english> ENG_NOUN:FOOTWEAR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБУЧЕНИЕ {} <to_english> ENG_NOUN:TRAINING {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБУЧЕНИЕ {} <to_english> ENG_NOUN:INSTRUCTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБЩЕСТВЕННОСТЬ {} <to_english> ENG_NOUN:PUBLIC {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБЩЕСТВО {} <to_english> ENG_NOUN:SOCIETY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБЩЕСТВО {} <to_english> ENG_NOUN:COMMUNITY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБЩНОСТЬ {} <to_english> ENG_NOUN:COMMUNITY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБЪЕДИНЕНИЕ {} <to_english> ENG_NOUN:UNION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБЪЕДИНЕНИЕ {} <to_english> ENG_NOUN:AMALGAMATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБЪЕДИНЕНИЕ {} <to_english> ENG_NOUN:MERGER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБЪЕМ {} <to_english> ENG_NOUN:VOLUME {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБЪЯСНЕНИЕ {} <to_english> ENG_NOUN:EXPLANATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБЪЯТИЕ {} <to_english> ENG_NOUN:EMBRACE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБЫЧАЙ {} <to_english> ENG_NOUN:CUSTOM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОБЯЗАННОСТЬ {} <to_english> ENG_NOUN:DUTY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОВОЩ {} <to_english> ENG_NOUN:VEGETABLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОВЕЧКА {} <to_english> ENG_NOUN:SHEEP {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОГЛАВЛЕНИЕ {} <to_english> ENG_NOUN:CONTENTS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОГРАНИЧЕНИЕ {} <to_english> ENG_NOUN:RESTRICTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОГРАНИЧЕНИЕ {} <to_english> ENG_NOUN:LIMITATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОГУРЕЦ {} <to_english> ENG_NOUN:CUCUNBER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОГУРЕЦ {} <to_english> ENG_NOUN:CUCUMBER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОДЕЯЛО {} <to_english> ENG_NOUN:BLANKET {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОДОБРЕНИЕ {} <to_english> ENG_NOUN:APPROVAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОДОЛЖЕНИЕ {} <to_english> ENG_NOUN:FAVOUR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОЖИВЛЕНИЕ {} <to_english> ENG_NOUN:ANIMATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОЖОГ {} <to_english> ENG_NOUN:BURN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОЗЕРО {} <to_english> ENG_NOUN:LAKE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОКРУГ {} <to_english> ENG_NOUN:DISTRICT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОКРУЖЕНИЕ {} <to_english> ENG_NOUN:ENVIRONMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОКТЯБРЬ {} <to_english> ENG_NOUN:OCTOBER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОПАСНОСТЬ {} <to_english> ENG_NOUN:DANGER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОПЕРА {} <to_english> ENG_NOUN:OPERA {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОПИСАНИЕ {} <to_english> ENG_NOUN:DESCRIPTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОПРАВДАНИЕ {} <to_english> ENG_NOUN:JUSTIFICATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОПРАВДАНИЕ {} <to_english> ENG_NOUN:EXCUSE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОПРОС {} <to_english> ENG_NOUN:INTERROGATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОПЫТ {} <to_english> ENG_NOUN:EXPERIENCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОРАТОР {} <to_english> ENG_NOUN:SPEAKER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОРБИТА {} <to_english> ENG_NOUN:ORBIT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОРГАНИЗАТОР {} <to_english> ENG_NOUN:ORGANIZER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОРГАНИЗАЦИЯ {} <to_english> ENG_NOUN:ORGANIZATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОРЕЛ {ОДУШ:ОДУШ} <to_english> ENG_NOUN:EAGLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОРКЕСТР {} <to_english> ENG_NOUN:ORCHESTRA {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОРНАМЕНТ {} <to_english> ENG_NOUN:ORNAMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОРОШЕНИЕ {} <to_english> ENG_NOUN:IRRIGATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОРУДИЕ {} <to_english> ENG_NOUN:IMPLEMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОРУДИЕ {} <to_english> ENG_NOUN:TOOL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОРУДИЕ {} <to_english> ENG_NOUN:INSTRUMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОРУДИЕ {} <to_english> ENG_NOUN:GUN {}

 // ---------------------------------

 link СУЩЕСТВИТЕЛЬНОЕ:ОСВЕЩЕНИЕ {} <to_english> ENG_NOUN:ILLUMINATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОСВОБОЖДЕНИЕ {} <to_english> ENG_NOUN:LIBERATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОСЕЛ {} <to_english> ENG_NOUN:DONKEY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОСЕЛ {} <to_english> ENG_NOUN:ASS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОСЕНЬ {} <to_english> ENG_NOUN:AUTUMN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОСЕНЬ {} <to_english> ENG_NOUN:FALL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОСЕТР {} <to_english> ENG_NOUN:STURGEON {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОСИНА {} <to_english> ENG_NOUN:ASPEN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОСЛОЖНЕНИЕ {} <to_english> ENG_NOUN:COMPLICATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОСМОТР {} <to_english> ENG_NOUN:INSPECTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОСМОТР {} <to_english> ENG_NOUN:EXAMINATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОСНОВАНИЕ {} <to_english> ENG_NOUN:FOUNDATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОСНОВАНИЕ {} <to_english> ENG_NOUN:REASON {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОСТАНОВКА {} <to_english> ENG_NOUN:STOP {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОСТРОВ {} <to_english> ENG_NOUN:ISLAND {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОСУШЕНИЕ {} <to_english> ENG_NOUN:DRAINAGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТВРАЩЕНИЕ {} <to_english> ENG_NOUN:DISGUST {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТВРАЩЕНИЕ {} <to_english> ENG_NOUN:LOATHING {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТГОВОРКА {} <to_english> ENG_NOUN:EXCUSE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТГОВОРКА {} <to_english> ENG_NOUN:PRETEXT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТДЕЛ {} <to_english> ENG_NOUN:SECTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТДЕЛ {} <to_english> ENG_NOUN:DEPARTMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТДЕЛЕНИЕ {} <to_english> ENG_NOUN:SECTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТДЕЛЕНИЕ {} <to_english> ENG_NOUN:DIVISION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТДЕЛЕНИЕ {} <to_english> ENG_NOUN:DEPARTMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТДЕЛЕНИЕ {} <to_english> ENG_NOUN:BRANCH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТДЫХ {} <to_english> ENG_NOUN:REST {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТДЫХ {} <to_english> ENG_NOUN:REPOSE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТДЫХ {} <to_english> ENG_NOUN:RELAXATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТДЫХ {} <to_english> ENG_NOUN:RECREATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТЕЧЕСТВО {} <to_english> ENG_NOUN:HOMELAND {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТЕЧЕСТВО {} <to_english> ENG_NOUN:MOTHERLAND {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТЗЫВ {} <to_english> ENG_NOUN:OPINION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТЗЫВ {} <to_english> ENG_NOUN:REFERENCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТЗЫВ {} <to_english> ENG_NOUN:REVIEW {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТКАЗ {} <to_english> ENG_NOUN:REFUSAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТКРЫТКА {} <to_english> ENG_NOUN:POSTCARD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТЛИЧИЕ {} <to_english> ENG_NOUN:DIFFIRENCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТЛИЧИЕ {} <to_english> ENG_NOUN:DISTINCTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТМЕТКА {} <to_english> ENG_NOUN:MARK {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТМЕТКА {} <to_english> ENG_NOUN:NOTE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТПЛЫТИЕ {} <to_english> ENG_NOUN:DEPARTURE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТПОР {} <to_english> ENG_NOUN:REBUFF {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТПУСК {} <to_english> ENG_NOUN:LEAVE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТПУСК {} <to_english> ENG_NOUN:HOLIDAY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТПУСК {} <to_english> ENG_NOUN:VACATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТРАЖЕНИЕ {} <to_english> ENG_NOUN:REFLECTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТРАЖЕНИЕ {} <to_english> ENG_NOUN:REPULSE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТРАСЛЬ {} <to_english> ENG_NOUN:BRANCH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТРАСЛЬ {} <to_english> ENG_NOUN:FIELD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТРЫВОК {} <to_english> ENG_NOUN:EXTRACT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТРЫВОК {} <to_english> ENG_NOUN:FRAGMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТРЫВОК {} <to_english> ENG_NOUN:PASSAGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТРЯД {} <to_english> ENG_NOUN:DETACHMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТСЕК {} <to_english> ENG_NOUN:SECTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТСЕК {} <to_english> ENG_NOUN:COMPARTMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТСЕК {} <to_english> ENG_NOUN:BAY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТСЕК {} <to_english> ENG_NOUN:MODULE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТСУТСТВИЕ {} <to_english> ENG_NOUN:ABSENCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТСУТСТВИЕ {} <to_english> ENG_NOUN:LACK {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТТЕНОК {} <to_english> ENG_NOUN:SHADE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТТЕНОК {} <to_english> ENG_NOUN:TINT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТТЕНОК {} <to_english> ENG_NOUN:HUE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТХОД {} <to_english> ENG_NOUN:DEPARTURE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТХОД {} <to_english> ENG_NOUN:DEVIATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТЧЕТ {} <to_english> ENG_NOUN:REPORT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОТЪЕЗД {} <to_english> ENG_NOUN:DEPARTURE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОФИЦИАНТ {} <to_english> ENG_NOUN:WAITER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОФИЦИАНТ {} <to_english> ENG_NOUN:STEWARD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОХОТА {} <to_english> ENG_NOUN:HUNTING {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОХОТНИК {} <to_english> ENG_NOUN:HUNTER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОХРАНА {} <to_english> ENG_NOUN:GUARD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОЦЕНКА {} <to_english> ENG_NOUN:EVALUATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОЦЕНКА {} <to_english> ENG_NOUN:ESTIMATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОЧАГ {} <to_english> ENG_NOUN:HEARTH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОЧЕРЕДЬ {} <to_english> ENG_NOUN:TURN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОЧЕРЕДЬ {} <to_english> ENG_NOUN:LINE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОЧЕРЕДЬ {} <to_english> ENG_NOUN:QUEUE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОШИБКА {} <to_english> ENG_NOUN:MISTAKE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОШИБКА {} <to_english> ENG_NOUN:ERROR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОЩУЩЕНИЕ {} <to_english> ENG_NOUN:SENSATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАВИЛЬОН {} <to_english> ENG_NOUN:PAVILLION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАДЕНИЕ {} <to_english> ENG_NOUN:FALL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАДЕНИЕ {} <to_english> ENG_NOUN:DROP {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАДЕНИЕ {} <to_english> ENG_NOUN:DOWNFALL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАКЕТ {} <to_english> ENG_NOUN:PACKET {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАКТ {} <to_english> ENG_NOUN:PACT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАЛАТА {} <to_english> ENG_NOUN:WARD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАЛАТА {} <to_english> ENG_NOUN:CHAMBER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАЛАТКА {} <to_english> ENG_NOUN:TENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАЛАТКА {} <to_english> ENG_NOUN:BOOTH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАЛАТКА {} <to_english> ENG_NOUN:STALL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАЛЕЦ {} <to_english> ENG_NOUN:FINGER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАЛКА {} <to_english> ENG_NOUN:STICK {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАЛУБА {} <to_english> ENG_NOUN:DECK {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАПА {} <to_english> ENG_NOUN:DAD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАПА {} <to_english> ENG_NOUN:DADY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАПА {} <to_english> ENG_NOUN:PAPA {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАР {} <to_english> ENG_NOUN:STEAM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАРАГРАФ {} <to_english> ENG_NOUN:PARAGRAPH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАРАД {} <to_english> ENG_NOUN:PARADE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАРАШЮТ {} <to_english> ENG_NOUN:PARACHUTE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАРЕНЬ {} <to_english> ENG_NOUN:FELLOW {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАРЕНЬ {} <to_english> ENG_NOUN:GUY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАРК {} <to_english> ENG_NOUN:PARK {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАРКЕТ {} <to_english> ENG_NOUN:PARQUET {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАРЛАМЕНТ {} <to_english> ENG_NOUN:PARLIAMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАРТЕР {} <to_english> ENG_NOUN:PIT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАРТИЯ {} <to_english> ENG_NOUN:PARTY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАРТНЕРША {} <to_english> ENG_NOUN:PARTNER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАРТНЕР {} <to_english> ENG_NOUN:PARTNER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАРУС {} <to_english> ENG_NOUN:SAIL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАС {} <to_english> ENG_NOUN:PASS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАСПОРТ {} <to_english> ENG_NOUN:PASSPORT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАССАЖИР {} <to_english> ENG_NOUN:PASSENGER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАСТУХ {} <to_english> ENG_NOUN:HERDSMAN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАТ {} <to_english> ENG_NOUN:STALEMATE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАТЕНТ {} <to_english> ENG_NOUN:PATENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАТРОН {} <to_english> ENG_NOUN:CARTRIDGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАЦИЕНТ {} <to_english> ENG_NOUN:PATIENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАЧКА {} <to_english> ENG_NOUN:PACKAGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЕВИЧКА {} <to_english> ENG_NOUN:SINGER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЕПЕЛ {} <to_english> ENG_NOUN:ASH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЕРВЕНСТВО {} <to_english> ENG_NOUN:CHAMPIONSHIP {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЕРЕВОД {} <to_english> ENG_NOUN:TRANSFER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЕРЕВОД {} <to_english> ENG_NOUN:TRANSLATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЕРЕВОД {} <to_english> ENG_NOUN:INTERPRETATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЕРЕГОВОР {} <to_english> ENG_NOUN:NEGOTIATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЕРЕГРУЗКА {} <to_english> ENG_NOUN:OVERLOAD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЕРЕДАТЧИК {} <to_english> ENG_NOUN:TRANSMITTER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЕРЕДАЧА {} <to_english> ENG_NOUN:BROADCAST {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЕРЕДВИЖЕНИЕ {} <to_english> ENG_NOUN:MOVEMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЕРЕИЗДАНИЕ {} <to_english> ENG_NOUN:REPRINT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЕРЕКЛЮЧАТЕЛЬ {} <to_english> ENG_NOUN:SWITCH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЕРЕЛЕТ {} <to_english> ENG_NOUN:FLIGHT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЕРЕЛОМ {} <to_english> ENG_NOUN:FRACTURE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЕРЕМЕНА {} <to_english> ENG_NOUN:CHANGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЕРЕПЛЕТ {} <to_english> ENG_NOUN:BINDING {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЕРЕПЛЕТ {} <to_english> ENG_NOUN:BOOKCOVER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЕРЕРЫВ {} <to_english> ENG_NOUN:BREAK {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЕРЕРЫВ {} <to_english> ENG_NOUN:INTERVAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЕРЕСАДКА {} <to_english> ENG_NOUN:TRANSFER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЕРЕСАДКА {} <to_english> ENG_NOUN:CHANGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЕРЕХОД {} <to_english> ENG_NOUN:PASSAGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЕРЕЦ {} <to_english> ENG_NOUN:PEPPER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЕРИОД {} <to_english> ENG_NOUN:PERIOD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЕРО {} <to_english> ENG_NOUN:FEATHER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЕРРОН {} <to_english> ENG_NOUN:PLATFORM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЕРСИК {} <to_english> ENG_NOUN:PEACH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЕРСОНАЛ {} <to_english> ENG_NOUN:PERSONNEL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЕРСОНАЛ {} <to_english> ENG_NOUN:STUFF {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЕСНЯ {} <to_english> ENG_NOUN:SONG {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЕЧАЛЬ {} <to_english> ENG_NOUN:SORROW {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЕЧЕНКА {} <to_english> ENG_NOUN:LIVER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЕЧЕНЬЕ {} <to_english> ENG_NOUN:BISCUIT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЕЩЕРА {} <to_english> ENG_NOUN:CAVE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПИАНИСТ {} <to_english> ENG_NOUN:PIANIST {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПИВО {} <to_english> ENG_NOUN:BEER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПИДЖАК {} <to_english> ENG_NOUN:COAT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПИЛОТ {} <to_english> ENG_NOUN:PILOT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПИРОГ {} <to_english> ENG_NOUN:PIE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПИСАТЕЛЬ {} <to_english> ENG_NOUN:WRITER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПИТАНИЕ {} <to_english> ENG_NOUN:DIET {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПИТАНИЕ {} <to_english> ENG_NOUN:NOURISHMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПИТАНИЕ {} <to_english> ENG_NOUN:NUTRITION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПИЩА {} <to_english> ENG_NOUN:FOOD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЛАКАТ {} <to_english> ENG_NOUN:POSTER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЛАН {} <to_english> ENG_NOUN:PLAN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЛАТА {} <to_english> ENG_NOUN:PAYMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЛАТА {} <to_english> ENG_NOUN:CHARGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЛАТА {} <to_english> ENG_NOUN:FARE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЛАТИНА {} <to_english> ENG_NOUN:PLATINUM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЛАТОК {} <to_english> ENG_NOUN:SHAWL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЛАТОК {} <to_english> ENG_NOUN:HANDKERCHIEF {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЛАТФОРМА {} <to_english> ENG_NOUN:PLATFORM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЛАТЬЕ {} <to_english> ENG_NOUN:DRESS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЛАТЬЕ {} <to_english> ENG_NOUN:GOWN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЛАЩ {} <to_english> ENG_NOUN:CLOAK {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЛАЩ {} <to_english> ENG_NOUN:RAINCOAT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЛЕЧО {} <to_english> ENG_NOUN:SHOULDER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЛОД {} <to_english> ENG_NOUN:FRUIT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЛОМБА {} <to_english> ENG_NOUN:SEAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЛОТИНА {} <to_english> ENG_NOUN:DAM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЛОТИНА {} <to_english> ENG_NOUN:DIKE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЛОТИНА {} <to_english> ENG_NOUN:DYKE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЛОЩАДКА {} <to_english> ENG_NOUN:GROUND {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЛОЩАДКА {} <to_english> ENG_NOUN:PLAYGROUND {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЛОЩАДКА {} <to_english> ENG_NOUN:COURT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЛОЩАДЬ {} <to_english> ENG_NOUN:AREA {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЛЯЖ {} <to_english> ENG_NOUN:BEACH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЛЯСКА {} <to_english> ENG_NOUN:DANCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОБЕДА {} <to_english> ENG_NOUN:VICTORY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОВАР {} <to_english> ENG_NOUN:CHEF {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОВАР {} <to_english> ENG_NOUN:COOK {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОВЕДЕНИЕ {} <to_english> ENG_NOUN:BEHAVIOUR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОВЕДЕНИЕ {} <to_english> ENG_NOUN:CONDUCT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОВЕСТКА {} <to_english> ENG_NOUN:NOTICE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОВЕСТКА {} <to_english> ENG_NOUN:SUMMONS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОВЕСТЬ {} <to_english> ENG_NOUN:STORY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОВОД {} <to_english> ENG_NOUN:OCCASION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОВОД {} <to_english> ENG_NOUN:REASON {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОВОД {} <to_english> ENG_NOUN:GROUND {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОВРЕЖДЕНИЕ {} <to_english> ENG_NOUN:DAMAGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОВРЕЖДЕНИЕ {} <to_english> ENG_NOUN:INJURY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОВЯЗКА {} <to_english> ENG_NOUN:BANDAGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОГОВОРКА {} <to_english> ENG_NOUN:SAYING {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОГОДА {} <to_english> ENG_NOUN:WEATHER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОДАРОК {} <to_english> ENG_NOUN:PRESENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОДБОРОДОК {} <to_english> ENG_NOUN:CHIN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОДГОТОВКА {} <to_english> ENG_NOUN:PREPARATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОДДЕРЖКА {} <to_english> ENG_NOUN:SUPPORT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОДНОС {} <to_english> ENG_NOUN:TRAY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОДОЗРЕНИЕ {} <to_english> ENG_NOUN:SUSPICTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОДОШВА {} <to_english> ENG_NOUN:SOLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОДПИСКА {} <to_english> ENG_NOUN:SUBSCRIPTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОДПИСЬ {} <to_english> ENG_NOUN:SIGNATURE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОДУШКА {} <to_english> ENG_NOUN:PILLOW {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОДЪЕЗД {} <to_english> ENG_NOUN:ENTRANCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОДЪЕЗД {} <to_english> ENG_NOUN:PORCH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОДЪЕМ {} <to_english> ENG_NOUN:ASCENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЕЗД {} <to_english> ENG_NOUN:TRAIN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЕЗДКА {} <to_english> ENG_NOUN:JOURNEY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЖАР {} <to_english> ENG_NOUN:FIRE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЖЕЛАНИЕ {} <to_english> ENG_NOUN:WISH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЗВОЛЕНИЕ {} <to_english> ENG_NOUN:PERMISSION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЗДРАВЛЕНИЕ {} <to_english> ENG_NOUN:CONGRATULATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЗИЦИЯ {} <to_english> ENG_NOUN:STAND {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЗИЦИЯ {} <to_english> ENG_NOUN:ATTITUDE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЗИЦИЯ {} <to_english> ENG_NOUN:POSITION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОИСК {} <to_english> ENG_NOUN:SEARCH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОКАЗАТЕЛЬ {} <to_english> ENG_NOUN:INDICATOR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОКОЙ {} <to_english> ENG_NOUN:REST {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОКОЙ {} <to_english> ENG_NOUN:PEACE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОКОЛЕНИЕ {} <to_english> ENG_NOUN:GENERATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОКРЫШКА {} <to_english> ENG_NOUN:TIRE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЛДЕНЬ {} <to_english> ENG_NOUN:NOON {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЛЕТ {} <to_english> ENG_NOUN:FLIGHT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЛИТИКА {} <to_english> ENG_NOUN:POLITICS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЛКА {} <to_english> ENG_NOUN:SHELF {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЛКОВНИК {} <to_english> ENG_NOUN:COLONEL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЛНОЧЬ {} <to_english> ENG_NOUN:MIDNIGHT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЛОВИНА {} <to_english> ENG_NOUN:HALF {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЛОЖЕНИЕ {} <to_english> ENG_NOUN:CONDITION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЛОЖЕНИЕ {} <to_english> ENG_NOUN:STATE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЛОСА {} <to_english> ENG_NOUN:STRIPE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЛОТЕНЦЕ {} <to_english> ENG_NOUN:TOWEL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЛОТНО {} <to_english> ENG_NOUN:LINEN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЛЬЗА {} <to_english> ENG_NOUN:USE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЛЮС {} <to_english> ENG_NOUN:POLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЛЯНА {} <to_english> ENG_NOUN:GLADE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОМАДА {} <to_english> ENG_NOUN:LIPSTICK {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОМИДОР {} <to_english> ENG_NOUN:TOMATO {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОМОЩНИК {} <to_english> ENG_NOUN:ASSISTANT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОМОЩЬ {} <to_english> ENG_NOUN:ASSISTANCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОНЕДЕЛЬНИК {} <to_english> ENG_NOUN:MONDAY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОНОС {} <to_english> ENG_NOUN:DIARRHEA {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОПРАВКА {} <to_english> ENG_NOUN:CORRECTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОПРАВКА {} <to_english> ENG_NOUN:AMENDMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОПЫТКА {} <to_english> ENG_NOUN:ATTEMPT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОПЫТКА {} <to_english> ENG_NOUN:TRIAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОРАЖЕНИЕ {} <to_english> ENG_NOUN:DEFEAT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОРОГ {} <to_english> ENG_NOUN:THRESHOLD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОРТ {} <to_english> ENG_NOUN:PORT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОРУЧЕНИЕ {} <to_english> ENG_NOUN:COMMISSION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОРЦИЯ {} <to_english> ENG_NOUN:PORTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОСЕЛОК {} <to_english> ENG_NOUN:SETTLEMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОСЕЛОК {} <to_english> ENG_NOUN:TOWNSHIP {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОСЕТИТЕЛЬ {} <to_english> ENG_NOUN:VISITOR {}
 link НАРЕЧИЕ:ПОСЛЕДСТВИЕ {} <to_english> ENG_NOUN:CONSEQUENCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОСОЛ { ОДУШ:ОДУШ } <to_english> ENG_NOUN:AMBASSADOR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОСОЛЬСТВО {} <to_english> ENG_NOUN:EMBASSY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОСТ {} <to_english> ENG_NOUN:POST {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОСТАНОВЛЕНИЕ {} <to_english> ENG_NOUN:DECISION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОСТАНОВЛЕНИЕ {} <to_english> ENG_NOUN:RESOLUTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОСТАНОВЛЕНИЕ {} <to_english> ENG_NOUN:DECREE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОСТЕЛЬ {} <to_english> ENG_NOUN:BED {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОСЫЛКА {} <to_english> ENG_NOUN:PARCEL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОТ {} <to_english> ENG_NOUN:SWEAT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОТОК {} <to_english> ENG_NOUN:STREAM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОТОК {} <to_english> ENG_NOUN:FLOW {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОТОЛОК {} <to_english> ENG_NOUN:CEILING {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОТРЕБНОСТЬ {} <to_english> ENG_NOUN:NECESSITY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОТРЕБНОСТЬ {} <to_english> ENG_NOUN:NEED {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОТРЕБНОСТЬ {} <to_english> ENG_NOUN:DEMAND {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОХВАЛА {} <to_english> ENG_NOUN:PRAISE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОХОДКА {} <to_english> ENG_NOUN:GAIT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОХОРОНЫ {} <to_english> ENG_NOUN:FUNERAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЦЕЛУЙ {} <to_english> ENG_NOUN:KISS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЧВА {} <to_english> ENG_NOUN:SOIL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЧЕТ {} <to_english> ENG_NOUN:HONOUR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЧИН {} <to_english> ENG_NOUN:INITIATIVE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЧКА {} <to_english> ENG_NOUN:KIDNEY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЧКА {} <to_english> ENG_NOUN:BUD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЧТА {} <to_english> ENG_NOUN:POST {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЧТАЛЬОН {} <to_english> ENG_NOUN:POSTMAN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЭМА {} <to_english> ENG_NOUN:POEM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЭТ {} <to_english> ENG_NOUN:POET {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЯС {} <to_english> ENG_NOUN:BELT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЯСНЕНИЕ {} <to_english> ENG_NOUN:EXPLANATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЯСНЕНИЕ {} <to_english> ENG_NOUN:ELUCIDATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРАВИЛО {} <to_english> ENG_NOUN:RULE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРАВИТЕЛЬСТВО {} <to_english> ENG_NOUN:GOVERNMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРАВЛЕНИЕ {} <to_english> ENG_NOUN:GOVERNMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРАВЛЕНИЕ {} <to_english> ENG_NOUN:RULE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРАЗДНЕСТВО {} <to_english> ENG_NOUN:FESTIVAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРАЗДНЕСТВО {} <to_english> ENG_NOUN:CELEBRATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРАЗДНИК {} <to_english> ENG_NOUN:HOLIDAY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРАЗДНИК {} <to_english> ENG_NOUN:FEAST {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРАЗДНОВАНИЕ {} <to_english> ENG_NOUN:CELEBRATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРАКТИКА {} <to_english> ENG_NOUN:PRACTICE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРЕБЫВАНИЕ {} <to_english> ENG_NOUN:STAY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРЕБЫВАНИЕ {} <to_english> ENG_NOUN:SOJOURN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРЕВОСХОДСТВО {} <to_english> ENG_NOUN:SUPERIORITY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРЕДЕЛ {} <to_english> ENG_NOUN:LIMIT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРЕДЛОЖЕНИЕ {} <to_english> ENG_NOUN:PROPOSAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРЕДЛОЖЕНИЕ {} <to_english> ENG_NOUN:SUGGESTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРЕДЛОЖЕНИЕ {} <to_english> ENG_NOUN:OFFER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРЕДМЕТ {} <to_english> ENG_NOUN:OBJECT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРЕДМЕТ {} <to_english> ENG_NOUN:SUBJECT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРЕДОК {} <to_english> ENG_NOUN:ANCESTOR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРЕДОК {} <to_english> ENG_NOUN:FOREFATHER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРЕДРАССУДОК {} <to_english> ENG_NOUN:PREJUSTICE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРЕДСЕДАТЕЛЬ {} <to_english> ENG_NOUN:CHAIRMAN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРЕДСЕДАТЕЛЬ {} <to_english> ENG_NOUN:PRESIDENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРЕДСТАВИТЕЛЬ {} <to_english> ENG_NOUN:REPRESENTATIVE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРЕДУПРЕЖДЕНИЕ {} <to_english> ENG_NOUN:WARNING {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРЕДУПРЕЖДЕНИЕ {} <to_english> ENG_NOUN:NOTICE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРЕЗИДЕНТ {} <to_english> ENG_NOUN:PRESIDENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРЕЗИДИУМ {} <to_english> ENG_NOUN:PRESIDIUM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРЕИМУЩЕСТВО {} <to_english> ENG_NOUN:ADVANTAGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРЕЛЕСТЬ {} <to_english> ENG_NOUN:CHARM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРЕМИЯ {} <to_english> ENG_NOUN:PRIZE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРЕМИЯ {} <to_english> ENG_NOUN:BONUS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРЕМИЯ {} <to_english> ENG_NOUN:REWARD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРЕПОДАВАТЕЛЬ {} <to_english> ENG_NOUN:TEACHER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРЕПЯТСТВИЕ {} <to_english> ENG_NOUN:OBSTACLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРЕПЯТСТВИЕ {} <to_english> ENG_NOUN:IMPEDIMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРЕПЯТСТВИЕ {} <to_english> ENG_NOUN:HURDLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРЕССА {} <to_english> ENG_NOUN:PRESS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРЕСТУПЛЕНИЕ {} <to_english> ENG_NOUN:CRIME {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРЕСТУПНИК {} <to_english> ENG_NOUN:CRIMINAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРЕТЕНЗИЯ {} <to_english> ENG_NOUN:CLAIM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРЕТЕНЗИЯ {} <to_english> ENG_NOUN:PRETENSION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРЕУВЕЛИЧЕНИЕ {} <to_english> ENG_NOUN:EXAGERATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИБОР {} <to_english> ENG_NOUN:INSTRUMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИБОР {} <to_english> ENG_NOUN:APPARATUS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИБЫЛЬ {} <to_english> ENG_NOUN:PROFIT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИБЫТИЕ {} <to_english> ENG_NOUN:ARRIVAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИВКУС {} <to_english> ENG_NOUN:SMACK {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИВКУС {} <to_english> ENG_NOUN:FLAVOUR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИВЫЧКА {} <to_english> ENG_NOUN:HABIT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИГОВОР {} <to_english> ENG_NOUN:SENTENCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИГОВОР {} <to_english> ENG_NOUN:VERDICT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИГОДНОСТЬ {} <to_english> ENG_NOUN:FITNESS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИГОДНОСТЬ {} <to_english> ENG_NOUN:USEFULNESS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИГОТОВЛЕНИЕ {} <to_english> ENG_NOUN:PREPARATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИЕЗД {} <to_english> ENG_NOUN:ARRIVAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИЕМ {} <to_english> ENG_NOUN:RECEPTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИЗ {} <to_english> ENG_NOUN:PRIZE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИКОСНОВЕНИЕ {} <to_english> ENG_NOUN:TOUCH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИЛАВОК {} <to_english> ENG_NOUN:COUNTER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИЛИВ {} <to_english> ENG_NOUN:FLOW {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИЛОЖЕНИЕ {} <to_english> ENG_NOUN:ANNEX {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИЛОЖЕНИЕ {} <to_english> ENG_NOUN:SUPPLEMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИМЕНЕНИЕ {} <to_english> ENG_NOUN:APPLICATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИМЕНЕНИЕ {} <to_english> ENG_NOUN:USE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИМЕР {} <to_english> ENG_NOUN:EXAMPLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИМЕР {} <to_english> ENG_NOUN:INSTANCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИМЕЧАНИЕ {} <to_english> ENG_NOUN:COMMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИМЕЧАНИЕ {} <to_english> ENG_NOUN:FOOTNOTE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИНЦИП {} <to_english> ENG_NOUN:PRINCIPLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИПЕВ {} <to_english> ENG_NOUN:CHORUS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИРОДА {} <to_english> ENG_NOUN:NATURE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИСТУП {} <to_english> ENG_NOUN:ATTACK {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИСТУП {} <to_english> ENG_NOUN:BOUT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИСТУП {} <to_english> ENG_NOUN:PANG {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИСУТСТВИЕ {} <to_english> ENG_NOUN:PRESENCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИТОК {} <to_english> ENG_NOUN:TRIBUTARY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИТОК {} <to_english> ENG_NOUN:FLOW {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИТОК {} <to_english> ENG_NOUN:INFLUX {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИТЯЖЕНИЕ {} <to_english> ENG_NOUN:ATTRACTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИЦЕП {} <to_english> ENG_NOUN:TRAILER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИЧЕСКА {} <to_english> ENG_NOUN:HAIRCUT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИЧИНА {} <to_english> ENG_NOUN:CAUSE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРИЧИНА {} <to_english> ENG_NOUN:REASON {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОВЕРКА {} <to_english> ENG_NOUN:CONTROL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОВЕРКА {} <to_english> ENG_NOUN:VERIFICATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОГНОЗ {} <to_english> ENG_NOUN:FORECAST {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОГНОЗ {} <to_english> ENG_NOUN:PROGNOSIS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОГРАММА {} <to_english> ENG_NOUN:PROGRAM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОГУЛКА {} <to_english> ENG_NOUN:WALK {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОДАЖА {} <to_english> ENG_NOUN:SALE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОДОЛЖЕНИЕ {} <to_english> ENG_NOUN:CONTINUATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОЕКТ {} <to_english> ENG_NOUN:PROJECT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОИГРЫВАТЕЛЬ {} <to_english> ENG_NOUN:RECORDPLAYER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОИЗВОДИТЕЛЬНОСТЬ {} <to_english> ENG_NOUN:PRODUCTIVITY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОИЗВОДСТВО {} <to_english> ENG_NOUN:PRODUCTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОИЗНОШЕНИЕ {} <to_english> ENG_NOUN:PRONUNCIATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОИСХОЖДЕНИЕ {} <to_english> ENG_NOUN:ORIGIN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОИСШЕСТВИЕ {} <to_english> ENG_NOUN:INCIDENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОКАТ {} <to_english> ENG_NOUN:HIRE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОМАХ {} <to_english> ENG_NOUN:MISS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОМАХ {} <to_english> ENG_NOUN:BLUNDER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОМЕЖУТОК {} <to_english> ENG_NOUN:INTERVAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОМЕЖУТОК {} <to_english> ENG_NOUN:SPACE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОМЕЖУТОК {} <to_english> ENG_NOUN:GAP {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОПАГАНДА {} <to_english> ENG_NOUN:PROPAGANDA {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОПОВЕДЬ {} <to_english> ENG_NOUN:SERMON {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОСВЕЩЕНИЕ {} <to_english> ENG_NOUN:EDUCATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОСВЕЩЕНИЕ {} <to_english> ENG_NOUN:ENLIGHTMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОСМОТР {} <to_english> ENG_NOUN:SURVEY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОСПЕКТ {} <to_english> ENG_NOUN:AVENUE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОСЬБА {} <to_english> ENG_NOUN:REQUEST {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОТЕСТ {} <to_english> ENG_NOUN:PROTEST {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОТИВНИК {} <to_english> ENG_NOUN:OPPONENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОТИВОРЕЧИЕ {} <to_english> ENG_NOUN:CONTRADICTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОФЕССИЯ {} <to_english> ENG_NOUN:OCCUPATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОФЕССИЯ {} <to_english> ENG_NOUN:PROFESSION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОХОД {} <to_english> ENG_NOUN:PASSAGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОЦЕСС {} <to_english> ENG_NOUN:PROCESS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОЦЕСС {} <to_english> ENG_NOUN:TRIAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРОЩАНИЕ {} <to_english> ENG_NOUN:FAREWELL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРУД {} <to_english> ENG_NOUN:POND {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРЫЖОК {} <to_english> ENG_NOUN:JUMP {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРЯЖКА {} <to_english> ENG_NOUN:BUCKLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПТИЦА {} <to_english> ENG_NOUN:BIRD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПРЯНОСТЬ {} <to_english> ENG_NOUN:SPICE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПСЕВДОНИМ {} <to_english> ENG_NOUN:PSEUDONYM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПУБЛИКА {} <to_english> ENG_NOUN:PUBLIC {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПУГОВИЦА {} <to_english> ENG_NOUN:BUTTON {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПУДРА {} <to_english> ENG_NOUN:POWDER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПУЛЬС {} <to_english> ENG_NOUN:PULSE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПУНКТ {} <to_english> ENG_NOUN:POINT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПУТЕВОДИТЕЛЬ {} <to_english> ENG_NOUN:GUIDE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПУТЕШЕСТВЕННИК {} <to_english> ENG_NOUN:TRAVELLER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПУТЕШЕСТВИЕ {} <to_english> ENG_NOUN:TRAVEL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПУТЬ {} <to_english> ENG_NOUN:WAY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПУТЬ {} <to_english> ENG_NOUN:ROAD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЮРЕ {} <to_english> ENG_NOUN:PUREE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЯТКА {} <to_english> ENG_NOUN:HEEL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЯТНИЦА {} <to_english> ENG_NOUN:FRIDAY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЯТНО {} <to_english> ENG_NOUN:SPOT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПЯТНО {} <to_english> ENG_NOUN:STAIN {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАБОТНИК {} <to_english> ENG_NOUN:WORKER {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАВНОПРАВИЕ {} <to_english> ENG_NOUN:EQUALITY {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАДИУС {} <to_english> ENG_NOUN:RADIUS {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАДОСТЬ {} <to_english> ENG_NOUN:JOY {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАЗВАЛИНА {} <to_english> ENG_NOUN:RUIN {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАЗВИТИЕ {} <to_english> ENG_NOUN:DEVELOPMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАЗВЛЕЧЕНИЕ {} <to_english> ENG_NOUN:AMUSEMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАЗВЛЕЧЕНИЕ {} <to_english> ENG_NOUN:ENTERTAINMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАЗЛИЧИЕ {} <to_english> ENG_NOUN:DISTINCTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАЗМАХ {} <to_english> ENG_NOUN:RANGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАЗМАХ {} <to_english> ENG_NOUN:SCOPE {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАЗМЕР {} <to_english> ENG_NOUN:SIZE {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАЗНИЦА {} <to_english> ENG_NOUN:DIFFERENCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАЗНОГЛАСИЕ {} <to_english> ENG_NOUN:DISAGREEMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАЗНООБРАЗИЕ {} <to_english> ENG_NOUN:VARIETY {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАЗОРУЖЕНИЕ {} <to_english> ENG_NOUN:DISARMAMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАЗОЧАРОВАНИЕ {} <to_english> ENG_NOUN:DISAPPOINMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАЗРЕШЕНИЕ {} <to_english> ENG_NOUN:PERMISSION {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАЗРЯД {} <to_english> ENG_NOUN:CATEGORY {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАКЕТА {} <to_english> ENG_NOUN:ROCKET {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАКЕТКА {} <to_english> ENG_NOUN:RACKET {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАКОВИНА {} <to_english> ENG_NOUN:SHELL {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАКОВИНА {} <to_english> ENG_NOUN:SINK {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАНА {} <to_english> ENG_NOUN:WOUND {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАПИРА {} <to_english> ENG_NOUN:FOIL {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАСПИСАНИЕ {} <to_english> ENG_NOUN:SCHEDULE {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАСПОРЯЖЕНИЕ {} <to_english> ENG_NOUN:ARRANGMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАСПОРЯДОК {} <to_english> ENG_NOUN:ORDER {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАССВЕТ {} <to_english> ENG_NOUN:DAWN {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАССКАЗ {} <to_english> ENG_NOUN:STORY {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАСТЕНИЕ {} <to_english> ENG_NOUN:PLANT {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАСТИТЕЛЬНОСТЬ {} <to_english> ENG_NOUN:VEGETATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАСЧЕТ {} <to_english> ENG_NOUN:CALCULATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАСШИРЕНИЕ {} <to_english> ENG_NOUN:EXTENSION {}
 link СУЩЕСТВИТЕЛЬНОЕ:РАСШИРЕНИЕ {} <to_english> ENG_NOUN:EXPANSION {}
 link СУЩЕСТВИТЕЛЬНОЕ:РЕАКЦИЯ {} <to_english> ENG_NOUN:REACTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:РЕАЛИЗМ {} <to_english> ENG_NOUN:REALISM {}
 link СУЩЕСТВИТЕЛЬНОЕ:РЕБРО {} <to_english> ENG_NOUN:RIB {}
 link СУЩЕСТВИТЕЛЬНОЕ:РЕДИС {} <to_english> ENG_NOUN:RADISH {}
 link СУЩЕСТВИТЕЛЬНОЕ:РЕЖИМ {} <to_english> ENG_NOUN:REGIME {}
 link СУЩЕСТВИТЕЛЬНОЕ:РЕЗИНА {} <to_english> ENG_NOUN:RUBBER {}
 link СУЩЕСТВИТЕЛЬНОЕ:РЕЗИНКА {} <to_english> ENG_NOUN:ERASER {}
 link СУЩЕСТВИТЕЛЬНОЕ:РЕЙС {} <to_english> ENG_NOUN:TRIP {}
 link СУЩЕСТВИТЕЛЬНОЕ:РЕКЛАМА {} <to_english> ENG_NOUN:ADVERTISEMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:РЕКОМЕНДАЦИЯ {} <to_english> ENG_NOUN:RECOMMENDATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:РЕКОНСТРУИРОВАНИЕ {} <to_english> ENG_NOUN:RECONSTRUCTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:РЕЛИГИЯ {} <to_english> ENG_NOUN:RELIGION {}
 link СУЩЕСТВИТЕЛЬНОЕ:РЕМЕНЬ {} <to_english> ENG_NOUN:STRAP {}
 link СУЩЕСТВИТЕЛЬНОЕ:РЕМОНТ {} <to_english> ENG_NOUN:REPAIR {}
 link СУЩЕСТВИТЕЛЬНОЕ:РЕПЕРТУАР {} <to_english> ENG_NOUN:REPERTOIRE {}
 link СУЩЕСТВИТЕЛЬНОЕ:РЕПЕРТУАР {} <to_english> ENG_NOUN:REPERTORY {}
 link СУЩЕСТВИТЕЛЬНОЕ:РЕПЛИКА {} <to_english> ENG_NOUN:CUE {}
 link СУЩЕСТВИТЕЛЬНОЕ:РЕПЛИКА {} <to_english> ENG_NOUN:REMARK {}
 link СУЩЕСТВИТЕЛЬНОЕ:РЕСТОРАН {} <to_english> ENG_NOUN:RESTAURANT {}
 link СУЩЕСТВИТЕЛЬНОЕ:РЕФОРМА {} <to_english> ENG_NOUN:REFORM {}
 link СУЩЕСТВИТЕЛЬНОЕ:РЕЦЕПТ {} <to_english> ENG_NOUN:RECIPE {}
 link СУЩЕСТВИТЕЛЬНОЕ:РЕЧЬ {} <to_english> ENG_NOUN:SPEECH {}
 link СУЩЕСТВИТЕЛЬНОЕ:РЕШЕНИЕ {} <to_english> ENG_NOUN:DECISION {}
 link СУЩЕСТВИТЕЛЬНОЕ:РЕШЕНИЕ {} <to_english> ENG_NOUN:RESOLUTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:РИС {} <to_english> ENG_NOUN:RICE {}
 link СУЩЕСТВИТЕЛЬНОЕ:РИТМ {} <to_english> ENG_NOUN:RHYTHM {}
 link СУЩЕСТВИТЕЛЬНОЕ:РОВЕСНИК {} <to_english> ENG_NOUN:COEVAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:РОДИНА {} <to_english> ENG_NOUN:HOMELAND {}
 link СУЩЕСТВИТЕЛЬНОЕ:РОДИНА {} <to_english> ENG_NOUN:MOTHERLAND {}
 link СУЩЕСТВИТЕЛЬНОЕ:РОДИТЕЛЬ {} <to_english> ENG_NOUN:PARENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:РОДСТВЕННИК {} <to_english> ENG_NOUN:RELATIVE {}
 link СУЩЕСТВИТЕЛЬНОЕ:РОЖДЕНИЕ {} <to_english> ENG_NOUN:BIRTH {}
 link СУЩЕСТВИТЕЛЬНОЕ:РОЖЬ {} <to_english> ENG_NOUN:RYE {}
 link СУЩЕСТВИТЕЛЬНОЕ:РОЗА {ОДУШ:НЕОДУШ} <to_english> ENG_NOUN:ROSE {}
 link СУЩЕСТВИТЕЛЬНОЕ:РОЛЬ {} <to_english> ENG_NOUN:ROLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:РОЛЬ {} <to_english> ENG_NOUN:PART {}
 link СУЩЕСТВИТЕЛЬНОЕ:РОМАН {} <to_english> ENG_NOUN:NOVEL {}
 link СУЩЕСТВИТЕЛЬНОЕ:РОМАНС {} <to_english> ENG_NOUN:ROMANCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:РОМАНС {} <to_english> ENG_NOUN:SONG {}
 link СУЩЕСТВИТЕЛЬНОЕ:РОМБ {} <to_english> ENG_NOUN:RHOMB {}
 link СУЩЕСТВИТЕЛЬНОЕ:РОСА {} <to_english> ENG_NOUN:DEW {}
 link СУЩЕСТВИТЕЛЬНОЕ:РОСТ {} <to_english> ENG_NOUN:HEIGHT {}
 link СУЩЕСТВИТЕЛЬНОЕ:РОТ {} <to_english> ENG_NOUN:MOUTH {}
 link СУЩЕСТВИТЕЛЬНОЕ:РОЩА {} <to_english> ENG_NOUN:GROVE {}
 link СУЩЕСТВИТЕЛЬНОЕ:РОЯЛЬ {} <to_english> ENG_NOUN:PIANO {}
 link СУЩЕСТВИТЕЛЬНОЕ:РУБАШКА {} <to_english> ENG_NOUN:SHIRT {}
 link СУЩЕСТВИТЕЛЬНОЕ:РУЖЬЕ {} <to_english> ENG_NOUN:RIFLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:РУКАВ {} <to_english> ENG_NOUN:SLEEVE {}
 link СУЩЕСТВИТЕЛЬНОЕ:РУКОВОДИТЕЛЬ {} <to_english> ENG_NOUN:LEADER {}
 link СУЩЕСТВИТЕЛЬНОЕ:РУКОВОДСТВО {} <to_english> ENG_NOUN:LEADERSHIP {}
 link СУЩЕСТВИТЕЛЬНОЕ:РУКОВОДСТВО {} <to_english> ENG_NOUN:GUIDANCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:РУКОПИСЬ {} <to_english> ENG_NOUN:MANUSCRIPT {}
 link СУЩЕСТВИТЕЛЬНОЕ:РУЛЬ {} <to_english> ENG_NOUN:HELM {}
 link СУЩЕСТВИТЕЛЬНОЕ:РУЛЬ {} <to_english> ENG_NOUN:RUDDER {}
 link СУЩЕСТВИТЕЛЬНОЕ:РУЧЕЙ {} <to_english> ENG_NOUN:STREAM {}
 link СУЩЕСТВИТЕЛЬНОЕ:РУЧЕЙ {} <to_english> ENG_NOUN:BROOK {}
 link СУЩЕСТВИТЕЛЬНОЕ:РУЧКА {} <to_english> ENG_NOUN:HANDLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:РУЧКА {} <to_english> ENG_NOUN:PEN {}
 link СУЩЕСТВИТЕЛЬНОЕ:РЫБА {} <to_english> ENG_NOUN:FISH {}
 link СУЩЕСТВИТЕЛЬНОЕ:РЫБАК {} <to_english> ENG_NOUN:FISHERMAN {}
 link СУЩЕСТВИТЕЛЬНОЕ:РЫНОК {} <to_english> ENG_NOUN:MARKET {}
 link СУЩЕСТВИТЕЛЬНОЕ:РЯД {} <to_english> ENG_NOUN:ROW {}
 link СУЩЕСТВИТЕЛЬНОЕ:САД {} <to_english> ENG_NOUN:GARDEN {}
 link СУЩЕСТВИТЕЛЬНОЕ:САД {} <to_english> ENG_NOUN:ORCHARD {}
 link СУЩЕСТВИТЕЛЬНОЕ:САДОВНИК {} <to_english> ENG_NOUN:GARDENER {}
 link СУЩЕСТВИТЕЛЬНОЕ:САКСОФОН {} <to_english> ENG_NOUN:SAXOPHONE {}
 link СУЩЕСТВИТЕЛЬНОЕ:САЛАТ {} <to_english> ENG_NOUN:SALAD {}
 link СУЩЕСТВИТЕЛЬНОЕ:САЛО {} <to_english> ENG_NOUN:FAT {}
 link СУЩЕСТВИТЕЛЬНОЕ:САЛО {} <to_english> ENG_NOUN:GREASE {}
 link СУЩЕСТВИТЕЛЬНОЕ:САЛОН {} <to_english> ENG_NOUN:SALOON {}
 link СУЩЕСТВИТЕЛЬНОЕ:САЛФЕТКА {} <to_english> ENG_NOUN:NAPKIN {}
 link СУЩЕСТВИТЕЛЬНОЕ:САЛФЕТКА {} <to_english> ENG_NOUN:SERVIETTE {}
 link СУЩЕСТВИТЕЛЬНОЕ:САЛЮТ {} <to_english> ENG_NOUN:SALUTE {}
 link СУЩЕСТВИТЕЛЬНОЕ:САМОЛЕТ {} <to_english> ENG_NOUN:PLANE {}
 link СУЩЕСТВИТЕЛЬНОЕ:САМОЛЕТ {} <to_english> ENG_NOUN:AIRCRAFT {}
 link СУЩЕСТВИТЕЛЬНОЕ:САМОУБИЙСТВО {} <to_english> ENG_NOUN:SUICIDE {}
 link СУЩЕСТВИТЕЛЬНОЕ:САНАТОРИЙ {} <to_english> ENG_NOUN:SANATORIUM {}
 link СУЩЕСТВИТЕЛЬНОЕ:САПФИР {} <to_english> ENG_NOUN:SAPPHIRE {}
 link СУЩЕСТВИТЕЛЬНОЕ:САРАФАН {} <to_english> ENG_NOUN:SARAFAN {}
 link СУЩЕСТВИТЕЛЬНОЕ:САТАНА {} <to_english> ENG_NOUN:SATAN {}
 link СУЩЕСТВИТЕЛЬНОЕ:САХАР {} <to_english> ENG_NOUN:SUGAR {}
 link СУЩЕСТВИТЕЛЬНОЕ:СБОР {} <to_english> ENG_NOUN:COLLECTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:СВАДЬБА {} <to_english> ENG_NOUN:WEDDING {}
 link СУЩЕСТВИТЕЛЬНОЕ:СВЕДЕНИЯ {} <to_english> ENG_NOUN:INFORMATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:СВЕЧА {} <to_english> ENG_NOUN:CANDLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СВИДЕТЕЛЬ {} <to_english> ENG_NOUN:WITNESS {}
 link СУЩЕСТВИТЕЛЬНОЕ:СВИНЬЯ {} <to_english> ENG_NOUN:PIG {}
 link СУЩЕСТВИТЕЛЬНОЕ:СВИСТ {} <to_english> ENG_NOUN:WHISTLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СВИСТОК {} <to_english> ENG_NOUN:WHISTLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СВОДКА {} <to_english> ENG_NOUN:SUMMARY {}
 link СУЩЕСТВИТЕЛЬНОЕ:СВОДКА {} <to_english> ENG_NOUN:REPORT {}
 link СУЩЕСТВИТЕЛЬНОЕ:СВЯЗКА {} <to_english> ENG_NOUN:SHEAF {}
 link СУЩЕСТВИТЕЛЬНОЕ:СВЯЗКА {} <to_english> ENG_NOUN:BUNCH {}
 link СУЩЕСТВИТЕЛЬНОЕ:СВЯЗЬ {} <to_english> ENG_NOUN:TIE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СВЯЩЕННИК {} <to_english> ENG_NOUN:PRIEST {}
 link СУЩЕСТВИТЕЛЬНОЕ:СДЕЛКА {} <to_english> ENG_NOUN:DEAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:СДЕЛКА {} <to_english> ENG_NOUN:BARGAIN {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЕАНС {} <to_english> ENG_NOUN:SHOW {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЕВЕР {} <to_english> ENG_NOUN:NORTH {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЕЗОН {} <to_english> ENG_NOUN:SEASON {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЕКРЕТ {} <to_english> ENG_NOUN:SECRET {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЕКРЕТАРЬ {} <to_english> ENG_NOUN:SECRETARY {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЕЛО {} <to_english> ENG_NOUN:VILLAGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЕМАФОР {} <to_english> ENG_NOUN:SEMAPHORE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЕМЬЯ {} <to_english> ENG_NOUN:FAMILY {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЕНТЯБРЬ {} <to_english> ENG_NOUN:SEPTEMBER {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЕРЕДИНА {} <to_english> ENG_NOUN:MIDDLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЕРЖАНТ {} <to_english> ENG_NOUN:SERGEANT {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЕРИЯ {} <to_english> ENG_NOUN:SERIES {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЕСТРА {} <to_english> ENG_NOUN:SISTER {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЕТКА {} <to_english> ENG_NOUN:NET {}
 link СУЩЕСТВИТЕЛЬНОЕ:СИГАРА {} <to_english> ENG_NOUN:CIGAR {}
 link СУЩЕСТВИТЕЛЬНОЕ:СИГНАЛ {} <to_english> ENG_NOUN:SIGNAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:СИДЕЛКА {} <to_english> ENG_NOUN:NURSE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СИДЕНИЕ {} <to_english> ENG_NOUN:SEAT {}
 link СУЩЕСТВИТЕЛЬНОЕ:СИДЕНЬЕ {} <to_english> ENG_NOUN:SEAT {}
 link СУЩЕСТВИТЕЛЬНОЕ:СИЛА {} <to_english> ENG_NOUN:STRENGTH {}
 link СУЩЕСТВИТЕЛЬНОЕ:СИЛА {} <to_english> ENG_NOUN:POWER {}
 link СУЩЕСТВИТЕЛЬНОЕ:СИЛОС {} <to_english> ENG_NOUN:SILAGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СИМФОНИЯ {} <to_english> ENG_NOUN:SYMPHONY {}
 link СУЩЕСТВИТЕЛЬНОЕ:СИНЯК {} <to_english> ENG_NOUN:BRUISE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СИРОП {} <to_english> ENG_NOUN:SYRUP {}
 link СУЩЕСТВИТЕЛЬНОЕ:СКАЗКА {} <to_english> ENG_NOUN:TALE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СКАЗКА {} <to_english> ENG_NOUN:STORY {}
 link СУЩЕСТВИТЕЛЬНОЕ:СКАМЕЙКА {} <to_english> ENG_NOUN:BENCH {}
 link СУЩЕСТВИТЕЛЬНОЕ:СКРИПКА {} <to_english> ENG_NOUN:VIOLIN {}
 link СУЩЕСТВИТЕЛЬНОЕ:СКУЛЬПТОР {} <to_english> ENG_NOUN:SCULPTOR {}
 link СУЩЕСТВИТЕЛЬНОЕ:СКУЛЬПТУРА {} <to_english> ENG_NOUN:SCULPTURE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЛАБОСТЬ {} <to_english> ENG_NOUN:WEAKNESS {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЛАВА {ОДУШ:НЕОДУШ} <to_english> ENG_NOUN:FAME {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЛАВА {ОДУШ:НЕОДУШ} <to_english> ENG_NOUN:GLORY {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЛЕД {} <to_english> ENG_NOUN:TRACK {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЛЕД {} <to_english> ENG_NOUN:TRACE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЛЕДОВАТЕЛЬ {} <to_english> ENG_NOUN:INVESTIGATOR {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЛЕДСТВИЕ {} <to_english> ENG_NOUN:CONSEQUENCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЛЕДСТВИЕ {} <to_english> ENG_NOUN:EFFECT {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЛЕЗА {} <to_english> ENG_NOUN:TEAR {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЛОН {} <to_english> ENG_NOUN:ELEPHANT {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЛУГА {} <to_english> ENG_NOUN:SERVANT {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЛУЖБА {} <to_english> ENG_NOUN:WORK {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЛУЧАЙ {} <to_english> ENG_NOUN:CASE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СМЕНА {} <to_english> ENG_NOUN:SHIFT {}
 link СУЩЕСТВИТЕЛЬНОЕ:СМУЩЕНИЕ {} <to_english> ENG_NOUN:EMBARRASSMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:СМЫСЛ {} <to_english> ENG_NOUN:SENSE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СНАБЖЕНИЕ {} <to_english> ENG_NOUN:SUPPLY {}
 link СУЩЕСТВИТЕЛЬНОЕ:СНЕГ {} <to_english> ENG_NOUN:SNOW {}
 link СУЩЕСТВИТЕЛЬНОЕ:СНОП {} <to_english> ENG_NOUN:SHEAF {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОБЕСЕДНИК {} <to_english> ENG_NOUN:INTERLOCUTOR {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОБОЛЕЗНОВАНИЕ {} <to_english> ENG_NOUN:CONDOLENCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОБОР {} <to_english> ENG_NOUN:CATHEDRAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОБСТВЕННОСТЬ {} <to_english> ENG_NOUN:PROPERTY {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОБСТВЕННОСТЬ {} <to_english> ENG_NOUN:OWNERSHIP {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОБЫТИЕ {} <to_english> ENG_NOUN:EVENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОВЕРШЕНСТВО {} <to_english> ENG_NOUN:PERFECTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОВЕСТЬ {} <to_english> ENG_NOUN:CONSCIENCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОВЕТ {} <to_english> ENG_NOUN:ADVICE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОВЕТНИК {} <to_english> ENG_NOUN:ADVISER {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОВЕТНИК {} <to_english> ENG_NOUN:COUNSELLOR {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОВЕЩАНИЕ {} <to_english> ENG_NOUN:CONFERENCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОГЛАСИЕ {} <to_english> ENG_NOUN:CONSENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОГЛАШЕНИЕ {} <to_english> ENG_NOUN:AGREEMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОДЕЙСТВИЕ {} <to_english> ENG_NOUN:ASSISTANCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОДЕРЖАНИЕ {} <to_english> ENG_NOUN:CONTENTS {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОЖАЛЕНИЕ {} <to_english> ENG_NOUN:REGRET {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОЗДАНИЕ {} <to_english> ENG_NOUN:CREATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОЗДАНИЕ {} <to_english> ENG_NOUN:CREATURE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОЗНАНИЕ {} <to_english> ENG_NOUN:CONSCIOUSNESS {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОК {} <to_english> ENG_NOUN:JUICE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОЛДАТ {} <to_english> ENG_NOUN:SOLDIER {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОЛИДАРНОСТЬ {} <to_english> ENG_NOUN:SOLIDARITY {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОЛЬ {} <to_english> ENG_NOUN:SALT {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОМНЕНИЕ {} <to_english> ENG_NOUN:DOUBT {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОН {} <to_english> ENG_NOUN:SLEEP {}
 link СУЩЕСТВИТЕЛЬНОЕ:СООБЩЕНИЕ {} <to_english> ENG_NOUN:COMMUNICATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:СООРУЖЕНИЕ {} <to_english> ENG_NOUN:CONSTRUCTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:СООРУЖЕНИЕ {} <to_english> ENG_NOUN:BUILDING {}
 link СУЩЕСТВИТЕЛЬНОЕ:СООРУЖЕНИЕ {} <to_english> ENG_NOUN:STRUCTURE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОПЕРНИК {} <to_english> ENG_NOUN:OPPONENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОРЕВНОВАНИЕ {} <to_english> ENG_NOUN:COMPETITION {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОРОЧКА {} <to_english> ENG_NOUN:SHIRT {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОРОЧКА {} <to_english> ENG_NOUN:CHEMISE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОРТ {} <to_english> ENG_NOUN:SORT {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОРТ {} <to_english> ENG_NOUN:KIND {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОСЕД {} <to_english> ENG_NOUN:NEIGHBOUR {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОСТАВ {} <to_english> ENG_NOUN:COMPOSITION {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОСТАВ {} <to_english> ENG_NOUN:STRUCTURE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОСТОЯНИЕ {} <to_english> ENG_NOUN:CONDITION {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОСТОЯНИЕ {} <to_english> ENG_NOUN:STATE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОСТЯЗАНИЕ {} <to_english> ENG_NOUN:COMPETITION {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОСТЯЗАНИЕ {} <to_english> ENG_NOUN:CONTEST {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОЧУВСТВИЕ {} <to_english> ENG_NOUN:SYMPATHY {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОЮЗ {} <to_english> ENG_NOUN:UNION {}
 link СУЩЕСТВИТЕЛЬНОЕ:СОЮЗНИК {} <to_english> ENG_NOUN:ALLY {}
 link СУЩЕСТВИТЕЛЬНОЕ:СПАЛЬНЯ {} <to_english> ENG_NOUN:BEDROOM {}
 link СУЩЕСТВИТЕЛЬНОЕ:СПЕКТАКЛЬ {} <to_english> ENG_NOUN:PERFORMANCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СПЕКТАКЛЬ {} <to_english> ENG_NOUN:SHOW {}
 link СУЩЕСТВИТЕЛЬНОЕ:СПЕЦИАЛИСТ {} <to_english> ENG_NOUN:EXPERT {}
 link СУЩЕСТВИТЕЛЬНОЕ:СПИСОК {} <to_english> ENG_NOUN:LIST {}
 link СУЩЕСТВИТЕЛЬНОЕ:СПОР {} <to_english> ENG_NOUN:ARGUMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:СПРАВЕДЛИВОСТЬ {} <to_english> ENG_NOUN:JUSTICE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СПРАВКА {} <to_english> ENG_NOUN:CERTIFICATE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СПУСК {} <to_english> ENG_NOUN:DESCENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:СПУСК {} <to_english> ENG_NOUN:SLOPE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СПУТНИК {} <to_english> ENG_NOUN:COMPANION {}
 link СУЩЕСТВИТЕЛЬНОЕ:СРАВНЕНИЕ {} <to_english> ENG_NOUN:COMPARISON {}
 link СУЩЕСТВИТЕЛЬНОЕ:СРЕДА {} <to_english> ENG_NOUN:ENVIRONMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:СРЕДА {} <to_english> ENG_NOUN:WEDNESDAY {}
 link СУЩЕСТВИТЕЛЬНОЕ:СРОК {} <to_english> ENG_NOUN:DATE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СРОК {} <to_english> ENG_NOUN:TERM {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТАДИОН {} <to_english> ENG_NOUN:STADIUM {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТАДИЯ {} <to_english> ENG_NOUN:STAGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТАДО {} <to_english> ENG_NOUN:HERD {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТАКАН {} <to_english> ENG_NOUN:GLASS {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТАЛЬ {} <to_english> ENG_NOUN:STEEL {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТАНЦИЯ {} <to_english> ENG_NOUN:STATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТАРТ {} <to_english> ENG_NOUN:START {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТАТИСТИКА {} <to_english> ENG_NOUN:STATISTICS {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТАТЬЯ {} <to_english> ENG_NOUN:ARTICLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТЕКЛО {} <to_english> ENG_NOUN:GLASS {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТЕПЕНЬ {} <to_english> ENG_NOUN:DEGREE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТЕПЬ {} <to_english> ENG_NOUN:STEPPE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТИЛЬ {} <to_english> ENG_NOUN:STYLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТИПЕНДИЯ {} <to_english> ENG_NOUN:GRANT {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТОИМОСТЬ {} <to_english> ENG_NOUN:COST {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТОИМОСТЬ {} <to_english> ENG_NOUN:VALUE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТОЛБ {} <to_english> ENG_NOUN:PILLAR {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТОЛЕТИЕ {} <to_english> ENG_NOUN:CENTURY {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТОЛИЦА {} <to_english> ENG_NOUN:CAPITAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТОЛКНОВЕНИЕ {} <to_english> ENG_NOUN:COLLISION {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТОРОННИК {} <to_english> ENG_NOUN:SUPPORTER {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТОЯНКА {} <to_english> ENG_NOUN:STOP {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТРАНИЦА {} <to_english> ENG_NOUN:PAGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТРАХ {} <to_english> ENG_NOUN:FEAR {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТРАХОВАНИЕ {} <to_english> ENG_NOUN:INSURANCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТРЕЛКА {} <to_english> ENG_NOUN:HAND {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТРЕЛКА {} <to_english> ENG_NOUN:NEEDLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТРОЕНИЕ {} <to_english> ENG_NOUN:BUILDING {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТРОЕНИЕ {} <to_english> ENG_NOUN:CONSTRUCTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТРОЕНИЕ {} <to_english> ENG_NOUN:STRUCTURE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТРОКА {} <to_english> ENG_NOUN:LINE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТРУНА {} <to_english> ENG_NOUN:STRING {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТУДЕНТ {} <to_english> ENG_NOUN:STUDENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТУК {} <to_english> ENG_NOUN:KNOCK {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТУПЕНЬ {} <to_english> ENG_NOUN:STAGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СТЫД {} <to_english> ENG_NOUN:SHAME {}
 link СУЩЕСТВИТЕЛЬНОЕ:СУВЕНИР {} <to_english> ENG_NOUN:SOUVENIR {}
 link СУЩЕСТВИТЕЛЬНОЕ:СУД {} <to_english> ENG_NOUN:COURT {}
 link СУЩЕСТВИТЕЛЬНОЕ:СУДЬБА {} <to_english> ENG_NOUN:FATE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СУДЬБА {} <to_english> ENG_NOUN:DESTINY {}
 link СУЩЕСТВИТЕЛЬНОЕ:СУДЬЯ { род:муж } <to_english> ENG_NOUN:JUDGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СУМЕРКИ {} <to_english> ENG_NOUN:TWILIGHT {}
 link СУЩЕСТВИТЕЛЬНОЕ:СУМКА {} <to_english> ENG_NOUN:BAG {}
 link СУЩЕСТВИТЕЛЬНОЕ:СУММА {} <to_english> ENG_NOUN:SUM {}
 link СУЩЕСТВИТЕЛЬНОЕ:СУП {} <to_english> ENG_NOUN:SOUP {}
 link СУЩЕСТВИТЕЛЬНОЕ:СУПРУГ {} <to_english> ENG_NOUN:HUSBAND {}
 link СУЩЕСТВИТЕЛЬНОЕ:СУСТАВ {} <to_english> ENG_NOUN:JOINT {}
 link СУЩЕСТВИТЕЛЬНОЕ:СУЩЕСТВО { ОДУШ:ОДУШ } <to_english> ENG_NOUN:BEING {}
 link СУЩЕСТВИТЕЛЬНОЕ:СУЩЕСТВО { ОДУШ:ОДУШ } <to_english> ENG_NOUN:CREATURE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СУЩНОСТЬ {} <to_english> ENG_NOUN:ESSENCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЦЕНА {} <to_english> ENG_NOUN:STAGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЧЕТ {} <to_english> ENG_NOUN:ACCOUNT {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЧЕТ {} <to_english> ENG_NOUN:BILL {~ENG_PROPER_NOUN}
 link СУЩЕСТВИТЕЛЬНОЕ:СЫР {} <to_english> ENG_NOUN:CHEESE {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЮЖЕТ {} <to_english> ENG_NOUN:SUBJECT {}
 link СУЩЕСТВИТЕЛЬНОЕ:СЮРПРИЗ {} <to_english> ENG_NOUN:SURPRISE {}

 // ---------------------------------------------------------------------

 link СУЩЕСТВИТЕЛЬНОЕ:ТАБАК {} <to_english> ENG_NOUN:TOBACCO {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТАБЛЕТКА {} <to_english> ENG_NOUN:TABLET {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТАБЛЕТКА {} <to_english> ENG_NOUN:PILL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТАБЛИЦА {} <to_english> ENG_NOUN:TABLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТАБУРЕТКА {} <to_english> ENG_NOUN:STOOL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТАБУРЕТОЧКА {} <to_english> ENG_NOUN:STOOL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТАЗ {} <to_english> ENG_NOUN:PELVIS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТАЗ {} <to_english> ENG_NOUN:BASIN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТАКТ {} <to_english> ENG_NOUN:TACT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТАЛАНТ {} <to_english> ENG_NOUN:TALENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТАПКА {} <to_english> ENG_NOUN:SLIPPER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТАРЕЛКА {} <to_english> ENG_NOUN:PLATE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТВОРЧЕСТВО {} <to_english> ENG_NOUN:CREATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТЕАТР {} <to_english> ENG_NOUN:THEATRE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТЕКСТ {} <to_english> ENG_NOUN:TEXT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТЕЛЕВИДЕНИЕ {} <to_english> ENG_NOUN:TELEVISION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТЕЛЕГРАФ {} <to_english> ENG_NOUN:TELEGRAPH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТЕЛЕЖКА {} <to_english> ENG_NOUN:CART {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТЕЛЕФОН {} <to_english> ENG_NOUN:TELEPHONE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТЕЛЕФОН {} <to_english> ENG_NOUN:PHONE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТЕМА {} <to_english> ENG_NOUN:SUBJECT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТЕМА {} <to_english> ENG_NOUN:TOPIC {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТЕМНОТА {} <to_english> ENG_NOUN:DARK {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТЕМП {} <to_english> ENG_NOUN:RATE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТЕМП {} <to_english> ENG_NOUN:PACE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТЕМП {} <to_english> ENG_NOUN:TEMPO {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТЕМПЕРАТУРА {} <to_english> ENG_NOUN:TEMPERATURE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТЕННИС {} <to_english> ENG_NOUN:TENNIS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТЕНОР {} <to_english> ENG_NOUN:TENOR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТЕОРИЯ {} <to_english> ENG_NOUN:THEORY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТЕРРОР {} <to_english> ENG_NOUN:TERROR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТЕРРИТОРИЯ {} <to_english> ENG_NOUN:TERRITORY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТЕТЯ {} <to_english> ENG_NOUN:AUNT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТЕХНИКА {} <to_english> ENG_NOUN:TECHNICS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТЕЧЕНИЕ {} <to_english> ENG_NOUN:COURSE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТЕЧЕНИЕ {} <to_english> ENG_NOUN:CURRENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТЕЧЕНИЕ {} <to_english> ENG_NOUN:STREAM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТИГР {} <to_english> ENG_NOUN:TIGER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТИРАЖ {} <to_english> ENG_NOUN:PRINT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТИФ {} <to_english> ENG_NOUN:TYPHUS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТИШИНА {} <to_english> ENG_NOUN:QUIET {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТИШИНА {} <to_english> ENG_NOUN:CALM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТОВАРИЩ {} <to_english> ENG_NOUN:COMRADE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТОК {} <to_english> ENG_NOUN:CURRENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТОКАРЬ {} <to_english> ENG_NOUN:TURNER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТОЛК {} <to_english> ENG_NOUN:SENSE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТОЛПА {} <to_english> ENG_NOUN:CROWD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТОЛЧОК {} <to_english> ENG_NOUN:PUSH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТОМ {} <to_english> ENG_NOUN:VOLUME {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТОМАТ {} <to_english> ENG_NOUN:TOMATO {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТОН {} <to_english> ENG_NOUN:TONE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТОННА {} <to_english> ENG_NOUN:TON {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТОННЕЛЬ {} <to_english> ENG_NOUN:TUNNEL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТОПЛИВО {} <to_english> ENG_NOUN:FUEL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТОПОР {} <to_english> ENG_NOUN:AXE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТОСКА {} <to_english> ENG_NOUN:MELANCHOLY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТОСТ {} <to_english> ENG_NOUN:TOAST {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТРАКТОР {} <to_english> ENG_NOUN:TRACTOR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТРАМВАЙ {} <to_english> ENG_NOUN:TRAM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТРАМВАЙ {} <to_english> ENG_NOUN:"STREET-CAR" {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТРАНСЛЯЦИЯ {} <to_english> ENG_NOUN:BROADCAST {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТРАНСЛЯЦИЯ {} <to_english> ENG_NOUN:TRANSMISSION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТРАНСПОРТ {} <to_english> ENG_NOUN:TRANSPORT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТРАП {} <to_english> ENG_NOUN:LADDER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТРЕНЕР {} <to_english> ENG_NOUN:TRAINER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТРЕНЕР {} <to_english> ENG_NOUN:COACH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТРИБУНА {} <to_english> ENG_NOUN:ROSTRUM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТРОЛЛЕЙБУС {} <to_english> ENG_NOUN:"TROLLEY-BUS" {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТРОМБОН {} <to_english> ENG_NOUN:TROMBONE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТРОПА {} <to_english> ENG_NOUN:PATH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТРОСТЬ {} <to_english> ENG_NOUN:"WALKING-STICK" {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТРОСТЬ {} <to_english> ENG_NOUN:CANE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТРОТУАР {} <to_english> ENG_NOUN:PAVEMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТРОТУАР {} <to_english> ENG_NOUN:SIDEWALK {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТРУБА {} <to_english> ENG_NOUN:PIPE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТРУБА {} <to_english> ENG_NOUN:TUBE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТРУБКА {} <to_english> ENG_NOUN:TUBE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТРУД {} <to_english> ENG_NOUN:LABOUR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТРУД {} <to_english> ENG_NOUN:WORK {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТРУППА {} <to_english> ENG_NOUN:TROUPE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТУМАН {} <to_english> ENG_NOUN:MIST {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТУМАН {} <to_english> ENG_NOUN:FOG {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТУННЕЛЬ {} <to_english> ENG_NOUN:TUNNEL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТУР {} <to_english> ENG_NOUN:TURN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТУРБИНА {} <to_english> ENG_NOUN:TURBINE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТУРИЗМ {} <to_english> ENG_NOUN:TOURISM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТУРИСТ {} <to_english> ENG_NOUN:TOURIST {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТУРНИР {} <to_english> ENG_NOUN:TOURNAMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТУЧА {} <to_english> ENG_NOUN:CLOUD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТУЧКА {} <to_english> ENG_NOUN:CLOUD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТЯЖЕСТЬ {} <to_english> ENG_NOUN:LOAD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТЯЖЕСТЬ {} <to_english> ENG_NOUN:WEIGHT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ТЯЖЕСТЬ {} <to_english> ENG_NOUN:BURDEN {}
 link СУЩЕСТВИТЕЛЬНОЕ:УБЕЖДЕНИЕ {} <to_english> ENG_NOUN:CONVICTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:УБЕЖДЕНИЕ {} <to_english> ENG_NOUN:BELIEF {}
 link СУЩЕСТВИТЕЛЬНОЕ:УБЕЖИЩЕ {} <to_english> ENG_NOUN:ASYLUM {}
 link СУЩЕСТВИТЕЛЬНОЕ:УВАЖЕНИЕ {} <to_english> ENG_NOUN:RESPECT {}
 link СУЩЕСТВИТЕЛЬНОЕ:УВЕЛИЧЕНИЕ {} <to_english> ENG_NOUN:INCREASE {}
 link СУЩЕСТВИТЕЛЬНОЕ:УВЛЕЧЕНИЕ {} <to_english> ENG_NOUN:PASSION {}
 link СУЩЕСТВИТЕЛЬНОЕ:УВЛЕЧЕНИЕ {} <to_english> ENG_NOUN:ENTHUSIASM {}
 link СУЩЕСТВИТЕЛЬНОЕ:УВЛЕЧЕНИЕ {} <to_english> ENG_NOUN:INFATUATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:УВОЛЬНЕНИЕ {} <to_english> ENG_NOUN:DISCHARGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:УВОЛЬНЕНИЕ {} <to_english> ENG_NOUN:DISMISSAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:УГНЕТЕНИЕ {} <to_english> ENG_NOUN:OPRESSION {}
 link СУЩЕСТВИТЕЛЬНОЕ:УГОЛ {} <to_english> ENG_NOUN:CORNER {}
 link СУЩЕСТВИТЕЛЬНОЕ:УГОЛЬ {} <to_english> ENG_NOUN:COAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:УГОЩЕНИЕ {} <to_english> ENG_NOUN:TREAT {}
 link СУЩЕСТВИТЕЛЬНОЕ:УГОЩЕНИЕ {} <to_english> ENG_NOUN:REFRESHMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:УГРОЗА {} <to_english> ENG_NOUN:THREAT {}
 link СУЩЕСТВИТЕЛЬНОЕ:УГРОЗА {} <to_english> ENG_NOUN:MENACE {}
 link СУЩЕСТВИТЕЛЬНОЕ:УДАР {} <to_english> ENG_NOUN:BLOW {}
 link СУЩЕСТВИТЕЛЬНОЕ:УДАР {} <to_english> ENG_NOUN:STROKE {}
 link СУЩЕСТВИТЕЛЬНОЕ:УДАЧА {} <to_english> ENG_NOUN:SUCCESS {}
 link СУЩЕСТВИТЕЛЬНОЕ:УДАЧА {} <to_english> ENG_NOUN:LUCK {}
 link СУЩЕСТВИТЕЛЬНОЕ:УДИВЛЕНИЕ {} <to_english> ENG_NOUN:SURPRISE {}
 link СУЩЕСТВИТЕЛЬНОЕ:УДОБРЕНИЕ {} <to_english> ENG_NOUN:FERTILIZER {}
 link СУЩЕСТВИТЕЛЬНОЕ:УДОБСТВО {} <to_english> ENG_NOUN:CONVENIENCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:УДОВОЛЬСТВИЕ {} <to_english> ENG_NOUN:PLEASURE {}
 link СУЩЕСТВИТЕЛЬНОЕ:УДОЧКА {} <to_english> ENG_NOUN:"FISHING-ROD" {}
 link СУЩЕСТВИТЕЛЬНОЕ:УЖИН {} <to_english> ENG_NOUN:SUPPER {}
 link СУЩЕСТВИТЕЛЬНОЕ:УЗЕЛ {} <to_english> ENG_NOUN:KNOT {}
 link СУЩЕСТВИТЕЛЬНОЕ:УЗДЕЧКА {} <to_english> ENG_NOUN:BRIDLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:УЗОР {} <to_english> ENG_NOUN:DESIGN {}
 link СУЩЕСТВИТЕЛЬНОЕ:УЗОР {} <to_english> ENG_NOUN:PATTERN {}
 link СУЩЕСТВИТЕЛЬНОЕ:УКАЗ {} <to_english> ENG_NOUN:DECREE {}
 link СУЩЕСТВИТЕЛЬНОЕ:УКАЗ {} <to_english> ENG_NOUN:EDICT {}
 link СУЩЕСТВИТЕЛЬНОЕ:УКОЛ {} <to_english> ENG_NOUN:INJECTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:УКРАШЕНИЕ {} <to_english> ENG_NOUN:DECORATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:УКРАШЕНИЕ {} <to_english> ENG_NOUN:ORNAMENTATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:УКРАШЕНИЕ {} <to_english> ENG_NOUN:ADORNMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:УКРАШЕНИЕ {} <to_english> ENG_NOUN:ORNAMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:УКСУС {} <to_english> ENG_NOUN:VINEGAR {}
 link СУЩЕСТВИТЕЛЬНОЕ:УЛОВ {} <to_english> ENG_NOUN:CATCH {}
 link СУЩЕСТВИТЕЛЬНОЕ:УЛОВ {} <to_english> ENG_NOUN:TAKE {}
 link СУЩЕСТВИТЕЛЬНОЕ:УМ {} <to_english> ENG_NOUN:MIND {}
 link СУЩЕСТВИТЕЛЬНОЕ:УМ {} <to_english> ENG_NOUN:INTELLECT {}
 link СУЩЕСТВИТЕЛЬНОЕ:УМНОЖЕНИЕ {} <to_english> ENG_NOUN:MULTIPLICATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:УНИВЕРСИТЕТ {} <to_english> ENG_NOUN:UNIVERSITY {}
 link СУЩЕСТВИТЕЛЬНОЕ:УПОТРЕБЛЕНИЕ {} <to_english> ENG_NOUN:USE {}
 link СУЩЕСТВИТЕЛЬНОЕ:УПОТРЕБЛЕНИЕ {} <to_english> ENG_NOUN:USAGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:УПРАВЛЕНИЕ {} <to_english> ENG_NOUN:MANAGEMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:УПРАЖНЕНИЕ {} <to_english> ENG_NOUN:EXERCISE {}
 link СУЩЕСТВИТЕЛЬНОЕ:УПРАЖНЕНИЕ {} <to_english> ENG_NOUN:PRACTICE {}
 link СУЩЕСТВИТЕЛЬНОЕ:УПРЯЖЬ {} <to_english> ENG_NOUN:HARNESS {}
 link СУЩЕСТВИТЕЛЬНОЕ:УРАГАН {} <to_english> ENG_NOUN:HURRICANE {}
 link СУЩЕСТВИТЕЛЬНОЕ:УРНА {} <to_english> ENG_NOUN:"DUST-BIN" {}
 link СУЩЕСТВИТЕЛЬНОЕ:УРНА {} <to_english> ENG_NOUN:URN {}
 link СУЩЕСТВИТЕЛЬНОЕ:УРОВЕНЬ {} <to_english> ENG_NOUN:LEVEL {}
 link СУЩЕСТВИТЕЛЬНОЕ:УРОЖАЙ {} <to_english> ENG_NOUN:HARVEST {}
 link СУЩЕСТВИТЕЛЬНОЕ:УРОЖАЙ {} <to_english> ENG_NOUN:CROP {}
 link СУЩЕСТВИТЕЛЬНОЕ:УРОЖАЙ {} <to_english> ENG_NOUN:YIELD {}
 link СУЩЕСТВИТЕЛЬНОЕ:УРОК {} <to_english> ENG_NOUN:LESSON {}
 link СУЩЕСТВИТЕЛЬНОЕ:УСИЛИЕ {} <to_english> ENG_NOUN:EFFORT {}
 link СУЩЕСТВИТЕЛЬНОЕ:УСИЛИТЕЛЬ {} <to_english> ENG_NOUN:AMPLIFIER {}
 link СУЩЕСТВИТЕЛЬНОЕ:УСЛОВИЕ {} <to_english> ENG_NOUN:CONDITION {}
 link СУЩЕСТВИТЕЛЬНОЕ:УСТАЛОСТЬ {} <to_english> ENG_NOUN:TIREDNESS {}
 link СУЩЕСТВИТЕЛЬНОЕ:УСТАЛОСТЬ {} <to_english> ENG_NOUN:WEARINESS {}
 link СУЩЕСТВИТЕЛЬНОЕ:УСТРОЙСТВО {} <to_english> ENG_NOUN:PATTERN {}
 link СУЩЕСТВИТЕЛЬНОЕ:УСТРОЙСТВО {} <to_english> ENG_NOUN:STRUCTURE {}
 link СУЩЕСТВИТЕЛЬНОЕ:УСТУПКА {} <to_english> ENG_NOUN:CONCESSION {}
 link СУЩЕСТВИТЕЛЬНОЕ:УТКА {} <to_english> ENG_NOUN:DUCK {}
 link СУЩЕСТВИТЕЛЬНОЕ:УТОМЛЕНИЕ {} <to_english> ENG_NOUN:FATIGUE {}
 link СУЩЕСТВИТЕЛЬНОЕ:УТЮГ {} <to_english> ENG_NOUN:IRON {}
 link СУЩЕСТВИТЕЛЬНОЕ:УХУДШЕНИЕ {} <to_english> ENG_NOUN:DETERIORATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:УХУДШЕНИЕ {} <to_english> ENG_NOUN:CHANGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:УЧАСТИЕ {} <to_english> ENG_NOUN:PARTICIPATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:УЧАСТОК {} <to_english> ENG_NOUN:PLOT {}
 link СУЩЕСТВИТЕЛЬНОЕ:УЧЕБНИК {} <to_english> ENG_NOUN:"TEXT-BOOK" {}
 link СУЩЕСТВИТЕЛЬНОЕ:УЧЕБНИК {} <to_english> ENG_NOUN:MANUAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:УЧЕБНИК {} <to_english> ENG_NOUN:"SCHOOL-BOOK" {}
 link СУЩЕСТВИТЕЛЬНОЕ:УЧЕНИК {} <to_english> ENG_NOUN:PUPIL {}
 link СУЩЕСТВИТЕЛЬНОЕ:УЧРЕЖДЕНИЕ {} <to_english> ENG_NOUN:INSTITUTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:УЧРЕЖДЕНИЕ {} <to_english> ENG_NOUN:ESTABLISHMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:УЩЕРБ {} <to_english> ENG_NOUN:DAMAGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФАБРИКА {} <to_english> ENG_NOUN:FACTORY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФАБРИКА {} <to_english> ENG_NOUN:MILL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФАЙЛ {} <to_english> ENG_NOUN:FILE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФАКУЛЬТЕТ {} <to_english> ENG_NOUN:FACULTY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФАКУЛЬТЕТ {} <to_english> ENG_NOUN:DEPARTMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФАМИЛИЯ {} <to_english> ENG_NOUN:NAME {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФАРА {} <to_english> ENG_NOUN:HEADLIGHT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФАРФОР {} <to_english> ENG_NOUN:CHINA {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФАРФОР {} <to_english> ENG_NOUN:PORCELAIN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФАРФОР {} <to_english> ENG_NOUN:CHINAWARE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФАУНА {} <to_english> ENG_NOUN:FAUNA {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФЕВРАЛЬ {} <to_english> ENG_NOUN:FEBRUARY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФИЗИК {} <to_english> ENG_NOUN:PHYSICIST {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФИЗИКА {} <to_english> ENG_NOUN:PHYSICS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФИЛИАЛ {} <to_english> ENG_NOUN:BRANCH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФИЛОСОФ {} <to_english> ENG_NOUN:PHILOSOPHER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФИЛОСОФИЯ {} <to_english> ENG_NOUN:PHILOSOPHY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФИЛЬТР {} <to_english> ENG_NOUN:FILTER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФИНАЛ {} <to_english> ENG_NOUN:FINALE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФИНАЛ {} <to_english> ENG_NOUN:FINAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФИНИШ {} <to_english> ENG_NOUN:FINISH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФИРМА {} <to_english> ENG_NOUN:FIRM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФЛАГ {} <to_english> ENG_NOUN:FLAG {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФЛАКОН {} <to_english> ENG_NOUN:BOTTLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФЛОТ {} <to_english> ENG_NOUN:FLEET {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФОКУС {} <to_english> ENG_NOUN:FOCUS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФОКУС {} <to_english> ENG_NOUN:TRICK {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФОН {} <to_english> ENG_NOUN:BACKGROUND {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФОНАРЬ {} <to_english> ENG_NOUN:LANTERN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФОНД {} <to_english> ENG_NOUN:FUND {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФОНТАН {} <to_english> ENG_NOUN:FOUNTAIN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФОТОГРАФ {} <to_english> ENG_NOUN:PHOTOGRAPHER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФОТОГРАФИЯ {} <to_english> ENG_NOUN:PHOTOGRAPHY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФОТОГРАФИЯ {} <to_english> ENG_NOUN:PHOTO {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФОТОГРАФИЯ {} <to_english> ENG_NOUN:PICTURE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФРАЗА {} <to_english> ENG_NOUN:PHRASE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФРЕСКА {} <to_english> ENG_NOUN:FRESCO {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФРОНТ {} <to_english> ENG_NOUN:FRONT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФРУКТ {} <to_english> ENG_NOUN:FRUIT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФУРАЖКА {} <to_english> ENG_NOUN:CAP {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФУРАЖКА {} <to_english> ENG_NOUN:"PEAK-CAP" {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФУТБОЛ {} <to_english> ENG_NOUN:FOOTBALL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФУТБОЛ {} <to_english> ENG_NOUN:SOCCER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ФУТЛЯР {} <to_english> ENG_NOUN:CASE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ХАЛАТ {} <to_english> ENG_NOUN:"DRESSING-GOWN" {}
 link СУЩЕСТВИТЕЛЬНОЕ:ХАРАКТЕР {} <to_english> ENG_NOUN:CHARACTER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ХАРАКТЕР {} <to_english> ENG_NOUN:TEMPER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ХВОСТ {} <to_english> ENG_NOUN:TAIL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ХИМИК {} <to_english> ENG_NOUN:CHEMIST {}
 link СУЩЕСТВИТЕЛЬНОЕ:ХИМИК {} <to_english> ENG_NOUN:CHEMISTRY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ХИРУРГ {} <to_english> ENG_NOUN:SURGEON {}
 link СУЩЕСТВИТЕЛЬНОЕ:ХЛЕБ {} <to_english> ENG_NOUN:BREAD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ХОД {} <to_english> ENG_NOUN:MOTION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ХОЗЯИН {} <to_english> ENG_NOUN:MASTER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ХОЗЯИН {} <to_english> ENG_NOUN:BOSS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ХОЗЯИН {} <to_english> ENG_NOUN:OWNER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ХОЛМ {} <to_english> ENG_NOUN:HILL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ХОЛОД {} <to_english> ENG_NOUN:COLD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ХОЛСТ {} <to_english> ENG_NOUN:CANVAS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ХОР {} <to_english> ENG_NOUN:CHOIR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ХОР {} <to_english> ENG_NOUN:CHORUS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ХОХОТ {} <to_english> ENG_NOUN:LAUGHTER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ХРОНИКА {} <to_english> ENG_NOUN:CHRONICLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ХРОНОМЕТР {} <to_english> ENG_NOUN:CHRONOMETER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ХУЛИГАН {} <to_english> ENG_NOUN:HOOLIGAN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЦАРАПИНКА {} <to_english> ENG_NOUN:SCRATCH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЦВЕТОК {} <to_english> ENG_NOUN:FLOWER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЦЕЛЬ {} <to_english> ENG_NOUN:GOAL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЦЕМЕНТ {} <to_english> ENG_NOUN:CEMENT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЦЕНА {} <to_english> ENG_NOUN:PRICE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЦЕННОСТЬ {} <to_english> ENG_NOUN:VALUE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЦЕНТНЕР {} <to_english> ENG_NOUN:CENTNER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЦЕНТР {} <to_english> ENG_NOUN:CENTRE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЦЕНТР {} <to_english> ENG_NOUN:CENTER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЦЕРЕМОНИЯ {} <to_english> ENG_NOUN:CEREMONY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЦЕРКОВЬ {} <to_english> ENG_NOUN:CHURCH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЦИФРА {} <to_english> ENG_NOUN:FIGURE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЧАШКА {} <to_english> ENG_NOUN:CUP {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЧЕЛЮСТЬ {} <to_english> ENG_NOUN:JAW {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЧЕМОДАН {} <to_english> ENG_NOUN:SUITCASE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЧЕРВЬ {} <to_english> ENG_NOUN:WORM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЧЕРЕП {} <to_english> ENG_NOUN:SKULL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЧЕРНИКА {} <to_english> ENG_NOUN:BILBERRY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЧЕРТ {} <to_english> ENG_NOUN:DEVIL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЧЕРТА {} <to_english> ENG_NOUN:LINE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЧЕРТЕЖ {} <to_english> ENG_NOUN:DRAUGHT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЧЕРТЕЖ {} <to_english> ENG_NOUN:DRAFT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЧЕСТНОСТЬ {} <to_english> ENG_NOUN:HONESTY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЧЕСТЬ {} <to_english> ENG_NOUN:HONOUR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЧИТАТЕЛЬ {} <to_english> ENG_NOUN:READER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЧЛЕН { одуш:одуш } <to_english> ENG_NOUN:MEMBER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЧУВСТВО {} <to_english> ENG_NOUN:SENSE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЧУДАК {} <to_english> ENG_NOUN:CRANK {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЧУДАК {} <to_english> ENG_NOUN:ECCENTRIC {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЧУЛОК {} <to_english> ENG_NOUN:STOCKING {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШАНС {} <to_english> ENG_NOUN:CHANCE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШАНТАЖ {} <to_english> ENG_NOUN:BLACKMAIL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШАПКА {} <to_english> ENG_NOUN:CAP {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШАР {} <to_english> ENG_NOUN:BALL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШАР {} <to_english> ENG_NOUN:SPHERE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШАРФ {} <to_english> ENG_NOUN:SCARF {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШАРФ {} <to_english> ENG_NOUN:MUFFLER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШАХТА {} <to_english> ENG_NOUN:MINE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШАХТА {} <to_english> ENG_NOUN:PIT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШЕДЕВР {} <to_english> ENG_NOUN:"MASTER-PIECE" {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШЕЛЕСТ {} <to_english> ENG_NOUN:RUSTLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШЕПОТ {} <to_english> ENG_NOUN:WHISPER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШЕСТВИЕ {} <to_english> ENG_NOUN:PROCESSION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШЕФ {} <to_english> ENG_NOUN:PATRON {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШЕФ {} <to_english> ENG_NOUN:CHIEF {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШЕЯ {} <to_english> ENG_NOUN:NECK {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШИНА {} <to_english> ENG_NOUN:TYRE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШИНА {} <to_english> ENG_NOUN:TIRE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШИП {} <to_english> ENG_NOUN:THORN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШИРОТА {} <to_english> ENG_NOUN:LATITUDE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШИФР {} <to_english> ENG_NOUN:CIPHER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШИШКА {} <to_english> ENG_NOUN:LUMP {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШКАФ {} <to_english> ENG_NOUN:CUPBOARD {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШКОЛЬНИК {} <to_english> ENG_NOUN:SHOOLBOY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШПИЛЬКА {} <to_english> ENG_NOUN:HAIRPIN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШПИОН {} <to_english> ENG_NOUN:SPY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШРАМ {} <to_english> ENG_NOUN:SCAR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШТАПЕЛЬ {} <to_english> ENG_NOUN:STAPLE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШТИЛЬ {} <to_english> ENG_NOUN:CALM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШТОПОР {} <to_english> ENG_NOUN:"CORK-SCREW" {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШТОРА {} <to_english> ENG_NOUN:CURTAIN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШТОРА {} <to_english> ENG_NOUN:DRAPERY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШТОРМ {} <to_english> ENG_NOUN:STORM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШТРАФ {} <to_english> ENG_NOUN:FINE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШТУКА {} <to_english> ENG_NOUN:PIECE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШТУРМ {} <to_english> ENG_NOUN:ASSAULT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШУБА {} <to_english> ENG_NOUN:"FUR-COAT" {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШУМ {} <to_english> ENG_NOUN:NOISE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ШУТКА {} <to_english> ENG_NOUN:JOKE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЩАВЕЛЬ {} <to_english> ENG_NOUN:SORREL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЩЕКА {} <to_english> ENG_NOUN:CHEEK {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЩЕТКА {} <to_english> ENG_NOUN:BRUSH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭВМ {} <to_english> ENG_NOUN:COMPUTER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭКЗАМЕН {} <to_english> ENG_NOUN:EXAMINATION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭКЗАМЕН {} <to_english> ENG_NOUN:EXAM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭКВАТОР {} <to_english> ENG_NOUN:EQUATOR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭКЗЕМПЛЯР {} <to_english> ENG_NOUN:COPY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭКИПАЖ {} <to_english> ENG_NOUN:CREW {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭКОНОМИКА {} <to_english> ENG_NOUN:ECONOMY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭКРАН {} <to_english> ENG_NOUN:SCREEN {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭКСКАВАТОР {} <to_english> ENG_NOUN:EXCAVATOR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭКСКУРСИЯ {} <to_english> ENG_NOUN:EXCURSION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭКСПЕДИЦИЯ {} <to_english> ENG_NOUN:EXPEDISION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭКСПОЗИЦИЯ {} <to_english> ENG_NOUN:EXPOSITION {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭКСПОНАТ {} <to_english> ENG_NOUN:EXHIBIT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭЛЕВАТОР {} <to_english> ENG_NOUN:ELEVATOR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭМБЛЕМА {} <to_english> ENG_NOUN:EMBLEM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭНЕРГИЯ {} <to_english> ENG_NOUN:ENERGY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭНТУЗИАЗМ {} <to_english> ENG_NOUN:ENTHUSIASM {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭНТУЗИАСТ {} <to_english> ENG_NOUN:ENTHUSIAST {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭНЦИКЛОПЕДИЯ {} <to_english> ENG_NOUN:ENCYCLOPAEDIA {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭСКАЛАТОР {} <to_english> ENG_NOUN:ESCALATOR {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭТАЖ {} <to_english> ENG_NOUN:STOREY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭТАП {} <to_english> ENG_NOUN:STAGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭТИКЕТ {} <to_english> ENG_NOUN:ETIQUETTE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭТИКЕТКА {} <to_english> ENG_NOUN:LABEL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЭФИР {} <to_english> ENG_NOUN:ETHER {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЮНОША {} <to_english> ENG_NOUN:YOUTH {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЯДРО {} <to_english> ENG_NOUN:KERNEL {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЯДРО {} <to_english> ENG_NOUN:NUCLEUS {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЯЗЫК {} <to_english> ENG_NOUN:TONGUE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЯИЧНИЦА {} <to_english> ENG_NOUN:OMELET {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЯИЧНИЦА {} <to_english> ENG_NOUN:OMELETTE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЯМА {} <to_english> ENG_NOUN:PIT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЯМКА {} <to_english> ENG_NOUN:PIT {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЯНВАРЬ {} <to_english> ENG_NOUN:JANUARY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЯРОСТЬ {} <to_english> ENG_NOUN:FURY {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЯРОСТЬ {} <to_english> ENG_NOUN:RAGE {}
 link СУЩЕСТВИТЕЛЬНОЕ:ЯХТА {} <to_english> ENG_NOUN:YACHT {}



 link СУЩЕСТВИТЕЛЬНОЕ: "Албания" {} <to_english> ENG_NOUN:"Albania" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Алжир" {} <to_english> ENG_NOUN:"Algeria" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Самоа" {} <to_english> ENG_NOUN:"Samoa" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Андорра" {} <to_english> ENG_NOUN:"Andorra" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Ангола" {} <to_english> ENG_NOUN:"Angola" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Ангилья" {} <to_english> ENG_NOUN:"Anguilla" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Антарктика" {} <to_english> ENG_NOUN:"Antarctica" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Антигуа" {} <to_english> ENG_NOUN:"Antigua" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Аргентина" {} <to_english> ENG_NOUN:"Argentina" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Армения" {} <to_english> ENG_NOUN:"Armenia" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Аруба" {} <to_english> ENG_NOUN:"Aruba" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Австралия" {} <to_english> ENG_NOUN:"Australia" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Австрия" {} <to_english> ENG_NOUN:"Austria" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Азербайджан" {} <to_english> ENG_NOUN:"Azerbaijan" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Бахрейн" {} <to_english> ENG_NOUN:"Bahrain" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Бангладеш" {} <to_english> ENG_NOUN:"Bangladesh" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Барбадос" {} <to_english> ENG_NOUN:"Barbados" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Беларусь" {} <to_english> ENG_NOUN:"Belarus" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Бельгия" {} <to_english> ENG_NOUN:"Belgium" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Белиз" {} <to_english> ENG_NOUN:"Belize" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Бенин" {} <to_english> ENG_NOUN:"Benin" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Бермуды" {} <to_english> ENG_NOUN:"Bermuda" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Бутан" {} <to_english> ENG_NOUN:"Bhutan" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Боливия" {} <to_english> ENG_NOUN:"Bolivia" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Босния" {} <to_english> ENG_NOUN:"Bosnia" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Ботсвана" {} <to_english> ENG_NOUN:"Botswana" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Бразилия" {} <to_english> ENG_NOUN:"Brazil" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Бруней" {} <to_english> ENG_NOUN:"Brunei Darussalam" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Болгария" {} <to_english> ENG_NOUN:"Bulgaria" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Буркина Фасо" {} <to_english> ENG_NOUN:"Burkina Faso" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Бурунди" {} <to_english> ENG_NOUN:"Burundi" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Камбоджа" {} <to_english> ENG_NOUN:"Cambodia" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Камерун" {} <to_english> ENG_NOUN:"Cameroon" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Канада" {} <to_english> ENG_NOUN:"Canada" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Чад" {CharCasing:FirstCapitalized} <to_english> ENG_NOUN:"Chad" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Чили" {} <to_english> ENG_NOUN:"Chile" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Китай" {} <to_english> ENG_NOUN:"China" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Колумбия" {} <to_english> ENG_NOUN:"Colombia" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Конго" {} <to_english> ENG_NOUN:"Congo" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Хорватия" {} <to_english> ENG_NOUN:"Croatia" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Куба" {} <to_english> ENG_NOUN:"Cuba" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Кипр" {} <to_english> ENG_NOUN:"Cyprus" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Чехия" {} <to_english> ENG_NOUN:"Czech" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Дания" {} <to_english> ENG_NOUN:"Denmark" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Джибути" {} <to_english> ENG_NOUN:"Djibouti" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Доминика" {} <to_english> ENG_NOUN:"Dominica" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Эквадор" {} <to_english> ENG_NOUN:"Ecuador" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Египет" {} <to_english> ENG_NOUN:"Egypt" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Сальвадор" {} <to_english> ENG_NOUN:"El Salvador" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Англия" {} <to_english> ENG_NOUN:"England" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Гвинея" {} <to_english> ENG_NOUN:"Guinea" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Эритрея" {} <to_english> ENG_NOUN:"Eritrea" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Эстония" {} <to_english> ENG_NOUN:"Estonia" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Эфиопия" {} <to_english> ENG_NOUN:"Ethiopia" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Фиджи" {} <to_english> ENG_NOUN:"Fiji" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Финляндия" {} <to_english> ENG_NOUN:"Finland" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Франция" {} <to_english> ENG_NOUN:"France" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Гвиана" {} <to_english> ENG_NOUN:"Guiana" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Полинезия" {} <to_english> ENG_NOUN:"Polynesia" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Габон" {} <to_english> ENG_NOUN:"Gabon" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Гамбия" {} <to_english> ENG_NOUN:"Gambia" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Грузия" {} <to_english> ENG_NOUN:"Georgia" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Германия" {} <to_english> ENG_NOUN:"Germany" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Гана" {} <to_english> ENG_NOUN:"Ghana" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Гибралтар" {} <to_english> ENG_NOUN:"Gibraltar" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Греция" {} <to_english> ENG_NOUN:"Greece" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Гренландия" {} <to_english> ENG_NOUN:"Greenland" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Гренада" {} <to_english> ENG_NOUN:"Grenada" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Гваделупа" {} <to_english> ENG_NOUN:"Guadeloupe" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Гуам" {} <to_english> ENG_NOUN:"Guam" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Гватемала" {} <to_english> ENG_NOUN:"Guatemala" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Гвинея" {} <to_english> ENG_NOUN:"Guinea" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Гвинея-Бисау" {} <to_english> ENG_NOUN:"Guinea-Bissau" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Гайана" {} <to_english> ENG_NOUN:"Guyana" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Гаити" {} <to_english> ENG_NOUN:"Haiti" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Гондурас" {} <to_english> ENG_NOUN:"Honduras" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Гонконг" {} <to_english> ENG_NOUN:"Hong Kong" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Венгрия" {} <to_english> ENG_NOUN:"Hungary" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Исландия" {} <to_english> ENG_NOUN:"Iceland" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Индия" {} <to_english> ENG_NOUN:"India" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Индонезия" {} <to_english> ENG_NOUN:"Indonesia" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Иран" {} <to_english> ENG_NOUN:"Iran" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Ирак" {} <to_english> ENG_NOUN:"Iraq" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Ирландия" {} <to_english> ENG_NOUN:"Ireland" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Израиль" {} <to_english> ENG_NOUN:"Israel" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Италия" {} <to_english> ENG_NOUN:"Italy" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Ямайка" {} <to_english> ENG_NOUN:"Jamaica" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Япония" {} <to_english> ENG_NOUN:"Japan" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Иордания" {} <to_english> ENG_NOUN:"Jordan" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Казахстан" {} <to_english> ENG_NOUN:"Kazakhstan" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Кения" {} <to_english> ENG_NOUN:"Kenya" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Кирибати" {} <to_english> ENG_NOUN:"Kiribati" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Корея" {} <to_english> ENG_NOUN:"Korea" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Кувейт" {} <to_english> ENG_NOUN:"Kuwait" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Кыргызстан" {} <to_english> ENG_NOUN:"Kyrgyzstan" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Лаос" {} <to_english> ENG_NOUN:"Lao" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Латвия" {} <to_english> ENG_NOUN:"Latvia" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Ливан" {} <to_english> ENG_NOUN:"Lebanon" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Лесото" {} <to_english> ENG_NOUN:"Lesotho" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Либерия" {} <to_english> ENG_NOUN:"Liberia" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Ливия" {} <to_english> ENG_NOUN:"Libya" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Лихтенштейн" {} <to_english> ENG_NOUN:"Liechtenstein" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Литва" {} <to_english> ENG_NOUN:"Lithuania" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Люксембург" {} <to_english> ENG_NOUN:"Luxembourg" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Макао" {} <to_english> ENG_NOUN:"Macau" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Македония" {} <to_english> ENG_NOUN:"Macedonia" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Мадагаскар" {} <to_english> ENG_NOUN:"Madagascar" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Малави" {} <to_english> ENG_NOUN:"Malawi" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Малайзия" {} <to_english> ENG_NOUN:"Malaysia" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Мальдивские острова" {} <to_english> ENG_NOUN:"Maldives" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Мали" {} <to_english> ENG_NOUN:"Mali" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Мальта" {} <to_english> ENG_NOUN:"Malta" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Мартиника" {} <to_english> ENG_NOUN:"Martinique" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Мавритания" {} <to_english> ENG_NOUN:"Mauritania" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Маврикий" {} <to_english> ENG_NOUN:"Mauritius" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Майотта" {} <to_english> ENG_NOUN:"Mayotte" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Мексика" {} <to_english> ENG_NOUN:"Mexico" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Микронезия" {} <to_english> ENG_NOUN:"Micronesia" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Молдова" {} <to_english> ENG_NOUN:"Moldova" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Монако" {} <to_english> ENG_NOUN:"Monaco" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Монголия" {} <to_english> ENG_NOUN:"Mongolia" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Монтсеррат" {} <to_english> ENG_NOUN:"Montserrat" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Марокко" {} <to_english> ENG_NOUN:"Morocco" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Мозамбик" {} <to_english> ENG_NOUN:"Mozambique" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Мьянма" {} <to_english> ENG_NOUN:"Myanmar" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Намибия" {} <to_english> ENG_NOUN:"Namibia" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Науру" {} <to_english> ENG_NOUN:"Nauru" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Непал" {} <to_english> ENG_NOUN:"Nepal" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Нидерланды" {} <to_english> ENG_NOUN:"Netherlands" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Каледония" {} <to_english> ENG_NOUN:"Caledonia" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Зеландия" {} <to_english> ENG_NOUN:"Zealand" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Никарагуа" {} <to_english> ENG_NOUN:"Nicaragua" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Нигер" {} <to_english> ENG_NOUN:"Niger" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Нигерия" {} <to_english> ENG_NOUN:"Nigeria" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Ниуэ" {} <to_english> ENG_NOUN:"Niue" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Норвегия" {} <to_english> ENG_NOUN:"Norway" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Оман" {} <to_english> ENG_NOUN:"Oman" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Пакистан" {} <to_english> ENG_NOUN:"Pakistan" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Палау" {} <to_english> ENG_NOUN:"Palau" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Палестина" {} <to_english> ENG_NOUN:"Palestina" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Панама" {} <to_english> ENG_NOUN:"Panama" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Папуа" {} <to_english> ENG_NOUN:"Papua" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Парагвай" {} <to_english> ENG_NOUN:"Paraguay" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Перу" {} <to_english> ENG_NOUN:"Peru" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Филиппины" {} <to_english> ENG_NOUN:"Philippines" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Польша" {} <to_english> ENG_NOUN:"Poland" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Португалия" {} <to_english> ENG_NOUN:"Portugal" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Пуэрто-Рико" {} <to_english> ENG_NOUN:"Puerto Rico" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Катар" {} <to_english> ENG_NOUN:"Qatar" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Реюньон" {} <to_english> ENG_NOUN:"Reunion" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Румыния" {} <to_english> ENG_NOUN:"Romania" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Россия" {} <to_english> ENG_NOUN:"Russia" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Руанда" {} <to_english> ENG_NOUN:"Rwanda" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Самоа" {} <to_english> ENG_NOUN:"Samoa" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Сан-Марино" {} <to_english> ENG_NOUN:"San Marino" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Аравия" {} <to_english> ENG_NOUN:"Saudi" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Шотландия" {} <to_english> ENG_NOUN:"Scotland" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Сенегал" {} <to_english> ENG_NOUN:"Senegal" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Сьерра-Леоне" {} <to_english> ENG_NOUN:"Sierra Leone" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Сингапур" {} <to_english> ENG_NOUN:"Singapore" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Словакия" {} <to_english> ENG_NOUN:"Slovakia" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Словения" {} <to_english> ENG_NOUN:"Slovenia" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Соломоновы острова" {} <to_english> ENG_NOUN:"Solomon Islands" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Сомали" {} <to_english> ENG_NOUN:"Somalia" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Испания" {} <to_english> ENG_NOUN:"Spain" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Шри Ланка" {} <to_english> ENG_NOUN:"Sri Lanka" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Судан" {} <to_english> ENG_NOUN:"Sudan" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Суринам" {} <to_english> ENG_NOUN:"Suriname" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Свазиленд" {} <to_english> ENG_NOUN:"Swaziland" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Швеция" {} <to_english> ENG_NOUN:"Sweden" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Швейцария" {} <to_english> ENG_NOUN:"Switzerland" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Сирия" {} <to_english> ENG_NOUN:"Syrian Arab Republic" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Тайвань" {} <to_english> ENG_NOUN:"Taiwan" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Таджикистан" {} <to_english> ENG_NOUN:"Tajikistan" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Танзания" {} <to_english> ENG_NOUN:"Tanzania" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Тайланд" {} <to_english> ENG_NOUN:"Thailand" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Тимор" {} <to_english> ENG_NOUN:"Timor" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Того" {} <to_english> ENG_NOUN:"Togo" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Токелау" {} <to_english> ENG_NOUN:"Tokelau" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Тонга" {} <to_english> ENG_NOUN:"Tonga" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Тринидад" {} <to_english> ENG_NOUN:"Trinidad" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Тунис" {} <to_english> ENG_NOUN:"Tunisia" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Турция" {} <to_english> ENG_NOUN:"Turkey" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Туркменистан" {} <to_english> ENG_NOUN:"Turkmenistan" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Тувалу" {} <to_english> ENG_NOUN:"Tuvalu" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Уганда" {} <to_english> ENG_NOUN:"Uganda" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Украина" {} <to_english> ENG_NOUN:"Ukraine" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Уругвай" {} <to_english> ENG_NOUN:"Uruguay" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Узбекистан" {} <to_english> ENG_NOUN:"Uzbekistan" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Вануату" {} <to_english> ENG_NOUN:"Vanuatu" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Ватикан" {} <to_english> ENG_NOUN:"Vatican" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Венесуэла" {} <to_english> ENG_NOUN:"Venezuela" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Вьетнам" {} <to_english> ENG_NOUN:"Viet Nam" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Уэльс" {} <to_english> ENG_NOUN:"Wales" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Сахара" {} <to_english> ENG_NOUN:"Sahara" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Йемен" {} <to_english> ENG_NOUN:"Yemen" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Югославия" {} <to_english> ENG_NOUN:"Yugoslavia" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Замбия" {} <to_english> ENG_NOUN:"Zambia" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Зимбабве" {} <to_english> ENG_NOUN:"Zimbabwe" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Афганистан" {} <to_english> ENG_NOUN:"Afghanistan" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Барбуда" {} <to_english> ENG_NOUN:"Barbuda" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Тобаго" {} <to_english> ENG_NOUN:"Tobago" {}
 link СУЩЕСТВИТЕЛЬНОЕ: "Герцеговина" {} <to_english> ENG_NOUN:"Herzegovina" {}

 LINK_NOUN( Водород , Hydrogen )
 LINK_NOUN( Неон , Neon )
 LINK_NOUN( Фермий , Fermium )
 LINK_NOUN( Менделевий , Mendelevium )
 LINK_NOUN( Нобелий , Nobelium )
 LINK_NOUN( Лоуренсий , Lawrencium )
 LINK_NOUN( Резерфордий , Rutherfordium )
 LINK_NOUN( Дубний , Dubnium )
 LINK_NOUN( Сиборгий , Seaborgium )
 LINK_NOUN( Борий , Bohrium )
 LINK_NOUN( Хассий , Hassium )
 LINK_NOUN( Мейтнерий , Meitnerium )
 LINK_NOUN( Натрий , Sodium )
 LINK_NOUN( Дармштадтий , Darmstadtium )
 LINK_NOUN( Рентгений , Roentgenium )
 LINK_NOUN( Магний , Magnesium )
 LINK_NOUN( Алюминий , Aluminium )
 LINK_NOUN( Кремний , Silicon )
 LINK_NOUN( Фосфор , Phosphorus )
 LINK_NOUN( Сера , Sulfur )
 LINK_NOUN( Хлор , Chlorine )
 LINK_NOUN( Аргон , Argon )
 LINK_NOUN( Калий , Potassium )
 LINK_NOUN( Гелий , Helium )
 LINK_NOUN( Кальций , Calcium )
 LINK_NOUN( Скандий , Scandium )
 LINK_NOUN( Титан , Titanium )
 LINK_NOUN( Ванадий , Vanadium )
 LINK_NOUN( Хром , Chromium )
 LINK_NOUN( Марганец , Manganese )
 LINK_NOUN( Железо , Iron )
 LINK_NOUN( Кобальт , Cobalt )
 LINK_NOUN( Никель , Nickel )
 LINK_NOUN( Медь , Copper )
 LINK_NOUN( Литий , Lithium )
 LINK_NOUN( Цинк , Zinc )
 LINK_NOUN( Галлий , Gallium )
 LINK_NOUN( Германий , Germanium )
 LINK_NOUN( Мышьяк , Arsenic )
 LINK_NOUN( Селен , Selenium )
 LINK_NOUN( Бром , Bromine )
 LINK_NOUN( Криптон , Krypton )
 LINK_NOUN( Рубидий , Rubidium )
 LINK_NOUN( Стронций , Strontium )
 LINK_NOUN( Иттрий , Yttrium )
 LINK_NOUN( Бериллий , Beryllium )
 LINK_NOUN( Цирконий , Zirconium )
 LINK_NOUN( Ниобий , Niobium )
 LINK_NOUN( Молибден , Molybdenum )
 LINK_NOUN( Технеций , Technetium )
 LINK_NOUN( Рутений , Ruthenium )
 LINK_NOUN( Родий , Rhodium )
 LINK_NOUN( Палладий , Palladium )
 LINK_NOUN( Серебро , Silver )
 LINK_NOUN( Кадмий , Cadmium )
 LINK_NOUN( Индий , Indium )
 LINK_NOUN( Бор , Boron )
 LINK_NOUN( Олово , Tin )
 LINK_NOUN( Сурьма , Antimony )
 LINK_NOUN( Теллур , Tellurium )
 LINK_NOUN( Иод , Iodine )
 LINK_NOUN( Ксенон , Xenon )
 LINK_NOUN( Цезий , Caesium )
 LINK_NOUN( Барий , Barium )
 LINK_NOUN( Лантан , Lanthanum )
 LINK_NOUN( Церий , Cerium )
 LINK_NOUN( Празеодим , Praseodymium )
 LINK_NOUN( Углерод , Carbon )
 LINK_NOUN( Неодим , Neodymium )
 LINK_NOUN( Прометий , Promethium )
 LINK_NOUN( Самарий , Samarium )
 LINK_NOUN( Европий , Europium )
 LINK_NOUN( Гадолиний , Gadolinium )
 LINK_NOUN( Тербий , Terbium )
 LINK_NOUN( Диспрозий , Dysprosium )
 LINK_NOUN( Гольмий , Holmium )
 LINK_NOUN( Эрбий , Erbium )
 LINK_NOUN( Тулий , Thulium )
 LINK_NOUN( Азот , Nitrogen )
 LINK_NOUN( Иттербий , Ytterbium )
 LINK_NOUN( Лютеций , Lutetium )
 LINK_NOUN( Гафний , Hafnium )
 LINK_NOUN( Тантал , Tantalum )
 LINK_NOUN( Вольфрам , Tungsten )
 LINK_NOUN( Рений , Rhenium )
 LINK_NOUN( Осмий , Osmium )
 LINK_NOUN( Иридий , Iridium )
 LINK_NOUN( Платина , Platinum )
 LINK_NOUN( Золото , Gold )
 LINK_NOUN( Кислород , Oxygen )
 LINK_NOUN( Ртуть , Mercury )
 LINK_NOUN( Таллий , Thallium )
 LINK_NOUN( Свинец , Lead )
 LINK_NOUN( Висмут , Bismuth )
 LINK_NOUN( Полоний , Polonium )
 LINK_NOUN( Астат , Astatine )
 LINK_NOUN( Радон , Radon )
 LINK_NOUN( Франций , Francium )
 LINK_NOUN( Радий , Radium )
 LINK_NOUN( Актиний , Actinium )
 LINK_NOUN( Фтор , Fluorine )
 LINK_NOUN( Торий , Thorium )
 LINK_NOUN( Протактиний , Protactinium )
 LINK_NOUN( Нептуний , Neptunium )
 LINK_NOUN( Плутоний , Plutonium )
 LINK_NOUN( Америций , Americium )
 LINK_NOUN( Кюрий , Curium )
 LINK_NOUN( Берклий , Berkelium )
 LINK_NOUN( Калифорний , Californium )
 LINK_NOUN( Эйнштейний , Einsteinium )






 link ENG_NOUN:ZOOPLANKTON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:зоопланктон {}
 link ENG_NOUN:ZOOLOGIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:зоолог {}
 link ENG_NOUN:ZOMBIE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:зомби {}
 link ENG_NOUN:ZODIAC {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:зодиак {}
 link ENG_NOUN:ZIRCON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:циркон {}
 link ENG_NOUN:ZIRCONIUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:цирконий {}
 link ENG_NOUN:ZINC {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:цинк {}
 link ENG_NOUN:ZIMBABWE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:зимбабве {}
 link ENG_NOUN:ZIGZAG {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:зигзаг {}
 link ENG_NOUN:ZEPPELIN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:цеппелин {}
 link ENG_NOUN:ZEBRA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:зебра {}
 link ENG_NOUN:ZEALOT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:зилот {}
 link ENG_NOUN:YTTERBIUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:иттербий {}
 link ENG_NOUN:YTTRIUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:иттрий {}
 link ENG_NOUN:YOGHURT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:йогурт {}
 link ENG_NOUN:YOGA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:йога {}
 link ENG_NOUN:YANKEE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:янки {}
 link ENG_NOUN:XYLOPHONE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ксилофон {}
 link ENG_NOUN:XMAS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:рождество {}
 link ENG_NOUN:XEROX {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ксерокс {}
 link ENG_NOUN:XEROGRAPHY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ксерография {}
 link ENG_NOUN:XENOPHOBIA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ксенофобия {}
 link ENG_NOUN:XENOPHOBE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ксенофоб {}
 link ENG_NOUN:WUNDERKIND {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вундеркинд {}
 link ENG_NOUN:WRONGNESS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ошибочность {}
 link ENG_NOUN:WRITING {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:письмо {}
 link ENG_NOUN:WRIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:запястье {}
 link ENG_NOUN:WRAPPER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:обертка {}
 link ENG_NOUN:WORSHIP {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:поклонение {}
 link ENG_NOUN:WORSHIP {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:преклонение {}
 link ENG_NOUN:WORMHOLE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:червоточина {}
 link ENG_NOUN:WORLD {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мир {}
 link ENG_VERB:WORK {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:работа {}
 link ENG_NOUN:WORKABILITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:работоспособность {}
 link ENG_NOUN:WOOL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:шерсть {}
 link ENG_NOUN:WOMBAT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вомбат {}
 link ENG_NOUN:WOLFRAM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вольфрам {}
 link ENG_NOUN:WISDOM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мудрость {}
 link ENG_NOUN:WIRE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:проволока {}
 link ENG_NOUN:WIRE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:провод {}
 link ENG_NOUN:WINTERTIME {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:зима {}
 link ENG_NOUN:WINNER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:победитель {}
 link ENG_NOUN:WINEGLASS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:рюмка {}
 link ENG_NOUN:WIDTH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ширина {}
 link ENG_NOUN:WIDOW {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вдова {}
 link ENG_NOUN:WIDGET {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:виджет {}
 link ENG_NOUN:WHISKY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:виски {}
 link ENG_NOUN:WHISKEY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:виски {}
 link ENG_NOUN:WEST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:запад {}
 link ENG_NOUN:WESTERN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вестерн {}
 link ENG_NOUN:WEREWOLF {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вервольф {}
 link ENG_NOUN:WEREWOLF {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:оборотень {}
 link ENG_NOUN:WEISMANNISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вейсманизм {}
 link ENG_NOUN:WEAPON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:оружие {}
 link ENG_NOUN:WEALTH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:благосостояние {}
 link ENG_NOUN:WAVELET {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вейвлет {}
 link ENG_NOUN:WATT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ватт {}
 link ENG_NOUN:WATERFALL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:водопад {}
 link ENG_NOUN:WASTE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:отход {}
 link ENG_NOUN:WASP {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:оса {}
 link ENG_NOUN:WASH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мытье {}
 link ENG_NOUN:WASHING {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мытье {}
 link ENG_NOUN:WASHERWOMAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:прачка {}
 link ENG_NOUN:WALKWAY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тротуар {}
 link ENG_NOUN:WALKMAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пешеход {}
 link ENG_NOUN:WAGON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вагон {}
 link ENG_NOUN:VULNERABILITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:уязвимость {}
 link ENG_NOUN:VULGARITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вульгарность {}
 link ENG_NOUN:VULGARISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вульгаризм {}
 link ENG_NOUN:VULCANOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вулканология {}
 link ENG_NOUN:VULCANOLOGIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вулканолог {}
 link ENG_NOUN:VOYEURISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вуайеризм {}
 link ENG_NOUN:VOYAGEUR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:путешественник {}
 link ENG_NOUN:VOYAGE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:путешествие {}
 link ENG_NOUN:VOLUNTARYISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:волюнтаризм {}
 link ENG_NOUN:VOLUNTARISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:волюнтаризм {}
 link ENG_NOUN:VOLTE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вольт {}
 link ENG_NOUN:VOLTAGE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вольтаж {}
 link ENG_NOUN:VOLATILITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:волатильность {}
 link ENG_NOUN:VODKA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:водка {}
 link ENG_NOUN:VOCODER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вокодер {}
 link ENG_NOUN:VOCALIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вокалист {}
 link ENG_NOUN:VITAMIN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:витамин {}

 link ENG_NOUN:VITALITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:жизненность {}
 link ENG_NOUN:VITALISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:витализм {}
 link ENG_NOUN:VISITOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:визитер {}
 link ENG_NOUN:VISIONARY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:зрение {}
 link ENG_NOUN:VISION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:зрение {}
 link ENG_NOUN:VISCOSE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вискоза {}
 link ENG_NOUN:VISAGE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:визаж {}
 link ENG_NOUN:VIRUS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вирус {}
 link ENG_NOUN:VIRGO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:дева {}
 link ENG_NOUN:VIRGINIA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:девственница {}
 link ENG_NOUN:VIRGINIA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:виргиния {}
 link ENG_NOUN:VIOLIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:скрипач {}
 link ENG_NOUN:VIOLATOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нарушитель {}
 link ENG_NOUN:VINYL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:винил {}
 link ENG_NOUN:VILLA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вилла {}
 link ENG_NOUN:VIKING {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:викинг {}
 link ENG_NOUN:VIEWING {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:просмотр {}
 link ENG_NOUN:VIDEOPHONE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:видеофон {}
 link ENG_NOUN:VIDEO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:видео {}
 link ENG_NOUN:VICTOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:виктор {}
 link ENG_NOUN:VIBRATOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вибратор {}
 link ENG_NOUN:VIBRATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вибрация {}
 link ENG_NOUN:VIBRAPHONE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вибрафон {}
 link ENG_NOUN:VETERAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:витеран {}
 link ENG_NOUN:VERTEX {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вершина {}
 link ENG_NOUN:VETERAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ветеран {}
 link ENG_NOUN:VERSION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:версия {}
 link ENG_NOUN:VERMOUTH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вермут {}
 link ENG_NOUN:VERMICELLI {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вермишель {}
 link ENG_NOUN:VERDICT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вердикт {}
 link ENG_NOUN:VERBALISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вербализм {}
 link ENG_NOUN:VENTILATOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вентилятор {}
 link ENG_NOUN:VENTILATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вентиляция {}
 link ENG_NOUN:VENDOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вендор {}
 link ENG_NOUN:VELOUR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:велюр {}
 link ENG_NOUN:VELOCITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:скорость {}
 link ENG_NOUN:VELOCIPEDE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:велосипед {}
 link ENG_NOUN:VELOCIMETER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:спидометр {}
 link ENG_NOUN:VEHICLE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:транспорт {}
 link ENG_NOUN:VEHICLE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:автомобиль {}
 link ENG_NOUN:VEGA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вега {}
 link ENG_NOUN:VECTOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вектор {}
 link ENG_NOUN:VATMAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ватман {}
 link ENG_NOUN:VASSAL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вассал {}
 link ENG_NOUN:VASELINE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вазелин {}
 link ENG_NOUN:VARNA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:варна {}
 link ENG_NOUN:VARISTOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:варистор {}
 link ENG_NOUN:VARIATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вариация {}
 link ENG_NOUN:VAPOUR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пар {}
 link ENG_NOUN:VAPORISATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:испарение {}
 link ENG_NOUN:VANILLA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ванилла {}
 link ENG_NOUN:VANILLA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ваниль {}
 link ENG_NOUN:VANESSA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ванесса {}
 link ENG_NOUN:VANDALISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вандализм {}
 link ENG_NOUN:VAMPIRISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вампиризм {}
 link ENG_NOUN:VAMPIRE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вампир {}
 link ENG_NOUN:VALVE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:клапан {}
 link ENG_NOUN:VALUATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:оценка {}
 link ENG_NOUN:VALIUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:валиум {}
 link ENG_NOUN:VALIDATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:валидация {}
 link ENG_NOUN:VALIDATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:проверка {}
 link ENG_NOUN:VALERIAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:валериан {}
 link ENG_NOUN:VAGINA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вагина {}
 link ENG_NOUN:VACUUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вакуум {}
 link ENG_NOUN:VACCINE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вакцина {}
 link ENG_NOUN:VACANCY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вакансия {}
 link ENG_NOUN:UZBEK {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:узбек {}
 link ENG_NOUN:UTOPIA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:утопия {}
 link ENG_NOUN:UTILITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:утилита {}
 link ENG_NOUN:UTILITARIANISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:утилитаризм {}
 link ENG_NOUN:UTILITARIAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:утилитарист {}
 link ENG_NOUN:USURPATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:узурпация {}
 link ENG_NOUN:USER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пользователь {}
 link ENG_NOUN:USER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:юзер {}
 link ENG_NOUN:USABILITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:юзабилити {}
 link ENG_NOUN:URUGUAY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:уругвай {}
 link ENG_NOUN:UROLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:урология {}
 link ENG_NOUN:UROLOGIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:уролог {}
 link ENG_NOUN:URINE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:урина {}
 link ENG_NOUN:URINATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:моча {}
 link ENG_NOUN:URETHRA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:уретра {}
 link ENG_NOUN:URDU {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:урду {}
 link ENG_NOUN:URBANISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:урбанизм {}
 link ENG_NOUN:UPANISHAD {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:упанишады {}
 link ENG_NOUN:UNWORKABILITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:неработоспособность {}
 link ENG_NOUN:UNWISDOM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:неумность {}
 link ENG_NOUN:UNTIDINESS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нечистота {}
 link ENG_NOUN:UNSURENESS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:неуверенность {}
 link ENG_NOUN:UNSOUNDNESS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:беззвучие {}
 link ENG_NOUN:UNSOUNDNESS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:беззвучность {}
 link ENG_NOUN:UNREST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:беспорядок {}
 link ENG_NOUN:UNRESPONSIVENESS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:безответственность {}
 link ENG_NOUN:UNRELIABILITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ненадежность {}
 link ENG_NOUN:UNREALITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нереальность {}
 link ENG_NOUN:UNREADABILITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:неготовность {}
 link ENG_NOUN:UNPREPAREDNESS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:неготовность {}
 link ENG_NOUN:UNPREDICTABILITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:непредсказуемость {}
 link ENG_NOUN:UNORTHODOXY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:неортодоксальность {}
 link ENG_NOUN:UNLIKELINESS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:непохожесть {}
 link ENG_NOUN:UNLIKELIHOOD {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:непохожесть {}
 link ENG_NOUN:UNLAWFULNESS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:беззаконие {}
 link ENG_NOUN:UNIVERSALISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:универсализм {}
 link ENG_NOUN:UNITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:юнит {}
 link ENG_NOUN:UNIT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:юнит {}
 link ENG_NOUN:UNIONIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:юнионист {}
 link ENG_NOUN:UNIFORMITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:однородность {}
 link ENG_NOUN:UNIFICATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:унификация {}
 link ENG_NOUN:UNHAPPINESS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:несчастье {}
 link ENG_NOUN:UNHAPPINESS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:несчастливость {}
 link ENG_NOUN:UNFAITHFULNESS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:безверие {}
 link ENG_NOUN:UNFAIRNESS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нечестность {}
 link ENG_NOUN:UNDISCIPLINE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:недисциплинированность {}
 link ENG_NOUN:UNDESIRABILITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нежелательность {}
 link ENG_NOUN:UNDERWEAR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:белье {}
 link ENG_NOUN:UNDERTAKING {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:понимание {}
 link ENG_NOUN:UNDERSTANDING {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:понимание {}
 link ENG_ADVERB:UNDERGROUND {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:подземелье {}
 link ENG_NOUN:UNDERGROUND {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:подземелье {}
 link ENG_NOUN:UNDERFLOW {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:антипереполнение {}
 link ENG_NOUN:UNDERESTIMATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:недооценка {}
 link ENG_NOUN:UNBELIEF {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:невение {}
 link ENG_NOUN:UNBELIEF {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:безверие {}
 link ENG_NOUN:UNAVAILABILITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:недоступность {}
 link ENG_NOUN:UNATTRACTIVENESS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:непритягательность {}
 link ENG_NOUN:UNACCEPTABILITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:неприемлемость {}
 link ENG_NOUN:UMBRA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:амбра {}
 link ENG_NOUN:ULTRASOUND {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ультразвук {}
 link ENG_NOUN:ULTRAMICROSCOPE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ультрамикроскоп {}
 link ENG_NOUN:ULTRACENTRIFUGE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ультрацентрифуга {}
 link ENG_NOUN:ULTIMATUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ультиматум {}
 link ENG_NOUN:UKRAINIAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:украинец {}
 link ENG_NOUN:UKRAINE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:украина {}
 link ENG_NOUN:UGLIFICATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:обезображивание {}
 link ENG_NOUN:UGANDA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:уганда {}
 link ENG_NOUN:UFO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нло {}
 link ENG_NOUN:UFOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:уфология {}
 link ENG_NOUN:TZIGANE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:циган {}
 link ENG_NOUN:TYRANNOSAURUS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тиранозавр {}
 link ENG_NOUN:TYPOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:типология {}
 link ENG_NOUN:TYPOGRAPHY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:типография {}
 link ENG_NOUN:TYPHOON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тайфун {}
 link ENG_NOUN:TWIN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:близнец {}
 link ENG_NOUN:TURTLE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:черепаха {}
 link ENG_NOUN:TUNICA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:туника {}
 link ENG_NOUN:TUNIC {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:туника {}
 link ENG_NOUN:TUNER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тюнер {}
 link ENG_NOUN:TUNDRA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тундра {}
 link ENG_NOUN:TULIP {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тюльпан {}
 link ENG_NOUN:TUESDAY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вторник {}
 link ENG_NOUN:TSUNAMI {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:цунами {}
 link ENG_NOUN:TSAREVICH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:царевич {}
 link ENG_NOUN:TRUST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:доверие {}
 link ENG_NOUN:TRUISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:трюизм {}
 link ENG_NOUN:TROY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:троя {}
 link ENG_NOUN:TROUBADOUR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:трубадур {}
 link ENG_NOUN:TROTSKYISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:троцкизм {}
 link ENG_NOUN:TROPOSPHERE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тропосфера {}
 link ENG_NOUN:TROPOPAUSE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тропопауза {}
 link ENG_NOUN:TROPISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тропизм {}
 link ENG_NOUN:TROOPER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:танкист {}
 link ENG_NOUN:TROMBONIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тромбонист {}
 link ENG_NOUN:TROIKA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тройка {}
 link ENG_NOUN:TROGLODYTE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:троглодит {}
 link ENG_NOUN:TRIVIALITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тривиальность {}
 link ENG_NOUN:TRIUMPH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:триумф {}
 link ENG_NOUN:TRITON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тритон {}
 link ENG_NOUN:TRITIUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тритий {}
 link ENG_NOUN:TRIREME {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:трирема {}
 link ENG_NOUN:TRIPTYCH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:триптих {}
 link ENG_NOUN:TRIPOD {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:триножник {}
 link ENG_NOUN:TRIPLICITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тройственность {}
 link ENG_NOUN:TRIPLICATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:утроение {}
 link ENG_NOUN:TRIPLET {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:триплет {}
 link ENG_NOUN:TRIPLANE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:триплан {}
 link ENG_NOUN:TRIOXIDE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:триоксид {}
 link ENG_NOUN:TRIODE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:триод {}
 link ENG_NOUN:TRIO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:трио {}
 link ENG_NOUN:TRINITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:троица {}
 link ENG_NOUN:TRIMMING {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тримминг {}
 link ENG_NOUN:TRIMMING {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:дрессировка {}
 link ENG_NOUN:TRIMARAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тримаран {}
 link ENG_NOUN:TRILOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:трилогия {}
 link ENG_NOUN:TRILOBITE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:трилобит {}
 link ENG_NOUN:TRILLION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:триллион {}
 link ENG_NOUN:TRIGRAPH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:триграф {}
 link ENG_NOUN:TRIGONOMETRY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тригонометрия {}
 link ENG_NOUN:TRIGGER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:триггер {}
 link ENG_NOUN:TRIDENT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:трезубец {}
 link ENG_NOUN:TRICYCLE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:трицикл {}
 link ENG_NOUN:TRICHOTOMY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:трисекция {}
 link ENG_NOUN:TRICERATOPS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:трицераптор {}
 link ENG_NOUN:TRIBUTE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:дань {}
 link ENG_NOUN:TRIBUTE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:контрибуция {}
 link ENG_NOUN:TRIBUNAL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:трибунал {}
 link ENG_NOUN:TRIBE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:племя {}
 link ENG_NOUN:TRIANGULATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:триангуляция {}
 link ENG_NOUN:TRIANGLE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:треуголник {}
 link ENG_NOUN:TRIAD {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:триада {}
 link ENG_NOUN:TREND {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тренд {}
 link ENG_NOUN:TREND {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тенденция {}
 link ENG_NOUN:TREMOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тремор {}
 link ENG_NOUN:TREMOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:дрожь {}
 link ENG_NOUN:TREMBLER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:трамблер {}
 link ENG_NOUN:TREATY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:соглашение {}
 link ENG_NOUN:TREASURE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:казна {}
 link ENG_NOUN:TREASURY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:казна {}
 link ENG_NOUN:TREASURER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:казначей {}
 link ENG_NOUN:TRAUMA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:травма {}
 link ENG_NOUN:TRAUMATISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:травматизм {}
 link ENG_NOUN:TRATTORIA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:траттория {}
 link ENG_NOUN:TRASH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мусор {}
 link ENG_NOUN:TRAPEZOID {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:трапеция {}
 link ENG_NOUN:TRAPEZIUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:трапеция {}
 link ENG_NOUN:TRAP {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ловушка {}
 link ENG_NOUN:TRANSVESTITE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:трансвестит {}
 link ENG_NOUN:TRANSVESTISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:трансвестизм {}
 link ENG_NOUN:TRANSPUTER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:транспьютер {}
 link ENG_NOUN:TRANSPOSITION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:транспозиция {}
 link ENG_NOUN:TRANSPORTER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:транспортер {}
 link ENG_NOUN:TRANSPORTATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:перевозка {}
 link ENG_NOUN:TRANSPORTATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:транспортировка {}
 link ENG_NOUN:TRANSPORTABILITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:транспортабельность {}
 link ENG_NOUN:TRANSPONDER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:транспондер {}
 link ENG_NOUN:TRANSPLANTATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:трансплантация {}
 link ENG_NOUN:TRANSPARENCY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:прозрачность {}
 link ENG_NOUN:TRANSMUTATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:трансмутация {}
 link ENG_NOUN:TRANSMITTER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:трансмиттер {}
 link ENG_NOUN:TRANSLITERATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:транслитерация {}
 link ENG_NOUN:TRANSLATOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:транслятор {}
 link ENG_NOUN:TRANSLATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:трансляция {}
 link ENG_NOUN:TRANSITIVITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:транзитивность {}
 link ENG_NOUN:TRANSISTOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:транзистор {}
 link ENG_NOUN:TRANSFORMER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:трансформер {}
 link ENG_NOUN:TRANSFORMATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:трансформация {}
 link ENG_NOUN:TRANSFER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:трансфер {}
 link ENG_NOUN:TRANSCRIPTION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:транскрипция {}
 link ENG_NOUN:TRANSCENDENTALISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:трансконтинентализм {}
 link ENG_NOUN:TRANSCEIVER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:трансивер {}
 link ENG_NOUN:TRANSACTION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:транзакция {}
 link ENG_NOUN:TRANCHE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:транш {}
 link ENG_NOUN:TRAMWAY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:трамвай {}
 link ENG_NOUN:TRAJECTORY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:траектория {}
 link ENG_NOUN:TRAGICOMEDY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:трагикомедия {}
 link ENG_NOUN:TRAGEDY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:трагедия {}
 link ENG_NOUN:TRAGEDIAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:трагик {}
 link ENG_NOUN:TRAFFIC {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:траффик {}
 link ENG_NOUN:TRAFFIC {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:движение {}
 link ENG_NOUN:TRADITION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:традиция {}
 link ENG_NOUN:TRADITIONALIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:традиционалист {}
 link ENG_NOUN:TRADITIONALISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:традиционализм {}
 link ENG_NOUN:TRADING {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:торговля {}
 link ENG_NOUN:TRADE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:торговля {}
 link ENG_NOUN:TRADESMAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:торговец {}
 link ENG_NOUN:TRADER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:трейдер {}
 link ENG_NOUN:TRACING {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:трассировка {}
 link ENG_NOUN:TRACHOMA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:трахома {}
 link ENG_NOUN:TRACHEOTOMY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:трахеотомия {}
 link ENG_NOUN:TRACHEA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:трахея {}
 link ENG_NOUN:TRACEABILITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:отслеживаемость {}
 link ENG_NOUN:TOXIN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:токсин {}
 link ENG_NOUN:TOXIN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:яд {}
 link ENG_NOUN:TOXICOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:токсикология {}
 link ENG_NOUN:TOVARISH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:товарищ {}
 link ENG_NOUN:TOURNIQUET {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:турникет {}
 link ENG_NOUN:TOUR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тур {}
 link ENG_NOUN:TOTEM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тотем {}
 link ENG_NOUN:TOTALIZATOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тотализатор {}
 link ENG_NOUN:TOTALITARIANISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тоталитаризм {}
 link ENG_NOUN:TORUS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тор {}
 link ENG_NOUN:TORPEDO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:торпеда {}
 link ENG_NOUN:TOROID {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тороид {}
 link ENG_NOUN:TORNADO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:торнадо {}
 link ENG_NOUN:TORERO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тореро {}
 link ENG_NOUN:TORCH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:факел {}
 link ENG_NOUN:TORAH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тора {}
 link ENG_NOUN:TOQUILLA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:текилла {}
 link ENG_NOUN:TOPONYM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:топоним {}
 link ENG_NOUN:TOPOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:топология {}
 link ENG_NOUN:TOPOGRAPHY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:топография {}
 link ENG_NOUN:TOPAZ {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:топаз {}

 link ENG_NOUN:TOMMY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:томми {}
 link ENG_NOUN:TOLERANCE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:толерантность {}
 link ENG_NOUN:TOLEDO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:толедо {}
 link ENG_NOUN:TOILET {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:туалет {}
 link ENG_NOUN:TOGO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:того {}
 link ENG_NOUN:TOBAGO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тобаго {}
 link ENG_NOUN:TOASTER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тостер {}
 link ENG_NOUN:TITAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:титан {}
 link ENG_NOUN:TISSUE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ткань {}
 link ENG_NOUN:TIRADE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тирада {}
 link ENG_NOUN:TIPTOE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:цыпочки {}
 link ENG_NOUN:TIMER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:таймер {}
 link ENG_NOUN:TIDE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:прилив {}
 link ENG_NOUN:TIDE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:отлив {}
 link ENG_NOUN:THURSDAY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:четверг {}
 link ENG_NOUN:THORIUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:торий {}
 link ENG_NOUN:THING {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вещь {}
 link ENG_NOUN:THETA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тета {}
 link ENG_NOUN:THESAURUS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тезаурус {}
 link ENG_NOUN:THERMOSTAT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:термостат {}
 link ENG_NOUN:THERMOMETER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:термометр {}
 link ENG_NOUN:THERMOGRAPH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:термограф {}
 link ENG_NOUN:THERMOGRAPHY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:термография {}
 link ENG_NOUN:THERMOGRAM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:термограмма {}
 link ENG_NOUN:THERMODYNAMIC {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:термодинамика {}
 link ENG_NOUN:THERMOCOUPLE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:термопара {}
 link ENG_NOUN:THERAPY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:терапия {}
 link ENG_NOUN:THEOSOPHY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:теософия {}
 link ENG_NOUN:THEORETICIAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:теоретик {}
 link ENG_NOUN:THEOREM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:теорема {}
 link ENG_NOUN:THEOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:теология {}
 link ENG_NOUN:THEOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:богословие {}
 link FR_NOUN:THEOLOGIE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:теология {}
 link ENG_NOUN:THEOLOGIAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:богослов {}
 link ENG_NOUN:THEOLOGIAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:теолог {}
 link ENG_NOUN:THEODOLITE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:теодолит {}
 link ENG_NOUN:THEOCRACY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:теократия {}
 link ENG_NOUN:THEME {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тема {}
 link ENG_NOUN:THEISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:теизм {}
 link ENG_NOUN:THEATER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:театр {}
 link ENG_NOUN:THANKSGIVING {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:благодарение {}
 link ENG_NOUN:THANATOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:танатология {}
 link ENG_NOUN:THALLIUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:таллий {}
 link ENG_NOUN:THALIDOMIDE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:талидомид {}
 link ENG_NOUN:TEXTUALIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:текстуалист {}
 link ENG_NOUN:TETRODE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тетрод {}
 link ENG_NOUN:TETRARCH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тетрарх {}
 link ENG_NOUN:TETRAPOD {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:четырехножник {}
 link ENG_NOUN:TETRALOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тетралогия {}
 link ENG_NOUN:TETRAGRAM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тетраграмма {}
 link ENG_NOUN:TETRAGRAMMATON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тетраграмматон {}
 link ENG_NOUN:TETRAGRAMMATON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:четырехугольник {}
 link ENG_NOUN:TETRAGON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:четырехугольник {}
 link ENG_NOUN:TEST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тест {}
 link ENG_NOUN:TESTICLE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:яичко {}
 link ENG_NOUN:TESTAMENT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:завет {}
 link ENG_NOUN:TESTABILITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:проверяемость {}
 link ENG_NOUN:TESLA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тесла {}
 link ENG_NOUN:TERRORIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:террорист {}
 link ENG_NOUN:TERRARIUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:террариум {}
 link ENG_NOUN:TERRACOTTA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:терракот {}
 link ENG_NOUN:TERRACE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:терраса {}
 link ENG_NOUN:TERMITE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:термит {}
 link ENG_NOUN:TERMINOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:терминология {}
 link ENG_NOUN:TERMINATOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:терминатор {}
 link ENG_NOUN:TERMINATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:уничтожение {}
 link ENG_NOUN:TERMINAL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:терминал {}

 link ENG_NOUN:TERBIUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тербий {}
 link ENG_NOUN:TEQUILA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:текила {}
 link ENG_NOUN:TEOCALLI {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:теокали {}
 link ENG_NOUN:TENSOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тензор {}
 link ENG_NOUN:TENSION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:натяжение {}
 link ENG_NOUN:TEMPORALITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:временность {}
 link ENG_NOUN:TEMPERAMENT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:темперамент {}
 link ENG_NOUN:TELPHER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тельфер {}
 link ENG_NOUN:TELETYPE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:телетайп {}
 link ENG_NOUN:TELETEXT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:телетекст {}
 link ENG_NOUN:TELESCOPE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:телескоп {}
 link ENG_NOUN:TELEPHONY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:телефония {}
 link ENG_NOUN:TELEPHONIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:телефонист {}
 link ENG_NOUN:TELEPATHY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:телепатия {}
 link ENG_NOUN:TELEOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:телеология {}
 link ENG_NOUN:TELEMETRY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:телеметрия {}
 link ENG_NOUN:TELEKINESIS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:телекинез {}
 link ENG_NOUN:TELEGRAPHIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:телеграфист {}
 link ENG_NOUN:TELEGRAM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:телеграма {}
 link ENG_NOUN:TELEFILM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:телефильм {}
 link ENG_NOUN:TELEFAX {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:телефакс {}
 link ENG_NOUN:TELECAMERA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:телекамера {}
 link ENG_NOUN:TEFLON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:телефлон {}
 link ENG_NOUN:TEENAGER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тинейджер {}
 link ENG_NOUN:TEENAGER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:подросток {}
 link ENG_NOUN:TEDDY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тэдди {}
 link ENG_NOUN:TECHNOPHOBIA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:технофобия {}
 link ENG_NOUN:TECHNOPHILE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:технофил {}
 link ENG_NOUN:TECHNOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:технология {}
 link ENG_NOUN:TECHNOLOGIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:технолог {}
 link ENG_NOUN:TECHNOCRAT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:технократ {}
 link ENG_NOUN:TECHNOCRACY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:технократия {}
 link ENG_NOUN:TECHNICIAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:техник {}
 link ENG_NOUN:TECHNICALITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:техничность {}
 link ENG_NOUN:TECHNETIUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:технеций {}
 link ENG_NOUN:TEASPOON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ложка {}
 link ENG_NOUN:TEAPOT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:чайник {}
 link ENG_NOUN:TEACHER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:учитель {}
 link ENG_NOUN:TAX {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:налог {}
 link ENG_NOUN:TAXPAYER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:налогоплательщик {}
 link ENG_NOUN:TAXON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:таксон {}
 link ENG_NOUN:TAXONOMY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:таксономия {}
 link ENG_NOUN:TAXONOMIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:таксономист {}
 link ENG_NOUN:TAXIDERMY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:таксидермия {}
 link ENG_NOUN:TAXIDERMIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:таксидермист {}
 link ENG_NOUN:TAXATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:налогообложение {}
 link ENG_NOUN:TAVERN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:таверна {}
 link ENG_NOUN:TAVERNA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:таверна {}
 link ENG_NOUN:TAUTOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тавтология {}
 link ENG_NOUN:TARZAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тарзан {}
 link ENG_NOUN:TARTAR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тартар {}
 link ENG_NOUN:TARANTELLA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тарантелла {}
 link ENG_NOUN:TAR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:смола {}
 link ENG_NOUN:TAPIR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тапир {}
 link ENG_NOUN:TAPIOCA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тапиока {}
 link ENG_NOUN:TANTALUS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тантал {}
 link ENG_NOUN:TANTALUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тантал {}
 link ENG_NOUN:TANKER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:танкер {}
 link ENG_NOUN:TAMPON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тампон {}
 link ENG_NOUN:TAMPONAGE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тампонаж {}
 link ENG_NOUN:TAMBOUR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тамбур {}
 link ENG_NOUN:TAMBOURIN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тамбурин {}
 link ENG_NOUN:TALMUD {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:талмуд {}
 link ENG_NOUN:TALISMAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:талисман {}
 link ENG_NOUN:TALION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:талион {}
 link ENG_NOUN:TAIWAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тайвань {}
 link ENG_NOUN:TABOURET {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:табурет {}
 link ENG_NOUN:TABLOID {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:таблоид {}

 link ENG_NOUN:TABLEAU {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:табло {}
 link ENG_NOUN:SYRIAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сириец {}
 link ENG_NOUN:SYNTHESIS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:синтез {}
 link ENG_NOUN:SYNTAX {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:синтакс {}
 link ENG_NOUN:SYNOPTIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:синоптик {}
 link ENG_NOUN:SYNOPSIS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:прогноз {}
 link ENG_NOUN:SYNONYM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:синоним {}
 link ENG_NOUN:SYNERGISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:синергизм {}
 link ENG_NOUN:SYNDROME {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:синдром {}
 link ENG_NOUN:SYNDICATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:синдикация {}
 link ENG_NOUN:SYNDICATE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:синдикат {}
 link ENG_NOUN:SYNDICALIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:синдикалист {}
 link ENG_NOUN:SYNDICALISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:синдикализм {}
 link ENG_NOUN:SYNCHRONISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:синхронизм {}
 link ENG_NOUN:SYNCHRONICITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:синхронность {}
 link ENG_NOUN:SYNAPSIS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:синапс {}
 link ENG_NOUN:SYNAGOGUE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:синагога {}
 link ENG_NOUN:SYNAGOGUE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:синагога {}
 link ENG_NOUN:SYMPTOM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:симптом {}
 link ENG_NOUN:SYMPOSIUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:симпозиум {}
 link ENG_NOUN:SYMPATHY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:симпатия {}
 link ENG_NOUN:SYMMETRY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:симметрия {}
 link ENG_NOUN:SYMBOLIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:символист {}
 link ENG_NOUN:SYMBOL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:символ {}
 link ENG_NOUN:SYMBOLISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:символизм {}
 link ENG_NOUN:SYMBIONT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:симбионт {}
 link ENG_NOUN:SYLLOGISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:силлогизм {}
 link ENG_NOUN:SYLLABLE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:слог {}
 link ENG_NOUN:SWORD {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:меч {}
 link ENG_VERB:SWING {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:свинг {}
 link ENG_NOUN:SWEATER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:свитер {}
 link ENG_NOUN:SWASTIKA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:свастика {}
 link ENG_NOUN:SWAHILI {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:суахили {}
 link ENG_NOUN:SUSSEX {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сассекс {}
 link ENG_NOUN:SUSHI {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:суши {}
 link ENG_NOUN:SURVEYOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:обозреватель {}
 link ENG_NOUN:SURREALISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сюрреализм {}
 link ENG_NOUN:SURGERY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:хирургия {}
 link ENG_NOUN:SUPPOSITION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:предположение {}
 link ENG_NOUN:SUPPLIER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:поставщик {}
 link ENG_NOUN:SUPINATOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:супинатор {}
 link ENG_NOUN:SUPERVISOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:надсмотрщик {}
 link ENG_NOUN:SUPERTANKER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:супертанкер {}
 link ENG_NOUN:SUPERPOSITION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:суперпозиция {}
 link ENG_NOUN:SUPERPHOSPHATE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:суперфосфат {}
 link ENG_NOUN:SUPERNOVA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сверхновая {}
 link ENG_NOUN:SUPERMODEL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:супермодель {}
 link ENG_NOUN:SUPERMARKET {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:супермаркет {}
 link ENG_NOUN:SUPERHERO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сверхгерой {}
 link ENG_NOUN:SUPERGIANT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сверхгигант {}
 link ENG_NOUN:SUPERFAMILY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сверхсемья {}
 link ENG_NOUN:SUPERCONDUCTOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сверхпроводник {}
 link ENG_NOUN:SUPERCOMPUTER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:суперкомпьютер {}
 link ENG_NOUN:SUPERCLASS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:суперкласс {}
 link ENG_NOUN:SUNLIGHT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:свет {}
 link ENG_NOUN:SUNFLOWER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:подсолнух {}
 link ENG_NOUN:SUNDOWN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:закат {}
 link ENG_NOUN:SUMO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сумо {}
 link ENG_NOUN:SUMMIT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:саммит {}
 link ENG_NOUN:SUMMATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сложение {}
 link ENG_NOUN:SUMMA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сумма {}
 link ENG_NOUN:SULTAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:султан {}
 link ENG_NOUN:SULPHITE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сулфит {}
 link ENG_NOUN:SULPHIDE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сулфид {}
 link ENG_NOUN:SULPHATE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сулфат {}
 link ENG_NOUN:SUICIDE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:суицид {}
 link ENG_NOUN:SUFFIX {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:суфикс {}
 link ENG_NOUN:SUFFICIENCY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:достаточность {}
 link ENG_NOUN:SUDDENNESS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:неожиданность {}
 link ENG_NOUN:SUCCESS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:успех {}
 link ENG_NOUN:SUBWAY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:подземка {}
 link ENG_NOUN:SUBVENTION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:субвенция {}
 link ENG_NOUN:SUBTROPIC {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:субтропик {}
 link ENG_NOUN:SUBSYSTEM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:подсистема {}
 link ENG_NOUN:SUBSTRATUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:субстрат {}
 link ENG_NOUN:SUBSTRATE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:субстрат {}
 link ENG_NOUN:SUBSTATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:подстанция {}
 link ENG_NOUN:SUBSECTION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:подсекция {}
 link ENG_NOUN:SUBSCRIBER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:подписчик {}
 link ENG_NOUN:SUBROUTINE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:подпрограмма {}
 link ENG_NOUN:SUBREGION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:субрегион {}
 link ENG_NOUN:SUBORDINATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:субординация {}
 link ENG_NOUN:SUBMARINE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:подлодка {}
 link ENG_NOUN:SUBLIMATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сублимация {}
 link ENG_NOUN:SUBJECT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:субъект {}
 link ENG_NOUN:SUBJECTIVITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:субъективность {}
 link ENG_NOUN:SUBJECTIVIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:субъективист {}
 link ENG_NOUN:SUBJECTIVISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:субъективизм {}
 link ENG_NOUN:SUBDIVISION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:подразделение {}
 link ENG_NOUN:SUBCULTURE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:субкультура {}
 link ENG_NOUN:SUBCONTINENT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:субконтинент {}
 link ENG_NOUN:SUBCOMMITTEE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:подкомитет {}
 link ENG_NOUN:SUBCLASS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:подкласс {}

 link ENG_NOUN:SUBCATEGORY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:подкатегория {}
 link ENG_NOUN:STYLO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:стило {}
 link ENG_NOUN:STYLIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:стилист {}
 link ENG_NOUN:STYLET {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:стилет {}
 link ENG_NOUN:STUPOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ступор {}
 link ENG_NOUN:STUPIDITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тупость {}
 link ENG_NOUN:STUDIO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:студия {}
 link ENG_NOUN:STRONTIUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:стронций {}
 link ENG_NOUN:STROBOSCOPE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:стробоскоп {}
 link ENG_NOUN:STRING {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:строка {}
 link ENG_NOUN:STRIKEBREAKER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:штрейхбрекер {}
 link ENG_NOUN:STRESS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:стресс {}
 link ENG_NOUN:STRATEGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:стратегия {}
 link ENG_NOUN:STRATEGIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:стратег {}
 link ENG_NOUN:STORAGE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:хранилище {}
 link ENG_NOUN:STOMATOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:стоматология {}
 link ENG_NOUN:STOICISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:стоицизм {}
 link ENG_NOUN:STIPULATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:стипуляция {}
 link ENG_NOUN:STIMULATOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:стимулятор {}
 link ENG_NOUN:STIMULATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:стимуляция {}
 link ENG_NOUN:STEROID {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:стероид {}
 link ENG_NOUN:STERILITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:стерильность {}
 link ENG_NOUN:STEREOTYPE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:стереотип {}
 link ENG_NOUN:STEREOMETRY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:стереометрия {}
 link ENG_NOUN:STEREOGRAPHY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:стереграфия {}
 link ENG_NOUN:STERADIAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:стерадиан {}
 link ENG_NOUN:STENOGRAPHY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:стенография {}
 link ENG_NOUN:STENOGRAPHER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:стенографист {}
 link ENG_NOUN:STEARIN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:стеарин {}
 link ENG_NOUN:STEAMSHIP {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пароход {}
 link ENG_NOUN:STEALTH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:невидимка {}
 link ENG_NOUN:STATUS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:статус {}
 link ENG_NOUN:STATUETTE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:статуэтка {}
 link ENG_NOUN:STATOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:статор {}
 link ENG_NOUN:STANDARD {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:стандарт {}
 link ENG_NOUN:STALACTITE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сталактит {}
 link ENG_NOUN:STAIR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ступень {}
 link ENG_NOUN:STAIRWAY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лестница {}
 link ENG_NOUN:STAGNATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:стагнация {}
 link ENG_NOUN:STAGFLATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:стагфляция {}
 link ENG_ADVERB:STACCATO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:стаккато {}
 link ENG_NOUN:STABILITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:стабильность {}
 link ENG_NOUN:SRI LANKA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:шри ланка {}
 link ENG_NOUN:SPYGLASS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лупа {}
 link ENG_NOUN:SPUTNIK {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:спутник {}
 link ENG_NOUN:SPRINGTIME {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:весна {}

 link ENG_NOUN:SPRAY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:спрей {}
 link ENG_NOUN:SPORT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:спорт {}
 link ENG_NOUN:SPORTSMAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:спортсмен {}
 link ENG_NOUN:SPONSOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:спонсор {}
 link ENG_NOUN:SPOILER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:спойлер {}
 link ENG_NOUN:SPIDER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:паук {}
 link ENG_NOUN:SPHEROID {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сфероид {}
 link ENG_NOUN:SPHAGNUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сфагнум {}
 link ENG_NOUN:SPERM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сперма {}
 link ENG_NOUN:SPERMATOZOID {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сперматозоид {}
 link ENG_NOUN:SPELL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:заклинание {}
 link ENG_NOUN:SPELEOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:спелеология {}
 link ENG_NOUN:SPECTRUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:спектр {}
 link ENG_NOUN:SPECTROSCOPY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:спектроскопия {}
 link ENG_NOUN:SPECTROSCOPE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:спектроскоп {}
 link ENG_NOUN:SPECTROPHOTOMETRY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:спектрофотометрия {}
 link ENG_NOUN:SPECTROPHOTOMETER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:спектрофотометр {}
 link ENG_NOUN:SPECTROMETRY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:спектрометрия {}
 link ENG_NOUN:SPECTROMETER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:спектрометр {}
 link ENG_NOUN:SPECTROGRAPH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:спектрограф {}
 link ENG_NOUN:SPECTROGRAM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:спектрограма {}
 link ENG_NOUN:SPECIFICATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:спецификация {}
 link ENG_NOUN:SPECIALITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:специальность {}
 link ENG_NOUN:SPECIALIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:специалист {}
 link ENG_NOUN:SPEARMAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:копьеносец {}
 link ENG_NOUN:SPEARHEAD {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:наконечник {}
 link ENG_NOUN:SPASM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:спазм {}
 link ENG_NOUN:SPAM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:спам {}
 link ENG_NOUN:SPAGHETTI {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:спагетти {}
 link ENG_NOUN:SOUNDTRACK {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:саундтрек {}
 link ENG_NOUN:SOUNDNESS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:звучность {}
 link ENG_NOUN:SOPRANO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сопрано {}
 link ENG_NOUN:SOPHISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:софизм {}
 link ENG_NOUN:SONATA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:соната {}
 link ENG_NOUN:SONAR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сонар {}
 link ENG_NOUN:SOMNAMBULISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сомнамбулизм {}
 link ENG_NOUN:SOMNAMBULIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сомнамбула {}
 link ENG_NOUN:SOMBRERO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сомбреро {}
 link ENG_NOUN:SOLFEGGIO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сольфеджио {}
 link ENG_NOUN:SOLECISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:солицизм {}
 link ENG_NOUN:SOFTWARE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:программа {}
 link ENG_NOUN:SODOM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:содом {}
 link ENG_NOUN:SODOMY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:содомия {}
 link ENG_NOUN:SOCIOMETRY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:социометрия {}
 link ENG_NOUN:SOCIOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:социология {}
 link ENG_NOUN:SOCIOLOGIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:социолог {}
 link ENG_NOUN:SOCIOLINGUIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:социолингвист {}
 link ENG_NOUN:SOCIOBIOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:социобиология {}
 link ENG_NOUN:SOCIALIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:социалист {}
 link ENG_NOUN:SOCIALISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:социализм {}
 link ENG_NOUN:SOAP {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мыло {}
 link ENG_NOUN:SNOWSTORM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вьюга {}
 link ENG_NOUN:SNOWSTORM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:буря {}
 link ENG_NOUN:SNOWMAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:снеговик {}
 link ENG_NOUN:SNOWFLAKE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:снежинка {}
 link ENG_NOUN:SNOWFALL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:снегопад {}
 link ENG_NOUN:SNOWBALL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:снежок {}
 link ENG_NOUN:SMELL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:запах {}

 link ENG_NOUN:SLOVEN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:словенец {}
 link ENG_NOUN:SLEEPWALKER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лунатик {}
 link ENG_NOUN:SLAVE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:славянин {}
 link ENG_NOUN:SLANG {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:слэнг {}
 link ENG_NOUN:SKINHEAD {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:скинхед {}
 link ENG_NOUN:SKETCH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:скетч {}
 link ENG_NOUN:SKELETON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:скелет {}
 link ENG_NOUN:SISTERHOOD {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сестринство {}
 link ENG_NOUN:SIREN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сирена {}
 link ENG_NOUN:SIPHON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сифон {}
 link ENG_NOUN:SINUSOID {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:синусоида {}
 link ENG_NOUN:SINUS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:синус {}
 link ENG_NOUN:SINGULARITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сингулярность {}
 link ENG_NOUN:SINGLETON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:одиночка {}
 link ENG_NOUN:SINFULNESS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:греховность {}
 link ENG_NOUN:SINECURE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:синекура {}
 link ENG_NOUN:SINE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:синус {}
 link ENG_NOUN:SIMULATOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:симулятор {}
 link ENG_NOUN:SIMULATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:симуляция {}
 link ENG_NOUN:SIMULATOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:имитация {}
 link ENG_NOUN:SIMULATOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:имитатор {}
 link ENG_NOUN:SIMULATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:имитация {}
 link ENG_NOUN:SIMPLIFICATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:упрощение {}
 link ENG_NOUN:SIMPLICITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:простота {}
 link ENG_NOUN:SIMILARITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:похожесть {}
 link ENG_NOUN:SILVER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:серебро {}
 link ENG_NOUN:SILK {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:шелк {}
 link ENG_NOUN:SILICONE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:силикон {}
 link ENG_NOUN:SILICON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:силикон {}
 link ENG_NOUN:SILHOUETTE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:силует {}
 link ENG_NOUN:SILENCE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тишина {}
 link ENG_NOUN:SIGNORINA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:синьорина {}
 link ENG_NOUN:SIGNOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:синьор {}
 link ENG_NOUN:SIGNIFICANCE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:значимость {}
 link ENG_NOUN:SIGNATURE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сигнатура {}
 link ENG_NOUN:SIGMA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сигма {}
 link ENG_NOUN:SIESTA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сиеста {}
 link ENG_NOUN:SIERRA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сьерра {}
 link ENG_NOUN:SIERRA LEONE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сьерра леоне {}
 link ENG_NOUN:SIEMENS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сименс {}
 link ENG_NOUN:SHUTTLE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:челнок {}
 link ENG_NOUN:SHUTDOWN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:заглушение {}
 link ENG_NOUN:SHOWMAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:шоумен {}
 link ENG_NOUN:SHOP {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:магазин {}
 link ENG_NOUN:SHOPPING {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:шоппинг {}
 link ENG_NOUN:SHOEMAKER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сапожник {}
 link ENG_NOUN:SHOCK {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:шок {}
 link ENG_NOUN:SHIPOWNER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:судовладелец {}
 link ENG_NOUN:SHERIFF {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:шериф {}
 link ENG_NOUN:SHERATON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:шератон {}
 link ENG_NOUN:SHELTER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:укрытие {}
 link ENG_NOUN:SHEIKH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:шейх {}
 link ENG_NOUN:SHAVING {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:бритье {}
 link ENG_NOUN:SHAVER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:бритва {}
 link ENG_NOUN:SHAREHOLDING {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:акционер {}
 link ENG_NOUN:SHAREHOLDER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:акционер {}
 link ENG_NOUN:SHAMPOO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:шампунь {}
 link ENG_NOUN:SHAMELESSNESS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:бесстыдство {}
 link ENG_NOUN:SHAMAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:шаман {}
 link ENG_NOUN:SEX {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:секс {}
 link ENG_NOUN:SEXUALITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сексуальность {}
 link ENG_NOUN:SEXTANT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:секстант {}
 link ENG_NOUN:SEXPLOITATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сексплуатация {}
 link ENG_NOUN:SEXOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сексология {}
 link ENG_NOUN:SEXOLOGIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сексолог {}
 link ENG_NOUN:SEXISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сексизм {}
 link ENG_NOUN:SESSION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сессия {}
 link ENG_NOUN:SERVITUDE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сервитут {}
 link ENG_NOUN:SERVICEABILITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:обслуживаемость {}
 link ENG_NOUN:SERVER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сервер {}
 link ENG_NOUN:SERPENT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:змея {}
 link ENG_NOUN:SEROTINE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:серотин {}
 link ENG_NOUN:SERJEANT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сержант {}
 link ENG_NOUN:SERB {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:серб {}
 link ENG_NOUN:SEQUOIA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:секвойя {}
 link ENG_NOUN:SEQUESTRUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:секвестр {}
 link ENG_NOUN:SEQUEL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сиквел {}
 link ENG_NOUN:SEPSIS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сепсис {}
 link ENG_NOUN:SEPARATOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сепаратор {}
 link ENG_NOUN:SEPARATIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сепаратист {}
 link ENG_NOUN:SEPARATISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сепаратизм {}
 link ENG_NOUN:SEPARATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сепарация {}
 link ENG_NOUN:SEPARATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:отделение {}
 link ENG_NOUN:SEPARABILITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:разделимость {}
 link ENG_NOUN:SENSOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сенсор {}
 link ENG_NOUN:SENSITIVENESS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:чувствительность {}
 link ENG_NOUN:SENSIBILITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:чувствительность {}
 link ENG_NOUN:SENIOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сеньор {}
 link ENG_NOUN:SENHOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сеньор {}
 link ENG_NOUN:SENHORITA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сеньорита {}
 link ENG_NOUN:SENHORA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сеньора {}
 link ENG_NOUN:SENATOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сенатор {}
 link ENG_NOUN:SENATE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сенат {}
 link ENG_NOUN:SEMIOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:семиология {}
 link ENG_NOUN:SEMINAR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:семинар {}
 link ENG_NOUN:SEMIFINAL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:полуфинал {}
 link ENG_NOUN:SEMIDIAMETER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:полудиаметр {}
 link ENG_NOUN:SEMICYLINDER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:полуцилиндр {}
 link ENG_NOUN:SEMICONDUCTOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:полупроводник {}
 link ENG_NOUN:SEMESTER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:семестр {}
 link ENG_NOUN:SEMANTICS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:семантика {}
 link ENG_NOUN:SEMANTEME {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:семантема {}
 link ENG_NOUN:SELLER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:продавец {}
 link ENG_NOUN:SELENOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:селенология {}
 link ENG_NOUN:SELENOGRAPHY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:селенография {}

 link ENG_NOUN:SELECTOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:селектор {}
 link ENG_NOUN:SELECTIVITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:выборочность {}
 link ENG_NOUN:SELECTION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:выбор {}
 link ENG_NOUN:SELECTION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:селекция {}
 link ENG_NOUN:SEISMOMETER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сейсмометр {}
 link ENG_NOUN:SEISMOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сейсмология {}
 link ENG_NOUN:SEISMOLOGIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сейсмолог {}
 link ENG_NOUN:SEISMOGRAPH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сейсмограф {}
 link ENG_NOUN:SEISMOGRAM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сейсмограма {}
 link ENG_NOUN:SEIGNEUR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:барин {}
 link ENG_NOUN:SEGREGATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сегрегация {}
 link ENG_NOUN:SEGMENT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сегмент {}
 link ENG_NOUN:SEGMENTATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сегментация {}
 link ENG_NOUN:SECURITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:безопасность {}
 link ENG_NOUN:SECTOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сектор {}
 link ENG_NOUN:SECTION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:секция {}
 link ENG_NOUN:SECRETARIAT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:секретариат {}
 link ENG_NOUN:SEATING {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сиденье {}
 link ENG_NOUN:SEASONALITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сезонность {}
 link ENG_NOUN:SEASHORE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:побережье {}
 link ENG_VERB:SEAL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:печать {}
 link ENG_NOUN:SCRUBBER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:скраббер {}
 link ENG_NOUN:SCREWDRIVER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:отвертка {}
 link ENG_NOUN:SCOUTER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:скутер {}
 link ENG_NOUN:SCORPION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:скорпион {}
 link ENG_NOUN:SCORE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:счет {}
 link ENG_NOUN:SCLEROSIS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:склероз {}
 link ENG_NOUN:SCINTILLATOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сцинтиллятор {}
 link ENG_NOUN:SCINTILLATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сцинтилляция {}
 link ENG_NOUN:SCIENTOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сайентология {}
 link ENG_NOUN:SCHOOLROOM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:класс {}
 link ENG_NOUN:SCHOOLMISTRESS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:учительница {}
 link ENG_NOUN:SCHOOLGIRL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:школьница {}
 link ENG_NOUN:SCHOOLCHILD {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:школьник {}
 link ENG_NOUN:SCHIZOPHRENIA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:шизофрения {}
 link ENG_NOUN:SCEPSIS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:скепсис {}
 link ENG_NOUN:SCENE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сцена {}
 link ENG_NOUN:SCENARIO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сценарий {}
 link ENG_NOUN:SCENA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сцена {}
 link ENG_NOUN:SCANNER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сканер {}
 link ENG_NOUN:SCANDAL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:скандал {}
 link ENG_NOUN:SCALP {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:скальп {}
 link ENG_NOUN:SAXOPHONIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:саксофонист {}
 link ENG_NOUN:SAXONY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:саксония {}
 link ENG_NOUN:SAVOY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:савой {}
 link ENG_NOUN:SAVANNAH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:саванна {}
 link ENG_NOUN:SAUNA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сауна {}
 link ENG_NOUN:SATURN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сатурн {}
 link ENG_NOUN:SATURDAY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:суббота {}
 link ENG_NOUN:SATRAP {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сатрап {}
 link ENG_NOUN:SATISFACTION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:удовлетворение {}
 link ENG_NOUN:SATANIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сатанист {}
 link ENG_NOUN:SATANISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сатанизм {}
 link ENG_NOUN:SARCASM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сарказм {}
 link ENG_NOUN:SARCOMA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:саркома {}
 link ENG_NOUN:SAPROPHYTE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сапрофит {}
 link ENG_NOUN:SANDBOX {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:песочница {}
 link ENG_NOUN:SAN MARINO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сан марино {}
 link ENG_NOUN:SAMOVAR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:самовар {}
 link ENG_NOUN:SAMOSA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:самоса {}
 link ENG_NOUN:SAMOA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:самоа {}
 link ENG_NOUN:SAMBO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:самбо {}
 link ENG_NOUN:SAMARA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:самара {}
 link ENG_NOUN:SALVATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:спасение {}
 link ENG_NOUN:SALVADOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сальвадор {}
 link ENG_NOUN:SALMONELLA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сальмонелла {}
 link ENG_NOUN:SALARY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:зарплата {}
 link ENG_NOUN:SALAMANDER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:саламандра {}
 link ENG_NOUN:SAGA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сага {}
 link ENG_NOUN:SAFARI {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сафари {}
 link ENG_NOUN:SADOMASOCHISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:садомазохизм {}
 link ENG_NOUN:SABOTAGE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:саботаж {}
 link ENG_NOUN:SABAOTH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:саваоф {}
 link ENG_NOUN:RWANDA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:руанда {}
 link ENG_NOUN:RUPIAH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:рупия {}
 link ENG_NOUN:RUNE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:руна {}
 link ENG_NOUN:RUMOUR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:слух {}
 link ENG_NOUN:RUMOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:слух {}
 link ENG_NOUN:RULER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:линейка {}
 link ENG_NOUN:RUGBY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:регби {}
 link ENG_NOUN:RUBIDIUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:рубидий {}
 link ENG_NOUN:RUBBLE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:рубль {}
 link ENG_NOUN:ROYALIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:роялист {}
 link ENG_NOUN:ROUNDABOUT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:округление {}
 link ENG_NOUN:ROULETTE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:рулет {}
 link ENG_NOUN:ROTTWEILER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ротвейлер {}
 link ENG_NOUN:ROTOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ротор {}
 link ENG_NOUN:ROTATOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ротатор {}
 link ENG_NOUN:ROTATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вращение {}
 link ENG_NOUN:ROSEMARY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:розмари {}
 link ENG_NOUN:ROSARY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:розарий {}
 link ENG_NOUN:ROSARIUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:розарий {}
 link ENG_NOUN:RONDO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:рондо {}
 link ENG_NOUN:ROMEO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ромео {}
 link ENG_NOUN:ROASTER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ростер {}
 link ENG_NOUN:ROADSTER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:родстер {}
 link ENG_NOUN:RIVIERA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ривьера {}
 link ENG_NOUN:RITUAL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ритуал {}
 link ENG_NOUN:RISOTTO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ризотто {}
 link ENG_NOUN:RIDER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:наездник {}
 link ENG_NOUN:RICOCHET {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:рикошет {}
 link ENG_NOUN:RHODOPSIN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:родопсин {}
 link ENG_NOUN:RHODIUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:родий {}
 link ENG_NOUN:RHEUMATISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ревматизм {}
 link ENG_NOUN:RHEOSTAT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:реостат {}
 link ENG_NOUN:RHENIUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:рений {}
 link ENG_NOUN:RHAPSODY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:рапсодия {}
 link ENG_NOUN:REVOLVER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:револьвер {}
 link ENG_NOUN:REVOLUTION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:революция {}
 link ENG_NOUN:REVISION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ревизия {}
 link ENG_NOUN:REVISION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пересмотр {}
 link ENG_NOUN:REVISIONIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ревизионист {}
 link ENG_NOUN:REVISIONIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ревизионизм {}
 link ENG_NOUN:REVISIONISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ревизионизм {}
 link ENG_NOUN:REVANCHIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:реваншист {}
 link ENG_NOUN:REVANCHISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:реваншизм {}
 link ENG_NOUN:RETROVIRUS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ретровирус {}
 link ENG_NOUN:RETROSPECTION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ретроспекция {}
 link ENG_NOUN:RETRIEVER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ретривер {}
 link ENG_NOUN:RETINA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ретина {}
 link ENG_NOUN:RETICULATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ретикуляция {}
 link ENG_NOUN:RESTITUTION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:реституция {}
 link ENG_NOUN:RESPONSIBILITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ответственность {}
 link ENG_NOUN:RESPONSE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:отклик {}
 link ENG_NOUN:RESPONDENT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:респондент {}
 link ENG_NOUN:RESPIRATOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:респиратор {}
 link ENG_NOUN:RESOURCE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ресурс {}
 link ENG_NOUN:RESONATOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:резонатор {}
 link ENG_NOUN:RESONANCE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:резонанс {}
 link ENG_NOUN:RESISTOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:резистор {}
 link ENG_NOUN:RESISTANCE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сопротивление {}
 link ENG_NOUN:RESIDENCE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:резиденция {}
 link ENG_NOUN:RESERVOIR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:резервуар {}
 link ENG_NOUN:RESERVIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:резервист {}
 link ENG_NOUN:RESERVATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:резервация {}
 link ENG_NOUN:RESEARCHER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:исследователь {}

 link ENG_NOUN:RESEARCH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:исследование {}
 link ENG_NOUN:RESCUE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:спасение {}
 link ENG_NOUN:REQUISITE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:реквизит {}
 link ENG_NOUN:REQUIREMENT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:требование {}
 link ENG_NOUN:REQUIEM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:реквием {}
 link ENG_NOUN:REPUBLICAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:республиканец {}
 link ENG_NOUN:REPTILIAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:рептилия {}
 link ENG_NOUN:REPRODUCTION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:репродукция {}
 link ENG_NOUN:REPRODUCIBILITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:репродуктивность {}
 link ENG_NOUN:REPOSITORY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:репозиторий {}
 link ENG_NOUN:REPORTER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:репортер {}
 link ENG_NOUN:REPORTAGE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:репортаж {}
 link ENG_NOUN:REPLY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ответ {}
 link ENG_NOUN:REPLICATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:репликация {}
 link ENG_NOUN:REPLICA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:реплика {}
 link ENG_NOUN:REPLICA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:копия {}
 link ENG_NOUN:REPLACEMENT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:замена {}
 link ENG_NOUN:REPETITION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:повторение {}
 link ENG_NOUN:REPEATER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:повторитель {}
 link ENG_NOUN:REPATRIATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:репатриация {}
 link ENG_NOUN:REPARATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:репарация {}
 link ENG_NOUN:RENOVATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:обновление {}
 link ENG_NOUN:RENDEZVOUS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:рандеву {}
 link ENG_NOUN:RENDEZVOUS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:свидание {}
 link ENG_NOUN:RENATIONALISATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ренационализация {}
 link ENG_NOUN:RENAISSANCE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ренесанс {}
 link ENG_NOUN:REMOVAL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:удаление {}
 link ENG_NOUN:REMINDER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:напоминание {}
 link ENG_NOUN:REMAINDER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:остаток {}
 link ENG_NOUN:RELIABILITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:надежность {}
 link ENG_NOUN:RELIABILITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:достоверность {}
 link ENG_NOUN:RELEVANCE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:релевантность {}
 link ENG_NOUN:RELEASE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:релиз {}
 link ENG_NOUN:RELAY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:эстафета {}
 link ENG_NOUN:RELAXATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:релаксация {}
 link ENG_NOUN:RELATIVITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:относительность {}
 link ENG_NOUN:RELATIVIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:релятивист {}
 link ENG_NOUN:RELATIVISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:релятивизм {}
 link ENG_NOUN:RELATIONSHIP {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:родство {}
 link ENG_NOUN:RELATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:отношение {}
 link ENG_NOUN:REJECTION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:отвергание {}
 link ENG_NOUN:REINVESTMENT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:реинвестирование {}
 link ENG_NOUN:REINTEGRATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:реинтеграция {}
 link ENG_NOUN:REGULATOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:регулятор {}
 link ENG_NOUN:REGULATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:регуляция {}
 link ENG_NOUN:REGULATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:регулирование {}
 link ENG_NOUN:REGULARITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:регулярность {}
 link ENG_NOUN:REGRESSION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:регрессия {}
 link ENG_NOUN:REGISTRY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:реестр {}
 link ENG_NOUN:REGISTRATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:регистрация {}
 link ENG_NOUN:REGISTRAR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:регистратор {}
 link ENG_NOUN:REGISTER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:регистр {}
 link ENG_NOUN:REGIONALISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:регионализм {}
 link ENG_NOUN:REGINA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:регина {}
 link ENG_NOUN:REGGIE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:регги {}
 link ENG_NOUN:REGENERATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:регенерация {}
 link ENG_NOUN:REGATTA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:регата {}
 link ENG_NOUN:REFUGEE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:беженец {}
 link ENG_NOUN:REFRIGERATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:замораживание {}
 link ENG_NOUN:REFRIGERATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:охлаждение {}
 link ENG_NOUN:REFRIGERATOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:рефрижератор {}
 link ENG_NOUN:REFRIGERATOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:холодильник {}
 link ENG_NOUN:REFORMIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:реформист {}
 link ENG_NOUN:REFORMISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:реформизм {}
 link ENG_NOUN:REFLEXIVITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:рефлексивность {}
 link ENG_NOUN:REFLEXIVENESS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:рефлексивность {}
 link ENG_NOUN:REFLEXION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:рефлексия {}
 link ENG_NOUN:REFLECTOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:рефлектор {}
 link ENG_NOUN:REFERENCE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ссылка {}
 link ENG_NOUN:REDUNDANCY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:избыточность {}
 link ENG_NOUN:REDIRECTION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:перенаправление {}
 link ENG_NOUN:RECUPERATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:рекуперация {}
 link ENG_NOUN:RECTANGLE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:прямоугольник {}
 link ENG_NOUN:RECRUITER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вербовщик {}
 link ENG_NOUN:RECRUITMENT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вербовка {}
 link ENG_NOUN:RECOVERY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:восстановление {}
 link ENG_NOUN:RECONSTRUCTION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:реконструкция {}
 link ENG_NOUN:RECONNECTION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:переподключение {}
 link ENG_NOUN:RECONFIGURATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:переконфигурирование {}
 link ENG_NOUN:RECOMPILATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:перекомпиляция {}
 link ENG_NOUN:RECOMBINATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:рекомбинация {}
 link ENG_NOUN:RECOGNITION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:распознавание {}
 link ENG_NOUN:RECLAMATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:рекламация {}
 link ENG_NOUN:RECIPIENT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:реципиент {}
 link ENG_NOUN:RECIDIVIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:рецидивист {}
 link ENG_NOUN:RECIDIVISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:рецидивизм {}
 link ENG_NOUN:RECEPTOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:рецептор {}
 link ENG_NOUN:RECEIVER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:приемник {}
 link ENG_NOUN:RECEIVER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ресивер {}
 link ENG_NOUN:RECALIBRATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:перекалибровка {}
 link ENG_NOUN:REBELLION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:восстание {}
 link ENG_NOUN:REBELLION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:бунт {}

 link ENG_NOUN:REALTOR {} <в_сущ> СУЩЕСТВИТЕЛЬНОЕ:риэлтор {}
 link ENG_NOUN:REALM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:царство {}
 link ENG_NOUN:REALITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:реальность {}
 link ENG_NOUN:READING {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:чтение {}
 link ENG_NOUN:REACTIVITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:реактивность {}
 link ENG_NOUN:REACTIVATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:реактивация {}
 link ENG_NOUN:RAT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:крыса {}
 link ENG_NOUN:RATIO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:соотношение {}
 link ENG_NOUN:RATIONALITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:рациональность {}
 link ENG_NOUN:RATIONALIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:рационалист {}
 link ENG_NOUN:RATIONALISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:рационализм {}
 link ENG_NOUN:RATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:рацион {}
 link ENG_NOUN:RARITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:раритет {}
 link ENG_NOUN:RAPE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:изнасилование {}
 link ENG_NOUN:RANDOMNESS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:случайность {}
 link ENG_NOUN:RAMP {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:рампа {}
 link ENG_NOUN:RAMBLER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:бродяга {}
 link ENG_NOUN:RALLY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ралли {}
 link ENG_NOUN:RAISIN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:изюм {}
 link ENG_NOUN:RAID {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:рейд {}
 link ENG_NOUN:RAGE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:бешенство {}
 link ENG_NOUN:RADON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:радон {}
 link ENG_NOUN:RADIX {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:основание {}
 link ENG_NOUN:RADIOTHERAPY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:радиотерапия {}
 link ENG_NOUN:RADIOSCOPY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:радиоскопия {}
 link ENG_NOUN:RADIOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:радиология {}
 link ENG_NOUN:RADIOLOGIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:радиолог {}
 link ENG_NOUN:RADIOISOTOPE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:радиоизотоп {}
 link ENG_NOUN:RADIOGRAPHY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:радиография {}
 link ENG_NOUN:RADIOGRAPH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:радиограф {}
 link ENG_NOUN:RADIOGRAM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:радиограма {}
 link ENG_NOUN:RADIOCHEMISTRY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:радиохимия {}
 link ENG_NOUN:RADIOCARBON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:радиоуглерод {}
 link ENG_NOUN:RADIOBIOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:радиобиология {}
 link ENG_NOUN:RADIOACTIVITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:радиоактивность {}
 link ENG_NOUN:RADIATOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:радиатор {}
 link ENG_NOUN:RADIATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:радиация {}
 link ENG_NOUN:RADIAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:радиан {}
 link ENG_NOUN:RADAR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:радар {}
 link ENG_NOUN:RACISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:расизм {}
 link ENG_NOUN:RACER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:гонщик {}
 link ENG_NOUN:QUOTA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:квота {}
 link ENG_NOUN:QUINTILLION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:квинтиллион {}
 link ENG_NOUN:QUINTESSENCE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:квинтэссенция {}
 link ENG_NOUN:QUICKSILVER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ртуть {}
 link ENG_NOUN:QUESTIONARY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вопросник {}
 link ENG_NOUN:QUESTIONARY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:анкета {}

 link ENG_NOUN:QUERY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:запрос {}
 link ENG_NOUN:QUASAR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:квазар {}
 link ENG_NOUN:QUARTZ {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:кварц {}
 link ENG_NOUN:QUARTO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:кватро {}
 link ENG_NOUN:QUARTER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:четвертак {}
 link ENG_NOUN:QUANTUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:квант {}
 link ENG_NOUN:QUANT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:квант {}
 link ENG_NOUN:QUALIFICATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:квалификация {}
 link ENG_NOUN:QUAKER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:квакер {}
 link ENG_NOUN:QUADRUPLET {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:квадруплет {}
 link ENG_NOUN:QUADRATURE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:квадратура {}
 link ENG_NOUN:QUADRAT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:квадрат {}
 link ENG_NOUN:PYTHON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:питон {}
 link ENG_NOUN:PYROXYLIN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пироксилин {}
 link ENG_NOUN:PYROMETER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пирометр {}
 link ENG_NOUN:PYROMANIA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пиромания {}
 link ENG_NOUN:PYROGRAPHY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пирография {}
 link ENG_NOUN:PYRAMID {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пирамида {}
 link ENG_VERB:PUZZLE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:головоломка {}
 link ENG_NOUN:PUSSYCAT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:киска {}
 link ENG_NOUN:PUSSY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:киска {}
 link ENG_NOUN:PURPURA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пурпур {}
 link ENG_NOUN:PURITANISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пуританство {}
 link ENG_NOUN:PURIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пурист {}
 link ENG_NOUN:PURIFICATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:очистка {}
 link ENG_NOUN:PUPPY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:щенок {}
 link ENG_NOUN:PUNCTUATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пунктуация {}
 link ENG_NOUN:PUNCTUALITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пунктуальность {}
 link ENG_NOUN:PUMPKIN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тыква {}
 link ENG_NOUN:PUMA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пума {}
 link ENG_NOUN:PULSATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пульсация {}
 link ENG_NOUN:PULSAR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пульсар {}
 link ENG_NOUN:PUEBLO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пуэбло {}
 link ENG_NOUN:PUDDING {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пуддинг {}
 link ENG_NOUN:PUBLICATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:публикация {}
 link ENG_NOUN:PTEROSAUR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:птерозавр {}
 link ENG_NOUN:PTEROPOD {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:птеропод {}
 link ENG_NOUN:PTERODACTYL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:птеродактиль {}
 link ENG_NOUN:PSYCHOTHERAPY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:психотерапия {}
 link ENG_NOUN:PSYCHOTHERAPIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:психотерапевт {}
 link ENG_NOUN:PSYCHOSIS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:психоз {}
 link ENG_NOUN:PSYCHOPATHY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:психопатия {}
 link ENG_NOUN:PSYCHOPATHOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:психопатология {}
 link ENG_NOUN:PSYCHOPATH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:психопат {}
 link ENG_NOUN:PSYCHOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:психология {}
 link ENG_NOUN:PSYCHOLOGIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:психолог {}
 link ENG_NOUN:PSYCHOKINESIS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:психокинетика {}
 link ENG_NOUN:PSYCHOANALYST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:психоанализ {}
 link ENG_NOUN:PSYCHO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:псих {}
 link ENG_NOUN:PSYCHEDELIA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:психоделия {}
 link ENG_NOUN:PSORIASIS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:псориаз {}
 link ENG_NOUN:PSEUDOPOD {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:псевдопод {}
 link ENG_NOUN:PSEUDOPODIUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:псевдоподия {}
 link ENG_NOUN:PSALM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:псалм {}
 link ENG_NOUN:PROXIMITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:близость {}
 link ENG_NOUN:PROVOCATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:провокация {}
 link ENG_NOUN:PROVISOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:провизор {}
 link ENG_NOUN:PROVISION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:провизия {}
 link ENG_NOUN:PROVINCE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:провинция {}
 link ENG_NOUN:PROVIDER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:провайдер {}
 link ENG_NOUN:PROVERB {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:поговорка {}
 link ENG_NOUN:PROTOTYPE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:прототип {}
 link ENG_NOUN:PROTOPLASM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:протоплазма {}
 link ENG_NOUN:PROTOCOL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:протокол {}
 link ENG_VERB:PROTEST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:протест {}
 link ENG_NOUN:PROTESTANT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:протестант {}
 link ENG_NOUN:PROTESTANTISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:протестантизм {}
 link ENG_NOUN:PROTEIN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:протеин {}
 link ENG_NOUN:PROTECTORATE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:протекторат {}
 link ENG_NOUN:PROTECTOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:протектор {}
 link ENG_NOUN:PROTECTIONIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:протекционист {}
 link ENG_NOUN:PROTECTIONISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:протекционизм {}
 link ENG_NOUN:PROTAGONIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:протагонист {}
 link ENG_NOUN:PROTACTINIUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:протактиний {}
 link ENG_NOUN:PROSTRATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:прострация {}
 link ENG_NOUN:PROSTITUTION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:проституция {}
 link ENG_NOUN:PROSTATE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:простата {}
 link ENG_NOUN:PROSPERITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:процветание {}
 link ENG_NOUN:PROPULSION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:двигатель {}
 link ENG_NOUN:PROPRIETY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:собственность {}
 link ENG_NOUN:PROPRIETOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:собственник {}
 link ENG_NOUN:PROPORTION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пропорция {}
 link ENG_NOUN:PROPORTIONALITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пропорциональность {}
 link ENG_NOUN:PROPHET {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пророк {}
 link ENG_NOUN:PROPHESY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пророчество {}
 link ENG_NOUN:PROPANE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пропан {}
 link ENG_NOUN:PRONOUNCE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:произношение {}
 link ENG_NOUN:PROMULGATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:промульгация {}
 link ENG_NOUN:PROMOTION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:продвижение {}
 link ENG_NOUN:PROMOTER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:промоутер {}
 link ENG_NOUN:PROLOGUE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пролог {}
 link ENG_NOUN:PROLETARIAT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пролетариат {}
 link ENG_NOUN:PROLETARIAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пролетарий {}
 link ENG_NOUN:PROLEGOMENON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пролегомен {}
 link ENG_NOUN:PROKARYOTE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:прокариот {}
 link ENG_NOUN:PROJECTION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:проекция {}
 link ENG_NOUN:PROHIBITION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:запрет {}
 link ENG_NOUN:PROGRESSION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:прогрессия {}
 link ENG_NOUN:PROGRESS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:прогресс {}
 link ENG_NOUN:PROGRAMME {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:программа {}
 link ENG_NOUN:PROGRAMMER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:программист {}
 link ENG_NOUN:PROFIT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:выгода {}
 link ENG_NOUN:PROFILE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:профиль {}
 link ENG_NOUN:PRODIGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:загадка {}
 link ENG_NOUN:PROCESSION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:процессия {}
 link ENG_NOUN:PROBE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:проба {}
 link ENG_NOUN:PROBE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:зонд {}
 link ENG_NOUN:PRIZEWINNER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:призер {}
 link ENG_NOUN:PRIVATEER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пират {}
 link ENG_NOUN:PRISON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тюрьма {}
 link ENG_NOUN:PRISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:призма {}
 link ENG_NOUN:PRIORITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:приоритет {}
 link ENG_NOUN:PRINTER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:принтер {}
 link ENG_NOUN:PRINCE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:принц {}
 link ENG_NOUN:PRINCESS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:принцесса {}
 link ENG_NOUN:PRIMULA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:примула {}
 link ENG_NOUN:PRIMITIVE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:примитив {}
 link ENG_NOUN:PREY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:добыча {}
 link ENG_NOUN:PREVIEW {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:превью {}
 link ENG_NOUN:PREVENTION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:предотвращение {}
 link ENG_NOUN:PRETENDER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:претендент {}
 link ENG_NOUN:PRESUMPTION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:презумпция {}
 link ENG_NOUN:PRESTIDIGITATOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:престидижитатор {}
 link ENG_NOUN:PRESTIDIGITATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:престидижитация {}
 link ENG_VERB:PRESS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пресс {}
 link ENG_NOUN:PRESERVATIVE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пресерватив {}
 link ENG_NOUN:PRESENTER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:даритель {}
 link ENG_NOUN:PRESENTEE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:одаряемый {}
 link ENG_NOUN:PRESENTATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:презентация {}
 link ENG_NOUN:PRESCRIPT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:предписание {}
 link ENG_NOUN:PREPRINT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:препринт {}
 link ENG_NOUN:PRELUDE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:прелюдия {}

 link ENG_NOUN:PRELATE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:прелат {}
 link ENG_NOUN:PREGNANCY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:беременность {}
 link ENG_NOUN:PREFERENCE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:преференция {}
 link ENG_NOUN:PREFERENCE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:предпочтение {}
 link ENG_NOUN:PREFECT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:префект {}
 link ENG_NOUN:PREDICTOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:предиктор {}
 link ENG_NOUN:PREDICTION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:предсказание {}
 link ENG_NOUN:PREDICATE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:предиат {}
 link ENG_NOUN:PREDECESSOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:предок {}
 link ENG_NOUN:PREDATOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:хищник {}
 link ENG_NOUN:PRECONDITION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:предусловие {}
 link ENG_NOUN:PRECISION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:точность {}
 link ENG_NOUN:PRECAUTION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:предостережение {}
 link ENG_NOUN:PRANA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:прана {}
 link ENG_NOUN:PRAGMATIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:прагматик {}
 link ENG_NOUN:PRAGMATISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:прагматизм {}
 link ENG_NOUN:PRAETOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:претор {}
 link ENG_NOUN:POWERPLANT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:электростанция {}
 link ENG_NOUN:POWER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:энергия {}
 link ENG_NOUN:POVERTY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:бедность {}
 link ENG_NOUN:POT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:горшок {}
 link ENG_NOUN:POTENTIAL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:потенциал {}
 link ENG_NOUN:POTASH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:поташ {}
 link ENG_NOUN:POTASSIUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:калий {}
 link ENG_NOUN:POSTULATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:постулирование {}
 link ENG_NOUN:POSTULATE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:постулат {}
 link ENG_NOUN:POSTMARK {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:марка {}
 link ENG_NOUN:POSSESSOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:владелец {}
 link ENG_NOUN:POSSESSION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:владение {}
 link ENG_NOUN:POSITRON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:позитрон {}
 link ENG_NOUN:POSITIVITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:позитивность {}
 link ENG_NOUN:POSITIVIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:позитивист {}
 link ENG_NOUN:POSITIVISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:позитивизм {}
 link ENG_NOUN:POSITIVENESS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:позитивность {}
 link ENG_NOUN:PORTRAIT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:портрет {}
 link ENG_NOUN:PORTRAITIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:портретист {}
 link ENG_NOUN:PORTFOLIO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:портфолио {}
 link ENG_NOUN:PORTABILITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:портабельность {}
 link ENG_NOUN:PORTABILITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:переносимость {}
 link ENG_NOUN:PORNO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:порно {}
 link ENG_NOUN:PORNOGRAPHY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:порнография {}
 link ENG_NOUN:PORNOGRAPHER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:порнограф {}
 link ENG_NOUN:PORK {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:свинина {}
 link ENG_NOUN:POPULIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:популист {}
 link ENG_NOUN:POPULATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:популяция {}
 link ENG_NOUN:POPULARITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:популярность {}
 link ENG_NOUN:POPCORN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:попкорн {}
 link ENG_NOUN:PONTIFICATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:понтификация {}
 link ENG_NOUN:PONCHO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пончо {}
 link ENG_NOUN:POMADE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:помада {}
 link ENG_NOUN:POLYTHEIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:политеист {}
 link ENG_NOUN:POLYTHEISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:политеизм {}
 link ENG_NOUN:POLYPUS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:полип {}
 link ENG_NOUN:POLYP {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:полип {}
 link ENG_NOUN:POLYPROPYLENE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:полипропилен {}
 link ENG_NOUN:POLYNOMIAL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:полином {}
 link ENG_NOUN:POLYMORPHISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:полиморфизм {}
 link ENG_NOUN:POLYMER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:полимер {}
 link ENG_NOUN:POLYGONUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:полигон {}
 link ENG_NOUN:POLYGON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:полигон {}
 link ENG_NOUN:POLO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:поло {}
 link ENG_NOUN:POLONAISE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:полонез {}
 link ENG_NOUN:POLLUTION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:поллюция {}
 link ENG_NOUN:POLITICIAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:политик {}
 link ENG_NOUN:POLICY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:полиция {}
 link ENG_NOUN:POLAND {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:польша {}
 link ENG_NOUN:POESY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:поэзия {}
 link ENG_NOUN:PODIUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:подиум {}
 link ENG_NOUN:PODAGRA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:подагра {}
 link ENG_NOUN:PNEUMONIA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пневмония {}
 link ENG_NOUN:PLUTONIUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:плутоний {}
 link ENG_NOUN:PLUTON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:плутон {}
 link ENG_NOUN:PLUTO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:плутон {}
 link ENG_NOUN:PLUS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:плюс {}
 link ENG_NOUN:PLURALIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:плюралист {}
 link ENG_NOUN:PLURALISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:плюрализм {}
 link ENG_NOUN:PLAZA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:плаза {}
 link ENG_NOUN:PLAZA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:площадь {}
 link ENG_NOUN:PLAYER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:игрок {}
 link ENG_NOUN:PLAYBOY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:шалун {}
 link ENG_NOUN:PLATEAU {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:плато {}
 link ENG_NOUN:PLATAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:платан {}
 link ENG_NOUN:PLASMA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:плазма {}
 link ENG_NOUN:PLANKTON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:планктон {}
 link ENG_NOUN:PLANETOID {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:планетоид {}
 link ENG_NOUN:PLANETARIUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:планетарий {}
 link ENG_NOUN:PLANCHET {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:планшет {}
 link ENG_NOUN:PLAGUE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:чума {}
 link ENG_NOUN:PLACENTA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:плацента {}
 link ENG_NOUN:PLACEBO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:плацебо {}
 link ENG_NOUN:PIZZA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пицца {}
 link ENG_NOUN:PISTON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пистон {}
 link ENG_NOUN:PISTOLE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пистолет {}
 link ENG_NOUN:PISTOL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пистолет {}
 link ENG_NOUN:PISSOIR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:писсуар {}
 link ENG_NOUN:PIROUETTE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пируэт {}
 link ENG_NOUN:PIRACY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пиратство {}
 link ENG_NOUN:PIONEER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пионер {}
 link ENG_NOUN:PINTA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пинта {}
 link ENG_NOUN:PIMP {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:прыщ {}
 link ENG_NOUN:PIMPLE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:прыщ {}
 link ENG_NOUN:PIMP {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сутенер {}
 link ENG_NOUN:PILGRIM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пилигрим {}
 link ENG_NOUN:PIEZOELECTRICITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пьезоэлектричество {}
 link ENG_NOUN:PIER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пьер {}
 link ENG_NOUN:PICTOGRAM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пиктограма {}
 link ENG_NOUN:PICNIC {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пикник {}
 link ENG_NOUN:PICADOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пикадор {}
 link ENG_NOUN:PIANOLA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пианола {}
 link ENG_NOUN:PHYSIOTHERAPY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:физиотерапия {}
 link ENG_NOUN:PHYSIOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:физиология {}
 link ENG_NOUN:PHYSIOLOGIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:физиолог {}
 link ENG_NOUN:PHOTOTROPISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:фототропизм {}
 link ENG_NOUN:PHOTOSYNTHESIS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:фотосинтез {}
 link ENG_NOUN:PHOTOSPHERE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:фотосфера {}
 link ENG_NOUN:PHOTORECEPTOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:фоторецептор {}
 link ENG_NOUN:PHOTOPHOBIA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:фотофобия {}
 link ENG_NOUN:PHOTON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:фотон {}
 link ENG_NOUN:PHOTOMULTIPLIER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:фотоумножитель {}
 link ENG_NOUN:PHOTOMETER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:фотометр {}
 link ENG_NOUN:PHOTOLITHOGRAPHY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:фотолитография {}
 link ENG_NOUN:PHOTOGRAPHER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:фотограф {}
 link ENG_NOUN:PHOTODIODE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:фотодиод {}
 link ENG_NOUN:PHOTOCOPY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:фотокопия {}
 link ENG_NOUN:PHOTOCHEMISTRY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:фотохимия {}
 link ENG_NOUN:PHOSPHOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:фосфор {}
 link ENG_NOUN:PHOSPHORITE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:фосфорит {}
 link ENG_NOUN:PHOSPHITE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:фосфит {}
 link ENG_NOUN:PHOSPHIDE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:фосфид {}
 link ENG_NOUN:PHOSPHATE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:фосфат {}
 link ENG_NOUN:PHONON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:фонон {}
 link ENG_NOUN:PHONOGRAPH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:фонограф {}
 link ENG_NOUN:PHONOGRAM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:фонограма {}
 link ENG_NOUN:PHONEME {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:фонема {}
 link ENG_NOUN:PHOBIA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:фобия {}
 link ENG_NOUN:PHLOX {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:флокс {}
 link ENG_NOUN:PHLOGISTON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:флогистон {}
 link ENG_NOUN:PHILOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:филология {}
 link ENG_NOUN:PHILOLOGIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:филолог {}
 link ENG_NOUN:PHILODENDRON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:филодендрон {}
 link ENG_NOUN:PHILANTHROPY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:филантропия {}
 link ENG_NOUN:PHILANTHROPIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:филантроп {}
 link ENG_NOUN:PHILANTHROPE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:филантроп {}
 link ENG_NOUN:PHEROMONE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:феромон {}
 link ENG_NOUN:PHENYL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:фенил {}
 link ENG_NOUN:PHENOTYPE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:фенотип {}
 link ENG_NOUN:PHENOMENON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:феномен {}
 link ENG_NOUN:PHENOMENOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:феноменология {}
 link ENG_NOUN:PHENOMENOLOGIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:феноменолог {}
 link ENG_NOUN:PHENOMENALISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:феноменализм {}
 link ENG_NOUN:PHENOL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:фенол {}
 link ENG_NOUN:PHASE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:фаза {}
 link ENG_NOUN:PHARMACY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:фармация {}
 link ENG_NOUN:PHARMACOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:фармакология {}
 link ENG_NOUN:PHARMACOLOGIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:фармаколог {}
 link FR_NOUN:PHARMACIE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:фармация {}
 link ENG_NOUN:PHANTASM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:фантазм {}
 link ENG_NOUN:PHANTASMAGORIA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:фантасмагория {}
 link ENG_NOUN:PHAGOCYTE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:фагоцит {}
 link ENG_NOUN:PHAETON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:фаэтон {}
 link ENG_NOUN:PETROL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:бензин {}
 link ENG_NOUN:PETITION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:петиция {}
 link ENG_NOUN:PESTICIDE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пестицид {}
 link ENG_NOUN:PESSIMIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пессимист {}
 link ENG_NOUN:PESSIMISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пессимизм {}
 link ENG_NOUN:PERVERSION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:перверсия {}
 link ENG_NOUN:PERVERSION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:извращение {}
 link ENG_NOUN:PERVASIVENESS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:извращенность {}
 link ENG_NOUN:PERU {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:перу {}
 link ENG_NOUN:PERTURBATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пертурбация {}
 link ENG_NOUN:PERTINENCE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:постоянство {}
 link ENG_NOUN:PERSONALITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:персональность {}
 link ENG_NOUN:PERSONAL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:персонал {}
 link ENG_NOUN:PEROXIDE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пероксид {}
 link ENG_NOUN:PERMUTATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:перестановка {}
 link ENG_NOUN:PERISCOPE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:перископ {}
 link ENG_NOUN:PERIPHERY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:периферия {}
 link ENG_NOUN:PEREGRINE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:перегрин {}
 link ENG_NOUN:PERCEPTION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:восприятие {}
 link ENG_NOUN:PERCENT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:процент {}
 link ENG_NOUN:PEPPERBOX {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:перечница {}
 link ENG_NOUN:PENTODE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пентод {}
 link ENG_NOUN:PENTHOUSE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пентхауз {}
 link ENG_NOUN:PENTANGLE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пятиугольник {}
 link ENG_NOUN:PENTANE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пентан {}
 link ENG_NOUN:PENTAGRAM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пентаграмма {}
 link ENG_NOUN:PENTAGON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пентагон {}
 link ENG_NOUN:PENSIONER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пенсионер {}
 link ENG_NOUN:PENSION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пенсия {}
 link ENG_NOUN:PENIS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пенис {}
 link ENG_NOUN:PENICILLIN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пенициллин {}
 link ENG_NOUN:PENETRATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:проникновение {}
 link ENG_NOUN:PENDULUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:маятник {}
 link ENG_NOUN:PELICAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пеликан {}
 link ENG_NOUN:PEDICURE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:педикюр {}
 link ENG_NOUN:PEDERASTY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:педерастия {}
 link ENG_NOUN:PEDERAST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:педераст {}
 link ENG_NOUN:PEDAGOGUE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:педагог {}
 link ENG_NOUN:PEDAGOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:педагогия {}
 link ENG_NOUN:PECULIARITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:странность {}
 link ENG_NOUN:PEASANT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:крестьянин {}
 link ENG_NOUN:PEACEMAKER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:миротворец {}
 link ENG_NOUN:PEACEKEEPER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:миротворец {}
 link ENG_NOUN:PAUSE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пауза {}
 link ENG_NOUN:PATROL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:патруль {}
 link ENG_NOUN:PATRIARCH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:патриарх {}
 link ENG_NOUN:PATRIARCHY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:патриархия {}
 link ENG_NOUN:PATIO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:патио {}
 link ENG_NOUN:PATINA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:патина {}
 link ENG_NOUN:PATIENCE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:терпение {}
 link ENG_NOUN:PATHOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:патология {}
 link ENG_NOUN:PATERNALIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:патерналист {}
 link ENG_NOUN:PATERNALISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:патернализм {}
 link ENG_NOUN:PATCH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:заплата {}

 link ENG_NOUN:PASTORALE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пастораль {}
 link ENG_NOUN:PASTOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пастор {}
 link ENG_NOUN:PASTA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:макароны {}
 link ENG_NOUN:PASCAL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:паскаль {}
 link ENG_NOUN:PARTY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:вечеринка {}
 link ENG_NOUN:PARTITION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:раздел {}
 link ENG_NOUN:PARTISAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:партизан {}
 link ENG_NOUN:PARTICLE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:частица {}
 link ENG_NOUN:PARTICIPLE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:причастие {}
 link ENG_NOUN:PARTICIPANT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:участник {}
 link ENG_NOUN:PAROXYSM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пароксизм {}
 link ENG_NOUN:PARODY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пародия {}
 link ENG_NOUN:PARMESAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пармезан {}
 link ENG_NOUN:PARAVANE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:параван {}
 link ENG_NOUN:PARATROOPER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:парашютист {}
 link ENG_NOUN:PARATROOP {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:парашют {}
 link ENG_NOUN:PARASITISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:паразитизм {}
 link ENG_NOUN:PARAPHRASE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:парафраза {}
 link ENG_NOUN:PARAPET {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:парапет {}
 link ENG_NOUN:PARAMETER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:параметр {}
 link ENG_NOUN:PARALLELISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:параллелизм {}
 link ENG_NOUN:PARAGUAY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:парагвай {}
 link ENG_NOUN:PARAFFIN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:парафин {}
 link ENG_NOUN:PARADOX {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:парадокс {}
 link ENG_NOUN:PARADISE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:рай {}
 link ENG_NOUN:PARADIGM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:парадигма {}
 link ENG_NOUN:PARACHUTE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:параш {}
 link ENG_NOUN:PARACETAMOL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:парацетамол {}
 link ENG_NOUN:PARABOLOID {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:параболоид {}
 link ENG_NOUN:PARABOLA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:парабола {}
 link ENG_NOUN:PAPYRUS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:папирус {}
 link ENG_NOUN:PAPUA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:папуа {}
 link ENG_NOUN:PAPAYA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:папайя {}
 link ENG_NOUN:PAPARAZZO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:папарацци {}
 link ENG_NOUN:PANTOMIME {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пантомима {}
 link ENG_NOUN:PANTOGRAPH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пантограф {}
 link ENG_NOUN:PANTHER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пантера {}
 link ENG_NOUN:PANTHEON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пантеон {}
 link ENG_NOUN:PANORAMA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:панорама {}
 link ENG_NOUN:PANIC {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:паника {}
 link ENG_NOUN:PANEL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:панель {}
 link ENG_NOUN:PANEGYRIC {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:панегирик {}
 link ENG_NOUN:PANDA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:панда {}
 link ENG_NOUN:PANACEA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:панацея {}
 link ENG_NOUN:PAMPHLET {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:памфлет {}
 link ENG_NOUN:PAMPAS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пампасы {}
 link ENG_NOUN:PALETTE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:палитра {}
 link ENG_NOUN:PALESTINA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:палестина {}
 link ENG_NOUN:PALAU {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:палау {}
 link ENG_NOUN:PALAEOBOTANY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:палеоботаника {}
 link ENG_NOUN:PAINTBRUSH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:кисть {}
 link ENG_NOUN:PAINKILLER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:болеутолитель {}
 link ENG_NOUN:PAHLAVI {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пахлави {}
 link ENG_NOUN:PAGODA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пагода {}
 link ENG_NOUN:PAEDOPHILIA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:педофилия {}
 link ENG_NOUN:PAEDOPHILE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:педофил {}
 link ENG_NOUN:PAEDIATRICS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:педиатрия {}
 link ENG_NOUN:PACIFISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:пацифизм {}
 link ENG_NOUN:OXYMORON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:оксиморон {}
 link ENG_NOUN:OXIDE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:оксид {}
 link ENG_NOUN:OWL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сова {}
 link ENG_NOUN:OVULATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:овуляция {}
 link ENG_NOUN:OVERTURE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:увертюра {}
 link ENG_NOUN:OVERSIMPLIFICATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:переупрощение {}
 link ENG_NOUN:OVERPRODUCTION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:перепроизводство {}
 link ENG_NOUN:OVERPOPULATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:перенаселенность {}
 link ENG_NOUN:OVERFATIGUE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:переутомление {}
 link ENG_NOUN:OVEN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:печь {}
 link ENG_NOUN:OUTPUT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:выход {}
 link ENG_NOUN:OUTLINE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:контур {}
 link ENG_NOUN:OUSTER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:устрица {}
 link ENG_NOUN:OTTOMAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:оттоман {}
 link ENG_NOUN:OTOLITH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:отолит {}
 link ENG_NOUN:OSTRACISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:остракизм {}
 link ENG_NOUN:OSTEOPATHY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:остеопатия {}
 link ENG_NOUN:OSMOSIS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:осмос {}
 link ENG_NOUN:OSCILLOSCOPE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:осцилоскоп {}
 link ENG_NOUN:OSCILLOGRAPH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:осцилограф {}
 link ENG_NOUN:OSCILLATOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:осциллятор {}
 link ENG_NOUN:OSCILLATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:осцилляция {}
 link ENG_NOUN:OSCAR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:оскар {}
 link ENG_NOUN:ORTHODOXY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ортодоксальность {}
 link ENG_NOUN:ORPHAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сирота {}
 link ENG_NOUN:ORPHANAGE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сиротство {}
 link ENG_NOUN:ORNITHOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:орнитология {}
 link ENG_NOUN:ORIGAMI {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:оригами {}
 link ENG_NOUN:ORIENTATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ориентация {}
 link ENG_NOUN:ORIENTALISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ориентализм {}
 link ENG_NOUN:ORGASM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:оргазм {}
 link ENG_NOUN:ORGAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:орган {}
 link ENG_NOUN:ORGANISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:организм {}
 link ENG_NOUN:ORGANIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:органист {}
 link ENG_NOUN:ORCHID {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:орхидея {}
 link ENG_NOUN:ORATOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:оратор {}
 link ENG_NOUN:ORATORY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:оратория {}
 link ENG_NOUN:ORANGERY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:оранжерея {}
 link ENG_NOUN:ORACLE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:оракул {}
 link ENG_NOUN:OPTION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:опция {}
 link ENG_NOUN:OPTIMIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:оптимист {}
 link ENG_NOUN:OPTIMISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:оптимизм {}
 link ENG_NOUN:OPPRESSOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:угнетатель {}
 link ENG_NOUN:OPPOSITION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:оппозиция {}
 link ENG_NOUN:OPPORTUNITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:возможность {}
 link ENG_NOUN:OPPORTUNIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:оппортунист {}
 link ENG_NOUN:OPPORTUNISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:оппортунизм {}
 link ENG_NOUN:OPPONENT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:оппонент {}
 link ENG_NOUN:OPOSSUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:опоссум {}
 link ENG_NOUN:OPHTHALMOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:офтальмология {}
 link ENG_NOUN:OPHTHALMOLOGIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:офтальмолог {}
 link ENG_NOUN:OPERETTA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:оперетта {}
 link ENG_NOUN:OPERATOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:оператор {одуш:неодуш}
 link ENG_NOUN:OPERATOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:оператор {одуш:одуш}
 link ENG_NOUN:OPERAND {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:операнд {}
 link ENG_NOUN:OPEN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:открытие {}
 link ENG_NOUN:OPAL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:опал {}
 link ENG_NOUN:ONTOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:онтология {}
 link ENG_NOUN:ONTOGENESIS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:онтогенезис {}
 link ENG_NOUN:ONCOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:онкология {}
 link ENG_NOUN:ONANISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:онанизм {}
 link ENG_NOUN:OMNIBUS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:омнибус {}
 link ENG_NOUN:OMICRON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:омикрон {}
 link ENG_NOUN:OMEN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:предзнаменование {}
 link ENG_NOUN:OMEGA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:омега {}
 link ENG_NOUN:OLYMPIAD {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:олимпиада {}

 link ENG_NOUN:OLIGOPOLY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:олигополия {}
 link ENG_NOUN:OLIGARCHY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:олигархия {}
 link ENG_NOUN:OFFSET {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:смещение {}
 link ENG_NOUN:OFFICER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:офицер {}
 link ENG_NOUN:ODYSSEY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:одиссей {}
 link ENG_NOUN:ODOUR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:аромат {}
 link ENG_NOUN:ODOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:аромат {}
 link ENG_NOUN:ODOMETER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:одометр {}
 link ENG_NOUN:ODDITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:странность {}
 link ENG_NOUN:OCTOPUS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:осьминог {}
 link ENG_NOUN:OCTOPOD {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:осьминог {}
 link ENG_NOUN:OCTET {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:октет {}
 link ENG_NOUN:OCTAGON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:восьмиугольник {}
 link ENG_NOUN:OCHLOCRACY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:охлократия {}
 link ENG_NOUN:OCEANOGRAPHY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:океанография {}
 link ENG_NOUN:OCEANOGRAPHER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:океанограф {}
 link ENG_NOUN:OCEANIA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:океания {}
 link ENG_NOUN:OCEANARIUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:океанариум {}
 link ENG_NOUN:OCEAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:океан {}
 link ENG_NOUN:OCCUPANT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:оккупант {}
 link ENG_NOUN:OBSTRUCTION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:обструкция {}
 link ENG_NOUN:OBSTRUCTIONISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:обструкционизм {}
 link ENG_NOUN:OBSIDIAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:обсидиан {}
 link ENG_NOUN:OBSCURANTIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:обскурантист {}
 link ENG_NOUN:OBSCURANTISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:обскурантизм {}
 link ENG_NOUN:OBJECT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:объект {}
 link ENG_NOUN:OBJECTIVITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:объективность {}
 link ENG_NOUN:OBJECTIVISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:объективизм {}
 link ENG_NOUN:OBELISK {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:обелиск {}
 link ENG_NOUN:OASIS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:оазис {}
 link ENG_NOUN:NYMPH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нимфа {}
 link ENG_NOUN:NYMPHOMANIA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нимфомания {}
 link ENG_NOUN:NU {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ню {}
 link ENG_NOUN:NUT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:орех {}
 link ENG_NOUN:NUTSHELL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:скорлупа {}
 link ENG_NOUN:NUTRIA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нутрия {}
 link ENG_NOUN:NUMISMATICS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нумизматика {}
 link ENG_NOUN:NUMEROLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нумерология {}
 link ENG_NOUN:NUMEROLOGIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нумеролог {}
 link ENG_NOUN:NUDITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:обнаженность {}
 link ENG_NOUN:NUDIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нудист {}
 link ENG_NOUN:NUCLIDE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нуклид {}
 link ENG_NOUN:NUCLEOTIDE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нуклиотид {}
 link ENG_NOUN:NOVOCAINE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:новокаин {}
 link ENG_NOUN:NOVELLA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:новелла {}
 link ENG_NOUN:NOTEBOOK {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:блокнот {}
 link ENG_NOUN:NOTATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нотация {}
 link ENG_NOUN:NOSTALGIA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ностальгия {}
 link ENG_NOUN:NONSENSE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нонсенс {}
 link ENG_NOUN:NOMOGRAM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:номограмма {}
 link ENG_NOUN:NOMINATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:номинация {}
 link ENG_NOUN:NOCTURNE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ноктюрн {}
 link ENG_NOUN:NITRITE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нитрит {}
 link ENG_NOUN:NITRIDE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нитрид {}
 link ENG_NOUN:NITRATE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нитрат {}
 link ENG_NOUN:NIRVANA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нирвана {}
 link ENG_NOUN:NIPPLE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сосок {}
 link ENG_NOUN:NIOBIUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ниобий {}
 link ENG_NOUN:NINJA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ниндзя {}
 link ENG_NOUN:NIHILISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нигилизм {}
 link ENG_NOUN:NIGHTMARE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:кошмар {}
 link ENG_NOUN:NIGGER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ниггер {}
 link ENG_NOUN:NICOTINE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:никотин {}
 link ENG_NOUN:NICKNAME {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:прозвище {}
 link ENG_NOUN:NICHROME {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нихром {}
 link ENG_NOUN:NICARAGUA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:никарагуа {}
 link ENG_NOUN:NEXUS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нексус {}
 link ENG_NOUN:NEWTON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ньютон {}
 link ENG_NOUN:NEWS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:новость {}
 link ENG_NOUN:NEVADA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:невада {}
 link ENG_NOUN:NEUTRON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нейтрон {}
 link ENG_NOUN:NEUTRINO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нейтрино {}
 link ENG_NOUN:NEUROSURGERY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нейрохирургия {}
 link ENG_NOUN:NEUROSURGEON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нейрохирург {}
 link ENG_NOUN:NEURON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нейрон {}
 link ENG_NOUN:NEUROBIOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нейробиология {}
 link ENG_NOUN:NETWORK {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сеть {}
 link ENG_NOUN:NETHERLANDS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нидерланды {}
 link ENG_NOUN:NEST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:гнездо {}
 link ENG_NOUN:NEREID {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нереида {}
 link ENG_NOUN:NEPTUNIUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нептуний {}
 link ENG_NOUN:NEPTUNE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нептун {}
 link ENG_NOUN:NEPOTISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:непотия {}
 link ENG_NOUN:NEOPRENE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:неопрен {}
 link ENG_NOUN:NEOPLATONISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:неоплатонизм {}
 link ENG_NOUN:NEOPHYTE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:неофит {}
 link ENG_NOUN:NEODYMIUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:неодим {}
 link ENG_NOUN:NEMATODE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нематода {}
 link ENG_NOUN:NEGATIVITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:негативность {}
 link ENG_NOUN:NECTARINE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нектарин {}
 link ENG_NOUN:NECTAR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нектар {}
 link ENG_NOUN:NECROPHOBIA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:некрофобия {}
 link ENG_NOUN:NECROPHILIA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:некрофилия {}
 link ENG_NOUN:NECKTIE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:галстук {}
 link ENG_NOUN:NEBULA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:небула {}
 link ENG_NOUN:NAVIGATOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:навигатор {}
 link ENG_NOUN:NAVIGATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:навигация {}
 link ENG_NOUN:NAVAJO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:навахо {}
 link ENG_NOUN:NAUTILUS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:наутилус {}
 link ENG_NOUN:NAURU {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:науру {}
 link ENG_NOUN:NATURIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:натурист {}
 link ENG_NOUN:NATURISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:натуризм {}
 link ENG_NOUN:NATURE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:натура {}
 link ENG_NOUN:NATURALIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:натуралист {}
 link ENG_NOUN:NATURALISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:натурализм {}
 link ENG_NOUN:NATIONALIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:националист {}
 link ENG_ADVERB:NATIONALISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:национализм {}
 link ENG_NOUN:NATIONALISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:национализм {}
 link ENG_NOUN:NASTURTIUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:настурция {}
 link ENG_NOUN:NARCOSIS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:наркоз {}
 link ENG_NOUN:NARCISSISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нарциссизм {}
 link ENG_NOUN:NAPOLEON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:наполеон {}
 link ENG_NOUN:NAPALM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:напалм {}
 link ENG_NOUN:NANOMETRE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нанометр {}
 link ENG_NOUN:NANKEEN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:нанкин {}
 link ENG_NOUN:NABOB {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:набоб {}
 link ENG_NOUN:MYTH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:миф {}
 link ENG_NOUN:MYTHOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мифология {}
 link ENG_NOUN:MYSTICISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мистицизм {}
 link ENG_NOUN:MYSTIFICATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мистификация {}
 link ENG_NOUN:MYSTERY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:загадка {}
 link ENG_NOUN:MYOPIA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:миопия {}

 link ENG_NOUN:MYOGLOBIN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:миоглобин {}
 link ENG_NOUN:MYCELIUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:миселий {}
 link ENG_NOUN:MUZHIK {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мужик {}
 link ENG_NOUN:MUTTON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:овчина {}
 link ENG_NOUN:MUTATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мутация {}
 link ENG_NOUN:MUTABILITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:изменчивость {}
 link ENG_NOUN:MUSTARD {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:горчица {}
 link ENG_NOUN:MUSTANG {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мустанг {}
 link ENG_NOUN:MUSICALITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:музыкальность {}
 link ENG_NOUN:MUSCULATURE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мускулатура {}
 link ENG_NOUN:MUON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мюон {}
 link ENG_NOUN:MULTIPLIER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:умножитель {}
 link ENG_NOUN:MULTIPLICAND {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:множитель {}
 link ENG_NOUN:MULTIPLEXOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мультиплексор {}
 link ENG_NOUN:MULTIMETER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мультиметр {}
 link ENG_NOUN:MULTIMEDIA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мультимедия {}
 link ENG_NOUN:MUJAHIDIN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:муджахед {}
 link ENG_NOUN:MOUSSE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мусс {}
 link ENG_NOUN:MOTORIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:моторист {}
 link ENG_NOUN:MOTORCYCLE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мотоцикл {}
 link ENG_NOUN:MOTORBIKE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мотоцикл {}
 link ENG_NOUN:MOTIVATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мотивация {}
 link ENG_NOUN:MOTEL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мотель {}
 link ENG_NOUN:MOSQUITO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:москит {}
 link ENG_NOUN:MOSCOW {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:москва {}
 link ENG_NOUN:MORTGAGE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ипотека {}
 link ENG_NOUN:MORPHOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:морфология {}
 link ENG_NOUN:MORPHINE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:морфин {}
 link ENG_NOUN:MORPHEME {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:морфема {}
 link ENG_NOUN:MORMON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мормон {}
 link ENG_NOUN:MORGUE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:морг {}
 link ENG_NOUN:MORALIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:моралист {}
 link ENG_NOUN:MORALE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мораль {}
 link ENG_NOUN:MORALISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:морализм {}
 link ENG_NOUN:MORALITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:моральность {}
 link ENG_NOUN:MONTAGE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:монтаж {}
 link ENG_NOUN:MONSTER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:монстр {}
 link FR_NOUN:MONSIEUR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:господин {}
 link ENG_NOUN:MONSIGNOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:господин {}
 link ENG_NOUN:MONOTONY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:монотонность {}
 link ENG_NOUN:MONOTHEIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:монотеист {}
 link ENG_NOUN:MONOTHEISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:монотеизм {}
 link ENG_NOUN:MONOPOLY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:монополия {}
 link ENG_NOUN:MONOPOLIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:монополист {}
 link ENG_NOUN:MONOPLANE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:моноплан {}
 link ENG_NOUN:MONOMER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мономер {}
 link ENG_NOUN:MONOLOGUE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:монолог {}
 link ENG_NOUN:MONOLITH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:монолит {}
 link ENG_NOUN:MONOHYBRID {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:моногидрид {}
 link ENG_NOUN:MONOGAMY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:моногамия {}
 link ENG_NOUN:MONOCULTURE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:монокультура {}
 link ENG_NOUN:MONOCLE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:монокль {}
 link ENG_NOUN:MONKEY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:обезьяна {}
 link ENG_NOUN:MONISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:монизм {}
 link ENG_NOUN:MONETARIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:монетарист {}
 link ENG_NOUN:MONETARISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:монетаризм {}
 link ENG_NOUN:MONARCH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:монарх {}
 link ENG_NOUN:MONARCHIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:монархист {}
 link ENG_NOUN:MONARCHISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:монархизм {}
 link ENG_NOUN:MONAD {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:монада {}
 link ENG_NOUN:MONACO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:монако {}
 link ENG_NOUN:MOM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мама {}
 link ENG_NOUN:MOMMY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мама {}
 link ENG_NOUN:MOMENTUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:момент {}
 link ENG_NOUN:MOLYBDENITE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:молибденит {}
 link ENG_NOUN:MOLOCH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:молох {}
 link ENG_NOUN:MOLLUSC {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:моллюск {}
 link ENG_NOUN:MOLECULE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:молекула {}
 link ENG_NOUN:MOHAIR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мохер {}
 link ENG_NOUN:MOHAWK {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:томогавк {}
 link ENG_NOUN:MODULUS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:модуль {}
 link ENG_NOUN:MODULE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:модуль {}
 link ENG_NOUN:MODULATOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:модулятор {}
 link ENG_NOUN:MODULATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:модуляция {}
 link ENG_NOUN:MODIFIER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:модификатор {}
 link ENG_NOUN:MODIFICATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:модификация {}
 link ENG_NOUN:MODESTY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:скромность {}
 link ENG_NOUN:MODERNIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:модернист {}
 link ENG_ADVERB:MODERNISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:модернизм {}
 link ENG_NOUN:MODERNISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:модернизм {}
 link ENG_NOUN:MODERATOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:модератор {}
 link ENG_NOUN:MODERATOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:замедлитель {}
 link ENG_NOUN:MODERATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:замедление {}
 link ENG_NOUN:MODEM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:модем {}
 link ENG_NOUN:MODEL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:модель {}
 link ENG_NOUN:MODE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:режим {}
 link ENG_NOUN:MODALITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:модальность {}
 link ENG_NOUN:MOCCASIN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мокасин {}
 link ENG_NOUN:MOBILITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мобильность {}
 link ENG_NOUN:MOB {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:толпа {}
 link ENG_NOUN:MIXER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:миксер {}
 link ENG_NOUN:MITOSIS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:митоз {}
 link ENG_NOUN:MITOCHONDRIA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:митохондрия {}
 link ENG_NOUN:MITHRAISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:митраизм {}
 link ENG_NOUN:MISTER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мистер {}
 link ENG_VERB:MISS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мисс {}
 link ENG_NOUN:MISSIS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:миссис {}
 link ENG_NOUN:MISSIONER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:миссионер {}
 link ENG_NOUN:MISSILE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ракета {}
 link ENG_NOUN:MISFORTUNE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:невезенье {}
 link ENG_NOUN:MISFORTUNE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:некдача {}
 link ENG_NOUN:MISFORTUNE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:неудача {}
 link ENG_NOUN:MIRAGE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мираж {}
 link ENG_NOUN:MIRADOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мирадор {}
 link ENG_NOUN:MIRACLE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:загадка {}
 link ENG_NOUN:MINUET {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:минует {}
 link ENG_NOUN:MINOTAUR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:минотавр {}
 link ENG_NOUN:MINORITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:меньшинство {}
 link ENG_NOUN:MINISKIRT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:миниюбка {}
 link ENG_NOUN:MINIMALITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:минимальность {}
 link ENG_NOUN:MINIMALIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:минималист {}
 link ENG_NOUN:MINIMALISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:минимализм {}
 link ENG_NOUN:MINICOMPUTER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:миникомпьютер {}
 link ENG_NOUN:MINIATURE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:миниатюра {}
 link ENG_NOUN:MINI {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мини {}
 link ENG_NOUN:MINERALOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:минералогия {}
 link ENG_NOUN:MINARET {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:минарет {}
 link ENG_NOUN:MIMOSA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мимоза {}
 link ENG_NOUN:MIMICRY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мимикрия {}
 link ENG_NOUN:MILLIMETRE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:миллиметр {}
 link ENG_NOUN:MILLILITRE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:миллилитр {}
 link ENG_NOUN:MILLIGRAM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:миллиграм {}
 link ENG_NOUN:MILLIBAR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:минибар {}
 link ENG_NOUN:MILLIAMPERE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:миллиампер {}
 link ENG_NOUN:MILLENNIUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:миллениум {}
 link ENG_NOUN:MILLENNIUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:тысячелетие {}
 link ENG_NOUN:MILKMAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:молочник {}
 link ENG_NOUN:MILITIA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:милиция {}
 link ENG_NOUN:MILITARIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:милитарист {}
 link ENG_NOUN:MILITARISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:милитаризм {}
 link ENG_NOUN:MIKADO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:микадо {}
 link ENG_NOUN:MIGRATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:миграция {}
 link ENG_ADJECTIVE:MIGRANT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мигрант {}
 link ENG_NOUN:MICROWAVE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:микроволна {}
 link ENG_NOUN:MICROTOME {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:микротом {}
 link ENG_NOUN:MICROSURGERY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:микрохирургия {}
 link ENG_NOUN:MICROSTRUCTURE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:микроструктура {}
 link ENG_NOUN:MICROSPORE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:микроскоп {}
 link ENG_NOUN:MICROSECOND {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:микросекунда {}
 link ENG_NOUN:MICROSCOPY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:микроскопия {}
 link ENG_NOUN:MICROSCOPE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:микроскоп {}
 link ENG_NOUN:MICROPROGRAM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:микропрограмма {}
 link ENG_NOUN:MICROPROCESSOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:микропроцессор {}
 link ENG_NOUN:MICROMETRE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:микрометр {}
 link ENG_NOUN:MICROMETER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:микрометр {}
 link ENG_NOUN:MICROINSTRUCTION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:микроинструкция {}
 link ENG_NOUN:MICROGRAVITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:микрогравитация {}
 link ENG_NOUN:MICROGRAPH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:микрограф {}
 link ENG_NOUN:MICROFILM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:микрофильм {}
 link ENG_NOUN:MICROCOSM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:микрокосм {}
 link ENG_NOUN:MICROCOMPUTER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:микрокомпьютер {}
 link ENG_NOUN:MICROCODE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:микрокод {}
 link ENG_NOUN:MICROCLIMATE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:микроклимат {}
 link ENG_NOUN:MICROCHIP {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:микрочип {}
 link ENG_NOUN:MICROBIOLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:микробиология {}
 link ENG_NOUN:MICROBIOLOGIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:микробиолог {}
 link FR_NOUN:MICROBE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:микроб {}
 link ENG_NOUN:MICROBE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:микроб {}
 link ENG_NOUN:MICROANALYSIS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:микроанализ {}
 link ENG_NOUN:MEZZANINE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мезанин {}
 link ENG_NOUN:MEXICO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мехико {}
 link ENG_NOUN:METRO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:метро {}
 link ENG_NOUN:METRONOME {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:метроном {}
 link ENG_NOUN:METROLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:метрология {}
 link ENG_NOUN:METHYL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:метил {}
 link ENG_NOUN:METHYLENE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:метилен {}
 link ENG_NOUN:METHOD {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:метод {}
 link ENG_NOUN:METHANOL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:метанол {}
 link ENG_NOUN:METHANE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:метан {}
 link ENG_NOUN:METHAMPHETAMINE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:метамфитамин {}

 link ENG_NOUN:METHADONE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:метадон {}
 link ENG_NOUN:METER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:метр {}
 link ENG_NOUN:METEOROLOGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:метеорология {}
 link ENG_NOUN:METEOROLOGIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:метеоролог {}
 link ENG_NOUN:METEORITE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:метеорит {}
 link ENG_NOUN:METASTASIS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:метастаз {}
 link ENG_NOUN:METASTASE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:метастаз {}
 link ENG_NOUN:METASTABILITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:метастабильность {}
 link ENG_NOUN:METAPHRASE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:метафаза {}
 link ENG_NOUN:METAPHOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:метафора {}
 link ENG_NOUN:METAMORPHOSIS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:метаморфоза {}
 link ENG_NOUN:METAMORPHISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:метаморфизм {}
 link ENG_NOUN:METALLURGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:металлургия {}
 link ENG_NOUN:METALLURGIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:металлург {}
 link ENG_NOUN:METALLOGRAPHY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:металлография {}
 link ENG_NOUN:METALANGUAGE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:метаязык {}
 link ENG_NOUN:METACENTRE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:метацентр {}
 link ENG_NOUN:METABOLISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:метаболизм {}
 link ENG_NOUN:MESSIAH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мессия {}
 link ENG_NOUN:MESOSPHERE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мезосфера {}
 link ENG_NOUN:MESON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мезон {}
 link ENG_NOUN:MESOMORPH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мезоморф {}
 link ENG_NOUN:MESODERM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мезодерма {}
 link ENG_NOUN:MESOBLAST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мезобласт {}
 link ENG_NOUN:MERLIN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мерлин {}
 link ENG_NOUN:MERCHANTMAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:торговец {}
 link ENG_NOUN:MENTHOL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ментол {}
 link ENG_NOUN:MENTALITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ментальность {}
 link ENG_NOUN:MENSTRUATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:менструация {}
 link ENG_NOUN:MENDELISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:менделизм {}
 link ENG_NOUN:MENDELEVIUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:менделевий {}
 link ENG_NOUN:MEMORANDUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:меморандум {}
 link ENG_NOUN:MEMBRANE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мембрана {}
 link ENG_NOUN:MEMBERSHIP {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:членство {}
 link ENG_NOUN:MELTDOWN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:проплавление {}
 link ENG_NOUN:MELON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:дыня {}
 link ENG_NOUN:MELODIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мелодист {}
 link ENG_NOUN:MELANIN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:меланин {}
 link ENG_NOUN:MELANCHOLIA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:меланхолия {}
 link ENG_NOUN:MEGAWATT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мегаватт {}
 link ENG_NOUN:MEGAVOLT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мегавольт {}
 link ENG_NOUN:MEGAPHONE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мегафон {}
 link ENG_NOUN:MEGALOMANIA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мегаломания {}
 link ENG_NOUN:MEGABYTE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мегабайт {}
 link ENG_NOUN:MEDUSA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:медуза {}
 link ENG_NOUN:MEDITATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:медитация {}
 link ENG_NOUN:MEDIA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:среда {}
 link ENG_NOUN:MEDAL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:медаль {}
 link ENG_NOUN:MEDALLIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:медалист {}
 link ENG_NOUN:MEDALLION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:медальон {}
 link ENG_NOUN:MECHANICS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:механика {}
 link ENG_NOUN:MECHANICIAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:механик {}
 link ENG_NOUN:MECCA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мекка {}
 link ENG_NOUN:MEASUREMENT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:измерение {}
 link ENG_NOUN:MEAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:средство {}
 link ENG_NOUN:MEANINGLESSNESS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:бессмыслица {}
 link ENG_NOUN:MEAL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:еда {}
 link ENG_NOUN:MAZURKA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мазурка {}
 link ENG_NOUN:MAZE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лабиринт {}
 link ENG_NOUN:MAZER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мазер {}
 link ENG_NOUN:MAYOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мэр {}
 link ENG_NOUN:MAYA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:майя {}
 link ENG_NOUN:MAXIMUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:максимум {}
 link ENG_NOUN:MAXIMALIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:максималист {}
 link ENG_NOUN:MAXIM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:максим {}
 link ENG_NOUN:MAUSOLEUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мавзолей {}
 link ENG_NOUN:MATURATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:созревание {}
 link ENG_NOUN:MATRIX {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:матрица {}
 link ENG_NOUN:MATRASS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:матрас {}
 link ENG_NOUN:MATHEMATICS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:математика {}
 link ENG_NOUN:MATHEMATICIAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:математик {}
 link ENG_NOUN:MATERIALITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:материальность {}
 link ENG_NOUN:MATERIALIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:материалист {}
 link ENG_NOUN:MATER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сущность {}
 link ENG_NOUN:MATADOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:матадор {}
 link ENG_NOUN:MASTIFF {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мастиф {}
 link ENG_NOUN:MASTERSHIP {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мастерство {}
 link ENG_NOUN:MASSAGE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:массаж {}
 link ENG_NOUN:MASOCHIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:масохист {}
 link ENG_NOUN:MASER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мазер {}
 link ENG_NOUN:MARZIPAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:марципан {}
 link ENG_NOUN:MARXISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:марксизм {}
 link ENG_NOUN:MARTIN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мартин {}
 link ENG_NOUN:MARTINI {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мартини {}
 link ENG_NOUN:MARTINIQUE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мартиника {}
 link ENG_NOUN:MARS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:марс {}
 link ENG_NOUN:MARMALADE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мармелад {}
 link ENG_NOUN:MARKER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:маркер {}
 link ENG_NOUN:MARIONETTE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:марионетка {}
 link ENG_NOUN:MARINA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:марина {}
 link ENG_NOUN:MARINADE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:маринад {}
 link ENG_NOUN:MARIJUANA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:марихуана {}
 link ENG_NOUN:MARGIN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:маржа {}
 link ENG_NOUN:MARGIN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:поле {}
 link ENG_NOUN:MARC {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:марк {}
 link ENG_NOUN:MARATHON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:марафон {}
 link ENG_NOUN:MARASMUS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:маразм {}
 link ENG_NOUN:MAOISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:маоизм {}
 link ENG_NOUN:MANUSCRIPT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:манускрипт {}
 link ENG_NOUN:MANUFACTURER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:изготовитель {}
 link ENG_NOUN:MANTRA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мантра {}
 link ENG_NOUN:MANTISSA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мантисса {}
 link ENG_NOUN:MANTA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:манта {}
 link ENG_NOUN:MANOEUVRE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:маневр {}
 link ENG_NOUN:MANNEQUIN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:манекен {}
 link ENG_NOUN:MANIPULATOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:манипулятор {}
 link ENG_NOUN:MANIPULATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:манипуляция {}
 link ENG_NOUN:MANILLA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:манилла {}
 link ENG_NOUN:MANIFESTO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:манифест {}
 link ENG_NOUN:MANIFESTATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:манифестация {}
 link ENG_NOUN:MANIA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мания {}
 link ENG_NOUN:MANHATTAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:манхэттен {}
 link ENG_NOUN:MANGO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:манго {}
 link ENG_NOUN:MANDRAGORA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мандрагора {}
 link ENG_NOUN:MANDATE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мандат {}
 link ENG_NOUN:MAMMON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:маммона {}
 link ENG_NOUN:MAMA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мама {}
 link ENG_NOUN:MALI {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мали {}
 link ENG_NOUN:MALFUNCTION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сбой {}
 link ENG_NOUN:MALE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:самец {}
 link ENG_NOUN:MALACHITE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:малахит {}
 link ENG_NOUN:MAKING {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:изготовление {}
 link ENG_NOUN:MAINTENANCE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:обслуживание {}
 link ENG_NOUN:MAINTAINABILITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:обслуживаемость {}
 link ENG_NOUN:MAINFRAME {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:миникомпьютер {}
 link ENG_NOUN:MAID {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:дева {}
 link ENG_NOUN:MAHATMA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:махатма {}
 link ENG_NOUN:MAHARISHI {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:махариши {}
 link ENG_NOUN:MAGNUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:магнум {}
 link ENG_NOUN:MAGNOLIA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:магнолия {}
 link ENG_NOUN:MAGNITUDE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:интенсивность {}
 link ENG_NOUN:MAGNET {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:магнит {}
 link ENG_NOUN:MAGNETRON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:магнетрон {}
 link ENG_NOUN:MAGNETOSPHERE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:магнитосфера {}
 link ENG_NOUN:MAGNETON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:магнетон {}
 link ENG_NOUN:MAGNETOMETER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:магнитометр {}
 link ENG_NOUN:MAGNETO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:магнето {}
 link ENG_NOUN:MAGNETITE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:магнетит {}
 link ENG_NOUN:MAGNETISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:магнетизм {}
 link ENG_NOUN:MAGNESIA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:магнезия {}
 link ENG_NOUN:MAGMA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:магма {}
 link ENG_NOUN:MAGISTRATE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:магистрат {}
 link ENG_NOUN:MAGICIAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:волшебник {}
 link ENG_NOUN:MAFIA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мафия {}
 link ENG_NOUN:MAESTRO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:маэстро {}
 link ENG_NOUN:MADWOMAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:дура {}
 link ENG_NOUN:MADONNA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мадонна {}
 link ENG_NOUN:MADMAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:дурак {}
 link ENG_NOUN:MADEMOISELLE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мадмуазель {}
 link FR_NOUN:MADEMOISELLE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мадмуазель {}
 link ENG_NOUN:MADEIRA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мадейра {}
 link FR_NOUN:MADAME {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мадам {}
 link ENG_NOUN:MAC {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:приятель {}
 link ENG_NOUN:MACROPHOTOGRAPHY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:макрофотография {}
 link ENG_NOUN:MACROPHAGE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:макрофаг {}
 link ENG_NOUN:MACROMOLECULE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:макромолекула {}
 link ENG_NOUN:MACROCOSM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:макрокосмос {}
 link ENG_NOUN:MACKINTOSH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:макинтош {}
 link ENG_NOUN:MACHETE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мачете {}
 link ENG_NOUN:MACAW {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:макао {}
 link ENG_NOUN:MACARONI {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:макароны {}
 link ENG_NOUN:LYSOSOME {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лизосома {}
 link ENG_NOUN:LYSIN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лизин {}
 link ENG_NOUN:LYNX {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:рысь {}
 link ENG_NOUN:LYMPH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лимфа {}
 link ENG_NOUN:LYMPHOCYTE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лимфоцит {}
 link ENG_NOUN:LYCRA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лайкра {}
 link ENG_NOUN:LYCOPODIUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ликоподий {}
 link ENG_NOUN:LUX {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:люкс {}
 link ENG_NOUN:LUXURY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:богатство {}
 link ENG_NOUN:LUXEMBOURG {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:люксембург {}
 link ENG_NOUN:LUTETIUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лютеций {}
 link ENG_NOUN:LUST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:похоть {}
 link ENG_NOUN:LUPUS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:волк {}
 link ENG_NOUN:LUMEN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:люмен {}
 link ENG_NOUN:LUGGAGE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:багаж {}
 link ENG_NOUN:LUFTWAFFE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:люфтваффе {}
 link ENG_NOUN:LUCIFER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:люцифер {}
 link ENG_NOUN:LOYALTY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лояльность {}
 link ENG_NOUN:LOUVRE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лувр {}
 link ENG_NOUN:LOTTO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лотто {}
 link ENG_NOUN:LOTTERY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лотерея {}
 link ENG_NOUN:LOSS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:потеря {}
 link ENG_NOUN:LOSER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:неудачник {}
 link ENG_NOUN:LOOP {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:цикл {}
 link ENG_NOUN:LOOK {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:взгляд {}
 link ENG_NOUN:LONDONER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лондонец {}
 link ENG_NOUN:LOMBARD {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ломбард {}
 link ENG_NOUN:LOGOTYPE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:логотип {}
 link ENG_NOUN:LOGISTICS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:логистика {}
 link ENG_NOUN:LOGGIA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лоджия {}
 link ENG_NOUN:LOGBOOK {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:журнал {}
 link ENG_NOUN:LOGARITHM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:логарифм {}
 link ENG_NOUN:LOCUS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:место {}
 link ENG_NOUN:LOCOMOTIVE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:локомотив {}
 link ENG_NOUN:LOCOMOTION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:движение {}
 link ENG_NOUN:LOCALE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:локаль {}
 link ENG_NOUN:LOBSTER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лобстер {}
 link ENG_NOUN:LOBOTOMY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лоботомия {}
 link ENG_NOUN:LOBBYIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лоббист {}
 link ENG_NOUN:LOADING {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:загрузка {}
 link ENG_NOUN:LIZARD {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ящерица {}
 link ENG_NOUN:LIVING {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:жизнь {}
 link ENG_NOUN:LITURGY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:литургия {}
 link ENG_NOUN:LITHUANIA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:литва {}
 link ENG_NOUN:LITHOSPHERE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:литосфера {}
 link ENG_NOUN:LITHOGRAPHY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:литография {}
 link ENG_NOUN:LITHIUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:литий {}
 link ENG_NOUN:LISP {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лисп {}
 link ENG_NOUN:LIRA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лира {}
 link ENG_NOUN:LIQUOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:жидкость {}
 link ENG_NOUN:LIQUIDATOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ликвидатор {}
 link ENG_NOUN:LIQUIDATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ликвидация {}
 link ENG_NOUN:LIQUEUR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ликер {}
 link ENG_NOUN:LIPOSOME {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:липосома {}
 link ENG_NOUN:LIPID {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:липид {}
 link ENG_NOUN:LINOLEUM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:линолеум {}
 link ENG_NOUN:LINKAGE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:связывание {}
 link ENG_NOUN:LINGUIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лингвист {}
 link ENG_NOUN:LIMOUSINE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лимузин {}
 link ENG_NOUN:LIMIT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лимит {}
 link ENG_NOUN:LILY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лили {}
 link ENG_NOUN:LIKENESSES {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:похожесть {}
 link ENG_NOUN:LIKELIHOOD {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:похожесть {}
 link ENG_NOUN:LIGHTING {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:освещение {}
 link ENG_NOUN:LIGATURE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лигатура {}
 link ENG_NOUN:LIEUTENANT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лейтенант {}
 link ENG_NOUN:LIBRETTO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:либретто {}
 link ENG_NOUN:LIBRETTIST {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:либреттист {}
 link ENG_NOUN:LIBRATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:либрация {}
 link ENG_NOUN:LIBIDO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:либидо {}
 link ENG_NOUN:LIAR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лжец {}
 link ENG_NOUN:LEXICON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лексикон {}
 link ENG_NOUN:LEXICOGRAPHY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лексикография {}
 link ENG_NOUN:LEXEME {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лексема {}
 link ENG_NOUN:LEVITATION {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:левитация {}
 link ENG_NOUN:LEVIATHAN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:левиафан {}
 link ENG_NOUN:LEUKAEMIA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лейкемия {}
 link ENG_NOUN:LEUCOCYTE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лейкоцит {}
 link ENG_NOUN:LESOTHO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лесото {}
 link ENG_NOUN:LESBIANISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лесбиянство {}
 link ENG_NOUN:LEO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лев {CharCasing:FirstCapitalized}
 link ENG_NOUN:LEONID {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:леонид {}
 link ENG_NOUN:LENS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:линза {}
 link ENG_NOUN:LENINISM {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ленинизм {}
 link ENG_NOUN:LENGTH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:длина {}
 link ENG_NOUN:LEMUR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лемур {}
 link ENG_NOUN:LEMONADE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лимонад {}
 link ENG_NOUN:LEMMA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лемма {}
 link ENG_NOUN:LEITMOTIV {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лейтмотив {}
 link ENG_NOUN:LEITMOTIF {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лейтмотив {}
 link ENG_NOUN:LEISURE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:отдых {}
 link ENG_NOUN:LEGO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лего {}
 link ENG_NOUN:LEGALITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:легальность {}
 link ENG_NOUN:LECITHIN {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лецитин {}
 link ENG_NOUN:LEARNING {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:изучение {}
 link ENG_NOUN:LEAGUE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лига {}
 link ENG_NOUN:LEADER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лидер {}
 link ENG_NOUN:LEADERSHIP {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лидерство {}
 link ENG_NOUN:LAZAR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лазарь {}
 link ENG_NOUN:LAYER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:слой {}
 link ENG_NOUN:LAWNMOWER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:газонокосильщик {}
 link ENG_NOUN:LAWMAKER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:законодатель {}
 link ENG_NOUN:LAWGIVER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:законодатель {}
 link ENG_NOUN:LAVA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лава {}
 link ENG_NOUN:LAUNCH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ланч {}
 link ENG_NOUN:LATEX {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:латекс {}
 link ENG_NOUN:LASSO {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лассо {}
 link ENG_NOUN:LARYNGOSCOPE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ларингоскоп {}
 link ENG_NOUN:LARYNGITIS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ларингит {}
 link ENG_NOUN:LARRY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ларри {}
 link ENG_NOUN:LAPTOP {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лэптоп {}
 link ENG_NOUN:LANTHANIDE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лантанид {}
 link ENG_NOUN:LANGOUSTE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лангуст {}
 link ENG_NOUN:LANDSCAPE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ландшафт {}
 link ENG_NOUN:LANDOWNER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:землевладелец {}
 link ENG_NOUN:LANDAU {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ландау {}
 link ENG_NOUN:LANCER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:кинжал {}
 link ENG_NOUN:LAMB {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ягненок {}
 link ENG_NOUN:LAMBERT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ламберт {}
 link ENG_NOUN:LAMBDA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лямбда {}
 link ENG_NOUN:LAGOON {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лагуна {}
 link ENG_NOUN:LABYRINTH {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лабиринт {}
 link ENG_NOUN:LABRADOR {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лабрадор {}
 link ENG_NOUN:LABOURER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:трудяга {}
 link ENG_NOUN:KVASS {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:квас {}

 link ENG_NOUN:HIRISHIMA {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:хиросима {}
 link ENG_ADJECTIVE:ZODIACAL {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:зодиакальный {}
 link ENG_ADJECTIVE:YUGOSLAV {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:югославский {}
 link ENG_ADJECTIVE:YEARLY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:ежегодный {}
 link ENG_ADJECTIVE:WRONGFUL {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:ошибочный {}
 link ENG_ADJECTIVE:WRONG {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:ошибочный {}
 link ENG_ADJECTIVE:WORLDWIDE {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:всемирный {}
 link ENG_ADJECTIVE:WORKABLE {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:работоспособный {}
 link ENG_ADJECTIVE:WOMANLY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:женский {}
 link ENG_ADJECTIVE:WOMANISH {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:женский {}
 link ENG_ADJECTIVE:WIRELESS {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:беспроводной {}
 link ENG_ADJECTIVE:WINDY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:ветренный {}
 link ENG_ADJECTIVE:WESTERN {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:западный {}
 link ENG_ADJECTIVE:WEIGHTLESS {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:невесомый {}
 link ENG_ADJECTIVE:WEEKLY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:еженедельный {}
 link ENG_ADJECTIVE:WASHABLE {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:моющийся {}
 link ENG_ADJECTIVE:VOLCANIC {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:вулканический {}
 link ENG_ADJECTIVE:VIRGINAL {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:девственный {}
 link ENG_ADJECTIVE:VIENNESE {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:венский {}
 link ENG_ADJECTIVE:VICTORIAN {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:викторианский {}
 link ENG_ADJECTIVE:VETERINARY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:ветеринарный {}
 link ENG_ADJECTIVE:VERY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:самый {}
 link ENG_ADJECTIVE:VENETIAN {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:венецианский {}
 link ENG_ADJECTIVE:VEGETABLE {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:овощной {}
 link ENG_ADJECTIVE:VARIABLE {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:изменяемый {}
 link ENG_ADJECTIVE:VARIABLE {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:разный {}
 link ENG_ADJECTIVE:VANDAL {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:вандальский {}
 link ENG_ADJECTIVE:VALUELESS {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:бесценный {}
 link ENG_ADJECTIVE:UTILE {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:полезный {}
 link ENG_ADJECTIVE:UNILINGUAL {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:одноязычный {}
 link ENG_ADJECTIVE:TYPEWRITTEN {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:напечатанный {}
 link ENG_ADJECTIVE:TRAUMATIC {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:травматический {}
 link ENG_ADJECTIVE:TRANSPARENT {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:транспарентный {}
 link ENG_ADJECTIVE:TRANSOCEANIC {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:трансокеанический {}
 link ENG_ADJECTIVE:TOTALITARIAN {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:тоталитарный {}
 link ENG_ADJECTIVE:THERMOPLASTIC {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:термопластичный {}
 link ENG_ADJECTIVE:THEATRICAL {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:театральный {}
 link ENG_ADJECTIVE:THEATRIC {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:театральный {}
 link ENG_ADJECTIVE:TALKATIVE {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:разговорчивый {}
 link ENG_ADJECTIVE:TACTLESS {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:бестактный {}
 link ENG_ADJECTIVE:SYNTHETIC {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:синтетический {}

 link ПРИЛАГАТЕЛЬНОЕ:АВАРИЙНЫЙ {} <to_english> ENG_ADJECTIVE:emergency {}
 link ENG_ADJECTIVE:ZEALOUS {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:ревностный {}
 link ENG_ADJECTIVE:YOUTHFUL {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:юношеский {}
 link ENG_ADJECTIVE:YEASTY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:дрожжевой {}
 link ENG_ADJECTIVE:WRY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:лукавый {}
 link ENG_ADJECTIVE:WRINKLY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:мятый {}
 link ENG_ADJECTIVE:WRINKLY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:сморщенный {}
 link ENG_ADJECTIVE:WRATHY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:гневный {}
 link ENG_ADJECTIVE:WRATHFUL {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:гневный {}
 link ENG_ADJECTIVE:WORTHY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:достойный {}
 link ENG_ADJECTIVE:WORTHWHILE {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:стоящий {}
 link ENG_ADJECTIVE:WORTHLESS {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:никчемный {}
 link ENG_ADJECTIVE:WORSHIPFUL {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:поклоняющийся {}
 link ENG_ADJECTIVE:WORRISOME {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:тревожный {}
 link ENG_ADJECTIVE:WORRISOME {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:беспокоящий {}
 link ENG_ADJECTIVE:WORMY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:червивый {}
 link ENG_ADJECTIVE:WORKMANLIKE {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:мастерский {}
 link ENG_ADJECTIVE:WORDY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:многословный {}
 link ENG_ADJECTIVE:WOOZY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:окосевший {}
 link ENG_ADJECTIVE:WOOLLY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:шерстяной {}
 link ENG_ADJECTIVE:WOOLLEN {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:шерстяной {}
 link ENG_ADJECTIVE:WOODY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:деревянный {}
 link ENG_ADJECTIVE:WONKY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:шаткий {}
 link ENG_ADJECTIVE:WOEFUL {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:печальный {}
 link ENG_ADJECTIVE:WOBBLY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:дрожащий {}
 link ENG_ADJECTIVE:WOBBLY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:шаткий {}
 link ПРЕДЛОГ:О {} <to_english> ENG_PREP:about {}
 link НАРЕЧИЕ:ТОЛЬКО {} <to_english> ENG_ADVERB:only {}
 link МЕСТОИМ_СУЩ:КТО {} <to_english> ENG_PARTICLE:who {}
 link ПРЕДЛОГ:ДЛЯ {} <to_english> ENG_PREP:for {}
 link НАРЕЧИЕ:УЖЕ {} <to_english> ENG_ADVERB:already {}
 link ЧАСТИЦА:ДА {} <to_english> ENG_PARTICLE:yes {}
 link ЧАСТИЦА:ДА {} <to_english> ENG_CONJ:and {}
 link ЧАСТИЦА:НЕТ {} <to_english> ENG_PARTICLE:not {}
 link ПРЕДЛОГ:ПЕРЕД {} <to_english> ENG_PREP:before {}
 link ЧАСТИЦА:ДАЖЕ {} <to_english> ENG_ADVERB:even {}
 link НАРЕЧИЕ:ГДЕ {} <to_english> ENG_ADVERB:where {}
 link ПРЕДЛОГ:ПОД {} <to_english> ENG_PREP:under {}
 link НАРЕЧИЕ:ТЕПЕРЬ {} <to_english> ENG_ADVERB:now {}
 link ПРЕДЛОГ:ВО {} <to_english> ENG_PREP:in {}
 link ПРЕДЛОГ:ВО {} <to_english> ENG_PREP:into {}
 link ПРИЛАГАТЕЛЬНОЕ:ОБА {} <to_english> ENG_ADJECTIVE:both {}
 link ПРЕДЛОГ:СО {} <to_english> ENG_PREP:with {}
 link ПРЕДЛОГ:С {} <to_english> ENG_PREP:with {}
 link НАРЕЧИЕ:ОЧЕНЬ {} <to_english> ENG_ADVERB:very {}
 link НАРЕЧИЕ:ТАМ {} <to_english> ENG_ADVERB:there {}
 link НАРЕЧИЕ:НИЧЕГО {} <to_english> ENG_ADVERB:nothing {}
 link НАРЕЧИЕ:ЗДЕСЬ {} <to_english> ENG_ADVERB:here {}
 link ПРИЛАГАТЕЛЬНОЕ:СЛЕДУЮЩИЙ {} <to_english> ENG_ADJECTIVE:next {}
 link ПРИЛАГАТЕЛЬНОЕ:СЛЕДУЮЩИЙ {} <to_english> ENG_ADJECTIVE:next {}
 link НАРЕЧИЕ:ТУТ {} <to_english> ENG_ADVERB:here {}
 link ПРЕДЛОГ:БЕЗ {} <to_english> ENG_PREP:without {}
 link НАРЕЧИЕ:БОЛЬШЕ {} <to_english> ENG_ADVERB:more {}
 link НАРЕЧИЕ:СЕЙЧАС {} <to_english> ENG_ADVERB:now {}
 link ПРЕДЛОГ:ЧЕРЕЗ {} <to_english> ENG_PREP:after {}
 link ПРИЛАГАТЕЛЬНОЕ:НЕКОТОРЫЙ {} <to_english> ENG_ADJECTIVE:some {}
 link ПРЕДЛОГ:ПОСЛЕ {} <to_english> ENG_PREP:after {}
 link НАРЕЧИЕ:ТОГДА {} <to_english> ENG_ADVERB:then {}
 link МЕСТОИМ_СУЩ:НИКТО {} <to_english> ENG_NOUN:nobody {}
 link ПРЕДЛОГ:НАД {} <to_english> ENG_PREP:over {}
 link СУЩЕСТВИТЕЛЬНОЕ:МЭРИ {} <to_english> ENG_NOUN:mary {}
 link ПРЕДЛОГ:ПЕРЕД {} <to_english> ENG_PREP:before {}
 link НАРЕЧИЕ:ПРОСТО {} <to_english> ENG_ADVERB:simply {}
 link НАРЕЧИЕ:ПОКА {} <to_english> ENG_ADVERB:still {}
 link НАРЕЧИЕ:СНОВА {} <to_english> ENG_ADVERB:again {}
 link НАРЕЧИЕ:ПОЧЕМУ {} <to_english> ENG_ADVERB:why {}
 link ИНФИНИТИВ:ПОЙТИ {} <to_english> ENG_VERB:go {}
 link ГЛАГОЛ:ПОЙТИ {} <to_english> ENG_VERB:go {}
 link СУЩЕСТВИТЕЛЬНОЕ:ГАРРИ {} <to_english> ENG_NOUN:harry {}
 link СОЮЗ:ХОТЯ {} <to_english> ENG_CONJ:but {}
 link ПРЕДЛОГ:ОБ {} <to_english> ENG_PREP:about {}
 link ПРЕДЛОГ:ОБ {} <to_english> ENG_PREP:of {}
 link НАРЕЧИЕ:БОЛЕЕ {} <to_english> ENG_ADVERB:more {}
 link НАРЕЧИЕ:НИКОГДА {} <to_english> ENG_ADVERB:never {}
 link НАРЕЧИЕ:ХОРОШО {} <to_english> ENG_ADVERB:well {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПАЛЬТО {} <to_english> ENG_NOUN:overcoat {}
 link ИНФИНИТИВ:ИМЕТЬ {} <to_english> ENG_VERB:have {}
 link ГЛАГОЛ:ИМЕТЬ {} <to_english> ENG_VERB:have {}
 link ПРИЛАГАТЕЛЬНОЕ:КРАЙНИЙ {} <to_english> ENG_ADJECTIVE:extreme {}
 link ПРЕДЛОГ:МЕЖДУ {} <to_english> ENG_PREP:between {}
 link НАРЕЧИЕ:КУДА {} <to_english> ENG_ADVERB:where {}
 link НАРЕЧИЕ:МНОГО {} <to_english> ENG_ADVERB:many {}
 link НАРЕЧИЕ:МНОГО {} <to_english> ENG_ADVERB:much {}
 link СОЮЗ:ОДНАКО {} <to_english> ENG_CONJ:but {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВЕСТЬ {} <to_english> ENG_NOUN:news {}
 link НАРЕЧИЕ:ИМЕННО {} <to_english> ENG_ADVERB:namely {}
 link НАРЕЧИЕ:ЗАТЕМ {} <to_english> ENG_ADVERB:then {}
 link НАРЕЧИЕ:ОПЯТЬ {} <to_english> ENG_ADVERB:again {}
 link НАРЕЧИЕ:ВМЕСТЕ {} <to_english> ENG_ADVERB:together {}
 link ГЛАГОЛ:ПРИЙТИ {} <to_english> ENG_VERB:come {}
 link ГЛАГОЛ:ПРИЙТИ {} <to_english> ENG_NOUN:come {}
 link МЕСТОИМ_СУЩ:НЕЧТО {} <to_english> ENG_NOUN:something {}
 link НАРЕЧИЕ:НАЗАД {} <to_english> ENG_ADVERB:back {}
 link НАРЕЧИЕ:БЫСТРО {} <to_english> ENG_ADVERB:fast {}
 link НАРЕЧИЕ:БЫСТРО {} <to_english> ENG_ADVERB:quickly {}
 link НАРЕЧИЕ:СЕГОДНЯ {} <to_english> ENG_ADVERB:today {}
 link НАРЕЧИЕ:ДОМА {} <to_english> ENG_NOUN:home {}
 link ПРИЛАГАТЕЛЬНОЕ:ЧЕЙ {} <to_english> ENG_PARTICLE:whose {}
 link ПРИЛАГАТЕЛЬНОЕ:ОСОБЕННЫЙ {} <to_english> ENG_ADJECTIVE:special {}
 link ГЛАГОЛ:НАЙТИ {} <to_english> ENG_VERB:find {}
 link ИНФИНИТИВ:НАЙТИ {} <to_english> ENG_VERB:find {}
 link НАРЕЧИЕ:ПРЯМО {} <to_english> ENG_ADVERB:directly {}
 link ПРИЛАГАТЕЛЬНОЕ:МОРСКОЙ {} <to_english> ENG_NOUN:sea {}
 link ПРИЛАГАТЕЛЬНОЕ:ДОВОЛЬНЫЙ {} <to_english> ENG_ADJECTIVE:satisfied {}
 link ПРИЛАГАТЕЛЬНОЕ:ДОВОЛЬНЫЙ {} <to_english> ENG_ADJECTIVE:contented {}
 link ПРИЛАГАТЕЛЬНОЕ: ДОВОЛЬНЫЙ {} <to_english> ENG_VERB:satisfy {}
 link НАРЕЧИЕ:ВОКРУГ {} <to_english> ENG_ADVERB:around {}
 link СУЩЕСТВИТЕЛЬНОЕ:КОМПАНИЯ {} <to_english> ENG_NOUN:company {}
 link ПРЕДЛОГ:КО {} <to_english> ENG_PREP:to {}
 link ПРИЛАГАТЕЛЬНОЕ:ДАННЫЙ {} <to_english> ENG_ADJECTIVE:this {}
 link НАРЕЧИЕ:ТОЧНО {} <to_english> ENG_ADVERB:exactly {}
 link ПРЕДЛОГ:СРЕДИ {} <to_english> ENG_PREP:among {}
 link ПРЕДЛОГ:ПРО {} <to_english> ENG_PREP:about {}
 link ПРЕДЛОГ:ПРО {} <to_english> ENG_PREP:of {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЛЬ {} <to_english> ENG_NOUN:paul {}
 link ИНФИНИТИВ:ОСТАВАТЬСЯ {} <to_english> ENG_VERB:stay {}
 link ГЛАГОЛ:ОСТАВАТЬСЯ {} <to_english> ENG_VERB:stay {}
 link НАРЕЧИЕ:СЮДА {} <to_english> ENG_ADVERB:here {}
 link НАРЕЧИЕ:ДОЛГО {} <to_english> ENG_ADJECTIVE:long {}
// link НАРЕЧИЕ:ДАЛЬШЕ {} <to_english> ENG_ADVERB:further {}
 link ПРИЛАГАТЕЛЬНОЕ:НЕОЖИДАННЫЙ {} <to_english> ENG_ADJECTIVE:unexpected {}
 link ПРИЛАГАТЕЛЬНОЕ:БЛИЖАЙШИЙ {} <to_english> ENG_ADJECTIVE:nearest {}
 link ПРИЛАГАТЕЛЬНОЕ:БЛИЖАЙШИЙ {} <to_english> ENG_ADJECTIVE:immediate {}
 link ПРИЛАГАТЕЛЬНОЕ:БЛИЖАЙШИЙ {} <to_english> ENG_ADJECTIVE:near {}
 link ПРИЛАГАТЕЛЬНОЕ:ДЕЙСТВИТЕЛЬНЫЙ {} <to_english> ENG_ADJECTIVE:real {}
 link ПРИЛАГАТЕЛЬНОЕ:ДЕЙСТВИТЕЛЬНЫЙ {} <to_english> ENG_ADJECTIVE:actual {}
 link ИНФИНИТИВ:УЙТИ {} <to_english> ENG_VERB:leave {}
 link ИНФИНИТИВ:УЙТИ {} <to_english> ENG_VERB:go {}
 link НАРЕЧИЕ:КАК {} <to_english> ENG_ADVERB:how {}
 link ПРЕДЛОГ:К {} <to_english> ENG_PREP:to {}
 link ПРЕДЛОГ:ИЗ {} <to_english> ENG_PREP:from {}
 link ПРЕДЛОГ:ЗА {} <to_english> ENG_PREP:for {}
 link НАРЕЧИЕ:ТАК {} <to_english> ENG_ADVERB:so {}
 link ПРЕДЛОГ:ОТ {} <to_english> ENG_PREP:from {}
 link ЧАСТИЦА:НЕТ {} <to_english> ENG_PARTICLE:not {}
 link ЧАСТИЦА:НЕТ {} <to_english> ENG_PARTICLE:no {}
 link НАРЕЧИЕ:СЛИШКОМ {} <to_english> ENG_ADVERB:too {}
 link СУЩЕСТВИТЕЛЬНОЕ:дите {} <to_english> ENG_NOUN:child {}
 link НАРЕЧИЕ:ПОЭТОМУ {} <to_english> ENG_ADVERB:so {}
 link НАРЕЧИЕ:ЗАЧЕМ {} <to_english> ENG_ADVERB:why {}
 link НАРЕЧИЕ:ТУДА {} <to_english> ENG_ADVERB:there {}
 link НАРЕЧИЕ:МЕДЛЕННО {} <to_english> ENG_ADVERB:slowly {}
 link НАРЕЧИЕ:ВОЗМОЖНО {} <to_english> ENG_ADVERB:possibly {}
 link НАРЕЧИЕ:ДЕЙСТВИТЕЛЬНО {} <to_english> ENG_ADVERB:really {}
 link ПРЕДЛОГ:ПРОТИВ {} <to_english> ENG_PREP:against {}
 link ИНФИНИТИВ:ВОЙТИ {} <to_english> ENG_VERB:enter {}
 link ГЛАГОЛ:ВОЙТИ {} <to_english> ENG_VERB:enter {}
 link ПРИЛАГАТЕЛЬНОЕ:НЕОБХОДИМЫЙ {} <to_english> ENG_ADJECTIVE:necessary {}
 link СУЩЕСТВИТЕЛЬНОЕ:СПОСОБНОСТЬ {} <to_english> ENG_NOUN:ability {}
 link СУЩЕСТВИТЕЛЬНОЕ:ОДЕЖДА {} <to_english> ENG_NOUN:cloth {}
 link СОЮЗ:ИБО {} <to_english> ENG_CONJ:because {}
 link ИНФИНИТИВ:ВСТАТЬ {} <to_english> ENG_VERB:stand {}
 link ГЛАГОЛ:ВСТАТЬ {} <to_english> ENG_VERB:stand {}
 link НАРЕЧИЕ:МАЛО {} <to_english> ENG_ADJECTIVE:few {}
 link ПРИЛАГАТЕЛЬНОЕ:ЕСТЕСТВЕННЫЙ {} <to_english> ENG_ADJECTIVE:natural {}
 link СУЩЕСТВИТЕЛЬНОЕ:ПОЛИЦЕЙСКИЙ {} <to_english> ENG_NOUN:policeman {}
 link ПРИЛАГАТЕЛЬНОЕ:ВЕРХНИЙ {} <to_english> ENG_ADJECTIVE:upper {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДЫХАНИЕ {} <to_english> ENG_NOUN:respiration {}
 link СУЩЕСТВИТЕЛЬНОЕ:ДЫХАНИЕ {} <to_english> ENG_NOUN:breathing {}
 link ПРИЛАГАТЕЛЬНОЕ:МЕСТНЫЙ {} <to_english> ENG_ADJECTIVE:local {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВОСПОМИНАНИЕ {} <to_english> ENG_NOUN:memory {}
 link СУЩЕСТВИТЕЛЬНОЕ:ВОСПОМИНАНИЕ {} <to_english> ENG_NOUN:recollection {}
 link ENG_ADJECTIVE:PROTECTIVE {} <в_сущ> ENG_NOUN:protection {}
 link ENG_ADJECTIVE:STAGNANT {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:стоячий {}
 link ENG_ADJECTIVE:STAGNANT {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:застойный {}
 link ENG_ADJECTIVE:SQUEAKY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:скрипящий {}
 link ENG_ADJECTIVE:SQUAT {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:приземистый {}
 link ENG_ADJECTIVE:SQUALID {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:убогий {}
 link ENG_ADJECTIVE:SQUALID {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:грязный {}
 link ENG_ADJECTIVE:SPRY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:бодрый {}
 link ENG_ADJECTIVE:SPRINGY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:упругий {}
 link ENG_ADJECTIVE:SPOTTY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:прыщавый {}
 link ENG_ADJECTIVE:SPORTY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:спортивный {}
 link ENG_ADJECTIVE:SPORADIC {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:спорадический {}
 link ENG_ADJECTIVE:SPOOKY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:зловещий {}
 link ENG_ADJECTIVE:SPOOKY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:жуткий {}
 link ENG_ADJECTIVE:SPONGY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:губчатый {}
 link ENG_ADJECTIVE:SPLENDID {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:великолепный {}
 link ENG_ADJECTIVE:SPITEFUL {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:злобный {}
 link ENG_ADJECTIVE:SPIRITUAL {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:духовный {}
 link ENG_ADJECTIVE:SPINDLY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:иголочный {}
 link ENG_ADJECTIVE:SPIKY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:колючий {}
 link ENG_ADJECTIVE:SPECTACULAR {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:впечатляющий {}
 link ENG_ADJECTIVE:SPECIFIC {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:определенный {}
 link ENG_ADJECTIVE:SPATIAL {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:пространственный {}
 link ENG_ADJECTIVE:SPASMODIC {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:спазматический {}
 link ENG_ADJECTIVE:SPACIOUS {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:просторный {}
 link ENG_ADJECTIVE:SOUTHERLY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:южный {}
 link ENG_ADJECTIVE:SORROWFUL {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:печальный {}
 link ENG_ADJECTIVE:SORREL {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:щавелевый {}
 link ENG_ADJECTIVE:SORE {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:обиженный {}
 link ENG_ADJECTIVE:SORDID {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:загаженный {}
 link ENG_ADJECTIVE:SORDID {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:гнусный {}
 link ENG_ADJECTIVE:SOLUBLE {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:растворимый {}
 link ENG_ADJECTIVE:SOLEMN {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:торжественный {}
 link ENG_ADJECTIVE:SOLE {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:единственный {}
 link ENG_ADJECTIVE:SOLE {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:исключительный {}
 link ENG_ADJECTIVE:SOGGY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:сырой {}
 link ENG_ADJECTIVE:SOGGY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:размокший {}
 link ENG_ADJECTIVE:SOBER {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:трезвый {}
 link ENG_ADJECTIVE:SOAPY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:мыльный {}
 link ENG_ADJECTIVE:SNUG {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:уютный {}
 link ENG_ADJECTIVE:SNOWY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:снежный {}
 link ENG_ADJECTIVE:SNOTTY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:сопливый {}
 link ENG_ADJECTIVE:SNOTTY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:наглый {}
 link ENG_ADJECTIVE:SNOOTY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:задиристый {}
 link ENG_ADJECTIVE:SNIDE {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:ехидный {}
 link ENG_ADJECTIVE:SNAZZY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:шикарный {}
 link ENG_ADJECTIVE:SNAPPY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:броский {}
 link ENG_ADJECTIVE:SMOKY {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:задымленный {}
 link ENG_ADJECTIVE:SMART {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:опрятный {}
 link ENG_ADJECTIVE:SMART {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:модный {}
 link ENG_ADJECTIVE:SMART {} <to_russian> ПРИЛАГАТЕЛЬНОЕ:толковый {}
 link ENG_NOUN:ANALOGUE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:аналог {}
 link ENG_NOUN:MORALITY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:мораль {}
 link ENG_NOUN:AMBIENCE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:атмосфера {}
 link ENG_NOUN:AGONY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:агония {}
 link ENG_NOUN:ADULT {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:взрослый {}
 link ENG_NOUN:ACCURACY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:точность {}
 link ENG_NOUN:ACCURACY {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:аккуратность {}
 link ENG_VERB:WARN {} <to_russian> ИНФИНИТИВ:предупреждать {}
 link ENG_NOUN:SURVIVAL {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:спасение {}
 link ENG_VERB:SURVIVE {} <to_russian> ИНФИНИТИВ:спастись {}
 link ENG_VERB:SUPPOSE {} <to_russian> ИНФИНИТИВ:предполагать {}
 link ENG_VERB:SUGGEST {} <to_russian> ИНФИНИТИВ:предлагать {}
 link ENG_VERB:SERVE {} <to_russian> ИНФИНИТИВ:служить {}
 link ENG_VERB:SEPARATE {} <to_russian> ИНФИНИТИВ:отделять {}
 link ENG_VERB:REQUIRE {} <to_russian> ИНФИНИТИВ:требовать {}
 link ENG_VERB:REMIND {} <to_russian> ИНФИНИТИВ:напоминать {}
 link ENG_NOUN:RELIEF {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:облегчение {}
 link ENG_VERB:RELAX {} <to_russian> ИНФИНИТИВ:отдыхать {}
 link ENG_VERB:REFUSE {} <to_russian> ИНФИНИТИВ:отказывать {}
 link ENG_VERB:REFLECT {} <to_russian> ИНФИНИТИВ:отражать {}
 link ENG_VERB:RECOGNIZE {} <to_russian> ИНФИНИТИВ:распознавать {}
 link ENG_VERB:PROVIDE {} <to_russian> ИНФИНИТИВ:обеспечивать {}
 link ENG_VERB:PRODUCE {} <to_russian> ИНФИНИТИВ:производить {}
 link ENG_VERB:PREVENT {} <to_russian> ИНФИНИТИВ:предотвращать {}
 link ENG_VERB:PRAY {} <to_russian> ИНФИНИТИВ:молиться {}
 link ENG_VERB:POSSESSE {} <to_russian> ИНФИНИТИВ:владеть {}
 link ENG_VERB:OCCUPY {} <to_russian> ИНФИНИТИВ:оккупировать {вид:несоверш}
 link ENG_VERB:OCCUPY {} <to_russian> ИНФИНИТИВ:занять {}
 link ENG_NOUN:OCCUPATION {} <to_russian> ИНФИНИТИВ:занятие {}
 link ENG_VERB:OBSERVE {} <to_russian> ИНФИНИТИВ:обозревать {}
 link ENG_NOUN:MOVE {} <to_russian> ИНФИНИТИВ:двигать {}
 link ENG_NOUN:MOVE {} <to_russian> ИНФИНИТИВ:двигаться {}
 link ENG_NOUN:MOVE {} <to_russian> ИНФИНИТИВ:перемещаться {}
 link ENG_NOUN:MOVE {} <to_russian> ИНФИНИТИВ:перемещать {}
 link ENG_VERB:MOVE {} <to_russian> ИНФИНИТИВ:перемещать {}
 link ENG_VERB:MOVE {} <to_russian> ИНФИНИТИВ:перемещаться {}
 link ENG_VERB:MOVE {} <to_russian> ИНФИНИТИВ:двигаться {}
 link ENG_VERB:MOVE {} <to_russian> ИНФИНИТИВ:двигать {}
 link ENG_NOUN:MEETING {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:встреча {}
 link ENG_NOUN:MARRIAGE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:женитьба {}
 link ENG_VERB:MARRY {} <to_russian> ИНФИНИТИВ:жениться {вид:несоверш}
 link ENG_VERB:MANAGE {} <to_russian> ИНФИНИТИВ:управлять {}
 link ENG_NOUN:LISTENER {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:слушатель {}
 link ENG_VERB:LIGHT {} <to_russian> ИНФИНИТИВ:освещать {}
 link ENG_VERB:LEARN {} <to_russian> ИНФИНИТИВ:изучать {}
 link ENG_VERB:LEARN {} <to_russian> ИНФИНИТИВ:учить {}
 link ENG_VERB:LAUGH {} <to_russian> ИНФИНИТИВ:смеяться {}
 link ENG_VERB:KILL {} <to_russian> ИНФИНИТИВ:убить {}
 link ENG_VERB:KILL {} <to_russian> ИНФИНИТИВ:убивать {}
 link ENG_VERB:INVOLVE {} <to_russian> ИНФИНИТИВ:вовлекать {}
 link ENG_VERB:INVOLVE {} <to_russian> ИНФИНИТИВ:вовлечь {}
 link ENG_VERB:INFORM {} <to_russian> ИНФИНИТИВ:информировать {}
 link ENG_VERB:INFORM {} <to_russian> ИНФИНИТИВ:проинформировать {}
 link ENG_VERB:INDICATE {} <to_russian> ИНФИНИТИВ:показывать {}
 link ENG_VERB:INDICATE {} <to_russian> ИНФИНИТИВ:отображать {}
 link ENG_VERB:INCLUDE {} <to_russian> ИНФИНИТИВ:включать {}
 link ENG_VERB:HUNT {} <to_russian> ИНФИНИТИВ:охотиться {}
 link ENG_VERB:HOPE {} <to_russian> ИНФИНИТИВ:надеяться {}
 link ENG_VERB:FOOLISH {} <to_russian> ИНФИНИТИВ:дурачить {}
 link ENG_VERB:FOOLISH {} <to_russian> ИНФИНИТИВ:дурачиться {}
 link ENG_VERB:FINISH {} <to_russian> ИНФИНИТИВ:заканчивать {}
 link ENG_VERB:FINISH {} <to_russian> ИНФИНИТИВ:заканчиваться {}
 link ENG_VERB:FINISH {} <to_russian> ИНФИНИТИВ:закончиться {}
 link ENG_VERB:FINISH {} <to_russian> ИНФИНИТИВ:закончить {}
 link ENG_VERB:FIGHT {} <to_russian> ИНФИНИТИВ:биться {}
 link ENG_VERB:FIGHT {} <to_russian> ИНФИНИТИВ:драться {}
 link ENG_VERB:EXTEND {} <to_russian> ИНФИНИТИВ:расширять {}
 link ENG_VERB:EXTEND {} <to_russian> ИНФИНИТИВ:расширить {}
 link ENG_VERB:EXPLODE {} <to_russian> ИНФИНИТИВ:взорваться {}
 link ENG_VERB:EXPLODE {} <to_russian> ИНФИНИТИВ:взрываться {}
 link ENG_VERB:EXPECT {} <to_russian> ИНФИНИТИВ:ожидать {}
 link ENG_VERB:EXIST {} <to_russian> ИНФИНИТИВ:существовать {}
 link ENG_VERB:EXCEPT {} <to_russian> ИНФИНИТИВ:исключать {}
 link ENG_VERB:ESCAPE {} <to_russian> ИНФИНИТИВ:убегать {}
 link ENG_VERB:DRIVE {} <to_russian> ИНФИНИТИВ:вести {}
 link ENG_VERB:DREAM {} <to_russian> ИНФИНИТИВ:мечтать {}
 link ENG_VERB:DISCOVER {} <to_russian> ИНФИНИТИВ:открывать {}
 link ENG_VERB:DESTROY {} <to_russian> ИНФИНИТИВ:разрушать {}
 link ENG_VERB:DESTROY {} <to_russian> ИНФИНИТИВ:разрушить {}
 link ENG_VERB:DESCRIBE {} <to_russian> ИНФИНИТИВ:описывать {}
 link ENG_VERB:DENY {} <to_russian> ИНФИНИТИВ:отказывать {}
 link ENG_VERB:DENY {} <to_russian> ИНФИНИТИВ:отказать {}
 link ENG_VERB:DELIVER {} <to_russian> ИНФИНИТИВ:доставлять {}
 link ENG_VERB:DELIVER {} <to_russian> ИНФИНИТИВ:доставить {}
 link ENG_VERB:DECLARE {} <to_russian> ИНФИНИТИВ:объявить {}
 link ENG_VERB:DECLARE {} <to_russian> ИНФИНИТИВ:объявлять {}
 link ENG_VERB:CREATE {} <to_russian> ИНФИНИТИВ:создать {}
 link ENG_VERB:CREATE {} <to_russian> ИНФИНИТИВ:создавать {}
 link ENG_VERB:COOL {} <to_russian> ИНФИНИТИВ:охлаждать {}
 link ENG_VERB:CONTAIN {} <to_russian> ИНФИНИТИВ:содержать {}
 link ENG_VERB:CONSIDER {} <to_russian> ИНФИНИТИВ:думать {}
 link ENG_VERB:CONSIDER {} <to_russian> ИНФИНИТИВ:размышлять {}
 link ENG_VERB:CONNECT {} <to_russian> ИНФИНИТИВ:соединить {}
 link ENG_VERB:CONNECT {} <to_russian> ИНФИНИТИВ:соединять {}
 link ENG_VERB:CONFUSE {} <to_russian> ИНФИНИТИВ:смущать {}
 link ENG_VERB:CONFUSE {} <to_russian> ИНФИНИТИВ:смутить {}
 link ENG_VERB:COLOR {} <to_russian> ИНФИНИТИВ:расцвечивать {}
 link ENG_VERB:COLOR {} <to_russian> ИНФИНИТИВ:расцветить {}
 link ENG_VERB:CLOSE {} <to_russian> ИНФИНИТИВ:закрыть {}
 link ENG_VERB:CLOSE {} <to_russian> ИНФИНИТИВ:закрывать {}
 link ENG_VERB:CLEAR {} <to_russian> ИНФИНИТИВ:очищать {}
 link ENG_VERB:CLEAR {} <to_russian> ИНФИНИТИВ:очистить {}
 link ENG_VERB:CLEAR {} <to_russian> ИНФИНИТИВ:прояснять {}
 link ENG_VERB:CLEAR {} <to_russian> ИНФИНИТИВ:прояснить {}
 link ENG_VERB:CHOOSE {} <to_russian> ИНФИНИТИВ:избирать {}
 link ENG_VERB:CHOOSE {} <to_russian> ИНФИНИТИВ:выбирать {}
 link ENG_VERB:CHOOSE {} <to_russian> ИНФИНИТИВ:выбрать {}
 link ENG_NOUN:CHOICE {} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:выбор {}
 link ENG_VERB:CHECK {} <to_russian> ИНФИНИТИВ:проверить {}
 link ENG_VERB:CHECK {} <to_russian> ИНФИНИТИВ:проверять {}
 link ENG_VERB:CENTER {} <to_russian> ИНФИНИТИВ:центрировать {}
 link ENG_VERB:CARRY {} <to_russian> ИНФИНИТИВ:нести {}
 link ENG_VERB:BELIEVE {} <to_russian> ИНФИНИТИВ:верить {}
 link ENG_VERB:BELIEVE {} <to_russian> ИНФИНИТИВ:полагать {}
 link ENG_VERB:ATTACH {} <to_russian> ИНФИНИТИВ:прикреплять {}
 link ENG_VERB:ATTACH {} <to_russian> ИНФИНИТИВ:прикрепить {}
 link ENG_VERB:ARRIVE {} <to_russian> ИНФИНИТИВ:прибывать {}
 link ENG_VERB:ARRANGE {} <to_russian> ИНФИНИТИВ:размещать {}
 link ENG_VERB:ARRANGE {} <to_russian> ИНФИНИТИВ:разместить {}
 link ENG_VERB:ALLOW {} <to_russian> ИНФИНИТИВ:разрешать {}
 link ENG_VERB:ALLOW {} <to_russian> ИНФИНИТИВ:разрешить {}
 link ENG_VERB:ALLOW {} <to_russian> ИНФИНИТИВ:дозволять {}
 link ENG_VERB:ALLOW {} <to_russian> ИНФИНИТИВ:дозволить {}
 link ENG_VERB:ALLOW {} <to_russian> ИНФИНИТИВ:позволять {}
 link ENG_VERB:ALLOW {} <to_russian> ИНФИНИТИВ:позволить {}
 link ENG_VERB:AGREE {} <to_russian> ИНФИНИТИВ:соглашаться {}
 link ENG_VERB:AGREE {} <to_russian> ИНФИНИТИВ:согласиться {}
 link ENG_VERB:AGREE {} <to_russian> ИНФИНИТИВ:соглашаться {}
 link ENG_VERB:ACCEPT {} <to_russian> ИНФИНИТИВ:принять {}
 link ENG_VERB:ACCEPT {} <to_russian> ИНФИНИТИВ:принимать {}
 link ENG_VERB:consente {} <to_russian> ИНФИНИТИВ:согласиться {}
 link ENG_VERB:consente {} <to_russian> ИНФИНИТИВ:соглашаться {}
 link ENG_VERB:wound {} <to_russian> ИНФИНИТИВ:ранить {}
 link ENG_VERB:gallop {} <to_russian> ИНФИНИТИВ:скакать {}
 link ENG_VERB:be about to {} <to_russian> ИНФИНИТИВ:собираться {}
 link ENG_VERB:rise up {} <to_russian> ИНФИНИТИВ:вставать {}

 link ENG_VERB:write{} <to_russian> ИНФИНИТИВ:писать { aux stress="пис^ать"}
 link ENG_VERB:chalk{} <to_russian> ИНФИНИТИВ:писать { aux stress="пис^ать"}
 link ENG_VERB:indite{} <to_russian> ИНФИНИТИВ:писать { aux stress="пис^ать"}
 link ENG_VERB:pen{} <to_russian> ИНФИНИТИВ:писать { aux stress="пис^ать"}

 link ENG_VERB:piss{} <to_russian> ИНФИНИТИВ:писать { aux stress="п^исать"}


 link complex "run over" <to_russian> { бегать по }



 link ENG_ADJECTIVE:unskillful{} <to_russian> прилагательное:неумелый{}
 link ENG_ADJECTIVE:skillful{} <to_russian> прилагательное:умелый{}
 link ENG_ADJECTIVE:willful{} <to_russian> прилагательное:своенравный{}
 link ENG_ADJECTIVE:server{} <to_russian> прилагательное:серверный{}


 link ENG_ADVERB:ONCE {} <to_russian> наречие:однажды {}
 link ENG_ADVERB:piteously {} <to_russian> наречие:жалобно {}
 link ENG_ADVERB:perpetually {} <to_russian> наречие:постоянно{}
 link ENG_ADVERB:lazily {} <to_russian> наречие:лениво{}
 link ENG_ADVERB:thoughtlessly{} <to_russian> наречие:бездумно{}
 link ENG_ADVERB:jocularly{} <to_russian> наречие:шутливо{}
 link ENG_ADVERB:terribly{} <to_russian> наречие:ужасно{}
 link ENG_NOUN:difficulty{} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:сложность {}
 link ENG_ADVERB:cheerfully{} <to_russian> наречие:радостно{}
 link ENG_ADVERB:considerably{} <to_russian> наречие:сравнительно{}
 link ENG_ADVERB:fiercely{} <to_russian> наречие:яростно{}
 link ENG_ADVERB:carelessly{} <to_russian> наречие:беззаботно{}
 link ENG_ADVERB:comfortably{} <to_russian> наречие:удобно{}
 link ENG_ADVERB:indignantly{} <to_russian> наречие:униженно{}
 link ENG_ADVERB:abundantly{} <to_russian> наречие:обильно{}
 link ENG_ADVERB:exultingly{} <to_russian> наречие:ликующе{}
 link ENG_ADVERB:resolutely{} <to_russian> наречие:твердо{}
 link ENG_ADVERB:successfully{} <to_russian> наречие:успешно{}
 link ENG_ADVERB:boastingly{} <to_russian> наречие:хвастливо{}
 link ENG_ADVERB:amazingly{}  <to_russian> наречие:удивленно{}
 link ENG_ADVERB:finally{} <to_russian> наречие:в конце концов{}
 link ENG_ADVERB:lately{} <to_russian> наречие:раньше{}
 link ENG_ADVERB:deceitfully{} <to_russian> наречие:лживо{}
 link ENG_ADVERB:unskillfully{} <to_russian> наречие:неумело{}
 link ENG_ADVERB:duly{} <to_russian> наречие:своевременно{}
 link ENG_ADVERB:lustily{} <to_russian> наречие:похотливо{}
 link ENG_ADVERB:all the time{} <to_russian> наречие:всегда{}
 link ENG_ADVERB:sharply{} <to_russian> наречие:резко{}
 link ENG_ADVERB:brightly{} <to_russian> наречие:ярко{}
 link ENG_ADVERB:modestly{} <to_russian> наречие:скромно{}
 link ENG_ADVERB:favorably{} <to_russian> наречие:благосклонно{}
 link ENG_ADVERB:unceasingly{} <to_russian> наречие:беспрерывно{}
 link ENG_ADVERB:sincerely{} <to_russian> наречие:искренне{}
 link ENG_ADVERB:cunningly{} <to_russian> наречие:хитро{}
 link ENG_ADVERB:fearfully{} <to_russian> наречие:испуганно{}
 link ENG_ADVERB:definitely{} <to_russian> наречие:несомненно{}
 link ENG_ADVERB:successfully{} <to_russian> наречие:успешно{}


 link ENG_NOUN:disputing{} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:спор {}
 link ENG_NOUN:acquaintance{} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:знакомство {}
 link ENG_NOUN:laborer{} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:рабочий {}
 link ENG_NOUN:outlay{} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:затрата {}
 link ENG_NOUN:boatman{} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лодочник {}
 link ENG_NOUN:timber{} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:древесина {}
 link ENG_NOUN:labor{} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:труд {}
 link ENG_NOUN:farmyard{} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ферма {}
 link ENG_NOUN:sheepdog{} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:овчарка {}
 link ENG_NOUN:hedgehog{} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:ёж {}
 link ENG_NOUN:vine{} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:лоза {}
 link ENG_NOUN:swiftness{} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:проворство {}
 link ENG_NOUN:marketplace{} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:базар {}

 link ENG_INTERJECTION:alas{} <to_russian> ЧАСТИЦА:УВЫ{} 

 link ENG_NOUN:Aethiop {}  <to_russian> существительное:эфиоп {}

 link ENG_NOUN:doggy{} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:собачка {}
 link ENG_NOUN:doggie{} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:собачка {}
 link ENG_NOUN:kitty{} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:кошечка {}
 link ENG_NOUN:kittie{} <to_russian> СУЩЕСТВИТЕЛЬНОЕ:кошечка {}
 link ENG_ADJECTIVE:kittenish{}  <to_russian> прилагательное:кошачий{} 
 link ENG_ADJECTIVE:doggish{}  <to_russian> прилагательное:собачий{} 

 LINK_NOUN(существительное,noun)
 LINK_NOUN(прилагательное,adjective)
 LINK_NOUN(союз,conjunction)
 LINK_ADJ(этот,this)
 LINK_ADJ(тот,that)
 LINK_ADJ(этот,these)
 LINK_ADJ(тот,those)
 LINK_ADJ(бездействующий, abeyant)
 
 LINK_NOUN( Аахен, Aachen )
 
 LINK_NOUN( show, шоу )
 LINK_NOUN( girl, девчонка )
 LINK_NOUN( woman, женщина )
 LINK_NOUN( warroir, воитель )
 LINK_NOUN( millenium, тысячелетие )
 LINK_NOUN( warroir, миллениум )
 LINK_NOUN( mouse, мышонок )
 LINK_NOUN( singer, певица )
 LINK_NOUN( picture, картинка )
 LINK_NOUN( image, изображение )
 LINK_NOUN( image, имидж )

 link СУЩЕСТВИТЕЛЬНОЕ:уран{ CharCasing:Lower } <to_english> ENG_NOUN:Uranium {}

 link ENG_VERB:listen in{} <to_russian> ИНФИНИТИВ:подслушивать {}
 link ENG_VERB:listen in{} <to_russian> ИНФИНИТИВ:подслушать {}
 link ENG_VERB:listen in{} <to_russian> ИНФИНИТИВ:послушать {}

 link eng_adjective:several{} <to_russian> наречие:несколько{}

 link ENG_VERB:need{} <to_russian> прилагательное:нужный {} // I need a rest = Мне нужен отдых
 link ENG_VERB:need{} <to_russian> прилагательное:необходимый {} // I need a rest = Мне необходим отдых

 LINK_VERB( hammer, забить )
 LINK_VERB( hammer, забивать )
 LINK_VERB( nail, пригвоздить )
 LINK_VERB( down, повалить )
 LINK_VERB( down, валить )
 LINK_VERB( borrow, занять )
 LINK_VERB( sing, попеть )
 LINK_VERB( view, посмотреть )
 LINK_VERB( stop, останавливать )
 LINK_VERB( stop, останавить )
 LINK_VERB( stop, заканчивать )
 LINK_VERB( stop, оканчивать )
 LINK_VERB( stop, прекратить )
 LINK_VERB( stop, прекратить )
 LINK_VERB( accelerate, ускорить )
 LINK_VERB( accelerate, убыстрять )
 LINK_VERB( accelerate, убыстрить )
 LINK_VERB( expose, демонстрировать )
 LINK_VERB( expose, продемонстрировать )
 LINK_VERB( minimize, уменьшить )
 LINK_VERB( minimize, уменьшать )
 LINK_VERB( minimize, преуменьшить )
 LINK_VERB( minimize, преуменьшать )
 LINK_VERB( maximize, максимизировать )
 LINK_VERB( maximize, увеличивать )
 LINK_VERB( fuck, ебать )
 LINK_VERB( fuck, выебать )
 LINK_VERB( fuck, трахать )
 LINK_VERB( fuck, трахать )
 LINK_VERB( suck, пососать )
 LINK_VERB( question, спросить )
 LINK_VERB( require, потребовать )
 

 LINK_PREP( в, in )
 LINK_PREP( на, in )
 LINK_PREP( в, to )
 LINK_PREP( во, to )
 LINK_PREP( к, to )
 LINK_PREP( о, to )
 LINK_PREP( на, on )
 LINK_PREP( на, at )
 LINK_PREP( в, at )
 LINK_PREP( во, at )
 LINK_PREP( под, under )
 LINK_PREP( подо, under )
 LINK_PREP( внутри, inside )
 LINK_PREP( в, inside )
 LINK_PREP( с, with )
 LINK_PREP( со, with )
 LINK_PREP( через, across )
 LINK_PREP( по, ascoss )
 LINK_PREP( над, over )
 LINK_PREP( надо, over )

/*
 LINK_PREP( ,  )
 LINK_PREP( ,  )
 LINK_PREP( ,  )
 LINK_PREP( ,  )
 LINK_PREP( ,  )
 LINK_PREP( ,  )
 LINK_PREP( ,  )
 LINK_PREP( ,  )
*/
 

 LINK_CONJ( и, and )
 LINK_CONJ( или, or )
 LINK_CONJ( ни, nor )
 LINK_CONJ( ни, neither )
 LINK_CONJ( и, and )
 LINK_CONJ( или, or )
 LINK_CONJ( либо, or )
 LINK_CONJ( или, either )
 LINK_CONJ( но, but )
 LINK_CONJ( если, if )
 LINK_CONJ( то, then )

/*
 LINK_CONJ( ,  )
 LINK_CONJ( ,  )
 LINK_CONJ( ,  )
 LINK_CONJ( ,  )
 LINK_CONJ( ,  )
 LINK_CONJ( ,  )
 LINK_CONJ( ,  )
 LINK_CONJ( ,  )
 LINK_CONJ( ,  )
*/

 
}
 
