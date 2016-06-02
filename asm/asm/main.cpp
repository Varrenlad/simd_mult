#include "headers.h"

int main(){
	matrix m_A, m_B, out;
	system("dir");
	get_matrix("input.txt", &m_A, 1);
	get_matrix("input2.txt", &m_B, 0);
	multiply(m_A, m_B, out);
	put_matrix("output.txt", out);
	destroy_matrix(out);
	return 0;
}
