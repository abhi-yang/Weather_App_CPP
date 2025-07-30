#include "WeatherUI.h"
#include <string>
#include <cstring>
#include <iomanip>
#include <sstream>

// Static member initialization
Font WeatherUI::font = { 0 };
Texture2D WeatherUI::clearIcon = { 0 };
Texture2D WeatherUI::cloudyIcon = { 0 };
Texture2D WeatherUI::rainIcon = { 0 };
Texture2D WeatherUI::snowIcon = { 0 };
Texture2D WeatherUI::thunderIcon = { 0 };
Texture2D WeatherUI::tempIcon = { 0 };
Texture2D WeatherUI::humidityIcon = { 0 };
Texture2D WeatherUI::windIcon = { 0 };

void WeatherUI::Init() {
    const int fontSize = 32;
    const int maxChars = 256;
    font = LoadFontEx("assets/fonts/Roboto-Bold.ttf", fontSize, nullptr, maxChars); // Load extended glyphs

    clearIcon = LoadTexture("assets/images/clear.png");
    cloudyIcon = LoadTexture("assets/images/cloudy.png");
    rainIcon = LoadTexture("assets/images/rain.png");
    snowIcon = LoadTexture("assets/images/snow.png");
    thunderIcon = LoadTexture("assets/images/thunder.png");
      tempIcon = LoadTexture("assets/images/temperature.png");
    humidityIcon = LoadTexture("assets/images/humidity.png");
    windIcon = LoadTexture("assets/images/wind.png");
}

void WeatherUI::Cleanup() {
    UnloadFont(font);
    UnloadTexture(clearIcon);
    UnloadTexture(cloudyIcon);
    UnloadTexture(rainIcon);
    UnloadTexture(snowIcon);
    UnloadTexture(thunderIcon);
    UnloadTexture(tempIcon);
    UnloadTexture(humidityIcon);
    UnloadTexture(windIcon);
}

void WeatherUI::Show(const WeatherData& data) {
    BeginDrawing();

    // UI Theme Colors
    Color bgColor = { 15, 23, 42, 255 };              // Deep navy
    Color cardColor = { 250, 250, 255, 255 };         // Off-white
    Color accentColor = { 16, 185, 129, 255 };        // Vibrant teal
    Color accentBG = Fade(accentColor, 0.1f);
    Color textColor = { 30, 41, 59, 255 };
    Color highlightColor = { 59, 130, 246, 255 };

    ClearBackground(bgColor);

    DrawRectangleRounded({25, 25, 750, 550}, 0.1f, 16, Fade(DARKGRAY, 0.2f));
    DrawRectangleRounded({20, 20, 760, 560}, 0.1f, 16, cardColor);

    // Choose icon
    Texture2D* weatherIcon = &clearIcon;
    if (data.description.find("cloud") != std::string::npos) weatherIcon = &cloudyIcon;
    else if (data.description.find("rain") != std::string::npos) weatherIcon = &rainIcon;
    else if (data.description.find("snow") != std::string::npos) weatherIcon = &snowIcon;
    else if (data.description.find("thunder") != std::string::npos) weatherIcon = &thunderIcon;

    // Header
    DrawTextEx(font, data.city.c_str(), {40, 40}, 48, 2, textColor);
    DrawTextEx(font, TextToUpper(data.description.c_str()), {40, 100}, 24, 2, accentColor);

    // Format temperature with 1 decimal and ° symbol
    std::ostringstream tempStream;
    tempStream << std::fixed << std::setprecision(1) << data.temperature << "°C";
    std::string tempStr = tempStream.str();

    // Main icon and temp
    DrawTexturePro(*weatherIcon, {0, 0, (float)weatherIcon->width, (float)weatherIcon->height},
                   {40, 160, 128, 128}, {0, 0}, 0, WHITE);
    DrawTextEx(font, tempStr.c_str(), {200, 180}, 72, 2, highlightColor);

    // Info cards
    float cardY = 360;
    float cardWidth = 220;
    float cardSpacing = 30;

    auto drawInfoCard = [&](float x, Texture2D icon, const char* label, const char* value) {
        Rectangle cardRect = {x, cardY, cardWidth, 160};
        DrawRectangleRounded(cardRect, 0.1f, 8, accentBG);
        DrawTexture(icon, x + 20, cardY + 20, WHITE);
        DrawTextEx(font, label, {x + 20, cardY + 80}, 20, 2, textColor);
        DrawTextEx(font, value, {x + 20, cardY + 110}, 24, 2, highlightColor);
    };

    drawInfoCard(40, tempIcon, "Temperature", tempStr.c_str());
    drawInfoCard(40 + cardWidth + cardSpacing, humidityIcon, "Humidity", data.humidity.c_str());
    drawInfoCard(40 + 2 * (cardWidth + cardSpacing), windIcon, "Wind Speed", data.wind.c_str());

    DrawTextEx(font, "Press R to search another city", {280, 540}, 20, 2, GRAY);

    EndDrawing();
}

std::string WeatherUI::GetCityInput() {
    static char city[64] = "";
    static int letterCount = 0;
    static int framesCounter = 0;

    BeginDrawing();

    Color bgColor = { 27, 27, 27, 255 };
    Color cardColor = { 250, 250, 255, 255 };
    Color accentColor = { 16, 185, 129, 255 };
    Color accentText = accentColor;
    Color textColor = { 30, 41, 59, 255 };
    Color inputBoxColor = Fade(accentColor, 0.15f);
    Color hintColor = { 148, 163, 184, 255 };

    ClearBackground(bgColor);
    DrawRectangleRounded({20, 20, 760, 560}, 0.1f, 16, cardColor);
    DrawTextEx(font, "Enter city name:", {280, 240}, 32, 2, accentText);

    // Input box with border
    DrawRectangleRounded({200, 300, 400, 45}, 0.3f, 8, inputBoxColor);
   DrawRectangle(200, 300, 400, 45, Fade(accentText, 0.2f));

    // Handle keyboard input
    int key = GetCharPressed();
    if (key >= 32 && key <= 125 && letterCount < 63) {
        city[letterCount++] = (char)key;
        city[letterCount] = '\0';
    }
    if (IsKeyPressed(KEY_BACKSPACE) && letterCount > 0) {
        city[--letterCount] = '\0';
    }
    if (IsKeyPressed(KEY_DELETE)) {
        letterCount = 0;
        city[0] = '\0';
    }

    DrawTextEx(font, city, {220, 310}, 28, 2, textColor);

    // Blinking cursor
    framesCounter++;
    if ((framesCounter / 20) % 2 == 0) {
        float cursorX = 220 + MeasureTextEx(font, city, 28, 2).x;
        DrawTextEx(font, "_", {cursorX, 310}, 28, 2, accentText);
    }

    DrawTextEx(font, "Press Enter to search", {280, 380}, 24, 2, hintColor);

    EndDrawing();

    if (IsKeyPressed(KEY_ENTER)) return std::string(city);
    return "";
}
