#pragma once

#include <vector>

#include <barkleygl.h>
#include <barkley_types.h>

#include "Buffer.h"

namespace barkley { namespace graphics {

	class VertexArray
	{
	private:
		GLuint m_ArrayID;
		std::vector<Buffer*> m_Buffers;
	public:
		VertexArray();
		~VertexArray();

		void AddBuffer(Buffer* buffer, uint index);
		void Bind() const;
		void Unbind() const;

	};
	
}}