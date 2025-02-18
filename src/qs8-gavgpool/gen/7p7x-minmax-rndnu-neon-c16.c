// Auto-generated file. Do not edit!
//   Template: src/qs8-gavgpool/multipass-neon.c.in
//   Generator: tools/xngen
//
// Copyright 2020 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <arm_neon.h>

#include <xnnpack/gavgpool.h>
#include <xnnpack/math.h>


void xnn_qs8_gavgpool_minmax_rndnu_ukernel_7p7x__neon_c16(
    size_t rows,
    size_t channels,
    const int8_t* input,
    size_t input_stride,
    const int8_t* zero,
    int32_t* buffer,
    int8_t* output,
    const union xnn_qs8_avgpool_minmax_params params[restrict XNN_MIN_ELEMENTS(1)]) XNN_OOB_READS
{
  assert(rows > 7);
  assert(channels != 0);

  const int8_t* i0 = input;
  const int8_t* i1 = (const int8_t*) ((uintptr_t) i0 + input_stride);
  const int8_t* i2 = (const int8_t*) ((uintptr_t) i1 + input_stride);
  const int8_t* i3 = (const int8_t*) ((uintptr_t) i2 + input_stride);
  const int8_t* i4 = (const int8_t*) ((uintptr_t) i3 + input_stride);
  const int8_t* i5 = (const int8_t*) ((uintptr_t) i4 + input_stride);
  const int8_t* i6 = (const int8_t*) ((uintptr_t) i5 + input_stride);
  const size_t input_increment = 7 * input_stride - round_up_po2(channels, 16);

  const int32x4_t vinit_bias = vld1q_dup_s32(&params->rndnu_neon.init_bias);
  int32_t* b = buffer;
  size_t c = channels;
  for (; c != 0; c = doz(c, 16)) {
    const int8x8_t vi0x01234567 = vld1_s8(i0); i0 += 8;
    const int8x8_t vi0x89ABCDEF = vld1_s8(i0); i0 += 8;
    const int8x8_t vi1x01234567 = vld1_s8(i1); i1 += 8;
    const int8x8_t vi1x89ABCDEF = vld1_s8(i1); i1 += 8;

    const int8x8_t vi2x01234567 = vld1_s8(i2); i2 += 8;
    int16x8_t vsum01234567 = vaddl_s8(vi0x01234567, vi1x01234567);
    const int8x8_t vi2x89ABCDEF = vld1_s8(i2); i2 += 8;
    int16x8_t vsum89ABCDEF = vaddl_s8(vi0x89ABCDEF, vi1x89ABCDEF);

    const int8x8_t vi3x01234567 = vld1_s8(i3); i3 += 8;
    vsum01234567 = vaddw_s8(vsum01234567, vi2x01234567);
    const int8x8_t vi3x89ABCDEF = vld1_s8(i3); i3 += 8;
    vsum89ABCDEF = vaddw_s8(vsum89ABCDEF, vi2x89ABCDEF);
    const int8x8_t vi4x01234567 = vld1_s8(i4); i4 += 8;
    vsum01234567 = vaddw_s8(vsum01234567, vi3x01234567);
    const int8x8_t vi4x89ABCDEF = vld1_s8(i4); i4 += 8;
    vsum89ABCDEF = vaddw_s8(vsum89ABCDEF, vi3x89ABCDEF);
    const int8x8_t vi5x01234567 = vld1_s8(i5); i5 += 8;
    vsum01234567 = vaddw_s8(vsum01234567, vi4x01234567);
    const int8x8_t vi5x89ABCDEF = vld1_s8(i5); i5 += 8;
    vsum89ABCDEF = vaddw_s8(vsum89ABCDEF, vi4x89ABCDEF);
    const int8x8_t vi6x01234567 = vld1_s8(i6); i6 += 8;
    vsum01234567 = vaddw_s8(vsum01234567, vi5x01234567);
    const int8x8_t vi6x89ABCDEF = vld1_s8(i6); i6 += 8;
    vsum89ABCDEF = vaddw_s8(vsum89ABCDEF, vi5x89ABCDEF);
    vsum01234567 = vaddw_s8(vsum01234567, vi6x01234567);
    vsum89ABCDEF = vaddw_s8(vsum89ABCDEF, vi6x89ABCDEF);

    const int32x4_t vacc0123 = vaddw_s16(vinit_bias, vget_low_s16(vsum01234567));
    const int32x4_t vacc4567 = vaddw_s16(vinit_bias, vget_high_s16(vsum01234567));
    const int32x4_t vacc89AB = vaddw_s16(vinit_bias, vget_low_s16(vsum89ABCDEF));
    const int32x4_t vaccCDEF = vaddw_s16(vinit_bias, vget_high_s16(vsum89ABCDEF));

    vst1q_s32(b, vacc0123); b += 4;
    vst1q_s32(b, vacc4567); b += 4;
    vst1q_s32(b, vacc89AB); b += 4;
    vst1q_s32(b, vaccCDEF); b += 4;
  }

  for (rows -= 7; rows > 7; rows -= 7) {
    i0 = (const int8_t*) ((uintptr_t) i0 + input_increment);
    i1 = (const int8_t*) ((uintptr_t) i1 + input_increment);
    i2 = (const int8_t*) ((uintptr_t) i2 + input_increment);
    i3 = (const int8_t*) ((uintptr_t) i3 + input_increment);
    i4 = (const int8_t*) ((uintptr_t) i4 + input_increment);
    i5 = (const int8_t*) ((uintptr_t) i5 + input_increment);
    i6 = (const int8_t*) ((uintptr_t) i6 + input_increment);

    int32_t* b = buffer;
    size_t c = channels;
    for (; c != 0; c = doz(c, 16)) {
      const int8x8_t vi0x01234567 = vld1_s8(i0); i0 += 8;
      const int8x8_t vi0x89ABCDEF = vld1_s8(i0); i0 += 8;
      const int8x8_t vi1x01234567 = vld1_s8(i1); i1 += 8;
      const int8x8_t vi1x89ABCDEF = vld1_s8(i1); i1 += 8;

      const int8x8_t vi2x01234567 = vld1_s8(i2); i2 += 8;
      int16x8_t vsum01234567 = vaddl_s8(vi0x01234567, vi1x01234567);
      const int8x8_t vi2x89ABCDEF = vld1_s8(i2); i2 += 8;
      int16x8_t vsum89ABCDEF = vaddl_s8(vi0x89ABCDEF, vi1x89ABCDEF);

      const int8x8_t vi3x01234567 = vld1_s8(i3); i3 += 8;
      vsum01234567 = vaddw_s8(vsum01234567, vi2x01234567);
      const int8x8_t vi3x89ABCDEF = vld1_s8(i3); i3 += 8;
      vsum89ABCDEF = vaddw_s8(vsum89ABCDEF, vi2x89ABCDEF);
      const int8x8_t vi4x01234567 = vld1_s8(i4); i4 += 8;
      vsum01234567 = vaddw_s8(vsum01234567, vi3x01234567);
      const int8x8_t vi4x89ABCDEF = vld1_s8(i4); i4 += 8;
      vsum89ABCDEF = vaddw_s8(vsum89ABCDEF, vi3x89ABCDEF);
      const int8x8_t vi5x01234567 = vld1_s8(i5); i5 += 8;
      vsum01234567 = vaddw_s8(vsum01234567, vi4x01234567);
      const int8x8_t vi5x89ABCDEF = vld1_s8(i5); i5 += 8;
      vsum89ABCDEF = vaddw_s8(vsum89ABCDEF, vi4x89ABCDEF);
      const int8x8_t vi6x01234567 = vld1_s8(i6); i6 += 8;
      vsum01234567 = vaddw_s8(vsum01234567, vi5x01234567);
      const int8x8_t vi6x89ABCDEF = vld1_s8(i6); i6 += 8;
      vsum89ABCDEF = vaddw_s8(vsum89ABCDEF, vi5x89ABCDEF);
      int32x4_t vacc0123 = vld1q_s32(b);
      int32x4_t vacc4567 = vld1q_s32(b + 4);
      vsum01234567 = vaddw_s8(vsum01234567, vi6x01234567);
      int32x4_t vacc89AB = vld1q_s32(b + 8);
      int32x4_t vaccCDEF = vld1q_s32(b + 12);
      vsum89ABCDEF = vaddw_s8(vsum89ABCDEF, vi6x89ABCDEF);

      vacc0123 = vaddw_s16(vacc0123, vget_low_s16(vsum01234567));
      vacc4567 = vaddw_s16(vacc4567, vget_high_s16(vsum01234567));
      vacc89AB = vaddw_s16(vacc89AB, vget_low_s16(vsum89ABCDEF));
      vaccCDEF = vaddw_s16(vaccCDEF, vget_high_s16(vsum89ABCDEF));

      vst1q_s32(b, vacc0123); b += 4;
      vst1q_s32(b, vacc4567); b += 4;
      vst1q_s32(b, vacc89AB); b += 4;
      vst1q_s32(b, vaccCDEF); b += 4;
    }
  }

  i0 = (const int8_t*) ((uintptr_t) i0 + input_increment);
  i1 = (const int8_t*) ((uintptr_t) i1 + input_increment);
  if XNN_UNPREDICTABLE(rows < 2) {
    i1 = zero;
  }
  i2 = (const int8_t*) ((uintptr_t) i2 + input_increment);
  if XNN_UNPREDICTABLE(rows <= 2) {
    i2 = zero;
  }
  i3 = (const int8_t*) ((uintptr_t) i3 + input_increment);
  if XNN_UNPREDICTABLE(rows < 4) {
    i3 = zero;
  }
  i4 = (const int8_t*) ((uintptr_t) i4 + input_increment);
  if XNN_UNPREDICTABLE(rows <= 4) {
    i4 = zero;
  }
  i5 = (const int8_t*) ((uintptr_t) i5 + input_increment);
  if XNN_UNPREDICTABLE(rows < 6) {
    i5 = zero;
  }
  i6 = (const int8_t*) ((uintptr_t) i6 + input_increment);
  if XNN_UNPREDICTABLE(rows <= 6) {
    i6 = zero;
  }

  const int32x4_t vleft_pre_shift = vld1q_dup_s32(&params->rndnu_neon.left_pre_shift);
  const int32x4_t vmultiplier = vld1q_dup_s32(&params->rndnu_neon.multiplier);
  const int32x4_t vleft_post_shift = vld1q_dup_s32(&params->rndnu_neon.left_post_shift);
  const int16x8_t voutput_zero_point = vld1q_dup_s16(&params->rndnu_neon.output_zero_point);
  const int8x16_t voutput_min = vld1q_dup_s8(&params->rndnu_neon.output_min);
  const int8x16_t voutput_max = vld1q_dup_s8(&params->rndnu_neon.output_max);
  for (; channels >= 16; channels -= 16) {
    const int8x8_t vi0x01234567 = vld1_s8(i0); i0 += 8;
    const int8x8_t vi0x89ABCDEF = vld1_s8(i0); i0 += 8;
    const int8x8_t vi1x01234567 = vld1_s8(i1); i1 += 8;
    const int8x8_t vi1x89ABCDEF = vld1_s8(i1); i1 += 8;

    const int8x8_t vi2x01234567 = vld1_s8(i2); i2 += 8;
    int16x8_t vsum01234567 = vaddl_s8(vi0x01234567, vi1x01234567);
    const int8x8_t vi2x89ABCDEF = vld1_s8(i2); i2 += 8;
    int16x8_t vsum89ABCDEF = vaddl_s8(vi0x89ABCDEF, vi1x89ABCDEF);

    const int8x8_t vi3x01234567 = vld1_s8(i3); i3 += 8;
    vsum01234567 = vaddw_s8(vsum01234567, vi2x01234567);
    const int8x8_t vi3x89ABCDEF = vld1_s8(i3); i3 += 8;
    vsum89ABCDEF = vaddw_s8(vsum89ABCDEF, vi2x89ABCDEF);
    const int8x8_t vi4x01234567 = vld1_s8(i4); i4 += 8;
    vsum01234567 = vaddw_s8(vsum01234567, vi3x01234567);
    const int8x8_t vi4x89ABCDEF = vld1_s8(i4); i4 += 8;
    vsum89ABCDEF = vaddw_s8(vsum89ABCDEF, vi3x89ABCDEF);
    const int8x8_t vi5x01234567 = vld1_s8(i5); i5 += 8;
    vsum01234567 = vaddw_s8(vsum01234567, vi4x01234567);
    const int8x8_t vi5x89ABCDEF = vld1_s8(i5); i5 += 8;
    vsum89ABCDEF = vaddw_s8(vsum89ABCDEF, vi4x89ABCDEF);
    const int8x8_t vi6x01234567 = vld1_s8(i6); i6 += 8;
    vsum01234567 = vaddw_s8(vsum01234567, vi5x01234567);
    const int8x8_t vi6x89ABCDEF = vld1_s8(i6); i6 += 8;
    vsum89ABCDEF = vaddw_s8(vsum89ABCDEF, vi5x89ABCDEF);
    int32x4_t vacc0123 = vld1q_s32(buffer); buffer += 4;
    int32x4_t vacc4567 = vld1q_s32(buffer); buffer += 4;
    vsum01234567 = vaddw_s8(vsum01234567, vi6x01234567);
    int32x4_t vacc89AB = vld1q_s32(buffer); buffer += 4;
    int32x4_t vaccCDEF = vld1q_s32(buffer); buffer += 4;
    vsum89ABCDEF = vaddw_s8(vsum89ABCDEF, vi6x89ABCDEF);

    vacc0123 = vaddw_s16(vacc0123, vget_low_s16(vsum01234567));
    vacc4567 = vaddw_s16(vacc4567, vget_high_s16(vsum01234567));
    vacc89AB = vaddw_s16(vacc89AB, vget_low_s16(vsum89ABCDEF));
    vaccCDEF = vaddw_s16(vaccCDEF, vget_high_s16(vsum89ABCDEF));

    vacc0123 = vqshlq_s32(vacc0123, vleft_pre_shift);
    vacc4567 = vqshlq_s32(vacc4567, vleft_pre_shift);
    vacc89AB = vqshlq_s32(vacc89AB, vleft_pre_shift);
    vaccCDEF = vqshlq_s32(vaccCDEF, vleft_pre_shift);

    vacc0123 = vqdmulhq_s32(vacc0123, vmultiplier);
    vacc4567 = vqdmulhq_s32(vacc4567, vmultiplier);
    vacc89AB = vqdmulhq_s32(vacc89AB, vmultiplier);
    vaccCDEF = vqdmulhq_s32(vaccCDEF, vmultiplier);

    vacc0123 = vrshlq_s32(vacc0123, vleft_post_shift);
    vacc4567 = vrshlq_s32(vacc4567, vleft_post_shift);
    vacc89AB = vrshlq_s32(vacc89AB, vleft_post_shift);
    vaccCDEF = vrshlq_s32(vaccCDEF, vleft_post_shift);

    #if XNN_ARCH_ARM64
      int16x8_t vacc01234567 = vqmovn_high_s32(vqmovn_s32(vacc0123), vacc4567);
      int16x8_t vacc89ABCDEF = vqmovn_high_s32(vqmovn_s32(vacc89AB), vaccCDEF);
    #else  // !XNN_ARCH_ARM64
      int16x8_t vacc01234567 = vcombine_s16(vqmovn_s32(vacc0123), vqmovn_s32(vacc4567));
      int16x8_t vacc89ABCDEF = vcombine_s16(vqmovn_s32(vacc89AB), vqmovn_s32(vaccCDEF));
    #endif  // !XNN_ARCH_ARM64

    vacc01234567 = vqaddq_s16(vacc01234567, voutput_zero_point);
    vacc89ABCDEF = vqaddq_s16(vacc89ABCDEF, voutput_zero_point);

    #if XNN_ARCH_ARM64
      int8x16_t vout0123456789ABCDEF = vqmovn_high_s16(vqmovn_s16(vacc01234567), vacc89ABCDEF);
    #else  // !XNN_ARCH_ARM64
      int8x16_t vout0123456789ABCDEF = vcombine_s8(vqmovn_s16(vacc01234567), vqmovn_s16(vacc89ABCDEF));
    #endif  // !XNN_ARCH_ARM64

    vout0123456789ABCDEF = vmaxq_s8(vout0123456789ABCDEF, voutput_min);

    vout0123456789ABCDEF = vminq_s8(vout0123456789ABCDEF, voutput_max);

    vst1q_s8(output, vout0123456789ABCDEF); output += 16;
  }
  if XNN_UNLIKELY(channels != 0) {
    do {
      const int8x8_t vi0x01234567 = vld1_s8(i0); i0 += 8;
      const int8x8_t vi1x01234567 = vld1_s8(i1); i1 += 8;
      const int8x8_t vi2x01234567 = vld1_s8(i2); i2 += 8;
      int16x8_t vsum01234567 = vaddl_s8(vi0x01234567, vi1x01234567);

      const int8x8_t vi3x01234567 = vld1_s8(i3); i3 += 8;
      vsum01234567 = vaddw_s8(vsum01234567, vi2x01234567);
      const int8x8_t vi4x01234567 = vld1_s8(i4); i4 += 8;
      vsum01234567 = vaddw_s8(vsum01234567, vi3x01234567);
      const int8x8_t vi5x01234567 = vld1_s8(i5); i5 += 8;
      vsum01234567 = vaddw_s8(vsum01234567, vi4x01234567);
      const int8x8_t vi6x01234567 = vld1_s8(i6); i6 += 8;
      vsum01234567 = vaddw_s8(vsum01234567, vi5x01234567);
      int32x4_t vacc0123 = vld1q_s32(buffer); buffer += 4;
      int32x4_t vacc4567 = vld1q_s32(buffer); buffer += 4;
      vsum01234567 = vaddw_s8(vsum01234567, vi6x01234567);

      vacc0123 = vaddw_s16(vacc0123, vget_low_s16(vsum01234567));
      vacc4567 = vaddw_s16(vacc4567, vget_high_s16(vsum01234567));

      vacc0123 = vqshlq_s32(vacc0123, vleft_pre_shift);
      vacc4567 = vqshlq_s32(vacc4567, vleft_pre_shift);

      vacc0123 = vqdmulhq_s32(vacc0123, vmultiplier);
      vacc4567 = vqdmulhq_s32(vacc4567, vmultiplier);

      vacc0123 = vrshlq_s32(vacc0123, vleft_post_shift);
      vacc4567 = vrshlq_s32(vacc4567, vleft_post_shift);

      #if XNN_ARCH_ARM64
        int16x8_t vacc01234567 = vqmovn_high_s32(vqmovn_s32(vacc0123), vacc4567);
      #else
        int16x8_t vacc01234567 = vcombine_s16(vqmovn_s32(vacc0123), vqmovn_s32(vacc4567));
      #endif
      vacc01234567 = vqaddq_s16(vacc01234567, voutput_zero_point);

      int8x8_t vout01234567 = vqmovn_s16(vacc01234567);
      vout01234567 = vmax_s8(vout01234567, vget_low_s8(voutput_min));
      vout01234567 = vmin_s8(vout01234567, vget_low_s8(voutput_max));

      if XNN_LIKELY(channels >= 8) {
        vst1_s8(output, vout01234567); output += 8;
        channels -= 8;
      } else {
        if (channels & 4) {
          vst1_lane_u32((void*) output, vreinterpret_u32_s8(vout01234567), 0); output += 4;
          vout01234567 = vext_s8(vout01234567, vout01234567, 4);
        }
        if (channels & 2) {
          vst1_lane_u16((void*) output, vreinterpret_u16_s8(vout01234567), 0); output += 2;
          vout01234567 = vext_s8(vout01234567, vout01234567, 2);
        }
        if (channels & 1) {
          vst1_lane_s8(output, vout01234567, 0); output += 1;
        }
        channels = 0;
      }
    } while (channels != 0);
  }
}
