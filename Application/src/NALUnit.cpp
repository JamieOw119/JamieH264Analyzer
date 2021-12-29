#include "../include/NAlUnit.h"
#include "../include/global.h"

CNALUnit::CNALUnit(uint8 *pSODB, uint32 SODBlength)
{
    _pSODB = pSODB;
    _SODBlength = SODBlength;
}

CNALUnit::~CNALUnit(){}