cmake_minimum_required(VERSION 3.8.2)
project(mosaic CXX)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)
find_package(Ceres REQUIRED)
find_package( OpenCV REQUIRED )

# --- 確認用 ----
add_executable(hello
hello.cpp
)

target_link_libraries( hello
    Eigen3::Eigen
    Ceres::ceres
    ${OpenCV_LIBS}
)
# --- 確認用 ----

add_executable(mosaic
    main.cpp
)

target_link_libraries( mosaic
    Eigen3::Eigen
    Ceres::ceres
    ${OpenCV_LIBS}
)

target_include_directories( mosaic
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

# ---------
add_executable(diff
bg_diff.cpp
)

target_link_libraries( diff
    Eigen3::Eigen
    Ceres::ceres
    ${OpenCV_LIBS}
)

target_include_directories( diff
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)


# -- blending
# add_executable(blending
#     blending.cpp
# )

# target_link_libraries( blending
#     Eigen3::Eigen
#     Ceres::ceres
#     ${OpenCV_LIBS}
# )
