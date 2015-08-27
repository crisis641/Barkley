#pragma once

#include <vector>
#include <barkleygl.h>

#include "Font.h"
#include "Texture.h"
#include "Mask.h"
#include "../maths/Maths.h"



namespace barkley { namespace graphics {
	
	class Renderable2D;


	class Renderer2D
	{
	protected:
		std::vector<maths::mat4> m_TransformationStack;
		const maths::mat4* m_TransformationBack;
		const Mask* m_Mask;
	protected:
		Renderer2D()
			: m_Mask(nullptr)
		{
			m_TransformationStack.push_back(maths::mat4::Identity());
			m_TransformationBack = &m_TransformationStack.back();
		}
	
	public:
		virtual ~Renderer2D() { }
		virtual void Begin() {}
		virtual void Submit(const Renderable2D* renderable) = 0;
		virtual void DrawString(const std::string& text, const maths::vec3& position, const Font& font, unsigned int color) { }
		virtual void End() {}
		virtual void Flush() = 0;

		void Push(const maths::mat4& matrix, bool override = false)
		{
			if (override)
			{
				m_TransformationStack.push_back(matrix);
			}
			else
			{
				m_TransformationStack.push_back(m_TransformationStack.back() * matrix);
			}
			m_TransformationBack = &m_TransformationStack.back();

		}

		void Pop()
		{
			if (m_TransformationStack.size() > 1)
				m_TransformationStack.pop_back();
			m_TransformationBack = &m_TransformationStack.back();

			//TODO: Add to log!;
		}

		virtual void SetMask(const Mask* mask) { m_Mask = mask;}

		

	};

}}