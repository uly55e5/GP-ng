#ifndef TIFFIMG_H
#define TIFFIMG_H

#include <inttypes.h>
#include <string>
#include <vector>
#include <valarray>

class TiffImgSet;

class TiffImg
{
public:
  enum class Photometric: uint16_t { WHITISZERO=0, BLACKISZERO=1 };
  enum class Compression: uint16_t { NONE=1,LZW=5 };
  TiffImg(TiffImgSet* set);
  void setPhotometric(Photometric photometric);
  void setWidth(uint16_t width);
  uint16_t Width() const;
  void setHeight(uint16_t height);
  uint16_t Height() const;
  void setSamples(uint16_t samples);
  void setDepth(uint16_t depth);
  void setDescription(const std::string& description);
  void setCompression(Compression compression);
  void setTiffDirectory(uint16_t directory);
  void setRowsPerStrip(uint32_t rows);
  void readRawValues();
  u_char* rgbaData();
private:

    TiffImgSet* mImgSet;
    Photometric mPhotometric;
    uint16_t mWidth, mHeight, mSamples, mDepth;
    std::string mDescription;
    Compression mCompression;
    std::vector<uint16_t> * mRawValues;

    std::vector<uint32_t> * mRgbValues;
    uint16_t mTiffDirectory;
    uint32_t mRowsPerStrip;
};

#endif // TIFFIMG_H
