#define _CRT_SECURE_NO_WARNINGS
#include "Auth.h"

void HandleTextInput(char* text, int maxLen, bool active)
{
    if (!active) return;

    int key = GetCharPressed();
    while (key > 0)
    {
        int len = TextLength(text);
        if (key >= 32 && key <= 125 && len < maxLen - 1)
        {
            text[len] = (char)key;
            text[len + 1] = '\0';
        }
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE))
    {
        int len = TextLength(text);
        if (len > 0) text[len - 1] = '\0';
    }
}
bool AccountExists(const char* username)
{
    ifstream file("accounts.txt");
    string line;
    string search = string(username) + ":";

    while (getline(file, line))
    {
        if (line.find(search) == 0)
        {
            return true;
        }
    }
    return false;
}

void SaveAccount(const char* username, const char* password)
{
    ofstream file("accounts.txt", ios::app);
    file << username << ":" << password << endl;
    file.close();
}

bool DrawAuthBackButton(Vector2 mouse, bool darkMode)
{
    Color boxColor = darkMode ? Color{ 60, 60, 70, 255 } : LIGHTGRAY;
    Color textColor = darkMode ? RAYWHITE : BLACK;

    Rectangle backBtn = { 20.0f, 20.0f, 100.0f, 40.0f };
    DrawRectangleRec(backBtn, boxColor);
    DrawRectangleLinesEx(backBtn, 2, GRAY);
    DrawText("Back", (int)backBtn.x + 25, (int)backBtn.y + 10, 20, textColor);

    return CheckCollisionPointRec(mouse, backBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}
void DrawLoginScreen(bool darkMode, char* username, char* password, bool& userActive, bool& passActive, float& cursorBlink, ScreenState& currentScreen, bool& isLoggedIn, char* currentUser)
{
    Color textColor = darkMode ? RAYWHITE : BLACK;
    Color boxColor = darkMode ? Color{ 60, 60, 70, 255 } : LIGHTGRAY;
    Color activeColor = darkMode ? Color{ 80, 80, 90, 255 } : WHITE;

    Vector2 mouse = GetMousePosition();

    static const char* errorMessages[] = {
        "",
        "Account not found!",
        "Wrong password!"
    };
    static int errorCode = 0;

    Rectangle userBox = { 300.0f, 280.0f, 400.0f, 40.0f };
    Rectangle passBox = { 300.0f, 380.0f, 400.0f, 40.0f };
    Rectangle loginBtn = { 400.0f, 480.0f, 200.0f, 50.0f };
    Rectangle createAccBtn = { 350.0f, 560.0f, 300.0f, 40.0f };

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        userActive = CheckCollisionPointRec(mouse, userBox);
        passActive = CheckCollisionPointRec(mouse, passBox);

        if (CheckCollisionPointRec(mouse, loginBtn))
        {
            if (AccountExists(username))
            {
                ifstream file("accounts.txt");
                string line;
                string search = string(username) + ":" + string(password);
                bool found = false;
                while (getline(file, line))
                {
                    if (line == search)
                    {
                        found = true;
                        break;
                    }
                }
                file.close();

                if (found)
                {
                    isLoggedIn = true;
                    strcpy(currentUser, username);
                    currentScreen = SCREEN_MENU;
                    errorCode = 0;
                }
                else
                {
                    errorCode = 2;
                }
            }
            else
            {
                errorCode = 1;
            }
        }

        if (CheckCollisionPointRec(mouse, createAccBtn))
        {
            currentScreen = SCREEN_REGISTER;
            errorCode = 0;
            username[0] = '\0';
            password[0] = '\0';
            userActive = false;
            passActive = false;
        }
    }

    HandleTextInput(username, 64, userActive);
    HandleTextInput(password, 64, passActive);

    if (userActive || passActive)
    {
        cursorBlink += GetFrameTime();
        if (cursorBlink > 1.0f) cursorBlink = 0.0f;
    }

    DrawText("Login", 450, 150, 40, textColor);
    DrawText("Username:", 300, 250, 20, textColor);
    DrawText("Password:", 300, 350, 20, textColor);

    if (errorCode != 0)
    {
        DrawText(errorMessages[errorCode], 350, 440, 20, RED);
    }

    DrawRectangleRec(userBox, userActive ? activeColor : boxColor);
    DrawRectangleLinesEx(userBox, 2, userActive ? DARKBLUE : GRAY);
    DrawText(username, (int)userBox.x + 10, (int)userBox.y + 10, 20, textColor);

    DrawRectangleRec(passBox, passActive ? activeColor : boxColor);
    DrawRectangleLinesEx(passBox, 2, passActive ? DARKBLUE : GRAY);

    int passLen = TextLength(password);
    char stars[64] = "";
    for (int i = 0; i < passLen && i < 63; i++) stars[i] = '*';
    stars[passLen] = '\0';
    DrawText(stars, (int)passBox.x + 10, (int)passBox.y + 10, 20, textColor);

    if (userActive && cursorBlink < 0.5f)
    {
        int w = MeasureText(username, 20);
        DrawLine((int)userBox.x + 10 + w, (int)userBox.y + 8, (int)userBox.x + 10 + w, (int)userBox.y + 32, textColor);
    }
    if (passActive && cursorBlink < 0.5f)
    {
        int w = MeasureText(stars, 20);
        DrawLine((int)passBox.x + 10 + w, (int)passBox.y + 8, (int)passBox.x + 10 + w, (int)passBox.y + 32, textColor);
    }

    DrawRectangleRec(loginBtn, DARKBLUE);
    DrawText("Login", (int)loginBtn.x + 70, (int)loginBtn.y + 15, 20, WHITE);

    DrawRectangleRec(createAccBtn, boxColor);
    DrawText("Create Account", (int)createAccBtn.x + 70, (int)createAccBtn.y + 10, 20, textColor);
    DrawText("Create Account", (int)createAccBtn.x + 70, (int)createAccBtn.y + 10, 20, textColor);
}

