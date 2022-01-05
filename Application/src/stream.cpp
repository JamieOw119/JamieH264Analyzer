#include <iostream>

#include "../include/Stream.h"

using namespace std;

CStreamFile::CStreamFile(char *filename)
{
    m_filename = filename;
    m_sps = NULL;
    m_pps = NULL;
    m_IDR_Slice = NULL;

    m_inputfile = fopen(filename, "r");   
    if(!m_inputfile)
    {
        fileError(0);
    }
    fileInfo();

#if TRACE_CONFIG_LOGOUT
    g_traceFile.open("trace.txt");
    if(!g_traceFile.is_open())
    {
        fileError(1);
    }
#endif
}

CStreamFile::~CStreamFile()
{
    if(m_inputfile)
    {
        fclose(m_inputfile);
        m_inputfile = nullptr;
    }
    if (m_sps)
	{
		delete m_sps;
		m_sps = nullptr;
	}
    if(m_pps)
    {
        delete m_pps;
        m_pps = nullptr;
    }
    if(m_IDR_Slice)
    {
        delete m_IDR_Slice;
        m_IDR_Slice = nullptr;
    }

#if TRACE_CONFIG_LOGOUT
    if(g_traceFile.is_open())
    {
        g_traceFile.close();
    }
#endif
}

void CStreamFile::fileInfo()
{
    if(m_filename)
    {
        cout<<"Filename: "<<m_filename<<endl;
    }
}

void CStreamFile::fileError(int idx)
{
    switch (idx)
    {
    case 0:
        cout<<"Error: opening input file failed."<<endl;
        break;
    case 1:
        cout<<"Error: opening trace file failed."<<endl;
        break;
    
    default:
        break;
    }
}

int CStreamFile::Parse_h264_bitstream()
{
    int ret = 0;
    UINT32 sliceIdx = 0;
    do
    {
        ret = find_nal_prefix();
        if(m_nalVec.size())
        {
            UINT8 nalType = (UINT8)m_nalVec[0] & 0x1F;
            dump_NAL_type(nalType);
            ebsp_to_sodb();
            CNALUnit nalUnit(&m_nalVec[1], m_nalVec.size() - 1, nalType);

            switch(nalType)
            {
                case 5:
                    if(m_IDR_Slice)
                    {
                        delete m_IDR_Slice;
                        m_IDR_Slice = NULL;
                    }
                    m_IDR_Slice = new CSliceStruct(nalUnit.GET_SODB(), m_sps, m_pps, nalType, sliceIdx++);
                    m_IDR_Slice->Parse();
                    break;
                case 7:
                    if (m_sps)
                    {
                        delete m_sps;
                        m_sps = NULL;
                    }
                    m_sps = new CSeqParamSet;
                    nalUnit.Parse_as_seq_param_set(m_sps);
                    m_sps->Dump_sps_info();
                    break;
                case 8:
                    if(m_pps)
                    {
                        delete m_pps;
                        m_pps = NULL;
                    }
                    m_pps = new CPicParamSet;
                    nalUnit.Parse_as_pic_param_set(m_pps);
                    m_pps->Dump_pps_info();
                    break;
                default:
                    break;
            }
        }
    } while (ret);
    return ret;
}

int CStreamFile::find_nal_prefix()
{
    UINT8 prefix[3] = {0};
    UINT8 fileByte;
    int pos = 0;
    int getPrefix = 0;

    m_nalVec.clear();

    for(int idx = 0; idx < 3; idx++)
    {
        prefix[idx] = getc(m_inputfile);
        m_nalVec.push_back(prefix[idx]);
    }
    while(!feof(m_inputfile))
    {
        // 0x 00 00 01
        if((prefix[pos % 3] == 0) && (prefix[(pos + 1) % 3] == 0) && (prefix[(pos + 2) % 3] == 1))
        {
            m_nalVec.pop_back();
            m_nalVec.pop_back();
            m_nalVec.pop_back();
            getPrefix = 1;
            break;
        }
        // 0x 00 00 00 01
        else if((prefix[pos % 3] == 0) && (prefix[(pos + 1) % 3] == 0) && (prefix[(pos + 2) % 3] == 0))
        {
            if(getc(m_inputfile) == 1)
            {
                m_nalVec.pop_back();
                m_nalVec.pop_back();
                m_nalVec.pop_back();
                getPrefix=2;
                break;
            }
        }
        else
        {
            fileByte = getc(m_inputfile);
            prefix[(pos ++) % 3] = fileByte;
            m_nalVec.push_back(fileByte);
        }
    }
    return getPrefix;
}

void CStreamFile::ebsp_to_sodb()
{
    if(m_nalVec.size() < 3)
    {
        return;
    }

    for(vector<UINT8>::iterator it = m_nalVec.begin() + 2; it != m_nalVec.end();)
    {
        if((0 == *(it - 2)) && (0 == *(it - 1)) && (3 == *it))
        {
            vector<UINT8>::iterator tmp = m_nalVec.erase(it);
            it = tmp;
        }
        else
        {
            it ++;
        }
    }
}

void CStreamFile::dump_NAL_type(UINT8 nalType)
{
#if TRACE_CONFIG_CONSOLE
    cout<<"NAL Unit Type: "<<to_string(nalType)<<endl;
#endif

#if TRACE_CONFIG_LOGOUT
    g_traceFile<<"NAL Unit Type: "<<to_string(nalType)<<endl;
#endif
}