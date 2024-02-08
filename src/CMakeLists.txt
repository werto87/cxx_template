add_library(cxx_template hello.cxx)

find_package(Boost)

target_link_libraries(cxx_template PUBLIC
        pthread
        boost::boost
        )

target_include_directories(cxx_template INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>)

target_compile_features(cxx_template PUBLIC cxx_std_20)
