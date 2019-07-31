cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(SettingsLibrary)

set(SOURCES database.cpp result.cpp settings.cpp statement.cpp)

set(HEADERS database.h result.h settings.h statement.h)

add_library(settings_lib ${SOURCES} ${HEADERS})

include_directories(${SQLITE_LIB_PATH})

target_link_libraries (settings_lib ${SQLITE3_LIBRARIES})



