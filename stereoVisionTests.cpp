#include "stereoVisionTests.hpp"


ImgMaker::ImgMaker(int _algorithmType,int _rowsNum = IMG_ROWS_NUMBER,int _colsNum = IMG_COLS_NUMBER)
{
    algorithmType = _algorithmType;
    rowsNum = max(_rowsNum,0);
    colsNum = max(_colsNum,0);
    img = Mat::zeros(rowsNum,colsNum,CV_8UC1);
}

vector<vector<int> > ImgMaker::makeImgVectorWithAlgorithmType1()
{
    vector<vector<int> > imgValues;

    for(int i = 0; i < rowsNum; i++)
    {
        vector<int> temp;
        imgValues.push_back(temp);

        for(int j = 0; j < colsNum; j++)
        {
            imgValues[i].push_back((i + j) % MAX_PIXEL_VALUE);
        }
    }

    return imgValues;
}

vector<vector<int> > ImgMaker::makeImgVectorWithAlgorithmType2()
{
    vector<vector<int> > imgValues;
    int counter = 0;

    for(int i = 0; i < rowsNum; i++)
    {
        vector<int> temp;
        imgValues.push_back(temp);

        for(int j = 0; j < colsNum; j++)
        {
            imgValues[i].push_back(counter);
            counter = (counter + 1) % MAX_PIXEL_VALUE;
        }
    }

    return imgValues;
}

void ImgMaker::fillImgWithVector(vector<vector<int> > imgPixelVals)
{
    for(int i = 0; i < rowsNum; i++)
    {
        for(int j = 0; j < colsNum; j++)
        {
            img.at<u_int8_t>(i,j) = imgPixelVals[i][j];
        }
    }
}

Tester::Tester(Mat _leftImg , Mat _rightImg)
{
    leftImg = _leftImg;
    rightImg = _rightImg;
    
    stereo = new Stereo(leftImg,rightImg,MAX_DISPARITY,WINDOW_SIZE);
}

void Tester::testAllFuntions()
{
    InvalidInputTester invalidInputTester;
    ResultTester resultTester;

    invalidInputTester.testAllFunctionsInputs();
    resultTester.testAllFunctionResults();
}

void Tester::setLeftImg(Mat _leftImg)
{
    leftImg = _leftImg;
}

void Tester::setRightImg(Mat _rightImg)
{
    rightImg = _rightImg;
}

bool InvalidInputTester::testDisparityWithWrongXCordination()
{
    int wrongXCordination = 700;
    int rightYCordination = 100;

    d_pixel result = stereo->disparity(wrongXCordination,rightYCordination);
    
    if(result.get_x() == wrongXCordination || result.get_disparity() == INVALID_DISPARITY)
        return WRONG_ANSWER;
    else
        return RIGHT_ANSWER;
}

bool InvalidInputTester::testDisparityWithWrongYCordination()
{
    int rightXCordination = 100;
    int wrongYCordination = 700;

    d_pixel result = stereo->disparity(rightXCordination,wrongYCordination);

    if(result.get_y() == wrongYCordination || result.get_disparity() == INVALID_DISPARITY)
        return WRONG_ANSWER;
    else
        return RIGHT_ANSWER;
}

bool InvalidInputTester::testDisparityWithWrongCordination()
{
   int wrongXCordination = 700;
   int wrongYCordination = 750;

   d_pixel result = stereo->disparity(wrongXCordination,wrongYCordination);

   if(result.get_x() == wrongXCordination || result.get_y() == wrongYCordination || 
      result.get_disparity() == INVALID_DISPARITY)
        return WRONG_ANSWER;
   else
        return RIGHT_ANSWER;
}

bool InvalidInputTester::testDisparityWithUnInintializedVars()
{
    int xPos,yPos;

    d_pixel result = stereo->disparity(xPos,yPos);

    return RIGHT_ANSWER; //i could not find a way to check the answer is right or wrong but if this is not checked in function it will be cause runtime error
}