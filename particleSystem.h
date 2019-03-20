#include "particle.h"
#include <stdbool.h>

#define PSYSTEM_INIT_CAP 5

typedef struct {
  sfRenderWindow* window;
  bool randomize;
  unsigned int decay, size, capacity;
  Particle **list; // TODO replace with linked list (head and tail ptr)
} ParticleSystem;

/* Constructs a new ParticleSystem on the heap. Default flags are randomize = false,
 * decay = 0.
 */
ParticleSystem *ParticleSystem_create(void);

void ParticleSystem_destroy(ParticleSystem *system);

void ParticleSystem_spawnParticles(ParticleSystem *system, unsigned short n);

void ParticleSystem_setWindow(ParticleSystem *system, sfRenderWindow *window);

void ParticleSystem_setDecay(ParticleSystem *system, unsigned int decay);

void ParticleSystem_setRandomizeLocation(ParticleSystem *system, bool randomize);
