
#if 0

#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/maths/maths.h"

#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"

#include "src/graphics/renderer2d.h"
#include "src/graphics/batchrenderer2d.h"

#include "src/graphics/static_sprite.h"
#include "src/graphics/sprite.h"
#include "src/utils/timer.h"



#include "src/graphics/layers/group.h"
#include "src/graphics/texture.h"
#include "src/graphics/label.h"

#include "src\graphics\font_manager.h"

#include "src\audio\sound_manager.h"


#include "tilelayer.h"

#define BATCH_RENDERER 1


int main()
{
	using namespace barkley;
	using namespace graphics;
	using namespace audio;
	using namespace maths;

	Window window("Barkley!", 960, 540);
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader* s = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader& shader = *s;
	shader.enable();
	shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));

	//Texture* texture = new Texture("test2.png");
	
	TileLayer layer(&shader);
	
	Texture* textures[] =
	{
		new Texture("test.png"),
		new Texture("tb.png"),
		new Texture("tc.png")
	};
	
	
	for (float y = -9.0f; y < 9.0f; y++)
	{
		for (float x = -16.0f; x < 16.0f; x++)
		{
			if (rand() % 4 == 0)
			{
				int r = rand() % 255;
				int col = 0xffff00 << 8| r;
				layer.add(new Sprite(x, y, 0.9f, 0.9f, col));
			}
			else
			{
				layer.add(new Sprite(x, y, 0.9f, 0.9f, textures[rand() % 3]));
			}
		}
	}

	//FontManager::add(new Font("SourceSansPro200", "SourceSansPro-Light.ttf", 200));

	Group* g = new Group(maths::mat4::translation(maths::vec3(-15.0f, 7.0f, 0.0f)));

	Label* fps = new Label("", 0.5f, 0.5f, "SourceSansPro", 0xffffffff);
	g->add(new Sprite(0, 0, 4.7f, 1.5f, 0xffffff05));
	g->add(fps);
	
	
	layer.add(g);

	shader.setUniformMat4("pr_matrix", maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

	SoundManager::add(new Sound("HI", "test.wav"));
	SoundManager::add(new Sound("HI2", "test2.wav"));
	SoundManager::get("HI")->play();

	Timer time;
	float timer = 0;
	unsigned int frames = 0;
	float colortime = 0.0f;
	float gain = 0.5f;
	SoundManager::get("HI")->setGain(gain);
	
	while (!window.closed())
	{
		colortime += 0.01f;
		window.clear();
		double x, y;
		window.getMousePosition(x, y);
		shader.setUniform2f("light_pos", vec2((float)(x * 32.0f / window.getWidth() - 16.0f), (float)(9.0f - y * 18.0f / window.getHeight())));
		layer.render();
		
		const std::vector<Renderable2D*>& rs = layer.getRenderables();

		for (int i = 0; i < rs.size(); i++)
		{
			float c = sin(colortime) / 2 + 0.5;
			rs[i]->setColor(maths::vec4(c, 0, 1, 1));
		}

		if (window.isKeyTyped(GLFW_KEY_P))
		{
			SoundManager::get("HI2")->play();
		}
		if (window.isKeyTyped(GLFW_KEY_S))
		{
			SoundManager::get("HI2")->stop();
		}
		if (window.isKeyTyped(GLFW_KEY_1))
		{
			SoundManager::get("HI2")->pause();
		}
		if (window.isKeyTyped(GLFW_KEY_2))
		{
			SoundManager::get("HI2")->resume();
		}
		if (window.isKeyTyped(GLFW_KEY_L))
		{
			SoundManager::get("HI2")->loop();
		}
		if (window.isKeyTyped(GLFW_KEY_UP))
		{
			gain = SoundManager::get("HI2")->getGain();
			gain += 0.1f;
			SoundManager::get("HI2")->setGain(gain);
		}
		if (window.isKeyTyped(GLFW_KEY_DOWN))
		{
			gain = SoundManager::get("HI2")->getGain();
			gain -= 0.1f;
			SoundManager::get("HI2")->setGain(gain);
		}

		window.update();
		frames++;
		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			fps->text = std::to_string(frames) + " fps";
			printf("%d fps\n", frames);
			frames = 0;
		}
	}
	
	for (int i = 0; i < 3; i++)
	{
		delete textures[i];
	}

	
	return 0;
}
#endif


