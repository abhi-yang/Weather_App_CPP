#include "raylib.h"
#include "ApiHandler.h"
#include "WeatherUI.h"
#include <string>

int main() {
    InitWindow(800, 600, "Weather App");
    SetTargetFPS(60);
    WeatherUI::Init();
    std::string city;
    WeatherData data;
    bool hasData = false;
    while (!WindowShouldClose()) {
        if (!hasData) {
            city = WeatherUI::GetCityInput();
            if (!city.empty()) {
                auto result = ApiHandler::FetchWeather(city);
                if (result) {
                    data = *result;
                    hasData = true;
                }
            }
        } else {
            WeatherUI::Show(data);
            if (IsKeyPressed(KEY_R)) {
                hasData = false;
                city.clear();
            }
        }
    }
    WeatherUI::Cleanup();
    CloseWindow();
    return 0;
}
