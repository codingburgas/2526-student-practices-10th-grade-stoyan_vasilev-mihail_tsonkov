#include "../header/menu.h"
#include "../header/Auth.h"

void DrawHomeScreen(bool darkMode)
{
    Color textColor = darkMode ? RAYWHITE : BLACK;
    Color boxColor = darkMode ? Color{ 60,60,70,255 } : LIGHTGRAY;

    static int selectedDay = 0;

    Rectangle prevBtn = { 250,100,60,40 };
    Rectangle nextBtn = { 690,100,60,40 };

    Vector2 mouse = GetMousePosition();

    if (CheckCollisionPointRec(mouse, prevBtn) &&
        IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (selectedDay > 0)
            selectedDay--;
    }

    if (CheckCollisionPointRec(mouse, nextBtn) &&
        IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (selectedDay < 6)
            selectedDay++;
    }

    DrawText("Movies In Cinema", 320, 40, 35, textColor);

    DrawRectangleRec(prevBtn, boxColor);
    DrawRectangleRec(nextBtn, boxColor);

    DrawText("<", 272, 108, 25, textColor);
    DrawText(">", 712, 108, 25, textColor);

    DrawText(TextFormat("Day %d", selectedDay), 450, 108, 25, textColor);

    int y = 200;

    switch (selectedDay)
    {
    case 0:
        DrawRectangle(250, y, 500, 60, boxColor);
        DrawText("Minecraft Movie", 280, y + 18, 25, textColor);

        y += 80;

        DrawRectangle(250, y, 500, 60, boxColor);
        DrawText("How To Train Your Dragon", 280, y + 18, 25, textColor);
        break;

    case 1:
        DrawRectangle(250, y, 500, 60, boxColor);
        DrawText("Mission Impossible", 280, y + 18, 25, textColor);
        break;

    case 2:
        DrawRectangle(250, y, 500, 60, boxColor);
        DrawText("Lilo And Stitch", 280, y + 18, 25, textColor);
        break;

    case 3:
        DrawRectangle(250, y, 500, 60, boxColor);
        DrawText("Superman", 280, y + 18, 25, textColor);
        break;

    case 4:
        DrawRectangle(250, y, 500, 60, boxColor);
        DrawText("F1", 280, y + 18, 25, textColor);
        break;

    case 5:
        DrawRectangle(250, y, 500, 60, boxColor);
        DrawText("Elio", 280, y + 18, 25, textColor);
        break;

    case 6:
        DrawRectangle(250, y, 500, 60, boxColor);
        DrawText("Jurassic World", 280, y + 18, 25, textColor);
        break;
    }

    Rectangle backBtn = { 20,20,100,40 };

    DrawRectangleRec(backBtn, boxColor);
    DrawRectangleLinesEx(backBtn, 2, GRAY);
    DrawText("Back", 45, 30, 20, textColor);
}

int window()
{
    const int screenWidth = 1000;
    const int screenHeight = 800;

    static char loginUser[64] = "";
    static char loginPass[64] = "";

    static char regUser[64] = "";
    static char regPass[64] = "";
    static char regConfirm[64] = "";

    bool loginUserActive = false;
    bool loginPassActive = false;

    bool regUserActive = false;
    bool regPassActive = false;
    bool regConfirmActive = false;

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
        Vector2 mouse = GetMousePosition();

        if (currentScreen == SCREEN_MENU)
        {
            if (!isLoggedIn &&
                CheckCollisionPointRec(mouse, loginBtn) &&
                IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                currentScreen = SCREEN_LOGIN;
            }
        }
        else if (currentScreen == SCREEN_LOGIN ||
            currentScreen == SCREEN_REGISTER)
        {
            if (DrawAuthBackButton(mouse, darkMode))
            {
                currentScreen = SCREEN_MENU;
            }
        }
        else if (currentScreen == SCREEN_HOME)
        {
            Rectangle backBtn = { 20,20,100,40 };

            if (CheckCollisionPointRec(mouse, backBtn) &&
                IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                currentScreen = SCREEN_MENU;
            }
        }

        BeginDrawing();

        Color background =
            darkMode ? Color{ 25,25,30,255 } : RAYWHITE;

        Color textColor =
            darkMode ? RAYWHITE : BLACK;

        Color boxColor =
            darkMode ? Color{ 60,60,70,255 } : LIGHTGRAY;

        ClearBackground(background);

        darkMode = DrawDarkModeButton(darkMode);

        if (currentScreen == SCREEN_MENU)
        {
            if (!isLoggedIn)
            {
                DrawRectangleRec(loginBtn, boxColor);
                DrawRectangleLinesEx(loginBtn, 2, GRAY);

                DrawText(
                    "Login",
                    (int)loginBtn.x + 25,
                    (int)loginBtn.y + 10,
                    20,
                    textColor);
            }
            else
            {
                DrawText(
                    TextFormat("Welcome, %s", currentUser),
                    20,
                    20,
                    20,
                    textColor);
            }

            DrawText(
                "Cinema",
                screenWidth / 2 -
                MeasureText("Cinema", 60) / 2,
                screenHeight / 2 - 30,
                60,
                textColor);
        }
        else if (currentScreen == SCREEN_LOGIN)
        {
            DrawLoginScreen(
                darkMode,
                loginUser,
                loginPass,
                loginUserActive,
                loginPassActive,
                authCursorBlink,
                currentScreen,
                isLoggedIn,
                currentUser);
        }
        else if (currentScreen == SCREEN_REGISTER)
        {
            DrawRegisterScreen(
                darkMode,
                regUser,
                regPass,
                regConfirm,
                regUserActive,
                regPassActive,
                regConfirmActive,
                authCursorBlink,
                currentScreen);
        }
        else if (currentScreen == SCREEN_HOME)
        {
            DrawHomeScreen(darkMode);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}