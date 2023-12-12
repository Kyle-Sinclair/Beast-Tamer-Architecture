varying vec2 texCoord;

uniform sampler2D tex;
uniform vec2 Resolution;
uniform vec2 TexResolution;
uniform float Time;

float speed = 0.2;
float frequency = 20.;
float amplitude = 0.02;

void main(void)
{
    vec2 uv = texCoord;
    
    vec2 uvOffset = vec2(0.0, sin((texCoord.x + Time * speed) * frequency) * amplitude);
    vec4 col = texture2D(tex, uv);
    float falloff = clamp(1. - distance(uv - uvOffset * 0.25, vec2(0.5)), 0., 1.);
    col = mix(vec4(.75, .5, 1., 1.) * .5 * falloff + col, col, col.a);
    gl_FragColor = col;
}