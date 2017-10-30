#version 330
in vec2 texCoords;
layout(location = 0) out vec4 frag_color;
void main() {
	frag_color = vec4(texCoords,0,1);
}