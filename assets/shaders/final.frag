#version 440 core

out vec4 outColor;

in vec3 vColor;
in vec2 vUV;

uniform sampler2D defPos;
uniform sampler2D defNormal;
uniform sampler2D defDiffuseSpecular;
uniform sampler2D defOcclusionMap;

void main() {
	//vec3 pos = texture(defPos, vUV).xyz;
	//vec3 normal = texture(defNormal, vUV).xyz;
	float occlusion = texture(defOcclusionMap, vUV).r;
	vec3 diffuse = texture(defDiffuseSpecular, vUV).xyz;
	float specular = texture(defDiffuseSpecular, vUV).w;

	outColor = vec4(diffuse, 1) * occlusion;
}
