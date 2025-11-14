# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt (needed for Money.h -> decimal.h, which uses <iostream>)
# And for frontend code, if we test it
find_package(Qt6 COMPONENTS Core)

# Create the test executable
add_executable(
    atm_tests
    test_BanknoteService.cpp
    test_CardService.cpp
    # Add other test files here
)

# Add include directories
target_include_directories(atm_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR} # tests directory
        ${CMAKE_SOURCE_DIR}         # Project root directory
        ${CMAKE_SOURCE_DIR}/backend
        ${CMAKE_SOURCE_DIR}/frontend # In case it's needed
        mocks                       # mocks directory
)

# Link tests with gtest, gmock, our logic library, and Qt
target_link_libraries(atm_tests
    PRIVATE
        atm_logic
        gtest_main
        gmock
        Qt6::Core
)

# Add test to CTest
include(GoogleTest)
gtest_discover_tests(atm_tests)