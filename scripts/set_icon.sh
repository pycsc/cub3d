#!/bin/bash
# **************************************************************************** #
#                                                                              #
#                                                            +#                #
#    set_icon.sh                                            +##                #
#                                                         +###+                #
#    By: lucas <lucas@tsiaraso.com>                   +########+               #
#                                                           +###+              #
#    Created: 2026/05/09 13:46:24 by lucas                   ##+               #
#    Updated: 2026/05/09 13:46:24 by lucas                  #+                 #
#                                                                              #
# **************************************************************************** #

# This script sets the file icon on macOS.
# Usage: ./set_icon.sh <image_path> <target_file>

if [[ "$OSTYPE" == "darwin"* ]]; then
    IMAGE_PATH=$(realpath "$1")
    TARGET_PATH=$(realpath "$2")

    # Use AppleScript to set the icon via Finder
    # Using 'as alias' to be more robust
    osascript <<EOF
        try
            set imageFile to (POSIX file "$IMAGE_PATH") as alias
            set targetFile to (POSIX file "$TARGET_PATH") as alias
            tell application "Finder"
                set icon of targetFile to imageFile
            end tell
        on error errMsg
            log errMsg
        end try
EOF
    echo "Icon set attempted for $TARGET_PATH"
else
    echo "File icon setting is only implemented for macOS."
fi
