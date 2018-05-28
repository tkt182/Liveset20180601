uniform sampler2DRect image;
uniform int trueWidth,trueHeight;

varying vec3 pos;


void main( void ){
    //vec2 uv = vec2(pos.x / float(trueWidth), pos.y / float(trueHeight));
    vec2 uv = vec2(pos.xy);
    vec4 c[4];
    c[0] = texture2DRect(image, uv);
    c[1] = texture2DRect(image, vec2(1.0-uv.x, uv.y));
    c[2] = texture2DRect(image, vec2(uv.x, 1.0-uv.y));
    c[3] = texture2DRect(image, vec2(1.0-uv.x, 1.0-uv.y));

    vec4 color = (uv.y >= 0.5 && uv.x >= 0.5) ? c[0] :
                 (uv.y >= 0.5 && uv.x < 0.5) ? c[1] :
                 (uv.y < 0.5 && uv.x >= 0.5) ? c[2] : c[3];

    vec4 d = max(c[0], c[1]);
    d = max(d, c[2]);
    d = max(d, c[3]);


    vec3 s = mix(color.rgb, d.rgb, (color.rgb + d.rgb) * 0.5); 
    gl_FragColor.rgba = vec4(s.rgb, 1.0);

}
