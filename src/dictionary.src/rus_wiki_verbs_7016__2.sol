 #define v7016(Name) \
  #begin
   extern entry Name : ИНФИНИТИВ
   entry Name:ГЛАГОЛ
   {
    paradigm Глагол_7016
   }
  link ГЛАГОЛ : Name {}  <в_инфинитив> ИНФИНИТИВ : Name {}
  #end

automat sg
{
v7016(подсуропить)
v7016(забэкапить)
v7016(отфотошопить)
v7016(заапрувить)
v7016(отфотожопить)
}

