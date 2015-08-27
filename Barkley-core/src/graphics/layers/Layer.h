#pragma once

#include <barkley_types.h>

#include "../Renderable2D.h"
#include "../Renderer2D.h"
#include "../Mask.h"

namespace barkley { namespace graphics {

	class Layer{
	public:
		Renderer2D* renderer;

	protected:
		std::vector < Renderable2D* > m_Renderables;
		Shader* m_Shader;
		maths::mat4 m_ProjectionMatrix;

	public:
		Layer();
		virtual ~Layer();
		Layer(Renderer2D* renderer, Shader* shader, maths::mat4 projectionMatrix);
		virtual Renderable2D* Add(Renderable2D* renderable);

		inline void SetMask(const Mask* mask) const { renderer->SetMask(mask); };

		virtual void Render();

		inline const std::vector<Renderable2D*>& GetRenderables() const { return m_Renderables; }
	



	};

}}