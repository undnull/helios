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

# if you don't want to install the whole vulkan sdk, just download
# the latest glslangValidator and spirv-cross builds and place them in
# the directory where this script is (tools), then run the script:
# it should work like a champ.
# https://github.com/KhronosGroup/glslang/releases/tag/master-tot
# https://github.com/KhronosGroup/SPIRV-Cross/releases/
PATH=$PATH:"$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

source progressbar.sh || exit 1

sys_builddir="$PWD/build/shaders"

opt_manifest=""
opt_spirvdir=""
opt_rebuild=false

while getopts "m:o:rh" opt
do
    if [[ "$opt" == "m" ]]
    then
        opt_manifest="$opt_manifest $OPTARG"
        continue
    fi

    if [[ "$opt" == "o" ]]
    then
        opt_spirvdir="$OPTARG"
        continue
    fi

    if [[ "$opt" == "r" ]]
    then
        opt_rebuild=true
        continue
    fi

    >&2 echo "usage: $0 [-m <path>] [-o <path>] [-r] [-h]"
    >&2 echo "example: $0 -r -o assets/shaders"
    >&2 echo "options:"
    >&2 echo "  -m <path>   : add the manifest file"
    >&2 echo "  -o <path>   : set the output directory"
    >&2 echo "  -r          : force rebuild"
    >&2 echo "  -h          : print this message and exit"
    exit 1
done

if [[ -z "$opt_manifest" ]]
then
    opt_manifest="shaders/00_shaders.txt"
    >&2 echo "opt_manifest not set, defaulting to $opt_manifest"
    if [[ ! -f "$PWD/$opt_manifest" ]]
    then
        >&2 echo "fatal: file $opt_manifest doesn't exist"
        exit 1
    fi
fi

if [[ -z "$opt_spirvdir" ]]
then
    opt_spirvdir="assets/shaders"
    >&2 echo "opt_spirvdir not set, defaulting to $opt_spirvdir"
fi

opt_spirvdir="$PWD/$opt_spirvdir"
sys_builddir="$sys_builddir/$(echo $opt_spirvdir | md5sum | awk '{print $1}')"

mkdir -p "$sys_builddir"
mkdir -p "$opt_spirvdir"

for manifest in $opt_manifest
do
    if [[ -f "$PWD/$manifest" ]]
    then
        >&2 echo "building shaders from $manifest"
        manifestdir=$(dirname "$PWD/$manifest")
        while IFS=$' \t\r\n' read -r srcfile
        do
            if [[ -f "$manifestdir/$srcfile" ]]
            then
                manifestbase=$(basename "$manifest")
                pmessage="build ${manifestbase%.*}::$srcfile"

                >&2 progressbar "$pmessage" 0 6

                xspv=$(basename "$srcfile" .hlsl)

                spirvbase=$(basename "$opt_spirvdir")

                md5c=$(md5sum "$manifestdir/$srcfile" | awk '{print $1}')
                md5o=$(cat "$sys_builddir/$xspv.md5" 2> /dev/null)

                >&2 progressbar "$pmessage" 1 6

                if [[ "$md5c" == "$md5o" ]] && [[ $opt_rebuild == false ]]
                then
                    >&2 progressbar "$pmessage" 6 6
                    continue
                else
                    truncate -s 0 "$sys_builddir/$xspv.md5"

                    >&2 progressbar "$pmessage" 2 6
                    eout=$(glslangValidator --quiet -V --hlsl-dx9-compatible -e main -o "$sys_builddir/$xspv.spv" "$manifestdir/$srcfile")
                    if (( $? != 0 ))
                    then
                        >&2 printf "\n$eout\n"
                        continue
                    fi

                    >&2 progressbar "$pmessage" 3 6
                    eout=$(spirv-cross "$sys_builddir/$xspv.spv" > "$sys_builddir/$xspv.glsl")
                    if (( $? != 0 ))
                    then
                        >&2 printf "\n$eout\n"
                        continue
                    fi

                    >&2 progressbar "$pmessage" 4 6
                    eout=$(glslangValidator --quiet -G -e main -o "$opt_spirvdir/$xspv.spv" "$sys_builddir/$xspv.glsl")
                    if (( $? != 0 ))
                    then
                        >&2 printf "\n$eout\n"
                        continue
                    fi

                    >&2 progressbar "$pmessage" 5 6
                    echo "$md5c" > "$sys_builddir/$xspv.md5"
                    
                    >&2 progressbar "$pmessage" 6 6
                fi
            fi
        done < "$PWD/$manifest"
    fi
done
exit 0
