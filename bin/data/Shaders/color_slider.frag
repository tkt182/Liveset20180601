uniform sampler2DRect image;
uniform int imgWidth,imgHeight;
uniform int trueWidth, trueHeight;
uniform float rand;
uniform float timer;
uniform int flags;
uniform float val1;
uniform vec2 blur_vec;
uniform vec4 noise_color;
int flgs;
float pix_w,pix_h;
varying vec3 pos;

float srand(float val1, float val2){
    return 2.*fract(sin(dot(vec2(val1, val2), vec2(12.9898,78.233))) * 43758.5453)-1.;
}

void main (void)
{
    pix_w = 1.0;
    pix_h = 1.0;
    flgs = flags;
    
    vec2 texCoord = vec2(pos.x, pos.y);
    vec4 col = texture2DRect(image,texCoord);
    
    vec4 col_s;
    float rand2 = rand;
    //rand2 = step(0.0, srand(rand));
    float yrand = srand(timer, rand);
    //if(pos.y < yrand){
    float ybase = sin((20.0 * srand(timer, val1) * pos.y/float(trueHeight))) - 1.0;
    //float ybase = sin((0.1 * srand(val1, pos.y) * pos.y/float(trueHeight))) - 1.0;
    
    //if(ybase * rand2 < -1.0){
    //if(ybase * rand2 < rand - 2.0){
    //    col_s = texture2DRect(image,texCoord + vec2(floor(sin(pos.y/30.0*rand2+rand2*rand2))*30.0*rand2, 0.0));
    //}else{
        col_s = col;
    //}
    
    //if(pos.y < 500.){
    //    col_s = texture2DRect(image,texCoord + vec2(floor(sin(pos.y/30.0*rand2+rand2*rand2))*30.0*rand2,0));
    //}else{
    //    col_s = col;
    //}
    
    //vec4 col_s = texture2DRect(image,texCoord + vec2(floor(sin(pos.y/30.0*rand2+rand2*rand2))*30.0*rand2,0));
    
    vec4 col_s1[5],col_s2[5];
    for (int i = 0;i < 6;i++){
        /*
        col_s1[i] = texture2DRect(image,texCoord +  vec2(-pix_w*float(i)*blur_vec.x ,-pix_h*float(i)*blur_vec.y));
        col_s2[i] = texture2DRect(image,texCoord + vec2( pix_w*float(i)*blur_vec.x , pix_h*float(i)*blur_vec.y));
        */
        //if(pos.y < yrand){
        //if(pos.y < 500.){
        //if(ybase * rand2 < -1.0){
        //if(ybase * rand2 < rand - 2.0){
        if(ybase * rand2 < srand(pos.x, pos.y) - 2.0){
            col_s1[i] = texture2DRect(image,texCoord + vec2(-pix_w*float(i)*blur_vec.x*30.0 , 0.0));
            col_s2[i] = texture2DRect(image,texCoord + vec2( pix_w*float(i)*blur_vec.x*30.0 , 0.0));
            col_s1[i] += noise_color;
            col_s2[i] += noise_color;
        }else{
            col_s1[i] = col;
            col_s2[i] = col;
            col_s1[i] = texture2DRect(image,texCoord + vec2(-pix_w*float(i)*blur_vec.x*1.0 , 0.0));
            col_s2[i] = texture2DRect(image,texCoord + vec2( pix_w*float(i)*blur_vec.x*1.0 , 0.0));
        }
        
        //col_s1[i] = texture2DRect(image,texCoord + vec2(-pix_w*float(i)*blur_vec.x*10.0 , 0.0));
        //col_s2[i] = texture2DRect(image,texCoord + vec2( pix_w*float(i)*blur_vec.x*10.0 , 0.0));
        
    }
    
    col_s1[0] = (col_s1[0] + col_s1[1] + col_s1[2] + col_s1[3] + col_s1[4])/5.0;
    col_s2[0] = (col_s2[0]+ col_s2[1]+ col_s2[2]+ col_s2[3]+ col_s2[4])/5.0;
    
    
    col = (col_s1[0]*1.5 + col_s2[0]*1.5 + col_s) / 3.0;
    
	gl_FragColor.rgba = col.rgba;
}
