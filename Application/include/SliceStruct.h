#ifndef _SLICE_STRUCT_H_
#define _SLICE_STRUCT_H_

#include "Global.h"
#include "PicParamSet.h"
#include "SeqParamSet.h"
#include "SliceHeader.h"
#include "Macroblock.h"

#include <cstring>

class CSliceHeader;

class CSliceStruct
{
public:
    CSliceStruct(UINT8 *pSODB, CSeqParamSet *sps, CPicParamSet *pps, UINT8 nalType);
    ~CSliceStruct();

    UINT32 Parse();

    CSliceHeader *m_sliceHeader;

private:
    UINT8 *m_pSODB;
    UINT8 m_nalType;

    CSeqParamSet *m_sps_active;
    CPicParamSet *m_pps_active;
    UINT16 m_max_mb_number;
    CMacroblock **m_macroblocks;
};


#endif