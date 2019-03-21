#include "particle.h"
#include <stdlib.h>
#include <math.h>
#include <SFML/Window/Mouse.h>

Particle *Particle_create(void)
{
  // Create pointer
  Particle *particle = (Particle *) malloc(sizeof(Particle));

  // Initialize struct fields
  particle->shape = sfCircleShape_create();
  sfCircleShape_setRadius(particle->shape, 1.f);
  particle->vel = (sfVector2f *) malloc(sizeof(sfVector2f));
  particle->vel->x = 0.f;
  particle->vel->y = 0.f;

  // Return pointer
  return particle;
}

void Particle_destroy(Particle *particle)
{
  // Free components of the particle
  sfCircleShape_destroy(particle->shape);
  free(particle->vel);

  // Free the particle itself
  free(particle);
}

void Particle_updatePos(Particle *particle)
{
  sfCircleShape_move(particle->shape, *(particle->vel));
}

int Particle_setVelTowardsMouse(Particle *particle, sfVector2i mousePos)
{
  // Unit vector
  int mouseX = mousePos.x;
  float particleX = sfCircleShape_getPosition(particle->shape).x;
  float diffX = mouseX - particleX;

  int mouseY = mousePos.y;
  float particleY = sfCircleShape_getPosition(particle->shape).y;
  float diffY = mouseY - particleY;

  float denom = diffX * diffX + diffY * diffY;

  //if (denom != 0) {
  if (denom >= 10) {
    particle->vel->x = 2 * diffX / sqrt(denom);
    particle->vel->y = 2 * diffY / sqrt(denom);
    return 1;
  } else {
    Particle_destroy(particle);
    return 0;
  }

}

void Particle_randomizePosition(Particle *particle, sfRenderWindow *window) {
  sfVector2f windowDimensions = {
    rand() % sfRenderWindow_getSize(window).x,
    rand() % sfRenderWindow_getSize(window).y
  };
  sfCircleShape_setPosition(particle->shape, windowDimensions);
}
