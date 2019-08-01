cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(SettingsLibrary)

set(SOURCES database.cpp result.cpp settings.cpp statement.cpp)

set(HEADERS database.h result.h settings.h statement.h)

add_library(settings_lib SHARED ${SOURCES} ${HEADERS})

target_link_directories(settings_lib PUBLIC ${SQLITE_LIB_PATH})

target_include_directories(settings_lib PUBLIC ${SQLITE_DIR_PATH})

target_link_libraries(settings_lib sqlite3)
