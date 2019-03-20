#include <SFML/Graphics/CircleShape.h>
#include <SFML/Graphics/RenderWindow.h>

/* Particle struct contains a sfCircleShape (maintains pos.),
 * along with vel. and accel. vectors
 */
typedef struct {
  sfCircleShape* shape;
  sfVector2f* vel;
  sfVector2f* accel;
} Particle;

/* Constructs a new Particle on the heap. Pos. defaults to 0,0.
 * Returns a pointer to the new heap-allocated Particle.
 */
Particle *Particle_create(void);

/* Frees a Particle's memory.
 */
void Particle_destroy(Particle *particle);

/* Updates the Particle's pos. based on its current vel.
 */
void Particle_updatePos(Particle *particle);

/* Updates the Particle's pos. to point in the direction of the cursor.
 */
// void Particle_setVelTowardsMouse(Particle *particle, sfRenderWindow *window);
void Particle_setVelTowardsMouse(Particle *particle, sfVector2i mousePos);

/* Randomizes the Particle's pos. to a random point in the given window.
 */
void Particle_randomizePosition(Particle *particle, sfRenderWindow *window);
