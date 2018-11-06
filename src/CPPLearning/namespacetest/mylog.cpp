#include "stdafx.h"
#include "mylog.h"

using namespace ns_test;

void mylog::dolog() {

}


void ns_test::ns_log::domylog()
{
}

void foo() {
	mylog log;
	log.dolog();

	//domylog();
	ns_test::ns_log::domylog();
}

