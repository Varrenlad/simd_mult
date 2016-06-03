#pragma once
#pragma warning(disable:4996)

struct matrix{
	short int size = 0;
	float *load = nullptr;
	short was_aligned_by = 0;
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