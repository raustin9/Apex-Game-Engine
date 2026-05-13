add_executable(unit_tests
        "core/dimension_tests.cc"
        "core/extent_tests.cc"
        "core/handle_tests.cc"
        "containers/slot_map.cc"
        "system/system_event.cc"
)

target_link_libraries(unit_tests PRIVATE apex Catch2::Catch2WithMain)
