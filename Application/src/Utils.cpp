#include <assert.h>

#include "Utils.h"


int Get_bit_at_position(UINT8 *buf, UINT32 &bytePosition, UINT8 &bitPosition)
{
	UINT8 mask = 0, val = 0;

	mask = 1 << (7 - bitPosition);
	val = ((buf[bytePosition] & mask) != 0);
	if (++bitPosition > 7)
	{
		bytePosition++;
		bitPosition = 0;
	}

	return val;
}

int Get_uev_code_num(UINT8 *buf, UINT32 &bytePosition, UINT8 &bitPosition)
{
	assert(bitPosition < 8);
	UINT8 val = 0, prefixZeroCount = 0;
	int prefix = 0, surfix = 0;

	while (true)
	{
		val = Get_bit_at_position(buf, bytePosition, bitPosition);
		if (val == 0)
		{
			prefixZeroCount++;
		}
		else
		{
			break;
		}
	}
	prefix = (1 << prefixZeroCount) - 1;
	for (int i = 0; i < prefixZeroCount; i++)
	{
		val = Get_bit_at_position(buf, bytePosition, bitPosition);
		surfix += val * (1 << (prefixZeroCount - i - 1));
	}

	prefix += surfix;

	return prefix;
}

int Get_sev_code_num(UINT8 *buf, UINT32 &bytePosition, UINT8 &bitPosition)
{
	int uev = Get_uev_code_num(buf, bytePosition, bitPosition);
	int sign = (uev % 2) ? 1 : -1;
	int sev = sign * ((uev + 1) >> 1);
	
	return sev;
}

int Get_uint_code_num(UINT8 *buf, UINT32 &bytePosition, UINT8 &bitPosition, UINT8 length)
{
	UINT32 uVal = 0;

	for (int idx = 0; idx < length; idx++)
	{
		uVal += Get_bit_at_position(buf, bytePosition, bitPosition) << (length - idx - 1);
	}

	return uVal;
}

int Peek_uint_code_num(UINT8 *buf, UINT32 bytePosition, UINT8 bitPosition, UINT8 length)
{
	UINT32 uVal = 0;

	for (int idx = 0; idx < length; idx++)
	{
		uVal += Get_bit_at_position(buf, bytePosition, bitPosition) << (length - idx - 1);
	}

	return uVal;
}