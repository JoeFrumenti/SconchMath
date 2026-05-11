#pragma once

#include "SoundDevice.h"
#include "SoundBuffer.h"
#include "SoundSource.h"

#include <map>
#include <string>
#include <vector>
#include <atomic>
#include <mutex>
#include <unordered_map>

// In your header
struct ActiveSound {
	ALuint source;
	std::chrono::steady_clock::time_point startTime;
};



class SoundManager {
private:
	static std::atomic<int> activeSoundCount;
	SoundDevice* mysounddevice = SoundDevice::get();
	uint32_t sound2;
	SoundSource mySpeaker;

	std::map<std::string, uint32_t> noises;
	std::vector<float> notes;

	std::unordered_map<std::string, std::chrono::steady_clock::time_point> lastPlayed;

	std::mutex soundsMutex;
	std::vector<ActiveSound> activeSounds;
	const int MAX_VOICES = 10;
	ALuint sourcePool[10];
	ALuint importantSource;

	float loserScale = 1.0f;
	

public:
	static SoundManager& getInstance() {
		static SoundManager instance;
		return instance;
	}

	void playSound(std::string name, double pitch);
	void addSound(std::string name, std::string path);
	void playSong(std::string soundName);
	void setSong(std::string name);
	void updateMasterGain();
	void fadeOutAndStop(ALuint source);
	SoundManager();
	void playImportantSound(std::string);

};