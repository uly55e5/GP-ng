#ifndef TIFFIMGSET_H
#define TIFFIMGSET_H

#include <string>
#include <inttypes.h>
#include <array>
#include  "tiffio.h"

#define MAX_IMG_CNT 4
#
class TiffImg;

class TiffImgSet
{
public:
    TiffImgSet(std::string fileName);
    TIFF* open(int directory=0);
    void close();
    TiffImg* getImg(int num);
private:

    std::string _fileName;
    std::array<TiffImg*,MAX_IMG_CNT> _images;
    void readTags();
};

#endif // TIFFIMGSET_H
