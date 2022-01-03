#include "CAVLC.h"

using namespace std;

// 获取非 0 个数
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

// 获取 +- 1 尾数的个数及其符号
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

// 
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

int get_totalzeros_runbefore(const int coeff[16], int *runBefore, int *zerosLeft, int totalCoeffs)
{
    int idx = 15, totalZeros = 0, runIdx = 0;

    // totalZeros: 最后一个非零系数前零的数目
    for(; idx >= 0; idx--)
    {
        if(coeff[idx])
        {
            break;
        }
    }
    totalZeros = idx - totalCoeffs + 1;
    
    // runBefore：当前非零系数前面连续出现的0的个数
    // zeroLefts:当前非零系数前的0的总个数
    for(; idx >= 0; idx --)
    {
        if(coeff[idx]==0)
        {
            continue;
        }
        for(int run = 0; run <= idx; run++)
        {
            if(coeff[idx-1-run]==0)
            {
                runBefore[runIdx]++;
                zerosLeft[runIdx]++;
            }
            else
            {
                runIdx ++;
                break;
            }
        }
    }
    for(int a=0; a<runIdx; a++)
    {
        for(int b=0; b<runIdx; b++)
        {
            zerosLeft[a] += zerosLeft[b];
        }
    }
    return totalZeros;
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
    int totalZeros = get_totalzeros_runbefore(coeff, runBefore, zerosLeft, totalCoeffs);

    delete[] levels;
    return retStr;
}

int main(int argc, char const *argv[])
{
    int coeff[16] = {3, 2, 1, -1, 0, -1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0};


    return 0;
}