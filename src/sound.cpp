#include "sound.h"
#include <cmath>

Sound::Sound() : initialized(false), beeping(false), device(0), activeBeep(false) {
    if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {
        std::cerr << "Erro ao inicializar áudio SDL: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_zero(want);
    want.freq = 44100;
    want.format = AUDIO_F32SYS;
    want.channels = 1;
    want.samples = 512;
    want.callback = audioCallback;
    want.userdata = this;

    device = SDL_OpenAudioDevice(nullptr, 0, &want, &have, 0);
    if (!device) {
        std::cerr << "Erro ao abrir dispositivo de áudio: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_PauseAudioDevice(device, 0); // inicia o áudio
    initialized = true;
}

Sound::~Sound() {
    if (initialized)
        SDL_CloseAudioDevice(device);
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

// -------------------------------------------------------------
void Sound::audioCallback(void* userdata, Uint8* stream, int len) {
    Sound* self = static_cast<Sound*>(userdata);
    float* buffer = reinterpret_cast<float*>(stream);
    int samples = len / sizeof(float);

    if (!self->activeBeep.load()) {
        std::fill(buffer, buffer + samples, 0.0f);
        return;
    }

    static float phase = 0.0f;
    float freq = 440.0f; // tom A padrão
    float phaseInc = 2.0f * M_PI * freq / 44100.0f;

    for (int i = 0; i < samples; ++i) {
        buffer[i] = 0.2f * sin(phase);
        phase += phaseInc;
        if (phase >= 2.0f * M_PI) phase -= 2.0f * M_PI;
    }
}

// -------------------------------------------------------------
void Sound::startBeep() { activeBeep = true; }
void Sound::stopBeep()  { activeBeep = false; }

void Sound::update(bool active) {
    if (active && !beeping) {
        beeping = true;
        startBeep();
    } else if (!active && beeping) {
        beeping = false;
        stopBeep();
    }
}
