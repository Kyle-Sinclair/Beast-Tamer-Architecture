varying vec4 color;
varying vec2 texCoord;

uniform sampler2D tex;
uniform vec4 myColor;
uniform float Time;

void main(void)
{
    vec4 c = myColor * color;
    //vec4 col = texture2D(tex, texCoord);
    vec4 col = texture2D(tex, texCoord + vec2(Time, sin(Time * 2.5) * 0.5));
    float t = abs(fract(col.r + Time) * 2. - 1.);
    gl_FragColor = col;
    //gl_FragColor = col * fract(Time);
    //gl_FragColor = vec4(1.0, 0.0, 1.0, 1.0);
    //gl_FragColor = vec4(texCoord.xy, 0.0, 1.0);
}