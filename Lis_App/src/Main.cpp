#include <stdio.h>
#include "lis.h"

// Example of lis (test4.c)
int main(LIS_INT argc, char* argv[])
{
	LIS_INT i, n, gn, is, ie, iter;
	LIS_MATRIX A;
	LIS_VECTOR b, x, u;
	LIS_SOLVER solver;
	n = 12;
	lis_initialize(&argc, &argv);
	lis_matrix_create(LIS_COMM_WORLD, &A);
	lis_matrix_set_size(A, 0, n);
	lis_matrix_get_size(A, &n, &gn);
	lis_matrix_get_range(A, &is, &ie);
		for (i = is; i < ie; i++)
		{
			if (i > 0) lis_matrix_set_value(LIS_INS_VALUE, i, i - 1, -1.0, A);
			if (i < gn - 1) lis_matrix_set_value(LIS_INS_VALUE, i, i + 1, -1.0, A);
			lis_matrix_set_value(LIS_INS_VALUE, i, i, 2.0, A);
		}
	lis_matrix_set_type(A, LIS_MATRIX_CSR);
	lis_matrix_assemble(A);

	lis_vector_duplicate(A, &u);
	lis_vector_duplicate(A, &b);
	lis_vector_duplicate(A, &x);
	lis_vector_set_all(1.0, u);
	lis_matvec(A, u, b);

	lis_solver_create(&solver);
	lis_solver_set_optionC(solver);
	lis_solve(A, b, x, solver);
	lis_solver_get_iter(solver, &iter);
	printf("number of iterations = %d\n", iter);
	lis_vector_print(x);
	lis_matrix_destroy(A);
	lis_vector_destroy(u);
	lis_vector_destroy(b);
	lis_vector_destroy(x);
	lis_solver_destroy(solver);
	lis_finalize();
	return 0;
}

