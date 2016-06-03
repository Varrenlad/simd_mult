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
	int i, t_size = size / 4;
	float t_res = 0, res = 0;
	__m128 *x_vector, *y_vector, temp;
	//x_vector = (__m128 *)line_array_a;
	//y_vector = (__m128 *)line_array_b;
	for (i = 0; i < t_size; i++){
		x_vector = (__m128 *)(line_array_a + 4 * i);
		y_vector = (__m128 *)(line_array_b + 4 * i);
		temp = _mm_mul_ps(*x_vector, *y_vector);
		temp = _mm_hadd_ps(temp, temp);
		temp = _mm_hadd_ps(temp, temp);
		_mm_store_ss(&res, temp);
		t_res += res;
	}
	return t_res;
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