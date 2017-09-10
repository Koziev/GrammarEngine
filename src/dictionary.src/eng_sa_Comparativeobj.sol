// Оборот с компаративом.
patterns ComparativeObj export { node:root_node }

pattern ComparativeObj
{
 PronounGroup : export { node:root_node }
}

patterns NounGroup { language=English } export { NUMBER node:root_node }

pattern ComparativeObj
{
 NounGroup : export { node:root_node }
}
