// -----------------------------------------------------------------------------
// File IO_MEMORY_STREAM.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// ���������� ������ MemStream � ��� �����������.
//
// ������ ��� ������ � ����������� ������. ������� ��� �������� ��������� �����
// ����� BaseSource<...> � ��� �������������� ��������� ����� OFormatter.
//
// 16.07.2006 - ����� ��������� ������ ����������� ������������ ���������, �����
//              ������� �������� �������� ������. 
// 29.11.2008 - ��������� ����� MemStream::string, ��������� ��������, �����������
//              ��-�� ����, ��� ���������� ����� �� ������� null terminated
//              �������, ������� ����������� FString ������� ��������������.
// -----------------------------------------------------------------------------
//
// CD->02.03.1996
// LC->06.11.2014
// --------------


#include <lem/config.h>

#include <stdlib.h>

#include <lem/macros.h>
#include <lem/path.h>
#include <lem/conversions.h>
#include <lem/streams.h>

using namespace lem;


MemStream::MemStream(void)
{
    block = NULL;
    w_block = NULL;
    cursor = step = size = occupied = 0;
    return;
}


MemStream::MemStream(
    char **Block,  // ��������� �� ��������� �� ���� ������.
                    // ���� (*Block)=NULL � ���������� ������
                    // � �����, �� ���� ����� ������ �����
                    // �������, � ����� ����� �� ������ ���������
                    // ������ ����� � ������ ���������� ���
                    // ����������� �������.
    bool for_read,  // �� ����� ������ ����� ������
    bool for_write, // � ���� ������ ����� ������
    size_t Size,    // ������ ����� ������ (���� ������ � �����, �� 0)
    size_t Step     // ��� ���������� ������� ����� (��� ������)
)
    :Stream()
{
    SetMode(for_read, for_write);
    allocatable = !(*Block);
    block = Block;
    w_block = NULL;
    cursor = 0;
    occupied = size = Size;
    step = Step;

    if (size == 0 && for_read && !for_write)
        size = lem_strlen(*Block);

    return;
}


// *****************************************************************************
// ��� ������ � ���� ������. ���� ������ ��������� � ����������� ����� �������,
// � ������� ��� ����� � ����� ������ �������� ��������� �� ���� ����, ������
// ����� ::string() ��� ::PickBlock()
// *****************************************************************************
MemStream::MemStream(bool /*for_write*/)
    :Stream()
{
    SetMode(true, true);
    allocatable = true;
    w_block = NULL;
    block = &w_block;
    cursor = occupied = 0;
    size = 0;
    step = 128;
    return;
}

MemStream::~MemStream(void)
{
    IFDEBUG(Assert());

    close();
    block = NULL;
    cursor = size = occupied = 0;
    allocatable = false;
    free(w_block);
    return;
}

// **************************************************************************
// ������������ ����, � ������� ����� ����� ������. �������� ��� ����������
// ���������� � ���������� ���, � ��� ����� �������� �� ���� �����.
// **************************************************************************
char* MemStream::PickBlock(void)
{
    IFDEBUG(Assert());

    LEM_CHECKIT_Z(allocatable);
    LEM_CHECKIT_Z(block != NULL);
    char *ptr = *block;
    block = NULL;
    w_block = NULL;
    size = 0;
    cursor = occupied = 0;
    return ptr;
}

void MemStream::close(void)
{
    IFDEBUG(Assert());
    allocatable = false;
}

// ************************************************************************
// ������ ������������� ����� ������ � �����. ���� ����� ��������� ��
// ������, � ������� ���� �������� �� �������, �� ���� ����������������.
// ������ ������������� ����������.
// ************************************************************************
void MemStream::write(const void *src, pos_type src_size)
{
    IFDEBUG(Assert());
    CheckWritable();

    if (src_size)
    {
        reallocate(cursor + src_size + 1);
        memcpy(&((*block)[cursor]), src, src_size);
        cursor += src_size;
        (*block)[cursor] = 0; // �� ������ ������ ��������� ���������� ������
        occupied = cursor;
    }

    IFDEBUG(Assert());
    return;
}


