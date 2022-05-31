
// Simple Space game using my Textual UI library

#include "UIEngine.h"
#include "time.h"
#include <conio.h>
#include <thread>
#include <chrono>

using namespace UI;
using namespace std::chrono;

int ticks = 0;
std::wstring asciiNumbers[10] = { L" _____ \n/  _  \\\n|  |  |\n\\_____/"  ,
							L" ___  \n/   | \n |  | \n<____>",
							L" _____ \n<___  \\\n /  __/\n<_____|",
							L" _____ \n/  _  \\\n>-<_  <\n\\_____/",
							L" __ __ \n/  |  \\\n\\_    |\n  \\___/",
							L" _____ \n|  ___|\n|___  \\\n<_____/",
							L" ____  \n/  __| \n|  _  \\\n\_____/",
							L" _____ \n<__   \\\n  /   /\n <___/ ",
							L" _____ \n/  _  \\\n>  _  <\n\_____/",
							L" _____ \n/  _  \\\n\___  |\n|_____/" };
std::wstring spaceshipFacingUp = L"   /\\\n  (  )\n  (  )\n /|/\\|\\\n/_||||_\\";
std::wstring spaceshipFacingDown = L"\\‾||||‾/\n \\|\\/|/\n  (  )\n  (  )\n   \\/";
std::wstring ammo = L" _____  __  __  __  __  _____  _ \n/  _  \\/  \\/  \\/  \\/  \\/  _  \\<_>\n|  _  ||  \\/  ||  \\/  ||  |  | _ \n\\__|__/\\__ \\__/\\__ \\__/\\_____/<_>";
std::vector<UILabel*> bullets;
std::vector<std::tuple<int, int>> bulletPositions;
std::vector<UILabel*> enemies;
std::vector<std::tuple<int, int>> enemyPositions;
int width = 237;
int height = 66;
Screen screen(height, width);
UIEngine gameUI(&screen);
UILabel* ammoLabel = gameUI.Label(5, 1, ammo);
UILabel* ammo1thCountLabel = gameUI.Label(5, 5, asciiNumbers[5]);
UILabel* ammo0thCountLabel = gameUI.Label(13, 5, asciiNumbers[0]);
UILabel* spaceshipLabel = gameUI.Label(10, 10, spaceshipFacingUp);
int side = 1;

int x = 10;
int y = 10;
int ammoCount = 50;
int ticksSinceLastBullet = 0;
int ticksSinceLastBulletUpdate = 0;
int ticksSinceReload = 0;
int ticksSinceEnemyMovement = 0;
int ticksSinceSpaceshipUpdate = 0;


//Threaded tick function
void tickUpdate() {
	while (1)
	{
		Sleep(10);
		ticks++;
	}
}

void spaceshipMovementUpdate() {
	ticksSinceSpaceshipUpdate = ticks;
	if (GetAsyncKeyState(0x57) && y)
		spaceshipLabel->setPosition(x, --y);
	if (GetAsyncKeyState(0x41) && x)
		spaceshipLabel->setPosition(--x, y);
	if (GetAsyncKeyState(0x53) && y < height - 5)
		spaceshipLabel->setPosition(x, ++y);
	if (GetAsyncKeyState(0x44) && x < width - 8)
		spaceshipLabel->setPosition(++x, y);
}

void gameLogicUpdate() {
	if (ticks - ticksSinceLastBulletUpdate > 1)
	{
		ticksSinceLastBulletUpdate = ticks;
		for (int i = 0; i < bullets.size(); i++)
		{

			if (get<1>(bulletPositions[i]))
			{
				bullets[i]->setPosition(get<0>(bulletPositions[i]), --get<1>(bulletPositions[i]));
			}
			else
			{
				gameUI.removeElement(bullets[i]);
				bullets.erase(bullets.begin() + i);
				bulletPositions.erase(bulletPositions.begin() + i);
			}
		}
	}
	if (ticks - ticksSinceEnemyMovement > 1)
	{
		ticksSinceEnemyMovement = ticks;
		if (get<0>(enemyPositions[0]) == 1)
		{
			side = 1;
			for (int i = 0; i < enemies.size(); i++)
			{
				enemies[i]->setPosition(++get<0>(enemyPositions[i]), ++++get<1>(enemyPositions[i]));
			}
		}
		else if (get<0>(enemyPositions[enemyPositions.size() - 1]) == width - 10)
		{
			side = 0;
			for (int i = 0; i < enemies.size(); i++)
			{
				enemies[i]->setPosition(--get<0>(enemyPositions[i]), ++++get<1>(enemyPositions[i]));
			}
		}
		if (side)
		{
			for (int i = 0; i < enemies.size(); i++)
			{
				enemies[i]->setPosition(++get<0>(enemyPositions[i]), get<1>(enemyPositions[i]));
			}
		}
		else
		{
			for (int i = 0; i < enemies.size(); i++)
			{
				enemies[i]->setPosition(--get<0>(enemyPositions[i]), get<1>(enemyPositions[i]));
			}
		}
	}
	if (ticks - ticksSinceLastBullet > 5)
	{
		ticksSinceLastBullet = ticks;
		if (GetAsyncKeyState(VK_SPACE) && ammoCount)
		{
			ammoCount--;
			ammo0thCountLabel->setText(asciiNumbers[ammoCount % 10]);
			ammo1thCountLabel->setText(asciiNumbers[ammoCount / 10 % 10]);
			bullets.push_back(gameUI.Label(x + 3, y - 1, L"|"));
			bulletPositions.push_back({ x + 3,y - 1 });
		}
	}
	if (ticks - ticksSinceReload > 15)
	{
		ticksSinceReload = ticks;
		if (ammoCount < 50 && !GetAsyncKeyState(VK_SPACE))
		{
			ammoCount++;
			ammo0thCountLabel->setText(asciiNumbers[ammoCount % 10]);
			ammo1thCountLabel->setText(asciiNumbers[ammoCount / 10 % 10]);
		}
	}
}

void animationUpdate() {
	gameUI.drawElements();
}

int main() {
	spaceshipLabel->setVisibility(3);
	ammoLabel->setVisibility(2);
	ammo0thCountLabel->setVisibility(2);
	ammo1thCountLabel->setVisibility(2);
	srand(time(0));
	for (int i = 0; i < 50; i++)
	{
		gameUI.Label((rand() % width), (rand() % height), L".");
		gameUI.Label((rand() % width), (rand() % height), L"*");
	}
	for (int i = 0; i < 10; i++)
	{
		enemies.push_back(gameUI.Label(40 + i * 13, 10, spaceshipFacingUp));
		enemyPositions.push_back({ 40 + i * 13 ,10 });
		enemies[i]->setVisibility(3);
	}
	Sleep(1000);
	gameUI.drawElements();
	//Tick update handling
	std::thread tickThread(tickUpdate);
	while (1) {
		std::thread spaceshipMovementThread(spaceshipMovementUpdate);
		spaceshipMovementThread.detach();
		std::thread gameLogicThread(gameLogicUpdate);
		gameLogicThread.join();
		std::thread animationThread(animationUpdate);
		animationThread.join();

	}


}

