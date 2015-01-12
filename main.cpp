#include <iostream>
#include "libGP/tiffimg.h"

#include "libGP/tiffimgset.h"
using namespace std;

int main()
{
    TiffImgSet * tiffs = new TiffImgSet("../exdata/1738-16-hdac6.tif");
    TiffImg * tiff = tiffs->getImg(2);
    tiff->readRawValues();
    tiff->rgbaData();
    //char c;
    //std::cin >> c;
    return 0;

}

