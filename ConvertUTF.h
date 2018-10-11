/*
    Copyright (c) 2018, Jean Pierre Cimalando

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is furnished
    to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
    FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
    COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
    IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
    CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef INCLUDED_SimpleIni_ConvertUTF_h
#define INCLUDED_SimpleIni_ConvertUTF_h

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#if !defined(_MSC_VER)
#include <stdint.h>
#endif
#include <stddef.h>

typedef enum {
    conversionOK,
    sourceExhausted,
    targetExhausted,
    sourceIllegal
} ConversionResult;

typedef enum {
    strictConversion = 0,
    lenientConversion
} ConversionFlags;

#if !defined(_MSC_VER)
typedef uint32_t UTF32;
typedef uint16_t UTF16;
typedef uint8_t UTF8;
#else
typedef unsigned __int32 UTF32;
typedef unsigned __int16 UTF16;
typedef unsigned __int8 UTF8;
#endif

template <class CharSrc, class CharDst>
ConversionResult ConvertUTFtoUTF (
    const CharSrc **sourceStart, const CharSrc *sourceEnd,
    CharDst **targetStart, CharDst *targetEnd, ConversionFlags flags);

ConversionResult ConvertUTF8toUTF16(
    const UTF8 **sourceStart,
    const UTF8 *sourceEnd, UTF16 **targetStart,
    UTF16 *targetEnd, ConversionFlags flags);

ConversionResult ConvertUTF16toUTF8(
    const UTF16 **sourceStart,
    const UTF16 *sourceEnd, UTF8 **targetStart,
    UTF8 *targetEnd, ConversionFlags flags);

ConversionResult ConvertUTF8toUTF32(
    const UTF8 **sourceStart,
    const UTF8 *sourceEnd, UTF32 **targetStart,
    UTF32 *targetEnd, ConversionFlags flags);

ConversionResult ConvertUTF32toUTF8(
    const UTF32 **sourceStart,
    const UTF32 *sourceEnd, UTF8 **targetStart,
    UTF8 *targetEnd, ConversionFlags flags);

ConversionResult ConvertUTF16toUTF32(
    const UTF16 **sourceStart,
    const UTF16 *sourceEnd, UTF32 **targetStart,
    UTF32 *targetEnd, ConversionFlags flags);

ConversionResult ConvertUTF32toUTF16(
    const UTF32 **sourceStart,
    const UTF32 *sourceEnd, UTF16 **targetStart,
    UTF16 *targetEnd, ConversionFlags flags);

#endif // INCLUDED_SimpleIni_ConvertUTF_h
