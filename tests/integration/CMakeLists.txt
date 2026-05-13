add_executable(integration_tests
        "system/system_core.cc"
        "sync/mpsc_channel.cc"
        "sync/mpmc_channel.cc"
        "sync/broker.cc"
)

target_link_libraries(integration_tests PRIVATE apex Catch2::Catch2WithMain)
