#include "student_sort.h"
#include "student.h"

// Сортировка
void swap(void *l, void *r, size_t e_size)
{
    char tmp;
    char *pl = l;
    char *pr = r;
    for (size_t i = 0; i < e_size; i++)
    {
        tmp = *pl;
        *pl = *pr;
        *pr = tmp;
        pl++;
        pr++;
    }
}

void sa_bubble_sort(void *pdata, size_t n, size_t e_size, cmp_t cmp)
{
    if (n < 2)
        return;
    char *pbeg = pdata;
    char *pend = pbeg + n * e_size;
    char *last_swap = pend;
    char *ptop = pend;
    while (ptop > pbeg)
    {
        last_swap = pbeg;
        for (char *pcur = pbeg + e_size; pcur < ptop; pcur += e_size)
        {
            int rc = cmp(pcur - e_size, pcur);
            if (rc > 0)
            {
                swap(pcur - e_size, pcur, e_size);
                last_swap = pcur;
            }

        }
        ptop = last_swap;
    }
}

void sa_quicksort(void *pdata, size_t n, size_t e_size, cmp_t cmp) 
{
    qsort(pdata, n, e_size, cmp);
}

