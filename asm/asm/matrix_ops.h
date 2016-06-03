#pragma once
#include "headers.h"

extern inline int new_matrix(matrix *to_create);
extern inline void destroy_matrix(matrix *to_remove);
inline float dot_product_asm(float *line_array_a, float *line_array_b, int size);
inline float dot_product_intr(float *line_array_a, float *line_array_b, int size);
extern void multiply(matrix *A, matrix *B, matrix *out);

int new_matrix(matrix *to_create){
	int i, temp;
	temp = to_create->size * to_create->size;
	to_create->load = (float*)_aligned_malloc(temp * sizeof(float), 16);
	if (to_create->load == nullptr)
		return (FAIL);
	for (i = 0; i < temp; i++){
		to_create->load[i] = 0;
	}
	return (SUCCESS);
}

float dot_product_asm(float *line_array_a, float *line_array_b, int size){
	int i;
	float *a, *b, t_res, res = 0;
	for (i = 0; i < size / 4; i++){
		a = line_array_a + i * 4;
		b = line_array_b + i * 4;
		__asm {
			mov		eax, a;			//set pointer to first line
			mov		ebx, b;			//set pointer to second line
			movaps	xmm0, [eax];	//load first vector
			movaps	xmm1, [ebx];	//load second vector

			mulps	xmm0, xmm1;		//multiply vectors
			haddps	xmm0, xmm0;		//main value in 0-31 and 32-63
			haddps	xmm0, xmm0;		//value moved to 0-31
			movd	[t_res], xmm0;	//unload 0-31 to pointer
		};
		res += t_res;
	}
	return res;
}

void multiply(matrix *A, matrix *B, matrix *out){
	int i, j, temp = 0, temp2, temp3 = 0;
	out->size = A->size - A->was_aligned_by;
	new_matrix(out);
	for (i = 0; i < out->size; i++){
		temp2 = 0;
		for (j = 0; j < out->size; j++){
			out->load[temp3 + j] = dot_product_asm(A->load + temp, B->load + temp2, A->size);
			temp2 += A->size;
		}
		temp3 += out->size;
		temp += A->size;
	}	
	destroy_matrix(A);
	destroy_matrix(B);
	return;
}

void destroy_matrix(matrix *to_remove){
	_aligned_free(to_remove->load);
	to_remove->size = 0;
	to_remove->was_aligned_by = 0;
}