void MemStream::put(char ch)
{
    IFDEBUG(Assert());
    CheckWritable();

    if (cursor + 2 > size)
        reallocate();

    (*block)[cursor++] = static_cast<unsigned char>(ch);
    (*block)[cursor] = 0; // �� ������ ������ ��������� ���������� ������
    occupied = cursor;
    IFDEBUG(Assert());
    return;
}



// **********************************************************************
// ������ ���������� ���������� ������ �� ������. ��� ������ �� �������
// ����� ������ ���������� ����������.
//
// ������������ ����� ������� ������������� ������, �� ���� ����
// ���������� ��� ������ ����� ������ ������� �� ������� ��������
// ������ ������, �� �������� ����� ���������.
// **********************************************************************
Stream::pos_type MemStream::read(void *dest, size_t dest_size)
{
    IFDEBUG(Assert());

    CheckReadable();

    if (dest_size)
    {
        if (cursor + dest_size > occupied)
            dest_size = occupied - (cursor + dest_size);

        memcpy(dest, &((*block)[cursor]), dest_size);
    }

    IFDEBUG(Assert());
    return dest_size;
}

// **************************************************************************
// ���������� ���������� ����� �� ������. ���� ����� ����� ������ ���������,
// �� ����� ��������� EOF.
// **************************************************************************
int MemStream::get(void)
{
    IFDEBUG(Assert());
    CheckReadable();
    return cursor >= occupied ? EOF : (*block)[cursor++];
}



void MemStream::unget(char c)
{
    IFDEBUG(Assert());
    CheckReadable();
    if (cursor)
        cursor--;
}



void MemStream::SetReadable(void)
{
#if LEM_DEBUGGING==1
    Assert();
#endif

    SetMode(true, true);
    return;
}

bool MemStream::eof(void) const
{
#if LEM_DEBUGGING==1
    Assert();
#endif

    if (CanRead())
        return cursor >= occupied || cursor == lem::size_t_max;
    else
        return false;
}



// *******************************************************************
// ���������� ������� ����� ������ ��� ������ ��������� ������ ������.
// *******************************************************************
void MemStream::reallocate(void)
{
    IFDEBUG(Assert());
    LEM_CHECKIT_Z(allocatable);

    size += step;

    if (step < 32000000)
        step *= 2;

    char *new_block = (char*)realloc(*block, size);

    if (!new_block)
    {
        free_z(*block);
        size = 0;
        throw EMemFault(L"MemStream::reallocate fault");
    }

    *block = new_block;

    IFDEBUG(Assert());
    return;
}


void MemStream::reallocate(size_t new_size)
{
    IFDEBUG(Assert());
    LEM_CHECKIT_Z(allocatable);

    if (new_size <= size)
        return;

    if ((new_size - size) < step)
    {
        // ����� �������� �������� ��������� ������, �����������
        // ������ ������� ������.
        reallocate();
        return;
    }

    size = new_size;
    char *new_block = (char*)realloc(*block, size);

    if (!new_block)
    {
        free_z(*block);
        size = 0;
        throw EMemFault(L"MemStream::reallocate fault");
    }

    *block = new_block;

    IFDEBUG(Assert());
    return;
}

// *************************************************************************
// ��������� ������� (������� ������/������) � �������� ��������. ��������
// where_to - ������������� C-������� fseek.
// *************************************************************************
Stream::pos_type MemStream::seekp(off_type to, int whereto)
{
    IFDEBUG(Assert());
    switch (whereto)
    {
    case SEEK_SET:
        // ��������� � �������� ��������
        cursor = (size_t)to;
        break;

    case SEEK_CUR:
        // �������� ������ �� �������� �������� ������
        cursor += (size_t)to;
        break;

    case SEEK_END:
        LEM_STOPIT;
        break;
    }

    if (cursor >= occupied)
        return static_cast<pos_type>(-1);

    return 0;
}



