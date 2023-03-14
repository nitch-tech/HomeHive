cmake_minimum_required(VERSION 3.23)
project(HomeHive)

set(CMAKE_CXX_STANDARD 11)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

find_package(CURL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk+-3.0)

include_directories(${CURL_INCLUDE_DIR})
include_directories(${GTK_INCLUDE_DIRS})
link_directories(${GTK_LIBRARY_DIRS})

add_library(Requests request/request.cpp request/request.h request/Unsplash.cpp request/Unsplash.h request/UnsplashBackground.cpp request/UnsplashBackground.h)

add_executable(HomeHive main.cpp gui/BaseView.cpp gui/BaseView.h gui/App.cpp gui/App.h gui/HomeView.cpp gui/HomeView.h event/Timer.cpp event/Timer.h)
add_executable(test2 main2.cpp)
add_executable(test test.cpp)

target_link_libraries(Requests PRIVATE nlohmann_json::nlohmann_json ${CURL_LIBRARIES})
target_link_libraries(HomeHive Requests)

target_link_libraries(HomeHive ${GTK_LIBRARIES})
target_link_libraries(test2 ${GTK_LIBRARIES})
target_link_libraries(test PRIVATE nlohmann_json::nlohmann_json Requests)

