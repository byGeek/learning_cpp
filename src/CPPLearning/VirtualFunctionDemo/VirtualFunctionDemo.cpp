

#include <iostream>

#include "stdafx.h"
//#include "Airplane.h"
#include "Base.h"
#include "vptr_sizeof.h"

int main()
{
	test_vtable();
	test_sizeof_XYZ();
	//test_offset();

	std::cin.get();
    return 0;
}

