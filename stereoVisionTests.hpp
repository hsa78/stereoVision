#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <opencv2/imgproc/imgproc.hpp>

#define WINDOW_SIZE 3
#define IMG_ROWS_NUMBER 500
#define IMG_COLS_NUMBER 500

#define RIGHT_ANSWER true
#define WRONG_ANSWER false

#define MAX_PIXEL_VALUE 255

using namespace std;
using namespace cv;

class ImgMaker
{
    public:
        ImgMaker(int _algorithmType,int _rowsNum = IMG_ROWS_NUMBER,int _colsNum = IMG_COLS_NUMBER);
        Mat getImg() {return img;} 
    private:
        int algorithmType;
        int rowsNum;
        int colsNum;
        Mat img;

        vector<vector<int> > makeImgVectorWithAlgorithmType1();
        vector<vector<int> > makeImgVectorWithAlgorithmType2();
        void fillImgWithVector(vector<vector<int> > imgPixelVals);

};


class tester
{

};

class invalidInputTester : public tester
{
    public:
        void testAllFunctionsInputs();
    private:
        bool testDisparityWithWrongXCordination(); //just x is wrong
        bool testDisparityWithWrongYCordination(); // just y is wrong
        bool testDisparityWithWrongCordination();  // both x and y are wrong
        bool testDisparityWithUnInintializedVars();

        bool testSetPixelWithWrongXCordination();
        bool testSetPixelWithWrongYCordination();
        bool testSetPixelWithWrongCordination();
        bool testSetPixelWithNegativeDisparity();
        bool testSetPixelWithMoreThan255Disparity();
        bool testSetPixelWithUnInintializedVars();

        bool testStereoWithSoBigWindowSize();
        bool testStereoWithNegativeMaxDisparity();
        bool testStereoWithVeryBigMaxDisparity();
        bool testStereoWithUnInintializedVars();

        bool testTotalCostWithWrongXCordination();
        bool testTotalCostWithWrongYCordination();
        bool testTotalCostWithWrongCordination();  
        bool testTotalCostWithNegativeD();
        bool testTotalCostWithSoBigD();
        bool testTotalCostWithUnInintializedVars();

};

class resultTester : public tester 
{
    public:
        void testAllFunctionResults();
        void setRightImg(Mat _rightImg);
        void setLeftImg(Mat _leftImg);
    private:
        bool testDisparityResult();
        bool testSetPixelResult();
        bool testTotalCostResult();

    private:
        Mat leftImg;
        Mat rightImg;
};