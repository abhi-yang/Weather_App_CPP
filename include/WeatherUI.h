#pragma once
#include "ApiHandler.h"
#include "raylib.h"

class WeatherUI {
private:
    static Font font;
    static Texture2D clearIcon;
    static Texture2D cloudyIcon;
    static Texture2D rainIcon;
    static Texture2D snowIcon;
    static Texture2D thunderIcon;
    static Texture2D tempIcon;
    static Texture2D humidityIcon;
    static Texture2D windIcon;
    
public:
    static void Init(); // Call this at startup
    static void Cleanup(); // Call this at shutdown
    static void Show(const WeatherData& data);
    static std::string GetCityInput();
};
