#pragma once

#include <string>
#include "../maths/vec2.h"
#include "../../ext/FreeType-GL/freetype-gl.h"

namespace barkley { namespace graphics {


	class Font
	{
	private:
		ftgl::texture_atlas_t* m_FTAtlas;
		ftgl::texture_font_t* m_FTFont;
		maths::vec2 m_Scale;
		float m_Size;
		
		std::string m_Name;
		std::string m_Filename;


	public:

		Font(const std::string& name, const std::string& filename, float size);
		Font(const std::string& name, const byte* data, unsigned int datasize, float size);

		void SetScale(float x, float y);

		inline ftgl::texture_font_t* GetFTFont() const { return m_FTFont; }
		

		inline const unsigned int GetID() const { return m_FTAtlas->id; }
		inline const std::string& GetName() const { return m_Name; }
		inline const std::string& GetFileName() const { return m_Filename; }
		inline const float GetSize() const { return m_Size; }
		inline const maths::vec2& GetScale() const { return m_Scale; }
	};


}}