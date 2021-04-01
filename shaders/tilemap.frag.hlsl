/*
 * tilemap.frag.hlsl
 * Created: 2021-03-24, 15:40:07.
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

struct ps_input {
    float2 texcoord : TEXCOORD0;
};

cbuffer ubo : register(B1) {
    float2 tileset_size;
    float2 tilemap_size;
    float tile_size;
};

sampler2D tileset : register(S0);
sampler2D tilemap : register(S1);

/**
 * Basically what it does is it takes a pixel from a tilemap
 * and then picks a tile from a tileset assigned to the tilemap.
 * So the pixel color (0; 0; M) means that the tile at (0; 0) will be drawn.
 * Based on: https://blog.tojicode.com/2012/07/sprite-tile-maps-on-gpu.html
 */
float4 main(ps_input input) : SV_Target
{
    float2 pixcoord = input.texcoord * tilemap_size * tile_size;
    float4 color = tex2D(tilemap, input.texcoord);

    // Discard white tiles
    if(color.r == 1.0 || color.g == 1.0)
        return float4(0.0, 0.0, 0.0, 0.0);

    float2 tile_coord = fmod(pixcoord, tile_size);
    float2 tile_offset = floor(color.rg * 256.0) * tile_size;

    return tex2D(tileset, (tile_coord + tile_offset) / tileset_size);
}
