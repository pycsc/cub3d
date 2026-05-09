/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    set_icon.m                                            +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/05/09 14:09:35 by lucas                  ##+              */
/*    Updated: 2026/05/09 14:09:35 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#import <AppKit/AppKit.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <image_path> <target_file>\n", argv[0]);
        return 1;
    }

    @autoreleasepool {
        NSString *imagePath = [NSString stringWithUTF8String:argv[1]];
        NSString *targetPath = [NSString stringWithUTF8String:argv[2]];

        NSImage *image = [[NSImage alloc] initWithContentsOfFile:imagePath];
        if (!image) {
            fprintf(stderr, "Error: Could not load image at %s\n", argv[1]);
            return 1;
        }

        BOOL success = [[NSWorkspace sharedWorkspace] setIcon:image forFile:targetPath options:0];
        if (!success) {
            fprintf(stderr, "Error: Could not set icon for %s\n", argv[2]);
            return 1;
        }
    }
    return 0;
}
