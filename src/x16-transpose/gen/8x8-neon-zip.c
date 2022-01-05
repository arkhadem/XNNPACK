// Auto-generated file. Do not edit!
//   Template: src/x32-transpose/neon-zip.c.in
//   Generator: tools/xngen
//
// Copyright 2021 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.


#include <arm_neon.h>

#include <assert.h>

#include <xnnpack/common.h>
#include <xnnpack/math.h>
#include <xnnpack/transpose.h>


void xnn_x16_transpose_ukernel__8x8_neon_zip(
    const uint16_t *input,
    uint16_t * output,
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

  const uint16_t* i0 = input;

  uint16_t* o0 = (uint16_t*) output;

  do {
    size_t bh = block_height;
    for (; bh >= 8; bh -= 8) {
      uint16x8_t v3_0 = vld1q_u16(i0); i0 = (uint16_t*) ((uintptr_t) i0 + input_stride);
      uint16x8_t v3_1 = vld1q_u16(i0); i0 = (uint16_t*) ((uintptr_t) i0 + input_stride);
      uint16x8_t v3_2 = vld1q_u16(i0); i0 = (uint16_t*) ((uintptr_t) i0 + input_stride);
      uint16x8_t v3_3 = vld1q_u16(i0); i0 = (uint16_t*) ((uintptr_t) i0 + input_stride);
      uint16x8_t v3_4 = vld1q_u16(i0); i0 = (uint16_t*) ((uintptr_t) i0 + input_stride);
      uint16x8_t v3_5 = vld1q_u16(i0); i0 = (uint16_t*) ((uintptr_t) i0 + input_stride);
      uint16x8_t v3_6 = vld1q_u16(i0); i0 = (uint16_t*) ((uintptr_t) i0 + input_stride);
      uint16x8_t v3_7 = vld1q_u16(i0); i0 = (uint16_t*) ((uintptr_t) i0 + input_stride);

      const uint16x8x2_t v2_0 = vzipq_u16(v3_0, v3_4);
      const uint16x8x2_t v2_1 = vzipq_u16(v3_1, v3_5);
      const uint16x8x2_t v2_2 = vzipq_u16(v3_2, v3_6);
      const uint16x8x2_t v2_3 = vzipq_u16(v3_3, v3_7);

      const uint16x8x2_t v1_0 = vzipq_u16(v2_0.val[0], v2_2.val[0]);
      const uint16x8x2_t v1_1 = vzipq_u16(v2_0.val[1], v2_2.val[1]);
      const uint16x8x2_t v1_2 = vzipq_u16(v2_1.val[0], v2_3.val[0]);
      const uint16x8x2_t v1_3 = vzipq_u16(v2_1.val[1], v2_3.val[1]);
      const uint16x8x2_t v0_0 = vzipq_u16(v1_0.val[0], v1_2.val[0]);
      const uint16x8x2_t v0_1 = vzipq_u16(v1_0.val[1], v1_2.val[1]);
      const uint16x8x2_t v0_2 = vzipq_u16(v1_1.val[0], v1_3.val[0]);
      const uint16x8x2_t v0_3 = vzipq_u16(v1_1.val[1], v1_3.val[1]);

      size_t rem = min(block_width - 1, 7);
      uint16_t* o1 = (uint16_t*) ((uintptr_t) o0 + rem * output_stride);
      switch(rem) {
      case (7):
        vst1q_u16(o1, v0_3.val[1]); o1 = (uint16_t*) ((uintptr_t) o1 - output_stride);
      case (6):
        vst1q_u16(o1, v0_3.val[0]); o1 = (uint16_t*) ((uintptr_t) o1 - output_stride);
      case (5):
        vst1q_u16(o1, v0_2.val[1]); o1 = (uint16_t*) ((uintptr_t) o1 - output_stride);
      case (4):
        vst1q_u16(o1, v0_2.val[0]); o1 = (uint16_t*) ((uintptr_t) o1 - output_stride);
      case (3):
        vst1q_u16(o1, v0_1.val[1]); o1 = (uint16_t*) ((uintptr_t) o1 - output_stride);
      case (2):
        vst1q_u16(o1, v0_1.val[0]); o1 = (uint16_t*) ((uintptr_t) o1 - output_stride);
      case (1):
        vst1q_u16(o1, v0_0.val[1]);
      }
      vst1q_u16(o0, v0_0.val[0]); o0 = (uint16_t*) ((uintptr_t) o0 + tile_hbytes);
    }

    if (bh != 0) {
      uint16x8_t v3_0 = vld1q_u16(i0);
      if XNN_UNPREDICTABLE(bh > 1) {
        i0 = (uint16_t*) ((uintptr_t) i0 + input_stride);
      }
      uint16x8_t v3_1 = vld1q_u16(i0);
      if XNN_UNPREDICTABLE(bh > 2) {
        i0 = (uint16_t*) ((uintptr_t) i0 + input_stride);
      }
      uint16x8_t v3_2 = vld1q_u16(i0);
      if XNN_UNPREDICTABLE(bh > 3) {
        i0 = (uint16_t*) ((uintptr_t) i0 + input_stride);
      }
      uint16x8_t v3_3 = vld1q_u16(i0);
      if XNN_UNPREDICTABLE(bh > 4) {
        i0 = (uint16_t*) ((uintptr_t) i0 + input_stride);
      }
      uint16x8_t v3_4 = vld1q_u16(i0);
      if XNN_UNPREDICTABLE(bh > 5) {
        i0 = (uint16_t*) ((uintptr_t) i0 + input_stride);
      }
      uint16x8_t v3_5 = vld1q_u16(i0);
      if XNN_UNPREDICTABLE(bh > 6) {
        i0 = (uint16_t*) ((uintptr_t) i0 + input_stride);
      }
      uint16x8_t v3_6 = vld1q_u16(i0);
      if XNN_UNPREDICTABLE(bh > 7) {
        i0 = (uint16_t*) ((uintptr_t) i0 + input_stride);
      }
      uint16x8_t v3_7 = vmovq_n_u16(0);

      const uint16x8x2_t v2_0 = vzipq_u16(v3_0, v3_4);
      const uint16x8x2_t v2_1 = vzipq_u16(v3_1, v3_5);
      const uint16x8x2_t v2_2 = vzipq_u16(v3_2, v3_6);
      const uint16x8x2_t v2_3 = vzipq_u16(v3_3, v3_7);

      const uint16x8x2_t v1_0 = vzipq_u16(v2_0.val[0], v2_2.val[0]);
      const uint16x8x2_t v1_1 = vzipq_u16(v2_0.val[1], v2_2.val[1]);
      const uint16x8x2_t v1_2 = vzipq_u16(v2_1.val[0], v2_3.val[0]);
      const uint16x8x2_t v1_3 = vzipq_u16(v2_1.val[1], v2_3.val[1]);
      const uint16x8x2_t v0_0 = vzipq_u16(v1_0.val[0], v1_2.val[0]);
      const uint16x8x2_t v0_1 = vzipq_u16(v1_0.val[1], v1_2.val[1]);
      const uint16x8x2_t v0_2 = vzipq_u16(v1_1.val[0], v1_3.val[0]);
      const uint16x8x2_t v0_3 = vzipq_u16(v1_1.val[1], v1_3.val[1]);

      uint16x4_t v0_low = vget_low_u16(v0_0.val[0]);
      uint16x4_t v1_low = vget_low_u16(v0_0.val[1]);
      uint16x4_t v2_low = vget_low_u16(v0_1.val[0]);
      uint16x4_t v3_low = vget_low_u16(v0_1.val[1]);
      uint16x4_t v4_low = vget_low_u16(v0_2.val[0]);
      uint16x4_t v5_low = vget_low_u16(v0_2.val[1]);
      uint16x4_t v6_low = vget_low_u16(v0_3.val[0]);
      uint16x4_t v7_low = vget_low_u16(v0_3.val[1]);

      size_t rem = min(block_width - 1, 7);
      if (bh & 4) {
        uint16_t* o1 = (uint16_t*) ((uintptr_t) o0 + rem * output_stride);
        switch(rem) {
        case (7):
          vst1_u16(o1, v7_low); o1 = (uint16_t*) ((uintptr_t) o1 - output_stride);
        case (6):
          vst1_u16(o1, v6_low); o1 = (uint16_t*) ((uintptr_t) o1 - output_stride);
        case (5):
          vst1_u16(o1, v5_low); o1 = (uint16_t*) ((uintptr_t) o1 - output_stride);
        case (4):
          vst1_u16(o1, v4_low); o1 = (uint16_t*) ((uintptr_t) o1 - output_stride);
        case (3):
          vst1_u16(o1, v3_low); o1 = (uint16_t*) ((uintptr_t) o1 - output_stride);
        case (2):
          vst1_u16(o1, v2_low); o1 = (uint16_t*) ((uintptr_t) o1 - output_stride);
        case (1):
          vst1_u16(o1, v1_low);
        }
        vst1_u16(o0, v0_low); o0 += 4;
        v0_low = vget_high_u16(v0_0.val[0]);
        v1_low = vget_high_u16(v0_0.val[1]);
        v2_low = vget_high_u16(v0_1.val[0]);
        v3_low = vget_high_u16(v0_1.val[1]);
        v4_low = vget_high_u16(v0_2.val[0]);
        v5_low = vget_high_u16(v0_2.val[1]);
        v6_low = vget_high_u16(v0_3.val[0]);
        v7_low = vget_high_u16(v0_3.val[1]);
      }

      if (bh & 2) {
        uint16_t* o1 = (uint16_t*) ((uintptr_t) o0 + rem * output_stride);
        switch(rem) {
        case (7):
          vst1_lane_u32((void*) o1, vreinterpret_u32_u16(v7_low), 0); o1 = (uint16_t*) ((uintptr_t) o1 - output_stride);
        case (6):
          vst1_lane_u32((void*) o1, vreinterpret_u32_u16(v6_low), 0); o1 = (uint16_t*) ((uintptr_t) o1 - output_stride);
        case (5):
          vst1_lane_u32((void*) o1, vreinterpret_u32_u16(v5_low), 0); o1 = (uint16_t*) ((uintptr_t) o1 - output_stride);
        case (4):
          vst1_lane_u32((void*) o1, vreinterpret_u32_u16(v4_low), 0); o1 = (uint16_t*) ((uintptr_t) o1 - output_stride);
        case (3):
          vst1_lane_u32((void*) o1, vreinterpret_u32_u16(v3_low), 0); o1 = (uint16_t*) ((uintptr_t) o1 - output_stride);
        case (2):
          vst1_lane_u32((void*) o1, vreinterpret_u32_u16(v2_low), 0); o1 = (uint16_t*) ((uintptr_t) o1 - output_stride);
        case (1):
          vst1_lane_u32((void*) o1, vreinterpret_u32_u16(v1_low), 0);
        }
        vst1_lane_u32((void*) o0, vreinterpret_u32_u16(v0_low), 0); o0 += 2;
        v0_low = vreinterpret_u16_u64(vshr_n_u64(vreinterpret_u64_u16(v0_low), 32));
        v1_low = vreinterpret_u16_u64(vshr_n_u64(vreinterpret_u64_u16(v1_low), 32));
        v2_low = vreinterpret_u16_u64(vshr_n_u64(vreinterpret_u64_u16(v2_low), 32));
        v3_low = vreinterpret_u16_u64(vshr_n_u64(vreinterpret_u64_u16(v3_low), 32));
        v4_low = vreinterpret_u16_u64(vshr_n_u64(vreinterpret_u64_u16(v4_low), 32));
        v5_low = vreinterpret_u16_u64(vshr_n_u64(vreinterpret_u64_u16(v5_low), 32));
        v6_low = vreinterpret_u16_u64(vshr_n_u64(vreinterpret_u64_u16(v6_low), 32));
        v7_low = vreinterpret_u16_u64(vshr_n_u64(vreinterpret_u64_u16(v7_low), 32));
      }
      if (bh & 1) {
        uint16_t* o1 = (uint16_t*) ((uintptr_t) o0 + rem * output_stride);
        switch(rem) {
        case (7):
          vst1_lane_u16(o1, v7_low, 0); o1 = (uint16_t*) ((uintptr_t) o1 - output_stride);
        case (6):
          vst1_lane_u16(o1, v6_low, 0); o1 = (uint16_t*) ((uintptr_t) o1 - output_stride);
        case (5):
          vst1_lane_u16(o1, v5_low, 0); o1 = (uint16_t*) ((uintptr_t) o1 - output_stride);
        case (4):
          vst1_lane_u16(o1, v4_low, 0); o1 = (uint16_t*) ((uintptr_t) o1 - output_stride);
        case (3):
          vst1_lane_u16(o1, v3_low, 0); o1 = (uint16_t*) ((uintptr_t) o1 - output_stride);
        case (2):
          vst1_lane_u16(o1, v2_low, 0); o1 = (uint16_t*) ((uintptr_t) o1 - output_stride);
        case (1):
          vst1_lane_u16(o1, v1_low, 0);
        }
        vst1_lane_u16(o0, v0_low, 0);
      }
    }

    i0 = (const uint16_t*) ((uintptr_t) i0 + input_reset);
    o0 = (uint16_t*) ((uintptr_t) o0 + output_reset);
    block_width = doz(block_width, tile_width);
  } while (block_width != 0);
}
