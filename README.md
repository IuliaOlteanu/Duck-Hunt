**Duck Hunt**
\
This is an implementation of a Duck Hunt game. You can test the original game here: https://www.duck-hunt.org/.

**Construction** 
\
Ducks are represented by several 2D geometric primitives (minimum 4: body, wings and head), positioned suggestively. 

**Animate**
\
To build the duck it is necessary an assembly of several manually defined objects that will move together, but will also have independent animations. Thus, the duck:
\
➢ It will have a flight animation: it will flap its wings - you can for example apply a simple rotation to each wing
\
➢ It will fly in various directions as a unit - the entire assembly of objects that make up the duck will move or rotate together

**Display**
\
The ducks appear one by one on the screen, so that at a given moment there is only one duck present in the scene. When a duck is shot or escapes, the next one will be displayed.

**Motion**
\
The ducks appear at the bottom of the screen and will begin their flight in a random direction in the plane. Continuing in that direction, they will eventually reach the edge of the screen. In this situation, the duck must "reflect" and continue its journey in the relevant direction, like a billiard ball hitting the edge of the table. If the duck is shot, it will fall to the ground moving through a vertically downward animation, respectively if it escapes it will fly off the screen moving through a vertically upward animation. After a reasonable number of seconds, in which the duck has collided with the edge of the screen a few times, it will escape. 

**Lives**
\
The player will initially start with 3 lives. The moment a duck escapes (the player missed hitting the duck with all 3 bullets), it loses a life. The number of lives left will be drawn on the screen in the upper left corner, for example in the form of red circles.

**Bullets**
\
At any point in time, the player must know how many bullets he has left. For this, in the upper left corner (below the number of lives) it is displayed the number of available bullets in a similar way to the number of lives, for example in the form of green rectangles.

**Score**
\
For each duck shot, the player's score will increase. This will also be represented in the graphical interface in the upper-right corner with the help of two rectangles:
\
➢ A wireframe rectangle, representing the maximum score level (you can consider a maximum score level of 50 or any other value >10)
\
➢ A solid blue rectangle inside the wireframe that represents the current score

**Gameplay**
\
The goal of the game is for the player to shoot as many ducks as possible before they run out of lives. The game starts with a number of lives available, one of which is lost every time a duck manages to escape without being shot.

The ducks appear one by one on the screen, one after another, each after the disappearance (by escaping or shooting) of the previous one. A duck will fall to the ground when shot and fly vertically upwards to symbolize escape. They move according to the rules described in the "Ducks - Motion" section. After spawning 5 ducks each, their movement speed will increase and thus the difficulty of the game will increase.

**Shotgun**
\
To shoot a duck, the player has 3 bullets at his disposal which reload every time a new duck appears. Each time he clicks on the screen, it will be considered that a bullet was fired at that point on the screen and the number of available bullets will decrease by 1. If the point on the screen (details section "Bullet intersection with the duck") that was shot intersects the duck, it will be considered shot, the score (details section "Score") will increase and the duck will fall to the ground (details section "Ducks - Movement").

The intersection of the bullet and the duck : Since the ducks are quite complex in shape, it would be difficult to calculate exactly which points on the screen intersect with them. So you can approximate them in the form of a rectangle in which the duck is framed (similar to the figure below). To calculate the coordinates of the corners of this square, you can use some notions of plane geometry, applied according to the coordinates at which the points on the silhouette of the duck are located.

**Duck Escape**
\
When all 3 bullets have been consumed without the duck being shot, it escapes. Also, if the duck has not been shot for a certain number of seconds, it will escape. In both situations where the duck escapes, the player will lose a life (details in the "Lives" section) and will not receive the score related to that duck.
