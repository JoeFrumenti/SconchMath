#include "SoundManager.h"

void SoundManager::playSound(std::string name) {
	mySpeaker.Play(noises[name]);
}
void SoundManager::addSound(std::string name, std::string path) {
	const char* p = path.c_str();
	noises[name] = SoundBuffer::get()->addSoundEffect(p);
}
void SoundManager::playSong() {

}
void SoundManager::setSong(std::string name) {

}