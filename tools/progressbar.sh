#!/bin/bash

#
# progressbar.sh
# Created: 2021-03-20, 12:03:19.
# Copyright (C) 2021, Kirill GPRB.
# 
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#

function progressbar {
    message=$1
    current=$2
    maximum=$3

    cols=$(tput cols)
    num_grades=$(($cols / 3))

    progress=""

    count=$(($num_grades * $current / $maximum))
    progress="$progress["
    progress="$progress`printf '%*s' $count | tr ' ' '#'`"
    progress="$progress`printf '%*s' $(($num_grades - $count)) | tr ' ' '-'`"
    progress="$progress]"

    percent=$((100 * $current / $maximum))
    progress="$progress `printf %3d%% $percent`"

    printf "\r %s%*s" "$message" $(($cols - ${#message} - 2)) "$progress"
    if (( $current == $maximum ))
    then
        printf "\n"
    fi
}
