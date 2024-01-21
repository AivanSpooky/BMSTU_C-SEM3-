#include "process.h"

int process(FILE *f, int *r)
{
    int min_r = -1;

    int prev_num = 0;
    int cur_num = 0;
    int next_num = 0;

    size_t ind = 0;

    size_t i;
    if (fscanf(f, "%d%d%d", &prev_num, &cur_num, &next_num) == ANALYZING_NUMS)
    {
        i = 1;
        do
        {
            if ((cur_num > prev_num) && (cur_num > next_num))
            {
                if (ind == 0)
                    ind = i;
                else
                {
                    min_r = (min_r < 0) ? (int)(i - ind - 1) : min_r;
                    min_r = ((int)(i - ind - 1) < min_r) ? (int)(i - ind - 1) : min_r;
                    ind = i;
                }
            }
            prev_num = cur_num;
            cur_num = next_num;
            i++; 
        }
        while (fscanf(f, "%d", &next_num) == 1);
    }
    else
        return ERR_CNT;
    if (min_r < 0)
        return ERR_CNT;
    (*r) = min_r + 1;
    return OK;
}
