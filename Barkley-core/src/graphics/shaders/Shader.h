#pragma once

#include <barkleygl.h>
#include <vector>
#include <iostream>

#include "../../maths/Maths.h"
#include "../../utils/FileUtils.h"

namespace barkley { namespace graphics {

#define SHADER_VERTEX_INDEX		0
#define SHADER_UV_INDEX			1
#define SHADER_MASK_UV_INDEX	2
#define SHADER_TID_INDEX		3
#define SHADER_MASK_ID_INDEX	4
#define SHADER_COLOR_INDEX		5

	class Shader
	{

	private:
		const char* m_Name;
		const char *m_VertPath, *m_FragPath;
		const char *m_VertSrc, *m_FragSrc;
	public:
		GLuint m_ShaderID;
		Shader(const char* name, const char* vertSrc, const char* fragSrc);
		Shader(const char* vertPath, const char* fragPath);
		~Shader();

		
		void SetUniform1f(const GLchar* name, float value);
		void SetUniform1fv(const GLchar* name, float* value, int count);
		void SetUniform1i(const GLchar* name, int value);
		void SetUniform1iv(const GLchar* name, int* value, int count);
		void SetUniform2f(const GLchar* name, const maths::vec2& vector);
		void SetUniform3f(const GLchar* name, const maths::vec3& vector);
		void SetUniform4f(const GLchar* name, const maths::vec4& vector);
		void SetUniformMat4(const GLchar* name, const maths::mat4& matrix);
		
		
		void Bind() const;
		void Unbind() const;

	private:
		GLuint Load(const char* vertSrc, const char* fragSrc);
		GLint GetUniformLocation(const GLchar* name);

	public:
		static Shader* FromFile(const char* vertPath, const char* fragPath);
		static Shader* FromSrc(const char* vertSrc, const char* fragSrc);
		static Shader* FromSrc(const char* name, const char* vertSrc, const char* fragSrc);


	};


}}