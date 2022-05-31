#pragma once
#include <array>
#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <fcntl.h>
#include <io.h>
#include <tuple>
#include <vector>
#include <iomanip>

#define Black L"\u001b[30m"
#define Red L"\u001b[31m"
#define Green L"\u001b[32m"
#define Yellow L"\u001b[33m"
#define Blue L"\u001b[34m"
#define Magenta L"\u001b[35m"
#define Cyan L"\u001b[36m"
#define White L"\u001b[37m"
#define Bright L";1m"

#define BackgroundBlack L"\u001b[40m"
#define BackgroundRed L"\u001b[41m"
#define BackgroundGreen L"\u001b[42m"
#define BackgroundYellow L"\u001b[43m"
#define BackgroundBlue L"\u001b[44m"
#define BackgroundMagenta L"\u001b[45m"
#define BackgroundCyan L"\u001b[46m"
#define BackgroundWhite L"\u001b[47m"

#define Bold L"\u001b[1m"
#define Underline L"\u001b[4m"

#define Reset L"\u001b[0m"

using namespace std;

namespace UI {
	class Screen {
	public:
		Screen(int, int);
		void drawChar(int, int, std::wstring);
		void setInput(int, int);
		std::string getInput();
		tuple<int, int> getScreenSize();
		void Update();
		void Clear();
	private:
		// get handle to the console window
		HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
		HANDLE hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);
		std::wstring nextScreen[66][237];
		std::wstring currentScreen[66][237];
		COORD inputCoord;
		std::string inputValue = "";
		int lRow;
		int lCol;
		void setCursorPosition(int,int);

	};
}
