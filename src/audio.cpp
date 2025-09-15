#include "audio.hpp"


Audio::~Audio(){
	for (auto i: sounds){
		UnloadSound(i.second);
	}
}

void Audio::Add(const std::string& name, const std::string& fileName){
	std::string resourceDir;
	#if defined(WINDOWS)
		resourceDir = "assets\\";
	#else
		resourceDir = "assets/";
	#endif

	std::string filePath = resourceDir + fileName;

	Sound sound = LoadSound(filePath.c_str());
	
	sounds.emplace(std::make_pair(name, sound));
}

void Audio::Play(const std::string& name){
	auto sound = sounds.find(name);

	if (sound == sounds.end()) return;

	PlaySound(sound->second);
}

void Audio::Init(){
	if (isAudioOn) return;

	InitAudioDevice();

	isAudioOn = true;
}