void DrawRegisterScreen(bool darkMode, char* username, char* password, char* confirm, bool& userActive, bool& passActive, bool& confirmActive, float& cursorBlink, ScreenState& currentScreen)
{
    Color textColor = darkMode ? RAYWHITE : BLACK;
    Color boxColor = darkMode ? Color{ 60, 60, 70, 255 } : LIGHTGRAY;
    Color activeColor = darkMode ? Color{ 80, 80, 90, 255 } : WHITE;

    Vector2 mouse = GetMousePosition();

    static const char* errorMessages[] = {
        "",
        "Account already exists!",
        "Passwords don't match!",
        "Too short! Min 3 chars"
    };
    static const char* successMessages[] = {
        "",
        "Account created! Go back to login"
    };
    static int errorCode = 0;
    static int successCode = 0;

    Rectangle userBox = { 300.0f, 260.0f, 400.0f, 40.0f };
    Rectangle passBox = { 300.0f, 340.0f, 400.0f, 40.0f };
    Rectangle confirmBox = { 300.0f, 420.0f, 400.0f, 40.0f };
    Rectangle regBtn = { 400.0f, 500.0f, 200.0f, 50.0f };

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        userActive = CheckCollisionPointRec(mouse, userBox);
        passActive = CheckCollisionPointRec(mouse, passBox);
        confirmActive = CheckCollisionPointRec(mouse, confirmBox);

        if (CheckCollisionPointRec(mouse, regBtn))
        {
            if (AccountExists(username))
            {
                errorCode = 1;
                successCode = 0;
            }
            else if (strcmp(password, confirm) != 0)
            {
                errorCode = 2;
                successCode = 0;
            }
            else if (TextLength(username) < 3 || TextLength(password) < 3)
            {
                errorCode = 3;
                successCode = 0;
            }
            else
            {
                SaveAccount(username, password);
                successCode = 1;
                errorCode = 0;
                username[0] = '\0';
                password[0] = '\0';
                confirm[0] = '\0';
            }
        }
    }

    HandleTextInput(username, 64, userActive);
    HandleTextInput(password, 64, passActive);
    HandleTextInput(confirm, 64, confirmActive);

    if (userActive || passActive || confirmActive)
    {
        cursorBlink += GetFrameTime();
        if (cursorBlink > 1.0f) cursorBlink = 0.0f;
    }

    DrawText("Create Account", 380, 150, 40, textColor);
    DrawText("Username:", 300, 230, 20, textColor);
    DrawText("Password:", 300, 310, 20, textColor);
    DrawText("Confirm Password:", 300, 390, 20, textColor);

    if (errorCode != 0)
    {
        DrawText(errorMessages[errorCode], 320, 470, 20, RED);
    }
    if (successCode != 0)
    {
        DrawText(successMessages[successCode], 280, 470, 20, DARKGREEN);
    }

    DrawRectangleRec(userBox, userActive ? activeColor : boxColor);
    DrawRectangleLinesEx(userBox, 2, userActive ? DARKBLUE : GRAY);
    DrawText(username, (int)userBox.x + 10, (int)userBox.y + 10, 20, textColor);

    DrawRectangleRec(passBox, passActive ? activeColor : boxColor);
    DrawRectangleLinesEx(passBox, 2, passActive ? DARKBLUE : GRAY);

    int passLen = TextLength(password);
    char stars[64] = "";
    for (int i = 0; i < passLen && i < 63; i++) stars[i] = '*';
    stars[passLen] = '\0';
    DrawText(stars, (int)passBox.x + 10, (int)passBox.y + 10, 20, textColor);

    DrawRectangleRec(confirmBox, confirmActive ? activeColor : boxColor);
    DrawRectangleLinesEx(confirmBox, 2, confirmActive ? DARKBLUE : GRAY);

    int confirmLen = TextLength(confirm);
    char confirmStars[64] = "";
    for (int i = 0; i < confirmLen && i < 63; i++) confirmStars[i] = '*';
    confirmStars[confirmLen] = '\0';
    DrawText(confirmStars, (int)confirmBox.x + 10, (int)confirmBox.y + 10, 20, textColor);

    if (userActive && cursorBlink < 0.5f)
    {
        int w = MeasureText(username, 20);
        DrawLine((int)userBox.x + 10 + w, (int)userBox.y + 8, (int)userBox.x + 10 + w, (int)userBox.y + 32, textColor);
    }
    if (passActive && cursorBlink < 0.5f)
    {
        int w = MeasureText(stars, 20);
        DrawLine((int)passBox.x + 10 + w, (int)passBox.y + 8, (int)passBox.x + 10 + w, (int)passBox.y + 32, textColor);
    }
    if (confirmActive && cursorBlink < 0.5f)
    {
        int w = MeasureText(confirmStars, 20);
        DrawLine((int)confirmBox.x + 10 + w, (int)confirmBox.y + 8, (int)confirmBox.x + 10 + w, (int)confirmBox.y + 32, textColor);
    }

    DrawRectangleRec(regBtn, DARKGREEN);
    DrawText("Register", (int)regBtn.x + 55, (int)regBtn.y + 15, 20, WHITE);
}