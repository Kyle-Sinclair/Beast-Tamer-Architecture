#version 400

in vec2 texCoord;

uniform sampler2D tex;
uniform vec2 Resolution;
uniform vec2 TexResolution;
uniform float Time;

float speed = 0.2;
float frequency = 20.;
float amplitude = 0.02;

// Base on: t3ssel8r's "Crafting a Better Shader for Pixel Art Upscaling" video:
// https://www.youtube.com/watch?v=d6tp43wZqps
void main(void)
{
    vec2 uv = texCoord;
    vec2 boxSize = clamp(fwidth(uv) * TexResolution, 1e-5, 1.0);
    vec2 tx = uv * TexResolution - .5 * boxSize;
    vec2 txOffset = clamp((fract(tx) - (1. - boxSize)) / boxSize, 0.0, 1.0);
    //vec2 txOffset = smoothstep(1. - boxSize, vec2(1.), fract(tx));
    vec2 uvPix = (floor(tx) + .5 + txOffset) / TexResolution;
    
    float mipmapLevel = textureQueryLod(tex, uv).x;
    
    vec4 col0 = texture2D(tex, uv);
    vec4 col1 = textureLod(tex, uvPix, mipmapLevel);
    gl_FragColor = col1;
    //gl_FragColor = vec4(abs(col1.xyz - col0.xyz) * 10., 1.);
    //gl_FragColor = vec4(texCoord, 0.0, 1.0);
}