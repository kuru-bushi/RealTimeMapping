cmake_minimum_required(VERSION 3.8.2)
project(mosaic CXX)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)
find_package(Ceres REQUIRED)
find_package( OpenCV REQUIRED )

add_executable(mosaic
    main.cpp
)

target_link_libraries( mosaic
    Eigen3::Eigen
    Ceres::ceres
    ${OpenCV_LIBS}
)

target_link_libraries(main ${OpenCV_LIBS} )