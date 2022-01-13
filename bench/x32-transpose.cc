// Copyright 2021 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <xnnpack/AlignedAllocator.h>
#include <xnnpack/common.h>
#include <xnnpack/params.h>
#include <xnnpack/transpose.h>

#include <algorithm>
#include <cmath>
#include <functional>
#include <random>
#include <vector>

#include "bench/utils.h"
#include <benchmark/benchmark.h>

static void x32_transpose(
    benchmark::State& state,
    xnn_x32_transpose_ukernel_function transpose,
    size_t ukernel_size,
    benchmark::utils::IsaCheckFunction isa_check = nullptr) {
  if (isa_check && !isa_check(state)) {
    return;
  }

  std::random_device random_device;
  auto rng = std::mt19937(random_device());
  auto u32rng = std::bind(std::uniform_int_distribution<uint32_t>(), rng);
  const size_t ukernel_bytes = ukernel_size * sizeof(uint32_t);

  std::vector<uint32_t, AlignedAllocator<uint32_t, 64>> x(
      ukernel_size * ukernel_size + XNN_EXTRA_BYTES / sizeof(uint32_t));
  std::vector<uint32_t, AlignedAllocator<uint32_t, 64>> y(
      ukernel_size * ukernel_size + XNN_EXTRA_BYTES / sizeof(uint32_t));
  std::generate(x.begin(), x.end(), std::ref(u32rng));
  std::fill(y.begin(), y.end(), 0);

  for (auto _ : state) {
    transpose(x.data(), y.data(), ukernel_bytes, ukernel_bytes, ukernel_size,
              ukernel_size);
  }

  const uint64_t cpu_frequency = benchmark::utils::GetCurrentCpuFrequency();
  if (cpu_frequency != 0) {
    state.counters["cpufreq"] = cpu_frequency;
  }
}

BENCHMARK_CAPTURE(x32_transpose, scalar_int_32_1x2, xnn_x32_transpose_ukernel__1x2_scalar_int, 32)
    ->UseRealTime();
BENCHMARK_CAPTURE(x32_transpose, scalar_int_32_1x4, xnn_x32_transpose_ukernel__1x4_scalar_int, 32)
    ->UseRealTime();
BENCHMARK_CAPTURE(x32_transpose, scalar_int_32_2x1, xnn_x32_transpose_ukernel__2x1_scalar_int, 32)
    ->UseRealTime();
BENCHMARK_CAPTURE(x32_transpose, scalar_int_32_2x2, xnn_x32_transpose_ukernel__2x2_scalar_int, 32)
    ->UseRealTime();
BENCHMARK_CAPTURE(x32_transpose, scalar_int_32_2x4, xnn_x32_transpose_ukernel__2x4_scalar_int, 32)
    ->UseRealTime();
BENCHMARK_CAPTURE(x32_transpose, scalar_int_32_4x1, xnn_x32_transpose_ukernel__4x1_scalar_int, 32)
    ->UseRealTime();
BENCHMARK_CAPTURE(x32_transpose, scalar_int_32_4x2, xnn_x32_transpose_ukernel__4x2_scalar_int, 32)
    ->UseRealTime();
BENCHMARK_CAPTURE(x32_transpose, scalar_int_32_4x4, xnn_x32_transpose_ukernel__4x4_scalar_int, 32)
    ->UseRealTime();
BENCHMARK_CAPTURE(x32_transpose, scalar_float_32_1x2, xnn_x32_transpose_ukernel__1x2_scalar_float, 32)
    ->UseRealTime();
BENCHMARK_CAPTURE(x32_transpose, scalar_float_32_1x4, xnn_x32_transpose_ukernel__1x4_scalar_float, 32)
    ->UseRealTime();
BENCHMARK_CAPTURE(x32_transpose, scalar_float_32_2x1, xnn_x32_transpose_ukernel__2x1_scalar_float, 32)
    ->UseRealTime();
BENCHMARK_CAPTURE(x32_transpose, scalar_float_32_2x2, xnn_x32_transpose_ukernel__2x2_scalar_float, 32)
    ->UseRealTime();
BENCHMARK_CAPTURE(x32_transpose, scalar_float_32_2x4, xnn_x32_transpose_ukernel__2x4_scalar_float, 32)
    ->UseRealTime();
BENCHMARK_CAPTURE(x32_transpose, scalar_float_32_4x1, xnn_x32_transpose_ukernel__4x1_scalar_float, 32)
    ->UseRealTime();
BENCHMARK_CAPTURE(x32_transpose, scalar_float_32_4x2, xnn_x32_transpose_ukernel__4x2_scalar_float, 32)
    ->UseRealTime();
BENCHMARK_CAPTURE(x32_transpose, scalar_float_32_4x4, xnn_x32_transpose_ukernel__4x4_scalar_float, 32)
    ->UseRealTime();

#if XNN_ARCH_ARM || XNN_ARCH_ARM64
  BENCHMARK_CAPTURE(x32_transpose, neon_32_zip, xnn_x32_transpose_ukernel__4x4_neon_zip, 32)
      ->UseRealTime();
  BENCHMARK_CAPTURE(x32_transpose, neon_64_zip, xnn_x32_transpose_ukernel__4x4_neon_zip, 64)
      ->UseRealTime();
  BENCHMARK_CAPTURE(x32_transpose, neon_117_zip, xnn_x32_transpose_ukernel__4x4_neon_zip, 117)
      ->UseRealTime();
#endif  // XNN_ARCH_ARM || XNN_ARCH_ARM64

#if XNN_ARCH_ARM64
  BENCHMARK_CAPTURE(x32_transpose, aarch64_32_tbl, xnn_x32_transpose_ukernel__4x4_aarch64_neon_tbl, 32)
      ->UseRealTime();
  BENCHMARK_CAPTURE(x32_transpose, aarch64_64_tbl, xnn_x32_transpose_ukernel__4x4_aarch64_neon_tbl, 64)
      ->UseRealTime();
  BENCHMARK_CAPTURE(x32_transpose, aarch64_117_tbl, xnn_x32_transpose_ukernel__4x4_aarch64_neon_tbl, 117)
      ->UseRealTime();
#endif  // XNN_ARCH_ARM64

#if XNN_ARCH_X86 || XNN_ARCH_X86_64
  BENCHMARK_CAPTURE(x32_transpose, sse_32, xnn_x32_transpose_ukernel__4x4_sse, 32)
      ->UseRealTime();
  BENCHMARK_CAPTURE(x32_transpose, sse_117, xnn_x32_transpose_ukernel__4x4_sse, 117)
      ->UseRealTime();
  BENCHMARK_CAPTURE(x32_transpose, sse_1024, xnn_x32_transpose_ukernel__4x4_sse, 1024)
      ->UseRealTime();
#endif  // XNN_ARCH_X86 || XNN_ARCH_X86_64

#ifndef XNNPACK_BENCHMARK_NO_MAIN
BENCHMARK_MAIN();
#endif
