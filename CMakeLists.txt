cmake_minimum_required(VERSION 3.16)
project(AimTrainer LANGUAGES CXX)

cmake_policy(SET CMP0091 NEW)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(RAYLIB_PATH "C:/AimTrainer/raylib-5.5_win64_msvc16")

add_executable(AimTrainer
    src/main.cpp
    src/Game.cpp
    src/App.cpp
    src/Settings.cpp
    src/Arena.cpp
    src/Weapon.cpp
    src/HUD.cpp
)

target_include_directories(AimTrainer PRIVATE 
    src 
    include
    "${RAYLIB_PATH}/include"
)

target_link_directories(AimTrainer PRIVATE 
    "${RAYLIB_PATH}/lib"
)

target_link_libraries(AimTrainer PRIVATE 
    raylib winmm gdi32 opengl32 user32 shell32
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