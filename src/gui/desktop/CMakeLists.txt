cmake_minimum_required(VERSION 3.5)

project(desktop_brick_games VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

include_directories(${Qt6Widgets_INCLUDE_DIRS})

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(LIBS -lm -lrt -lpthread)
else()
    set(LIBS -lpthread)
endif()

set(MENU_SRC
    main.cpp
    mainwindow.cpp
)

set(INTERFACE_SRC
    buttons.cpp
    desktopview.cpp
    ../../brick_game/tetris/tetris_desktop_translate.cpp
    game.cpp
    helpfield.cpp
)

add_library(menu_lib OBJECT ${MENU_SRC})
add_library(interface_lib OBJECT ${INTERFACE_SRC})
add_library(snake_lib STATIC
    ../../brick_game/snake/snake_controller.cpp
    ../../brick_game/snake/snake_model.cpp
)
add_library(tetris_lib STATIC
    ../../brick_game/tetris/tetris_fsm.c
    ../../brick_game/tetris/tetris_logic.c
)

qt_add_executable(desktop_brick_games
    MANUAL_FINALIZATION
    $<TARGET_OBJECTS:menu_lib>
    $<TARGET_OBJECTS:interface_lib>
)

if(WIN32)
    target_link_libraries(desktop_brick_games PRIVATE snake_lib tetris_lib Qt6::Widgets)
    set_target_properties(desktop_brick_games PROPERTIES OUTPUT_NAME "desktop_brick_games.exe")
elseif(UNIX)
    if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
        target_link_libraries(desktop_brick_games PRIVATE snake_lib tetris_lib Qt6::Widgets ${LIBS})
        set_target_properties(desktop_brick_games PROPERTIES OUTPUT_NAME "desktop_brick_games")
    elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
        target_link_libraries(desktop_brick_games PRIVATE snake_lib tetris_lib Qt6::Widgets ${LIBS})
        set_target_properties(desktop_brick_games PROPERTIES OUTPUT_NAME "desktop_brick_games.app")
    endif()
endif()

qt_finalize_executable(desktop_brick_games)

install(TARGETS desktop_brick_games
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
