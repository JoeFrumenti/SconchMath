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


	

public:
	static SoundManager& getInstance() {
		static SoundManager instance;
		return instance;
	}

	void playSound(std::string name, double pitch);
	void addSound(std::string name, std::string path);
	void playSong(std::string soundName);
	void setSong(std::string name);


};