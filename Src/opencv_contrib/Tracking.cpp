#include <iostream>
#include "opencv2/opencv.hpp"

int main()
{

    std::string path1 = "/home/ikeda/VisualSlam/RealTimeMapping/panda1.png";
    // std::string path1 = "/home/ikeda/VisualSlam/RealTimeMapping/crack_m1.png";
    std::string path2 = "/home/ikeda/VisualSlam/RealTimeMapping/crack_m2.png";
    std::string path3 = "/home/ikeda/VisualSlam/RealTimeMapping/crack_m3.png";

    std::string save_path = "/home/ikeda/VisualSlam/RealTimeMapping/ob_test.jpg";

    auto img = cv::imread(path1);
    auto img_copy = img.clone();
    cv::Mat img_gray;
    cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);
    cv::threshold(img_gray, img_gray, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    std::cout << "start" << std::endl;

    std::vector<std::vector<cv::Point>> contours;

    cv::findContours(img_gray, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
    std::cout << "start" << std::endl;
    std::vector<std::vector<cv::Point>> contours_subset;


    cv::imwrite(save_path, img);
    std::cout << "save_path: " << save_path;
    save_path = "/home/ikeda/VisualSlam/RealTimeMapping/ob_gray.jpg";
    cv::imwrite(save_path, img_gray);

    std::cout << "start" << std::endl;

    std::vector<int> area_id;

    for (int i=0; i < contours.size(); i++) {
        double area = contourArea(contours.at(i));
        if (area > 10) {
        // if (area > 500 && area < 1500) {
            area_id.push_back(i);
            contours_subset.push_back(contours.at(i));
        }
    }
    std::cout << "contours.size(); " << contours.size() << std::endl;
    // 参考: https://geekyisawesome.blogspot.com/2019/07/recognising-simple-shapes-with-opencv.html
    // 参考2: https://cvtech.cc/count/4/

    auto mu = cv::moments(contours[area_id[0]]);
    // auto mu = cv::moments(img_gray, false);
    auto mc = cv::Point2f(mu.m10 / mu.m00 , mu.m01 / mu.m00 );
    // cv::circle(img, mc, 4, cv::Scalar(100), 2, 4);

    std::cout << "area_id.size(); " << area_id.size() << std::endl;

    int idx = 0;
    int x =0, y=0;
    int count=contours.at(0).size();

    // for (int idx=0; idx<contours.size(); idx++)
    // {
    std::cout << "img.rows, img.cols" << img.rows << "," << img.cols << std::endl;
    for (int area_idx=0; area_idx < area_id.size(); area_idx++)
    {
        // auto count=contours[idx];
        auto m = cv::moments(contours[area_id[area_idx]]);
        x = m.m10 / m.m00;
        y = m.m01 / m.m00;
        // x+=contours.at(i).at(j).x;
        // y+=contours.at(i).at(j).y;
        std::cout << "area end" <<x << ", " << y << std::endl;
        cv::circle(img, cv::Point(x,y),5, cv::Scalar(0,0,200),2,4);
    }

    std::string save_path2 = "/home/ikeda/VisualSlam/RealTimeMapping/ob_test2.jpg";
    cv::imwrite(save_path2, img);


    std::cout << "area end" << std::endl;

    cv::Mat mask = cv::Mat::zeros(img.rows, img.cols, CV_8UC1);
    cv::drawContours(mask, contours_subset, -1, cv::Scalar(255), -1);
    std::string save_path3 = "/home/ikeda/VisualSlam/RealTimeMapping/ob_test3_mask.jpg";
    cv::imwrite(save_path3, mask);

    std::cout << "draw end" << std::endl;
    cv::Mat result;
    img_copy.copyTo(result,mask);

    return 0;
}