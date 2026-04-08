#pragma once
#define DLLEXPORT __declspec(dllexport)

extern "C" {
    struct Particle {
        float x, y, z;
        float vx, vy, vz;
        float life;
    };

    // Funciones que llamará Unity
    DLLEXPORT void InitParticles(int count);
    DLLEXPORT void UpdateParticles(float deltaTime, float speed);
    DLLEXPORT Particle* GetParticles();
    DLLEXPORT int GetParticleCount();
}