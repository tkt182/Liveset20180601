uniform sampler2DRect image;
uniform int trueWidth,trueHeight;

varying vec3 pos;


void main( void ){
    //vec2 uv = vec2(pos.x / float(trueWidth), pos.y / float(trueHeight));
    //vec2 uv = vec2(gl_FragCoord.x / float(trueWidth), gl_FragColor.y / float(trueHeight));
    //vec2 uv = vec2(gl_FragCoord.x / 1024.0, gl_FragColor.y / 768.0);
    //vec2 uv = gl_FragCoord.xy;
    vec2 uv = vec2(pos.x, pos.y);
    vec4 c[4];
    vec4 c1;
    c[0] = texture2DRect(image, uv);
    c[1] = texture2DRect(image, vec2(float(trueWidth)-uv.x, uv.y));
    c[2] = texture2DRect(image, vec2(uv.x, float(trueHeight)-uv.y));
    c[3] = texture2DRect(image, vec2(float(trueWidth)-uv.x, float(trueHeight)-uv.y));

//    vec4 color = (uv.y >= 0.5 && uv.x >= 0.5) ? c[0] :
//                 (uv.y >= 0.5 && uv.x < 0.5) ? c[1] :
//                 (uv.y < 0.5 && uv.x >= 0.5) ? c[2] : c[3];
//
//    vec4 color = (gl_FragCoord.y >= 0.5 && gl_FragCoord.x >= 0.5) ? c[0] :
//                 (gl_FragCoord.y >= 0.5 && gl_FragCoord.x < 0.5) ? c[1] :
//                 (gl_FragCoord.y < 0.5 && gl_FragCoord.x >= 0.5) ? c[2] : c[3];
    vec4 color;
    if((pos.y >= float(trueHeight / 2)) && (pos.x >= float(trueWidth / 2))){
        color = c[0];
    }else if((pos.y >= float(trueHeight / 2)) && (pos.x < float(trueWidth / 2))){
        color = c[1];
    }else if((pos.y < float(trueHeight / 2)) && (pos.x >= float(trueWidth / 2))){
        color = c[2];
    }else{
        color = c[3];
    }

    vec4 d = max(c[0], c[1]);
    d = max(d, c[2]);
    d = max(d, c[3]);

    vec3 s = mix(color.rgb, d.rgb, (color.rgb + d.rgb) * 0.5); 
    //gl_FragColor.rgba = vec4(s.rgb, 1.0);
    gl_FragColor.rgba = vec4(color.rgb, 1.0);
    //gl_FragColor.rgba = vec4(c[2].rgb, 1.0);
    //gl_FragColor.rgba = vec4(c[1].rgb, 1.0);
    //gl_FragColor.rgba = vec4(vec3(1.0-uv.x), 1.0);

}
