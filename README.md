# WeatherApp

A simple C++ weather app using Raylib for UI and curl for API requests.

## Features
- Enter city name via GUI
- Fetches weather data from wttr.in
- Displays weather info with Raylib

## Build Instructions
- Requires Raylib and curl libraries
- Use CMake or provided tasks.json for build

## Usage
- Run the app, enter a city, and view weather info
- Press R to reset and enter a new city


## Building and running the code :
```bash
    cmake -S . -B build; cmake --build build
```
## Running the code:
```bash
   .\build\weather_app.exe
```

# 📦 Requirements – C++ Weather App

This project depends on the following libraries, tools, and build systems to compile and run successfully.

## 🔧 Tools & Build System
- **CMake** (version 3.15 or higher recommended)
- **MSYS2** with **GCC (g++)** installed

## 🎮 Graphics Library
- **raylib**
  - Used for rendering UI components or enhanced visuals (if applicable)
  - Installation (MSYS2):
    ```bash
    pacman -S mingw-w64-x86_64-raylib
    ```

## 🌐 Networking
- **cURL**
  - Used to make HTTP requests to fetch weather data from APIs
  - Installation (MSYS2):
    ```bash
    pacman -S mingw-w64-x86_64-curl
    ```

## 📄 JSON Parsing
- **nlohmann/json**
  - Header-only library for easy JSON parsing
  - Download from: https://github.com/nlohmann/json
  - Or install via MSYS2:
    ```bash
    pacman -S mingw-w64-x86_64-nlohmann-json
    ```

## ✅ Summary of Installation Commands (MSYS2 terminal)
```bash
pacman -Syu
pacman -S mingw-w64-x86_64-cmake
pacman -S mingw-w64-x86_64-gcc
pacman -S mingw-w64-x86_64-raylib
pacman -S mingw-w64-x86_64-curl
pacman -S mingw-w64-x86_64-nlohmann-json
