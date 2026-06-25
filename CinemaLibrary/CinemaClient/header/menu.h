#pragma once
#include "precompile.h"

int window();

enum ScreenState
{
    SCREEN_MENU = 0,
    SCREEN_LOGIN,
    SCREEN_REGISTER,
    SCREEN_HOME,
    SCREEN_ADD_MOVIE,
    SCREEN_REMOVE_MOVIE
};

void DrawHomeScreen(bool darkMode, bool isAdmin, ScreenState& currentScreen, bool& isLoggedIn, char* currentUser, char* loginUser, char* loginPass);
void DrawAddMovieScreen(bool darkMode, float& cursorBlink, ScreenState& currentScreen);
void DrawRemoveMovieScreen(bool darkMode, float& cursorBlink, ScreenState& currentScreen);

struct EventInputState
{
    char yearText[32] = "";
    char monthText[32] = "";
    char dayText[32] = "";
    char descText[256] = "";

    bool yearActive = false;
    bool monthActive = false;
    bool dayActive = false;
    bool descActive = false;

    bool showAddPanel = false;

    float cursorBlink = 0.0f;
};

static bool DrawDarkModeButton(bool darkMode)
{
    Rectangle btn = { 820, 20, 150, 45 };

    Vector2 mouse = GetMousePosition();

    bool hover = CheckCollisionPointRec(mouse, btn);

    DrawRectangleRec(btn, hover ? SKYBLUE : GRAY);
    DrawRectangleLinesEx(btn, 2, DARKGRAY);

    DrawText(
        darkMode ? "Light Mode" : "Dark Mode",
        btn.x + 20,
        btn.y + 12,
        20,
        BLACK);

    if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        return !darkMode;

    return darkMode;
}