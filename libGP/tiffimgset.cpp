#include "tiffimgset.h"
#include "tiffio.h"
#include <iostream>
#include "tiffimg.h"

TiffImgSet::TiffImgSet(std::string fileName):_fileName(fileName)
{
    readTags();
}

TIFF* TiffImgSet::open(int directory)
{
    TIFF* tif = TIFFOpen(_fileName.c_str(), "r");
    TIFFSetDirectory(tif,directory);
    return tif;
}

TiffImg *TiffImgSet::getImg(int num)
{
  _images[num]->readRawValues();
  return _images[num];
}

void TiffImgSet::readTags()
{
  TIFF* tif=open();
        if (tif) {
            int dircount = 0;
            uint16 width,height,depth,samples;
            uint32 rows;
            TiffImg::Photometric photometric;
            TiffImg::Compression compression;
            char* descr=0;
            do {
                TiffImg * tiffImg = new TiffImg(this);
                _images[dircount]=tiffImg;
                TIFFSetDirectory(tif,dircount);
                TIFFGetField(tif,TIFFTAG_PHOTOMETRIC, &photometric);
                TIFFGetField(tif,TIFFTAG_IMAGEWIDTH, &width);
                TIFFGetField(tif,TIFFTAG_IMAGELENGTH, &height);
                TIFFGetField(tif,TIFFTAG_IMAGEDESCRIPTION,&descr);
                TIFFGetField(tif,TIFFTAG_SAMPLESPERPIXEL,&samples);
                TIFFGetField(tif,TIFFTAG_BITSPERSAMPLE,&depth);
                TIFFGetField(tif,TIFFTAG_COMPRESSION,&compression);
                TIFFGetField(tif,TIFFTAG_ROWSPERSTRIP, &rows);

                tiffImg->setTiffDirectory(dircount);
                tiffImg->setPhotometric(photometric);
                tiffImg->setWidth(width);
                tiffImg->setHeight(height);
                tiffImg->setSamples(samples);
                tiffImg->setDepth(depth);
                tiffImg->setDescription(descr);
                tiffImg->setCompression(compression);
                tiffImg->setRowsPerStrip(rows);
                dircount++;
            } while (TIFFReadDirectory(tif) && dircount<MAX_IMG_CNT);
            TIFFClose(tif);
        }
}
