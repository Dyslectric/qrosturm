#include "qrosturm.h"

#include <Windows.h>

#include <iostream>

int main() {

	std::cout << "Hello!";

	qrosturm::init();
	qrosturm::clear('#');
	qrosturm::refresh();
	qrosturm::get_key();

	Sleep(5000);

	qrosturm::end();
	
	return 0;
}