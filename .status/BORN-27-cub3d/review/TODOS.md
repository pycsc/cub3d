# cub3d Review Todos

Tested in `docker.io/library/alpine:3.20` (`aarch64`, `gcc` + `musl-dev` + `libx11-dev` + `libxext-dev`).
Fixed `engine/linux_icon.c` missing `#include "mlx.h"` and `#include <X11/Xatom.h>` so all `.c` translation units compile cleanly with `-Wall -Wextra -Werror`.

- [ ] **[P1][bug][linux-link]** `Makefile` / `libs/get_next_line`: GNU `ld` on Linux fails to link `cub3D` due to duplicate `ft_strlen`/`ft_strchr` symbols between `libft.a` and `libgnl.a` and archive link order (`ft_calloc` undefined after `-lft`). Remove duplicate `libft` symbols from `libgnl.a` or link `-lgnl -lft`.
- [ ] **[P2][bug][makefile]** `Makefile` `fclean` fails on fresh Linux checkout because `libs/minilibx-linux` `clean` runs before `./configure` generates `makefile.gen`.
- [ ] **[P2][test][unit-functional]** Add Unit (`tests/unit`) and Functional (`tests/functional`) tests for `parsing/` and `engine/dda_engine.c` alongside [test_cli.py](file:///Users/momo/Born/cub3d/tests/e2e/test_cli.py).
