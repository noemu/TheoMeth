#version 330								
layout(location = 0) in vec2 in_position;	
uniform mat4 pvm;							
out vec2 texCoords;						
void main() {								
	vec4 vert = vec4(in_position,0,1);		
	gl_Position = pvm*vert;					
	texCoords = vert.xy;					
}											