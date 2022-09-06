precision highp float;
precision highp int;


//Uniforms
//[texture.albedo]//
uniform sampler2D u_sampler_albedo;

//[vec3.albedo]//
uniform vec3 u_albedo;

//Varying
in mediump vec2 v_textureCoordOut;

out vec4 FragColor;

//Defined
const lowp float c_zero = 0.0;
const lowp float c_one = 1.0;
const float PI = 3.14159265359;

void main(void) {

	lowp vec3 albedo     = pow(texture(u_sampler_albedo, v_textureCoordOut).rgb, vec3(2.2)) * u_albedo;
	lowp float alpha	 = texture(u_sampler_albedo, v_textureCoordOut).a;

	FragColor = vec4(albedo, alpha);

}