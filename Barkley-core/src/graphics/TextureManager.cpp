#include "TextureManager.h"

namespace barkley { namespace graphics {

	std::vector<Texture*> TextureManager::m_Textures;

	void TextureManager::Add(Texture* texture)
	{
		m_Textures.push_back(texture);
	}

	Texture* TextureManager::Get(const std::string& name)
	{
		for (Texture* texture : m_Textures)
		{
			if (texture->GetName() == name)
				return texture;
		}
		return nullptr;
	}

	void TextureManager::Clean()
	{
		for (int i = 0; i < (int)m_Textures.size(); i++)
			delete m_Textures[i];
	}

} }