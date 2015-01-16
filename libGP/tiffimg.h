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
typedef std::vector<uint16_t> RawVector;
typedef std::vector<uint32_t> RgbVector;
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
  void setBrightness(double br);
  void setContrast(double co);
  static RawVector withBrightness(int32_t brightness, const RawVector& input);
  static RawVector withContrast(uint16_t Contrast, const RawVector& input);

private:


    TiffImgSet* mImgSet;
    Photometric mPhotometric;
    uint16_t mWidth, mHeight, mSamples, mDepth;
    std::string mDescription;
    Compression mCompression;
    RawVector * mRawValues;

    RgbVector * mRgbValues;
    uint16_t mTiffDirectory;
    uint32_t mRowsPerStrip;

    int32_t mBrightness;
    uint16_t mContrast;
    bool rgbChanged;
};

#endif // TIFFIMG_H
