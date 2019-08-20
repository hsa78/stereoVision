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
