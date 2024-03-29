#include <stdlib.h>
#include <stdio.h>

#include "bitmap_fonts.h"
#include "surface.h"
#include "surface16bpp.h"

int main(int argc, char *argv[])
{
	int x, y;
	spmp_bitmapFont * font;
	spmp_surface * surface;

	/* init LCD */
	if (spmp_surface16bpp_init()==SPMP_SURFACE16BPP_INIT_FAIL)
	{
		printf("Couldn't open LCD device, exiting...\n");
		return -1;
	}

	/* create surface */
	surface = spmp_surface16bpp_create();
	if (surface==NULL)
	{
		printf("Couldn't create surface, exiting...\n");
		return -1;
	}

	for (y=0; y<240; y++)
		for (x=0; x<320; x++)
			surface->framebuffer.u16[y*320+x] = 0xffff;

	/* create a new font */
	int baseline = 40;

	font = spmp_bitmapFont_create();
	spmp_bitmapFont_load(font, "goudy32.bfnt");
	spmp_surface_drawString(surface, "Goudy 32pt.", 12, baseline, font, 0, 0, 0);
	spmp_surface_drawString(surface, "The quick brown fox", 12, 160, font, 0, 0, 0);
	spmp_surface_drawString(surface, "jumps over the lazy dog.", 12, 160 + font->leading, font, 0, 0, 0);
	baseline += font->leading;
	spmp_bitmapFont_destroy(font);

	font = spmp_bitmapFont_create();
	spmp_bitmapFont_load(font, "italic24.bfnt");
	spmp_surface_drawString(surface, "Italic nice 24pt.", 12, baseline, font, 0, 0, 0);
	baseline += font->leading;
	spmp_bitmapFont_destroy(font);

	font = spmp_bitmapFont_create();
	spmp_bitmapFont_load(font, "mono24.bfnt");
	spmp_surface_drawString(surface, "Monospace 24pt.", 12, baseline, font, 0, 0, 0);
	baseline += font->leading;
	spmp_bitmapFont_destroy(font);

	font = spmp_bitmapFont_create();
	spmp_bitmapFont_load(font, "mono16.bfnt");
	spmp_surface_drawString(surface, "Monospace 16pt.", 12, baseline, font, 0, 0, 0);
	baseline += font->leading;
	spmp_bitmapFont_destroy(font);

	font = spmp_bitmapFont_create();
	spmp_bitmapFont_load(font, "mono12.bfnt");
	spmp_surface_drawString(surface, "Monospace 12pt.", 12, baseline, font, 0, 0, 0);
	spmp_surface_drawString(surface, "The quick brown fox jumps over the lazy dog.", 12, 220, font, 0, 0, 0);
	baseline += font->leading;
	spmp_bitmapFont_destroy(font);

	spmp_surface_blit(surface);

	/* close LCD */
	spmp_surface16bpp_close();

	return 0;
}
