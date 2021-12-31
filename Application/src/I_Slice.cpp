#include "../include/I_Slice.h"

I_Slice::I_Slice(UINT8 *pSODB, CSeqParamSet *sps, CPicParamSet *pps, UINT8 nalType)
{
    memset(this, 0, sizeof(I_Slice));
    m_pSODB = pSODB;
    m_sps_active = sps;
    m_pps_active = pps;
    m_nalType = nalType;
}

I_Slice::~I_Slice(){
    if(m_sliceHeader)
    {
        delete m_sliceHeader;
        m_sliceHeader = NULL;
    }
}

UINT32 I_Slice::Parse()
{
    m_sliceHeader = new CSliceHeader(m_pSODB, m_sps_active, m_pps_active, m_nalType);
    m_sliceHeader->Parse_slice_header();
    m_sliceHeader->Dump_slice_header_info();
    return 0;
}