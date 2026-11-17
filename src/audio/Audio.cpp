#include "Audio.h"
#include "raylib.h"
#include <cmath>

namespace Audio {
    static Sound clickSound;
    static Sound popSound;

    // Generate a clean, soft sound with fade-in to avoid harsh "drum" attack
    static Sound GenerateEnvelopeSound(float startFreq, float endFreq, float duration, float decay, float noiseAmount) {
        int sampleRate = 44100;
        int frameCount = (int)(sampleRate * duration);
        
        Wave wave = { 0 };
        wave.frameCount = frameCount;
        wave.sampleRate = sampleRate;
        wave.sampleSize = 16;
        wave.channels = 1;
        
        short* data = (short*)MemAlloc(frameCount * sizeof(short));
        float phase = 0.0f;
        
        for (int i = 0; i < frameCount; i++) {
            float t = (float)i / sampleRate;
            float progress = t / duration;
            
            // Gentle frequency sweep
            float freq = startFreq + (endFreq - startFreq) * progress;
            phase += 2.0f * PI * freq / sampleRate;
            
            // Soft attack (5ms fade-in) prevents harsh clicks
            float attack = (t < 0.005f) ? (t / 0.005f) : 1.0f;
            
            // Exponential decay
            float envelope = attack * std::exp(-t * decay);
            
            float sine = std::sin(phase);
            
            // Add a tiny bit of noise for texture (or none)
            float noise = ((float)GetRandomValue(-32767, 32767) / 32767.0f) * noiseAmount;
            
            data[i] = (short)((sine + noise) * envelope * 32767.0f * 0.7f);
        }
        wave.data = data;
        
        Sound sound = LoadSoundFromWave(wave);
        UnloadWave(wave);
        return sound;
    }

    void Init() {
        InitAudioDevice();
        
        // UI Click: Very short, soft sine "tick" (400Hz → 300Hz, 15ms)
        clickSound = GenerateEnvelopeSound(400.0f, 300.0f, 0.015f, 200.0f, 0.0f);
        
        // Target Pop: Slightly longer, wet-sounding sine sweep (250Hz → 120Hz, 70ms)
        popSound = GenerateEnvelopeSound(250.0f, 120.0f, 0.07f, 45.0f, 0.05f);
    }

    void Close() {
        UnloadSound(clickSound);
        UnloadSound(popSound);
        CloseAudioDevice();
    }

    void UpdateVolumes(float uiVol, float arenaVol, float popVol) {
        SetSoundVolume(clickSound, uiVol);
        SetSoundVolume(popSound, popVol);
        
        // arenaVol is reserved for future arena music
        (void)arenaVol;
    }

    void PlayClick() {
        PlaySound(clickSound);
    }

    void PlayPop() {
        PlaySound(popSound);
    }
}