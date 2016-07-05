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
	//int�^��string�^�ɕϊ�
	  int frontno = frame_no + front_back_diff;
	  stringstream number;
	  number << std::setw(5) << std::setfill('0') << frame_no;
	  stringstream front_number;
	  front_number << std::setw(5) << std::setfill('0') << frontno;

	//���͐�̃p�X
	string INPUT_PATH_FRONT = "/Users/t2ladmin/Documents/term7/InamiLab/Yurikamome/opencv_mask!/0705/input/front/";
	string INPUT_PATH_BACK = "/Users/t2ladmin/Documents/term7/InamiLab/Yurikamome/opencv_mask!/0705/input/back/";

    // �؂蔲�������V�K�摜
    string FRONT_IMG_PATH =INPUT_PATH_FRONT + "front" + front_number.str() + ".jpg";
	string BACK_IMG_PATH = INPUT_PATH_BACK + "back" + number.str() + ".jpg";


    // �}�X�N�摜
    string MASK_FRONT_IMG_PATH = "front_mask!.png";
	string MASK_BACK_IMG_PATH = "back_mask!.png";

    // �o�͐�̃p�X
    string OUTPUT_PATH = "/Users/t2ladmin/Documents/term7/InamiLab/Yurikamome/opencv_mask!/0705/output/";


    /*** 1,�V�K�摜�ǂݍ��� ***/
    Mat image_front = imread(FRONT_IMG_PATH);
	Mat image_back = imread(BACK_IMG_PATH);
    vector<Mat> channels_front;
    split(image_front, channels_front);   // �ǂݍ���image���`�����l��(RGB)���Ƃɕ�������vector�ɓ����
	vector<Mat> channels_back;
	split(image_back, channels_back);

    /*** 2,�}�X�N���� ***/
    Mat mask_front = imread(MASK_FRONT_IMG_PATH, 0); // �}�X�N�摜�ǂݍ��� ����0�̓O���[�X�P�[���œǂݍ���
    channels_front.push_back(mask_front); // vector�Ō���Ƀ}�X�N�摜�ǉ�
    Mat new_image_front;
    merge(channels_front, new_image_front); // merge���� 

	Mat mask_back = imread(MASK_BACK_IMG_PATH, 0); // �}�X�N�摜�ǂݍ��� ����0�̓O���[�X�P�[���œǂݍ���
    channels_back.push_back(mask_back); // vector�Ō���Ƀ}�X�N�摜�ǉ�
    Mat new_image_back;
    merge(channels_back, new_image_back); // merge���� 
	
	/***�f�o�b�O�p�Bfront��back�̃}�X�N��̉摜���o��***/
	//imwrite(OUTPUT_PATH + "masked_front.png" , new_image_front);
	//imwrite(OUTPUT_PATH + "masked_back.png" , new_image_back);

	/***��̃}�X�N���ꂽ�摜���d�ˍ��킹��(front���O)***/
	new_image_front.copyTo(new_image_back, mask_front);

	/*** 3,�摜�ۑ� ***/
    imwrite(OUTPUT_PATH + "gousei" + number.str() + ".jpg" , new_image_back);
}

int main()
{
	int i;
	for(i=1; i<16050; i++){
		mask_stitch(i, 35);
		std::cout << i << " �Ԗ�\n";
	}
	
	return 0;
}