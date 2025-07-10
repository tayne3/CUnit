file(GLOB_RECURSE files *.c *.cpp)

foreach(test_src ${files})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(${test_name} ${test_src})
    target_link_libraries(${test_name} cunit::cunit)
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach(test_src)

set_tests_properties(
    sample 
        PROPERTIES 
        PASS_REGULAR_EXPRESSION 
        "passed"
        FAIL_REGULAR_EXPRESSION 
        "failed"
)

set_tests_properties(
    sample_cpp
        PROPERTIES 
        PASS_REGULAR_EXPRESSION 
        "passed"
        FAIL_REGULAR_EXPRESSION 
        "failed"
)

set_tests_properties(
    expect_fail 
        PROPERTIES 
        PASS_REGULAR_EXPRESSION 
        "failed"
        FAIL_REGULAR_EXPRESSION 
        "passed"
)
