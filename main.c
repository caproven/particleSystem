#include "particle.h"
#include <stdlib.h>
#include <stdio.h>
#include <SFML/Graphics.h>

int main(int argc, char *argv[])
{
  // Create elements the program will use
  sfVideoMode mode = { 800, 600, 32};
  sfRenderWindow* window;
  sfColor bgColor = sfColor_fromRGB(71, 55, 62);
  sfFont* font;
  sfText* text;
  sfEvent event;
  Particle* particle;

  // Construct window
  window = sfRenderWindow_create(mode, "Application Title", sfResize | sfClose, NULL);
  if (!window)
    return EXIT_FAILURE;
  sfRenderWindow_setFramerateLimit(window, 30);

  // Construct particle
  particle = Particle_create();

  // Set text
  font = sfFont_createFromFile("resources/Roboto-Regular.ttf");
  if (!font)
    return EXIT_FAILURE;
  text = sfText_create();
  char myText[50];
  sprintf(myText, "%.5f %.5f",
          sfCircleShape_getPosition(particle->shape).x,
          sfCircleShape_getPosition(particle->shape).y);
  sfText_setString(text, myText);
  sfText_setFont(text, font);
  sfText_setCharacterSize(text, 30);

  // Game loop
  while (sfRenderWindow_isOpen(window)) {
    while (sfRenderWindow_pollEvent(window, &event)) {
      if (event.type == sfEvtKeyReleased)
        sfRenderWindow_close(window);
    }

    // Call updates
    Particle_setVelTowardsMouse(particle, window);
    //Particle_updatePos(particle);
    //sfVector2i mousePos = sfMouse_getPositionRenderWindow(window);
    //sprintf(myText, "%d %d", mousePos.x, mousePos.y);
    sprintf(myText, "%.5f %.5f",
            sfCircleShape_getPosition(particle->shape).x,
            sfCircleShape_getPosition(particle->shape).y);
    sfText_setString(text, myText);

    // Handle window redrawing
    sfRenderWindow_clear(window, bgColor);
    sfRenderWindow_drawText(window, text, NULL);
    sfRenderWindow_drawCircleShape(window, particle->shape, NULL);
    sfRenderWindow_display(window);
  }

  // Cleanup
  sfText_destroy(text);
  sfFont_destroy(font);
  Particle_destroy(particle);
  sfRenderWindow_destroy(window);

  return EXIT_SUCCESS;
}
