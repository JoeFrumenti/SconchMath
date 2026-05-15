#include "SoundManager.h"
#include <thread>
#include <chrono>

std::atomic<int> SoundManager::activeSoundCount = 0;

std::vector<std::string> pitches = { "A5", "D5", "A#4", "G4", "G5","D5","A#4","G4",
                                    "F#5", "D5", "A#4", "G4", "G5","D5","A#4","G4",
                                    "G5", "C5", "A4", "F4", "F5", "C5", "A4", "F4",
                                    "E5", "C5", "A4", "F4",  "F5", "C5", "A4", "F4",
                                    "F5", "A#4", "G4", "E4","E5","D#5", "G4", "D#4",
                                    "E5", "G4", "F4", "D4", "D5", "A4", "F4", "D4",
                                    "C#5","A4","F4", "D4","D5", "A4", "F4", "D4",
                                    "C#5","A4","F4", "D4", "D5", "A4", "F4", "D4"};

std::map<std::string, double> noteMap = {
    // Octave 4
    {"C4",  -12}, {"C#4", -11}, {"D4",  -10}, {"D#4", -9},
    {"E4",  -8},  {"F4",  -7},  {"F#4", -6},  {"G4",  -5},
    {"G#4", -4},  {"A4",  -3},  {"A#4", -2},  {"B4",  -1},
    // Octave 5
    {"C5",   0},  {"C#5",  1},  {"D5",   2},  {"D#5",  3},
    {"E5",   4},  {"F5",   5},  {"F#5",  6},  {"G5",   7},
    {"G#5",  8},  {"A5",   9},  {"A#5", 10},  {"B5",  11},
    // Octave 6
    {"C6",  12},  {"C#6", 13},  {"D6",  14},  {"D#6", 15},
    {"E6",  16},  {"F6",  17},  {"F#6", 18},  {"G6",  19},
    {"G#6", 20},  {"A6",  21},  {"A#6", 22},  {"B6",  23},
};


int pitchIndex = 0;


void SoundManager::playImportantSound(std::string name) {
    alGenSources(1, &importantSource);
    alSourcei(importantSource, AL_BUFFER, noises[name]);
    alSourcef(importantSource, AL_GAIN, 1.0f);
    alSourcePlay(importantSource);
}

void SoundManager::playSong(std::string soundName) {
    playSound(soundName, noteMap[pitches[pitchIndex]]);
    if (++pitchIndex >= pitches.size())
        pitchIndex = 0;
}

void SoundManager::updateMasterGain() {
    int active = activeSoundCount.load();
    float master = 1.0f / sqrtf((float)std::max(1, active));
    alListenerf(AL_GAIN, master);
}
void SoundManager::playSound(std::string name, double pitch) {
    if (name == "coin") {
        auto now = std::chrono::steady_clock::now();
        auto& last = lastPlayed[name];
        if (now - last < std::chrono::milliseconds(50)) return; // skip if played recently
        last = now;
    }
    ALuint buffer = noises[name];
    std::lock_guard<std::mutex> lock(soundsMutex);

    // prune finished voices
    activeSounds.erase(
        std::remove_if(activeSounds.begin(), activeSounds.end(), [](const ActiveSound& s) {
            ALint state;
            alGetSourcei(s.source, AL_SOURCE_STATE, &state);
            return state != AL_PLAYING;
            }),
        activeSounds.end()
    );

    ALuint source;
    if (activeSounds.size() >= MAX_VOICES) {
        // prefer to steal the oldest, but skip if it just started
        auto& oldest = activeSounds.front();
        auto age = std::chrono::steady_clock::now() - oldest.startTime;
        if (age < std::chrono::milliseconds(100)) {
            return; // don't play rather than cause a click
        }
        source = oldest.source;
        alSourceStop(source);
        activeSounds.erase(activeSounds.begin());
    }
    else {
        // grab next unused source from pool
        // find one not currently in activeSounds
        for (int i = 0; i < MAX_VOICES; i++) {
            bool inUse = false;
            for (auto& s : activeSounds) {
                if (s.source == sourcePool[i]) { inUse = true; break; }
            }
            if (!inUse) { source = sourcePool[i]; break; }
        }
    }

    alSourcef(source, AL_GAIN, 0.0f);  //  changed from 1.0f
    alSourcef(source, AL_PITCH, pow(2.0, pitch / 12.0));
    alSourcei(source, AL_BUFFER, buffer);
    alSourcePlay(source);
    activeSounds.push_back({ source, std::chrono::steady_clock::now() });

    std::thread([source]() {
        int steps = 32;
        for (int i = 1; i <= steps; i++) {
            alSourcef(source, AL_GAIN, i / (float)steps);
            std::this_thread::sleep_for(std::chrono::microseconds(500));
        }
        }).detach();


}

void SoundManager::fadeOutAndStop(ALuint source) {
    int steps = 16;
    for (int i = steps; i >= 0; i--) {
        alSourcef(source, AL_GAIN, i / (float)steps);
        std::this_thread::sleep_for(std::chrono::microseconds(500)); // 8ms total
    }
    alSourceStop(source);
}

/*vHEREv*/
void SoundManager::addSound(std::string name, std::string path) {
	const char* p = path.c_str();
	noises[name] = SoundBuffer::get()->addSoundEffect(p);
}
/*^HERE^*/
SoundManager::SoundManager() {
    for (int i = 0; i < MAX_VOICES; i++) {
        alGenSources(1, &sourcePool[i]);
    }
    noises["announce"] = SoundBuffer::get()->addSoundEffect("C:/Users/joefr/source/repos/SconchMath/assets/audio/thiefvsslime.mp3");

    noises["cork"] = SoundBuffer::get()->addSoundEffect("C:/Users/joefr/source/repos/SconchMath/assets/audio/corkloud.wav");
    noises["freeze"] = SoundBuffer::get()->addSoundEffect("C:/Users/joefr/source/repos/SconchMath/assets/audio/freeze.wav");
    noises["unfreeze"] = SoundBuffer::get()->addSoundEffect("C:/Users/joefr/source/repos/SconchMath/assets/audio/unfreeze.wav");
    noises["slimewins"] = SoundBuffer::get()->addSoundEffect("C:/Users/joefr/source/repos/SconchMath/assets/audio/slimewins.mp3");
    noises["icewins"] = SoundBuffer::get()->addSoundEffect("C:/Users/joefr/source/repos/SconchMath/assets/audio/icewins.mp3");
    noises["thiefwins"] = SoundBuffer::get()->addSoundEffect("C:/Users/joefr/source/repos/SconchMath/assets/audio/thiefwins.mp3");
    noises["powerup"] = SoundBuffer::get()->addSoundEffect("C:/Users/joefr/source/repos/SconchMath/assets/audio/powerup.wav");
    noises["powerdown"] = SoundBuffer::get()->addSoundEffect("C:/Users/joefr/source/repos/SconchMath/assets/audio/powerdown.wav");
    noises["bonk"] = SoundBuffer::get()->addSoundEffect("C:/Users/joefr/source/repos/SconchMath/assets/audio/bonk.mp3");

}
void SoundManager::setSong(std::string name) {

}

