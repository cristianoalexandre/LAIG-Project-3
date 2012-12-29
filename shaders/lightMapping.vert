uniform sampler2D firstImage;
uniform sampler2D secondImage;

void main()
{
	float height=0.5;
	// generate texture coords
	gl_TexCoord[0] = gl_MultiTexCoord0;
	vec4 v =vec4(gl_Vertex);

	vec4 offset= texture2D(firstImage, gl_TexCoord[0].st);
	v.y = offset.r+offset.g+offset.b;
	
	if(v.y < height){
		v.y = height;
	}

	// Set the position of the current vertex
	gl_Position = gl_ModelViewProjectionMatrix * v;
}
