#include "iostream"
#include <opencv2/opencv.hpp>
// #include <opencv2/xfeatures2d/nonfree.hpp>
#include "opencv2/features2d.hpp"
#include<fstream>


/*

///// EN ////
int 	nfeatures = 0,
int 	nOctaveLayers = 3,
double 	contrastThreshold = 0.04,
double 	edgeThreshold = 10,
double 	sigma = 1.6 



//// JA ///

*/

struct sift_params
{
// sift
    int n_features;
    int nOctaveLayers;
    double contrastThreshold;
    double edgeThreshold;
    double edgeThreshold;

// 画像のペア
    int pair_range;
// 前処理
    // 2値
    // ぼかす
    // 

}




int main(void)
{
    std::vector<sift_params> detect_params;
    
    return 0;
}