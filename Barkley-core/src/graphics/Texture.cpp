#include "texture.h"

#include <utils/Log.h>

namespace barkley { namespace graphics {

	TextureWrap Texture::s_WrapMode = REPEAT;


	Texture::Texture(uint width, uint height)
		:m_Width(width), m_Height(height), m_FileName("NULL")
		{
			m_TID = Load();
		}

	Texture::Texture(const std::string& name, const std::string& filename)
		: m_Name(name), m_FileName(filename)
		{
			m_TID = Load();
		}

		Texture::~Texture()
		{
			GLCall(glDeleteTextures(1, &m_TID));
		}

		GLuint Texture::Load()
		{
			//FIBITMAP *dib;
			BYTE* pixels = nullptr;
			if (m_FileName != "NULL")
				pixels = load_image(m_FileName.c_str(), &m_Width, &m_Height, &m_Bits);
			else
				m_Bits = 32; // temp

			GLuint result;
			GLCall(glGenTextures(1, &result));
			GLCall(glBindTexture(GL_TEXTURE_2D, result));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint) s_WrapMode));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint) s_WrapMode));


			if (m_Bits != 24 && m_Bits != 32)
			{

				//BARKLEY_ERROR("[Texture]: Unsupported image bit-depth! (", m_Bits, ")");
			}


			GLint InternalFormat = m_Bits == 32 ? GL_RGBA : GL_RGB;
#ifdef BARKLEY_PLATFORM_WEB
			GLenum format = m_Bits == 32 ? GL_RGBA : GL_RGB;
#else
			GLenum format = m_Bits == 32 ? GL_BGRA : GL_BGR;
#endif


			

			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, InternalFormat, m_Width, m_Height, 0,format, GL_UNSIGNED_BYTE, pixels));
			GLCall(glBindTexture(GL_TEXTURE_2D, 0));

			if (pixels != nullptr)
				delete[] pixels;

			return result;
		}

		void Texture::Bind() const
		{
			GLCall(glBindTexture(GL_TEXTURE_2D, m_TID));
		}

		void Texture::Unbind() const
		{
			GLCall(glBindTexture(GL_TEXTURE_2D, 0));
		}

}}