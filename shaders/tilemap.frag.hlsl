/*
 * tilemap.frag.hlsl
 * Created: 2021-03-24, 15:40:07.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
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
 * Basically what it does it take a pixel from the tilemap
 * and pick a tile from a tileset assigned to the tilemap.
 * So the pixel color (0; 0; M) means that the tile at (0; 0)
 * will be used for displaying.
 * Based on: https://blog.tojicode.com/2012/07/sprite-tile-maps-on-gpu.html
 */
float4 main(ps_input input) : SV_Target
{
    float2 pixcoord = input.texcoord * tilemap_size * tile_size;
    float4 color = tex2D(tilemap, input.texcoord);

    // Discard fully white pixels
    if(color.r == 1.0 && color.g == 1.0)
        return float4(0.0, 0.0, 0.0, 0.0);

    float2 tile_coord = fmod(pixcoord, tile_size);
    float2 tile_offset = floor(color.rg * 256.0) * tile_size;

    return tex2D(tileset, (tile_coord + tile_offset) / tileset_size);
}
