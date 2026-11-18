# **************************************************************************** #
#                                                                              #
#                                                            +#                #
#    test_cli.py                                            +##                #
#                                                         +###+                #
#    By: lucas <lucas@tsiaraso.com>                     +########+             #
#                                                           +###+              #
#    Created: 2026/11/18 08:30:00 by lucas                   ##+               #
#    Updated: 2026/11/18 08:30:00 by lucas                  #+                 #
#                                                                              #
# **************************************************************************** #

import subprocess
import tempfile
import unittest


class TestCub3dE2E(unittest.TestCase):
    """End-to-end CLI validation tests for cub3D."""

    def test_missing_args_exits_nonzero(self) -> None:
        res = subprocess.run(["./cub3D"], capture_output=True, text=True)
        self.assertNotEqual(res.returncode, 0)
        self.assertIn("Usage: ./cub3D", res.stdout + res.stderr)

    def test_bad_extension_exits_nonzero(self) -> None:
        res = subprocess.run(
            ["./cub3D", "README.md"], capture_output=True, text=True
        )
        self.assertNotEqual(res.returncode, 0)

    def test_invalid_map_exits_nonzero(self) -> None:
        with tempfile.NamedTemporaryFile(suffix=".cub", mode="w") as fh:
            fh.write("INVALID\n")
            fh.flush()
            res = subprocess.run(
                ["./cub3D", fh.name], capture_output=True, text=True
            )
            self.assertNotEqual(res.returncode, 0)
