#include "particle.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <SFML/Window/Mouse.h>

Particle *Particle_create(void)
{
  // Create pointer
  Particle *particle = (Particle *) malloc(sizeof(Particle));

  // Initialize struct fields
  particle->shape = sfCircleShape_create();
  sfCircleShape_setRadius(particle->shape, 5.f);
  particle->vel = (sfVector2f *) malloc(sizeof(sfVector2f));
  particle->vel->x = 0.f;
  particle->vel->y = 0.f;
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

void Particle_setVelTowardsMouse(Particle *particle, sfRenderWindow *window)
{
  // int mouseX = sfMouse_getPositionRenderWindow(window).x;
  // float particleX = particle->vel->x;
  // particle->vel->x = (mouseX - particleX) / sqrt(pow(mouseX - particleX, 2));
  // printf("%.5f\n", particle->vel->x);
  //
  // int mouseY = sfMouse_getPositionRenderWindow(window).y;
  // float particleY = particle->vel->y;
  // particle->vel->y = (mouseY - particleY) / sqrt(pow(mouseY - particleY, 2));

  sfVector2f mouseVec = {
                          sfMouse_getPositionRenderWindow(window).x,
                          sfMouse_getPositionRenderWindow(window).y
                        };
  sfCircleShape_setPosition(particle->shape, mouseVec);
}
