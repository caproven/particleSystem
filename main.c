#include "particleSystem.h"
#include <stdlib.h>
#include <SFML/Graphics.h>

#define FRAMERATE_LIMIT 60

int main(int argc, char *argv[])
{
  // Create elements the program will use
  sfVideoMode mode = { 800, 600, 32};
  sfRenderWindow* window;
  sfColor bgColor = sfColor_fromRGB(40, 32, 36);
  sfEvent event;
  ParticleSystem* psystem;

  // Construct window
  window = sfRenderWindow_create(mode, "Application Title", sfResize | sfClose, NULL);
  if (!window)
    return EXIT_FAILURE;
  sfRenderWindow_setFramerateLimit(window, FRAMERATE_LIMIT);
  sfRenderWindow_setMouseCursorVisible(window, false);

  // Construct particle system
  psystem = ParticleSystem_create();
  ParticleSystem_setWindow(psystem, window);
  ParticleSystem_setRandomizeLocation(psystem, 1);
  ParticleSystem_spawnParticles(psystem, 1);

  // Game loop
  while (sfRenderWindow_isOpen(window)) {
    while (sfRenderWindow_pollEvent(window, &event)) {
      if (event.type == sfEvtMouseButtonReleased ||
          event.type == sfEvtKeyReleased)
        sfRenderWindow_close(window);
      else if (event.type == sfEvtMouseWheelScrolled)
        ParticleSystem_spawnParticles(psystem, 5);
    }

    // Clear RenderWindow before redrawing elements
    sfRenderWindow_clear(window, bgColor);

    // Update each Particle in the ParticleSystem
    ParticleSystem_updateSystem(psystem);
    // sfVector2i mousePos = sfMouse_getPositionRenderWindow(window);
    for (int i = 0; i < psystem->size; i++) {
    //   Particle_setVelTowardsMouse(psystem->list[i], mousePos);
    //   sfCircleShape_move(psystem->list[i]->shape, *(psystem->list[i]->vel));
      if (psystem->list[i]) {
        sfRenderWindow_drawCircleShape(window, psystem->list[i]->shape, NULL);
      }
    }
    sfRenderWindow_display(window);
  }

  // Cleanup
  ParticleSystem_destroy(psystem);
  sfRenderWindow_destroy(window);

  return EXIT_SUCCESS;
}
