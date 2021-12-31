#ifndef _NALUNIT_H_
#define _NALUNIT_H_

#include "Global.h"
#include "Utils.h"
#include "ErrorInfo.h"
#include "SeqParamSet.h"
#include "PicParamSet.h"
#include "I_Slice.h"

class CNALUnit
{
public:
    CNALUnit(UINT8	*pSODB, UINT32	SODBLength, UINT8 nalType);
    ~CNALUnit();

    int Parse_as_seq_param_set(CSeqParamSet *sps);
    int Parse_as_pic_param_set(CPicParamSet *pps);
    
    UINT8 *GET_SODB();

private:
    UINT8	*m_pSODB;
	UINT32	m_SODBLength;
	UINT8	m_nalType;
};

#endif