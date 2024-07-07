cmake_minimum_required(VERSION 3.8.2)
project(mosaic CXX)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)
find_package(Ceres REQUIRED)
find_package( OpenCV REQUIRED )


# --- 確認用 ----
add_executable(test
    test.cpp
)

target_link_libraries( test
    Eigen3::Eigen
    ${OpenCV_LIBS}
)
