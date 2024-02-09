#include "qrosturm.h"

#include <Windows.h>

#include <iostream>

int main() {

	std::cout << "Hello!";

	qrosturm::init();
	qrosturm::clear('#');
	qrosturm::refresh();

	Sleep(5000);

	qrosturm::end();
	
	return 0;
}