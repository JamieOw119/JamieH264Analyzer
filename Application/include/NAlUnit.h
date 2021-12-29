#ifndef _NALUNIT_H_
#define _NALUNIT_H_

#include "global.h"

class CNALUnit
{
public:
    CNALUnit(uint8 *pSODB, uint32 SODBlength);
    ~CNALUnit();
private:
    uint8 *_pSODB;
    uint32 _SODBlength;
};

#endif