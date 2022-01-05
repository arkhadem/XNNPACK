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

void xnn_x8_transpose_ukernel__16x16_reuse_switch_sse2(
    const uint8_t* input,
    uint8_t* output,
    size_t input_stride,
    size_t output_stride,
    size_t block_width,
    size_t block_height)
{
  assert(output_stride >= block_height * sizeof(uint8_t));
  assert(input_stride >= block_width * sizeof(uint8_t));

  const size_t tile_height = 16;
  const size_t tile_width = 16;
  const size_t tile_hbytes = tile_height * sizeof(uint8_t);
  const size_t tile_wbytes = tile_width * sizeof(uint8_t);
  const size_t input_reset = tile_wbytes - (block_height - ((block_height % tile_height) != 0)) * input_stride;
  const size_t output_reset = tile_width * output_stride - round_down_po2(block_height, 2) * sizeof(uint8_t);

  const uint8_t* i = input;
  uint8_t* o = (uint8_t*) output;
  do {
    const size_t rem = min(block_width - 1, 15);
    const size_t oN_stride = rem * output_stride;
    size_t bh = block_height;
    for (; bh >= 16; bh -= 16) {
      const __m128i v4_0 = _mm_loadu_si128((const __m128i*) i);
      i = (uint8_t*) ((uintptr_t) i + input_stride);
      const __m128i v4_1 = _mm_loadu_si128((const __m128i*) i);
      i = (uint8_t*) ((uintptr_t) i + input_stride);
      const __m128i v4_2 = _mm_loadu_si128((const __m128i*) i);
      i = (uint8_t*) ((uintptr_t) i + input_stride);
      const __m128i v4_3 = _mm_loadu_si128((const __m128i*) i);
      i = (uint8_t*) ((uintptr_t) i + input_stride);
      const __m128i v4_4 = _mm_loadu_si128((const __m128i*) i);
      i = (uint8_t*) ((uintptr_t) i + input_stride);
      const __m128i v4_5 = _mm_loadu_si128((const __m128i*) i);
      i = (uint8_t*) ((uintptr_t) i + input_stride);
      const __m128i v4_6 = _mm_loadu_si128((const __m128i*) i);
      i = (uint8_t*) ((uintptr_t) i + input_stride);
      const __m128i v4_7 = _mm_loadu_si128((const __m128i*) i);
      i = (uint8_t*) ((uintptr_t) i + input_stride);
      const __m128i v4_8 = _mm_loadu_si128((const __m128i*) i);
      i = (uint8_t*) ((uintptr_t) i + input_stride);
      const __m128i v4_9 = _mm_loadu_si128((const __m128i*) i);
      i = (uint8_t*) ((uintptr_t) i + input_stride);
      const __m128i v4_10 = _mm_loadu_si128((const __m128i*) i);
      i = (uint8_t*) ((uintptr_t) i + input_stride);
      const __m128i v4_11 = _mm_loadu_si128((const __m128i*) i);
      i = (uint8_t*) ((uintptr_t) i + input_stride);
      const __m128i v4_12 = _mm_loadu_si128((const __m128i*) i);
      i = (uint8_t*) ((uintptr_t) i + input_stride);
      const __m128i v4_13 = _mm_loadu_si128((const __m128i*) i);
      i = (uint8_t*) ((uintptr_t) i + input_stride);
      const __m128i v4_14 = _mm_loadu_si128((const __m128i*) i);
      i = (uint8_t*) ((uintptr_t) i + input_stride);
      const __m128i v4_15 = _mm_loadu_si128((const __m128i*) i);
      i = (uint8_t*) ((uintptr_t) i + input_stride);

      const __m128i v3_0 = _mm_unpacklo_epi8(v4_0, v4_1);
      const __m128i v3_1 = _mm_unpackhi_epi8(v4_0, v4_1);
      const __m128i v3_2 = _mm_unpacklo_epi8(v4_2, v4_3);
      const __m128i v3_3 = _mm_unpackhi_epi8(v4_2, v4_3);
      const __m128i v3_4 = _mm_unpacklo_epi8(v4_4, v4_5);
      const __m128i v3_5 = _mm_unpackhi_epi8(v4_4, v4_5);
      const __m128i v3_6 = _mm_unpacklo_epi8(v4_6, v4_7);
      const __m128i v3_7 = _mm_unpackhi_epi8(v4_6, v4_7);
      const __m128i v3_8 = _mm_unpacklo_epi8(v4_8, v4_9);
      const __m128i v3_9 = _mm_unpackhi_epi8(v4_8, v4_9);
      const __m128i v3_10 = _mm_unpacklo_epi8(v4_10, v4_11);
      const __m128i v3_11 = _mm_unpackhi_epi8(v4_10, v4_11);
      const __m128i v3_12 = _mm_unpacklo_epi8(v4_12, v4_13);
      const __m128i v3_13 = _mm_unpackhi_epi8(v4_12, v4_13);
      const __m128i v3_14 = _mm_unpacklo_epi8(v4_14, v4_15);
      const __m128i v3_15 = _mm_unpackhi_epi8(v4_14, v4_15);

      const __m128i v2_0 = _mm_unpacklo_epi16(v3_0, v3_2);
      const __m128i v2_1 = _mm_unpackhi_epi16(v3_0, v3_2);
      const __m128i v2_2 = _mm_unpacklo_epi16(v3_1, v3_3);
      const __m128i v2_3 = _mm_unpackhi_epi16(v3_1, v3_3);
      const __m128i v2_4 = _mm_unpacklo_epi16(v3_4, v3_6);
      const __m128i v2_5 = _mm_unpackhi_epi16(v3_4, v3_6);
      const __m128i v2_6 = _mm_unpacklo_epi16(v3_5, v3_7);
      const __m128i v2_7 = _mm_unpackhi_epi16(v3_5, v3_7);
      const __m128i v2_8 = _mm_unpacklo_epi16(v3_8, v3_10);
      const __m128i v2_9 = _mm_unpackhi_epi16(v3_8, v3_10);
      const __m128i v2_10 = _mm_unpacklo_epi16(v3_9, v3_11);
      const __m128i v2_11 = _mm_unpackhi_epi16(v3_9, v3_11);
      const __m128i v2_12 = _mm_unpacklo_epi16(v3_12, v3_14);
      const __m128i v2_13 = _mm_unpackhi_epi16(v3_12, v3_14);
      const __m128i v2_14 = _mm_unpacklo_epi16(v3_13, v3_15);
      const __m128i v2_15 = _mm_unpackhi_epi16(v3_13, v3_15);

      const __m128i v1_0 = _mm_unpacklo_epi32(v2_0, v2_4);
      const __m128i v1_1 = _mm_unpackhi_epi32(v2_0, v2_4);
      const __m128i v1_2 = _mm_unpacklo_epi32(v2_1, v2_5);
      const __m128i v1_3 = _mm_unpackhi_epi32(v2_1, v2_5);
      const __m128i v1_4 = _mm_unpacklo_epi32(v2_2, v2_6);
      const __m128i v1_5 = _mm_unpackhi_epi32(v2_2, v2_6);
      const __m128i v1_6 = _mm_unpacklo_epi32(v2_3, v2_7);
      const __m128i v1_7 = _mm_unpackhi_epi32(v2_3, v2_7);
      const __m128i v1_8 = _mm_unpacklo_epi32(v2_8, v2_12);
      const __m128i v1_9 = _mm_unpackhi_epi32(v2_8, v2_12);
      const __m128i v1_10 = _mm_unpacklo_epi32(v2_9, v2_13);
      const __m128i v1_11 = _mm_unpackhi_epi32(v2_9, v2_13);
      const __m128i v1_12 = _mm_unpacklo_epi32(v2_10, v2_14);
      const __m128i v1_13 = _mm_unpackhi_epi32(v2_10, v2_14);
      const __m128i v1_14 = _mm_unpacklo_epi32(v2_11, v2_15);
      const __m128i v1_15 = _mm_unpackhi_epi32(v2_11, v2_15);

      const __m128i v0_0 = _mm_unpacklo_epi64(v1_0, v1_8);
      const __m128i v0_1 = _mm_unpackhi_epi64(v1_0, v1_8);
      const __m128i v0_2 = _mm_unpacklo_epi64(v1_1, v1_9);
      const __m128i v0_3 = _mm_unpackhi_epi64(v1_1, v1_9);
      const __m128i v0_4 = _mm_unpacklo_epi64(v1_2, v1_10);
      const __m128i v0_5 = _mm_unpackhi_epi64(v1_2, v1_10);
      const __m128i v0_6 = _mm_unpacklo_epi64(v1_3, v1_11);
      const __m128i v0_7 = _mm_unpackhi_epi64(v1_3, v1_11);
      const __m128i v0_8 = _mm_unpacklo_epi64(v1_4, v1_12);
      const __m128i v0_9 = _mm_unpackhi_epi64(v1_4, v1_12);
      const __m128i v0_10 = _mm_unpacklo_epi64(v1_5, v1_13);
      const __m128i v0_11 = _mm_unpackhi_epi64(v1_5, v1_13);
      const __m128i v0_12 = _mm_unpacklo_epi64(v1_6, v1_14);
      const __m128i v0_13 = _mm_unpackhi_epi64(v1_6, v1_14);
      const __m128i v0_14 = _mm_unpacklo_epi64(v1_7, v1_15);
      const __m128i v0_15 = _mm_unpackhi_epi64(v1_7, v1_15);

      uint8_t* oN = (uint8_t*) ((uintptr_t) o + oN_stride);
      switch (rem) {
        case 15:
          _mm_storeu_si128((__m128i*) oN, v0_15);
          oN = (uint8_t*) ((uintptr_t) oN - output_stride);
        case 14:
          _mm_storeu_si128((__m128i*) oN, v0_14);
          oN = (uint8_t*) ((uintptr_t) oN - output_stride);
        case 13:
          _mm_storeu_si128((__m128i*) oN, v0_13);
          oN = (uint8_t*) ((uintptr_t) oN - output_stride);
        case 12:
          _mm_storeu_si128((__m128i*) oN, v0_12);
          oN = (uint8_t*) ((uintptr_t) oN - output_stride);
        case 11:
          _mm_storeu_si128((__m128i*) oN, v0_11);
          oN = (uint8_t*) ((uintptr_t) oN - output_stride);
        case 10:
          _mm_storeu_si128((__m128i*) oN, v0_10);
          oN = (uint8_t*) ((uintptr_t) oN - output_stride);
        case 9:
          _mm_storeu_si128((__m128i*) oN, v0_9);
          oN = (uint8_t*) ((uintptr_t) oN - output_stride);
        case 8:
          _mm_storeu_si128((__m128i*) oN, v0_8);
          oN = (uint8_t*) ((uintptr_t) oN - output_stride);
        case 7:
          _mm_storeu_si128((__m128i*) oN, v0_7);
          oN = (uint8_t*) ((uintptr_t) oN - output_stride);
        case 6:
          _mm_storeu_si128((__m128i*) oN, v0_6);
          oN = (uint8_t*) ((uintptr_t) oN - output_stride);
        case 5:
          _mm_storeu_si128((__m128i*) oN, v0_5);
          oN = (uint8_t*) ((uintptr_t) oN - output_stride);
        case 4:
          _mm_storeu_si128((__m128i*) oN, v0_4);
          oN = (uint8_t*) ((uintptr_t) oN - output_stride);
        case 3:
          _mm_storeu_si128((__m128i*) oN, v0_3);
          oN = (uint8_t*) ((uintptr_t) oN - output_stride);
        case 2:
          _mm_storeu_si128((__m128i*) oN, v0_2);
          oN = (uint8_t*) ((uintptr_t) oN - output_stride);
        case 1:
          _mm_storeu_si128((__m128i*) oN, v0_1);
        case 0:
          _mm_storeu_si128((__m128i*) o, v0_0);
          o = (uint8_t*) ((uintptr_t) o + tile_hbytes);
          break;
        default:
          XNN_UNREACHABLE;
      }
    }

    if (bh != 0) {
      const __m128i v4_0 = _mm_loadu_si128((const __m128i*) i);
      if XNN_UNPREDICTABLE(bh >= 2) {
        i = (uint8_t*) ((uintptr_t) i + input_stride);
      }
      const __m128i v4_1 = _mm_loadu_si128((const __m128i*) i);
      if XNN_UNPREDICTABLE(bh > 2) {
        i = (uint8_t*) ((uintptr_t) i + input_stride);
      }
      const __m128i v4_2 = _mm_loadu_si128((const __m128i*) i);
      if XNN_UNPREDICTABLE(bh >= 4) {
        i = (uint8_t*) ((uintptr_t) i + input_stride);
      }
      const __m128i v4_3 = _mm_loadu_si128((const __m128i*) i);
      if XNN_UNPREDICTABLE(bh > 4) {
        i = (uint8_t*) ((uintptr_t) i + input_stride);
      }
      const __m128i v4_4 = _mm_loadu_si128((const __m128i*) i);
      if XNN_UNPREDICTABLE(bh >= 6) {
        i = (uint8_t*) ((uintptr_t) i + input_stride);
      }
      const __m128i v4_5 = _mm_loadu_si128((const __m128i*) i);
      if XNN_UNPREDICTABLE(bh > 6) {
        i = (uint8_t*) ((uintptr_t) i + input_stride);
      }
      const __m128i v4_6 = _mm_loadu_si128((const __m128i*) i);
      if XNN_UNPREDICTABLE(bh >= 8) {
        i = (uint8_t*) ((uintptr_t) i + input_stride);
      }
      const __m128i v4_7 = _mm_loadu_si128((const __m128i*) i);
      if XNN_UNPREDICTABLE(bh > 8) {
        i = (uint8_t*) ((uintptr_t) i + input_stride);
      }
      const __m128i v4_8 = _mm_loadu_si128((const __m128i*) i);
      if XNN_UNPREDICTABLE(bh >= 10) {
        i = (uint8_t*) ((uintptr_t) i + input_stride);
      }
      const __m128i v4_9 = _mm_loadu_si128((const __m128i*) i);
      if XNN_UNPREDICTABLE(bh > 10) {
        i = (uint8_t*) ((uintptr_t) i + input_stride);
      }
      const __m128i v4_10 = _mm_loadu_si128((const __m128i*) i);
      if XNN_UNPREDICTABLE(bh >= 12) {
        i = (uint8_t*) ((uintptr_t) i + input_stride);
      }
      const __m128i v4_11 = _mm_loadu_si128((const __m128i*) i);
      if XNN_UNPREDICTABLE(bh > 12) {
        i = (uint8_t*) ((uintptr_t) i + input_stride);
      }
      const __m128i v4_12 = _mm_loadu_si128((const __m128i*) i);
      if XNN_UNPREDICTABLE(bh >= 14) {
        i = (uint8_t*) ((uintptr_t) i + input_stride);
      }
      const __m128i v4_13 = _mm_loadu_si128((const __m128i*) i);
      if XNN_UNPREDICTABLE(bh > 14) {
        i = (uint8_t*) ((uintptr_t) i + input_stride);
      }
      const __m128i v4_14 = _mm_loadu_si128((const __m128i*) i);
      const __m128i v4_15 = _mm_undefined_si128();

      const __m128i v3_0 = _mm_unpacklo_epi8(v4_0, v4_1);
      const __m128i v3_1 = _mm_unpackhi_epi8(v4_0, v4_1);
      const __m128i v3_2 = _mm_unpacklo_epi8(v4_2, v4_3);
      const __m128i v3_3 = _mm_unpackhi_epi8(v4_2, v4_3);
      const __m128i v3_4 = _mm_unpacklo_epi8(v4_4, v4_5);
      const __m128i v3_5 = _mm_unpackhi_epi8(v4_4, v4_5);
      const __m128i v3_6 = _mm_unpacklo_epi8(v4_6, v4_7);
      const __m128i v3_7 = _mm_unpackhi_epi8(v4_6, v4_7);
      const __m128i v3_8 = _mm_unpacklo_epi8(v4_8, v4_9);
      const __m128i v3_9 = _mm_unpackhi_epi8(v4_8, v4_9);
      const __m128i v3_10 = _mm_unpacklo_epi8(v4_10, v4_11);
      const __m128i v3_11 = _mm_unpackhi_epi8(v4_10, v4_11);
      const __m128i v3_12 = _mm_unpacklo_epi8(v4_12, v4_13);
      const __m128i v3_13 = _mm_unpackhi_epi8(v4_12, v4_13);
      const __m128i v3_14 = _mm_unpacklo_epi8(v4_14, v4_15);
      const __m128i v3_15 = _mm_unpackhi_epi8(v4_14, v4_15);

      const __m128i v2_0 = _mm_unpacklo_epi16(v3_0, v3_2);
      const __m128i v2_1 = _mm_unpackhi_epi16(v3_0, v3_2);
      const __m128i v2_2 = _mm_unpacklo_epi16(v3_1, v3_3);
      const __m128i v2_3 = _mm_unpackhi_epi16(v3_1, v3_3);
      const __m128i v2_4 = _mm_unpacklo_epi16(v3_4, v3_6);
      const __m128i v2_5 = _mm_unpackhi_epi16(v3_4, v3_6);
      const __m128i v2_6 = _mm_unpacklo_epi16(v3_5, v3_7);
      const __m128i v2_7 = _mm_unpackhi_epi16(v3_5, v3_7);
      const __m128i v2_8 = _mm_unpacklo_epi16(v3_8, v3_10);
      const __m128i v2_9 = _mm_unpackhi_epi16(v3_8, v3_10);
      const __m128i v2_10 = _mm_unpacklo_epi16(v3_9, v3_11);
      const __m128i v2_11 = _mm_unpackhi_epi16(v3_9, v3_11);
      const __m128i v2_12 = _mm_unpacklo_epi16(v3_12, v3_14);
      const __m128i v2_13 = _mm_unpackhi_epi16(v3_12, v3_14);
      const __m128i v2_14 = _mm_unpacklo_epi16(v3_13, v3_15);
      const __m128i v2_15 = _mm_unpackhi_epi16(v3_13, v3_15);

      const __m128i v1_0 = _mm_unpacklo_epi32(v2_0, v2_4);
      const __m128i v1_1 = _mm_unpackhi_epi32(v2_0, v2_4);
      const __m128i v1_2 = _mm_unpacklo_epi32(v2_1, v2_5);
      const __m128i v1_3 = _mm_unpackhi_epi32(v2_1, v2_5);
      const __m128i v1_4 = _mm_unpacklo_epi32(v2_2, v2_6);
      const __m128i v1_5 = _mm_unpackhi_epi32(v2_2, v2_6);
      const __m128i v1_6 = _mm_unpacklo_epi32(v2_3, v2_7);
      const __m128i v1_7 = _mm_unpackhi_epi32(v2_3, v2_7);
      const __m128i v1_8 = _mm_unpacklo_epi32(v2_8, v2_12);
      const __m128i v1_9 = _mm_unpackhi_epi32(v2_8, v2_12);
      const __m128i v1_10 = _mm_unpacklo_epi32(v2_9, v2_13);
      const __m128i v1_11 = _mm_unpackhi_epi32(v2_9, v2_13);
      const __m128i v1_12 = _mm_unpacklo_epi32(v2_10, v2_14);
      const __m128i v1_13 = _mm_unpackhi_epi32(v2_10, v2_14);
      const __m128i v1_14 = _mm_unpacklo_epi32(v2_11, v2_15);
      const __m128i v1_15 = _mm_unpackhi_epi32(v2_11, v2_15);

      __m128i v0_0 = _mm_unpacklo_epi64(v1_0, v1_8);
      __m128i v0_1 = _mm_unpackhi_epi64(v1_0, v1_8);
      __m128i v0_2 = _mm_unpacklo_epi64(v1_1, v1_9);
      __m128i v0_3 = _mm_unpackhi_epi64(v1_1, v1_9);
      __m128i v0_4 = _mm_unpacklo_epi64(v1_2, v1_10);
      __m128i v0_5 = _mm_unpackhi_epi64(v1_2, v1_10);
      __m128i v0_6 = _mm_unpacklo_epi64(v1_3, v1_11);
      __m128i v0_7 = _mm_unpackhi_epi64(v1_3, v1_11);
      __m128i v0_8 = _mm_unpacklo_epi64(v1_4, v1_12);
      __m128i v0_9 = _mm_unpackhi_epi64(v1_4, v1_12);
      __m128i v0_10 = _mm_unpacklo_epi64(v1_5, v1_13);
      __m128i v0_11 = _mm_unpackhi_epi64(v1_5, v1_13);
      __m128i v0_12 = _mm_unpacklo_epi64(v1_6, v1_14);
      __m128i v0_13 = _mm_unpackhi_epi64(v1_6, v1_14);
      __m128i v0_14 = _mm_unpacklo_epi64(v1_7, v1_15);
      __m128i v0_15 = _mm_unpackhi_epi64(v1_7, v1_15);

      if (bh & 8) {
        uint8_t* oN = (uint8_t*) ((uintptr_t) o + oN_stride);
        switch (rem) {
          case 15:
            _mm_storel_epi64((__m128i*) oN, v0_15);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 14:
            _mm_storel_epi64((__m128i*) oN, v0_14);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 13:
            _mm_storel_epi64((__m128i*) oN, v0_13);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 12:
            _mm_storel_epi64((__m128i*) oN, v0_12);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 11:
            _mm_storel_epi64((__m128i*) oN, v0_11);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 10:
            _mm_storel_epi64((__m128i*) oN, v0_10);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 9:
            _mm_storel_epi64((__m128i*) oN, v0_9);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 8:
            _mm_storel_epi64((__m128i*) oN, v0_8);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 7:
            _mm_storel_epi64((__m128i*) oN, v0_7);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 6:
            _mm_storel_epi64((__m128i*) oN, v0_6);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 5:
            _mm_storel_epi64((__m128i*) oN, v0_5);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 4:
            _mm_storel_epi64((__m128i*) oN, v0_4);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 3:
            _mm_storel_epi64((__m128i*) oN, v0_3);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 2:
            _mm_storel_epi64((__m128i*) oN, v0_2);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 1:
            _mm_storel_epi64((__m128i*) oN, v0_1);
          case 0:
            _mm_storel_epi64((__m128i*) o, v0_0);
            break;
          default:
            XNN_UNREACHABLE;
        }
        o += 8;
        v0_0 = _mm_unpackhi_epi64(v0_0, v0_0);
        v0_1 = _mm_unpackhi_epi64(v0_1, v0_1);
        v0_2 = _mm_unpackhi_epi64(v0_2, v0_2);
        v0_3 = _mm_unpackhi_epi64(v0_3, v0_3);
        v0_4 = _mm_unpackhi_epi64(v0_4, v0_4);
        v0_5 = _mm_unpackhi_epi64(v0_5, v0_5);
        v0_6 = _mm_unpackhi_epi64(v0_6, v0_6);
        v0_7 = _mm_unpackhi_epi64(v0_7, v0_7);
        v0_8 = _mm_unpackhi_epi64(v0_8, v0_8);
        v0_9 = _mm_unpackhi_epi64(v0_9, v0_9);
        v0_10 = _mm_unpackhi_epi64(v0_10, v0_10);
        v0_11 = _mm_unpackhi_epi64(v0_11, v0_11);
        v0_12 = _mm_unpackhi_epi64(v0_12, v0_12);
        v0_13 = _mm_unpackhi_epi64(v0_13, v0_13);
        v0_14 = _mm_unpackhi_epi64(v0_14, v0_14);
        v0_15 = _mm_unpackhi_epi64(v0_15, v0_15);
      }

      if (bh & 4) {
        uint8_t* oN = (uint8_t*) ((uintptr_t) o + oN_stride);
        switch (rem) {
          case 15:
            *((int*) oN) = _mm_cvtsi128_si32(v0_15);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 14:
            *((int*) oN) = _mm_cvtsi128_si32(v0_14);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 13:
            *((int*) oN) = _mm_cvtsi128_si32(v0_13);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 12:
            *((int*) oN) = _mm_cvtsi128_si32(v0_12);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 11:
            *((int*) oN) = _mm_cvtsi128_si32(v0_11);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 10:
            *((int*) oN) = _mm_cvtsi128_si32(v0_10);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 9:
            *((int*) oN) = _mm_cvtsi128_si32(v0_9);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 8:
            *((int*) oN) = _mm_cvtsi128_si32(v0_8);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 7:
            *((int*) oN) = _mm_cvtsi128_si32(v0_7);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 6:
            *((int*) oN) = _mm_cvtsi128_si32(v0_6);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 5:
            *((int*) oN) = _mm_cvtsi128_si32(v0_5);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 4:
            *((int*) oN) = _mm_cvtsi128_si32(v0_4);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 3:
            *((int*) oN) = _mm_cvtsi128_si32(v0_3);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 2:
            *((int*) oN) = _mm_cvtsi128_si32(v0_2);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 1:
            *((int*) oN) = _mm_cvtsi128_si32(v0_1);
          case 0:
            *((int*) o) = _mm_cvtsi128_si32(v0_0);
            break;
          default:
            XNN_UNREACHABLE;
        }
        o += 4;
        v0_0 = _mm_srli_epi64(v0_0, 32);
        v0_1 = _mm_srli_epi64(v0_1, 32);
        v0_2 = _mm_srli_epi64(v0_2, 32);
        v0_3 = _mm_srli_epi64(v0_3, 32);
        v0_4 = _mm_srli_epi64(v0_4, 32);
        v0_5 = _mm_srli_epi64(v0_5, 32);
        v0_6 = _mm_srli_epi64(v0_6, 32);
        v0_7 = _mm_srli_epi64(v0_7, 32);
        v0_8 = _mm_srli_epi64(v0_8, 32);
        v0_9 = _mm_srli_epi64(v0_9, 32);
        v0_10 = _mm_srli_epi64(v0_10, 32);
        v0_11 = _mm_srli_epi64(v0_11, 32);
        v0_12 = _mm_srli_epi64(v0_12, 32);
        v0_13 = _mm_srli_epi64(v0_13, 32);
        v0_14 = _mm_srli_epi64(v0_14, 32);
        v0_15 = _mm_srli_epi64(v0_15, 32);
      }
      if (bh & 2) {
        uint8_t* oN = (uint8_t*) ((uintptr_t) o + oN_stride);
        switch (rem) {
          case 15:
            *((uint16_t*) oN) = (uint16_t) _mm_cvtsi128_si32(v0_15);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 14:
            *((uint16_t*) oN) = (uint16_t) _mm_cvtsi128_si32(v0_14);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 13:
            *((uint16_t*) oN) = (uint16_t) _mm_cvtsi128_si32(v0_13);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 12:
            *((uint16_t*) oN) = (uint16_t) _mm_cvtsi128_si32(v0_12);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 11:
            *((uint16_t*) oN) = (uint16_t) _mm_cvtsi128_si32(v0_11);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 10:
            *((uint16_t*) oN) = (uint16_t) _mm_cvtsi128_si32(v0_10);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 9:
            *((uint16_t*) oN) = (uint16_t) _mm_cvtsi128_si32(v0_9);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 8:
            *((uint16_t*) oN) = (uint16_t) _mm_cvtsi128_si32(v0_8);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 7:
            *((uint16_t*) oN) = (uint16_t) _mm_cvtsi128_si32(v0_7);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 6:
            *((uint16_t*) oN) = (uint16_t) _mm_cvtsi128_si32(v0_6);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 5:
            *((uint16_t*) oN) = (uint16_t) _mm_cvtsi128_si32(v0_5);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 4:
            *((uint16_t*) oN) = (uint16_t) _mm_cvtsi128_si32(v0_4);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 3:
            *((uint16_t*) oN) = (uint16_t) _mm_cvtsi128_si32(v0_3);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 2:
            *((uint16_t*) oN) = (uint16_t) _mm_cvtsi128_si32(v0_2);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 1:
            *((uint16_t*) oN) = (uint16_t) _mm_cvtsi128_si32(v0_1);
          case 0:
            *((uint16_t*) o) = (uint16_t) _mm_cvtsi128_si32(v0_0);
            break;
          default:
            XNN_UNREACHABLE;
        }
        o += 2;
        v0_0 = _mm_srli_epi32(v0_0, 16);
        v0_1 = _mm_srli_epi32(v0_1, 16);
        v0_2 = _mm_srli_epi32(v0_2, 16);
        v0_3 = _mm_srli_epi32(v0_3, 16);
        v0_4 = _mm_srli_epi32(v0_4, 16);
        v0_5 = _mm_srli_epi32(v0_5, 16);
        v0_6 = _mm_srli_epi32(v0_6, 16);
        v0_7 = _mm_srli_epi32(v0_7, 16);
        v0_8 = _mm_srli_epi32(v0_8, 16);
        v0_9 = _mm_srli_epi32(v0_9, 16);
        v0_10 = _mm_srli_epi32(v0_10, 16);
        v0_11 = _mm_srli_epi32(v0_11, 16);
        v0_12 = _mm_srli_epi32(v0_12, 16);
        v0_13 = _mm_srli_epi32(v0_13, 16);
        v0_14 = _mm_srli_epi32(v0_14, 16);
        v0_15 = _mm_srli_epi32(v0_15, 16);
      }
      if (bh & 1) {
        uint8_t* oN = (uint8_t*) ((uintptr_t) o + oN_stride);
        switch (rem) {
          case 15:
            *oN = (uint8_t) _mm_cvtsi128_si32(v0_15);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 14:
            *oN = (uint8_t) _mm_cvtsi128_si32(v0_14);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 13:
            *oN = (uint8_t) _mm_cvtsi128_si32(v0_13);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 12:
            *oN = (uint8_t) _mm_cvtsi128_si32(v0_12);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 11:
            *oN = (uint8_t) _mm_cvtsi128_si32(v0_11);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 10:
            *oN = (uint8_t) _mm_cvtsi128_si32(v0_10);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 9:
            *oN = (uint8_t) _mm_cvtsi128_si32(v0_9);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 8:
            *oN = (uint8_t) _mm_cvtsi128_si32(v0_8);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 7:
            *oN = (uint8_t) _mm_cvtsi128_si32(v0_7);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 6:
            *oN = (uint8_t) _mm_cvtsi128_si32(v0_6);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 5:
            *oN = (uint8_t) _mm_cvtsi128_si32(v0_5);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 4:
            *oN = (uint8_t) _mm_cvtsi128_si32(v0_4);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 3:
            *oN = (uint8_t) _mm_cvtsi128_si32(v0_3);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 2:
            *oN = (uint8_t) _mm_cvtsi128_si32(v0_2);
            oN = (uint8_t*) ((uintptr_t) oN - output_stride);
          case 1:
            *oN = (uint8_t) _mm_cvtsi128_si32(v0_1);
          case 0:
            *o = (uint8_t) _mm_cvtsi128_si32(v0_0);
            break;
          default:
            XNN_UNREACHABLE;
        }
      }
    }

    i = (const uint8_t*) ((uintptr_t) i + input_reset);
    o = (uint8_t*) ((uintptr_t) o + output_reset);
    block_width = doz(block_width, tile_width);
  } while (block_width != 0);
}
