#pragma once

#include "SoundDevice.h"
#include "SoundBuffer.h"
#include "SoundSource.h"

#include <map>
#include <string>
#include <vector>

class SoundManager {
private:

	SoundDevice* mysounddevice = SoundDevice::get();
	uint32_t sound2;

	SoundSource mySpeaker;

	std::map<std::string, uint32_t> noises;
	std::vector<float> notes;

	int nextNote = 0;

public:
	static SoundManager& getInstance() {
		static SoundManager instance;
		return instance;
	}

	void playSound(std::string name);
	void addSound(std::string name, std::string path);
	void playSong();
	void setSong(std::string name);


};