/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    set_icon.m                                            +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/05/09 16:00:08 by lucas                  ##+              */
/*    Updated: 2026/05/09 16:15:00 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#import <AppKit/AppKit.h>

static int	apply_icon(NSString *imagePath, NSString *targetPath)
{
	NSImage	*image;

	image = [[NSImage alloc] initWithContentsOfFile:imagePath];
	if (!image)
	{
		fprintf(stderr, "Error: Could not load image\n");
		return (1);
	}
	if (![[NSWorkspace sharedWorkspace] setIcon:image forFile:targetPath options:0])
	{
		fprintf(stderr, "Error: Could not set icon\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	int	res;

	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <image_path> <target_file>\n", argv[0]);
		return (1);
	}
	@autoreleasepool {
		res = apply_icon([NSString stringWithUTF8String:argv[1]], \
						[NSString stringWithUTF8String:argv[2]]);
	}
	return (res);
}
