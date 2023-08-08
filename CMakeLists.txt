cmake_minimum_required(VERSION 3.25)
project(QMultiMediaManager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# home path
set(PYTHON_EXECUTABLE "C:/Users/elecfrog/scoop/shims/python.exe")
set(CMAKE_PREFIX_PATH "C://Qt//6.5.1//msvc2019_64")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Sql
        Network
        REQUIRED)

# Set path to your Python virtual environment here
find_package(Python3 COMPONENTS Interpreter Development)
find_package(OpenSSL REQUIRED)


add_executable(QMultiMediaManager
        src/main.cpp

        src/base/Singleton.hpp

        src/models/FileSystemTreeModel.h
        src/models/MovieListModel.h
        src/models/MovieContentModel.h
        src/models/defs/DatabaseStatus.h
        src/models/defs/MovieMeta.h
        src/models/defs/SearchKeyword.h

        src/views/MainWindow.cpp
        src/views/MainWindow.h
        src/views/MainWindow.ui
        src/views/FileSystemTreeView.h
        src/views/MovieContentView.cpp
        src/views/MovieContentView.h
        src/views/MovieContentView.ui
        src/views/NavigatorBar.cpp
        src/views/NavigatorBar.h
        src/views/NavigatorBar.ui
        src/views/MovieListView.cpp
        src/views/MovieListView.h

        src/controllers/FileSystemTreeController.h
        src/controllers/MovieListController.h
        src/controllers/MovieContentController.h

        src/base/FileSystem.h
        src/io/SqliteDriver.cpp
        src/io/SqliteDriver.h
        src/io/SqilteServices.h

        src/components/LineInputDialog/LineInputDialog.cpp
        src/components/LineInputDialog/LineInputDialog.h
        src/components/LineInputDialog/LineInputDialog.ui
        src/components/ImageButton/NetworkImageButton.h

        src/script_service/RunPythonScript.h
        src/script_service/PythonInterpreter.cpp
        src/script_service/PythonInterpreter.h
)

target_link_libraries(QMultiMediaManager
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Sql
        Qt::Network

        Python3::Python
        Python3::Module

        OpenSSL::SSL
        OpenSSL::Crypto
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
    foreach (QT_LIB Core Gui Widgets Sql)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
