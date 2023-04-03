cmake_minimum_required(VERSION 3.10)
project(HomeHive)

set(CMAKE_CXX_STANDARD 11)

## DEPENDENCIES ##
include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

find_package(CURL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk+-3.0)

## INCLUDE AND LINKING DEPENDENCIES DIRECTORIES ##
include_directories(${CURL_INCLUDE_DIR})
include_directories(${GTK_INCLUDE_DIRS})
link_directories(${GTK_LIBRARY_DIRS})

## BUILD LIBRARIES AND THEIR SOURCES ##
add_library(HomeHiveGUIComponents
        gui/components/GuiComponent.cpp gui/components/GuiComponent.h
        gui/components/DateTimeComponent.cpp gui/components/DateTimeComponent.h
        gui/GuiHelpers.h gui/GuiHelpers.cpp
        gui/components/WeatherComponent.cpp gui/components/WeatherComponent.h
        gui/components/NewsComponent.cpp gui/components/NewsComponent.h gui/components/GreetingComponent.cpp gui/components/GreetingComponent.h)
add_library(HomeHiveRequests
        request/request.cpp request/request.h
        request/Unsplash.cpp request/Unsplash.h
        request/UnsplashBackground.cpp request/UnsplashBackground.h
        request/weather.cpp request/weather.h
        request/news.h request/news.cpp)
add_library(HomeHiveEvent
        event/Timer.cpp event/Timer.h
        event/SettingsEvent.cpp event/SettingsEvent.h)
add_library(HomeHiveGUI
        gui/BaseView.cpp gui/BaseView.h
        gui/App.cpp gui/App.h
        gui/HomeView.cpp gui/HomeView.h
        gui/settings.cpp gui/settings.h)

## DEFINE EXECUTABLES ##
add_executable(HomeHive main.cpp)
add_executable(test test.cpp)

# Define the schema file
set(SCHEMA_FILE ${CMAKE_CURRENT_SOURCE_DIR}/schemas/ca.uwo.cs3307.homehive.gschema.xml)

# Define the installation directory for the schema file
set(SCHEMA_INSTALL_DIR ${CMAKE_INSTALL_DATADIR}/glib-2.0/schemas)

# Compile the schema file into a binary format
add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/gschemas.compiled
  COMMAND glib-compile-schemas ${CMAKE_CURRENT_SOURCE_DIR}/schemas
  DEPENDS ${SCHEMA_FILE}
  COMMENT "Compiling GSettings schema"
)

## COPY RESOURCES ##
add_custom_target(resources
        COMMAND ${CMAKE_COMMAND}
        -E copy_directory
        ${CMAKE_CURRENT_LIST_DIR}/resources
        ${CMAKE_CURRENT_BINARY_DIR}/resources
        )
add_dependencies(HomeHive resources) # this links the resources to main exec, in order to copy every build

include(GNUInstallDirs)

set(SCHEMA_INSTALL_DIR ${CMAKE_INSTALL_DATADIR}/glib-2.0/schemas)

## LINK LIBRARIES TO EXECUTABLES ##
target_link_libraries(HomeHiveRequests PRIVATE nlohmann_json::nlohmann_json ${CURL_LIBRARIES})
target_link_libraries(HomeHiveGUIComponents ${GTK_LIBRARIES} HomeHiveRequests HomeHiveEvent)
target_link_libraries(HomeHiveGUI ${GTK_LIBRARIES} HomeHiveRequests HomeHiveEvent HomeHiveGUIComponents)
target_link_libraries(HomeHive ${GTK_LIBRARIES} HomeHiveRequests HomeHiveEvent HomeHiveGUI)
target_link_libraries(test PRIVATE nlohmann_json::nlohmann_json HomeHiveRequests)

## INSTALL THE COMPILED SCHEMA FILE ##
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/gschemas.compiled DESTINATION ${SCHEMA_INSTALL_DIR})