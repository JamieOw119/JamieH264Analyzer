#ifndef _SLICE_STRUCT_H_
#define _SLICE_STRUCT_H_

#include <cstring>

#include "Global.h"
#include "PicParamSet.h"
#include "SeqParamSet.h"
#include "SliceHeader.h"
#include "Macroblock.h"

class CSliceStruct
{
public:
	CSliceStruct(UINT8	*pSODB, CSeqParamSet *sps, CPicParamSet *pps, UINT8	nalType, UINT32 sliceIdx);
	~CSliceStruct();

	int Parse();
	CMacroblock *Get_macroblock_at_index(int mbIdx);

	CSliceHeader *m_sliceHeader;
    CSeqParamSet *m_sps_active;
	CPicParamSet *m_pps_active;

private:
	UINT8	*m_pSODB;
	UINT8   m_nalType;
	UINT32  m_sliceIdx;

	UINT16 m_max_mb_number;
	CMacroblock **m_macroblocks;
};


#endif