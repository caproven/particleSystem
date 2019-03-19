#include "particleSystem.h"
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
  sfText* textMouse;
  sfEvent event;
  ParticleSystem* psystem;

  // Construct window
  window = sfRenderWindow_create(mode, "Application Title", sfResize | sfClose, NULL);
  if (!window)
    return EXIT_FAILURE;
  sfRenderWindow_setFramerateLimit(window, 30);

  // Construct particle system
  psystem = ParticleSystem_create();
  ParticleSystem_setWindow(psystem, window);

  // Set text
  font = sfFont_createFromFile("resources/Roboto-Regular.ttf");
  if (!font)
    return EXIT_FAILURE;
  textMouse = sfText_create();
  char myText[50];
  sprintf(myText, "Mouse: %d %d",
          sfMouse_getPositionRenderWindow(window).x,
          sfMouse_getPositionRenderWindow(window).y);
  sfText_setString(textMouse, myText);
  sfText_setFont(textMouse, font);
  sfText_setCharacterSize(textMouse, 20);
  sfText_setPosition(textMouse, (sfVector2f) {0.f, 25.f});

  // Game loop
  while (sfRenderWindow_isOpen(window)) {
    while (sfRenderWindow_pollEvent(window, &event)) {
      if (event.type == sfEvtKeyReleased)
        sfRenderWindow_close(window);
    }

    // Call updates
    // moved to window redrawing to reduce redundant iteration

    sprintf(myText, "Mouse: %d %d",
            sfMouse_getPositionRenderWindow(window).x,
            sfMouse_getPositionRenderWindow(window).y);
    sfText_setString(textMouse, myText);

    // Handle window redrawing
    sfRenderWindow_clear(window, bgColor);
    sfRenderWindow_drawText(window, textMouse, NULL);
    for (int i = 0; i < psystem->size; i++) {
      Particle_updatePos(psystem->list[i]);
      sfRenderWindow_drawCircleShape(window, psystem->list[i]->shape, NULL);
    }
    sfRenderWindow_display(window);
  }

  // Cleanup
  sfText_destroy(textMouse);
  sfFont_destroy(font);
  ParticleSystem_destroy(psystem);
  sfRenderWindow_destroy(window);

  return EXIT_SUCCESS;
}
