#include "SoundManager.h"


namespace barkley{ namespace audio {

#ifdef BARKLEY_PLATFORM_WEB
#else
	ga_Mixer*	SoundManager::m_Mixer = nullptr;
	gau_Manager* SoundManager::m_Manager = nullptr;
#endif

	std::vector<Sound*> SoundManager::m_Sounds;

	void SoundManager::Init()
	{
#ifdef BARKLEY_PLATFORM_WEB
		EM_ASM(
		Module.SoundManager = { };
		Module.SoundManager.m_Sounds = { };
		Module.SoundManagerAdd = function(name, filename) { /*alert('Loading audio file ' + name + ' path=' + filename + '!');*/ Module.SoundManager.m_Sounds[name] = new Audio(filename); };
		Module.SoundManagerPlay = function(name) { Module.SoundManager.m_Sounds[name].play(); };
		Module.SoundManagerPause = function(name) { Module.SoundManager.m_Sounds[name].pause(); };
		Module.SoundManagerStop = function(name) { Module.SoundManagerPause(name); Module.SoundManager.m_Sounds[name].currentTime = 0; Module.SoundManager.m_Sounds[name].loop = false; };
		Module.SoundManagerLoop = function(name) { Module.SoundManager.m_Sounds[name].play(); Module.SoundManager.m_Sounds[name].loop = true; };
		Module.SoundManagerSetGain = function(name, gain) { Module.SoundManager.m_Sounds[name].volume = gain; };
		);
#else
		gc_initialize(0);
		m_Manager = gau_manager_create();
		m_Mixer = gau_manager_mixer(m_Manager);
#endif
	}

	Sound* SoundManager::Add(Sound* sound)
	{
		m_Sounds.push_back(sound);
#ifdef BARKLEY_PLATFORM_WEB
		SoundManagerAdd(sound->GetName().c_str(), sound->GetFileName().c_str());
#endif
		return sound;
	}

	Sound* SoundManager::Get(const std::string& name)
	{
		for (Sound* sound : m_Sounds)
		{
			if (sound->GetName() == name)
				return sound;
		}
		return nullptr;
	}

	void SoundManager::Update()
	{
#ifdef BARKLEY_PLATFORM_WEB
#else
		gau_manager_update(m_Manager);
#endif
	}


	void SoundManager::Clean()
	{
		for (uint i = 0; i < m_Sounds.size(); i++)
			delete m_Sounds[i];
#ifdef BARKLEY_PLATFORM_WEB
#else
		gau_manager_destroy(m_Manager);
		gc_shutdown();
#endif

	}
}}