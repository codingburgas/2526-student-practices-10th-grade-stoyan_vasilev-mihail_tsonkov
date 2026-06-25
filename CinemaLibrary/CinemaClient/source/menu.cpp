#include "../header/menu.h"
#include "../header/Auth.h"

struct Movie
{
    int dayIndex;
    char name[128];
    char time[32];
    char hall[32];
};

void CreateDefaultMoviesFile()
{
    ofstream file("movies.txt");
    if (!file.is_open()) return;

    file << "0|Minecraft Movie|14:00|Hall 1\n";
    file << "0|How To Train Your Dragon|18:30|Hall 2\n";
    file << "1|Mission Impossible|16:00|Hall 1\n";
    file << "1|Deadpool 3|19:30|Hall 2\n";
    file << "1|Inside Out 2|13:00|Hall 3\n";
    file << "2|Lilo And Stitch|13:30|Hall 3\n";
    file << "2|Frozen 3|17:00|Hall 2\n";
    file << "2|Spider-Man: Beyond|20:30|Hall 1\n";
    file << "3|Superman|19:00|Hall 1\n";
    file << "3|Batman Reborn|21:30|Hall 2\n";
    file << "3|The Flash|15:00|Hall 3\n";
    file << "4|F1|20:15|Hall 2\n";
    file << "4|Fast X|18:00|Hall 1\n";
    file << "4|Gran Turismo|14:30|Hall 3\n";
    file << "5|Elio|15:45|Hall 3\n";
    file << "5|Toy Story 5|18:00|Hall 1\n";
    file << "5|Minions 3|13:30|Hall 2\n";
    file << "6|Jurassic World|21:00|Hall 1\n";
    file << "6|King Kong Returns|18:30|Hall 2\n";
    file << "6|Godzilla X|16:00|Hall 3\n";

    file.close();
}

void LoadMovies(Movie movies[], int& count, int maxMovies)
{
    count = 0;

    ifstream check("movies.txt");
    if (!check.is_open())
    {
        check.close();
        CreateDefaultMoviesFile();
    }
    else
    {
        check.close();
    }

    ifstream file("movies.txt");
    if (!file.is_open()) return;

    string line;
    while (getline(file, line) && count < maxMovies)
    {
        if (line.empty()) continue;

        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);

        if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos)
            continue;

        string dayStr = line.substr(0, pos1);
        string nameStr = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string timeStr = line.substr(pos2 + 1, pos3 - pos2 - 1);
        string hallStr = line.substr(pos3 + 1);

        movies[count].dayIndex = atoi(dayStr.c_str());
        strncpy(movies[count].name, nameStr.c_str(), 127);
        movies[count].name[127] = '\0';
        strncpy(movies[count].time, timeStr.c_str(), 31);
        movies[count].time[31] = '\0';
        strncpy(movies[count].hall, hallStr.c_str(), 31);
        movies[count].hall[31] = '\0';

        count++;
    }
    file.close();
}

void SaveMovies(Movie movies[], int count)
{
    ofstream file("movies.txt");
    if (!file.is_open()) return;

    for (int i = 0; i < count; i++)
    {
        file << movies[i].dayIndex << "|"
            << movies[i].name << "|"
            << movies[i].time << "|"
            << movies[i].hall << "\n";
    }
    file.close();
}

