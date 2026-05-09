# cub3D - Technical Halftone Raycaster

*This project has been created as part of the 42 curriculum by lutsiara.*

## Description
cub3D is a highly stylized 3D raycasting game inspired by the mechanics of Wolfenstein 3D. It features a unique **technical halftone aesthetic**, rendering the world as a high-precision grid of dots (2px center with 1px spacing). 

The game includes a functional gameplay loop where players navigate a complex, closed technical maze to collect rotating circular coins.

### Key Features
- **Dynamic Raycasting Engine**: High-performance DDA algorithm with texture mapping.
- **Aesthetic Overlay**: Global 3x3 halftone dot-matrix pass for a distinctive "blueprint" look.
- **Interactive Objects**: Rotating circular coins that support transparency (can see walls through them).
- **Responsive HUD**: Pure white health and ammo bars, plus a numeric score display with custom digit rendering.
- **Minimap**: Real-time 2D top-down view with cardinal-aligned wall coloring and player direction indicator.
- **Cross-Platform**: Native support for Linux (X11) and macOS (Intel OpenGL / Apple Silicon Metal).
- **Branded**: Includes custom native executable and Dock icons.

## Instructions

### Compilation
The project uses a specialized cross-platform Makefile:
```bash
make        # Compile the project
make re     # Recompile everything
make clean  # Remove object files
make fclean # Remove executable and libraries
```

### Execution
Run the program with a valid `.cub` scene description file:
```bash
./cub3D maps/test.cub
```

### Controls
- **W / A / S / D**: Move through the maze.
- **Left / Right Arrows**: Rotate the camera view.
- **ESC / Red Cross**: Quit the game cleanly.

## Resources
- **Raycasting**: Lodev's Raycasting Tutorial.
- **MiniLibX**: 42's internal graphics library documentation.
- **Icons**: macOS Cocoa NSWorkspace API for native branding.

### AI Usage
AI was used strategically for:
- Refactoring the raycasting engine into modular, constraint-compliant files.
- Implementing the mathematical ellipsoid rotation for the coin visuals.
- Designing the custom pixel-based numeric HUD renderer.
- Automating the 42-header compliance and code style audits.

---
*Developed with rigor and precision in C.*
