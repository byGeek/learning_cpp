// ModifierDeMO.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "GameCharacter.h"
#include "mybase.h"

void test_virtual_func() {

	/*

	none-virtual function is statically bound function
	it depends on declaration, 

	BUT
	virtual function is dynamiclly bound, so you can a virtual function
	on an base class object, it will call derived override func

	*/

	mybase* b1 = new myderived();
	b1->non_virtual_fun();
	b1->virtual_func();
	b1->virtual_func(1);  //with default value 1

	delete b1;

	myderived* d1 = new myderived();
	d1->non_virtual_fun();
	d1->virtual_func();
	d1->virtual_func(1);  //with default value 2

	delete d1;

}


int main()
{
	//BadGuy badguy;
	//badguy.doHealthValue();

	//GameCharacter* ch = new BadGuy();
	//ch->healthValue();  //will call BadyGuy's doHealthValue function

	//delete ch;


	test_virtual_func();

	std::cin.get();

    std::cout << "Hello World!\n"; 
}


