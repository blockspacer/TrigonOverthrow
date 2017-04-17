#version 440 core
// NOTE: The locations must match ShaderAttributeID
layout (location = 0) in vec3 vertPos;
layout (location = 2) in vec3 vertColor;
layout (location = 3) in vec2 vertUV;
layout (location = 9) in vec4 charRect;
layout (location = 10) in vec2 charPos;

uniform mat4 m; // m will not change foreach char
uniform mat4 vp;

out vec3 vColor;
out vec2 vUV;

void main() {
	vColor = vertColor;
	// vertUV      = [0..1, 0..1]
	// charRect.xy = [startX, startY] in texture
	// charRect.zw = [width, height] of char
	// charPos     = [xPos, yPos]
	vUV = vertUV * charRect.zw + charRect.xy;

	gl_Position = vp * m * vec4(vertPos.xy * charRect.zw + charPos, vertPos.z, 1);
}
