/*
 * Copyright © 2016 Artem Smirnov
 * All right reserved.
 * Author: Artem Smirnov <msvrtm@gmail.com>
 * License: http://www.gnu.org/licenses/gpl.txt
 */

#ifndef IFONT_H_
#define IFONT_H_

#include <stdint.h>
#include <cstddef>

struct IFont
{
    enum class Mode
    {
        Antialias,
        Bitmap
    };


    explicit IFont(uint8_t _height, uint8_t _sizeOfBlock, Mode _mode)
        : height(_height), sizeOfBlock(_sizeOfBlock), mode(_mode) {}
    virtual ~IFont() = default;


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

    static inline const IFont::CHAR_INFO *descriptor(const wchar_t ch, const IFont &font);
};

const IFont::CHAR_INFO *IFont::descriptor(const wchar_t ch, const IFont &font)
{
    for (size_t n = 0; n < font.sizeOfBlock; ++n)
    {
        const IFont::BLOCK *const block = &font.blocks()[n];
        if (ch >= block->startChar && ch <= block->endChar)
            return &block->descriptors[ch - block->startChar];
    }

    const IFont::BLOCK *const block = &font.blocks()[font.sizeOfBlock - 1];
    return &block->descriptors[0];
}

#endif /* IFONT_H_ */
