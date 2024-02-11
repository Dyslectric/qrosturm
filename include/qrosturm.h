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

	// i'm caught with my pants down having these out here please don't touch
	static Buffer *screen_buffer;
	static WindowPosition cursor_pos;
	
	//enum CursorMode {};

	// creates a new buffer filled with ' ' and stores a handle to the old buffer
	void init();

	// clears the character buffer with clr_character
	void clear(char clr_character);

	// copies the internal character buffer into the screen buffer
	void refresh();

	// used when done with the buffer, restores old stdout buffer
	void end();

	// unimplemented for the most part, will return key events, etc
	Event poll_events();

	// sets the line x column coordinate for printing
	void set_print_coord(int line, int column);

	// prints the str to the screen at the print coordinates
	// will increment print coordinates by length of the string
	void print(std::string str);

	// returns the lines x columns dimensions of the the buffer
	// the buffer automatically resizes to the dimensions of the screen when it is resized
	WindowDimensions get_max_dimensions();

	// not yet implemented, thinking of adding different echo modes like numbers
	// only and the like for stuff like integer collection
	//void set_echo();
	//void set_echo_off();
}