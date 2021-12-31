#ifndef _STREAM_H_
#define _STREAM_H_

#include <cstdio>
#include <vector>

#include "Global.h"
#include "NAlUnit.h"
#include "Configuration.h"
#include "SeqParamSet.h"
#include "PicParamSet.h"
#include "I_Slice.h"

class CStreamFile
{
public:
    CStreamFile(char *filename);
    ~CStreamFile();
    void fileInfo();
    void fileError(int idx);

    int Parse_h264_bitstream();
    int find_nal_prefix();
    void ebsp_to_sodb();

    void dump_NAL_type(UINT8 nalType);

private:
    FILE *m_inputfile;
    char *m_filename;
    std::vector<UINT8> m_nalVec;

    CSeqParamSet *m_sps;
    CPicParamSet *m_pps;

    I_Slice *m_IDR_Slice;
};

#endif
