#pragma once

#ifdef BARKLEY_PLATFORM_WEB
	#include <emscripten\emscripten.h>
#endif

#include "graphics/Label.h"
#include "graphics/Sprite.h"
#include "graphics/Renderer2d.h"
#include "graphics/BatchRenderer2D.h"
#include "graphics/Window.h"
#include "graphics/layers/Layer.h"
#include "graphics/layers/Group.h"
#include "graphics/TextureManager.h"
#include "graphics/Window.h"


#include "graphics/shaders/Shader.h"
#include "graphics/shaders/ShaderFactory.h"

#include "audio/Sound.h"
#include "audio/SoundManager.h"

#include "maths/Maths.h"
#include "utils/Log.h"
#include "utils/Timer.h"

#ifdef BARKLEY_PLATFORM_WEB

static void dispatch_main(void* fp)
{
	std::function<void()>* func = (std::function<void()>*)fp;
	(*func)();
}


#endif


namespace barkley{

	class Barkley
	{
	private:
		graphics::Window* m_Window;
		Timer* m_Timer;
		unsigned int m_Frames;
		unsigned int m_FramesPerSecond, m_UpdatesPerSecond;

	public:

		void Start()
		{
			Init();
			Run();
		}

	protected:

		Barkley()
			: m_FramesPerSecond(0), m_UpdatesPerSecond(0)
		{

		}

		virtual ~Barkley() 
		{ 
			delete m_Window;
			delete m_Timer;
		}

		graphics::Window* CreateWindow(const char *title, int width, int height)
		{
			m_Window = new graphics::Window(title, width, height);
			return m_Window;
		}


		// Runs once upon initilization
		virtual void Init() = 0;
		// Runs once per second
		virtual void Tick() { }
		// Runs 60 times per second
		virtual void Update() { }
		// Runs as fast as possible (unless vsync is enabled)
		virtual void Render() = 0;

		const unsigned int getFPS() const { return m_FramesPerSecond; }
		const unsigned int getUPS() const { return m_UpdatesPerSecond; }

	private:
		void Run()
		{
			float timer = 0.0f;
			float updateTimer = 0.0f;
			float updateTick = 1.0f / 60.0f;
			int updates = 0;
			m_Frames = 0;
		
			m_Timer = new Timer();

#ifdef BARKLEY_PLATFORM_WEB
			std::function<void()> mainLoop = [&]() {
#else
			while (!m_Window->Closed())
			{
#endif
				m_Window->Clear();

				if (m_Timer->Elapsed() - updateTimer > updateTick)
				{
					m_Window->UpdateInput();
					Update();
					updates++;
					updateTimer += updateTick;
				}

				Render();
				m_Frames++;
				m_Window->Update();


				if (m_Timer->Elapsed() - timer > 1.0f)
				{
					timer += 1.0f;
					m_FramesPerSecond = m_Frames;
					m_UpdatesPerSecond = updates;
					m_Frames = 0;
					updates = 0;
					Tick();
				}
#ifdef BARKLEY_PLATFORM_WEB
			};
			emscripten_set_main_loop_arg(dispatch_main, &mainLoop, 0, 1);
#else
			}
#endif

		}
	};
}