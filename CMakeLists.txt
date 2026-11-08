cmake_minimum_required(VERSION 3.16)
project(AimTrainer LANGUAGES CXX)

cmake_policy(SET CMP0091 NEW)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(RAYLIB_PATH "C:/AimTrainer/raylib-5.5_win64_msvc16")

# --- 1. Группировка исходников ---
set(APP_SOURCES
    src/main.cpp
    src/Application.cpp
    src/App.cpp
    src/Game.cpp
)

set(CORE_SOURCES
    src/Settings.cpp
    src/Arena.cpp
    src/Weapon.cpp
    src/HUD.cpp
    src/SystemStats.cpp
    src/UITheme.cpp
)

set(MODE_SOURCES
    src/StaticMode.cpp
    src/MovingMode.cpp
    src/BouncingMode.cpp
    src/TimedMode.cpp
    src/MultiStaticMode.cpp
)

set(HEADERS
    src/GameConfig.h
    src/WeaponConfig.h
    src/RoomConfig.h
    src/Game.h
    src/App.h
    src/Settings.h
    src/Arena.h
    src/Weapon.h
    src/HUD.h
    src/SystemStats.h
    src/ITrainingMode.h
    src/StaticMode.h
    src/MovingMode.h
    src/BouncingMode.h
    src/TimedMode.h
    src/MultiStaticMode.h
    src/UITheme.h
)

# --- 2. Создание исполняемого файла и добавление исходников ---
add_executable(AimTrainer)

target_sources(AimTrainer PRIVATE
    ${APP_SOURCES}
    ${CORE_SOURCES}
    ${MODE_SOURCES}
    ${HEADERS}
)

# --- 3. Визуальная группировка ---
source_group("App" FILES ${APP_SOURCES})
source_group("Core" FILES ${CORE_SOURCES})
source_group("Modes" FILES ${MODE_SOURCES})
source_group("Headers" FILES ${HEADERS})

# --- 4. Настройки raylib ---
target_include_directories(AimTrainer PRIVATE 
    src 
    include
    "${RAYLIB_PATH}/include"
)

target_link_directories(AimTrainer PRIVATE 
    "${RAYLIB_PATH}/lib"
)

target_link_libraries(AimTrainer PRIVATE 
    raylib winmm gdi32 opengl32 user32 shell32 pdh
)

if(WIN32)
    set_target_properties(AimTrainer PROPERTIES WIN32_EXECUTABLE TRUE)
    if(MSVC)
        set_target_properties(AimTrainer PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup")
    endif()
    
    add_custom_command(TARGET AimTrainer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${RAYLIB_PATH}/lib/raylib.dll"
        $<TARGET_FILE_DIR:AimTrainer>
    )
endif()