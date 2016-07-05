#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <stdio.h>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>

#ifdef _DEBUG
#pragma comment(lib,"opencv_world300d.lib")
#pragma comment(lib,"opencv_ts300d.lib")
#endif

using namespace cv;
using namespace std;


void mask_stitch(int frame_no, int front_back_diff)
{
	//int型をstring型に変換
	  int frontno = frame_no + front_back_diff;
	  stringstream number;
	  number << std::setw(5) << std::setfill('0') << frame_no;
	  stringstream front_number;
	  front_number << std::setw(5) << std::setfill('0') << frontno;

	//入力先のパス
	string INPUT_PATH_FRONT = "/Users/t2ladmin/Documents/term7/InamiLab/Yurikamome/opencv_mask!/0705/input/front/";
	string INPUT_PATH_BACK = "/Users/t2ladmin/Documents/term7/InamiLab/Yurikamome/opencv_mask!/0705/input/back/";

    // 切り抜きたい新規画像
    string FRONT_IMG_PATH =INPUT_PATH_FRONT + "front" + front_number.str() + ".jpg";
	string BACK_IMG_PATH = INPUT_PATH_BACK + "back" + number.str() + ".jpg";


    // マスク画像
    string MASK_FRONT_IMG_PATH = "front_mask!.png";
	string MASK_BACK_IMG_PATH = "back_mask!.png";

    // 出力先のパス
    string OUTPUT_PATH = "/Users/t2ladmin/Documents/term7/InamiLab/Yurikamome/opencv_mask!/0705/output/";


    /*** 1,新規画像読み込み ***/
    Mat image_front = imread(FRONT_IMG_PATH);
	Mat image_back = imread(BACK_IMG_PATH);
    vector<Mat> channels_front;
    split(image_front, channels_front);   // 読み込んだimageをチャンネル(RGB)ごとに分離してvectorに入れる
	vector<Mat> channels_back;
	split(image_back, channels_back);

    /*** 2,マスク処理 ***/
    Mat mask_front = imread(MASK_FRONT_IMG_PATH, 0); // マスク画像読み込み 引数0はグレースケールで読み込み
    channels_front.push_back(mask_front); // vector最後尾にマスク画像追加
    Mat new_image_front;
    merge(channels_front, new_image_front); // mergeする 

	Mat mask_back = imread(MASK_BACK_IMG_PATH, 0); // マスク画像読み込み 引数0はグレースケールで読み込み
    channels_back.push_back(mask_back); // vector最後尾にマスク画像追加
    Mat new_image_back;
    merge(channels_back, new_image_back); // mergeする 
	
	/***デバッグ用。frontとbackのマスク後の画像を出力***/
	//imwrite(OUTPUT_PATH + "masked_front.png" , new_image_front);
	//imwrite(OUTPUT_PATH + "masked_back.png" , new_image_back);

	/***二つのマスクされた画像を重ね合わせる(frontが前)***/
	new_image_front.copyTo(new_image_back, mask_front);

	/*** 3,画像保存 ***/
    imwrite(OUTPUT_PATH + "gousei" + number.str() + ".jpg" , new_image_back);
}

int main()
{
	int i;
	for(i=1; i<16050; i++){
		mask_stitch(i, 35);
		std::cout << i << " 番目\n";
	}
	
	return 0;
}