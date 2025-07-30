#pragma once
#include <string>
#include <optional>

struct WeatherData {
    std::string city;
    std::string description;
    float temperature;
    std::string humidity;
    std::string wind;
};

class ApiHandler {
public:
    static std::optional<WeatherData> FetchWeather(const std::string& city);
};
