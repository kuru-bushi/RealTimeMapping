#include "iostream"
#include <opencv2/opencv.hpp>
// #include <opencv2/xfeatures2d/nonfree.hpp>
#include "ceres/ceres.h"
#include "opencv2/features2d.hpp"
#include<fstream>



void chooseGood(const std::vector<cv::DMatch> matches, std::vector<cv::DMatch> &good_match)
{
    std::cout << "--------------chooseGood()-----------" << std::endl;
	double max_dist = 40; double min_dist = 0.1;
    // --------------------------------------------
    int cnt=0;
    for (auto &it: matches)
    {
        if (it.distance < max_dist)
        {
            good_match.push_back(it);
            cnt++;
        }
    }
    std::cout << cnt << std::endl;
}


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


// findhomography を見つける
void detection_demo01(
    std::vector<cv::KeyPoint> &kp1,
    std::vector<cv::KeyPoint> &kp2,
    cv::Mat &des1,
    cv::Mat &des2,
    std::vector<cv::DMatch> &matches
)
{
    std::string path_img1 = "/home/panda1.png";
    std::string path_img2 = "/home/panda2.png";

    std::cout << "-----------detection_demo01()-----------"  << std::endl;
    std::cout << path_img1  << std::endl;
    std::cout << path_img2 << std::endl;

    cv::Mat img1 = cv::imread(path_img1);
    cv::Mat img2 = cv::imread(path_img2);

    auto detector = cv::SIFT::create();

    detector->detect(img1, kp1);
    detector->detect(img2, kp2);

    detector->compute(img1, kp1, des1);
    detector->compute(img2, kp2, des2);

    // 1. ------------
    auto matcher = cv::BFMatcher::create(cv::NORM_L2);
    matcher->match(des1, des2, matches); //# 成功
    // 1. ------------

    // 2. ------------
    // auto matcher = cv::FlannBasedMatcher matcher;
    // matcher.match(des1, des2, matches);
    // 2. ------------


}


void save_matrix(const std::string file_name, const cv::Mat matrix)
{
    std::cout << " ---------------- save_matrix() ---------------- " << std::endl;
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


// void ChooseGood()
// {

//     std::cout << "chooseGood start" << std::endl;

//     std::cout << "chooseGood start" << std::endl;
//     std::cout << "goodMatches2[0].distance: " ;
//     // std::cout<< goodMatches2[0].distance << std::endl;

//     std::vector<cv::Point2f> match_point1;
//     std::vector<cv::Point2f> match_point2;
//     std::vector<cv::Point2f> pt1, pt2;

//     for (auto &it: goodMatches1)
//     {
//         std::cout << "add pt!!" << std::endl;
//         std::cout << it.queryIdx << std::endl;
//         match_point1.push_back(kp1[it.queryIdx].pt);
//         match_point2.push_back(kp2[it.trainIdx].pt);
//     }

//     // TODO
//     cv::Mat h = cv::findHomography(match_point1, match_point2, cv::RANSAC);
//     std::cout << "findhomo: h" << h << std::endl;
// }

void good_kp(const std::vector<cv::KeyPoint> &kp1,
             const std::vector<cv::KeyPoint> &kp2,
             const std::vector<cv::DMatch> &good_matches,
             std::vector<cv::Point2f> &good_kp1,
             std::vector<cv::Point2f> &good_kp2)
{
    std::cout << " ------------ good_kp() ------------ " << std::endl;
    for (int i =0; i < good_matches.size(); i++)
    {
        good_kp1.push_back(kp1[good_matches[i].queryIdx].pt);
        good_kp2.push_back(kp2[good_matches[i].trainIdx].pt);
    }
}


void get_homography(const std::vector<cv::Point2f> good_kp1, const std::vector<cv::Point2f> good_kp2, cv::Mat &pair_kp)
{
    std::cout << "---------------- get_homography() ---------------- " << std::endl;
    cv::findHomography(good_kp1, good_kp2, pair_kp, cv::RANSAC, 3);
}

int main()
{
    std::vector<cv::KeyPoint> kp1, kp2;
    cv::Mat des1, des2;
    std::vector<cv::DMatch> matches;
    detection_demo01(kp1, kp2, des1, des2, matches);

    std::vector<cv::DMatch> good_matches;
    chooseGood(matches, good_matches);

    std::vector<cv::Point2f> good_kp1, good_kp2;
    good_kp(kp1, kp2, good_matches, good_kp1, good_kp2);

    cv::Mat pair_kp;
    get_homography(good_kp1, good_kp2, pair_kp);

    // std::cout << "pair_kp :" << pair_kp << std::endl;

}
