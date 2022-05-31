#include "Screen.h"


namespace UI {
	Screen::Screen(int lRow, int lCol)
	{
		system("cls");
		
		//Setting the screen to fullscreen
		::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);

		// retrieve screen buffer and cursor info
		CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
		CONSOLE_CURSOR_INFO cursorInfo;
		GetConsoleScreenBufferInfo(hConsoleOut, &scrBufferInfo);
		GetConsoleCursorInfo(hConsoleOut, &cursorInfo);

		// setting the cursor invisible
		cursorInfo.bVisible = false;
		SetConsoleCursorInfo(hConsoleOut, &cursorInfo);

		// current window size
		short winWidth = scrBufferInfo.srWindow.Right - scrBufferInfo.srWindow.Left + 1;
		short winHeight = scrBufferInfo.srWindow.Bottom - scrBufferInfo.srWindow.Top + 1;

		// current screen buffer size
		short scrBufferWidth = scrBufferInfo.dwSize.X;
		short scrBufferHeight = scrBufferInfo.dwSize.Y;

		// to remove the scrollbar, make sure the window height matches the screen buffer height
		COORD newSize;
		newSize.X = scrBufferWidth;
		newSize.Y = winHeight;

		// set the new screen buffer dimensions
		int Status = SetConsoleScreenBufferSize(hConsoleOut, newSize);
		this->lRow = lRow;
		this->lCol = lCol;

		//disabling quick edit mode
		DWORD prev_mode;
		GetConsoleMode(hConsoleIn, &prev_mode);
		SetConsoleMode(hConsoleIn, prev_mode & ~ENABLE_QUICK_EDIT_MODE | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

		// Initialize the screen memory
		std::fill(&currentScreen[0][0], &currentScreen[0][0] + lCol * lRow, ' ');
		std::fill(&nextScreen[0][0], &nextScreen[0][0] + lCol * lRow, ' ');
	}

	tuple<int, int> Screen::getScreenSize()
	{
		return { lRow,lCol };
	}

	void Screen::drawChar(int x, int y, std::wstring character)
	{
		nextScreen[y][x] = character;
	}

	void Screen::setInput(int x, int y)
	{
		//setting input coordiante
		inputCoord = { (short)x,(short)y };
	}

	std::string Screen::getInput()
	{
		return inputValue;
	}

	void Screen::Update() {
		//LockWindowUpdate(GetConsoleWindow());
		for (int i = 0; i < lRow; i++)
		{	
			for (int j = 0; j < lCol; j++)
			{
				if (currentScreen[i][j] != nextScreen[i][j])
				{
					SetConsoleCursorPosition(hConsoleOut, { (short)j,(short)i });
					wprintf(nextScreen[i][j].c_str());
				}
			}	
		}
		//LockWindowUpdate(NULL);
		if (inputCoord.X && inputCoord.Y)
		{
			//Input handling
			SetConsoleCursorPosition(hConsoleOut, inputCoord);
			cin >> inputValue;
			SetConsoleCursorPosition(hConsoleOut, inputCoord);
			for (int i = 0; i < inputValue.size(); i++)
			{
				wprintf(L" ");
			}
			inputCoord = {};
			Update();

		}
		else
		{
			std::copy(&nextScreen[0][0], &nextScreen[0][0]+lCol*lRow, &currentScreen[0][0]);
			std::fill(&nextScreen[0][0], &nextScreen[0][0] + lCol * lRow, ' ');
		}

	}

	void Screen::Clear()
	{
		//Clearing screen
		std::fill(&currentScreen[0][0], &currentScreen[0][0] + lCol * lRow, ' ');
		std::fill(&nextScreen[0][0], &nextScreen[0][0] + lCol * lRow, ' ');
		Update();
	}
}

