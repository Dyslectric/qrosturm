#pragma once

enum Key {
	ToDo
};

namespace qrosturm {
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

	enum CursorMode {};

	void init();
	void clear();
	void refresh();
	void set_echo();
	void set_echo_off();
	void end();
	Key get_key();
	void move_cursor(WindowPosition position);
	void print(const char* fmt, ...);
	WindowDimensions get_dimensions();
}