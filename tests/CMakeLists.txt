cmake_minimum_required(VERSION 3.25)

project(TestFindLAPACKE LANGUAGES CXX)

# ---------------------------------------------------------------------------
# Options driven by the CI matrix
# ---------------------------------------------------------------------------

# Pass -DLAPACKE_REQUIRED=ON to turn find_package into a hard requirement.
option(LAPACKE_REQUIRED "Invoke find_package(LAPACKE REQUIRED)" OFF)

# Pass -DEXPECT_FOUND=OFF when the scenario expects LAPACKE to be absent.
option(EXPECT_FOUND "Assert that LAPACKE_FOUND matches this value" ON)

# ---------------------------------------------------------------------------
# Find LAPACKE using our module
# ---------------------------------------------------------------------------
if(LAPACKE_REQUIRED)
    find_package(LAPACKE REQUIRED)
else()
    find_package(LAPACKE)
endif()

message(STATUS "LAPACKE_FOUND        : ${LAPACKE_FOUND}")
message(STATUS "LAPACKE_LIBRARIES    : ${LAPACKE_LIBRARIES}")
message(STATUS "LAPACKE_INCLUDE_DIRS : ${LAPACKE_INCLUDE_DIRS}")

# ---------------------------------------------------------------------------
# Assert the outcome matches what the scenario expects.
# This turns a wrong result into a configure-time failure, keeping the CI
# step red without requiring extra shell logic in the workflow.
# ---------------------------------------------------------------------------
if(EXPECT_FOUND AND NOT LAPACKE_FOUND)
    message(FATAL_ERROR
        "Scenario expected LAPACKE to be found, but it was not.\n"
        "  LAPACKE_LIBRARIES    = '${LAPACKE_LIBRARIES}'\n"
        "  LAPACKE_INCLUDE_DIRS = '${LAPACKE_INCLUDE_DIRS}'"
    )
endif()

if(NOT EXPECT_FOUND AND LAPACKE_FOUND)
    message(FATAL_ERROR
        "Scenario expected LAPACKE NOT to be found, but it was.\n"
        "  LAPACKE_LIBRARIES    = '${LAPACKE_LIBRARIES}'\n"
        "  LAPACKE_INCLUDE_DIRS = '${LAPACKE_INCLUDE_DIRS}'"
    )
endif()

# ---------------------------------------------------------------------------
# When found: build a small driver that calls LAPACKE_dgetrf at runtime.
# Linking against LAPACKE::LAPACKE also validates the imported target.
# ---------------------------------------------------------------------------
if(LAPACKE_FOUND)
    add_executable(test_lapacke test_lapacke.cpp)
    target_link_libraries(test_lapacke PRIVATE LAPACKE::LAPACKE)
endif()
