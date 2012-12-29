uniform sampler2D firstImage;


void main(){

	vec4 texture = texture2D(firstImage, gl_TexCoord[0].st);
	gl_FragColor = texture;
}