/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    macos_icon.m                                          +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/05/09 13:46:24 by lucas                  ##+              */
/*    Updated: 2026/05/09 13:46:24 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#import <Cocoa/Cocoa.h>

void	set_platform_icon(const char *path)
{
	@autoreleasepool {
		NSString *nsPath = [NSString stringWithUTF8String:path];
		NSImage *image = [[NSImage alloc] initWithContentsOfFile:nsPath];
		if (image)
		{
			[NSApp setApplicationIconImage:image];
		}
	}
}
