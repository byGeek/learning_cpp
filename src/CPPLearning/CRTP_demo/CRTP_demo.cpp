// CRTP_demo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include "generic_singleton.h"
#include "another_crtp.h"
#include "instance_cnt.h"

int main()
{

	test_simple_singleton();
	test_if_single();
	test_new_handler();

	test_ref();
}