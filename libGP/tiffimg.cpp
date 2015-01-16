#include "tiffimg.h"
#include "tiffio.h"
#include "tiffimgset.h"
#include <iostream>
#include <ios>
#include <thread>
TiffImg::TiffImg(TiffImgSet *set):mImgSet(set),mRawValues(nullptr),
    mRgbValues(nullptr),mContrast(UINT16_MAX/100),mBrightness(0)
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
    rgbChanged=true;


}

u_char *TiffImg::rgbaData()
{
    clock_t t;
    if(!mRgbValues)
        mRgbValues=new std::vector<uint32_t>(mRawValues->size());

    std::array<uint32_t,UINT16_MAX+1> cache;
    float cont = float(mContrast)/UINT16_MAX*100;
    if(rgbChanged)
    {
        for(int i=0; i<=UINT16_MAX;i++)
        {
            cache[i]=0xFF000000+((std::min(UINT16_MAX,std::max(0,int(((std::min(UINT16_MAX,std::max(0,i+mBrightness)))-UINT16_MAX/2)*cont+UINT16_MAX/2))))>>8)*0x00010000;
        }

        auto pos = mRgbValues->data();
        auto cpos = cache.data();
        auto rpos = mRawValues->data();
        for(int i=0; i<mRawValues->size();i++)
        {
            *(pos+i) = *(cpos+*(rpos+i));
        }

        rgbChanged=false;
    }
    return (u_char*)mRgbValues->data();
}

void TiffImg::setBrightness(double br)
{

    mBrightness=std::min(UINT16_MAX,std::max(-UINT16_MAX,int(br*UINT16_MAX)));
    rgbChanged=true;
}

void TiffImg::setContrast(double co)
{
    mContrast=std::min(UINT16_MAX,std::max(0,int(co*UINT16_MAX/5)));
    rgbChanged=true;
}


