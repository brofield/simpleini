# UTF-8 conversion test data

## Differential tests (primary)

`tests/ts-utf8-conversion.cpp` compares `SI_UTF8::Encode` /
`Decode` against the platform C library (`c32rtomb` / `mbrtoc32` from
`<uchar.h>`) for every assigned Unicode scalar value U+0000..U+10FFFF
(excluding surrogate code points U+D800..U+DFFF).

The test requires a UTF-8 locale (`C.UTF-8`, `en_US.UTF-8`, or system
default). It is skipped when `<uchar.h>` or a suitable locale is unavailable.

For each code point the test checks:

1. Our UTF-8 bytes match the system library
2. System UTF-8 decodes back to the same code point
3. Our UTF-8 decodes back to the same code point

## External fixtures

| File | Purpose |
|------|---------|
| `utf8-reject.hex` | Invalid UTF-8 byte sequences (hex) that must fail `SI_UTF8::Decode` and `ConvertFromStore` / `LoadData`. Sourced from [Markus Kuhn UTF-8-test.txt](https://www.cl.cam.ac.uk/~mgk25/ucs/examples/UTF-8-test.txt) sections 3–5 (CC BY 4.0). |
| `utf8-ini-roundtrip.ini` | UTF-8 INI integration test via `CSimpleIniW` |

**utf8-reject.hex** — one byte sequence per line as lowercase hex. Lines
starting with `#` are ignored.
