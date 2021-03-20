#!/bin/bash

#
# buildshaders.sh
# Created: 2021-03-20, 12:03:30.
# Copyright (C) 2021, Kirill GPRB.
# 
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#

# note: if you don't want to install the whole vulkan sdk, just download
# the latest glslangValidator build and place it in the directory where
# the script is, then run the script: it should work like a champ.
# https://github.com/KhronosGroup/glslang/releases/tag/master-tot
PATH=$PATH:"$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

source progressbar.sh || exit 1

hlsl_dir="$PWD/shaders"
spirv_dir="$PWD/assets/shaders"
build_dir="$PWD/build/shaders"

mkdir -p $spirv_dir
mkdir -p $build_dir

if [[ ! -d "$hlsl_dir" ]]
then
    echo "$0: fatal: directory $hlsl_dir doesn't exist"
    exit 1
fi

sources=$(find "$hlsl_dir" -name *.hlsl)
if [[ -z "$sources" ]]
then
    echo "$0: fatal: no shaders found in $hlsl_dir"
    exit 1
fi

for src in $sources
do
    xspv=$(basename "$src" .hlsl)
    md5_c=$(md5sum "$src" | awk '{ print $1 }')
    md5_o=$(cat "$build_dir/$xspv.md5" 2> /dev/null)
    if [[ "$md5_c" == "$md5_o" ]] && [[ "$1" != "rebuild" ]]
    then
        progressbar "Skip unchanged $xspv.hlsl" 4 4
        continue
    else
        progressbar "Compile $xspv.hlsl" 0 4
        glslangValidator --quiet -V --hlsl-dx9-compatible -e main -o "$build_dir/$xspv.spv" "$src"
        progressbar "Compile $xspv.hlsl" 1 4
        spirv-cross "$build_dir/$xspv.spv" > "$build_dir/$xspv.glsl"
        progressbar "Compile $xspv.hlsl" 2 4
        glslangValidator --quiet -G -e main -o "$spirv_dir/$xspv.spv" "$build_dir/$xspv.glsl"
        progressbar "Compile $xspv.hlsl" 3 4
        echo "$md5_c" > "$build_dir/$xspv.md5"
        progressbar "Compile $xspv.hlsl" 4 4
    fi
done
exit 0
