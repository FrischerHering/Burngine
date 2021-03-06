#version 330

in vec2 passVertexUv;

layout(location = 0) out vec4 outFragmentColor;

uniform vec4 gColor;
uniform sampler2D gTextureSampler;

void main() {

	// The brightness is stored in the red channel
	float texel = texture(gTextureSampler, passVertexUv).r;
	
	// This is actually similar to GL_INTENSITY. This way it's safe.
	outFragmentColor = vec4(texel) * gColor;
}