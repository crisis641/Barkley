#include "Window.h"
#include "../embedded/Embedded.h"



namespace barkley { namespace graphics {

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	void window_Resize(GLFWwindow* window, int width, int height);

	Window::Window(const char *title, int width, int height)
	{
		m_Title = title;
		m_Width = width;
		m_Height = height;
		if (!Init())
		{
			glfwTerminate();
		}
#ifdef BARKLEY_PLATFORM_WEB
		FontManager::Add(new Font("SourceSansPro", "res/SourceSansPro-Light.ttf", 32));
#else
		FontManager::Add(new Font("SourceSansPro", internal::DEFAULT_FONT, internal::DEFAULT_FONT_SIZE, 32));
#endif


#ifdef BARKLEY_PLATFORM_WEB
		FreeImage_Initialise();
#else
#endif
		audio::SoundManager::Init();
		for (int i = 0; i < MAX_KEYS; i++)
		{
			m_Keys[i] = false;
			m_KeyState[i] = false;
			m_KeyTyped[i] = false;
		}
		for (int i = 0; i < MAX_BUTTONS; i++)
		{
			m_MouseButtons[i] = false;
			m_MouseButtonsState[i] = false;
			m_MouseButtonsClicked[i] = false;
		}
	}

	Window::~Window()
	{
		FontManager::Clean();
		TextureManager::Clean();
		audio::SoundManager::Clean();
		glfwTerminate();
	}

	bool Window::Init()
	{
		if (!glfwInit())
		{
			BARKLEY_FATAL("[Window] Failed to initilize GLFW");
			return false;
		}
			
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
		if (!m_Window)
		{
			BARKLEY_FATAL("[Window] Failed to craete GLFW window!");
			return false;
		}
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetFramebufferSizeCallback(m_Window, window_Resize);
		glfwSetKeyCallback(m_Window, key_callback);
		glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
		glfwSetCursorPosCallback(m_Window, cursor_position_callback);
		

#ifndef BARKLEY_PLATFORM_WEB
		if (glewInit() != GLEW_OK)
		{
			BARKLEY_FATAL("[Window] Could not initilize GLEW!");
			return false;
		}
#endif
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		BARKLEY_INFO("[Window] OpenGL Version: ", glGetString((GL_VERSION)));

		return true;

	}

	bool Window::IsKeyPressed(unsigned int keycode) const
	{
		//TODO: Log this
		if (keycode >= MAX_KEYS)
			return false;

		return m_Keys[keycode];

	}

	bool Window::IsKeyTyped(unsigned int keycode) const
	{
		//TODO: Log this
		if (keycode >= MAX_KEYS)
			return false;

		return m_KeyTyped[keycode];
	}

	bool Window::IsMouseButtonPressed(unsigned int button) const
	{
		//TODO: Log this
		if (button >= MAX_BUTTONS)
			return false;

		return m_MouseButtons[button];
	}

	bool Window::IsMouseButtonClicked(unsigned int button) const
	{
		//TODO: Log this
		if (button >= MAX_BUTTONS)
			return false;

		return m_MouseButtonsClicked[button];

	}

	const maths::vec2& Window::GetMousePosition() const
	{
		return m_MousePosition;
	}

	void Window::SetVsync( bool enabled)
	{
		glfwSwapInterval((double)enabled);
		m_Vsync = enabled;
	}
	void Window::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

	}

	void Window::Update()
	{
	
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
			BARKLEY_FATAL("[Window] OpenGL Error: ", error);

		glfwSwapBuffers(m_Window);
		glfwPollEvents();
		
		audio::SoundManager::Update();
	}

	void Window::UpdateInput()
	{
		for (int i = 0; i < MAX_KEYS; i++)
			m_KeyTyped[i] = m_Keys[i] && !m_KeyState[i];
		
		for (int i = 0; i < MAX_BUTTONS; i++)
			m_MouseButtonsClicked[i] = m_MouseButtons[i] && !m_MouseButtonsState[i];

		memcpy(m_KeyState, m_Keys, MAX_KEYS);
		memcpy(m_MouseButtonsState, m_MouseButtons, MAX_BUTTONS);
	}

	bool Window::Closed() const
		{
		return glfwWindowShouldClose(m_Window) == 1;
		}

	void window_Resize(GLFWwindow *window, int width, int height)
	{
		glViewport(0, 0, width, height);
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_Width = width;
		win->m_Height = height;

	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		
			win->m_Keys[key] = action != GLFW_RELEASE;
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_MouseButtons[button] = action != GLFW_RELEASE;

	}

	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_MousePosition.x = (float) xpos;
		win->m_MousePosition.y = (float) ypos;

	}
}}