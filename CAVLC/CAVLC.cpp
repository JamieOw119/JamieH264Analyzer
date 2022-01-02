#include "CAVLC.h"

using namespace std;

int get_total_coeffs(const int coeff[16])
{
    int ret = 0;
    for(int idx = 0; idx < 16; idx ++)
    {
        if(coeff[idx])
        {
            ret ++;
        }
    }
    return ret;
}

int get_trailling_ones(const int coeff[16], int trailingSign[3])
{
    int ret = 0;
    for(int idx=15; idx >= 0; idx --)
    {
        if(abs(coeff[idx] > 1 || ret == 3))
        {
            break;
        }
        else if(abs(coeff[idx]) == 1)
        {
            if(coeff[idx] == 1)
            {
                trailingSign[ret] = 1;
            }
            else
            {
                trailingSign[ret] = -1;
            }
            ret ++;
        }
    }

    return ret;
}

int get_levels(const int coeff[16], int levels[], int levelCnt)
{
    int levelIdx = levelCnt - 1;
    for(int idx = 0; idx < 16; idx ++)
    {
        if(coeff[idx] != 0)
        {
            
        }
    }
    return 0;
} 

string Encoding_cavlc_16x16(const int coeff[16])
{
    string retStr;
    int totalCoeffs = get_total_coeffs(coeff);
    int trailingSign[3] = {0};
    int trailingOnes = get_trailling_ones(coeff, trailingSign);

    int levelCnt = totalCoeffs - trailingOnes;
    int *levels = new int[levelCnt];
    bzero(levels, sizeof(int)*levelCnt);
    get_levels(coeff, levels, levelCnt);

    int *runBefore = new int[totalCoeffs];
    int *zerosLeft = new int[totalCoeffs];
    get_levels(coeff, runBefore, totalCoeffs);
    get_levels(coeff, runBefore, totalCoeffs);


    delete[] levels;
    return retStr;
}

int main(int argc, char const *argv[])
{
    int coeff[16] = {3, 2, 1, -1, 0, -1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0};


    return 0;
}