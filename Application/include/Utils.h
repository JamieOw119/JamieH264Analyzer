#ifndef _UTILS_H_
#define _UTILS_H_

#include "Global.h"

int Get_bit_at_position(UINT8 *buf, UINT32 &bytePosition, UINT8 &bitPosition);
int Get_uev_code_num(UINT8 *buf, UINT32 &bytePosition, UINT8 &bitPosition);
int Get_sev_code_num(UINT8 *buf, UINT32 &bytePosition, UINT8 &bitPosition);
int Get_mev_code_num(UINT8 *buf, UINT32 &bytePosition, UINT8 &bitPosition);
int Get_uint_code_num(UINT8 *buf, UINT32 &bytePosition, UINT8 &bitPosition, UINT8 length);
int Peek_uint_code_num(UINT8 *buf, UINT32 bytePosition, UINT8 bitPosition, UINT8 length);


#endif