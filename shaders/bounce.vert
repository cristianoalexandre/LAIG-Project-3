varying vec4 diffuse,ambientGlobal,ambient;
varying vec3 normal,lightDir,halfVector;
varying float dist;


uniform float time;


void main(){

	vec4 ecPos;
	vec3 aux;
	
	/* Generate texture coordinates */
	gl_TexCoord[0] = gl_MultiTexCoord0;
	
	/* Normalize normals*/
	normal = normalize(gl_NormalMatrix * gl_Normal);
	
	for(int i = 0; i < gl_MaxLights; i++){
	
		/* Compute the light's direction */
		ecPos = gl_ModelViewMatrix * gl_Vertex;
		aux = vec3(gl_LightSource[i].position-ecPos);
		lightDir = normalize(aux);
		dist = length(aux);
		
		halfVector = normalize(gl_LightSource[i].halfVector.xyz);
			
		/* Compute the diffuse, ambient and globalAmbient terms */
		diffuse = gl_FrontMaterial.diffuse * gl_LightSource[i].diffuse;
			
		/* The ambient terms have been separated since one of them */
		/* suffers attenuation */
		ambient = gl_FrontMaterial.ambient * gl_LightSource[i].ambient;
		ambientGlobal = gl_LightModel.ambient * gl_FrontMaterial.ambient;
	}
	
	/* Compute vertex values for bounce animation */
	vec4 v = vec4(gl_Vertex);
	float xSin = sin(5.0*time*0.01)*cos(time*0.01)*0.1;
	//float zSin = sin(v.z*5.0 + 1.5) *0.5;
	
	if(xSin < 0.0){
		xSin = abs(xSin);
	}
	v.y = v.y + xSin;
	
	// Set the position of the current vertex
	gl_Position = gl_ModelViewProjectionMatrix * v;
}