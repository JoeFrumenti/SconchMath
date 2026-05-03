#include "SoundManager.h"
#include <thread>
#include <chrono>

std::vector<double> pitches = {0,1,2,3,4,5,6,7};
int pitchIndex = 0;
void SoundManager::playSong(std::string soundName) {

    
    
    playSound(soundName, pitches[pitchIndex]);
    if (++pitchIndex >= pitches.size())
        pitchIndex = 0;
}

//alSourcef(noises[soundName], AL_PITCH, pow(2.0, pitches[pitchIndex++] / 12.0));

void SoundManager::playSound(std::string name, double pitch) {
    ALuint buffer = noises[name];
    std::thread([buffer, pitch]() {
        SoundSource speaker;
        alSourcef(speaker.getSource(), AL_PITCH, pow(2.0, pitch/ 12.0));  // set on the source
        speaker.Play(buffer);
        ALint state;
        do {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            alGetSourcei(speaker.getSource(), AL_SOURCE_STATE, &state);
        } while (state == AL_PLAYING);
        }).detach();
}

void SoundManager::addSound(std::string name, std::string path) {
	const char* p = path.c_str();
	noises[name] = SoundBuffer::get()->addSoundEffect(p);
}

void SoundManager::setSong(std::string name) {

}
