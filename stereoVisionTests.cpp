#include "stereoVisionTests.hpp"

ImgMaker::ImgMaker(int _algorithmType,int _rowsNum = IMG_ROWS_NUMBER,int _colsNum = IMG_COLS_NUMBER)
{
    algorithmType = _algorithmType;
    rowsNum = max(_rowsNum,0);
    colsNum = max(_colsNum,0);
}

