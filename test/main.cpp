#include "qrosturm.h"

#include <Windows.h>

#include <iostream>
#include <chrono>

long long now() {

	using namespace std::chrono;

	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

bool is_delta_time(long long delta, long long &last_refresh) {
	long long t = now();
	long long test = t - last_refresh;
	if (t - last_refresh > delta) {
		last_refresh = t;
		return true;
	}
	else {
		return false;
	}
}

int main() {

	std::cout << "Hello!";

	qrosturm::init();
	//qrosturm::clear('#');

	long long int last_refresh = now();

	while (true) {
		qrosturm::clear('#');
		qrosturm::print("Hello World!");
		qrosturm::refresh();
		while (!is_delta_time(500, last_refresh)) {
			qrosturm::poll_events();
		}
		qrosturm::clear(';');
		qrosturm::print("Hello World!");
		qrosturm::refresh();
		while (!is_delta_time(500, last_refresh)) {
			qrosturm::poll_events();
		}
		qrosturm::clear('$');
		qrosturm::print("Hello World!");
		qrosturm::refresh();
		while (!is_delta_time(500, last_refresh)) {
			qrosturm::poll_events();
		}
	}
	//while (char key = qrosturm::get_key_ascii()) {
	//	char str[1] = { key };
	//	std::string my_string;
	//	my_string.append(str);
	//	qrosturm::print(my_string);
	//}

	Sleep(5000);

	qrosturm::end();
	
	return 0;
}