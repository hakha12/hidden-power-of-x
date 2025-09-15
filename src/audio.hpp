#ifndef __AUDIO_HPP__
#define __AUDIO_HPP__

#include "common.hpp"

class Audio {
	public:
		Audio():isAudioOn(false){}
		~Audio();

		void Init();

		void Add(const std::string& name, const std::string& fileName);
		void Play(const std::string& name);

	private:
		bool isAudioOn;

		std::unordered_map<std::string, Sound> sounds;
};

#endif