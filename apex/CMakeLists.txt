cmake_minimum_required(VERSION 3.10)

add_library(apex
        "src/system/system_input.cc"
        "src/system/cocoa/apex_application.mm"
        "src/system/cocoa/apex_window.mm"
        "src/system/cocoa/cocoa_display_server.mm"
        "src/system/cocoa/cocoa_display.mm"
)

# Using RTl library
FetchContent_Declare(
        rtl
        GIT_REPOSITORY https://github.com/raustin9/rtl.git
        GIT_TAG main
)
FetchContent_MakeAvailable(rtl)
target_link_libraries(apex PUBLIC rtl)

target_include_directories(apex
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}"
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

if (APPLE)
    message("Apple platform detected")
    target_link_libraries(apex
            PRIVATE
            "-framework Cocoa"
            "-framework Foundation"
            "-framework AppKit"
            "-framework Quartz"
    )
endif ()

# Add macro for detection on debug builds
target_compile_definitions(apex PUBLIC "$<$<CONFIG:Debug>:APEX_DEBUG>")

set_target_properties(apex PROPERTIES
        EXPORT_NAME ApexEngine::apex
        ALIAS_NAME ApexEngine::ApexEngine
)

add_library(ApexEngine::apex ALIAS apex)
set(ApexEngine_FOUND TRUE PARENT_SCOPE)
