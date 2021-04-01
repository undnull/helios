/*
 * background.vert.hlsl
 * Created: 2021-03-24, 23:02:34.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

struct vs_input {
    float2 position : POSITION;
    float2 texcoord : TEXCOORD1;
};

struct vs_output {
    float4 position : SV_Position;
    float2 texcoord : TEXCOORD0;
};

cbuffer ubo0 : register(B0) {
    row_major float4x4 projection;
    row_major float4x4 scale;
    float2 target_size;
    float2 view_position;
    float view_rotation;
    float view_zoom;
};

cbuffer ubo1 : register(B1) {
    float2 texture_size;
    float2 scroll_factor;
    bool fit;
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

    if(!fit) {
        float2 scale = texture_size / target_size;
        scale.y *= aspect_fix;
        output.texcoord /= scale;
    }

    return output;
}
