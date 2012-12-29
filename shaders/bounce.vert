uniform float time;


void main(){

	gl_TexCoord[0] = gl_MultiTexCoord0;
	vec4 v = vec4(gl_Vertex);
	
	float xSin = sin(5.0*time*0.004)*cos(time*0.004)*0.1;
	float zSin = sin(v.z*5.0 + 1.5) *0.5;
	
	if(xSin < 0.0){
		xSin = abs(xSin);
	}
	v.y = v.y;// + xSin;
	
	
	// Set the position of the current vertex
	gl_Position = gl_ModelViewProjectionMatrix * v;
}