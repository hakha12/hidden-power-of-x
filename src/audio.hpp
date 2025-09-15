#ifndef __AUDIO_HPP__
#define __AUDIO_HPP__

#include "common.hpp"

class Audio {
	public:
		Audio();
		~Audio();

		void Add(const std::string& name, const std::string& fileName);
		void Play(const std::string& name);

	private:
		void Init();

		std::unordered_map<std::string, Sound> sounds;
};

#endif