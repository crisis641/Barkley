#pragma once

#include <barkley_types.h>
#include <maths/maths.h>

namespace barkley{ namespace graphics { namespace MeshFactory{

	uint CreateQuad(float x, float y, float width, float height);
	uint CreateQuad(const maths::vec2& position, const maths::vec2& size);


}}}