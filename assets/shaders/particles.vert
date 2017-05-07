#version 440 core
// NOTE: The locations must match ShaderAttributeID
layout(location = 12) in vec3 vertPos;
layout(location = 13) in float vertVel;
layout(location = 14) in float life;

out vec3 vColor;

uniform mat4 v;
uniform mat4 p;

void main() {
	vColor = vec3(0, 1, 0);
	gl_PointSize = 2;
	gl_Position = p * v * vec4(vertPos, 1.0f);
}