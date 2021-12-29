#ifndef _STREAM_H_
#define _STREAM_H_

#include <cstdio>
#include <vector>

#include "global.h"

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

private:
    FILE *_inputfile;
    char *_filename;
    std::vector<uint8> _nalBytes;

};

#endif
