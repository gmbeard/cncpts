cmake_minimum_required(VERSION 3.7)

project(Cncpts CXX)

add_subdirectory(include)

set(CNCPTS_ENABLE_TESTS
    OFF
    CACHE
    BOOL
    "Enable tests for ${PROJECT_NAME}"
)

if(CNCPTS_ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

install(
    FILES cmake/CncptsConfig.cmake
    DESTINATION lib/cmake/cncpts
)

install(
    EXPORT CncptsTargets
    NAMESPACE Cncpts::
    FILE CncptsTargets.cmake
    DESTINATION lib/cmake/cncpts
)
