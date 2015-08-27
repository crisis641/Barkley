#pragma once

#include <iostream>

#include <barkleygl.h>

#include <GLFW/glfw3.h>

#include "../maths/Vec2.h"
#include "FontManager.h"
#include "TextureManager.h"
#include "../audio/SoundManager.h"


namespace barkley { namespace graphics {

#define MAX_KEYS	1024
#define MAX_BUTTONS 32

	class Window
	{

	private:
		

		int m_Width, m_Height;
		const char *m_Title;
		GLFWwindow *m_Window;
		bool m_Closed;

		bool m_Keys[MAX_KEYS];
		bool m_KeyState[MAX_KEYS];
		bool m_KeyTyped[MAX_KEYS];
		bool m_MouseButtons[MAX_BUTTONS];
		bool m_MouseButtonsState[MAX_BUTTONS];
		bool m_MouseButtonsClicked[MAX_BUTTONS];
	

		maths::vec2 m_MousePosition;
		bool m_Vsync;

	public:
		Window(const char *title, int width, int height);
		~Window();
		void Clear() const;
		void Update();
		void UpdateInput();
		bool Closed() const;

		inline int GetWidth() const { return m_Width; };
		inline int GetHeight() const { return m_Height; };

		bool IsKeyPressed(unsigned int keycode) const;
		bool IsKeyTyped(unsigned int keycode) const;
		bool IsMouseButtonPressed(unsigned int button) const;
		bool IsMouseButtonClicked(unsigned int button) const;
		const maths::vec2& GetMousePosition() const;

		void SetVsync(bool enabled);
		bool IsVsync() const { return m_Vsync; }

	private:
		bool Init();
		friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		friend void window_Resize(GLFWwindow* window, int width, int height);
	};

}}