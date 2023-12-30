// Game Name: Square Sprinter
// Written by: Alexandra Shellans
// Date: 12/5/22
//
// Instructions: Move the cursor at the bottom of the screen with the 4 and 6 or arrow keys to
// avoid the incoming squares. After each round, points will be added to your total score. 
// Survive as long as you can without hitting a square to beat your high score!

#include "graphics.h"
#include <string>
#include <random>

using namespace std;

const int BACKGROUND_COLOR = BLACK;
const int TEXT_COLOR = WHITE;

random_device myEngine;
uniform_real_distribution<double> randomXLocation(100, 1800);
uniform_real_distribution<double> randomColor(BLUE, YELLOW);

// Function prototypes
void welcomeScreen();
void printScore(int);
void printRound(int);

int main()
{
	bool keepGoing = true;
	char keyPressed;
	

	initwindow(1900, 1000, (char*)"Square Sprinter", 10, 10);

	welcomeScreen();

	bool playAgain = true;

	do {
		//
		// -------- Main "Play Again" loop
		//

		// Draw cursor
		double cursorX = 950, cursorPrev;
		const double cursorY = 800;

		setcolor(WHITE);
		setfillstyle(SOLID_FILL, WHITE);
		pieslice(cursorX, cursorY, 240, 300, 50);

		// Print initial score and round number (resets after each game)
		int score = 0;
		int round = 1;

		printScore(score);
		printRound(round);

		// 
		// -------- Main "Keep Going" loop
		// 
		keepGoing = true;
		while (keepGoing) {

			// Variables to draw and move squares
			double xVel, yVel = 2.0;
			double x1[10];
			double y1[10] = { 400, 400, 400, 400, 400, 400, 400, 400, 400, 400 };
			double x2[10];
			double y2[10] = { 430, 430, 430, 430, 430, 430, 430, 430, 430, 430 };
			double color[10];
			double x1Prev[10], y1Prev[10], x2Prev[10], y2Prev[10];

			for (int i = 0; i < 10; i++) {

				x1[i] = randomXLocation(myEngine);
				x2[i] = x1[i] + 30;
				color[i] = randomColor(myEngine);
			}

			setfillstyle(SOLID_FILL, color[0]);
			bar(x1[0], y1[0], x2[0], y2[0]);

			// Main square loop to create field of moving squares
			for (int j = 0; j <= 9; j++) {

				while ((!(x1[j] >= 1900) && !(x2[j] <= 0) && !(y1[j] >= 1000)) && keepGoing) {

					delay(5);

					x1Prev[0] = x1[0];
					y1Prev[0] = y1[0];
					x2Prev[0] = x2[0];
					y2Prev[0] = y2[0];

					if (x1[0] <= 380) {

						xVel = -4.0;
						x1[0] = x1[0] + xVel - 0.5;
						y1[0] += yVel;
						x2[0] += xVel;
						y2[0] = y2[0] + yVel + 0.5;
					}
					else if (x1[0] <= 760) {

						xVel = -2.0;
						x1[0] = x1[0] + xVel - 1;
						y1[0] += yVel;
						x2[0] += xVel;
						y2[0] = y2[0] + yVel + 1;
					}
					else if (x1[0] <= 1140) {

						xVel = 0.0;
						x1[0] = x1[0] + xVel - 0.75;
						y1[0] += yVel;
						x2[0] = x2[0] + xVel + 0.75;
						y2[0] = y2[0] + yVel + 1.5;
					}
					else if (x1[0] <= 1520) {

						xVel = 2.0;
						x1[0] += xVel;
						y1[0] += yVel;
						x2[0] = x2[0] + xVel + 1;
						y2[0] = y2[0] + yVel + 1;
					}
					else if (x1[0] <= 1900) {

						xVel = 4.0;
						x1[0] += xVel;
						y1[0] += yVel;
						x2[0] = x2[0] + xVel + 0.5;
						y2[0] = y2[0] + yVel + 0.5;
					}

					// Check for collision between cursor and square
					double rightDistance = (x1[0] - cursorX);
					double leftDistance = (cursorX - x2[0]);
					double topDistance = (y1[0] - cursorY);
					double bottomDistance = (cursorY - y2[0]);

					if ((rightDistance <= 20 && rightDistance > 0 && bottomDistance <= 0 && topDistance < 20)
						|| (leftDistance <= 20 && leftDistance > 0 && bottomDistance <= 0 && topDistance < 20)
						|| (cursorX > x1[0] && cursorX < x2[0] && bottomDistance <= 0 && topDistance < 20)) {

						setcolor(BLACK);
						setfillstyle(SOLID_FILL, BLACK);
						pieslice(cursorX, cursorY, 240, 300, 50);

						for (int i = 50; i <= 200; i += 50) {

							setcolor(WHITE);
							circle(cursorX, cursorY, i);
							delay(100);
						}
						for (int i = 50; i <= 200; i += 50) {

							setcolor(BLACK);
							circle(cursorX, cursorY, i);
							delay(100);
						}

						keepGoing = false;
					}

					setfillstyle(SOLID_FILL, BLACK);
					bar(x1Prev[0], y1Prev[0], x2Prev[0], y2Prev[0]);

					setfillstyle(SOLID_FILL, color[0]);
					bar(x1[0], y1[0], x2[0], y2[0]);

					for (int i = 0; i <= 9; i++) {

						if ((y1[i] > 450) || (x1[i] > 1850)) {

							setfillstyle(SOLID_FILL, color[i + 1]);
							bar(x1[i + 1], y1[i + 1], x2[i + 1], y2[i + 1]);

							x1Prev[i + 1] = x1[i + 1];
							y1Prev[i + 1] = y1[i + 1];
							x2Prev[i + 1] = x2[i + 1];
							y2Prev[i + 1] = y2[i + 1];

							if (x1[i + 1] <= 380) {

								xVel = -4.0;
								x1[i + 1] = x1[i + 1] + xVel - 0.5;
								y1[i + 1] += yVel;
								x2[i + 1] += xVel;
								y2[i + 1] = y2[i + 1] + yVel + 0.5;
							}
							else if (x1[i + 1] <= 760) {

								xVel = -2.0;
								x1[i + 1] = x1[i + 1] + xVel - 1;
								y1[i + 1] += yVel;
								x2[i + 1] += xVel;
								y2[i + 1] = y2[i + 1] + yVel + 1;
							}
							else if (x1[i + 1] <= 1140) {

								xVel = 0.0;
								x1[i + 1] = x1[i + 1] + xVel - 0.75;
								y1[i + 1] += yVel;
								x2[i + 1] = x2[i + 1] + xVel + 0.75;
								y2[i + 1] = y2[i + 1] + yVel + 1.5;
							}
							else if (x1[i + 1] <= 1520) {

								xVel = 2.0;
								x1[i + 1] += xVel;
								y1[i + 1] += yVel;
								x2[i + 1] = x2[i + 1] + xVel + 1;
								y2[i + 1] = y2[i + 1] + yVel + 1;
							}
							else if (x1[i + 1] <= 1900) {

								xVel = 4.0;
								x1[i + 1] += xVel;
								y1[i + 1] += yVel;
								x2[i + 1] = x2[i + 1] + xVel + 0.5;
								y2[i + 1] = y2[i + 1] + yVel + 0.5;
							}

							// Check for collision between cursor and square
							double rightDistance = (x1[i + 1] - cursorX);
							double leftDistance = (cursorX - x2[i + 1]);
							double topDistance = (y1[i + 1] - cursorY);
							double bottomDistance = (cursorY - y2[i + 1]);

							if ((rightDistance <= 20 && rightDistance > 0 && bottomDistance <= 0 && topDistance < 20)
								|| (leftDistance <= 20 && leftDistance > 0 && bottomDistance <= 0 && topDistance < 20)
								|| (cursorX > x1[i + 1] && cursorX < x2[i + 1] && bottomDistance <= 0 && topDistance < 20)) {

								setcolor(BLACK);
								setfillstyle(SOLID_FILL, BLACK);
								pieslice(cursorX, cursorY, 240, 300, 50);

								for (int i = 50; i <= 200; i += 50) {

									setcolor(WHITE);
									circle(cursorX, cursorY, i);
									delay(100);
								}
								for (int i = 50; i <= 200; i += 50) {

									setcolor(BLACK);
									circle(cursorX, cursorY, i);
									delay(100);
								}

								keepGoing = false;
							}

							setfillstyle(SOLID_FILL, BLACK);
							bar(x1Prev[i + 1], y1Prev[i + 1], x2Prev[i + 1], y2Prev[i + 1]);

							setfillstyle(SOLID_FILL, color[i + 1]);
							bar(x1[i + 1], y1[i + 1], x2[i + 1], y2[i + 1]);
						}
					}

					// -------- Check to see if a key has been pressed
					if (kbhit()) {

						keyPressed = getch();


						// KEY: Q or ESC pressed
						if (keyPressed == 'q' || keyPressed == 'Q' || keyPressed == 0x1b) {

							keepGoing = false;
						}

						// Key to move cursor to the left
						if (keyPressed == '4' || keyPressed == 0x4b) {

							if (cursorX > 50) {

								cursorPrev = cursorX;

								setcolor(BLACK);
								setfillstyle(SOLID_FILL, BLACK);
								pieslice(cursorPrev, cursorY, 240, 300, 50);

								setcolor(WHITE);
								setfillstyle(SOLID_FILL, WHITE);
								pieslice((cursorX -= 30), cursorY, 240, 300, 50);
							}
						}

						// Key to move cursor to the right
						if (keyPressed == '6' || keyPressed == 0x4d) {

							if (cursorX < 1850) {

								cursorPrev = cursorX;

								setcolor(BLACK);
								setfillstyle(SOLID_FILL, BLACK);
								pieslice(cursorPrev, cursorY, 240, 300, 50);

								setcolor(WHITE);
								setfillstyle(SOLID_FILL, WHITE);
								pieslice((cursorX += 30), cursorY, 240, 300, 50);
							}
						}
					}
				}
			} // end main square loop

			// Update and reprint score after each round
			score += 10;
			printScore(score);

			round += 1;
			printRound(round);

		} // end while(keepGoing)

		// Game has ended
		setcolor(WHITE);
		outtextxy(10, 10, (char*)"GAME OVER! Play Again? (Y/N)");
		keyPressed = getch();
		if (keyPressed == 'y' || keyPressed == 'Y') {

			welcomeScreen();
		}
		else {

			playAgain = false;
		}

	} while (playAgain == true);
	return 0;
} // end main()


