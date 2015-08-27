#include "tilelayer.h"

#include "maths/tvec2.h"



	TileLayer::TileLayer(barkley::graphics::Shader* shader)
		:Layer(new barkley::graphics::BatchRenderer2D(maths::tvec2<uint>(0,0)), shader, barkley::maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f))
		{
			
		}

		TileLayer::~TileLayer()
		{

		}

		
