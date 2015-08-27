precision highp float;

uniform highp vec4 col;
uniform highp vec2 light_pos;

varying highp vec4 vs_position;
varying highp vec2 vs_uv;
varying highp float vs_tid;
varying highp vec4 vs_color;

uniform sampler2D texture_0;
uniform sampler2D texture_1;
uniform sampler2D texture_2;
uniform sampler2D texture_3;
uniform sampler2D texture_4;
uniform sampler2D texture_5;
uniform sampler2D texture_6;
uniform sampler2D texture_7;
uniform sampler2D texture_8;
uniform sampler2D texture_9;
//uniform sampler2D texture_10;
//uniform sampler2D texture_11;
//uniform sampler2D texture_12;
//uniform sampler2D texture_13;
//uniform sampler2D texture_14;
//uniform sampler2D texture_15;
//uniform sampler2D texture_16;
//uniform sampler2D texture_17;
//uniform sampler2D texture_18;
//uniform sampler2D texture_19;
//uniform sampler2D texture_20;
//uniform sampler2D texture_21;
//uniform sampler2D texture_22;
//uniform sampler2D texture_23;
//uniform sampler2D texture_24;
//uniform sampler2D texture_25;
//uniform sampler2D texture_26;
//uniform sampler2D texture_27;
//uniform sampler2D texture_28;
//uniform sampler2D texture_29;
//uniform sampler2D texture_30;
//uniform sampler2D texture_31;

void main()
{
	float intensity = 1.0 / length(vs_position.xy - light_pos);
	vec4 texColor = vs_color;
	if (vs_tid > 0.0)
	{
		int tid = int(vs_tid - 0.5);
		if (tid == 0)
			texColor = vs_color * texture2D(texture_0, vs_uv);
		else if (tid == 1)
			texColor = vs_color * texture2D(texture_1, vs_uv);
		else if (tid == 2)
			texColor = vs_color * texture2D(texture_2, vs_uv);
		else if (tid == 3)
			texColor = vs_color * texture2D(texture_3, vs_uv);
		else if (tid == 4)
			texColor = vs_color * texture2D(texture_4, vs_uv);
		else if (tid == 5)
			texColor = vs_color * texture2D(texture_5, vs_uv);
		else if (tid == 6)
			texColor = vs_color * texture2D(texture_6, vs_uv);
		else if (tid == 7)
			texColor = vs_color * texture2D(texture_7, vs_uv);
		else if (tid == 8)
			texColor = vs_color * texture2D(texture_8, vs_uv);
		else if (tid == 9)
			texColor = vs_color * texture2D(texture_9, vs_uv);
//		else if (tid == 10)
//			texColor = vs_color * texture2D(texture_10, vs_uv);
//		else if (tid == 11)
//			texColor = vs_color * texture2D(texture_11, vs_uv);
//		else if (tid == 12)
//			texColor = vs_color * texture2D(texture_12, vs_uv);
//		else if (tid == 13)
//			texColor = vs_color * texture2D(texture_13, vs_uv);
//		else if (tid == 14)
//			texColor = vs_color * texture2D(texture_14, vs_uv);
//		else if (tid == 15)
//			texColor = vs_color * texture2D(texture_15, vs_uv);
//		else if (tid == 16)
//			texColor = vs_color * texture2D(texture_16, vs_uv);
//		else if (tid == 17)
//			texColor = vs_color * texture2D(texture_17, vs_uv);
//		else if (tid == 18)
//			texColor = vs_color * texture2D(texture_18, vs_uv);
//		else if (tid == 19)
//			texColor = vs_color * texture2D(texture_19, vs_uv);
//		else if (tid == 20)
//			texColor = vs_color * texture2D(texture_20, vs_uv);
//		else if (tid == 21)
//			texColor = vs_color * texture2D(texture_21, vs_uv);
//		else if (tid == 22)
//			texColor = vs_color * texture2D(texture_22, vs_uv);
//		else if (tid == 23)
//			texColor = vs_color * texture2D(texture_23, vs_uv);
//		else if (tid == 24)
//			texColor = vs_color * texture2D(texture_24, vs_uv);
//		else if (tid == 25)
//			texColor = vs_color * texture2D(texture_25, vs_uv);
//		else if (tid == 26)
//			texColor = vs_color * texture2D(texture_26, vs_uv);
//		else if (tid == 27)
//			texColor = vs_color * texture2D(texture_27, vs_uv);
//		else if (tid == 28)
//			texColor = vs_color * texture2D(texture_28, vs_uv);
//		else if (tid == 29)
//			texColor = vs_color * texture2D(texture_29, vs_uv);
//		else if (tid == 30)
//			texColor = vs_color * texture2D(texture_30, vs_uv);
//		else if (tid == 31)
//			texColor = vs_color * texture2D(texture_31, vs_uv);
	}
	gl_FragColor = texColor * intensity;
}