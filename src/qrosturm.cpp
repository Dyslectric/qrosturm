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

    StdOut = hStdOut;

    qrosturm::clear(' ');

    SetConsoleActiveScreenBuffer(buffer->out_handle);
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
#else

#endif
}

void qrosturm::set_echo() {
#ifdef _WIN32

#else

#endif
}

void qrosturm::set_echo_off() {
#ifdef _WIN32

#else

#endif
}

void qrosturm::end() {
#ifdef _WIN32
    SetConsoleActiveScreenBuffer(StdOut);
#else

#endif
}

Key qrosturm::get_key() {
#ifdef _WIN32
    return ToDo;
#else

#endif
}

void qrosturm::move_cursor(WindowPosition position) {
#ifdef _WIN32

#else

#endif
}

void qrosturm::print(const char* fmt, ...) {
#ifdef _WIN32

#else

#endif
}

WindowDimensions get_max_dimensions() {
#ifdef _WIN32
    WindowDimensions dimensions;
    return dimensions;
#else

#endif
}
