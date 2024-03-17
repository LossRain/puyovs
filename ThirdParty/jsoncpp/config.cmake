find_package(jsoncpp CONFIG)
if(NOT jsoncpp_FOUND)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/jsoncpp/jsoncpp)
  add_library(JsonCpp::JsonCpp ALIAS jsoncpp_static)
endif()