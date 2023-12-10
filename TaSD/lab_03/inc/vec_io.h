#ifndef VEC_IO_H__
#define VEC_IO_H__

#include "vec.h"
#include "matrix.h"
#include "matrix_io.h"
#include "prompt.h"

int vec_input(FILE *f_in, FILE *f_out, vector_t *vec, prompt_t prompt);

void vec_print(FILE *f, vector_t *vec);

void vec_normal_print(FILE *f, vector_t *vec);

#endif
