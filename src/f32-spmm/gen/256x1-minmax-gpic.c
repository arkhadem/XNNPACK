// Auto-generated file. Do not edit!
//   Template: src/f32-spmm/sse.c.in
//   Generator: tools/xngen
//
// Copyright 2019 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#define GPIC_RUN

#ifdef GPIC_RUN
#include <gpic.h>
#endif
#include <stdio.h>
 
#include <xnnpack/spmm.h>

void xnn_f32_spmm_minmax_ukernel_256x1__gpic(
    size_t mc,
    size_t nc,
    const float*restrict input,
    const float*restrict weights,
    const int32_t*restrict widx_dmap,
    const uint32_t*restrict nidx_nnzmap,
    float*restrict output,
    size_t output_stride,
    const union xnn_f32_minmax_params params[restrict XNN_MIN_ELEMENTS(1)])
{
  assert(mc != 0);
  assert(mc % sizeof(float) == 0);
  assert(nc != 0);

  int mc_int = (int)mc;
  int nc_int = (int)nc;

#ifdef GPIC_RUN
  char graph_name[100]; 
  sprintf(graph_name, "xnn_f32_spmm_minmax_ukernel_256x1__gpic_MC%d_NC%d", (int)(mc_int/sizeof(float)), (int)nc_int);
  gpic_initializer(graph_name);
#endif
  
  int output_decrement = output_stride * nc_int - 256 * sizeof(float);
#ifndef GPIC_RUN
  int _pc_load_f_1 = 0;
  int _pc_load_f_2 = 0;
  int _pc_load1_f_1 = 0;
  int _pc_load_f_3 = 0;
  int _pc_load1_f_2 = 0;
  int _pc_add_f_1 = 0;
  int _pc_mul_f_1 = 0;
  int _pc_min_f_1 = 0;
  int _pc_max_f_1 = 0;
  int _pc_store_f_1 = 0;
#endif

  while XNN_LIKELY(mc_int > 0) {
    const float*restrict w = weights;
    const int32_t* dmap = widx_dmap;
    const uint32_t* nnzmap = nidx_nnzmap;
    int n = nc_int;
    int itr_cnt = (256 < (mc_int / sizeof(float))) ? 256 : (mc_int / sizeof(float));
    do {
      uint32_t nnz = *nnzmap++;
#ifdef GPIC_RUN
      __pcf vacc0123 = _pc_load1_f(w, itr_cnt); w += 1;
#else
      _pc_load1_f_1 += 1;
#endif
      if XNN_LIKELY(nnz != 0) {
        do {
          const intptr_t diff = *dmap++;
#ifdef GPIC_RUN
          const __pcf vi0123 = _pc_load_f(input, itr_cnt);
#else
          _pc_load_f_3 += 1;
#endif          
          input = (const float*restrict) ((uintptr_t) input + (uintptr_t) diff);
#ifdef GPIC_RUN
          const __pcf vw = _pc_load1_f(w, itr_cnt); w += 1;
          vacc0123 = _pc_add_f(vacc0123, _pc_mul_f(vi0123, vw));
#else
          _pc_load1_f_2 += 1;
          _pc_add_f_1 += 1;
          _pc_mul_f_1 += 1;
#endif          
        } while (--nnz != 0);
      }
#ifdef GPIC_RUN
      const __pcf vmin = _pc_load_f(params->sse.min, 0);
      const __pcf vmax = _pc_load_f(params->sse.max, 0);
      __pcf vout0123 = _pc_min_f(vacc0123, vmax);
      vout0123 = _pc_max_f(vout0123, vmin);
      _pc_store_f(output, vout0123);
      gpic_flusher();
#else
      _pc_load_f_1 += 1;
      _pc_load_f_2 += 1;
      _pc_min_f_1 += 1;
      _pc_max_f_1 += 1;
      _pc_store_f_1 += 1;
#endif      
      output = (float*restrict) ((uintptr_t) output + output_stride);
    } while (--n != 0);
    output = (float*restrict) ((uintptr_t) output - output_decrement);
    input += 256;
    mc_int = (0 < (mc_int - 256 * sizeof(float))) ? (mc_int - 256 * sizeof(float)) : 0;
  }
#ifdef GPIC_RUN
  gpic_finisher();
#else 
  printf("mc: %d nc: %d _pc_load_f_1: %d _pc_load_f_2: %d _pc_load1_f_1: %d _pc_load_f_3: %d _pc_load1_f_2: %d _pc_add_f_1: %d _pc_mul_f_1: %d _pc_min_f_1: %d _pc_max_f_1: %d _pc_store_f_1:%d\n", (int)(mc_int/sizeof(float)), (int)nc_int, _pc_load_f_1, _pc_load_f_2, _pc_load1_f_1, _pc_load_f_3, _pc_load1_f_2, _pc_add_f_1, _pc_mul_f_1, _pc_min_f_1, _pc_max_f_1, _pc_store_f_1);
#endif
}