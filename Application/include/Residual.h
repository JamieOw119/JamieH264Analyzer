#ifndef _RESIDUAL_H_
#define _RESIDUAL_H_

#include <cstring>
#include "Macroblock.h"
#include "Global.h"

typedef struct Coeff4x4Block
{
    bool emptyBlock;
    UINT16 coeffToken;
    UINT8 numCoeff;
    UINT8 trailingOnes;
    int trailingSign[3];
    int levels[16];
    UINT8 totalZeros;
    UINT8 runBefore[16];

    Coeff4x4Block()
    {
        emptyBlock = false;
        coeffToken = 0;
        numCoeff = 0;
        trailingOnes = 0;
        totalZeros = 0;
        bzero(trailingSign, sizeof(int)*3);
        bzero(levels, sizeof(int)*16);
        bzero(runBefore, sizeof(UINT8)*16);
    }
} Coeff4x4Block;

class CResidual
{
public:
    CResidual(UINT8 *pSODB, UINT32 offset, CMacroblock *mb);
    ~CResidual();

    int Parse_macroblock_residual();
private:
    CMacroblock *m_macroblock_belongs;
    UINT8 *m_pSODB;
    UINT32 m_byteOffset;
    UINT8 m_bitOffset; 

    Coeff4x4Block luma_residual[4][4];

    int parse_luma_residual(UINT8 cbp_luma);
    int get_luma4x4_coeffs(int block_idc_x, int block_idc_y);
};

#endif