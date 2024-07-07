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


// combine 2 src
std::vector<cv::Point2f> getPtPair2()
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

// combine 2 dist
std::vector<cv::Point2f> getPtPair2Dist()
{

    cv::Point2f c_pt1(300,300);
    cv::Point2f c_pt2(300,500);
    cv::Point2f c_pt3(500,300);
    cv::Point2f c_pt4(400,400);

    std::vector<cv::Point2f> pts = {
        c_pt1,
        c_pt2,
        c_pt3,
        c_pt4
    };

    return pts;
}



// combine 3 src
std::vector<cv::Point2f> getPtPair3()
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

// combine 3 dist
std::vector<cv::Point2f> getPtPair3Dist1()
{

    cv::Point2f c_pt1(300,300);
    cv::Point2f c_pt2(300,500);
    cv::Point2f c_pt3(500,300);
    cv::Point2f c_pt4(400,400);

    std::vector<cv::Point2f> pts = {
        c_pt1,
        c_pt2,
        c_pt3,
        c_pt4
    };

    return pts;
}

// combine 3 dist
std::vector<cv::Point2f> getPtPair3Dist2()
{
    cv::Point2f c_pt1(300, 300);
    cv::Point2f c_pt2(300, 500);
    cv::Point2f c_pt3(500, 300);
    cv::Point2f c_pt4(400, 400);

    std::vector<cv::Point2f> pts = {
        c_pt1,
        c_pt2,
        c_pt3,
        c_pt4
    };

    return pts;
}


void MoisaicPt(const std::vector<cv::Point2f> pt, cv::Mat &mosaic)
{
    cv::Scalar dot_S(255, 255, 255);
    for (int i=0; i<pt.size(); i++)
    {
        auto c_pt = pt[i];

        cv::circle(mosaic,
                    c_pt,// 座標
                    10, // 半径
                    dot_S, // 色
                    -1, // 内側塗りつぶし1
                    cv::LINE_AA);
    }

}

void mosaic()
{
    std::string save_dir = "/home/ikeda/VisualSlam/RealTimeMapping/";
    std::string save_path;
    cv::Mat mosaic;
    // 他のやり方
    int mosaic_size = 1000;
    cv::Scalar dot_S(255, 255, 255);

    /////////////////// edit me ////////////////////////////////
    // demo1: 正方形 -> 正方形 平行移動
    // auto pts = getPtPair1();
    // auto pts_dist = getPtPair1Dist();

    // demo2: 正方形　→ 歪み
    auto pts = getPtPair2();
    auto pts_dist = getPtPair2Dist();

    // demo3: 正方形　→ 歪み & スケール
    auto pts = getPtPair2();
    auto pts_dist = getPtPair2Dist();

    /////////////////// edit me ////////////////////////////////

    // src 射影 → 画像の保存
    mosaic = cv::Mat::zeros(mosaic_size, mosaic_size, CV_8U);
    MoisaicPt(pts, mosaic);
    save_path = save_dir + "mosaic_src.jpg";
    cv::imwrite(save_path, mosaic);

    // dist 射影 → 画像の保存
    mosaic = cv::Mat::zeros(mosaic_size, mosaic_size, CV_8U);
    MoisaicPt(pts_dist, mosaic);
    save_path = save_dir + "mosaic_dist.jpg";
    cv::imwrite(save_path, mosaic);

    // 射影行列使って src 射影 → 画像の保存
    cv::Mat mask;
    cv::Mat H  = cv::findHomography(pts, pts_dist, mask, cv::RANSAC, 3);
    std::cout << "H: " << H << std::endl;
    mosaic = cv::Mat::zeros(mosaic_size, mosaic_size, CV_8U);

    cv::warpPerspective(mosaic, mosaic, H, mosaic.size(), cv::INTER_LINEAR);
    MoisaicPt(pts_dist, mosaic);
    save_path = save_dir + "mosaic_result.jpg";
    cv::imwrite(save_path, mosaic);
}

int main()
{

    std::cout << "test" <<std::endl;
    mosaic();
    std::cout << "mosaic" <<std::endl;
}

