# Thorn's HLSL
Since we are using OpenGL, newest versions of HLSL are simply incompatible with the OpenGL rendering pipeline: Direct3D10+ is aimed at samplers separated from images.  
However, Direct3D9 had combined image-samplers. Bingo!  

So if you would write a fragment (pixel) shader using HLSL for Thorn, you would need to use `sampler2D` and `tex2D()` instead of `SamplerState` and `Sample()`:
```hlsl
sampler2D source : register(S0);

float4 main(float2 uv : TEXCOORD0) : SV_Target
{
    return tex2D(source, uv);
}
```

Which is equivalent to GLSL:
```glsl
layout(location = 0) in vec2 uv;
layout(location = 0) out vec4 frag_color;
layout(binding = 0) uniform sampler2D source;
void main()
{
    frag_color = texture(source, uv);
}
```

# Shader Guide
* [Root](../shader_guide.md)
* [Requirements](00_requirements.md)
* **Thorn's HLSL**
* [Build script](02_build_script.md)
* [Shader example](03_shader_example.md)
