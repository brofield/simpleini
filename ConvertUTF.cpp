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

#include "ConvertUTF.h"
#define MYBOOST_NAMESPACE SimpleIni_ConvertUTF
#include "BoostUTF.hpp"

template <class CharSrc, class CharDst>
ConversionResult ConvertUTFtoUTF(
    const CharSrc **sourceStart, const CharSrc *sourceEnd,
    CharDst **targetStart, CharDst *targetEnd, ConversionFlags flags)
{
    namespace Utf = MYBOOST_NAMESPACE::locale::utf;
    typedef Utf::utf_traits<CharSrc> UtfSrc;
    typedef Utf::utf_traits<CharDst> UtfDst;

    const CharSrc *sourcePtr = *sourceStart;
    CharDst *targetPtr = *targetStart;

    while (sourcePtr < sourceEnd) {
        Utf::code_point cp = UtfSrc::decode(sourcePtr, sourceEnd);

        if (cp == Utf::illegal) {
            if (flags & lenientConversion)
                continue;
            return sourceIllegal;
        }
        if (cp == Utf::incomplete) {
            if (flags & lenientConversion)
                break;
            return sourceExhausted;
        }

        CharDst dst[UtfDst::max_width];
        CharDst *dstend = UtfDst::encode(cp, dst);

        size_t dstchars = dstend - dst;
        size_t dstavail = targetEnd - targetPtr;
        if (dstavail < dstchars)
            return targetExhausted;

        for (size_t i = 0; i < dstchars; ++i)
            *targetPtr++ = dst[i];
    }

    *sourceStart = sourcePtr;
    *targetStart = targetPtr;
    return conversionOK;
}

ConversionResult ConvertUTF8toUTF16(
    const UTF8 **sourceStart,
    const UTF8 *sourceEnd, UTF16 **targetStart,
    UTF16 *targetEnd, ConversionFlags flags)
{
    return ConvertUTFtoUTF<UTF8, UTF16>(sourceStart, sourceEnd, targetStart, targetEnd, flags);
}

ConversionResult ConvertUTF16toUTF8(
    const UTF16 **sourceStart,
    const UTF16 *sourceEnd, UTF8 **targetStart,
    UTF8 *targetEnd, ConversionFlags flags)
{
    return ConvertUTFtoUTF<UTF16, UTF8>(sourceStart, sourceEnd, targetStart, targetEnd, flags);
}

ConversionResult ConvertUTF8toUTF32(
    const UTF8 **sourceStart,
    const UTF8 *sourceEnd, UTF32 **targetStart,
    UTF32 *targetEnd, ConversionFlags flags)
{
    return ConvertUTFtoUTF<UTF8, UTF32>(sourceStart, sourceEnd, targetStart, targetEnd, flags);
}

ConversionResult ConvertUTF32toUTF8(
    const UTF32 **sourceStart,
    const UTF32 *sourceEnd, UTF8 **targetStart,
    UTF8 *targetEnd, ConversionFlags flags)
{
    return ConvertUTFtoUTF<UTF32, UTF8>(sourceStart, sourceEnd, targetStart, targetEnd, flags);
}

ConversionResult ConvertUTF16toUTF32(
    const UTF16 **sourceStart,
    const UTF16 *sourceEnd, UTF32 **targetStart,
    UTF32 *targetEnd, ConversionFlags flags)
{
    return ConvertUTFtoUTF<UTF16, UTF32>(sourceStart, sourceEnd, targetStart, targetEnd, flags);
}

ConversionResult ConvertUTF32toUTF16(
    const UTF32 **sourceStart,
    const UTF32 *sourceEnd, UTF16 **targetStart,
    UTF16 *targetEnd, ConversionFlags flags)
{
    return ConvertUTFtoUTF<UTF32, UTF16>(sourceStart, sourceEnd, targetStart, targetEnd, flags);
}
