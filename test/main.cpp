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
	qrosturm::clear(' ');

	long long int last_refresh = now();

	while (true) {
		//do {
		//	qrosturm::poll_events();
		//} while (!is_delta_time(150, last_refresh));
		//qrosturm::clear('#');
		//qrosturm::set_print_coord(3, 8);
		//qrosturm::print("Hello World!");
		//qrosturm::refresh();
		
		qrosturm::Event event = qrosturm::poll_event();

		if (
			event.type == qrosturm::EventType::Key &&
			event.key.type == qrosturm::KeyEventType::Letter &&
			event.key.state == qrosturm::ButtonState::Down
		) {
			std::string str = "Keydown:Unicode:";

			int unicode = event.key.letter;

			str += std::to_string(unicode);
			str += " ";

			qrosturm::print(str);
			qrosturm::refresh();
		}

		//qrosturm::clear(' ');

	}

	qrosturm::end();
	
	return 0;
}