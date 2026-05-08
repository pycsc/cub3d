# Project Plan: cub3D Raycaster (Detailed Assessment)

## 1. Current State Assessment

Based on a deep dive into the existing source code:

-   **Core Engine:** A functional DDA (Digital Differential Analyzer) raycasting engine is implemented in `engine/raycasting_engine.c`. It correctly calculates wall distances and renders vertical stripes.
-   **Rendering:** Basic rendering of solid walls, floor, and ceiling is present. **Texture mapping is currently missing.**
-   **Parsing:** The foundation for `.cub` parsing exists in `parsing/`, but it is incomplete. Specifically, `validate_map` is a placeholder, and the configuration parsing (textures, colors) needs robust implementation and verification.
-   **Player Controls:** Movement and rotation logic is defined in `engine/player_controller.c` but **not yet hooked** to keyboard events in `cub3d.c`.
-   **Platform Compatibility:** The `Makefile` is well-structured for cross-platform support (macOS ARM/Intel and Linux).
-   **Missing Features:** Texture mapping, full `.cub` validation, comprehensive error handling, and the minimap (dot rendering).

## 2. Updated Project Goals

### 2.1 Mandatory Refinements
-   **Complete Parser:** Implement full validation for `.cub` files, ensuring textures exist and colors are valid.
-   **Map Validation:** Replace the `validate_map` placeholder with a flood-fill or perimeter-check algorithm to ensure the map is fully closed.
-   **Texture Integration:** Modify `render_frame` and `draw_wall_stripe` to calculate texture coordinates and fetch colors from loaded XPM/PNG textures.
-   **Input Hooking:** Connect `W, A, S, D` and `Arrow` keys to `move_player` and `rotate_player` in the MiniLibX loop.
-   **Memory Leak Audit:** Ensure all allocated memory (especially the map array and textures) is freed on exit.

### 2.2 Bonus: Dot Rendering (Minimap)
-   **Objective:** Implement a 2D minimap overlay using "dot rendering" principles.
-   **Implementation:**
    -   Create a `draw_minimap` function.
    -   Iterate through the 2D map array and draw small colored squares ("dots") representing walls and empty spaces.
    -   Render a distinct dot for the player position.
    -   Draw a short line or "pointing dot" to indicate the player's view direction.

## 3. Revised Development Phases

### Phase 1: Robust Parsing & Validation
1.  Complete `parse_line` and configuration extraction.
2.  Implement a proper `validate_map` function (ensuring the player is enclosed).
3.  Add specific error messages for different parsing failures.

### Phase 2: Input & Movement Integration
1.  Update `key_hook` in `cub3d.c` to handle `W, A, S, D` and `Arrow` keys.
2.  Implement collision detection within `move_player` (partially exists, needs refinement).
3.  Ensure smooth movement by tracking key states (pressed/released) if necessary.

### Phase 3: Texture Mapping
1.  Implement texture loading using `mlx_xpm_file_to_image`.
2.  Update the raycasting loop to determine the exact hit point on the wall for texture coordinate ($u, v$) calculation.
3.  Fetch colors from the texture buffer instead of using solid colors.

### Phase 4: Minimap (Dot Rendering)
1.  Define minimap scale and position.
2.  Implement the 2D dot-based rendering for walls and the player.
3.  Optimize by rendering to a sub-image or buffer.

### Phase 5: Final Polish & Cross-Platform Verification
1.  Verify the build on Linux and macOS (Intel/M1).
2.  Run `valgrind` (on Linux) or `leaks` (on macOS) to ensure zero memory leaks.
3.  Final check against the `Norm` and `GEMINI.md` constraints.

## 4. Technical Specifications

-   **Screen Resolution:** 800x600 (as per current code).
-   **Minimap Scale:** 1 map unit = 10-15 pixels.
-   **Texture Format:** XPM (standard for MiniLibX) or PNG (supported by Metal/MMS version).
-   **Collision Radius:** 0.2 units for smooth wall interaction.
