/*************************************************************************/
/*  editor_theme.cpp                                                     */
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

#include "editor_theme.h"

void EditorTheme::_generate_styleboxes() {
}

void EditorTheme::_generate_colors() {
}

void EditorTheme::set_base_color(Color p_base_color) {
	base_color = p_base_color;
	dark_theme = ((base_color.r + base_color.g + base_color.b) / 3.0) < 0.5;

	// white (dark theme) or black (light theme), will be used to generate the rest of the colors
	float mono_term = dark_theme ? 1.0 : 0.0;
	float mono_term_inv = 1.0 - mono_term;
	float mono_sgn = dark_theme ? 1.0 : -1.0;
	float mono_sgn_inv = -mono_sgn;
	mono_color = Color(mono_term, mono_term, mono_term, 1);
	mono_color_inv = Color(mono_term_inv, mono_term_inv, mono_term_inv, 1);

	float base_h = base_color.get_h();
	float base_s = base_color.get_s();
	float base_v = base_color.get_v();

	// darker (if dark theme) or lighter (if light theme) variations of base
	base_color_strong = base_color.blend(mono_color_inv * Color(1, 1, 1, dark_theme ? 0.227 : 0.564));
	base_color_stronger = base_color.blend(mono_color_inv * Color(1, 1, 1, dark_theme ? 0.364 : 0.866));

	contrast_color = Color::from_hsv(base_h, base_s, base_v + mono_sgn * 0.8);
	contrast_color_strong = Color::from_hsv(base_h, base_s, base_v + mono_sgn * 0.9);

	float base_alpha = 0.058;
	alpha_color = mono_color_inv * Color(1, 1, 1, base_alpha);

	font_color = contrast_color;
	font_color_muted = alpha_color;
	font_color_dim = Color::from_hsv(font_color.get_h(), font_color.get_s(), font_color.get_v() + mono_sgn_inv * 0.4);
	font_color_strong = contrast_color_strong;

	set_color("mono_color", mono_color);
	set_color("mono_color_inv", mono_color_inv);
	set_color("base_color", base_color);
	set_color("base_color_strong", base_color_strong);
	set_color("base_color_stronger", base_color_stronger);

	set_color("contrast_color", contrast_color);
	set_color("contrast_color_strong", contrast_color_strong);

	set_color("alpha_color", alpha_color);

	set_color("font_color", font_color);
	set_color("font_color_muted", font_color_muted);
	set_color("font_color_dim", font_color_dim);
	set_color("font_color_strong", font_color_strong);

	// status colors
}

void EditorTheme::set_accent_color(Color p_accent_color) {
}