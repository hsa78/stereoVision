#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(){
    Mat a;
    Mat b;
    vector<vector<int> > c;
    
    a = imread("./cat.png",CV_LOAD_IMAGE_GRAYSCALE);

    for(int r = 0; r< a.rows; r++){
        vector<int> d(a.cols);
        c.push_back(d);
    }

    b = Mat::zeros(a.rows,a.cols,CV_8UC1);
    cout<<a.rows<<"  "<<a.cols<<endl;
    cout<<a.size<<endl;
    for(int row = 0; row < a.rows; row++){
        for(int col = 0; col < a.cols; col++){
           c[row][col] = int(a.at<uint8_t>(row,col));
        }
    }
    
    for(int row = 0; row < a.rows; row++){
        for(int col = 0; col < a.cols; col++){
            cout<<c[row][col]<<endl;
           b.at<uint8_t>(row,col) = c[row][col];
        }
    }

    imshow("test",a);
    imshow("testB",b);
    waitKey();
}