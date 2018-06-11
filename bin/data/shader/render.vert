uniform sampler2DRect posTex;
uniform vec2 screen;

varying vec4 vColor;

void main() {
    
    vec2 pixPos = texture2DRect(posTex, gl_MultiTexCoord0.xy).xy;
    
    pixPos.x = pixPos.x * screen.x - screen.x/2.;
    pixPos.y = pixPos.y * screen.x - screen.x/2.;
    
    vColor = gl_Color;
    
    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * vec4(pixPos, 0.0, 1.0);
    
     
}