void DrawHomeScreen(bool darkMode, bool isAdmin, ScreenState& currentScreen)
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

    if (isAdmin)
    {
        DrawRectangle(820, 80, 150, 35, RED);
        DrawText("ADMIN MODE", 835, 87, 20, RAYWHITE);

        // ADMIN BUTTONS
        Rectangle addBtn = { 820, 120, 150, 40 };
        Rectangle removeBtn = { 820, 170, 150, 40 };

        DrawRectangleRec(addBtn, DARKGREEN);
        DrawRectangleLinesEx(addBtn, 2, GRAY);
        DrawText("Add Movie", (int)addBtn.x + 20, (int)addBtn.y + 10, 20, WHITE);

        DrawRectangleRec(removeBtn, MAROON);
        DrawRectangleLinesEx(removeBtn, 2, GRAY);
        DrawText("Remove", (int)removeBtn.x + 25, (int)removeBtn.y + 10, 20, WHITE);

        if (CheckCollisionPointRec(mouse, addBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            currentScreen = SCREEN_ADD_MOVIE;
        }
        if (CheckCollisionPointRec(mouse, removeBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            currentScreen = SCREEN_REMOVE_MOVIE;
        }
    }

    static Movie movies[50];
    static int movieCount = 0;
    static bool loaded = false;

    if (!loaded)
    {
        LoadMovies(movies, movieCount, 50);
        loaded = true;
    }

    int y = 200;
    for (int i = 0; i < movieCount; i++)
    {
        if (movies[i].dayIndex == selectedDay)
        {
            DrawRectangle(250, y, 500, 80, boxColor);
            DrawText(movies[i].name, 280, y + 10, 25, textColor);

            char info[256];
            snprintf(info, 256, "%s | %s", movies[i].time, movies[i].hall);
            DrawText(info, 280, y + 45, 18, DARKGRAY);

            y += 100;
        }
    }

    Rectangle backBtn = { 20,20,100,40 };
    Rectangle logoutBtn = { 20, 70, 100, 40 };

    DrawRectangleRec(backBtn, boxColor);
    DrawRectangleLinesEx(backBtn, 2, GRAY);
    DrawText("Back", 45, 30, 20, textColor);

    DrawRectangleRec(logoutBtn, boxColor);
    DrawRectangleLinesEx(logoutBtn, 2, GRAY);
    DrawText("Logout", 30, 80, 20, textColor);
}

void DrawAddMovieScreen(bool darkMode, float& cursorBlink, ScreenState& currentScreen)
{
    Color textColor = darkMode ? RAYWHITE : BLACK;
    Color boxColor = darkMode ? Color{ 60, 60, 70, 255 } : LIGHTGRAY;
    Color activeColor = darkMode ? Color{ 80, 80, 90, 255 } : WHITE;

    Vector2 mouse = GetMousePosition();

    static char dayText[8] = "";
    static char nameText[128] = "";
    static char timeText[32] = "";
    static char hallText[32] = "";

    static bool dayActive = false;
    static bool nameActive = false;
    static bool timeActive = false;
    static bool hallActive = false;

    static const char* errorMsg = "";
    static const char* successMsg = "";

    Rectangle dayBox = { 300.0f, 200.0f, 400.0f, 40.0f };
    Rectangle nameBox = { 300.0f, 280.0f, 400.0f, 40.0f };
    Rectangle timeBox = { 300.0f, 360.0f, 400.0f, 40.0f };
    Rectangle hallBox = { 300.0f, 440.0f, 400.0f, 40.0f };
    Rectangle addBtn = { 400.0f, 520.0f, 200.0f, 50.0f };

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        dayActive = CheckCollisionPointRec(mouse, dayBox);
        nameActive = CheckCollisionPointRec(mouse, nameBox);
        timeActive = CheckCollisionPointRec(mouse, timeBox);
        hallActive = CheckCollisionPointRec(mouse, hallBox);

        if (CheckCollisionPointRec(mouse, addBtn))
        {
            int dayIdx = atoi(dayText);
            if (dayIdx < 0 || dayIdx > 6 || strlen(nameText) == 0 || strlen(timeText) == 0 || strlen(hallText) == 0)
            {
                errorMsg = "Invalid input! Check day (0-6) and fill all fields.";
                successMsg = "";
            }
            else
            {
                ofstream file("movies.txt", ios::app);
                file << dayIdx << "|" << nameText << "|" << timeText << "|" << hallText << "\n";
                file.close();

                successMsg = "Movie added successfully!";
                errorMsg = "";
                dayText[0] = '\0';
                nameText[0] = '\0';
                timeText[0] = '\0';
                hallText[0] = '\0';
            }
        }
    }

    HandleTextInput(dayText, 8, dayActive);
    HandleTextInput(nameText, 128, nameActive);
    HandleTextInput(timeText, 32, timeActive);
    HandleTextInput(hallText, 32, hallActive);

    if (dayActive || nameActive || timeActive || hallActive)
    {
        cursorBlink += GetFrameTime();
        if (cursorBlink > 1.0f) cursorBlink = 0.0f;
    }

    DrawText("Add Movie", 400, 100, 40, textColor);

    DrawText("Day (0-6):", 300, 175, 20, textColor);
    DrawRectangleRec(dayBox, dayActive ? activeColor : boxColor);
    DrawRectangleLinesEx(dayBox, 2, dayActive ? DARKBLUE : GRAY);
    DrawText(dayText, (int)dayBox.x + 10, (int)dayBox.y + 10, 20, textColor);

    DrawText("Movie Name:", 300, 255, 20, textColor);
    DrawRectangleRec(nameBox, nameActive ? activeColor : boxColor);
    DrawRectangleLinesEx(nameBox, 2, nameActive ? DARKBLUE : GRAY);
    DrawText(nameText, (int)nameBox.x + 10, (int)nameBox.y + 10, 20, textColor);

    DrawText("Time:", 300, 335, 20, textColor);
    DrawRectangleRec(timeBox, timeActive ? activeColor : boxColor);
    DrawRectangleLinesEx(timeBox, 2, timeActive ? DARKBLUE : GRAY);
    DrawText(timeText, (int)timeBox.x + 10, (int)timeBox.y + 10, 20, textColor);

    DrawText("Hall:", 300, 415, 20, textColor);
    DrawRectangleRec(hallBox, hallActive ? activeColor : boxColor);
    DrawRectangleLinesEx(hallBox, 2, hallActive ? DARKBLUE : GRAY);
    DrawText(hallText, (int)hallBox.x + 10, (int)hallBox.y + 10, 20, textColor);

    if (strlen(errorMsg) > 0)
        DrawText(errorMsg, 250, 490, 20, RED);
    if (strlen(successMsg) > 0)
        DrawText(successMsg, 280, 490, 20, DARKGREEN);

    DrawRectangleRec(addBtn, DARKGREEN);
    DrawText("Add Movie", (int)addBtn.x + 45, (int)addBtn.y + 15, 20, WHITE);

    if (DrawAuthBackButton(mouse, darkMode))
    {
        currentScreen = SCREEN_HOME;
        errorMsg = "";
        successMsg = "";
    }

    // Cursor blinking
    if (dayActive && cursorBlink < 0.5f)
    {
        int w = MeasureText(dayText, 20);
        DrawLine((int)dayBox.x + 10 + w, (int)dayBox.y + 8, (int)dayBox.x + 10 + w, (int)dayBox.y + 32, textColor);
    }
    if (nameActive && cursorBlink < 0.5f)
    {
        int w = MeasureText(nameText, 20);
        DrawLine((int)nameBox.x + 10 + w, (int)nameBox.y + 8, (int)nameBox.x + 10 + w, (int)nameBox.y + 32, textColor);
    }
    if (timeActive && cursorBlink < 0.5f)
    {
        int w = MeasureText(timeText, 20);
        DrawLine((int)timeBox.x + 10 + w, (int)timeBox.y + 8, (int)timeBox.x + 10 + w, (int)timeBox.y + 32, textColor);
    }
    if (hallActive && cursorBlink < 0.5f)
    {
        int w = MeasureText(hallText, 20);
        DrawLine((int)hallBox.x + 10 + w, (int)hallBox.y + 8, (int)hallBox.x + 10 + w, (int)hallBox.y + 32, textColor);
    }
}

