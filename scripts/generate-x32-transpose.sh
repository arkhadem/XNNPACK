#!/bin/sh
# Copyright 2021 Google LLC
#
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree.

#################################### Scalar ###################################
tools/xngen src/x32-transpose/scalar.c.in -D TILE_HEIGHT=1 TILE_WIDTH=2 TYPE=int SIZE=32 -o src/x32-transpose/gen/1x2-scalar-int.c &
tools/xngen src/x32-transpose/scalar.c.in -D TILE_HEIGHT=1 TILE_WIDTH=4 TYPE=int SIZE=32 -o src/x32-transpose/gen/1x4-scalar-int.c &
tools/xngen src/x32-transpose/scalar.c.in -D TILE_HEIGHT=2 TILE_WIDTH=1 TYPE=int SIZE=32 -o src/x32-transpose/gen/2x1-scalar-int.c &
tools/xngen src/x32-transpose/scalar.c.in -D TILE_HEIGHT=2 TILE_WIDTH=2 TYPE=int SIZE=32 -o src/x32-transpose/gen/2x2-scalar-int.c &
tools/xngen src/x32-transpose/scalar.c.in -D TILE_HEIGHT=2 TILE_WIDTH=4 TYPE=int SIZE=32 -o src/x32-transpose/gen/2x4-scalar-int.c &
tools/xngen src/x32-transpose/scalar.c.in -D TILE_HEIGHT=4 TILE_WIDTH=1 TYPE=int SIZE=32 -o src/x32-transpose/gen/4x1-scalar-int.c &
tools/xngen src/x32-transpose/scalar.c.in -D TILE_HEIGHT=4 TILE_WIDTH=2 TYPE=int SIZE=32 -o src/x32-transpose/gen/4x2-scalar-int.c &
tools/xngen src/x32-transpose/scalar.c.in -D TILE_HEIGHT=4 TILE_WIDTH=4 TYPE=int SIZE=32 -o src/x32-transpose/gen/4x4-scalar-int.c &
tools/xngen src/x32-transpose/scalar.c.in -D TILE_HEIGHT=1 TILE_WIDTH=2 TYPE=float SIZE=32 -o src/x32-transpose/gen/1x2-scalar-float.c &
tools/xngen src/x32-transpose/scalar.c.in -D TILE_HEIGHT=1 TILE_WIDTH=4 TYPE=float SIZE=32 -o src/x32-transpose/gen/1x4-scalar-float.c &
tools/xngen src/x32-transpose/scalar.c.in -D TILE_HEIGHT=2 TILE_WIDTH=1 TYPE=float SIZE=32 -o src/x32-transpose/gen/2x1-scalar-float.c &
tools/xngen src/x32-transpose/scalar.c.in -D TILE_HEIGHT=2 TILE_WIDTH=2 TYPE=float SIZE=32 -o src/x32-transpose/gen/2x2-scalar-float.c &
tools/xngen src/x32-transpose/scalar.c.in -D TILE_HEIGHT=2 TILE_WIDTH=4 TYPE=float SIZE=32 -o src/x32-transpose/gen/2x4-scalar-float.c &
tools/xngen src/x32-transpose/scalar.c.in -D TILE_HEIGHT=4 TILE_WIDTH=1 TYPE=float SIZE=32 -o src/x32-transpose/gen/4x1-scalar-float.c &
tools/xngen src/x32-transpose/scalar.c.in -D TILE_HEIGHT=4 TILE_WIDTH=2 TYPE=float SIZE=32 -o src/x32-transpose/gen/4x2-scalar-float.c &
tools/xngen src/x32-transpose/scalar.c.in -D TILE_HEIGHT=4 TILE_WIDTH=4 TYPE=float SIZE=32 -o src/x32-transpose/gen/4x4-scalar-float.c &

#################################### SSE2 ###################################
tools/xngen src/x32-transpose/sse2.c.in -D IN_PTRS=REUSE OUT_PTRS=DEC SIZE=32 -o src/x32-transpose/gen/4x4-reuse-dec-sse2.c &
tools/xngen src/x32-transpose/sse2.c.in -D IN_PTRS=REUSE OUT_PTRS=SWITCH SIZE=32 -o src/x32-transpose/gen/4x4-reuse-switch-sse2.c &
tools/xngen src/x32-transpose/sse2.c.in -D IN_PTRS=REUSE OUT_PTRS=MULTI SIZE=32 -o src/x32-transpose/gen/4x4-reuse-multi-sse2.c &
tools/xngen src/x32-transpose/sse2.c.in -D IN_PTRS=MULTI OUT_PTRS=SWITCH SIZE=32 -o src/x32-transpose/gen/4x4-multi-switch-sse2.c &
tools/xngen src/x32-transpose/sse2.c.in -D IN_PTRS=MULTI OUT_PTRS=MULTI SIZE=32 -o src/x32-transpose/gen/4x4-multi-multi-sse2.c &
tools/xngen src/x32-transpose/sse2.c.in -D IN_PTRS=MULTI OUT_PTRS=DEC SIZE=32 -o src/x32-transpose/gen/4x4-multi-dec-sse2.c &

#################################### ARM NEON ###############################
tools/xngen src/x32-transpose/neon-zip.c.in -D SIZE=32 ARCH=neon -o src/x32-transpose/gen/4x4-neon-zip.c &

################################## Unit tests #################################
tools/generate-transpose-test.py --spec test/x32-transpose.yaml --output=test/x32-transpose.cc &

wait
