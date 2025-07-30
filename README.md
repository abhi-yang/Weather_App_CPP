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