#include "tiffimg.h"
#include "tiffio.h"
#include "tiffimgset.h"
#include <iostream>
#include <ios>

TiffImg::TiffImg(TiffImgSet *set):mImgSet(set),mRawValues(nullptr),mRgbValues(nullptr)
{

}

void TiffImg::setPhotometric(TiffImg::Photometric photometric)
{
  mPhotometric=photometric;
}

void TiffImg::setWidth(uint16_t width)
{
  mWidth=width;
}

uint16_t TiffImg::Width() const
{
  return mWidth;
}

void TiffImg::setHeight(uint16_t height)
{
  mHeight=height;
}

uint16_t TiffImg::Height() const
{
  return mHeight;
}

void TiffImg::setSamples(uint16_t samples)
{
  mSamples=samples;
}

void TiffImg::setDepth(uint16_t depth)
{
  mDepth=depth;
}

void TiffImg::setDescription(const std::string &description)
{
  mDescription=description;
}

void TiffImg::setCompression(TiffImg::Compression compression)
{
  mCompression=compression;
}

void TiffImg::setTiffDirectory(uint16_t directory)
{
  mTiffDirectory=directory;
}

void TiffImg::setRowsPerStrip(uint32_t rows)
{
  mRowsPerStrip=rows;
}

void TiffImg::readRawValues()
{
  TIFF * tif=mImgSet->open(mTiffDirectory);
  if(mDepth != 16 || mSamples != 1)
    throw std::exception(); // TODO specific exception type
  if(!mRawValues)
    mRawValues=new std::vector<uint16_t>(mWidth*mHeight);
  int strips=mHeight/mRowsPerStrip;
  int stripSize=mRowsPerStrip*mWidth;
  uint16_t * pos=mRawValues->data();
  for(int i=0; i<strips;i++)
  {
      TIFFReadEncodedStrip(tif,i,pos,-1);
      pos+=stripSize;
  }


}

u_char *TiffImg::rgbaData()
{
  if(!mRgbValues)
    mRgbValues=new std::vector<uint32_t>(mRawValues->size());
  std::transform(mRawValues->begin(),mRawValues->end(),mRgbValues->begin(),[&](uint16_t &raw){
    //std::cout << std::hex << (raw>>8) << "  ";
    return 0xFF000000+(raw>>8)*0x00010000;});
  /* for(int i=0; i<5000;i++)
    {
      std::cout << std::hex << mRawValues->at(i) << " : " << mRgbValues->at(i) << std::hex << std::endl;
    }*/
  return (u_char*)mRgbValues->data();
}
