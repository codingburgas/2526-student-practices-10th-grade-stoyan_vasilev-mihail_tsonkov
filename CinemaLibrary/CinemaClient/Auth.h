#pragma once
#include "header/menu.h"
#include "header/precompile.h"


void DrawLoginScreen(bool darkMode, char* username, char* password, bool& userActive, bool& passActive, float& cursorBlink, ScreenState& currentScreen, bool& isLoggedIn, char* currentUser);
void DrawRegisterScreen(bool darkMode, char* username, char* password, char* confirm, bool& userActive, bool& passActive, bool& confirmActive, float& cursorBlink, ScreenState& currentScreen);
bool DrawAuthBackButton(Vector2 mouse, bool darkMode);
void HandleTextInput(char* text, int maxLen, bool active);
bool AccountExists(const char* username);
void SaveAccount(const char* username, const char* password);