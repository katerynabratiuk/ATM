cmake_minimum_required(VERSION 3.20)
project(ATMSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt codegen
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(libpqxx CONFIG REQUIRED)

# Collect sources
file(GLOB FRONTEND_UI   "${CMAKE_CURRENT_SOURCE_DIR}/frontend/*.ui")
file(GLOB FRONTEND_QRC  "${CMAKE_CURRENT_SOURCE_DIR}/frontend/*.qrc")
file(GLOB FRONTEND_SRC  "${CMAKE_CURRENT_SOURCE_DIR}/frontend/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/frontend/*.h")
file(GLOB_RECURSE BACKEND_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/backend/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/backend/*.h"
)

add_executable(ATMSimulator
    ${FRONTEND_SRC}
    ${FRONTEND_UI}
    ${FRONTEND_QRC}
    ${BACKEND_SRC}
    main.cpp
)

# Include paths (after add_executable)
target_include_directories(ATMSimulator
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}          # allows #include "frontend/..."
        ${CMAKE_CURRENT_SOURCE_DIR}/frontend # allows #include "IPage.h"
        ${CMAKE_CURRENT_SOURCE_DIR}/backend  # allows #include "Enums.h"
)

# Let AUTOUIC find .ui files in frontend/
set_property(TARGET ATMSimulator PROPERTY AUTOUIC_SEARCH_PATHS
    "${CMAKE_CURRENT_SOURCE_DIR}/frontend"
)

target_link_libraries(ATMSimulator
    PRIVATE
        Qt6::Widgets
        libpqxx::pqxx
)

if (MSVC)
  target_compile_options(ATMSimulator PRIVATE /W4 /permissive-)
endif()
