#include "Layer.h"

namespace barkley { namespace graphics {

		
	Layer::Layer(Renderer2D* renderer, Shader* shader, maths::mat4 projectionMatrix)
		: renderer(renderer), m_Shader(shader), m_ProjectionMatrix(projectionMatrix)
	{
	
		m_Shader->Bind();
		m_Shader->SetUniformMat4("pr_matrix", m_ProjectionMatrix);

#ifdef BARKLEY_PLATFORM_WEB
		m_Shader->SetUniform1i("texture_0", 0);
		m_Shader->SetUniform1i("texture_1", 1);
		m_Shader->SetUniform1i("texture_2", 2);
		m_Shader->SetUniform1i("texture_3", 3);
		m_Shader->SetUniform1i("texture_4", 4);
		m_Shader->SetUniform1i("texture_5", 5);
		m_Shader->SetUniform1i("texture_6", 6);
		m_Shader->SetUniform1i("texture_7", 7);
		m_Shader->SetUniform1i("texture_8", 8);
		//m_Shader->setUniform1i("textures_9", 9);
		#if 0
m_Shader->setUniform1i("textures_10", 10);
		m_Shader->SetUniform1i("textures_12", 12);
		m_Shader->SetUniform1i("textures_13", 13);
		m_Shader->SetUniform1i("textures_14", 14);
		m_Shader->SetUniform1i("textures_15", 15);
		m_Shader->SetUniform1i("textures_16", 16);
		m_Shader->SetUniform1i("textures_17", 17);
		m_Shader->SetUniform1i("textures_18", 18);
		m_Shader->SetUniform1i("textures_19", 19);
		m_Shader->SetUniform1i("textures_20", 20);
		m_Shader->SetUniform1i("textures_21", 21);
		m_Shader->SetUniform1i("textures_22", 22);
		m_Shader->SetUniform1i("textures_23", 23);
		m_Shader->SetUniform1i("textures_24", 24);
		m_Shader->SetUniform1i("textures_25", 25);
		m_Shader->SetUniform1i("textures_11", 11);
		m_Shader->SetUniform1i("textures_26", 26);
		m_Shader->SetUniform1i("textures_27", 27);
		m_Shader->SetUniform1i("textures_28", 28);
		m_Shader->SetUniform1i("textures_29", 29);
		m_Shader->SetUniform1i("textures_30", 30);
		m_Shader->SetUniform1i("textures_31", 31);
#endif

#else
		GLint texIDs[] =
		{
			0,   1,  2,  3,  4,  5,  6,  7,  8,  9,
			10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
			20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
			30, 31
		};

		m_Shader->SetUniform1iv("textures", texIDs, 32);
#endif
		m_Shader->Unbind();

	}

	Layer::~Layer()
	{
		delete m_Shader;
		delete renderer;
		for (uint i = 0; i < m_Renderables.size(); i++)
		{
			delete m_Renderables[i];
		}

	}
	
	Renderable2D* Layer::Add(Renderable2D* renderable)
		{
			m_Renderables.push_back(renderable);
			return renderable;

		}

	void Layer::Render()
	{
		m_Shader->Bind();
		renderer->Begin();
		
		for (const Renderable2D* renderable : m_Renderables)
			renderable->Submit(renderer);
		
		renderer->End();
		renderer->Flush();

	}

}}