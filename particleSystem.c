#include "particleSystem.h"
#include <stdlib.h>
#include <stdio.h>

static void printStatus(const ParticleSystem *system)
{
  printf("[PSystem] ParticleSystem has random:%d decay:%d size:%d capacity:%d\n",
      system->randomize, system->decay, system->size, system->capacity);
}

ParticleSystem *ParticleSystem_create()
{
  // Create pointer
  ParticleSystem *system = (ParticleSystem *) malloc(sizeof(ParticleSystem));

  // Initialize struct fields
  system->window = NULL;
  system->randomize = false;
  system->decay = 0;
  system->size = 0;
  system->capacity = PSYSTEM_INIT_CAP;
  system->list = (Particle **) malloc(PSYSTEM_INIT_CAP * sizeof(Particle *));

  printf("[PSystem] Constructing new ParticleSystem..\n");
  printStatus(system);

  // Return pointer
  return system;
}

void ParticleSystem_destroy(ParticleSystem *system)
{
  printf("[PSystem] Destroying ParticleSystem..\n");

  // Free components
  for (int i = 0; i < system->size; i++) {
    Particle_destroy(system->list[i]);
  }
  free(system->list);
  // window field will be freed in main

  // Free ParticleSystem itself
  free(system);
}

void ParticleSystem_spawnParticles(ParticleSystem *system, unsigned short n)
{
  // Ensure adequate capacity
  if (system->size + n > system->capacity) {
    system->capacity *= 2;
    system->list = (Particle **) realloc(system->list, system->capacity * sizeof(Particle *));
  }

  // Construct Particles
  for (int i = 0; i < n; i++) {
    system->list[system->size + i] = Particle_create();
    if (system->randomize) { // TODO add in check that system->window has been set
      Particle_randomizePosition(system->list[system->size + i], system->window);
    }
  }
  system->size += n; // done after loop so accessing based off size of system works
  printf("[PSystem] Spawning particles..\n");
  printStatus(system);
}

void ParticleSystem_setWindow(ParticleSystem *system, sfRenderWindow *window)
{
  system->window = window;
}

void ParticleSystem_setDecay(ParticleSystem *system, unsigned int decay)
{
  system->decay = decay;
}

void ParticleSystem_setRandomizeLocation(ParticleSystem *system, bool randomize)
{
  system->randomize = randomize;
}

void ParticleSystem_updateSystem(ParticleSystem *system)
{
  sfVector2i mousePos = sfMouse_getPositionRenderWindow(system->window);
  for (int i = 0; i < system->size; i++) {
    if (system->list[i]) { // if ptr isn't NULL
      if (Particle_setVelTowardsMouse(system->list[i], mousePos)) { // if particle wasnt freed
        sfCircleShape_move(system->list[i]->shape, *(system->list[i]->vel));
      } else { // particle was freed, set ptr = NULL
        system->list[i] = NULL;
      }
    }
  }
}
