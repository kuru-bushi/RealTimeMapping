#include "iostream"
#include <opencv2/opencv.hpp>
// #include <opencv2/xfeatures2d/nonfree.hpp>
#include "ceres/ceres.h"
#include "opencv2/features2d.hpp"
#include<fstream>
#include <opencv2/opencv.hpp>



std::vector<std::string> IMG_PATHS=
{
    "/home/crack_m1.png",
    "/home/crack_m2.png",
    "/home/crack_m3.png"
};

int main()
{
    auto img1 = cv::imread(IMG_PATHS[0]);
    auto img2 = cv::imread(IMG_PATHS[1]);

    // auto diff_img = img2 - img1;
    auto diff_img = img2;
    std::string save_path ="/home/diff_img.JPG";

    cv::Mat gray_img;
    cvtColor(diff_img, gray_img, cv::COLOR_BGR2GRAY);  //追加　グレースケールに変換

    cv::imshow("test", gray_img);

    // cv::imwrite(save_path, diff_img);

    return 0;
}