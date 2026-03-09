#include "../header/menu.h"

int window()
{
	const int screenWidth = 1000;
	const int screenHeight = 800;

	InitWindow(screenWidth, screenHeight, "Cinema");
	SetTargetFPS(60);
	ScreenState currentScreen = SCREEN_MENU;

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		if (currentScreen == SCREEN_MENU)
		{
			DrawText("Cinema", 180, 150, 50, DARKBLUE);
		}
		EndDrawing();
	}
	CloseWindow();

	
	return 0;
}