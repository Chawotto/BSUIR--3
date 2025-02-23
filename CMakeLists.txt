cmake_minimum_required(VERSION 3.29)
project(MorrsQT)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "C:/Users/alexe/.vcpkg-clion/vcpkg/installed/x64-mingw-dynamic")
set(CMAKE_TOOLCHAIN_FILE "C:/Users/alexe/.vcpkg-clion/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
set(CMAKE_PREFIX_PATH "C:\\Qt\\6.7.3\\mingw_64")

find_package(jsoncpp CONFIG REQUIRED)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(MorrsQT
        source/main.cpp
        source/User.cpp
        source/gamOpt.cpp
        source/Game.cpp
        source/devOpt.cpp
        source/developermenu.cpp
        source/header/developermenu.h
        source/developermenu.ui
        source/gamermenu.cpp
        source/header/gamermenu.h
        source/gamermenu.ui
        source/mainwindow.cpp
        source/header/mainwindow.h
        source/mainwindow.ui
        source/enterwindow.cpp
        source/header/enterwindow.h
        source/enterwindow.ui
        source/registrationwindow.cpp
        source/header/registrationwindow.h
        source/registrationwindow.ui
        source/devprofile.cpp
        source/header/devprofile.h
        source/devprofile.ui
        source/gameprofile.cpp
        source/header/gameprofile.h
        source/gameprofile.ui
        source/header/GameException.h
        source/header/UserException.h
        source/DeveloperUser.cpp
        source/GamerUser.cpp
        source/header/GamerUser.h
        source/header/DeveloperUser.h
        source/Template.cpp
        source/header/Template.h
        source/RPGGame.cpp
        source/header/RPGGame.h
        source/ActionGame.cpp
        source/header/ActionGame.h
        source/header/gamecollection.h
        source/gamecollection.cpp
        source/gameIterator.cpp
        source/header/gameIterator.h
)

target_link_libraries(MorrsQT
        Qt::Core
        Qt::Gui
        Qt::Widgets
        JsonCpp::JsonCpp
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
