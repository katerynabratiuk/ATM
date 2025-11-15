cmake_minimum_required(VERSION 3.20)
project(ATMSimulator LANGUAGES C CXX)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build/vcpkg_installed/x64-windows")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt codegen
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(libpqxx CONFIG REQUIRED)

file(GLOB FRONTEND_UI   "${CMAKE_CURRENT_SOURCE_DIR}/frontend/*.ui")
file(GLOB FRONTEND_QRC  "${CMAKE_CURRENT_SOURCE_DIR}/frontend/*.qrc")
file(GLOB FRONTEND_SRC  "${CMAKE_CURRENT_SOURCE_DIR}/frontend/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/frontend/*.h")
file(GLOB_RECURSE BACKEND_SRC CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/backend/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/backend/*.h"
)

# exclude other mains
list(FILTER BACKEND_SRC EXCLUDE REGEX ".*/(tests?|examples?|samples?)/.*\\.cpp$")
list(FILTER BACKEND_SRC EXCLUDE REGEX ".*/main[^/]*\\.cpp$")
list(FILTER FRONTEND_SRC EXCLUDE REGEX "CMakeCXXCompilerId\\.c(c|pp)$")
list(FILTER BACKEND_SRC  EXCLUDE REGEX "CMakeCXXCompilerId\\.c(c|pp)$")

add_executable(ATMSimulator
    ${FRONTEND_SRC}
    ${FRONTEND_UI}
    ${FRONTEND_QRC}
    ${BACKEND_SRC}
    main.cpp
)

target_include_directories(ATMSimulator
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/frontend
        ${CMAKE_CURRENT_SOURCE_DIR}/backend
)

set_property(TARGET ATMSimulator PROPERTY AUTOUIC_SEARCH_PATHS
    "${CMAKE_CURRENT_SOURCE_DIR}/frontend"
)

set(BCRYPT_HINT_INCLUDE
    "C:/Program Files/libbcrypt/include"
    "C:/Program Files (x86)/libbcrypt/include"
    "${CMAKE_SOURCE_DIR}/backend/external/libbcrypt/include"
)
set(BCRYPT_HINT_LIB
    "C:/Program Files/libbcrypt/lib"
    "C:/Program Files (x86)/libbcrypt/lib"
    "${CMAKE_SOURCE_DIR}/backend/external/libbcrypt/build/Release"
    "${CMAKE_SOURCE_DIR}/backend/external/libbcrypt/build/Debug"
)

find_path(BCRYPT_INCLUDE_DIR NAMES bcrypt/BCrypt.hpp PATHS ${BCRYPT_HINT_INCLUDE} NO_DEFAULT_PATH)
find_library(BCRYPT_LIBRARY NAMES libbcrypt PATHS ${BCRYPT_HINT_LIB} NO_DEFAULT_PATH)

set(_bcrypt_dll_candidates
    "C:/Program Files/libbcrypt/bin/libbcrypt.dll"
    "C:/Program Files (x86)/libbcrypt/bin/libbcrypt.dll"
    "${CMAKE_SOURCE_DIR}/backend/external/libbcrypt/build/Release/libbcrypt.dll"
    "${CMAKE_SOURCE_DIR}/backend/external/libbcrypt/build/Debug/libbcrypt.dll"
)
foreach(_cand IN LISTS _bcrypt_dll_candidates)
  if(EXISTS "${_cand}")
    set(BCRYPT_DLL "${_cand}")
    break()
  endif()
endforeach()

set(_bcrypt_link_target "")
if (BCRYPT_INCLUDE_DIR AND BCRYPT_LIBRARY)
  message(STATUS "Found libbcrypt: ${BCRYPT_LIBRARY}")
  set(_bcrypt_link_target ${BCRYPT_LIBRARY})
  if (BCRYPT_DLL)
    add_custom_command(TARGET ATMSimulator POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different "${BCRYPT_DLL}" "$<TARGET_FILE_DIR:ATMSimulator>")
  endif()
else()
  set(_bcrypt_vendor_dir "${CMAKE_SOURCE_DIR}/backend/external/libbcrypt")
  set(_bcrypt_vendor_sources
      "${_bcrypt_vendor_dir}/src/bcrypt.c"
      "${_bcrypt_vendor_dir}/src/crypt_blowfish.c"
      "${_bcrypt_vendor_dir}/src/crypt_gensalt.c"
      "${_bcrypt_vendor_dir}/src/wrapper.c"
  )
  if (EXISTS "${_bcrypt_vendor_dir}")
    message(STATUS "Building bundled libbcrypt sources.")
    add_library(libbcrypt STATIC ${_bcrypt_vendor_sources})
    target_include_directories(libbcrypt PUBLIC "${_bcrypt_vendor_dir}/include")
    set(_bcrypt_link_target libbcrypt)
    set(BCRYPT_INCLUDE_DIR "${_bcrypt_vendor_dir}/include")
  else()
    message(WARNING "libbcrypt not found. Update BCRYPT_HINT_* or build/install libbcrypt.")
  endif()
endif()

if (BCRYPT_INCLUDE_DIR)
  target_include_directories(ATMSimulator BEFORE PRIVATE ${BCRYPT_INCLUDE_DIR})
endif()

if (_bcrypt_link_target)
  target_link_libraries(ATMSimulator PRIVATE ${_bcrypt_link_target})
endif()

target_link_libraries(ATMSimulator
    PRIVATE
        Qt6::Widgets
        libpqxx::pqxx
)

if (MSVC)
  target_compile_options(ATMSimulator PRIVATE /W4 /permissive-)
endif()

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ATMSimulator)