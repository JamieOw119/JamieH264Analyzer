#include <cstdio>
#include <vector>


typedef unsigned char uint8;

static int find_nal_prefix(FILE *p_file_in, std::vector<uint8> &nalBytes)
{
    FILE *p = p_file_in;
    uint8 prefix[3] = {0};
    uint8 fileByte;
    int pos = 0;
    int getPrefix = 0;

    for(int idx = 0; idx < 3; idx++)
    {
        prefix[idx] = getc(p);
        nalBytes.push_back(prefix[idx]);
    }
    while(!feof(p))
    {
        // 0x 00 00 01
        if((prefix[pos % 3] == 0) && (prefix[(pos + 1) % 3] == 0) && (prefix[(pos + 2) % 3] == 1))
        {
            nalBytes.pop_back();
            nalBytes.pop_back();
            nalBytes.pop_back();
            return true;
        }
        // 0x 00 00 00 01
        else if((prefix[pos % 3] == 0) && (prefix[(pos + 1) % 3] == 0) && (prefix[(pos + 2) % 3] == 0))
        {
            if(getc(p) == 1)
            {
                nalBytes.pop_back();
                nalBytes.pop_back();
                nalBytes.pop_back();
                getPrefix=2;
                break;
            }
        }
        else
        {
            fileByte = getc(p_file_in);
            prefix[(pos ++) % 3] = fileByte;
            nalBytes.push_back(fileByte);
        }
    }
    return getPrefix;
}

int main(int argc, char const *argv[])
{
    FILE *p_file_in = fopen("test.h264", "r");
    if(!p_file_in)
    {
        printf("Error: Opening input file failed\n");
        return 0;
    }

    while(!feof(p_file_in))
    {
        std::vector<uint8> nalBytes;
        find_nal_prefix(p_file_in, nalBytes);

        for(int idx = 0; idx < nalBytes.size(); idx++)
        {
            printf("%x ", nalBytes.at(idx));
        }
    }
    
    return 0;
}
