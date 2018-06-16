add_executable(
    tests
    cncpts_tests.cpp
)

target_compile_options(
    tests
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX /permissive->
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Werror -Wall -Wextra>
)

target_link_libraries(
    tests
    PRIVATE
        Cncpts::cncpts
)

add_test(
    Tests
    COMMAND tests
)
