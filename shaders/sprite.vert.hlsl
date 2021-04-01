/*
 * sprite.vert.hlsl
 * Created: 2021-03-08, 22:41:30.
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
    int instance_id : SV_InstanceID;
};

struct vs_output {
    float4 position : SV_Position;
    float2 texcoord : TEXCOORD0;
};

cbuffer ubo : register(B0) {
    row_major float4x4 projection;
    row_major float4x4 scale;
    row_major float4x4 view;
};

row_major StructuredBuffer<float4x4> ssbo : register(U0);

vs_output main(vs_input input)
{
    vs_output output;

    output.position = float4(input.position, 0.0, 1.0);
    output.position = mul(output.position, scale);
    output.position = mul(output.position, ssbo[input.instance_id]);
    output.position = mul(output.position, view);
    output.position = mul(output.position, projection);

    output.texcoord = input.texcoord;

    return output;
}