void DrawRemoveMovieScreen(bool darkMode, float& cursorBlink, ScreenState& currentScreen)
{
    Color textColor = darkMode ? RAYWHITE : BLACK;
    Color boxColor = darkMode ? Color{ 60, 60, 70, 255 } : LIGHTGRAY;
    Color activeColor = darkMode ? Color{ 80, 80, 90, 255 } : WHITE;

    Vector2 mouse = GetMousePosition();

    static char dayText[8] = "";
    static char nameText[128] = "";
    static bool dayActive = false;
    static bool nameActive = false;
    static const char* errorMsg = "";
    static const char* successMsg = "";

    Rectangle dayBox = { 300.0f, 220.0f, 400.0f, 40.0f };
    Rectangle nameBox = { 300.0f, 300.0f, 400.0f, 40.0f };
    Rectangle removeBtn = { 400.0f, 400.0f, 200.0f, 50.0f };

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        dayActive = CheckCollisionPointRec(mouse, dayBox);
        nameActive = CheckCollisionPointRec(mouse, nameBox);

        if (CheckCollisionPointRec(mouse, removeBtn))
        {
            int dayIdx = atoi(dayText);
            if (strlen(nameText) == 0 || dayIdx < 0 || dayIdx > 6)
            {
                errorMsg = "Invalid input! Enter day (0-6) and movie name.";
                successMsg = "";
            }
            else
            {
                Movie movies[50];
                int count = 0;
                LoadMovies(movies, count, 50);

                bool found = false;
                int newCount = 0;
                for (int i = 0; i < count; i++)
                {
                    if (movies[i].dayIndex == dayIdx && strcmp(movies[i].name, nameText) == 0 && !found)
                    {
                        found = true; // Skip this one (remove it)
                    }
                    else
                    {
                        movies[newCount] = movies[i];
                        newCount++;
                    }
                }

                if (found)
                {
                    SaveMovies(movies, newCount);
                    successMsg = "Movie removed successfully!";
                    errorMsg = "";
                    dayText[0] = '\0';
                    nameText[0] = '\0';
                }
                else
                {
                    errorMsg = "Movie not found!";
                    successMsg = "";
                }
            }
        }
    }

    HandleTextInput(dayText, 8, dayActive);
    HandleTextInput(nameText, 128, nameActive);

    if (dayActive || nameActive)
    {
        cursorBlink += GetFrameTime();
        if (cursorBlink > 1.0f) cursorBlink = 0.0f;
    }

    DrawText("Remove Movie", 360, 100, 40, textColor);

    DrawText("Day (0-6):", 300, 195, 20, textColor);
    DrawRectangleRec(dayBox, dayActive ? activeColor : boxColor);
    DrawRectangleLinesEx(dayBox, 2, dayActive ? DARKBLUE : GRAY);
    DrawText(dayText, (int)dayBox.x + 10, (int)dayBox.y + 10, 20, textColor);

    DrawText("Movie Name:", 300, 275, 20, textColor);
    DrawRectangleRec(nameBox, nameActive ? activeColor : boxColor);
    DrawRectangleLinesEx(nameBox, 2, nameActive ? DARKBLUE : GRAY);
    DrawText(nameText, (int)nameBox.x + 10, (int)nameBox.y + 10, 20, textColor);

    if (strlen(errorMsg) > 0)
        DrawText(errorMsg, 280, 370, 20, RED);
    if (strlen(successMsg) > 0)
        DrawText(successMsg, 280, 370, 20, DARKGREEN);

    DrawRectangleRec(removeBtn, MAROON);
    DrawText("Remove", (int)removeBtn.x + 50, (int)removeBtn.y + 15, 20, WHITE);

    if (DrawAuthBackButton(mouse, darkMode))
    {
        currentScreen = SCREEN_HOME;
        errorMsg = "";
        successMsg = "";
    }

    if (dayActive && cursorBlink < 0.5f)
    {
        int w = MeasureText(dayText, 20);
        DrawLine((int)dayBox.x + 10 + w, (int)dayBox.y + 8, (int)dayBox.x + 10 + w, (int)dayBox.y + 32, textColor);
    }
    if (nameActive && cursorBlink < 0.5f)
    {
        int w = MeasureText(nameText, 20);
        DrawLine((int)nameBox.x + 10 + w, (int)nameBox.y + 8, (int)nameBox.x + 10 + w, (int)nameBox.y + 32, textColor);
    }
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
    bool isAdmin = false;

    char currentUser[64] = "";

    static EventInputState eventInputState;

    InitWindow(screenWidth, screenHeight, "Cinema");
    SetTargetFPS(60);
    Texture2D logo = LoadTexture("../assets/logo.png");

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
                isAdmin = false;
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
                isAdmin = false;
                currentUser[0] = '\0';
                loginUser[0] = '\0';
                loginPass[0] = '\0';
                currentScreen = SCREEN_MENU;
            }
        }
        else if (currentScreen == SCREEN_ADD_MOVIE ||
            currentScreen == SCREEN_REMOVE_MOVIE)
        {
            if (DrawAuthBackButton(mouse, darkMode))
            {
                currentScreen = SCREEN_HOME;
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
            DrawTexture(logo, screenWidth / 2 - logo.width / 2, 150, WHITE);

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
                isAdmin,
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
            DrawHomeScreen(darkMode, isAdmin, currentScreen);
        }
        else if (currentScreen == SCREEN_ADD_MOVIE)
        {
            DrawAddMovieScreen(darkMode, authCursorBlink, currentScreen);
        }
        else if (currentScreen == SCREEN_REMOVE_MOVIE)
        {
            DrawRemoveMovieScreen(darkMode, authCursorBlink, currentScreen);
        }

        EndDrawing();
    }

    UnloadTexture(logo);
    CloseWindow();

    return 0;
}