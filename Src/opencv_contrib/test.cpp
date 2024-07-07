#include <iostream>
#include "opencv2/opencv.hpp"

// combine 1 src
std::vector<cv::Point2f> getPtPair1()
{
    cv::Point2f c_pt1(200,200);
    cv::Point2f c_pt2(200,300);
    cv::Point2f c_pt3(300,200);
    cv::Point2f c_pt4(300,300);

    std::vector<cv::Point2f> pts = {
        c_pt1,
        c_pt2,
        c_pt3,
        c_pt4
    };
    return pts;
}
// combine 1 dist
std::vector<cv::Point2f> getPtPair1Dist()
{

    cv::Point2f c_pt1(300,300);
    cv::Point2f c_pt2(300,400);
    cv::Point2f c_pt3(400,300);
    cv::Point2f c_pt4(400,400);

    std::vector<cv::Point2f> pts = {
        c_pt1,
        c_pt2,
        c_pt3,
        c_pt4
    };
    return pts;
}


void mosaic()
{
    cv::Mat mosaic = cv::Mat::zeros(500, 500, CV_8U);
    // 他のやり方
    cv::Scalar dot_S(255, 255, 255);
    auto pts = getPtPair1();
    auto pts_dist = getPtPair1Dist();

    // const Mat srcPoints;
    // const Mat& dstPoints;
    cv::Mat mask;
    cv::Mat H  = cv::findHomography(pts, pts_dist, mask, cv::RANSAC, 3);

 
    for (int i=0; i<pts.size(); i++)
    {
        auto c_pt = pts[i];

        cv::circle(mosaic,
                    c_pt,// 座標
                    10, // 半径
                    dot_S, // 色
                    -1, // 内側塗りつぶし1
                    cv::LINE_AA);
        

    }

    cv::imwrite("/home/mosaic.jpg", mosaic);
}

int main()
{

    std::cout << "test" <<std::endl;
    mosaic();
    std::cout << "mosaic" <<std::endl;
}

