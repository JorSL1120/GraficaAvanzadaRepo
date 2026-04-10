#include "ParticlesSystem.h"
#include <vector>
#include <cstdlib>

std::vector<Particle> particles;
int particleCount = 0;

// Función de ayuda para generar la velocidad formando la letra "E"
void AsignarVelocidadFormaE(Particle& p) {
    int part = rand() % 4; // Elegir aleatoriamente uno de los 4 trazos de la "E"
    float targetX = 0, targetY = 0;

    if (part == 0) { // 1. Línea vertical izquierda (espalda)
        targetX = -1.0f;
        targetY = ((float)rand() / RAND_MAX) * 2.0f - 1.0f; // y va de -1 a 1
    } 
    else if (part == 1) { // 2. Línea horizontal superior
        targetX = ((float)rand() / RAND_MAX) * 2.0f - 1.0f; // x va de -1 a 1
        targetY = 1.0f;
    } 
    else if (part == 2) { // 3. Línea horizontal de en medio (más corta)
        targetX = ((float)rand() / RAND_MAX) * 1.5f - 1.0f; // x va de -1 a 0.5
        targetY = 0.0f;
    } 
    else if (part == 3) { // 4. Línea horizontal inferior
        targetX = ((float)rand() / RAND_MAX) * 2.0f - 1.0f; // x va de -1 a 1
        targetY = -1.0f;
    }

    float fuerzaExplosion = 5.0f; // Qué tan rápido se expande el fuego artificial
    p.vx = targetX * fuerzaExplosion;
    p.vy = targetY * fuerzaExplosion;
    // Poca velocidad en Z para que se vea plano, pero con algo de volumen
    p.vz = ((float)rand() / RAND_MAX) * 0.4f - 0.2f; 
}

extern "C" {
    void InitParticles(int count) {
        particles.clear();
        particleCount = count;
        for (int i = 0; i < count; ++i) {
            Particle p;
            p.x = 0; p.y = 0; p.z = 0; // Nacen en el centro
            AsignarVelocidadFormaE(p);
            
            // Vida ligeramente aleatoria para que no todas desaparezcan de golpe
            p.life = 2.0f + ((float)rand() / RAND_MAX) * 0.5f; 
            particles.push_back(p);
        }
    }

    void UpdateParticles(float deltaTime, float speed) {
        for (auto& p : particles) {
            // Movimiento por la velocidad (expansión)
            p.x += p.vx * deltaTime * speed;
            p.y += p.vy * deltaTime * speed;
            p.z += p.vz * deltaTime * speed;
            
            // Efecto de gravedad para que las chispas caigan después de explotar
            p.vy -= 3.0f * deltaTime * speed; 

            p.life -= deltaTime;

            // Reiniciar partícula para el siguiente fuego artificial
            if (p.life <= 0) {
                p.x = p.y = p.z = 0; // Regresan al centro
                AsignarVelocidadFormaE(p); // Vuelven a agarrar forma de "E"
                p.life = 2.0f + ((float)rand() / RAND_MAX) * 0.5f;
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