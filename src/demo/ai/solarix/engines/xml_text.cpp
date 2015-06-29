#include <lem/config.h>

#if defined FAIND_IENGINES || defined DLL_EXPORTS

#include <lem/oformatter.h>
#include <lem/ustreams.h>
#include <lem/solarix/faind_internal.h>

using namespace Solarix;
using namespace lem;

XmlText::XmlText(void) : content(true)
{
 out = new OUFormatter( new lem::Char_Stream::UTF8_Reader( lem::Ptr<lem::Stream>(&content,null_deleter()) ), true );
}



XmlText::~XmlText(void)
{
 delete out;
}

int XmlText::GetChars( char *Buffer, int BufferSize )
{
 strncpy( Buffer, content.get_Block(), BufferSize );
 Buffer[BufferSize-1]=0;
 return std::min( (int)BufferSize-1, (int)GetLen() );
}

#endif
