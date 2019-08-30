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

Tester::Tester(Mat _leftImg = ImgMaker(1).getImg() , Mat _rightImg = ImgMaker(1).getImg())
{
    leftImg = _leftImg;
    rightImg = _rightImg;
    
    stereo = new Stereo(leftImg,rightImg,MAX_DISPARITY,WINDOW_SIZE);
}

void Tester::testAllFuntions()
{
    InvalidInputTester invalidInputTester = InvalidInputTester();
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

InvalidInputTester::InvalidInputTester()
{
    wrongXCordination = 700;
    wrongYCordination = 700;
    rightXCordination = 100;
    rightYCordination = 100;
    rightDisparity = 10;
    negativeDisparity = -10;
    outOfBondDisparity = 400;
    outOfBondWindowSize = 700;
}

bool InvalidInputTester::testDisparityWithWrongXCordination()
{
    d_pixel result = stereo->disparity(wrongXCordination,rightYCordination);
    
    if(result.get_x() == wrongXCordination || result.get_disparity() == INVALID_DISPARITY)
        return WRONG_ANSWER;
    else
        return RIGHT_ANSWER;
}

bool InvalidInputTester::testDisparityWithWrongYCordination()
{
    d_pixel result = stereo->disparity(rightXCordination,wrongYCordination);

    if(result.get_y() == wrongYCordination || result.get_disparity() == INVALID_DISPARITY)
        return WRONG_ANSWER;
    else
        return RIGHT_ANSWER;
}

bool InvalidInputTester::testDisparityWithWrongCordination()
{
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

bool InvalidInputTester::testSetPixelWithWrongXCordination()
{
    stereo->set_pixel(d_pixel(wrongXCordination,rightYCordination,rightDisparity));//set_pixel could return response

    Mat stereoResult = stereo->get_result();

    if(stereoResult.at<u_int8_t>(wrongXCordination,rightYCordination) == rightDisparity)
        return WRONG_ANSWER;
    else
        return RIGHT_ANSWER; 
}

bool InvalidInputTester::testSetPixelWithWrongYCordination()
{
    stereo->set_pixel(d_pixel(rightXCordination,wrongYCordination,rightDisparity));

    Mat stereoResult = stereo->get_result();

    if(stereoResult.at<u_int8_t>(rightXCordination,wrongYCordination) == rightDisparity)
        return WRONG_ANSWER;
    else
        return RIGHT_ANSWER; 
}

bool InvalidInputTester::testSetPixelWithWrongCordination()
{
    stereo->set_pixel(d_pixel(wrongXCordination,wrongYCordination,rightDisparity));
    Mat stereoResult = stereo->get_result();

    if(stereoResult.at<u_int8_t>(wrongXCordination,wrongYCordination) == rightDisparity)
        return WRONG_ANSWER;
    else
        return RIGHT_ANSWER; 
}

bool InvalidInputTester::testSetPixelWithNegativeDisparity()
{
    stereo->set_pixel(d_pixel(rightXCordination,rightYCordination,negativeDisparity));

    Mat stereoResult = stereo->get_result();

    if(stereoResult.at<u_int8_t>(rightXCordination,rightYCordination) == negativeDisparity)
        return WRONG_ANSWER;
    else
        return RIGHT_ANSWER; 
}

bool InvalidInputTester::testSetPixelWithMoreThan255Disparity()
{
    stereo->set_pixel(d_pixel(rightXCordination,rightYCordination,outOfBondDisparity));

    Mat stereoResult = stereo->get_result();

    if(stereoResult.at<u_int8_t>(rightXCordination,rightYCordination) == outOfBondDisparity)
        return WRONG_ANSWER;
    else
        return RIGHT_ANSWER; 
}

bool InvalidInputTester::testSetPixelWithUnInintializedVars()
{
    int xPos,yPos,disparity;
    stereo->set_pixel(d_pixel(xPos,yPos,disparity));

    return RIGHT_ANSWER;//i could not find a way to check the answer is right or wrong but if this is not checked in function it will be cause runtime error
}

bool InvalidInputTester::testStereoWithSoBigWindowSize()
{
    Stereo stereoTest = Stereo(ImgMaker(1).getImg(),ImgMaker(1).getImg(),MAX_DISPARITY,outOfBondWindowSize);
    //TODO Stereo at least should have geters i could not check functionality

    return RIGHT_ANSWER;
}

bool InvalidInputTester::testStereoWithNegativeMaxDisparity()
{
    Stereo stereoTest = Stereo(ImgMaker(1).getImg(),ImgMaker(1).getImg(),negativeDisparity,WINDOW_SIZE);
    //TODO Stereo at least should have geters i could not check functionality

    return RIGHT_ANSWER;
}

bool InvalidInputTester::testStereoWithVeryBigMaxDisparity()
{
    Stereo stereoTest = Stereo(ImgMaker(1).getImg(),ImgMaker(1).getImg(),outOfBondDisparity,WINDOW_SIZE);
    //TODO Stereo at least should have geters i could not check functionality

    return RIGHT_ANSWER;
}

bool InvalidInputTester::testStereoWithUnInintializedVars()
{
    int windowSize,disparity;
    Mat img1,img2;
    Stereo stereoTest = Stereo(img1,img2,disparity,windowSize);
    //TODO Stereo at least should have geters i could not check functionality

    return RIGHT_ANSWER;
}

void InvalidInputTester::testAllFunctionsInputs()
{
    assert(testDisparityWithWrongXCordination());
    assert(testDisparityWithWrongYCordination());
    assert(testDisparityWithWrongCordination());
    assert(testDisparityWithUnInintializedVars());

    assert(testSetPixelWithWrongXCordination());
    assert(testSetPixelWithWrongYCordination());
    assert(testSetPixelWithWrongCordination());
    assert(testSetPixelWithNegativeDisparity());
    assert(testSetPixelWithMoreThan255Disparity());
    assert(testSetPixelWithUnInintializedVars());

    assert(testStereoWithSoBigWindowSize());
    assert(testStereoWithNegativeMaxDisparity());
    assert(testStereoWithVeryBigMaxDisparity());
    assert(testStereoWithUnInintializedVars());
}



