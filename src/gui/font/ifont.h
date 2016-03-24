#ifndef IFONT_H_
#define IFONT_H_

#include <stdint.h>

struct IFont
{
    enum class Mode
    {
        Antialias,
        Bitmap
    };


    IFont(uint8_t _height, uint8_t _sizeOfBlock, Mode _mode)
            : height(_height), sizeOfBlock(_sizeOfBlock), mode(_mode) {}


    struct CHAR_INFO
    {
        const uint8_t   fstRow;
        const uint8_t   sizeRow;
        const uint8_t   width;
        const uint16_t position;
    };
    struct BLOCK
    {
        const uint16_t    startChar;
        const uint16_t    endChar;
        const CHAR_INFO *descriptors;
    };

    const uint8_t height;
    const uint8_t sizeOfBlock;
    const Mode   mode;

    virtual const BLOCK *blocks()    const = 0;
    virtual const uint8_t *bitmaps() const = 0;
};


#endif /* IFONT_H_ */
