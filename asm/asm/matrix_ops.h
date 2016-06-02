#pragma once
#include "headers.h"

extern inline int new_matrix(matrix to_create);
extern inline void destroy_matrix(matrix to_remove);
inline void asm_multiply(float *vec_a, float *vec_b, float *res, int size);
extern void multiply(matrix A, matrix B, matrix result);

int new_matrix(matrix to_create){
	int i, j;
	to_create.load = (float*)_aligned_malloc(to_create.size * sizeof(float), 16);
	if (to_create.load == nullptr)
		return (FAIL);
	for (i = 0; i < to_create.size * to_create.size; i++){
		to_create.load[i] = 0;
	}
	return (SUCCESS);
}

void asm_multiply(float *vec_a, float *vec_b, float *res, int size){
	int i;
	float f = 0;
	__asm {
		mov		cx, size;
		mov		eax, 0;		//pointer multiplier for float array
		mov		ebx, 0;		//temporal result register for movss
		mov		edx, 0;		//result register
		mov		edi, res;	//pointer to res

		loop:
			movaps	xmm1, [vec_a + 128 * eax];
			movaps	xmm2, [vec_b + 128 * eax];
			mulps	xmm1, xmm2;
			haddps	xmm1, xmm1;
			haddps	xmm1, xmm1;
			movss	ebx,  xmm1;
			add		edx,  ebx;
			add		eax,  1;	
		sub		cx, 4;		//substract 4 (size of xmm)
		cmp		cx, 0;		//compare cx-cycle-register with 0
		ja		cx, loop:;  //jump to the start of cycle if not all done
			
		mov [edi], edx;
	};
	}

void multiply(matrix A, matrix B, matrix result){
	int i, j, temp = 0, temp2;
	result.size = A.size - A.was_aligned_by;
	new_matrix(result);
	for (i = 0; i < result.size; i++){
		temp += A.size;
		temp2 = 0;
		for (j = 0; j < result.size; j++)
			temp2 += A.size;
			asm_multiply(A.load + temp, B.load + temp2,
			&(result.load[temp + temp2]), A.size);
	}
	destroy_matrix(A);
	destroy_matrix(B);
	return;
}

void destroy_matrix(matrix to_remove){
	_aligned_free(to_remove.load);
	to_remove.size = 0;
	to_remove.was_aligned_by = 0;
}