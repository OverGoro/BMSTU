#include "student.h"

int student_cmp(const void *student_l, const void *student_r, cmp_t cmp)
{
    int rc = cmp(student_l, student_r);
    return rc;
}

int cmp_mark(const void *student_l, const void *student_r)
{
    double res = ((student_t *)student_l)->average_mark - ((student_t *)student_r)->average_mark;
    if (res > 0)
        return 1;
    if (res == 0)
        return 0;
    else
        return -1;
}

int cmp_housing_type(const void *student_l, const void *student_r)
{
    return (int)((student_t *)student_l)->housing_type - (int)((student_t *)student_r)->housing_type;
}

int cmp_entry_date(const void *student_l, const void *student_r)
{
    return (int)((student_t *)student_l)->entry_date - (int)((student_t *)student_r)->entry_date;
}
