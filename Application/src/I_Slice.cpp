#include "../include/I_Slice.h"

I_Slice::I_Slice(UINT8 *pSODB, CSeqParamSet *sps, CPicParamSet *pps, UINT8 nalType)
{
    memset(this, 0, sizeof(I_Slice));
    m_pSODB = pSODB;
    m_sps_active = sps;
    m_pps_active = pps;
    m_nalType = nalType;
    m_max_mb_number = m_sps_active->Get_pic_width_in_mbs() * m_sps_active->Get_pic_height_in_mbs();
    m_macroblocks = new CMacroblock *[m_max_mb_number];
    memset(m_macroblocks, NULL, m_max_mb_number * sizeof(CMacroblock *));
}

I_Slice::~I_Slice(){
    if(m_sliceHeader)
    {
        delete m_sliceHeader;
        m_sliceHeader = NULL;
    }
    if(m_macroblocks)
    {
        for(int idx = 0; idx < m_max_mb_number; idx ++)
        {
            if(m_macroblocks[idx])
            {
                delete m_macroblocks[idx];
                m_macroblocks[idx] = NULL;
            }
        }
        delete m_macroblocks;
        m_macroblocks = NULL;
    }
}

UINT32 I_Slice::Parse()
{
    m_sliceHeader = new CSliceHeader(m_pSODB, m_sps_active, m_pps_active, m_nalType);
    m_sliceHeader->Parse_slice_header();
    m_sliceHeader->Dump_slice_header_info();

    UINT32 sliceHeaderLength = 0, macroblockOffset = 0;
    macroblockOffset = sliceHeaderLength = m_sliceHeader->Parse_slice_header();
    for(int idx=0; idx < m_max_mb_number; idx++)
    {
        m_macroblocks[idx] = new CMacroblock(m_pSODB, macroblockOffset);
        m_macroblocks[idx]->Set_pic_param_set(m_pps_active);
        macroblockOffset += m_macroblocks[idx]->Parse_macroblock();
        m_macroblocks[idx]->Dump_macroblock_info();
        break;
    }

    return 0;
}