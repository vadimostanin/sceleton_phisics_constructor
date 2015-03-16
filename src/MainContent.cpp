/*
 * MainContent.cpp
 *
 *  Created on: Mar 13, 2015
 *      Author: vostanin
 */

#include "MainContent.h"

#include <Elementary.h>

#include <Evas_Engine_Buffer.h>
#include <iostream>
using namespace std;

#define MAIN_EDJ "./main.edj"

MainContent::MainContent( Evas_Object *parent ) : m_Parent( parent ), m_MainLayout( NULL )
{
	createLayout();
}

MainContent::~MainContent()
{

}

Evas_Object * MainContent::getLayout()
{
	return m_MainLayout;
}

void MainContent::createLayout()
{
	Evas_Object *layout = elm_layout_add( m_Parent );
	elm_layout_file_set(layout, MAIN_EDJ, "main_layout");
//	elm_win_resize_object_add( m_Parent, layout );
	evas_object_show(layout);

	m_MainLayout = layout;
}
//
//static Evas *create_canvas(int width, int height)
//{
//	Evas *canvas;
//	Evas_Engine_Info_Buffer *einfo;
//	int method;
//	void *pixels;
//	method = evas_render_method_lookup("buffer");
//	if (method <= 0)
//	{
//		fputs("ERROR: evas was not compiled with 'buffer' engine!\n", stderr);
//		return NULL;
//	}
//	canvas = evas_new();
//	if (!canvas)
//	{
//		fputs("ERROR: could not instantiate new evas canvas.\n", stderr);
//		return NULL;
//	}
//	evas_output_method_set(canvas, method);
//	evas_output_size_set(canvas, width, height);
//	evas_output_viewport_set(canvas, 0, 0, width, height);
//	einfo = (Evas_Engine_Info_Buffer *)evas_engine_info_get(canvas);
//	if (!einfo)
//	{
//		fputs("ERROR: could not get evas engine info!\n", stderr);
//		evas_free(canvas);
//		return NULL;
//	}
//	// ARGB32 is sizeof(int), that is 4 bytes, per pixel
//	pixels = malloc(width * height * sizeof(int));
//	if (!pixels)
//	{
//		fputs("ERROR: could not allocate canvas pixels!\n", stderr);
//		evas_free(canvas);
//		return NULL;
//	}
//	einfo->info.depth_type = EVAS_ENGINE_BUFFER_DEPTH_ARGB32;
//	einfo->info.dest_buffer = pixels;
//	einfo->info.dest_buffer_row_bytes = width * sizeof(int);
//	einfo->info.use_color_key = 0;
//	einfo->info.alpha_threshold = 0;
//	einfo->info.func.new_update_region = NULL;
//	einfo->info.func.free_update_region = NULL;
//	evas_engine_info_set(canvas, (Evas_Engine_Info *)einfo);
//	return canvas;
//}
//
//
//static void save_scene(Evas *canvas, const char *dest)
//{
//	Evas_Engine_Info_Buffer *einfo;
//	const unsigned int *pixels, *pixels_end;
//	int width, height;
//	FILE *f;
//	einfo = (Evas_Engine_Info_Buffer *)evas_engine_info_get(canvas);
//	if (!einfo)
//	{
//		fputs("ERROR: could not get evas engine info!\n", stderr);
//		return;
//	}
//	evas_output_size_get(canvas, &width, &height);
//	f = fopen(dest, "wb+");
//	if (!f)
//	{
//		fprintf(stderr, "ERROR: could not open for writing '%s': %s\n",
//		dest, strerror(errno));
//		return;
//	}
//	pixels = (const unsigned int*)einfo->info.dest_buffer;
//	pixels_end = pixels + (width * height);
//	// PPM P6 format is dead simple to write:
//	fprintf(f, "P6\n%d %d\n255\n", width, height);
//	for (; pixels < pixels_end; pixels++)
//	{
//		int r, g, b;
//		r = ((*pixels) & 0xff0000) >> 16;
//		g = ((*pixels) & 0x00ff00) >> 8;
//		b = (*pixels) & 0x0000ff;
//		fprintf(f, "%c%c%c", r, g, b);
//	}
//	fclose(f);
//	printf("saved scene as '%s'\n", dest);
//}

















