#include <barkley.h>

using namespace barkley;
using namespace graphics;
using namespace audio;
using namespace maths;

class Game : public Barkley
{

private:
	Window* window;
	Shader* shader;
	Layer* layer;
	Label* fps;
	Sprite* sprite;
	vec3 mask;
	Label* debugInfo;
	
public:
	Game()
	{

	}

	~Game()
	{


	}

	void Init() override
	{

		window = CreateWindow("TestGame", 1280, 720);
		
		FontManager::Get()->SetScale(window->GetWidth() / 32.0f, window->GetHeight() / 18.0f);

		shader = ShaderFactory::DefaultShader();
		//shader = ShaderFactory::BasicLightShader();

		layer = new Layer(new BatchRenderer2D(tvec2<uint>(1280, 720)), shader, mat4::Orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

		TextureManager::Add(new Texture("test", "res/test.png"));
		Texture* t2 = new Texture("t", "res/tb.png");

		Texture* textures[] =
		{
			new Texture("t1", "res/test.png"),
			new Texture("t2", "res/tb.png"),
			new Texture("t3", "res/tc.png"),
			new Texture("t4", "res/test32.png")
		};

#ifdef BARKLEY_PLATFORM_WEB			
		sprite = new Sprite(0.0f, 0.0f, 4, 4, new Texture("test", "res/test.png"));
#else
		sprite = new Sprite(0.0f, 0.0f, 4, 4, TextureManager::Get("test"));
		//sprite = new Sprite(0.0f, 0.0f, 4, 4, t2);
		
		for (float y = -9.0f; y < 9.0f; y++)
		{
			for (float x = -16.0f; x < 16.0f; x++)
			{
				if (rand() % 4 == 0)
				{
					int r = rand() % 255;
					int col = 0xffff00 << 8 | r;
					layer->Add(new Sprite(x, y, 0.9f, 0.9f, col));
				}
				else
				{
					layer->Add(new Sprite(x, y, 0.9f, 0.9f, textures[rand() % 4]));
				}
			}
		}
		layer->Add(sprite);
#endif

		fps = new Label("", -15.5f, 8.0f, 0xffffffff);
		layer->Add(fps);

		debugInfo = new Label("", -15.5f, 6.8f, 0xffffffff);
		layer->Add(debugInfo);


		Texture::SetWrap(TextureWrap::CLAMP);
		
		layer->SetMask(new Mask(new Texture("Mask", "res/mask.png")));
		//layer->setMask(new Mask("mask", "res/mask.png"));

		//shader->enable();
		


#ifdef BARKLEY_PLATFORM_WEB
		SoundManagerAdd("testsound", "test2.wav");
#else
		SoundManager::Add(new Sound("testsound", "res/test2.wav"));
#endif

	}
	void Tick() override
	{
		fps->text = std::to_string(getFPS()) + " fps";
		BARKLEY_INFO(getUPS(), " ups, ", getFPS(), " fps");
	}

	void Update() override
	{
		//std::cin.get();
		float speed = 0.5f;
		if (window->IsKeyPressed(GLFW_KEY_UP))
		{
			sprite->position.y += speed;
		}
		if (window->IsKeyPressed(GLFW_KEY_DOWN))
		{
			sprite->position.y -= speed;
		}
		if (window->IsKeyPressed(GLFW_KEY_LEFT))
		{
			sprite->position.x -= speed;
		}
		if (window->IsKeyPressed(GLFW_KEY_RIGHT))
		{
			sprite->position.x += speed;
		}

		if (window->IsKeyPressed(GLFW_KEY_UP))
		{
			mask.y += speed * 0.01f;
		}
		if (window->IsKeyPressed(GLFW_KEY_DOWN))
		{
			mask.y -= speed * 0.01f;
		}
		if (window->IsKeyPressed(GLFW_KEY_LEFT))
		{
			mask.x -= speed * 0.01f;
		}
		if (window->IsKeyPressed(GLFW_KEY_RIGHT))
		{
			mask.x += speed * 0.01f;
		}

		if (window->IsKeyPressed(GLFW_KEY_V))
		{
			window->SetVsync(!window->IsVsync());
		}




		if (window->IsKeyPressed(GLFW_KEY_P))
		{
#ifdef BARKLEY_PLATFORM_WEB
			SoundManagerPlay("testsound");
#else
			SoundManager::Get("testsound")->Play();
#endif
		}

		if (window->IsKeyPressed(GLFW_KEY_1))
			((BatchRenderer2D*)layer->renderer)->SetRenderTarget(RenderTarget::SCREEN);
		if (window->IsKeyPressed(GLFW_KEY_2))
			((BatchRenderer2D*)layer->renderer)->SetRenderTarget(RenderTarget::BUFFER);
		
		static maths::vec3 scale(1, 1, 1);
		maths::tvec2<uint> size = ((BatchRenderer2D*)layer->renderer)->GetViewportSize();
		if (window->IsKeyPressed(GLFW_KEY_O))
		{
			size.x+= 16;
			size.y+= 9;
			//scale.x += speed;
			//scale.y += speed;
		}
		if (window->IsKeyPressed(GLFW_KEY_L))
		{
			size.x-=16;
			size.y-=9;
			//scale.x -= speed;
			//scale.y -= speed;
		}

		if (size.x > 10000)
			size.x = 0;
		if (size.y > 10000)
			size.y = 0;


		maths::vec2 mouse_position = window->GetMousePosition();
		
		shader->SetUniformMat4("mask_matrix", maths::mat4::Translate(mask) * maths::mat4::Scale(scale));
		shader->SetUniform2f("light_pos", maths::vec2((float)(mouse_position.x * 32.0f / window->GetWidth() - 16.0f), (float)(9.0f - mouse_position.y * 18.0f / window->GetHeight())));

		debugInfo->text = std::to_string(size.x) + ", " + std::to_string(size.y);
		((BatchRenderer2D*)layer->renderer)->SetViewportSize(size);
		
	}

	void Render() override
	{
		
		layer->Render();
	}

};

int main()
{
	Game game;
	game.Start();
	return 0;
}