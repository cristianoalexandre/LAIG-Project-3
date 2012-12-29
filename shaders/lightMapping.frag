uniform sampler2D firstImage;
uniform sampler2D secondImage;

void main()
{
	float height = 0.6;
	vec4 image = texture2D(secondImage, gl_TexCoord[0].st);
	
	vec4 heightmap = texture2D(firstImage, gl_TexCoord[0].st);
	
	if(heightmap.r+heightmap.g+heightmap.b < height){
		image.r = 0.0;
		image.g = 0.0;
	 }

	gl_FragColor = image;
}
