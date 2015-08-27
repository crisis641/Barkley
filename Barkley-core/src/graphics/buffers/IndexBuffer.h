#pragma once

#include <barkley_types.h>
#include <barkleygl.h>

namespace barkley {
	namespace graphics {

		class IndexBuffer
		{
		private:
			GLuint m_BufferID;
			GLuint m_Count;
		public:
			IndexBuffer(short* data, uint count);
			IndexBuffer(uint* data, uint count);
			~IndexBuffer();


			void Bind() const;
			void Unbind() const;

			inline GLuint GetCount() const { return m_Count; }

		};


	}
}