#ifndef _MACROBLOCK_H_
#define _MACROBLOCK_H_

#include "Global.h"
#include "SeqParamSet.h"
#include "PicParamSet.h"
#include "Utils.h"
#include "Configuration.h"
#include "Residual.h"
#include "SliceStruct.h"
#include "Macroblock_defines.h"

typedef struct IntraPredStruct
{
    UINT8 block_mode;
    bool prev_intra_pred_mode_flag;
    UINT8 rem_intra_pred_mode;
    IntraPredStruct()
    {
        block_mode = 0;
        prev_intra_pred_mode_flag = false;
    }
} IntraPredStruct;

class CMacroblock
{
public:
    CMacroblock::CMacroblock(UINT8 *pSODB, UINT32 offset, UINT32 idx);
    ~CMacroblock();

    void Set_pic_param_set(CPicParamSet *pps);
    void Set_slice_struct(CSliceStruct *sliceStruct);
    UINT32 Parse_macroblock();
    
    CPicParamSet *Get_pps_active();
    
    void Dump_macroblock_info();


    UINT8  m_mb_type;
	UINT8  m_cbp_luma;
	UINT8  m_cbp_chroma;
	int  m_mb_qp;
	int  m_intra16x16PredMode;

private:
    UINT8 *m_pSODB;
    UINT32 m_mbDataSize;
    UINT32 m_byteOffset;
    UINT8 m_bitOffset;

    CPicParamSet *m_pps_active;
    CSliceStruct *m_slice;

    int m_mb_idx;
	bool m_transform_size_8x8_flag;

    IntraPredStruct *m_pred_struct;
    UINT8 m_intra_chroma_pred_mode;

	UINT8  m_coded_block_pattern;
	UINT8  m_mb_qp_delta;

    CResidual *m_residual;

    void interpret_mb_mode();
};

#endif
