include_directories(${EMBEDDEDCOMMANDLINE_SOURCE_DIR}/src)
include_directories(${EMBEDDEDCOMMANDLINE_SOURCE_DIR}/test)
include_directories(${EMBEDDEDCOMMANDLINE_SOURCE_DIR}/googlemock/include)
include_directories(${EMBEDDEDCOMMANDLINE_SOURCE_DIR}/googlemock/gtest/include)

add_executable(test DumbLineEditorTest.cpp)

target_link_libraries(test gtest gmock gmock_main)
