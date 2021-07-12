#include "Matrix/Core/main.h"

#include "Matrix/Engine/INTERNAL/INTERNAL_engine.h"
#include "Matrix/Engine/INTERNAL/INTERNAL_engine_data.h"

int main(const int argc, const char** const argv)
{
	Matrix_Engine engine = matrix_engine_construct();
	matrix_engine_run(&engine);
	matrix_engine_destruct(&engine);
}