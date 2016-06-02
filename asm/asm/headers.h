#pragma once
#pragma warning(disable:4996)

struct matrix{
	int size;
	float *load;
	short was_aligned_by;
};

#define STDPATH "input.txt"

#ifndef SUCCESS
#define SUCCESS 0
#endif

#ifndef FAIL
#define FAIL 1
#endif

#ifndef MEM_ERR
#define MEM_ERR 2
#endif

#ifndef MAX_LENGTH
#define MAX_LENGTH 256
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include "matrix_ops.h"
#include "matrix_io.h"