# CUB3D - Ray-Casting FPS Game

This project has been created as part of the 42 curriculum by lutsiara

## Description

A ray-casting 3D FPS engine inspired by Wolfenstein 3D. The project creates a first-person perspective view inside a maze using ray-casting algorithms, displaying textures, and providing interactive movement controls.

### Goal
Implement a 3D graphical representation of a maze through ray-casting principles, using miniLibX for rendering and parsing .cub configuration files.

## Instructions

### Requirements
- C programming language
- macOS or Linux
- miniLibX library

### Setup

**On macOS:**
1. Extract `minilibx_macos_metal.tgz` to your project directory
2. Navigate to the minilibx directory
3. Compile with: `make`

**On Linux:**
1. Extract `minilibx-linux.tgz` to your project directory
2. Navigate to the minilibx directory
3. Compile with: `make`

### Compilation
```
make
```

### Running
```
./cub3D maps/sample.cub
``` 

Example map file format:
```
NO ./texture_north.png
SO ./texture_south.png
WE ./texture_west.png
EA ./texture_east.png
F 220,100,0
C 225,30,0
111111
100101
101001
1100N1
111111
```

## Resources

- [Wolfenstein 3D Documentation](http://users.atw.hu/wolf3d/)
- [Ray Casting Algorithm Tutorials](https://lodev.org/cgtutor/raycasting.html)
- [miniLibX Documentation](https://github.com/42Paris/minilibx)
- [42 Subject on Cub3D](https://github.com/42Paris/cub3d)

## Technical Overview

### Core Components
- **Map Parsing**: Parse .cub files with textures, colors, and level design
- **Ray Casting**: Calculate 3D wall projections from 2D map
- **Rendering**: MiniLibX window generation with textures
- **Input Handling**: Keyboard controls (WASD + arrows) and mouse

### Bonus Features
- Wall collision detection
- Minimap system  
- Doors with opening/closing
- Animated sprites
- Mouse rotation

## Architecture

```
cub3d/
├── cub3d.c          # Main program and initialization
├── parsing/         # Map parsing and .cub file handling
├── engine/          # Raycasting and rendering logic
├── mlx/            # MiniLibX wrapper functions
├── include/        # Header files
├── maps/           # Test maps
└── textures/       # Texture images
```

### Key Algorithms
1. **DDA Algorithm**: Used for efficient ray-wall intersection
2. **Wall Strip Calculation**: Generate 3D wall segments
3. **Texture Mapping**: Apply textures based on wall side and distance
4. **Line Drawing**: Draw vertical wall strips

## Controls
- **W/S**: Move forward/backward
- **A/D**: Strafe left/right  
- **Left/Right Arrow**: Turn view angle
- **Mouse**: Rotate view angle (bonus)
- **ESC**: Close application
- **Window Close Button**: Close application
