#include <iostream>

#include "../include/stream.h"
#include "../include/global.h"
#include "../include/NAlUnit.h"

using namespace std;

CStreamFile::CStreamFile(char *filename)
{
    _filename = filename;
    _inputfile = fopen(filename, "r");   
    if(!_inputfile)
    {
        fileError(0);
    }
    fileInfo();
}

CStreamFile::~CStreamFile()
{
    if(_inputfile)
    {
        fclose(_inputfile);
        _inputfile = nullptr;
    }
}

void CStreamFile::fileInfo()
{
    if(_filename)
    {
        cout<<"Filename: "<<_filename<<endl;
    }
}

void CStreamFile::fileError(int idx)
{
    switch (idx)
    {
    case 0:
        cout<<"Error: opening input file failed."<<endl;
        break;
    
    default:
        break;
    }
}

int CStreamFile::Parse_h264_bitstream()
{
    int ret = 0;
    do
    {
        ret = find_nal_prefix();
        if(_nalBytes.size())
        {
            cout<<"NAL Unit Type: "<<(_nalBytes[0] & 0x1F)<<endl;
            ebsp_to_sodb();
            CNALUnit nalUnit(&_nalBytes[1], _nalBytes.size()-1);
        }
    } while (ret);
    return ret;
}

int CStreamFile::find_nal_prefix()
{
    uint8 prefix[3] = {0};
    uint8 fileByte;
    int pos = 0;
    int getPrefix = 0;

    _nalBytes.clear();

    for(int idx = 0; idx < 3; idx++)
    {
        prefix[idx] = getc(_inputfile);
        _nalBytes.push_back(prefix[idx]);
    }
    while(!feof(_inputfile))
    {
        // 0x 00 00 01
        if((prefix[pos % 3] == 0) && (prefix[(pos + 1) % 3] == 0) && (prefix[(pos + 2) % 3] == 1))
        {
            _nalBytes.pop_back();
            _nalBytes.pop_back();
            _nalBytes.pop_back();
            getPrefix = 1;
            return true;
        }
        // 0x 00 00 00 01
        else if((prefix[pos % 3] == 0) && (prefix[(pos + 1) % 3] == 0) && (prefix[(pos + 2) % 3] == 0))
        {
            if(getc(_inputfile) == 1)
            {
                _nalBytes.pop_back();
                _nalBytes.pop_back();
                _nalBytes.pop_back();
                getPrefix=2;
                break;
            }
        }
        else
        {
            fileByte = getc(_inputfile);
            prefix[(pos ++) % 3] = fileByte;
            _nalBytes.push_back(fileByte);
        }
    }
    return getPrefix;
}

void CStreamFile::ebsp_to_sodb()
{
    if(_nalBytes.size() < 3)
    {
        return;
    }

    for(vector<uint8>::iterator it = _nalBytes.begin() + 2; it != _nalBytes.end();)
    {
        if((0 == *(it - 2)) && (0 == *(it - 1)) && (3 == *it))
        {
            vector<uint8>::iterator tmp = _nalBytes.erase(it);
            it = tmp;
        }
        else
        {
            it ++;
        }
    }
}