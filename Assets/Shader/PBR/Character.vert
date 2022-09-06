#define MAX_WEIGHTS 3

// Attributes
//[att.position]//
in vec4 a_position;
//[att.tex_uv]//
in vec2 a_textureCoordIn;

// Uniforms
//[matrix.projection]//
uniform mat4 u_projectionMatrix;//Projection;
//[matrix.modelview]//
uniform mat4 u_modelViewMatrix;//Modelview;
// Varying
out mediump vec2 v_textureCoordOut;


//defined
const lowp float c_zero = 0.0;
const lowp float c_one = 1.0;

void main(void) {
	v_textureCoordOut = a_textureCoordIn;

    //vertex position
    gl_Position = u_projectionMatrix * u_modelViewMatrix * a_position;
}
