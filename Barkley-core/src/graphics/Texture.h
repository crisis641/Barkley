#pragma once

#include <iostream>
#include <string>

#include <FreeImage.h>

#include <barkley_types.h>
#include <barkleygl.h>

#include <utils/ImageLoad.h>


namespace barkley { namespace graphics{

	enum TextureWrap
	{
	REPEAT =			GL_REPEAT, 
	CLAMP =				GL_CLAMP,
	MIRRORED_REPEAT =	GL_MIRRORED_REPEAT,
	CLAMP_TO_EDGE =		GL_CLAMP_TO_EDGE,
	CLAM_TO_BORDER =	GL_CLAMP_TO_BORDER
	};
	
	class Texture
	{
	private:
		std::string m_Name, m_FileName;
		uint m_TID;
		uint m_Width, m_Height;
		unsigned int m_Bits;
		
		static TextureWrap s_WrapMode;

	public:
		Texture(uint width, uint height);
		Texture(const std::string& name, const std::string& filename);
		~Texture();
		void Bind() const;
		void Unbind() const;
		
		inline const std::string& GetName() const { return m_Name; }
		inline const unsigned int GetID() const { return m_TID; }
		inline const unsigned int GetWidth() const { return m_Width; }
		inline const unsigned int GetHeight() const { return m_Height; }

		inline static void SetWrap(TextureWrap mode) { s_WrapMode = mode; };

	private:
		GLuint Load();


	};
}}