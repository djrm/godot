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

	// user specified
	Color primary_color;
	Color accent_color;

	Color accent_color_opt;

	Color base_color;
	Color base_color_strong;
	Color base_color_stronger;
	Color contrast_color;
	Color contrast_color_strong;
	Color background_color;

	Color mono_color;
	Color mono_color_inv;
	Color font_color_muted; // muted color, used for disabled things
	Color font_color_dim; // subtle variation of font color
	Color font_color; // default font color
	Color font_color_strong; // highlight font color
	Color alpha_color;
	Color separation_color;
	Color separator_color;

	// strongest color.
	Ref<StyleBoxFlat> style_background;

	// its only property is having the default margins
	Ref<StyleBoxFlat> style_base;

	// this has primary color bg and default padding
	Ref<StyleBoxFlat> style_container;

	Ref<StyleBoxFlat> style_button;
	Ref<StyleBoxFlat> style_button_pressed;
	Ref<StyleBoxFlat> style_button_focused;
	Ref<StyleBoxFlat> style_button_hovered;
	Ref<StyleBoxFlat> style_button_disabled;
	Ref<StyleBoxFlat> style_button_flat;
	Ref<StyleBoxFlat> style_button_flat_pressed;
	Ref<StyleBoxFlat> style_button_flat_focused;
	Ref<StyleBoxFlat> style_button_flat_hovered;
	Ref<StyleBoxFlat> style_button_flat_disabled;

	Ref<StyleBoxFlat> style_input;
	Ref<StyleBoxFlat> style_input_focused;
	// Ref<StyleBoxFlat> style_input_hovered;
	Ref<StyleBoxFlat> style_input_disabled;

	// content panels, they use the base color
	Ref<StyleBoxFlat> style_panel;

	// style for popup menus
	Ref<StyleBoxFlat> style_popup;

	Ref<StyleBoxFlat> style_window;
	// this style is used windows that contain unusual ui, like tabs
	Ref<StyleBoxFlat> style_special_window;

	Ref<StyleBoxFlat> style_tab_selected;
	Ref<StyleBoxFlat> style_tab_unselected;
	// Ref<StyleBoxFlat> style_tab_disabled;

	Ref<StyleBoxFlat> style_tab_container;

	// a frame that goes around a hovered element
	Ref<StyleBoxFlat> style_cursor;

	Ref<StyleBoxFlat> style_tooltip;

	Ref<StyleBoxLine> style_separator;

	// texture style boxes
	Ref<StyleBoxTexture> style_scroll_bg;
	Ref<StyleBoxTexture> style_scroll_grabber;
	Ref<StyleBoxTexture> style_scroll_grabber_hover;
	Ref<StyleBoxTexture> style_scroll_grabber_pressed;
	Ref<StyleBoxTexture> style_progress_bg;
	Ref<StyleBoxTexture> style_progress_fill;

	void _set_constants();
	void _set_icons();
	void _set_colors();

public:
	void set_thumb_size(int p_thumb_size);
	void set_scale(int p_scale);

	void set_primary_color(Color p_primary_color);
	void set_accent_color(Color p_accent_color);

	int get_thumb_size() const { return thumb_size; };
	int get_scale() const { return scale; };
	// bool is_dark_theme() const;

	EditorTheme(Color p_primary_color, Color p_accent_color, int p_scale, int p_thumb_size);
};

#endif