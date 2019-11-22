#version 330 core

in vec3 in_Position;
in vec4 in_Color;
out vec4 ex_Color;

uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;

void main(void) {
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(in_Position, 1.0f);
	ex_Color = in_Color;
}