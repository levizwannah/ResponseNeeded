# Interface Specification 
## Introduction
This interface specification will provide an interface between the backend and frontend development. It will help the both teams to code in parallel.  
In this document, the interfaces are methods that will be called for certain purposes and is provided to another team for usage. The consumer of the API need not know the underlying logic of the 
API.  

## Organization
This document consist of different objects and methods that can be called on those objects to perform certain tasks. Not every method of the object is listed only
the important ones are.

## Constants
1. `S_WIDTH: int`: screen width
2. `S_HEIGHT: int`: screen height
3. `C_SIDE: int`: cube side length
4. `enum Color`: Red -> 0, Green -> 1, Blue -> 2, Yellow -> 3. Colors of the cube.
5. `R_SPEED: int`: The speed of the roller   

## CubeMover Object
This object is responsible to move a group of cubes around in circle. Part of the circle is off the screen while the other half is on the screen.  
This object is like the escalator, it is always moving and only needs cubes to be placed on it. The methods to call on this object are:  
1. `**+addCube(mainX: int, mainY: int, side: int): int**` : This methods adds a cube object to the mover. The (mainX, mainY) is the point of the cube on which every other point of the cube depends. The side is the mathematical side of the cube. This method returns the index of the cube on the mover.
2. `**+stop(): bool**`: Stops the CubeMover
3. `**+start(): bool**`: starts the CubeMover
4. `**+remove(index: int): bool**`: Removes a cube from the mover given its index
5. `**+remove(cubeId: int): bool**`: Removes the the cube whose ID was provided
6. `**+getIndex(cube: Cube): int**`: returns the index of a cube on the mover 
7. `**+setSpeed(speed: int): void**`: sets the speed of the mover

## Cube
This is the cube object. The methods to call on this object are:
1. `**+setColor(color: Color): void**`: Sets the color of the cube.
2. `**+getColor(): Color**`: Gets the color of the cube
3. `**+setMainX(x: int): void**`: Sets the main X coordinate of the cube.
4. `**+getMainX(): int**`: Gets the main X coordinate of the cube.
5. `**+setMainY(y: int): void**`: Sets the main Y coordinate of the cube.
6. `**+getMainY(): int**`: Gets the main Y coordinate of the cube.
7. `**+setMainCoord(x: int, y: int): void**`: Sets the mainXY point of the cube. The mainXY point is the point of the Cube one which every other point(vertex) depends.
8. `**+getId(): int**`: Every cube has an ID and this methods gets the ID of the cube.
9. `**+explode(): bool**`: Explodes the cube and deletes it, setting it to null.

## Gun
This is the object that is responsible to shoot out bullets. It can only move left and right.  
The methods to call on this object are:
1. `**+setX(x: int): void**`: Sets the X position of the Gun.
2. `**+getX(x: int): int**`: returns the X position of the Gun.
3. `**+shoot(): Bullet**`: returns a bullet with the X+offset position of the Gun. The Offest is to ensure that the bullet is in the middle of the gun. Mostly, offset will be the width of the gun/2.

## Bullet
This is the object that gets shot from the gun and when it collides with the cubes, causes both itself and the cube to explode. This object only moves up the screen hence only the Y position is chageable. Secondly, the new Y position cannot be less than the current Y position.
The methods to call on this object are:
1. `**+setY(y: int): bool**`: This will set the Y position of the bullet and it will ensure that the current Y position is less than the new Y position. It returns bool on success.
2. `**+getY(): int**`: returns the Y position of the bullet
3. `**+explode(): bool**`: Explodes the bullet and set it to null

## Target Cube
This is the cube that tells the player which cube to shoot out.
1. `**+setColor(color: Color): bool**`: Sets the color of the Target Cube.
2. `**+getColor(): Color**`: returns the color of the target cube.

## Score
This is the text that shows the score of the player.  
These are the available methods to call.
1. `**+setScore(score: int): void**`: Sets the score of the player
2. `**+getScore(): int**`: returns the score of the player

## PlayerLife
This indicates the life of the player.  
These are the methods to call on this object
1. `**+addLife(): bool**`: Adds one life to the player's life
2. `**+removeLife(): bool**`: removes a life from the player's life
3. `**+getLife(): int**`: returns the number of life the player has

