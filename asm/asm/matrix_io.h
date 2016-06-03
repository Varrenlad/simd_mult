#pragma once

#include "headers.h"
#include "matrix_ops.h"

extern int get_matrix(char *filename, matrix *result, int op);
extern int put_matrix(char *filename, matrix out);

/*gets a matrix from file; transponates it if op = 0*/
int get_matrix(char *filename, matrix *result, int op){
	FILE *file_pointer;
	int i, j, temp, temp2;
	if (filename == nullptr)
		return (FAIL);
	if ((file_pointer = fopen(filename, "r")) == nullptr)
		return (FAIL);
	fscanf(file_pointer, "%d", &(result->size));
	result->was_aligned_by = 4 - result->size % 4;
	temp2 = result->size;
	result->size += result->was_aligned_by;
	if (new_matrix(result))
		return (MEM_ERR);
	if (op)
	for (i = 0; i < temp2; i++){
			temp = i * result->size;
		for (j = 0; j < temp2; j++)
				fscanf(file_pointer, "%f", &(result->load[temp + j]));
			}
	else
	for (i = 0; i < temp2; i++){
			temp = 0;
			for (j = 0; j < temp2; j++){
				fscanf(file_pointer, "%f", &(result->load[i + temp])); //we trasp. it by jumping in linear array by height of matrix
				temp += result->size;
			}
	}

	return SUCCESS;
}

int put_matrix(char *filename, matrix out){
	FILE *file_pointer;
	int i, j, temp = 0;
	if (filename == nullptr)
		return (FAIL);
	if ((file_pointer = fopen(filename, "w")) == nullptr)
		return (FAIL);
	for (i = 0; i < out.size; i++){
		for (j = 0; j < out.size; j++){
			fprintf(file_pointer, "%f ", out.load[j + temp]);
		}
		temp += out.size;
		fputc('\n', file_pointer);
	}
	fclose(file_pointer);
	return (SUCCESS);
}