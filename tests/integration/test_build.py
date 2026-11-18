# **************************************************************************** #
#                                                                              #
#                                                            +#                #
#    test_build.py                                          +##                #
#                                                         +###+                #
#    By: lucas <lucas@tsiaraso.com>                     +########+             #
#                                                           +###+              #
#    Created: 2026/11/18 16:51:30 by lucas                   ##+               #
#    Updated: 2026/11/18 16:51:30 by lucas                  #+                 #
#                                                                              #
# **************************************************************************** #

import os
import unittest


class TestCub3dIntegration(unittest.TestCase):
    """Integration test verifying cub3D binary and map assets."""

    def test_binary_and_maps_exist(self) -> None:
        self.assertTrue(os.path.isfile("./cub3D"))
        self.assertTrue(os.access("./cub3D", os.X_OK))
        self.assertTrue(os.path.isdir("./maps"))


if __name__ == "__main__":
    unittest.main()
