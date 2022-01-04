#include "../include/Residual.h"
#include "../include/Macroblock.h"

using namespace std;

CResidual::CResidual(UINT8 *pSODB, UINT32 offset, CMacroblock *mb)
{
    m_macroblock_belongs = mb;
    m_pSODB = pSODB;
    m_byteOffset = offset / 8;
    m_bitOffset = offset % 8;
}

CResidual::~CResidual(){};

int CResidual::Parse_macroblock_residual()
{
    UINT8 cbp_luma = m_macroblock_belongs->m_cbp_luma;
    UINT8 cbp_chroma = m_macroblock_belongs->m_cbp_chroma;
    if(cbp_luma)
    {
        parse_luma_residual(cbp_luma);
    }

    return 0;
}

int CResidual::parse_luma_residual(UINT8 cbp_luma)
{
    int err = 0;
    int idx8x8 = 0, block_x = 0, block_y = 0, block_sub_idc_x = 0, block_sub_idc_y = 0;
    for(; block_y < 4; block_y += 2)
    {
        for(; block_x < 4; block_x += 2)
        {
            if(m_macroblock_belongs->Get_pps_active()->Get_entropy_coding_flag() == false)
            {
                // CAVLC
                for(block_sub_idc_y = block_y; block_sub_idc_y < block_y + 2; block_sub_idc_y ++)
                {
                    for(block_sub_idc_x = block_x; block_sub_idc_x < block_x + 2; block_sub_idc_x ++)
                    {
                        idx8x8 = 2 *(block_y / 2) + block_x / 2;
                        if(cbp_luma & (1<<idx8x8))
                        {
                            luma_residual[block_sub_idc_y][block_sub_idc_x].emptyBlock = false;
                            err = get_luma4x4_coeffs(block_sub_idc_x, block_sub_idc_y);
							if (err < 0)
							{
								return err;
							}
                        }
                        else
                        {
                            luma_residual[block_sub_idc_y][block_sub_idc_x].emptyBlock = true;
                        }
                    }
                }
            }
            else
            {
                //  CABAC
            }
        }
    }

    return 0;
}

int CResidual::get_luma4x4_coeffs(int block_sub_idc_x, int block_sub_idc_y)
{
    
}
