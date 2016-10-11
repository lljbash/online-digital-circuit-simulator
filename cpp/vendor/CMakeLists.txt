include(ExternalProject)

externalproject_add(gtest_project
    # Comment above line, and uncomment line below to use subversion.
    # SVN_REPOSITORY http://googletest.googlecode.com/svn/trunk/ 
    # Uncomment line below to freeze a revision (here the one for 1.7.0)
    # SVN_REVISION -r700
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    URL https://github.com/google/googletest/archive/release-1.7.0.zip
    URL_HASH SHA256=b58cb7547a28b2c718d1e38aee18a3659c9e3ff52440297e965f5edffe34b6d0
    INSTALL_COMMAND ""
)

externalproject_get_property(gtest_project source_dir binary_dir)
set(GTEST_INCLUDE_DIR "${source_dir}/include" PARENT_SCOPE)
set(GTEST_LIB_DIR "${binary_dir}")

add_library(gtest STATIC IMPORTED GLOBAL)
set_target_properties(gtest PROPERTIES IMPORTED_LOCATION "${GTEST_LIB_DIR}/libgtest.a")
add_dependencies(gtest gtest_project)

add_library(gtest_main STATIC IMPORTED GLOBAL)
set_target_properties(gtest_main PROPERTIES IMPORTED_LOCATION "${GTEST_LIB_DIR}/libgtest_main.a")
add_dependencies(gtest_main gtest_project)

externalproject_add(gflags_project
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gflags
    URL https://github.com/schuhschuh/gflags/archive/v2.1.2.tar.gz
    URL_MD5 ac432de923f9de1e9780b5254884599f
    INSTALL_COMMAND ""
)
externalproject_get_property(gflags_project source_dir binary_dir)
set(GFLAGS_INCLUDE_DIR "${binary_dir}/include" PARENT_SCOPE)
set(GFLAGS_LIB_DIR "${binary_dir}/lib")

add_library(gflags STATIC IMPORTED GLOBAL)
set_target_properties(gflags PROPERTIES IMPORTED_LOCATION "${GFLAGS_LIB_DIR}/libgflags.a")
add_dependencies(gflags gflags_project)
