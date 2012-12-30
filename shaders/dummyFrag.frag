varying vec4 diffuse, ambientGlobal, ambient;
varying vec3 normal, lightDir, halfVector;
varying float dist;
	

uniform sampler2D firstImage;


void main(){

	vec3 n,halfV,viewV,ldir,colorTexture,colorFragment;
	float NdotL,NdotHV;
	vec4 texel, color = ambientGlobal;
	float att, alphaTexture, alphaFragment;

		
	/* a fragment shader can't write a varying variable, hence we need
	a new variable to store the normalized interpolated normal */
	n = normalize(normal);
		
	/* compute the dot product between normal and normalized lightdir */
	NdotL = max(dot(n,normalize(lightDir)),0.0);
	
	for(int i = 0; i < gl_MaxLights; i++){
	
		if (NdotL > 0.0) {
		
			att = 1.0 / (gl_LightSource[i].constantAttenuation +
					gl_LightSource[i].linearAttenuation * dist +
					gl_LightSource[i].quadraticAttenuation * dist * dist);
			color += att * (diffuse * NdotL + ambient);
					
			halfV = normalize(halfVector);
			NdotHV = max(dot(n,halfV),0.0);
			color += att * gl_FrontMaterial.specular * gl_LightSource[i].specular * 
							pow(NdotHV,gl_FrontMaterial.shininess);
		}
	}
	
	colorFragment = color.rgb;
	alphaFragment = color.a;

	texel = texture2D(firstImage, gl_TexCoord[0].st);
	colorTexture = texel.rgb;
	alphaTexture = texel.a;
	
	gl_FragColor = vec4(colorTexture * colorFragment, alphaTexture * alphaFragment);
}