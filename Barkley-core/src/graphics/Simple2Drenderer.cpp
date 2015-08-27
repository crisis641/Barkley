#include "simple2Drenderer.h"
#include "renderable2d.h"

namespace barkley { namespace graphics {
	
	void Simple2DRenderer::Submit(const Renderable2D* renderable)
	{
		m_RenderQueue.push_back((StaticSprite*)renderable);

	}
	void Simple2DRenderer::Flush()
	{
		while (!m_RenderQueue.empty())
		{
			const StaticSprite* sprite = m_RenderQueue.front();
			sprite->getVAO()->Bind();
			sprite->getIBO()->Bind();

			sprite->getShader().SetUniformMat4("ml_matrix", maths::mat4::Translate(sprite->GetPosition()));
			glDrawElements(GL_TRIANGLES, sprite->getIBO()->GetCount(), GL_UNSIGNED_SHORT, 0);

			sprite->getIBO()->Unbind();
			sprite->getVAO()->Unbind();

			m_RenderQueue.pop_front();
		}
	}

}}