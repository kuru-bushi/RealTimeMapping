#include "iostream"
#include <opencv2/opencv.hpp>
// #include <opencv2/xfeatures2d/nonfree.hpp>
#include "ceres/ceres.h"
#include "opencv2/features2d.hpp"
#include<fstream>


void chooseGood(cv::Mat descriptor,std::vector<cv::DMatch> matches, std::vector<cv::DMatch> good_match)
{
	double max_dist = 0; double min_dist = 10;
	 for( int i = 0; i < descriptor.rows; i++ )
		{ double dist = matches[i].distance;
		  if( dist < min_dist ) 
			  min_dist = dist;
		  if( dist > max_dist ) 
			  max_dist = dist;
	    }
	std::vector<cv::DMatch> goodMatches;
	for(int i=0; i <descriptor.rows;i++)
	{
		if(matches[i].distance<3*min_dist)
			goodMatches.push_back(matches[i]);
	}
    good_match = goodMatches;
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
void detection_demo01()
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
    // auto matcher = cv::FlannBasedMatcher matcher;
    // matcher.match(des1, des2, matches);
    // 2. ------------

    // -----------------
    std::vector<cv::DMatch> goodMatches1, goodMatches2, symMatches;
	chooseGood(des1, matches, goodMatches1);
	chooseGood(des2, matches, goodMatches2);

    std::vector<cv::Point2f> match_point1;
    std::vector<cv::Point2f> match_point2;

    std::vector<cv::Point2f> pt1, pt2;
    // kp1[0].convert(pt1);
    // kp2[0].convert(pt2);

    for (auto &it: goodMatches1)
    {
        std::cout << it.queryIdx << std::endl;
        // match_point1.push_back(kp1[it.queryIdx]);
        // match_point1.push_back(kp2[it.trainIdx]);
    }

    // TODO
    // cv::Mat h = cv::findHomography(goodMatches1, goodMatches2);
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
    // detection("test");
    detection_demo01();
    std::cout << "hello world" << std::endl;

    
}


