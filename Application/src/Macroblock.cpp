#include "../include/Macroblock.h"

using namespace std;

CMacroblock::CMacroblock(UINT8 *pSODB, UINT32 offset)
{
    m_pSODB = pSODB;
    m_byteOffset = offset / 8;
    m_bitOffset = offset % 8;

    m_pps_active = NULL;
    m_mb_type = 0;
    m_transform_size_8x8_flag = false;
    m_pred_struct = NULL;
    m_intra_chroma_pred_mode = 0;
    m_coded_block_pattern = 0;
    m_mb_qp_delta = 0;
}

CMacroblock::~CMacroblock(){}

void CMacroblock::Set_pic_param_set(CPicParamSet *pps)
{
    m_pps_active = pps;
}

UINT32 CMacroblock::Parse_macroblock()
{
    UINT32 macroblockLength = 0;
    m_mb_type = Get_uev_code_num(m_pSODB, m_byteOffset, m_bitOffset);
    if(m_mb_type == 25)
    {
        // I-PCM MODE;
    }
    else if(m_mb_type == 0)
    {
        if (m_pps_active->Get_transform_8x8_mode_flag())
		{
			m_transform_size_8x8_flag = Get_bit_at_position(m_pSODB, m_byteOffset, m_bitOffset);
		}
        if (m_transform_size_8x8_flag)
		{
			// Using intra_8x8
			m_pred_struct = new IntraPredStruct[4];	
			for (int luma8x8BlkIdx = 0; luma8x8BlkIdx < 4; luma8x8BlkIdx++)
			{
				m_pred_struct[luma8x8BlkIdx].block_mode = 1;
				m_pred_struct[luma8x8BlkIdx].prev_intra_pred_mode_flag = Get_bit_at_position(m_pSODB, m_byteOffset, m_bitOffset);
				if (!m_pred_struct[luma8x8BlkIdx].prev_intra_pred_mode_flag)
				{
					m_pred_struct[luma8x8BlkIdx].rem_intra_pred_mode = Get_uint_code_num(m_pSODB, m_byteOffset, m_bitOffset, 3);
				}
			}
		} 
        else
		{
			// Using intra_4x4
			m_pred_struct = new IntraPredStruct[16];
			for (int luma4x4BlkIdx = 0; luma4x4BlkIdx < 16; luma4x4BlkIdx++)
			{
				m_pred_struct[luma4x4BlkIdx].block_mode = 0;
				m_pred_struct[luma4x4BlkIdx].prev_intra_pred_mode_flag = Get_bit_at_position(m_pSODB, m_byteOffset, m_bitOffset);
				if (!m_pred_struct[luma4x4BlkIdx].prev_intra_pred_mode_flag)
				{
					m_pred_struct[luma4x4BlkIdx].rem_intra_pred_mode = Get_uint_code_num(m_pSODB, m_byteOffset, m_bitOffset, 3);
				}
			}
		}
        m_intra_chroma_pred_mode = Get_uev_code_num(m_pSODB, m_byteOffset, m_bitOffset);
    }
    else
    {
        // To do: Intra_16x16 mode
    }

    if (m_mb_type == 0 || m_mb_type == 25)
	{
		m_coded_block_pattern = Get_mev_code_num(m_pSODB, m_byteOffset, m_bitOffset);
        m_cbp_luma = m_coded_block_pattern % 16;
        m_cbp_chroma = m_coded_block_pattern / 16;
	}

    if (m_cbp_luma > 0 || m_cbp_chroma > 0 || (m_mb_type > 0 && m_mb_type < 25))
	{
		m_mb_qp_delta = Get_sev_code_num(m_pSODB, m_byteOffset, m_bitOffset);
	}

    return macroblockLength;
}

void CMacroblock::Dump_macroblock_info()
{
#if TRACE_CONFIG_LOGOUT

#if TRACE_CONFIG_MACROBLOCK
	g_traceFile << "mb_type: " << to_string(m_mb_type) << endl;
	if (m_mb_type == 0)
	{
		if (!m_transform_size_8x8_flag)
		{
			for (int idx = 0; idx < 16; idx++)
			{
				g_traceFile << "prev_intra4x4_pred_mode_flag: " << m_pred_struct[idx].prev_intra_pred_mode_flag << endl;
				if (!m_pred_struct[idx].prev_intra_pred_mode_flag)
				{
					g_traceFile << "rem_intra4x4_pred_mode: " << to_string(m_pred_struct[idx].rem_intra_pred_mode) << endl;
				}
			}
		}
	}

	g_traceFile << "intra_chroma_pred_mode: " << to_string(m_intra_chroma_pred_mode) << endl;
	if (m_mb_type == 0 || m_mb_type == 25)
	{
		g_traceFile << "coded_block_pattern: " << to_string(m_coded_block_pattern) << endl;
	}
	g_traceFile << "mb_qp_delta: " << to_string(m_mb_qp_delta) << endl;
#endif

#endif
}