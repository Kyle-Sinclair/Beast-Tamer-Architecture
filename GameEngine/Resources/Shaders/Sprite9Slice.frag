varying vec4 color;
varying vec2 texCoord;

uniform sampler2D tex;
uniform vec2 texSize;
uniform vec2 drawSize;
uniform vec4 myColor;
uniform float Time;

#define B vec4(5., 5., 5., 5.)

vec2 uv9slice(vec2 uv, vec2 scale, vec4 border)
{
    vec2 t = clamp((scale * uv - border.xy) / (scale - border.xy - border.zw), 0., 1.);
    return mix(uv * scale, 1. - scale * (1. - uv), t);
}

void main(void)
{
    vec2 s = drawSize / texSize;
    
    vec4 b = min(B / texSize.xyxy, vec4(.499));
    
    vec2 uv = uv9slice(texCoord, s, b);

    vec4 c = myColor * color;
    vec4 col = texture2D(tex, uv);
    gl_FragColor = col;
    
    //gl_FragColor = vec4(uv, 0.0, 1.0);
}