void MemStream::Check(void) const
{
#if LEM_DEBUGGING==1
    Assert();
#endif
    LEM_CHECKIT_Z(*block != NULL);
    return;
}

void MemStream::flush(void)
{
#if LEM_DEBUGGING==1
    Assert();
#endif
}

void MemStream::clear(void)
{
#if LEM_DEBUGGING==1
    Assert();
#endif
    cursor = occupied = 0;
    return;
}

const FString MemStream::string(void) const
{
#if LEM_DEBUGGING==1
    Assert();
#endif
    if (block == NULL)
    {
        return FString();
    }
    else
    {
        return FString((const char*)*block, ((const char*)*block) + occupied);
    }
}

const char* MemStream::get_Block(void) const
{
#if LEM_DEBUGGING==1
    Assert();
#endif
    return block == NULL ? NULL : *block;
}

lem::Stream::pos_type MemStream::tellp(void) const
{
#if LEM_DEBUGGING==1
    Assert();
#endif
    return static_cast<pos_type>(cursor);
}


bool MemStream::move(lem::Stream::off_type offset)
{
#if LEM_DEBUGGING==1
    Assert();
#endif

    cursor += (size_t)offset;
    return cursor <= occupied;
}

lem::Stream::pos_type MemStream::fsize(void) const
{
#if LEM_DEBUGGING==1
    Assert();
#endif
    return occupied;
}


lem::FString MemStream::Hex() const
{
    lem::FString res;

    for (int i = 0; i < occupied; ++i)
    {
        lem::uint8_t b = (lem::uint8_t)((*block)[i]);
        res += lem::get_numerique((b >> 4) & 0x0f);
        res += lem::get_numerique(b & 0x0f);
    }

    return res;
}


// *****************************************************************

MemReadStream::MemReadStream(const char *rBlock)
    :MemStream()
{
    SetMode(true, false);
    rblock = rBlock;
    w_block = NULL;

    cursor = 0;

    if (rBlock == NULL)
        size = 0;
    else
        size = lem_strlen(rblock) + 1;

    occupied = size;

    return;
}


MemReadStream::MemReadStream(const void *rBlock, size_t Size)
    :MemStream()
{
    SetMode(true, false);
    rblock = (const char*)rBlock;
    w_block = NULL;

    cursor = 0;
    occupied = size = Size;

    if (rBlock == NULL)
    {
        LEM_CHECKIT_Z(size == 0);
        size = 0;
    }

    return;
}


Stream::pos_type MemReadStream::read(void *dest, pos_type dest_size)
{
    IFDEBUG(Assert());

    if (dest == NULL)
    {
        LEM_CHECKIT_Z(dest_size == 0);
        return 0;
    }

    if (rblock == NULL || cursor == lem::size_t_max)
    {
        memset(dest, 0, dest_size);
        return 0;
    }

    if (cursor + dest_size > size)
    {
        pos_type sz = size - cursor;

        memset(dest, 0, dest_size);

        if (sz > 0)
            memcpy(dest, rblock + cursor, sz);

        dest_size = sz;
    }
    else
    {
        memcpy(dest, rblock + cursor, dest_size);
    }

    cursor += dest_size;

    return dest_size;
}


int MemReadStream::get(void)
{
    IFDEBUG(Assert());
    return (cursor >= size || rblock == NULL) ? EOF : (0x00ff & rblock[cursor++]);
}

void MemReadStream::unget(char c)
{
    IFDEBUG(Assert());
    CheckReadable();
    if (cursor)
        cursor--;
}

