/*
 * blit.vert.hlsl
 * Created: 2021-03-30, 12:26:42.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

struct vs_input {
    float2 position : POSITION;
    float2 texcoord : TEXCOORD1;
};

struct vs_output {
    float4 position : SV_Position;
    float2 texcoord : TEXCOORD0;
};

vs_output main(vs_input input)
{
    vs_output output;
    output.position = float4(input.position, 0.0, 1.0);
    output.texcoord = input.texcoord;
    return output;
}
