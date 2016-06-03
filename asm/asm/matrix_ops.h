#pragma once
#include "headers.h"

extern inline int new_matrix(matrix *to_create);
extern inline void destroy_matrix(matrix *to_remove);
inline void asm_multiply(float *vec_a, float *vec_b, float *res, int arr_size);
extern matrix *multiply(matrix *A, matrix *B);

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

void asm_multiply(float *vec_a, float *vec_b, float *res, short int arr_size){
/*	int i, temp;
	float f = 0, t, *a = vec_a, *b = vec_b;
	for (i = 0; i < size / 4; i += 4){
		temp = 4 * i;
		a += temp;
		b += temp;
		__asm{
			mov		eax, t;
		//	mov		ebx, f;
			movaps	xmm0, a;
			movaps	xmm1, b;
			mulps	xmm0, xmm1;
			haddps	xmm0, xmm0;
			haddps	xmm0, xmm0;
			movss	t, xmm0;
		//	add		ebx, eax;
		};
		f += t;
		__asm{nop};
	}*/
	__asm {
		mov		cx, arr_size;//get size
		mov		eax, 0;		//pointer multiplier for float array
		mov		ebx, 0;		//temporal result register for movss
		mov		edx, 0;		//result register
		mov		edi, res;	//pointer to res

		cmp		cx, 0;
		ja		calc;
		
		calc:
			mov		esi, vec_a;
			movaps	xmm1, [esi + eax];
			mov		esi, vec_b;
			movaps	xmm2, [esi + eax];
			mulps	xmm1, xmm2;
			//haddps	xmm1, xmm1;
			//haddps	xmm1, xmm1;
			//movss	ebx,  xmm1;
			movhlps	xmm2, xmm1;
			addps	xmm1, xmm2;
			shufps	xmm1, xmm1, 00000001b;
			movss	edx, xmm1;
			add		ebx, edx;
			add		eax, 128;	
			sub		cx, 4;		//substract 4 (size of xmm)
			cmp		cx, 0;		//compare cx-cycle-register with 0
			ja		calc;		//jump to the start of cycle if not all done
		
		mov	[edi], ebx;
	};
	}

matrix *multiply(matrix *A, matrix *B){
	matrix *result = new matrix;
	int i, j, temp = 0, temp2;
	result->size = A->size - A->was_aligned_by;
	new_matrix(result);
	for (i = 0; i < result->size; i++){
		temp += A->size;
		temp2 = 0;
		for (j = 0; j < result->size; j++){
			asm_multiply(A->load + temp, B->load + temp2,
				&(result->load[temp + temp2]), A->size);
			temp2 += A->size;
		}
	}
	//destroy_matrix(A);
	//destroy_matrix(B);
	return result;
}

void destroy_matrix(matrix *to_remove){
	_aligned_free(to_remove->load);
	to_remove->size = 0;
	to_remove->was_aligned_by = 0;
}