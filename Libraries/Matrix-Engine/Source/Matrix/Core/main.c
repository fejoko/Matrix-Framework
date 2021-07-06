#include "Matrix/Core/main.h"

#include "Matrix/Vector/vector.h"
#include <stdio.h>
#include "Matrix/Core/error.h"
#include "Matrix/Statemanager/INTERNAL/INTERNAL_statemanager.h"
#include "Matrix/Statemanager/INTERNAL/INTERNAL_statemanager_data.h"

void* a;
int s = 0;

void ac()
{
	printf("a created\n");
}

void ad()
{
	printf("a destroyed\n");

}

void ae()
{
	printf("a enter\n");
	if (s == 0)
	{
		matrix_statemanager_state_enter("b", a);
	}
}

void al()
{
	printf("a leave\n");
}

void bc()
{
	printf("b created\n");
}

void bd()
{
	printf("b destroyed\n");
}

void be()
{
	printf("b enter\n");
	s = 1;
}

void bl()
{
	printf("b leave\n");
}

int main(const int argc, const char** const argv)
{
	Matrix_Statemanager manager = matrix_statemanager_construct();
	a = &manager;

	Matrix_State sta = matrix_statemanager_state_construct();
	sta.name = "a";
	sta.on_creation = ac;
	sta.on_destruction = ad;
	sta.on_enter = ae;
	sta.on_leave = al;

	Matrix_State stb = matrix_statemanager_state_construct();
	stb.name = "b";
	stb.on_creation = bc;
	stb.on_destruction = bd;
	stb.on_enter = be;
	stb.on_leave = bl;

	matrix_statemanager_state_push_default(sta, &manager);
	matrix_statemanager_state_push(stb, &manager);

	matrix_statemanager_state_enter_default(&manager);

	matrix_statemanager_init(&manager);
	matrix_statemanager_shutdown(&manager);

	matrix_statemanager_state_destruct(&stb);
	matrix_statemanager_state_destruct(&sta);

	matrix_statemanager_destruct(&manager);
}