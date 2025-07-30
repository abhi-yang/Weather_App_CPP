 #include "ApiHandler.h"
 #include <curl/curl.h>
 #include <sstream>
 #include <iostream>
 #include <nlohmann/json.hpp>
 #include <fstream>

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::optional<WeatherData> ApiHandler::FetchWeather(const std::string& city) {
    // Read API key from .env
    std::ifstream envFile(".env");
    std::string apiKey;
    std::string line;
    while (std::getline(envFile, line)) {
        if (line.find("API_KEY=") == 0) {
            apiKey = line.substr(8);
            break;
        }
    }
    if (apiKey.empty()) return std::nullopt;
    CURL* curl = curl_easy_init();
    if (!curl) return std::nullopt;
    std::string readBuffer;
    std::string url = "https://api.openweathermap.org/data/2.5/weather?q=" + city + "&appid=" + apiKey + "&units=metric";
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    if (res != CURLE_OK) return std::nullopt;
    try {
        auto json = nlohmann::json::parse(readBuffer);
        WeatherData data;
        data.city = json["name"].get<std::string>();
        data.temperature = json["main"]["temp"].get<float>();
        data.humidity = std::to_string(json["main"]["humidity"].get<int>()) + "%";
        data.wind = std::to_string(json["wind"]["speed"].get<float>()) + " m/s";
        data.description = json["weather"][0]["description"].get<std::string>();
        return data;
    } catch (...) {
        return std::nullopt;
    }
}

