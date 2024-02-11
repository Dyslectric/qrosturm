#include <Windows.h>
#include <algorithm>
#include <stdio.h>
#include <vector>

#include "qrosturm.h"

using namespace qrosturm;

struct Buffer {
#ifdef _WIN32
    HANDLE out_handle;
    std::vector<CHAR_INFO> chr_buffer;
    COORD size;
#else

#endif
};

#ifdef _WIN32
static HANDLE StdOut;
#endif

// get max size of terminal for window and create a buffer of that size
void qrosturm::init() {
#ifdef _WIN32
    qrosturm::screen_buffer = new Buffer;

    auto buffer = qrosturm::screen_buffer;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hStdOut == INVALID_HANDLE_VALUE) {
        printf("CreateConsoleScreenBuffer failed - (%d)\n", GetLastError());
        exit(1);
    }

    StdOut = hStdOut;

    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(hStdOut, &csbiInfo);

    buffer->out_handle = CreateConsoleScreenBuffer(
        GENERIC_READ |
        GENERIC_WRITE,
        FILE_SHARE_READ |
        FILE_SHARE_WRITE,
        NULL,
        CONSOLE_TEXTMODE_BUFFER,
        NULL
    );

    if (buffer->out_handle == INVALID_HANDLE_VALUE) {
        printf("CreateConsoleScreenBuffer failed - (%d)\n", GetLastError());
        exit(1);
    }

    buffer->size.X = csbiInfo.srWindow.Right;
    buffer->size.Y = csbiInfo.srWindow.Bottom;

    buffer->chr_buffer = std::vector<CHAR_INFO>(buffer->size.X * buffer->size.Y);

    qrosturm::clear(' ');

    SetConsoleActiveScreenBuffer(buffer->out_handle);

    WindowPosition origin;
    origin.column = 0;
    origin.line = 0;

    qrosturm::cursor_pos = origin;
#else

#endif
}

void qrosturm::clear(char clr_character) {
#ifdef _WIN32

    auto buffer = qrosturm::screen_buffer;

    CHAR_INFO info;
    info.Char.UnicodeChar = clr_character;
    info.Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

    std::fill(buffer->chr_buffer.begin(), buffer->chr_buffer.end(), info);
#else

#endif
}

void qrosturm::refresh() {
#ifdef _WIN32
    COORD origin;
    origin.X = 0;
    origin.Y = 0;

    auto buffer = qrosturm::screen_buffer;

    SMALL_RECT dst_rect;
    dst_rect.Top = 0;
    dst_rect.Left = 0;
    dst_rect.Right = buffer->size.X;
    dst_rect.Bottom = buffer->size.Y;

    WriteConsoleOutput(
        buffer->out_handle,
        buffer->chr_buffer.data(),
        buffer->size,
        origin,
        &dst_rect);

    SetConsoleActiveScreenBuffer(qrosturm::screen_buffer->out_handle);
#else

#endif
}

//void qrosturm::set_echo() {
//#ifdef _WIN32
//
//#else
//
//#endif
//}
//
//void qrosturm::set_echo_off() {
//#ifdef _WIN32
//
//#else
//
//#endif
//}

void qrosturm::end() {
#ifdef _WIN32
    SetConsoleActiveScreenBuffer(StdOut);
#else

#endif
}

qrosturm::Event qrosturm::poll_events() {
#ifdef _WIN32

    DWORD input_count;
    INPUT_RECORD input_record;
    HANDLE input_handle = GetStdHandle(STD_INPUT_HANDLE);

    if (input_handle == NULL)
    {
        printf("Was not able to get handle to input.");
        exit(1);
    }

    DWORD n_events_not_read = 0;
    GetNumberOfConsoleInputEvents(input_handle, &n_events_not_read);

    for (; n_events_not_read > 0; n_events_not_read--) {
        ReadConsoleInput(input_handle, &input_record, 1, &input_count);

        if (input_record.EventType == WINDOW_BUFFER_SIZE_EVENT) {
            WindowDimensions dim;
            dim.columns = input_record.Event.WindowBufferSizeEvent.dwSize.X;
            dim.lines = input_record.Event.WindowBufferSizeEvent.dwSize.Y;

            qrosturm::screen_buffer->chr_buffer.resize(dim.columns * dim.lines);

            SetConsoleScreenBufferSize(qrosturm::screen_buffer->out_handle, input_record.Event.WindowBufferSizeEvent.dwSize);

            qrosturm::screen_buffer->size = input_record.Event.WindowBufferSizeEvent.dwSize;

            //SetConsoleScreenBufferInfo(qrosturm::screen_buffer->out_handle, )

            continue;
        } else if (
            input_record.EventType == KEY_EVENT
        ) {
            qrosturm::Event event;
            event.type = qrosturm::EventType::Key; 
            return event;
        }
    }

    Event event;
    event.type = qrosturm::EventType::Wait;
    return event;

#else

#endif
}

//int qrosturm::get_key_ascii() {
//#ifdef _WIN32
//    KEY_EVENT_RECORD key;
//    
//#else
//
//#endif
//}

void qrosturm::set_print_coord(int line, int column) {
#ifdef _WIN32
    qrosturm::cursor_pos.line = line;
    qrosturm::cursor_pos.column = column;
#else

#endif
}

void qrosturm::print(std::string str) {
#ifdef _WIN32
    int strlen = str.length();
    const char* c_str = str.c_str();

    int chr_buffer_cursor_index =
        qrosturm::cursor_pos.line * qrosturm::screen_buffer->size.X + qrosturm::cursor_pos.column;

    for (int i = 0; i < strlen; i++) {
        if (chr_buffer_cursor_index > qrosturm::screen_buffer->chr_buffer.size()) {
            break;
        }
        if (c_str[i] == '\0') {
            break;
        }
        
        qrosturm::screen_buffer->chr_buffer[chr_buffer_cursor_index].Char.UnicodeChar = c_str[i];
        chr_buffer_cursor_index++;
    }

    int new_chr_buffer_cursor_index = chr_buffer_cursor_index + strlen;

    qrosturm::cursor_pos.line = new_chr_buffer_cursor_index / qrosturm::screen_buffer->size.X;
    qrosturm::cursor_pos.column = new_chr_buffer_cursor_index % qrosturm::screen_buffer->size.X;
#else

#endif
}

WindowDimensions qrosturm::get_max_dimensions() {
#ifdef _WIN32
    WindowDimensions dimensions;

    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(StdOut, &csbiInfo);

    dimensions.columns = csbiInfo.srWindow.Right - csbiInfo.srWindow.Left;
    dimensions.lines = csbiInfo.srWindow.Bottom - csbiInfo.srWindow.Top;
    
    return dimensions;
#else

#endif
}
