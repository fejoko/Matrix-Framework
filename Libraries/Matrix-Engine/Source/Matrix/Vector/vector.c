#include "Matrix/Vector/vector.h"

#include "Matrix/Vector/INTERNAL/INTERNAL_vector_data.h"
#include "Matrix/Vector/INTERNAL/INTERNAL_vector_errors.h"

Matrix_Vector* matrix_vector_construct(const size_t element_size, const size_t vector_capacity)
{
	if (element_size < 1)
	{
		MTRX_ERROR_VECTOR_INVALID_ELEMENT_SIZE;
	}
	else
	{
		Matrix_Vector* vector = malloc(sizeof(*vector));
		if (NULL == vector)
		{
			MTRX_ERROR_MALLOC_FAILED;
		}
		else
		{
			vector->element_size = element_size;
			vector->vector_capacity = vector_capacity;
			
			if (vector_capacity < 1)
			{
				vector->vector_data = NULL;
			}
			else
			{
				vector->vector_data = malloc(element_size * vector_capacity);
				if (NULL == vector->vector_data)
				{
					MTRX_ERROR_MALLOC_FAILED;
				}
				else
				{
					return vector;
				}
			}
		}
	}
}

void matrix_vector_destruct(Matrix_Vector* vector)
{
	if (NULL == vector)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (vector->vector_capacity < 1)
		{
			//nothing
		}
		else
		{
 			if (NULL == vector->vector_data)
			{
				MTRX_ERROR_UNEXPECTED_NULL;
			}
			else
			{
				free(vector->vector_data);
				vector->vector_data = NULL;
			}
		}

		free(vector);
		vector = NULL;
	}
}

char* matrix_vector_at(const size_t index, Matrix_Vector* const vector)
{
	if (NULL == vector)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (vector->element_size < 1)
		{
			MTRX_ERROR_VECTOR_INVALID_ELEMENT_SIZE;
		}
		else
		{
			if (index >= vector->vector_capacity)
			{
				MTRX_ERROR_VECTOR_INVALID_INDEX;
			}
			else
			{
				if (NULL == vector->vector_data)
				{
					MTRX_ERROR_UNEXPECTED_NULL;
				}
				else
				{
					return vector->vector_data + (index * vector->element_size);
				}
			}
		}
	}
}

char* matrix_vector_front(Matrix_Vector* const vector)
{
	if (NULL == vector)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (NULL == vector->vector_data)
		{
			MTRX_ERROR_UNEXPECTED_NULL;
		}
		else
		{
			return vector->vector_data;
		}
	}
}

char* matrix_vector_back(Matrix_Vector* const vector)
{
	if (NULL == vector)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (vector->element_size < 1)
		{
			MTRX_ERROR_VECTOR_INVALID_ELEMENT_SIZE;
		}
		else
		{
			if (vector->vector_capacity < 1)
			{
				return vector->vector_data;
			}
			else
			{
				if (NULL == vector->vector_data)
				{
					MTRX_ERROR_UNEXPECTED_NULL;
				}
				else
				{
					return vector->vector_data + (((vector->vector_capacity - 1) * vector->element_size));
				}
			}
		}
	}
}

char* matrix_vector_data(const size_t index, Matrix_Vector* const vector)
{
	if (NULL == vector)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (NULL == vector->vector_data)
		{
			MTRX_ERROR_UNEXPECTED_NULL;
		}
		else
		{
			return vector->vector_data;
		}
	}
}

size_t matrix_vector_capacity(Matrix_Vector* const vector)
{
	if (NULL == vector)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		return vector->vector_capacity;
	}
}

void matrix_vector_clear(Matrix_Vector* const vector)
{
	if (NULL == vector)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (NULL == vector->vector_data)
		{
			//nothing
		}
		else
		{
			free(vector->vector_data);
			vector->vector_data = NULL;
		}
	}
}

//void matrix_vector_insert(size_t index, char* element, Matrix_Vector* vector);
//void matrix_vector_emplace(size_t index, char* element, Matrix_Vector* vector);

