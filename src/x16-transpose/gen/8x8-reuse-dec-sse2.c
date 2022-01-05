// Auto-generated file. Do not edit!
//   Template: src/x32-transpose/sse2.c.in
//   Generator: tools/xngen
//
// Copyright 2021 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <immintrin.h>

#include <assert.h>

#include <xnnpack/common.h>
#include <xnnpack/math.h>
#include <xnnpack/transpose.h>

void xnn_x16_transpose_ukernel__8x8_reuse_dec_sse2(
    const uint16_t* input,
    uint16_t* output,
    size_t input_stride,
    size_t output_stride,
    size_t block_width,
    size_t block_height)
{
  assert(output_stride >= block_height * sizeof(uint16_t));
  assert(input_stride >= block_width * sizeof(uint16_t));

  const size_t tile_height = 8;
  const size_t tile_width = 8;
  const size_t tile_hbytes = tile_height * sizeof(uint16_t);
  const size_t tile_wbytes = tile_width * sizeof(uint16_t);
  const size_t input_reset = tile_wbytes - (block_height - ((block_height % tile_height) != 0)) * input_stride;
  const size_t output_reset = tile_width * output_stride - round_down_po2(block_height, 2) * sizeof(uint16_t);
  output_stride *= -1;

  const uint16_t* i = input;
  uint16_t* o = (uint16_t*) output;
  do {
    const size_t rem = min(block_width - 1, 7);
    const size_t oN_stride = rem * output_stride;
    size_t bh = block_height;
    for (; bh >= 8; bh -= 8) {
      const __m128i v3_0 = _mm_loadu_si128((const __m128i*) i);
      i = (uint16_t*) ((uintptr_t) i + input_stride);
      const __m128i v3_1 = _mm_loadu_si128((const __m128i*) i);
      i = (uint16_t*) ((uintptr_t) i + input_stride);
      const __m128i v3_2 = _mm_loadu_si128((const __m128i*) i);
      i = (uint16_t*) ((uintptr_t) i + input_stride);
      const __m128i v3_3 = _mm_loadu_si128((const __m128i*) i);
      i = (uint16_t*) ((uintptr_t) i + input_stride);
      const __m128i v3_4 = _mm_loadu_si128((const __m128i*) i);
      i = (uint16_t*) ((uintptr_t) i + input_stride);
      const __m128i v3_5 = _mm_loadu_si128((const __m128i*) i);
      i = (uint16_t*) ((uintptr_t) i + input_stride);
      const __m128i v3_6 = _mm_loadu_si128((const __m128i*) i);
      i = (uint16_t*) ((uintptr_t) i + input_stride);
      const __m128i v3_7 = _mm_loadu_si128((const __m128i*) i);
      i = (uint16_t*) ((uintptr_t) i + input_stride);

      const __m128i v2_0 = _mm_unpacklo_epi16(v3_0, v3_1);
      const __m128i v2_1 = _mm_unpackhi_epi16(v3_0, v3_1);
      const __m128i v2_2 = _mm_unpacklo_epi16(v3_2, v3_3);
      const __m128i v2_3 = _mm_unpackhi_epi16(v3_2, v3_3);
      const __m128i v2_4 = _mm_unpacklo_epi16(v3_4, v3_5);
      const __m128i v2_5 = _mm_unpackhi_epi16(v3_4, v3_5);
      const __m128i v2_6 = _mm_unpacklo_epi16(v3_6, v3_7);
      const __m128i v2_7 = _mm_unpackhi_epi16(v3_6, v3_7);

      const __m128i v1_0 = _mm_unpacklo_epi32(v2_0, v2_2);
      const __m128i v1_1 = _mm_unpackhi_epi32(v2_0, v2_2);
      const __m128i v1_2 = _mm_unpacklo_epi32(v2_1, v2_3);
      const __m128i v1_3 = _mm_unpackhi_epi32(v2_1, v2_3);
      const __m128i v1_4 = _mm_unpacklo_epi32(v2_4, v2_6);
      const __m128i v1_5 = _mm_unpackhi_epi32(v2_4, v2_6);
      const __m128i v1_6 = _mm_unpacklo_epi32(v2_5, v2_7);
      const __m128i v1_7 = _mm_unpackhi_epi32(v2_5, v2_7);

      const __m128i v0_0 = _mm_unpacklo_epi64(v1_0, v1_4);
      const __m128i v0_1 = _mm_unpackhi_epi64(v1_0, v1_4);
      const __m128i v0_2 = _mm_unpacklo_epi64(v1_1, v1_5);
      const __m128i v0_3 = _mm_unpackhi_epi64(v1_1, v1_5);
      const __m128i v0_4 = _mm_unpacklo_epi64(v1_2, v1_6);
      const __m128i v0_5 = _mm_unpackhi_epi64(v1_2, v1_6);
      const __m128i v0_6 = _mm_unpacklo_epi64(v1_3, v1_7);
      const __m128i v0_7 = _mm_unpackhi_epi64(v1_3, v1_7);


      uint16_t* oN = (uint16_t*) ((uintptr_t) o - oN_stride);
      _mm_storeu_si128((__m128i*) oN, v0_7);
      if XNN_UNPREDICTABLE(block_width >= 8) {
        oN = (uint16_t*) ((uintptr_t) oN + output_stride);
      }
      _mm_storeu_si128((__m128i*) oN, v0_6);
      if XNN_UNPREDICTABLE(block_width > 6) {
        oN = (uint16_t*) ((uintptr_t) oN + output_stride);
      }
      _mm_storeu_si128((__m128i*) oN, v0_5);
      if XNN_UNPREDICTABLE(block_width >= 6) {
        oN = (uint16_t*) ((uintptr_t) oN + output_stride);
      }
      _mm_storeu_si128((__m128i*) oN, v0_4);
      if XNN_UNPREDICTABLE(block_width > 4) {
        oN = (uint16_t*) ((uintptr_t) oN + output_stride);
      }
      _mm_storeu_si128((__m128i*) oN, v0_3);
      if XNN_UNPREDICTABLE(block_width >= 4) {
        oN = (uint16_t*) ((uintptr_t) oN + output_stride);
      }
      _mm_storeu_si128((__m128i*) oN, v0_2);
      if XNN_UNPREDICTABLE(block_width > 2) {
        oN = (uint16_t*) ((uintptr_t) oN + output_stride);
      }
      _mm_storeu_si128((__m128i*) oN, v0_1);
      _mm_storeu_si128((__m128i*) o, v0_0);
      o = (uint16_t*) ((uintptr_t) o + tile_hbytes);
    }

    if (bh != 0) {
      const __m128i v3_0 = _mm_loadu_si128((const __m128i*) i);
      if XNN_UNPREDICTABLE(bh >= 2) {
        i = (uint16_t*) ((uintptr_t) i + input_stride);
      }
      const __m128i v3_1 = _mm_loadu_si128((const __m128i*) i);
      if XNN_UNPREDICTABLE(bh > 2) {
        i = (uint16_t*) ((uintptr_t) i + input_stride);
      }
      const __m128i v3_2 = _mm_loadu_si128((const __m128i*) i);
      if XNN_UNPREDICTABLE(bh >= 4) {
        i = (uint16_t*) ((uintptr_t) i + input_stride);
      }
      const __m128i v3_3 = _mm_loadu_si128((const __m128i*) i);
      if XNN_UNPREDICTABLE(bh > 4) {
        i = (uint16_t*) ((uintptr_t) i + input_stride);
      }
      const __m128i v3_4 = _mm_loadu_si128((const __m128i*) i);
      if XNN_UNPREDICTABLE(bh >= 6) {
        i = (uint16_t*) ((uintptr_t) i + input_stride);
      }
      const __m128i v3_5 = _mm_loadu_si128((const __m128i*) i);
      if XNN_UNPREDICTABLE(bh > 6) {
        i = (uint16_t*) ((uintptr_t) i + input_stride);
      }
      const __m128i v3_6 = _mm_loadu_si128((const __m128i*) i);
      const __m128i v3_7 = _mm_undefined_si128();

      const __m128i v2_0 = _mm_unpacklo_epi16(v3_0, v3_1);
      const __m128i v2_1 = _mm_unpackhi_epi16(v3_0, v3_1);
      const __m128i v2_2 = _mm_unpacklo_epi16(v3_2, v3_3);
      const __m128i v2_3 = _mm_unpackhi_epi16(v3_2, v3_3);
      const __m128i v2_4 = _mm_unpacklo_epi16(v3_4, v3_5);
      const __m128i v2_5 = _mm_unpackhi_epi16(v3_4, v3_5);
      const __m128i v2_6 = _mm_unpacklo_epi16(v3_6, v3_7);
      const __m128i v2_7 = _mm_unpackhi_epi16(v3_6, v3_7);

      const __m128i v1_0 = _mm_unpacklo_epi32(v2_0, v2_2);
      const __m128i v1_1 = _mm_unpackhi_epi32(v2_0, v2_2);
      const __m128i v1_2 = _mm_unpacklo_epi32(v2_1, v2_3);
      const __m128i v1_3 = _mm_unpackhi_epi32(v2_1, v2_3);
      const __m128i v1_4 = _mm_unpacklo_epi32(v2_4, v2_6);
      const __m128i v1_5 = _mm_unpackhi_epi32(v2_4, v2_6);
      const __m128i v1_6 = _mm_unpacklo_epi32(v2_5, v2_7);
      const __m128i v1_7 = _mm_unpackhi_epi32(v2_5, v2_7);

      __m128i v0_0 = _mm_unpacklo_epi64(v1_0, v1_4);
      __m128i v0_1 = _mm_unpackhi_epi64(v1_0, v1_4);
      __m128i v0_2 = _mm_unpacklo_epi64(v1_1, v1_5);
      __m128i v0_3 = _mm_unpackhi_epi64(v1_1, v1_5);
      __m128i v0_4 = _mm_unpacklo_epi64(v1_2, v1_6);
      __m128i v0_5 = _mm_unpackhi_epi64(v1_2, v1_6);
      __m128i v0_6 = _mm_unpacklo_epi64(v1_3, v1_7);
      __m128i v0_7 = _mm_unpackhi_epi64(v1_3, v1_7);


      if (bh & 4) {
        uint16_t* oN = (uint16_t*) ((uintptr_t) o - oN_stride);
        _mm_storel_epi64((__m128i*) oN, v0_7);
        if XNN_UNPREDICTABLE(block_width >= 8) {
          oN = (uint16_t*) ((uintptr_t) oN + output_stride);
        }
        _mm_storel_epi64((__m128i*) oN, v0_6);
        if XNN_UNPREDICTABLE(block_width > 6) {
          oN = (uint16_t*) ((uintptr_t) oN + output_stride);
        }
        _mm_storel_epi64((__m128i*) oN, v0_5);
        if XNN_UNPREDICTABLE(block_width >= 6) {
          oN = (uint16_t*) ((uintptr_t) oN + output_stride);
        }
        _mm_storel_epi64((__m128i*) oN, v0_4);
        if XNN_UNPREDICTABLE(block_width > 4) {
          oN = (uint16_t*) ((uintptr_t) oN + output_stride);
        }
        _mm_storel_epi64((__m128i*) oN, v0_3);
        if XNN_UNPREDICTABLE(block_width >= 4) {
          oN = (uint16_t*) ((uintptr_t) oN + output_stride);
        }
        _mm_storel_epi64((__m128i*) oN, v0_2);
        if XNN_UNPREDICTABLE(block_width > 2) {
          oN = (uint16_t*) ((uintptr_t) oN + output_stride);
        }
        _mm_storel_epi64((__m128i*) oN, v0_1);
        _mm_storel_epi64((__m128i*) o, v0_0);
        o += 4;
        v0_0 = _mm_unpackhi_epi64(v0_0, v0_0);
        v0_1 = _mm_unpackhi_epi64(v0_1, v0_1);
        v0_2 = _mm_unpackhi_epi64(v0_2, v0_2);
        v0_3 = _mm_unpackhi_epi64(v0_3, v0_3);
        v0_4 = _mm_unpackhi_epi64(v0_4, v0_4);
        v0_5 = _mm_unpackhi_epi64(v0_5, v0_5);
        v0_6 = _mm_unpackhi_epi64(v0_6, v0_6);
        v0_7 = _mm_unpackhi_epi64(v0_7, v0_7);
      }

      if (bh & 2) {
        uint16_t* oN = (uint16_t*) ((uintptr_t) o - oN_stride);
        *((int*) oN) = _mm_cvtsi128_si32(v0_7);
        if XNN_UNPREDICTABLE(block_width >= 8) {
          oN = (uint16_t*) ((uintptr_t) oN + output_stride);
        }
        *((int*) oN) = _mm_cvtsi128_si32(v0_6);
        if XNN_UNPREDICTABLE(block_width > 6) {
          oN = (uint16_t*) ((uintptr_t) oN + output_stride);
        }
        *((int*) oN) = _mm_cvtsi128_si32(v0_5);
        if XNN_UNPREDICTABLE(block_width >= 6) {
          oN = (uint16_t*) ((uintptr_t) oN + output_stride);
        }
        *((int*) oN) = _mm_cvtsi128_si32(v0_4);
        if XNN_UNPREDICTABLE(block_width > 4) {
          oN = (uint16_t*) ((uintptr_t) oN + output_stride);
        }
        *((int*) oN) = _mm_cvtsi128_si32(v0_3);
        if XNN_UNPREDICTABLE(block_width >= 4) {
          oN = (uint16_t*) ((uintptr_t) oN + output_stride);
        }
        *((int*) oN) = _mm_cvtsi128_si32(v0_2);
        if XNN_UNPREDICTABLE(block_width > 2) {
          oN = (uint16_t*) ((uintptr_t) oN + output_stride);
        }
        *((int*) oN) = _mm_cvtsi128_si32(v0_1);
        *((int*) o) = _mm_cvtsi128_si32(v0_0);
        o += 2;
        v0_0 = _mm_srli_epi64(v0_0, 32);
        v0_1 = _mm_srli_epi64(v0_1, 32);
        v0_2 = _mm_srli_epi64(v0_2, 32);
        v0_3 = _mm_srli_epi64(v0_3, 32);
        v0_4 = _mm_srli_epi64(v0_4, 32);
        v0_5 = _mm_srli_epi64(v0_5, 32);
        v0_6 = _mm_srli_epi64(v0_6, 32);
        v0_7 = _mm_srli_epi64(v0_7, 32);
      }
      if (bh & 1) {
        uint16_t* oN = (uint16_t*) ((uintptr_t) o - oN_stride);
        *((uint16_t*) oN) = (uint16_t) _mm_cvtsi128_si32(v0_7);
        if XNN_UNPREDICTABLE(block_width >= 8) {
          oN = (uint16_t*) ((uintptr_t) oN + output_stride);
        }
        *((uint16_t*) oN) = (uint16_t) _mm_cvtsi128_si32(v0_6);
        if XNN_UNPREDICTABLE(block_width > 6) {
          oN = (uint16_t*) ((uintptr_t) oN + output_stride);
        }
        *((uint16_t*) oN) = (uint16_t) _mm_cvtsi128_si32(v0_5);
        if XNN_UNPREDICTABLE(block_width >= 6) {
          oN = (uint16_t*) ((uintptr_t) oN + output_stride);
        }
        *((uint16_t*) oN) = (uint16_t) _mm_cvtsi128_si32(v0_4);
        if XNN_UNPREDICTABLE(block_width > 4) {
          oN = (uint16_t*) ((uintptr_t) oN + output_stride);
        }
        *((uint16_t*) oN) = (uint16_t) _mm_cvtsi128_si32(v0_3);
        if XNN_UNPREDICTABLE(block_width >= 4) {
          oN = (uint16_t*) ((uintptr_t) oN + output_stride);
        }
        *((uint16_t*) oN) = (uint16_t) _mm_cvtsi128_si32(v0_2);
        if XNN_UNPREDICTABLE(block_width > 2) {
          oN = (uint16_t*) ((uintptr_t) oN + output_stride);
        }
        *((uint16_t*) oN) = (uint16_t) _mm_cvtsi128_si32(v0_1);
        *((uint16_t*) o) = (uint16_t) _mm_cvtsi128_si32(v0_0);
      }
    }

    i = (const uint16_t*) ((uintptr_t) i + input_reset);
    o = (uint16_t*) ((uintptr_t) o + output_reset);
    block_width = doz(block_width, tile_width);
  } while (block_width != 0);
}
