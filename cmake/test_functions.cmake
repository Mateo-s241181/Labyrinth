function(add_task_file name)
    # Add the executable
    add_executable(${name} ${name}.cpp)
    # Link the Catch2 library
    target_link_libraries(${name} Catch2::Catch2WithMain)
    # Discover tests
    catch_discover_tests(${name})
endfunction()
