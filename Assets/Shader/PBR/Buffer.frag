precision highp float;
precision highp int;


//Uniforms
//[texture.albedo]//
uniform sampler2D u_sampler_albedo;
//[texture.typo]//
uniform sampler2D u_sampler_typo;

//IBL
//[light.irradiance]//
uniform samplerCube u_sampler_irradiance;
//[light.prefilter]//
uniform samplerCube u_prefilterMap;
//[light.brdf]//
uniform sampler2D u_brdfLUT;

//[vec3.albedo]//
uniform vec3 u_albedo;
//[float.metallic]//
uniform float u_metallic;
//[float.roughness]//
uniform float u_roughness;
//[float.ao]//
uniform float u_ao;
//[FLOAT_IRRADIANCE]//
uniform vec3 u_irradiance;


//[light.type]//
uniform int u_lightType[MAX_LIGHTS];
//[light.radius]//
uniform float u_lightRadius[MAX_LIGHTS];
//[light.color]//
uniform vec3 u_lightColor[MAX_LIGHTS];
//[light.shadow_map]//
uniform sampler2D u_shadowMap;
//[light.shadow_mode]//
uniform lowp int u_shadowMode[MAX_LIGHTS];
//[light.size]//
uniform int u_lightSize;

//Varying
in mediump vec3 v_eyespaceNormal;//EyespaceNormal;
in lowp vec3 v_lightPosition[MAX_LIGHTS];
in lowp vec4 v_fragPosLightSpace[MAX_LIGHTS];
in mediump vec2 v_textureCoordOut;
in lowp float v_distance[MAX_LIGHTS];
in mediump vec3 v_worldPosition;

out vec4 FragColor;

//Defined
const lowp float c_zero = 0.0;
const lowp float c_one = 1.0;
const float PI = 3.14159265359;

const lowp float c_shadow_width = 1024.f;
const lowp float c_shadow_height = 1024.f;

//Functions
float DistributionGGX(vec3 N, vec3 H, float roughness);
float DistributionPhong(vec3 N, vec3 H, float roughness);
float DistributionGGXMobile(vec3 N, vec3 H, float roughness);
float GeometrySchlickGGX(float NdotV, float roughness);
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness);
float GeometrySmith_Fast(vec3 N, vec3 V, vec3 L, float roughness);
vec3 fresnelSchlick(float cosTheta, vec3 F0);
vec3 fresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness);
float ShadowCalculation(int index, vec4 fragPosLightSpace, vec3 N, vec3 D);
vec4 GetTextureInArray(sampler2D src, int index, vec2 uv);

//Macro Functions
float ClampedPow(float X, float Y) {
	return pow(max(abs(X),0.000001f),Y);
}


void main(void) {
	lowp vec3 albedo = texture(u_sampler_albedo, v_textureCoordOut).rgb * u_albedo;
	float typo = texture(u_sampler_typo, vec2(v_textureCoordOut.x, 1.0f - v_textureCoordOut.y)).r;

	if(typo > 0.3f) {
	    albedo = vec3(1.0f);
	}

	FragColor = vec4(albedo, 1.0f);
}