#version 330 core

layout (location = 0) out vec4 color;

uniform vec4 col;
uniform vec2 light_pos;

in DATA
{
    vec4 position;
	vec2 uv;
	float tid;
	vec4 color;

} fs_in;

uniform sampler2D textures[32];


void main()
{
	float intensity = 1.0 / length(fs_in.position.xy - light_pos);
	vec4 texColor = fs_in.color;
	if (fs_in.tid > 0.0)
	{
		int t_id = int(fs_in.tid - 0.5);
		switch(t_id)
		{
		case 0: texColor = fs_in.color * texture(textures[0], fs_in.uv); break;
		case 1: texColor = fs_in.color * texture(textures[1], fs_in.uv); break;
		case 2: texColor = fs_in.color * texture(textures[2], fs_in.uv); break;
		case 3: texColor = fs_in.color * texture(textures[3], fs_in.uv); break;
		case 4: texColor = fs_in.color * texture(textures[4], fs_in.uv); break;
		case 5: texColor = fs_in.color * texture(textures[5], fs_in.uv); break;
		case 6: texColor = fs_in.color * texture(textures[6], fs_in.uv); break;
		case 7: texColor = fs_in.color * texture(textures[7], fs_in.uv); break;
		case 8: texColor = fs_in.color * texture(textures[8], fs_in.uv); break;
		case 9: texColor = fs_in.color * texture(textures[9], fs_in.uv); break;
		case 10: texColor = fs_in.color * texture(textures[10], fs_in.uv); break;
		case 11: texColor = fs_in.color * texture(textures[11], fs_in.uv); break;
		case 12: texColor = fs_in.color * texture(textures[12], fs_in.uv); break;
		case 13: texColor = fs_in.color * texture(textures[13], fs_in.uv); break;
		case 14: texColor = fs_in.color * texture(textures[14], fs_in.uv); break;
		case 15: texColor = fs_in.color * texture(textures[15], fs_in.uv); break;
		case 16: texColor = fs_in.color * texture(textures[16], fs_in.uv); break;
		case 17: texColor = fs_in.color * texture(textures[17], fs_in.uv); break;
		case 18: texColor = fs_in.color * texture(textures[18], fs_in.uv); break;
		case 19: texColor = fs_in.color * texture(textures[19], fs_in.uv); break;
		case 20: texColor = fs_in.color * texture(textures[20], fs_in.uv); break;
		case 21: texColor = fs_in.color * texture(textures[21], fs_in.uv); break;
		case 22: texColor = fs_in.color * texture(textures[22], fs_in.uv); break;
		case 23: texColor = fs_in.color * texture(textures[23], fs_in.uv); break;
		case 24: texColor = fs_in.color * texture(textures[24], fs_in.uv); break;
		case 25: texColor = fs_in.color * texture(textures[25], fs_in.uv); break;
		case 26: texColor = fs_in.color * texture(textures[26], fs_in.uv); break;
		case 27: texColor = fs_in.color * texture(textures[27], fs_in.uv); break;
		case 28: texColor = fs_in.color * texture(textures[28], fs_in.uv); break;
		case 29: texColor = fs_in.color * texture(textures[29], fs_in.uv); break;
		case 30: texColor = fs_in.color * texture(textures[30], fs_in.uv); break;
		case 31: texColor = fs_in.color * texture(textures[31], fs_in.uv); break;
		
		}
	


	}
	color = texColor * intensity;
	//color = vec4(fs_in.tid,0,0,1);

}