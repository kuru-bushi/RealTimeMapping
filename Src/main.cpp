#include "iostream"
#include <opencv2/opencv.hpp>
// #include <opencv2/xfeatures2d/nonfree.hpp>
#include "ceres/ceres.h"
#include "opencv2/features2d.hpp"
#include<fstream>




void detection(const std::string type)
{
    std::string path_img1 = "/home/panda1.png";
    std::string path_img2 = "/home/panda2.png";

    cv::Mat img1 = cv::imread(path_img1);
    cv::Mat img2 = cv::imread(path_img2);

    auto detector = cv::SIFT::create();
    std::vector<cv::KeyPoint> kp1, kp2;
    cv::Mat des1, des2;
    // std::vector<cv::KeyPoint> kp2;
    // cv::OutputArray des2;

    detector->detect(img1, kp1);
    detector->detect(img2, kp2);

    detector->compute(img1, kp1, des1);
    detector->compute(img2, kp2, des2);

    std::vector<cv::DMatch> matches;
    // 1. ------------
    auto matcher = cv::BFMatcher::create(cv::NORM_L2);
    matcher->match(des1, des2, matches); //# 成功
    // 1. ------------

    // 2. ------------
    // cv::FlannBasedMatcher matcher;
    // matcher.match(des1, des2, matches);
    // 2. ------------

    double max_dist = 0.0, min_dist = 10.0;
    std::vector<cv::DMatch> good_matches;
    for (int i = 0; i < matches.size(); i++)
    {
        if (matches[i].distance <= 2 * min_dist)
        {
            good_matches.push_back(matches[i]);
        }
    }

    cv::Mat img_matches;
    cv::drawMatches(img1, kp1, img2, kp2, good_matches, img_matches
            // cv::calar::all(-1), cv::Scalar::all(-1),
            //    std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS
    );
    
    cv::imwrite("/home/test.jpg", img_matches);
}


void save_matrix(std::string file_name, cv::Mat matrix)
{
    std::string save_dir = "/home/data/pair_img";
    std::string save_path =  save_dir+ "/" + file_name;

    std::ofstream outputfile(save_path);
    // for (auto &it; matrix.row)
    for (int i=0; i < matrix.rows; i++)
    {
        // outputfile << it << ",";
        outputfile << matrix.row(i) << ",";
    }
}

int main()
{
    detection("test");
    std::cout << "hello world" << std::endl;

    
}


