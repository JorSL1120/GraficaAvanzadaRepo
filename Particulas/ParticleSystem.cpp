#include "ParticlesSystem.h"
#include <vector>
#include <cmath>

std::vector<Particle> particles;
int particleCount = 0;

extern "C" {
    void InitParticles(int count) {
        particles.clear();
        particleCount = count;
        for (int i = 0; i < count; ++i) {
            Particle p;
            p.x = 0; p.y = 0; p.z = 0;
            // Movimiento aleatorio inicial
            p.vx = ((float)rand() / RAND_MAX) * 2 - 1;
            p.vy = ((float)rand() / RAND_MAX) * 2;
            p.vz = ((float)rand() / RAND_MAX) * 2 - 1;
            p.life = 5.0f;
            particles.push_back(p);
        }
    }

    void UpdateParticles(float deltaTime, float speed) {
        for (auto& p : particles) {
            p.x += p.vx * deltaTime * speed;
            p.y += p.vy * deltaTime * speed;
            p.z += p.vz * deltaTime * speed;
            p.life -= deltaTime;

            // Reiniciar partícula si muere
            if (p.life <= 0) {
                p.x = p.y = p.z = 0;
                p.life = 5.0f;
            }
        }
    }

    Particle* GetParticles() {
        return particles.data();
    }

    int GetParticleCount() {
        return particleCount;
    }
}