void welcomeScreen() {

	setbkcolor(BACKGROUND_COLOR);
	cleardevice();

	// Text
	setcolor(TEXT_COLOR);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 5);
	outtextxy(430, 300, (char*)"Welcome to Square Sprinter!");

	settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
	outtextxy(470, 450, (char*)"How to play: Guide your cursor through the");
	outtextxy(440, 480, (char*)"field of squares, using the 4 and 6 or arrow");
	outtextxy(510, 510, (char*)"keys to move. Earn points by surviving");
	outtextxy(540, 540, (char*)"each round without hitting a square!");

	outtextxy(650, 700, (char*)"Press any key to begin...");

	// Graphics
	setfillstyle(SOLID_FILL, BLUE);
	bar(200, 300, 250, 350);

	setfillstyle(SOLID_FILL, GREEN);
	bar(1500, 600, 1580, 680);

	setfillstyle(SOLID_FILL, CYAN);
	bar(1400, 850, 1450, 900);

	setfillstyle(SOLID_FILL, RED);
	bar(500, 100, 570, 170);

	setfillstyle(SOLID_FILL, MAGENTA);
	bar(400, 600, 450, 650);

	setfillstyle(SOLID_FILL, LIGHTGRAY);
	bar(300, 400, 330, 430);

	setfillstyle(SOLID_FILL, BROWN);
	bar(200, 700, 290, 790);

	setfillstyle(SOLID_FILL, DARKGRAY);
	bar(1000, 200, 1040, 240);

	setfillstyle(SOLID_FILL, LIGHTBLUE);
	bar(1100, 80, 1160, 140);

	setfillstyle(SOLID_FILL, LIGHTGREEN);
	bar(600, 850, 640, 890);

	setfillstyle(SOLID_FILL, LIGHTCYAN);
	bar(1650, 700, 1680, 730);

	setfillstyle(SOLID_FILL, LIGHTRED);
	bar(1100, 780, 1160, 840);

	setfillstyle(SOLID_FILL, LIGHTMAGENTA);
	bar(1700, 400, 1750, 450);

	setfillstyle(SOLID_FILL, YELLOW);
	bar(1500, 150, 1590, 240);

	getch();
	cleardevice();
}

void printScore(int score) {

	char s[20];
	sprintf_s(s, "Score: %d", score);

	setcolor(WHITE);
	outtextxy(10, 30, &s[0]); 
}

void printRound(int round) {

	char r[20];
	sprintf_s(r, "Round %d", round);

	setcolor(WHITE);
	outtextxy(10, 10, &r[0]);
}