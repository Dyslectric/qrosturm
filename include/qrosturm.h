#pragma once

#include <string>

struct Buffer;

namespace qrosturm {

	enum EventType {
		Key,
		Wait
	};

	struct Event {
		EventType type;
	};

	struct WindowPosition {
		int line;
		int column;
	};

	struct BufferPosition {
		int row;
		int column;
	};

	struct WindowDimensions {
		int lines;
		int columns;
	};

	static Buffer *screen_buffer;
	static WindowPosition cursor_pos;
	
	enum CursorMode {};

	void init();
	void clear(char clr_character);
	void refresh();
	void set_echo();
	void set_echo_off();
	void end();
	Event poll_events();
	void move_cursor(WindowPosition position);
	void print(std::string str);
	WindowDimensions get_max_dimensions();
}