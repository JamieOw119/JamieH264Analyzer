#include "../include/Stream.h"

int main(int argc, char const *argv[])
{
    CStreamFile h264Stream(const_cast<char *>(argv[1]));
    h264Stream.Parse_h264_bitstream();
    return 0;
}
