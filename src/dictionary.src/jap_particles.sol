// CD->08.03.2009
// LC->08.06.2009
// --------------

automat sg
{
 #define JapParticle(x) entry x : JAP_PARTICLE {}
 #define JapPostfix(x) entry x : JAP_PARTICLE {}

 JapParticle(も) // МО
 
 JapParticle(だ)

 // Отыменные послелоги
 JapPostfix(前) // (маэ) — перед
 JapPostfix(後) // (ато) — после
 JapPostfix(後ろ) // (усиро) — позади
 JapPostfix(上) // (уэ) — на
 JapPostfix(下) // (сита) — внизу, под
 JapPostfix(中) // (нака) — внутри
 JapPostfix(側) // (соба) — рядом
 JapPostfix(内) // (ути) — в
 JapPostfix(為) // (тамэ) — для
 JapPostfix(時) // (токи) — время

 JapPostfix(の下に) // – no shita ni – под
 JapPostfix(の上に) // – no ue ni – над, на, сверху на
 JapPostfix(の側に) // – no soba ni – рядом, возле
 JapPostfix(の前に) // – no mae ni – перед, впереди, ранее
 JapPostfix(の間に) // – no aida ni – между, среди
 JapPostfix(の中に) // – no naka ni – внутри, в

 
 JapParticle(ほうが) // для 男のほうが女より強いです。	Мужчины сильнее женщин.
 JapParticle(より) // для 男のほうが女より強いです。	Мужчины сильнее женщин.
 JapParticle(j_MORETHAN)
 
 JapParticle(なかで)
 JapParticle( 一番 )
 JapParticle(j_MOSTAMONG)

 
}
