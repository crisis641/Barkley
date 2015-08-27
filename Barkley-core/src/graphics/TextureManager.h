#pragma once

#include <vector>
#include <barkley_types.h>

#include "Texture.h"

namespace barkley { namespace graphics {

	class TextureManager
	{
	private:
		static std::vector<Texture*> m_Textures;
	public:
		static void Add(Texture* texture);
		static Texture* Get(const std::string& name);
		static void Clean();
	private:
		TextureManager() { }
	};

} }