cmake_minimum_required(VERSION 3.28)
project(SSMS)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/Users/martincao/Qt/6.6.2/macos/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(SSMS
        main.cpp
        ssms_ui.cpp
)

target_link_libraries(SSMS
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

