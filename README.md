This project has been created as part of the 42 curriculum by rduport, tirimesc.

cub3D is a 42 school project inspired by the legendary Wolfenstein 3D, the world's first FPS game. The goal is
to create a realistic 3D graphical representation of a maze from a first-person
perspective using raycasting  a rendering technique that simulates a 3D environment from a 2D map.
Raycasting is a rendering technique to create a 3D perspective using a 2D map (.cub files here).
For every vertical column of pixel it cast rays in front of the playerc until it finds a wall and render it accordingly to the calculation

The .cub file must follow this structure:

NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

111111
100001
1000N1
100001
111111
The map must be surrounded by walls (1), contain exactly one player start position (N, S, E, or W), and only valid characters (0, 1, space).

Usage :
make
./cub3D maps/example.cub