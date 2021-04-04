# Shader example
#### Vertex
```hlsl
// Vertex input
struct vs_input {
    float2 position : POSITION;
    float2 texcoord : TEXCOORD1;
};

// Vertex output
struct vs_output {
    float4 position : SV_Position;
    float2 texcoord : TEXCOORD0;
};

// Entry point
vs_output main(vs_input input)
{
    vs_output output;
    output.position = float4(input.position, 0.0, 1.0);
    output.texcoord = input.texcoord;
    return output;
}
```

#### Fragment
```hlsl
// Fragment input
struct ps_input {
    float2 texcoord : TEXCOORD0;
};

// Sampler
sampler2D source : register(S0);

// Entry point
float4 main(ps_input input) : SV_Target
{
    return tex2D(source, input.texcoord);
}
```

# Shader Guide
* [Root](../shader_guide.md)
* [Requirements](00_requirements.md)
* [Thorn's HLSL](01_thorns_hlsl.md)
* [Build script](02_build_script.md)
* **Shader example**
