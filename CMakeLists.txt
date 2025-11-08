cmake_minimum_required(VERSION 3.20)
project(ATMSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt codegen
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Deps (from vcpkg toolchain)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(libpqxx CONFIG REQUIRED)



add_executable(ATMSimulator
    main.cpp
    LoginWidget.cpp
    CardRepository.cpp
    ATMInterface.cpp
    ATMSimulator.ui
    LoginWidget.ui
    ATMSimulator.qrc
)

target_link_libraries(ATMSimulator
    PRIVATE
        Qt6::Widgets
        libpqxx::pqxx
)


# Optional: stricter warnings
if (MSVC)
  target_compile_options(ATMSimulator PRIVATE /W4 /permissive-)
endif()
