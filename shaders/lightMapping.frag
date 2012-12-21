uniform sampler2D firstImage;
uniform sampler2D secondImage;

void main()
{
	gl_FragColor = texture2D(secondImage, gl_TexCoord[0].st);
}
