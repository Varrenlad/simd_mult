#include "headers.h"

int main(){
	matrix m_A, m_B, out;
	clock_t timer;
	unsigned long long cycle_cnt;
	FILE *file_pointer = fopen("results.txt", "a");
	if (file_pointer == nullptr)
		return 1;

	if (get_matrix("input.txt", &m_A, 1))
		return 2;
	if (get_matrix("input2.txt", &m_B, 0))
		return 3;

	multiply(&m_A, &m_B, &out);

	timer = clock() - timer;
	cycle_cnt = rdtsc() - cycle_cnt;

	fprintf(file_pointer, "ASM SIMD multiply %lf sec\n", (double)timer / CLOCKS_PER_SEC);
	fprintf(file_pointer, "%llu processor cycles used\n", cycle_cnt);

	if (put_matrix("output.txt", out))
		return 4;
	destroy_matrix(&out);
	return 0;
}
