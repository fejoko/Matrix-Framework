#include "Matrix/Core/main.h"

#include "Matrix/Vector/vector.h"
#include <stdio.h>

int main(const int argc, const char** const argv)
{
	Matrix_Vector* vec = matrix_vector_construct(sizeof(int), 0);

	int i = 12;
	int ix = 123;
	int ixx = 1234;
	int ixxx = 12345;
	int ii = 98;
	int iix = 987;
	int iixx = 9876;
	int iixxx = 98765;
	matrix_vector_push_back(&i, vec);
	matrix_vector_push_back(&ix, vec);
	matrix_vector_push_back(&ixx, vec);
	matrix_vector_push_back(&ixxx, vec);
	matrix_vector_push_back(&ii, vec);
	matrix_vector_push_back(&iix, vec);
	matrix_vector_push_back(&iixx, vec);
	matrix_vector_push_back(&iixxx, vec);

	printf("%i\n", MTRX_VECTOR_AT_AS(int, 0, vec));
	printf("%i\n", MTRX_VECTOR_AT_AS(int, 1, vec));
	printf("%i\n", MTRX_VECTOR_AT_AS(int, 2, vec));
	printf("%i\n", MTRX_VECTOR_AT_AS(int, 3, vec));
	printf("%i\n", MTRX_VECTOR_AT_AS(int, 4, vec));
	printf("%i\n", MTRX_VECTOR_AT_AS(int, 5, vec));
	printf("%i\n", MTRX_VECTOR_AT_AS(int, 6, vec));
	printf("%i\n", MTRX_VECTOR_AT_AS(int, 7, vec));

	matrix_vector_destruct(vec);
}