// *************************************************************************
// ��������� ������� (������� ������/������) � �������� ��������. ��������
// where_to - ������������� C-������� fseek.
// *************************************************************************
Stream::pos_type MemReadStream::seekp(off_type to, int whereto)
{
    IFDEBUG(Assert());

    if (rblock == NULL || cursor == lem::size_t_max)
        return static_cast<pos_type>(-1);

    switch (whereto)
    {
    case SEEK_SET:
        // ��������� � �������� ��������
        cursor = (size_t)to;
        if (cursor >= size)
            cursor = size - 1;
        break;

    case SEEK_CUR:
        // �������� ������ �� �������� �������� ������
        cursor += (size_t)to;
        if (cursor >= size)
            cursor = size - 1;
        break;

    case SEEK_END:
        if (size)
            cursor = size - 1;

        break;
    }

    if (cursor >= occupied)
        return static_cast<pos_type>(-1);

    return cursor;
}


// -----------------------------


MemReadHexStream::MemReadHexStream(const char *HexData)
{
    LEM_CHECKIT_Z(HexData != NULL);

    size = strlen(HexData);
    block = new lem::uint8_t[size];

    for (int i = 0; i < size; ++i)
    {
        char c_hi = HexData[i * 2];
        char c_lo = HexData[i * 2 + 1];

        lem::uint8_t b8 = (lem::uint8_t)((lem::char_to_digit(c_hi) << 4) | lem::char_to_digit(c_lo));
        block[size] = b8;
    }

    cursor = 0;
}


MemReadHexStream::MemReadHexStream(const wchar_t *HexData)
{
    LEM_CHECKIT_Z(HexData != NULL);

    size = wcslen(HexData) / 2;
    block = new lem::uint8_t[size];

    for (int i = 0; i < size; ++i)
    {
        wchar_t c_hi = HexData[i * 2];
        wchar_t c_lo = HexData[i * 2 + 1];

        lem::uint8_t b8 = (lem::uint8_t)((lem::uchar_to_digit(c_hi) << 4) | lem::uchar_to_digit(c_lo));
        block[i] = b8;
    }

    cursor = 0;
}


MemReadHexStream::~MemReadHexStream()
{
    delete[] block;
}

bool MemReadHexStream::eof() const
{
    return cursor >= size;
}



lem::Stream::pos_type MemReadHexStream::read(void *dest, pos_type dest_size)
{
    if (dest == NULL)
    {
        LEM_CHECKIT_Z(dest_size == 0);
        return 0;
    }

    if (block == NULL || cursor == lem::size_t_max)
    {
        memset(dest, 0, dest_size);
        return 0;
    }

    if (cursor + dest_size > size)
    {
        pos_type sz = size - cursor;

        memset(dest, 0, dest_size);

        if (sz > 0)
            memcpy(dest, block + cursor, sz);

        dest_size = sz;
    }
    else
    {
        memcpy(dest, block + cursor, dest_size);
    }

    cursor += dest_size;

    return dest_size;
}


int MemReadHexStream::get()
{
    if (cursor >= size)
        return EOF;
    else
        return block[cursor++];
}


void MemReadHexStream::unget(char c)
{
    cursor--;
    LEM_CHECKIT_Z(cursor >= 0);
}


lem::Stream::pos_type MemReadHexStream::seekp(lem::Stream::off_type to, int whereto)
{
    switch (whereto)
    {
    case SEEK_SET:
        // ��������� � �������� ��������
        cursor = (size_t)to;
        if (cursor >= size)
            cursor = size - 1;
        break;

    case SEEK_CUR:
        // �������� ������ �� �������� �������� ������
        cursor += (size_t)to;
        if (cursor >= size)
            cursor = size - 1;
        break;

    case SEEK_END:
        if (size)
            cursor = size - 1;

        break;
    }

    // TODO ... ���. �������� ������ �� ������ ������� ...

    return cursor;
}

void MemReadHexStream::Check() const
{
    LEM_CHECKIT_Z(block != NULL);
    LEM_CHECKIT_Z(cursor >= 0 && cursor <= size);
    return;
}


bool MemReadHexStream::move(lem::Stream::off_type offset)
{
    cursor += offset;
    return cursor <= size;
}


