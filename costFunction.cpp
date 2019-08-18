
#include "stdafx.h"

#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

vector<vector<vector<int>>> SSDFunction(Mat right, Mat left, int D) {
	Mat rightGray, leftGray;
	vector<vector<vector<int>>> SSD;
	int C;
	cvtColor(right, rightGray, CV_BGR2GRAY);
	cvtColor(left, leftGray, CV_BGR2GRAY);

	for (int i = 0; i < rightGray.rows; i++){
		SSD.resize(SSD.size() + 1);
		for (int j = 0; j < rightGray.cols; j++) {	
			SSD[i].resize(SSD[i].size() + 1);
			for (int d = 0; d < D; d++) {
				if (i - d < 0)
					break;
				C = (int)leftGray.at<uchar>(i,j)-(int)rightGray.at<uchar>(i-d,j);
				SSD[i][j].push_back(C*C);
			}
		}
	}

	return SSD;
}
