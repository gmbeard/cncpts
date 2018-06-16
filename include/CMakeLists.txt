add_library(cncpts INTERFACE)
add_library(Cncpts::cncpts ALIAS cncpts)

target_include_directories(
    cncpts
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(
    cncpts
    INTERFACE
        cxx_decltype_auto
)

install(
    DIRECTORY cncpts
    DESTINATION include
)

install(
    TARGETS cncpts
    EXPORT CncptsTargets
)
