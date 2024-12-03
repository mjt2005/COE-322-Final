cmake_minimum_required( VERSION 3.20 )
project( main VERSION 1.0 )

message( "Using sources: main.cpp" )
add_executable( main )
target_sources( main PRIVATE main.cpp )

target_compile_features( main PRIVATE cxx_std_17 )
install( TARGETS main DESTINATION . )