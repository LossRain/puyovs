set(MZ_LIB_SUFFIX "-ng")
set(MINIZIP_TARGET minizip${MZ_LIB_SUFFIX})
option(BUILD_SHARED_LIBS "Build shared library" OFF)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/minizip-ng/minizip-ng)
add_library(MiniZip::MiniZip ALIAS ${MINIZIP_TARGET})

