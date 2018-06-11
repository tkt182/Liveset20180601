uniform sampler2DRect prevPosData;
uniform float t;
uniform float m;
uniform float w;
uniform vec2 center;

varying vec2 vTexCoord;

void main() {

    vec2 pos = texture2DRect(prevPosData, gl_FragCoord.xy).xy - vec2(0.5);
    pos = pos * 2.;

    vec2 cp = pos - center;

    float r2 = cp.x * cp.x + cp.y * cp.y;
    if (r2 < 0.000001) r2 = 0.000001;

    float a = abs(sin((atan(cp.y, cp.x) - length(cp) + t) * 10.0 * w) * 0.5) + 0.2;
	float b = 0.01 / abs(a - length(cp));
    b = clamp(b, 0.0, 1.0);

    vec2 v;
    v.x = - (m / r2 + b) * (cp.x * cos(t) + cp.y * sin(t));
    v.y = - (m / r2 + b) * (cp.y * cos(t) - cp.x * sin(t));

    pos = pos + v;

    gl_FragColor = vec4(pos * 0.5 + vec2(0.5), 0, 1.0);

}
