/*
 * sprite.frag.hlsl
 * Created: 2021-03-08, 22:59:26.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

struct ps_input {
    float2 texcoord : TEXCOORD0;
};

sampler2D color : register(S0);

float4 main(ps_input input) : SV_Target
{
    return tex2D(color, input.texcoord);
}
