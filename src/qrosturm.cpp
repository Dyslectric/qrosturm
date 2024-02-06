#include <Windows.h>
#include <stdio.h>

#include "qrosturm.h"

using namespace qrosturm;

// get max size of terminal for window and create a buffer of that size
void qrosturm::init() {
#ifdef _WIN32
	HANDLE hStdOut;
	HANDLE hNewScreenBuffer;
    SMALL_RECT srctReadRect;
    SMALL_RECT srctWriteRect;
    CHAR_INFO chrBuffer[160]; // [2][80];
    COORD coordBufSize;
    COORD coordBufCoord;
    BOOL fSuccess;

    PCONSOLE_SCREEN_BUFFER_INFO buffer_info;
    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfo(hStdOut, buffer_info);

    //
    //
    //  Here is where you were working dude
    //
    //
    buffer_info.

	hNewScreenBuffer = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL);

    if (hStdOut == INVALID_HANDLE_VALUE ||
        hNewScreenBuffer == INVALID_HANDLE_VALUE)
    {
        printf("CreateConsoleScreenBuffer failed - (%d)\n", GetLastError());
        exit(1);
    }

    // Make the new screen buffer the active screen buffer.

    if (!SetConsoleActiveScreenBuffer(hNewScreenBuffer))
    {
        printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError());
        exit(1);
    }

    // Set the source rectangle.

    srctReadRect.Top = 10;    // top left: row 0, col 0
    srctReadRect.Left = 10;
    srctReadRect.Bottom = 15; // bot. right: row 1, col 79
    srctReadRect.Right = 60;

    // The temporary buffer size is 2 rows x 80 columns.

    coordBufSize.Y = 2;
    coordBufSize.X = 80;

    // The top left destination cell of the temporary buffer is
    // row 0, col 0.

    coordBufCoord.X = 0;
    coordBufCoord.Y = 0;

    // Copy the block from the screen buffer to the temp. buffer.

    fSuccess = ReadConsoleOutput(
        hStdOut,        // screen buffer to read from
        chrBuffer,      // buffer to copy into
        coordBufSize,   // col-row size of chiBuffer
        coordBufCoord,  // top left dest. cell in chiBuffer
        &srctReadRect); // screen buffer source rectangle
    if (!fSuccess)
    {
        printf("ReadConsoleOutput failed - (%d)\n", GetLastError());
        exit(1);
    }

    // Set the destination rectangle.

    srctWriteRect.Top = 10;    // top lt: row 10, col 0
    srctWriteRect.Left = 10;
    srctWriteRect.Bottom = 15; // bot. rt: row 11, col 79
    srctWriteRect.Right = 60;

    // Copy from the temporary buffer to the new screen buffer.

    fSuccess = WriteConsoleOutput(
        hNewScreenBuffer, // screen buffer to write to
        chrBuffer,        // buffer to copy from
        coordBufSize,     // col-row size of chiBuffer
        coordBufCoord,    // top left src cell in chiBuffer
        &srctWriteRect);  // dest. screen buffer rectangle
    if (!fSuccess)
    {
        printf("WriteConsoleOutput failed - (%d)\n", GetLastError());
        exit(1);
    }
    Sleep(5000);

    // Restore the original active screen buffer.

    if (!SetConsoleActiveScreenBuffer(hStdOut))
    {
        printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError());
        exit(1);
    }

#else

#endif
}

void qrosturm::clear() {
#ifdef _WIN32

#else

#endif
}

void qrosturm::refresh() {
#ifdef _WIN32

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
