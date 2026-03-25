cmake_minimum_required(VERSION 3.25)

project(TestFindLAPACKE LANGUAGES CXX)

# ---------------------------------------------------------------------------
# Find LAPACKE using our module
# ---------------------------------------------------------------------------
find_package(LAPACKE REQUIRED)

message(STATUS "LAPACKE_FOUND        : ${LAPACKE_FOUND}")
message(STATUS "LAPACKE_LIBRARIES    : ${LAPACKE_LIBRARIES}")
message(STATUS "LAPACKE_INCLUDE_DIRS : ${LAPACKE_INCLUDE_DIRS}")

# ---------------------------------------------------------------------------
# When found: build a small driver that calls LAPACKE_dgetrf at runtime.
# Linking against LAPACKE::LAPACKE also validates the imported target.
# ---------------------------------------------------------------------------
add_executable(test_lapacke test_lapacke.cpp)
target_link_libraries(test_lapacke PRIVATE LAPACKE::LAPACKE)
