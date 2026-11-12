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
)

# --- Training ---
set(TRAINING_FILES
    src/training/TrainingSession.h
    src/training/TrainingSession.cpp
    src/training/Target3D.h
    src/training/Target3D.cpp
    src/training/TargetPool.h
    src/training/TargetPool.cpp
    src/training/GameConfig.h
    src/training/GameMode.h
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

# --- Build ---
add_executable(AimTrainer)
target_sources(AimTrainer PRIVATE
    ${INFRA_FILES}
    ${APP_FILES}
    ${TRAINING_FILES}
    ${MODES_FILES}
    ${SETTINGS_FILES}
    ${SCENE_FILES}
    ${VIEWMODEL_FILES}
    ${WEAPON_FILES}
    ${HANDS_FILES}
    ${UI_FILES}
    ${CARDS_FILES}
)

source_group("Infrastructure"   FILES ${INFRA_FILES})
source_group("Application"      FILES ${APP_FILES})
source_group("Training"         FILES ${TRAINING_FILES})
source_group("Training/Modes"   FILES ${MODES_FILES})
source_group("Settings"         FILES ${SETTINGS_FILES})
source_group("Scene"            FILES ${SCENE_FILES})
source_group("Viewmodel"        FILES ${VIEWMODEL_FILES})
source_group("Viewmodel/Weapon" FILES ${WEAPON_FILES})
source_group("Viewmodel/Hands"  FILES ${HANDS_FILES})
source_group("UI"               FILES ${UI_FILES})
source_group("UI/Cards"         FILES ${CARDS_FILES})

target_include_directories(AimTrainer PRIVATE
    src
    src/app
    src/training
    src/training/modes
    src/settings
    src/scene
    src/viewmodel
    src/viewmodel/weapon
    src/viewmodel/hands
    src/ui
    src/ui/cards
    include
    "${RAYLIB_PATH}/include"
)

target_link_directories(AimTrainer PRIVATE "${RAYLIB_PATH}/lib")
target_link_libraries(AimTrainer PRIVATE raylib winmm gdi32 opengl32 user32 shell32 pdh)

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