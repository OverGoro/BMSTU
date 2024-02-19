#ifndef  CHECK_CMP_H__
#define CHECK_CMP_H__
#include <check.h>
#include <stddef.h>

void cmp_arr_str(char parr[][8], size_t n_arr, char ans[][8], size_t n_ans);

void cmp_arr_int(int *parr, size_t n_arr, int *ans, size_t n_ans);

void cmp_arr_float(float *parr, size_t n_arr, float *ans, size_t n_ans);

void cmp_arr_double(double *parr, size_t n_arr, double *ans, size_t n_ans);

#endif

