#include "particle.h"
#include <stdlib.h>

Particle *Particle_create(void)
{
  // Create pointer
  Particle *particle = (Particle *) malloc(sizeof(Particle));

  // Initialize struct fields
  particle->shape = sfCircleShape_create();
  sfCircleShape_setRadius(particle->shape, 5.f);
  particle->vel = (sfVector2f *) malloc(sizeof(sfVector2f));
  particle->vel->x = 1.f;
  particle->vel->y = 1.f;
  particle->accel = (sfVector2f *) malloc(sizeof(sfVector2f));

  // Return pointer
  return particle;
}

void Particle_destroy(Particle *particle)
{
  // Free components of the particle
  sfCircleShape_destroy(particle->shape);
  free(particle->vel);
  free(particle->accel);

  // Free the particle itself (pointers to its components)
  free(particle);
}

void Particle_updatePos(Particle *particle)
{
  sfCircleShape_move(particle->shape, *(particle->vel));
}
