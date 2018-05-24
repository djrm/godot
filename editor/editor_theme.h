/*************************************************************************/
/*  editor_theme.h                                                       */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2018 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2018 Godot Engine contributors (cf. AUTHORS.md)    */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#ifndef EDITOR_THEME_H
#define EDITOR_THEME_H

#include "scene/resources/theme.h"

class EditorTheme : public Theme {
	GDCLASS(EditorTheme, Theme)

	int scale;
	int thumb_size;
	bool dark_theme;

	Color mono_color;
	Color mono_color_inv;
	Color base_color;
	Color base_color_strong;
	Color base_color_stronger;
	Color contrast_color;
	Color contrast_color_strong;
	Color base_color;
	Color accent_color;
	Color font_color_muted;
	Color font_color_dim;
	Color font_color;
	Color font_color_strong;

	void _generate_styleboxes();
	void _generate_colors();
	// void _generate_colors();

public:
	void update();

	int set_thumb_size(int p_thumb_size);
	int set_scale(int p_scale);
	// bool set_dark_theme(bool p_dark);

	void set_base_color(Color p_base_color);
	void set_accent_color(Color p_accent_color);

	bool get_thumb_size() const;
	bool get_scale() const;
	bool is_dark_theme() const;

	EditorTheme();
};

#endif