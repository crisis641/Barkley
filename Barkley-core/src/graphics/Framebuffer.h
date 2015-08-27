#pragma once

#include <barkleygl.h>
#include <barkley_types.h>

#include  "maths/vec4.h"
#include "maths/tvec2.h"

#include "Texture.h"

namespace barkley { namespace graphics{

	class FrameBuffer
	{
	private:
		struct FramebufferData
		{
			GLuint framebufferID;
			GLuint depthbufferID;
		};
		Texture* m_Texture;
		FramebufferData m_Data;
		maths::tvec2<uint> m_Size;
		uint& m_Width;
		uint& m_Height;

		maths::vec4 m_ClearColor;

	public:
		FrameBuffer(const maths::tvec2<uint>& size);
		FrameBuffer(uint width, uint height);
		~FrameBuffer();

		void Bind() const;
		void Clear();

		inline const maths::tvec2<uint>& getSize() const { return m_Size; }
		inline const uint GetWidth() const { return m_Width; }
		inline const uint GetHeight() const { return m_Height; }
		inline const Texture* GetTexture() const { return m_Texture; }

		inline void SetClearColor(const maths::vec4& color) { m_ClearColor = color; }

	private:
		void Create(uint width, uint height);


	};


}}