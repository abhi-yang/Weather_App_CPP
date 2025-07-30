cmake_minimum_required(VERSION 3.10)
project(WeatherApp)
set(CMAKE_CXX_STANDARD 17)
# Update these paths to your MSYS2 installation
set(MSYS2_MINGW64 "C:/msys64/mingw64")
include_directories(include
    ${MSYS2_MINGW64}/include
    ${MSYS2_MINGW64}/include/raylib
    ${MSYS2_MINGW64}/include/curl)
link_directories(${MSYS2_MINGW64}/lib)
add_executable(weather_app src/main.cpp src/ApiHandler.cpp src/WeatherUI.cpp)
target_link_libraries(weather_app raylib curl)
