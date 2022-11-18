include_directories(../)

add_executable(Doctest_vector_tests test_vector.cpp)
target_sources(Doctest_vector_tests PRIVATE ../types/vector.cpp)