#include "SoundManager.h"
#include <thread>
#include <chrono>
void SoundManager::playSound(std::string name) {
    ALuint buffer = noises[name];
    std::thread([buffer]() {
        SoundSource speaker;
        speaker.Play(buffer);

        // wait until done playing
        ALint state;
        do {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            alGetSourcei(speaker.getSource(), AL_SOURCE_STATE, &state);
        } while (state == AL_PLAYING);

        }).detach(); // detach so it cleans up automatically
}
void SoundManager::addSound(std::string name, std::string path) {
	const char* p = path.c_str();
	noises[name] = SoundBuffer::get()->addSoundEffect(p);
}
void SoundManager::playSong() {

}
void SoundManager::setSong(std::string name) {

}

/*pitch = rand() % pitches.size();
			alSourcef(sound1, AL_PITCH, pow(2.0, pitches[pitch] / 12.0));*/