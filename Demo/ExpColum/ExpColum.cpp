#include <iostream>
#include <assert.h>
using namespace std;

typedef unsigned char UINT8; 

static UINT8 get_bit_at_position(UINT8 *buf, UINT8 &bytePosition, UINT8 &bitPosition)
{
    UINT8 mask = 1<<(7-bitPosition);
    UINT8 ret = ((buf[bytePosition] & mask) != 0);
    if(++bitPosition > 7)
    {
        bytePosition++;
        bitPosition = 0;
    }
    return ret;
}

// codenum = 2^LeadingZeroBits - 1 + XXX
static int get_uev_code_num(UINT8 *buf, UINT8 &bytePosition, UINT8 &bitPosition)
{
    assert(bitPosition < 8);
    UINT8 val = 0, prefixZeroCount = 0;
    int prefix = 0, suffix = 0;

    while(true)
    {
        val = get_bit_at_position(buf, bytePosition, bitPosition);
        if(val == 0)
        {
            prefixZeroCount++;
        }
        else
        {
            break;
        }
    }
    prefix = (1<<prefixZeroCount)-1;
    for(int i = 0; i < prefixZeroCount; i++)
    {
        val = get_bit_at_position(buf, bytePosition, bitPosition);
        suffix += val * (1 << (prefixZeroCount - i - 1));
    }
    return prefix + suffix;
}


int main(int argc, char const *argv[])
{
    UINT8 strArray[6] = {0xA6, 0x42, 0x98, 0xE2, 0x04, 0x8A};

    UINT8 bytePosition = 0;
    UINT8 bitPosition  = 0;
    UINT8 dataLengthInBits = sizeof(strArray) * 8;

    int codeNum = 0;
    while((bytePosition * 8 + bitPosition) < dataLengthInBits)
    {
        codeNum = get_uev_code_num(strArray, bytePosition, bitPosition);
        cout<<"ExpoColumb codeNum = "<<codeNum<<endl;
    }

    return 0;
}
