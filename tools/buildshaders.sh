#!/bin/bash

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
    echo "$0: fatal: $hlsl_dir doesn't exist"
    exit 1
fi

sources=$(find "$hlsl_dir" -name *.hlsl)
if [[ -z "$sources" ]]
then
    echo "$0: fatal: no shaders found in $hlsl_dir/src/"
    exit 1
fi

for src in $sources
do
    xspv=$(basename "$src" .hlsl)
    progressbar "Building $xspv.hlsl" 1 4
    glslangValidator --quiet -V --hlsl-dx9-compatible -e main -o "$build_dir/$xspv.spv" "$src"
    progressbar "Building $xspv.hlsl" 2 4
    spirv-cross "$build_dir/$xspv.spv" > "$build_dir/$xspv.glsl"
    progressbar "Building $xspv.hlsl" 3 4
    glslangValidator --quiet -G -e main -o "$spirv_dir/$xspv.spv" "$build_dir/$xspv.glsl"
    progressbar "Building $xspv.hlsl" 4 4
done
exit 0
