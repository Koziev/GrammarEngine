// LC->09.02.2011

automat sg
{
 #define Antonym( A, B ) \
  #begin
   extern entry A:НАРЕЧИЕ
   extern entry B:НАРЕЧИЕ
   link НАРЕЧИЕ:A{} <antonym> НАРЕЧИЕ:B{}
  #end

 Antonym( много, мало )
 Antonym( высоко, низко )
 Antonym( громко, тихо )
 Antonym( внутри, снаружи )
 Antonym( сильно, слабо )
 Antonym( быстро, медленно )
 Antonym( горячо, холодно )
 Antonym( ярко, тускло )
 Antonym( агрессивно, миролюбиво )
 Antonym( прозрачно, непрозрачно )
 Antonym( красиво, уродливо )
 Antonym( ласково, неласково )
 Antonym( ласково, грубо )
 Antonym( активно, пассивно )
 Antonym( инициативно, безынициативно )
 Antonym( смело, трусливо )
 Antonym( разумно, неразумно )
 Antonym( спокойно, неспокойно )
 Antonym( просто, сложно )
 Antonym( хуёво, пиздато )
 Antonym( понятно, непонятно )
 Antonym( безрассудно, рассудительно )
 Antonym( хитро, бесхитростно )
 Antonym( чисто, грязно )
 Antonym( опасно, безопасно )
 Antonym( весело, грустно )
 Antonym( широко, узко )
 Antonym( тяжело, легко )
 Antonym( шумно, тихо )
 Antonym( сложно, легко )

 link НАРЕЧИЕ:ненакладно{} <antonym> НАРЕЧИЕ:накладно{}
 link НАРЕЧИЕ:неузнаваемо{} <antonym> НАРЕЧИЕ:узнаваемо{} 
}
