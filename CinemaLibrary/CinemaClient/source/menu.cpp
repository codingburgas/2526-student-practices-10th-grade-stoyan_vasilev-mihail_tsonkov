#include "../header/menu.h"
#include "../header/Auth.h"

void DrawHomeScreen(bool darkMode)
{
    Color textColor = darkMode ? RAYWHITE : BLACK;
    Color boxColor = darkMode ? Color{ 60,60,70,255 } : LIGHTGRAY;

    static int selectedDay = 0;

    const char* dates[] =
    {
        "Monday 16 June",
        "Tuesday 17 June",
        "Wednesday 18 June",
        "Thursday 19 June",
        "Friday 20 June",
        "Saturday 21 June",
        "Sunday 22 June"
    };

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

    DrawText(dates[selectedDay], 400, 108, 25, textColor);

    int y = 200;

    switch (selectedDay)
    {
    case 0:
        DrawRectangle(250, y, 500, 80, boxColor);
        DrawText("Minecraft Movie", 280, y + 10, 25, textColor);
        DrawText("14:00 | Hall 1", 280, y + 45, 18, DARKGRAY);

        y += 100;

        DrawRectangle(250, y, 500, 80, boxColor);
        DrawText("How To Train Your Dragon", 280, y + 10, 25, textColor);
        DrawText("18:30 | Hall 2", 280, y + 45, 18, DARKGRAY);
        break;

    case 1:
        DrawRectangle(250, y, 500, 80, boxColor);
        DrawText("Mission Impossible", 280, y + 10, 25, textColor);
        DrawText("16:00 | Hall 1", 280, y + 45, 18, DARKGRAY);

        y += 100;

        DrawRectangle(250, y, 500, 80, boxColor);
        DrawText("Deadpool 3", 280, y + 10, 25, textColor);
        DrawText("19:30 | Hall 2", 280, y + 45, 18, DARKGRAY);

        y += 100;

        DrawRectangle(250, y, 500, 80, boxColor);
        DrawText("Inside Out 2", 280, y + 10, 25, textColor);
        DrawText("13:00 | Hall 3", 280, y + 45, 18, DARKGRAY);
        break;


    case 2:
        DrawRectangle(250, y, 500, 80, boxColor);
        DrawText("Lilo And Stitch", 280, y + 10, 25, textColor);
        DrawText("13:30 | Hall 3", 280, y + 45, 18, DARKGRAY);

        y += 100;

        DrawRectangle(250, y, 500, 80, boxColor);
        DrawText("Frozen 3", 280, y + 10, 25, textColor);
        DrawText("17:00 | Hall 2", 280, y + 45, 18, DARKGRAY);

        y += 100;

        DrawRectangle(250, y, 500, 80, boxColor);
        DrawText("Spider-Man: Beyond", 280, y + 10, 25, textColor);
        DrawText("20:30 | Hall 1", 280, y + 45, 18, DARKGRAY);
        break;


    case 3:
        DrawRectangle(250, y, 500, 80, boxColor);
        DrawText("Superman", 280, y + 10, 25, textColor);
        DrawText("19:00 | Hall 1", 280, y + 45, 18, DARKGRAY);

        y += 100;

        DrawRectangle(250, y, 500, 80, boxColor);
        DrawText("Batman Reborn", 280, y + 10, 25, textColor);
        DrawText("21:30 | Hall 2", 280, y + 45, 18, DARKGRAY);

        y += 100;

        DrawRectangle(250, y, 500, 80, boxColor);
        DrawText("The Flash", 280, y + 10, 25, textColor);
        DrawText("15:00 | Hall 3", 280, y + 45, 18, DARKGRAY);
        break;

    case 4:
        DrawRectangle(250, y, 500, 80, boxColor);
        DrawText("F1", 280, y + 10, 25, textColor);
        DrawText("20:15 | Hall 2", 280, y + 45, 18, DARKGRAY);

        y += 100;

        DrawRectangle(250, y, 500, 80, boxColor);
        DrawText("Fast X", 280, y + 10, 25, textColor);
        DrawText("18:00 | Hall 1", 280, y + 45, 18, DARKGRAY);

        y += 100;

        DrawRectangle(250, y, 500, 80, boxColor);
        DrawText("Gran Turismo", 280, y + 10, 25, textColor);
        DrawText("14:30 | Hall 3", 280, y + 45, 18, DARKGRAY);
        break;


    case 5:
        DrawRectangle(250, y, 500, 80, boxColor);
        DrawText("Elio", 280, y + 10, 25, textColor);
        DrawText("15:45 | Hall 3", 280, y + 45, 18, DARKGRAY);

        y += 100;

        DrawRectangle(250, y, 500, 80, boxColor);
        DrawText("Toy Story 5", 280, y + 10, 25, textColor);
        DrawText("18:00 | Hall 1", 280, y + 45, 18, DARKGRAY);

        y += 100;

        DrawRectangle(250, y, 500, 80, boxColor);
        DrawText("Minions 3", 280, y + 10, 25, textColor);
        DrawText("13:30 | Hall 2", 280, y + 45, 18, DARKGRAY);
        break;


    case 6:
        DrawRectangle(250, y, 500, 80, boxColor);
        DrawText("Jurassic World", 280, y + 10, 25, textColor);
        DrawText("21:00 | Hall 1", 280, y + 45, 18, DARKGRAY);

        y += 100;

        DrawRectangle(250, y, 500, 80, boxColor);
        DrawText("King Kong Returns", 280, y + 10, 25, textColor);
        DrawText("18:30 | Hall 2", 280, y + 45, 18, DARKGRAY);

        y += 100;

        DrawRectangle(250, y, 500, 80, boxColor);
        DrawText("Godzilla X", 280, y + 10, 25, textColor);
        DrawText("16:00 | Hall 3", 280, y + 45, 18, DARKGRAY);
        break;

    }

    Rectangle backBtn = { 20,20,100,40 };
    Rectangle logoutBtn = { 20, 70, 100, 40 };

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
    Rectangle logoutBtn = { 20.0f, 70.0f, 100.0f, 40.0f };

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
            if (isLoggedIn &&
                CheckCollisionPointRec(mouse, logoutBtn) &&
                IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                isLoggedIn = false;
                currentUser[0] = '\0';
                currentScreen = SCREEN_MENU;
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
            Rectangle logoutBtn = { 850,20,120,40 };

            if (CheckCollisionPointRec(mouse, backBtn) &&
                IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                currentScreen = SCREEN_MENU;
            }

            if (CheckCollisionPointRec(mouse, logoutBtn) &&
                IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                isLoggedIn = false;

                currentUser[0] = '\0';

                loginUser[0] = '\0';
                loginPass[0] = '\0';

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

                DrawText("Login",
                    loginBtn.x + 25,
                    loginBtn.y + 10,
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
            if (isLoggedIn)
            {
                DrawRectangleRec(logoutBtn, boxColor);
                DrawRectangleLinesEx(logoutBtn, 2, GRAY);

                DrawText("Logout",
                    logoutBtn.x + 15,
                    logoutBtn.y + 10,
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