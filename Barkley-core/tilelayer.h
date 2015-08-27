#pragma once


#include "src\graphics\layers\layer.h"
#include "src\graphics\BatchRenderer2D.h"




		class TileLayer : public barkley::graphics::Layer
		{

		public:
			TileLayer(barkley::graphics::Shader* shader);
			virtual ~TileLayer();

		};

