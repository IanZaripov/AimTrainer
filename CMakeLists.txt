cmake_minimum_required(VERSION 3.16)
project(AimTrainer LANGUAGES CXX)

cmake_policy(SET CMP0091 NEW)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(RAYLIB_PATH "C:/AimTrainer/raylib-5.5_win64_msvc16")

# --- Infrastructure ---
set(INFRA_FILES
    src/main.cpp
    src/Engine.h
    src/Engine.cpp
)

# --- Application ---
set(APP_FILES
    src/app/ScreenManager.h
    src/app/ScreenManager.cpp
    src/app/IScreen.h
    src/app/screens/RoutinesScreen/RoutinesScreen.h
    src/app/screens/RoutinesScreen/RoutinesScreen.cpp
    src/app/screens/MouseSettingsScreen/MouseSettingsScreen.h
    src/app/screens/MouseSettingsScreen/MouseSettingsScreen.cpp
    src/app/screens/CrosshairSettingsScreen/CrosshairSettingsScreen.h
    src/app/screens/CrosshairSettingsScreen/CrosshairSettingsScreen.cpp
    src/app/screens/ArenaSettingsScreen/ArenaSettingsScreen.h
    src/app/screens/ArenaSettingsScreen/ArenaSettingsScreen.cpp
    src/app/screens/AudioSettingsScreen/AudioSettingsScreen.h
    src/app/screens/AudioSettingsScreen/AudioSettingsScreen.cpp
    src/app/screens/LanguageSettingsScreen/LanguageSettingsScreen.h
    src/app/screens/LanguageSettingsScreen/LanguageSettingsScreen.cpp
    src/app/screens/GameplayScreen/GameplayScreen.h
    src/app/screens/GameplayScreen/GameplayScreen.cpp
    src/app/screens/ResultsScreen/ResultsScreen.h
    src/app/screens/ResultsScreen/ResultsScreen.cpp
)

# --- Localization ---
set(LOC_FILES
    src/localization/Localization.h
    src/localization/Localization.cpp
)

# --- Audio ---
set(AUDIO_FILES
    src/audio/Audio.h
    src/audio/Audio.cpp
)

# --- Training ---
set(TRAINING_FILES
    src/training/TrainingSession.h
    src/training/TrainingSession.cpp
    src/training/SessionData.h
    src/training/SessionData.cpp
    src/training/GameExitReason.h
    src/training/GameConfig.h
    src/training/GameMode.h
)

# --- Targets ---
set(TARGET_FILES
    src/training/target/Target3D.h
    src/training/target/Target3D.cpp
    src/training/target/TargetPool.h
    src/training/target/TargetPool.cpp
)

# --- Training Modes ---
set(MODES_FILES
    src/training/modes/ITrainingMode.h
    src/training/modes/StaticMode.h
    src/training/modes/StaticMode.cpp
    src/training/modes/MovingMode.h
    src/training/modes/MovingMode.cpp
    src/training/modes/BouncingMode.h
    src/training/modes/BouncingMode.cpp
    src/training/modes/TimedMode.h
    src/training/modes/TimedMode.cpp
    src/training/modes/MultiStaticMode.h
    src/training/modes/MultiStaticMode.cpp
)

# --- Settings ---
set(SETTINGS_FILES
    src/settings/Settings.h
    src/settings/Settings.cpp
)

# --- Scene ---
set(SCENE_FILES
    src/scene/Arena.h
    src/scene/Arena.cpp
    src/scene/RoomConfig.h
)

# --- Viewmodel ---
set(VIEWMODEL_FILES
    src/viewmodel/Viewmodel.h
    src/viewmodel/Viewmodel.cpp
)

set(WEAPON_FILES
    src/viewmodel/weapon/Weapon.h
    src/viewmodel/weapon/Weapon.cpp
    src/viewmodel/weapon/WeaponConfig.h
)

set(HANDS_FILES
    src/viewmodel/hands/Hands.h
    src/viewmodel/hands/Hands.cpp
    src/viewmodel/hands/HandsConfig.h
)

# --- UI ---
set(UI_FILES
    src/ui/UITheme.h
    src/ui/UITheme.cpp
    src/ui/UIWidgets.h
    src/ui/UIWidgets.cpp
    src/ui/HUD.h
    src/ui/HUD.cpp
    src/ui/SystemStats.h
    src/ui/SystemStats.cpp
)

# --- UI Cards ---
set(CARDS_FILES
    src/ui/cards/TrainingCard.h
    src/ui/cards/TrainingCard.cpp
    src/ui/cards/StaticCard.cpp
    src/ui/cards/MovingCard.cpp
    src/ui/cards/BouncingCard.cpp
    src/ui/cards/TimedCard.cpp
    src/ui/cards/MultiStaticCard.cpp
)

# =========================================================
# Main Executable
# =========================================================
add_executable(AimTrainer)
target_sources(AimTrainer PRIVATE
    ${INFRA_FILES} ${APP_FILES} ${LOC_FILES} ${AUDIO_FILES}
    ${TRAINING_FILES} ${TARGET_FILES} ${MODES_FILES}
    ${SETTINGS_FILES} ${SCENE_FILES} ${VIEWMODEL_FILES}
    ${WEAPON_FILES} ${HANDS_FILES} ${UI_FILES} ${CARDS_FILES}
)

# ... (source_group опущены для краткости, они не меняются) ...

target_include_directories(AimTrainer PRIVATE
    src src/app src/app/screens/RoutinesScreen src/app/screens/MouseSettingsScreen
    src/app/screens/CrosshairSettingsScreen src/app/screens/ArenaSettingsScreen
    src/app/screens/AudioSettingsScreen src/app/screens/LanguageSettingsScreen
    src/app/screens/GameplayScreen src/app/screens/ResultsScreen
    src/localization src/audio src/training src/training/target
    src/training/modes src/settings src/scene src/viewmodel
    src/viewmodel/weapon src/viewmodel/hands src/ui src/ui/cards
    include "${RAYLIB_PATH}/include"
)

target_link_directories(AimTrainer PRIVATE "${RAYLIB_PATH}/lib")
target_link_libraries(AimTrainer PRIVATE raylib winmm gdi32 opengl32 user32 shell32 pdh)

# =========================================================
# Tests
# =========================================================
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(AimTrainerTests EXCLUDE_FROM_ALL
    tests/test_session_data.cpp
    tests/test_localization.cpp
    tests/test_target_pool.cpp
    # Add the implementations required by the tests
    src/training/SessionData.cpp
    src/localization/Localization.cpp
    src/training/target/Target3D.cpp
    src/training/target/TargetPool.cpp
)

target_include_directories(AimTrainerTests PRIVATE
    src src/training src/training/target src/settings src/localization
    include "${RAYLIB_PATH}/include"
)

target_link_libraries(AimTrainerTests PRIVATE
    "${RAYLIB_PATH}/lib/raylib.lib"
    winmm gdi32 opengl32 user32 shell32 pdh
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(AimTrainerTests)

# =========================================================
# Windows post-build
# =========================================================
if(WIN32)
    set_target_properties(AimTrainer PROPERTIES WIN32_EXECUTABLE TRUE)
    if(MSVC)
        set_target_properties(AimTrainer PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup")
    endif()
    
    add_custom_command(TARGET AimTrainer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${RAYLIB_PATH}/lib/raylib.dll" $<TARGET_FILE_DIR:AimTrainer>
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/assets" $<TARGET_FILE_DIR:AimTrainer>/assets
    )
    
    add_custom_command(TARGET AimTrainerTests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/assets" $<TARGET_FILE_DIR:AimTrainerTests>/assets
    )
endif()