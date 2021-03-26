/*
 * background.vert.hlsl
 * Created: 2021-03-24, 23:02:34.
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

cbuffer ubo : register(B0) {
    row_major float4x4 projection;
    row_major float4x4 scale;
    float2 target_size;
    float2 texture_size;
    float2 scroll_factor;
    float2 view_position;
    float view_rotation;
    float view_zoom;
};

vs_output main(vs_input input)
{
    vs_output output;

    output.position = float4(input.position, 0.0, 1.0);
    output.position = mul(output.position, scale);
    output.position = mul(output.position, projection);

    float texture_aspect = texture_size.x / texture_size.y;
    float target_aspect = target_size.x / target_size.y;
    float aspect_fix = texture_aspect / target_aspect;

    float s = sin(view_rotation);
    float c = cos(view_rotation);

    output.texcoord = input.texcoord;

    output.texcoord.y *= aspect_fix;
    output.texcoord.y -= aspect_fix * 0.5 - 0.5;

    output.texcoord -= 0.5;

    output.texcoord.x *= texture_aspect;
    output.texcoord = mul(output.texcoord, float2x2(c, -s, s, c));
    output.texcoord.x /= texture_aspect;

    output.texcoord *= view_zoom;
    output.texcoord -= view_position * scroll_factor * 0.001;

    output.texcoord += 0.5;

    return output;
}
