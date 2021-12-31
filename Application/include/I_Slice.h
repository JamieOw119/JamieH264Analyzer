#ifndef _I_SLICE_H_
#define _I_SLICE_H_

#include "Global.h"
#include "PicParamSet.h"
#include "SeqParamSet.h"
#include "SliceHeader.h"
#include "Macroblock.h"

#include <cstring>

class CSliceHeader;

class I_Slice
{
public:
    I_Slice(UINT8 *pSODB, CSeqParamSet *sps, CPicParamSet *pps, UINT8 nalType);
    ~I_Slice();

    UINT32 Parse();

private:
    UINT8 *m_pSODB;
    UINT8 m_nalType;

    CSeqParamSet *m_sps_active;
    CPicParamSet *m_pps_active;
    
    CSliceHeader *m_sliceHeader;

    UINT16 m_max_mb_number;
    CMacroblock **m_macroblocks;
};


#endif