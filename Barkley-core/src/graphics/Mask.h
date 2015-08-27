#pragma once

#include "Texture.h"
#include "../maths/maths.h"

namespace barkley{ namespace graphics{

	struct Mask
	{
		Texture* texture;
		maths::mat4 transform;

		Mask(Texture* texture, const maths::mat4 transform = maths::mat4::Identity())
			: texture(texture), transform(transform) 
		{ 
			this->transform = maths::mat4::Scale(maths::vec3((float)texture->GetWidth() / (float)texture->GetHeight(), 1.0f, 1.0f));
		}


	
	};


}}