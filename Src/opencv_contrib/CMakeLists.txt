cmake_minimum_required(VERSION 3.8.2)
project(mosaic CXX)

# CERES-Solver に Eigen が入っているため、Eigen のビルドは不要(なはず)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)
# find_package(Ceres REQUIRED)
find_package( OpenCV REQUIRED )


# --- 確認用 ----
# add_executable(HomoTest
#     HomoTest.cpp
# )

# target_link_libraries( HomoTest
#     Eigen3::Eigen
#     ${OpenCV_LIBS}
# )
# --- Object Tracking ----
add_executable(TestTracking
    Tracking.cpp
)

target_link_libraries( TestTracking
    Eigen3::Eigen
    ${OpenCV_LIBS}
)