void matrix_vector_push_back(char* const element, Matrix_Vector* const vector)
{
	if (NULL == vector)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (vector->element_size < 1)
		{
			MTRX_ERROR_VECTOR_INVALID_ELEMENT_SIZE;
		}
		else
		{
			if (NULL == vector->vector_data)
			{
				if (vector->vector_capacity < 1)
				{
					vector->vector_data = malloc(vector->element_size);
					if (NULL == vector->vector_data)
					{
						MTRX_ERROR_MALLOC_FAILED;
					}
					else
					{
						if (NULL == vector->vector_data + (vector->element_size * vector->vector_capacity))
						{
							MTRX_ERROR_UNEXPECTED_NULL;
						}
						else
						{
							memcpy(vector->vector_data, element, vector->element_size);
							vector->vector_capacity++;
						}
					}
				}
				else
				{
					MTRX_ERROR_VECTOR_INVALID_CAPACITY;
				}
				
			}
			else
			{
				if (vector->vector_capacity < 1)
				{
					MTRX_ERROR_VECTOR_INVALID_CAPACITY;
				}
				else
				{
					char* temp = realloc(vector->vector_data, vector->element_size * (vector->vector_capacity + 1));
					if (NULL == temp)
					{
						MTRX_ERROR_REALLOC_FAILED;
					}
					else
					{
						vector->vector_data = temp;
					
						if (NULL == vector->vector_data + (vector->element_size * vector->vector_capacity))
						{
							MTRX_ERROR_UNEXPECTED_NULL;
						}
						else
						{
							memcpy(vector->vector_data + (vector->element_size * vector->vector_capacity), element, vector->element_size);
							vector->vector_capacity++;
						}
					}
				}
			}
		}
	}
}

//void matrix_vector_emplace_back(char* element, Matrix_Vector* vector);

void matrix_vector_pop_back(Matrix_Vector* const vector)
{
	if (NULL == vector)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (NULL == vector->vector_data)
		{
			MTRX_ERROR_UNEXPECTED_NULL;
		}
		else
		{
			if (vector->element_size < 1)
			{
				MTRX_ERROR_VECTOR_INVALID_ELEMENT_SIZE;
			}
			else
			{
				if (vector->vector_capacity < 1)
				{
					MTRX_ERROR_VECTOR_INVALID_CAPACITY;
				}
				else
				{
					if (vector->vector_capacity < 2)
					{
						free(vector->vector_data);
						vector->vector_data = NULL;
						vector->vector_capacity--;
					}
					else
					{
						char* temp = realloc(vector->vector_data, vector->element_size * (vector->vector_capacity - 1));
						if (NULL == vector->vector_data)
						{
							MTRX_ERROR_REALLOC_FAILED;
						}
						else
						{
							vector->vector_capacity--;
						}
					}
				}
			}
			
		}
	}
}

void matrix_vector_resize(const size_t capacity, Matrix_Vector* const vector)
{
	if (NULL == vector)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (NULL == vector->vector_data)
		{
			MTRX_ERROR_UNEXPECTED_NULL;
		}
		else
		{
			if (vector->element_size < 1)
			{
				MTRX_ERROR_VECTOR_INVALID_ELEMENT_SIZE;
			}
			else
			{
				if (vector->vector_capacity < 1)
				{
					MTRX_ERROR_VECTOR_INVALID_CAPACITY;
				}
				else
				{
					char* temp = realloc(vector->vector_data, vector->element_size * (capacity));
					if (NULL == temp)
					{
						MTRX_ERROR_UNEXPECTED_NULL;
					}
					else
					{
						vector->vector_data = temp;
						vector->vector_capacity = capacity;
					}
				}
			}

		}
	}
}

//void matrix_vector_swap(Matrix_Vector** vector1, Matrix_Vector** vector2);
//void matrix_vector_copy(Matrix_Vector* source, Matrix_Vector* destination);
//void matrix_vector_copy_assign(Matrix_Vector* source, Matrix_Vector* destination);

//Matrix_Vector* matrix_vector_move_construct(Matrix_Vector* source)
//{
//	if (NULL == source)
//	{
//		MTRX_ERROR_UNEXPECTED_NULL;
//	}
//	else
//	{
//		Matrix_Vector* vector = malloc(sizeof(*vector));
//		if (NULL == vector)
//		{
//			MTRX_ERROR_MALLOC_FAILED;
//		}
//		else
//		{
//			vector->element_size = source->element_size;
//			vector->vector_capacity = source->vector_capacity;
//
//			if (source->vector_capacity < 1)
//			{
//				vector->vector_data = NULL;
//			}
//			else
//			{
//				vector->vector_data = malloc(source->element_size * source->vector_capacity);
//				if (NULL == vector->vector_data)
//				{
//					MTRX_ERROR_MALLOC_FAILED;
//				}
//				else
//				{
//					return vector;
//				}
//			}
//		}
//	}
//}

//void matrix_vector_move_assign(Matrix_Vector* source, Matrix_Vector* destination);