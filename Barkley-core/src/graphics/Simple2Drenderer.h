#pragma once

#include <deque>

#include "renderer2d.h"
#include "static_sprite.h"

namespace barkley { namespace graphics {

		class Simple2DRenderer : Renderer2D
		{
		private:
			std::deque<const StaticSprite*> m_RenderQueue;
		public:
			void Submit(const Renderable2D* renderable) override;
			void Flush() override;

		};

}}