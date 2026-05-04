#include "../header/menu.h"
#include "../Auth.h"

int window()
{
    const int screenWidth = 1000;
    const int screenHeight = 800;
    static char loginUser[64] = "";
    static char loginPass[64] = "";
    static char regUser[64] = "";
    static char regPass[64] = "";
    static char regConfirm[64] = "";
    bool loginUserActive = false, loginPassActive = false;
    bool regUserActive = false, regPassActive = false, regConfirmActive = false;
    float authCursorBlink = 0.0f;
    bool isLoggedIn = false;
    char currentUser[64] = "";
    static EventInputState eventInputState;

    InitWindow(screenWidth, screenHeight, "Cinema");
    SetTargetFPS(60);
    ScreenState currentScreen = SCREEN_MENU;
    bool darkMode = false;

    Rectangle loginBtn = { 20.0f, 20.0f, 100.0f, 40.0f };

    while (!WindowShouldClose())
    {
        {
            Vector2 mouse = GetMousePosition();

            if (currentScreen == SCREEN_MENU)
            {
                if (!isLoggedIn && CheckCollisionPointRec(mouse, loginBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    currentScreen = SCREEN_LOGIN;
            }
            else if (currentScreen == SCREEN_LOGIN || currentScreen == SCREEN_REGISTER)
            {
                if (DrawAuthBackButton(mouse, darkMode))
                    currentScreen = SCREEN_MENU;
            }
            else
            {
                Rectangle backBtn = { 20.0f, 20.0f, 100.0f, 40.0f };
                if (CheckCollisionPointRec(mouse, backBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    currentScreen = SCREEN_MENU;
            }

            BeginDrawing();
            Color background = darkMode ? Color{ 25, 25, 30, 255 } : RAYWHITE;
            Color textColor = darkMode ? RAYWHITE : BLACK;
            Color boxColor = darkMode ? Color{ 60, 60, 70, 255 } : LIGHTGRAY;
            ClearBackground(background);

            darkMode = DrawDarkModeButton(darkMode);

            if (currentScreen == SCREEN_MENU)
            {
                if (!isLoggedIn)
                {
                    DrawRectangleRec(loginBtn, boxColor);
                    DrawRectangleLinesEx(loginBtn, 2, GRAY);
                    DrawText("Login", (int)loginBtn.x + 25, (int)loginBtn.y + 10, 20, textColor);
                }
                else
                {
                    DrawText(TextFormat("Welcome, %s", currentUser), 20, 20, 20, textColor);
                }

                DrawText("Cinema", screenWidth / 2 - MeasureText("Cinema", 60) / 2, screenHeight / 2 - 30, 60, textColor);
            }
            else if (currentScreen == SCREEN_LOGIN)
            {
                DrawLoginScreen(darkMode, loginUser, loginPass, loginUserActive, loginPassActive,
                    authCursorBlink, currentScreen, isLoggedIn, currentUser);
            }
            else if (currentScreen == SCREEN_REGISTER)
            {
                DrawRegisterScreen(darkMode, regUser, regPass, regConfirm, regUserActive,
                    regPassActive, regConfirmActive, authCursorBlink, currentScreen);
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}