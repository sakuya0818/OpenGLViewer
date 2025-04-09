#version 460 core
out vec4 FragColor;

uniform sampler2D sampler;
uniform sampler2D sampler1;

in vec2 uv;
in vec3 normal;

void main()
{
	//vec4 aColor = texture(sampler, uv);
	//vec4 bColor = texture(sampler1, uv);
	//vec4 finalColor = aColor * 0.5 + bColor * 0.5;
	//FragColor = vec4(finalColor.rgb, 1.0);

	vec3 normalN = normalize(normal);
	vec3 normalColor = clamp(normalN, 0.0, 1.0);
	FragColor = vec4(normalColor, 1.0);
}