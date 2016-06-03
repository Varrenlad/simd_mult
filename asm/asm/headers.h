#pragma once
#pragma warning(disable:4996)

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

struct matrix{
	int size = 0;
	float *load = nullptr;
	short was_aligned_by = 0;
};

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include "matrix_ops.h"
#include "matrix_io.h"
#include <stdint.h>
#include <intrin.h>
uint64_t rdtsc(){
	return __rdtsc();
}