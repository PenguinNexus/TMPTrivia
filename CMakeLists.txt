cmake_minimum_required(VERSION 3.21)

project(hello_plugin CXX)

add_library(hello_plugin SHARED Plugin.cxx)

target_compile_features(hello_plugin PRIVATE cxx_std_17)

# Point this at the include/ folder of the SDK repository.
target_include_directories(hello_plugin PRIVATE
    "${CMAKE_SOURCE_DIR}/GameClientSDK/include"
)

# Make the plugin self-contained.
target_link_options(hello_plugin PRIVATE
    -static
    -static-libgcc
    -static-libstdc++
)
