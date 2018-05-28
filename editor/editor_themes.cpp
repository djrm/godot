/*************************************************************************/
/*  editor_themes.cpp                                                    */
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

#include "editor_themes.h"

#include "core/io/resource_loader.h"
#include "editor_fonts.h"
#include "editor_icons.gen.h"
#include "editor_scale.h"
#include "editor_settings.h"
#include "editor_theme.h"
#include "modules/svg/image_loader_svg.h"
#include "time.h"

static Ref<StyleBoxEmpty> make_empty_stylebox(float p_margin_left = -1, float p_margin_top = -1, float p_margin_right = -1, float p_margin_bottom = -1) {
	Ref<StyleBoxEmpty> style(memnew(StyleBoxEmpty));
	style->set_default_margin(MARGIN_LEFT, p_margin_left * EDSCALE);
	style->set_default_margin(MARGIN_RIGHT, p_margin_right * EDSCALE);
	style->set_default_margin(MARGIN_BOTTOM, p_margin_bottom * EDSCALE);
	style->set_default_margin(MARGIN_TOP, p_margin_top * EDSCALE);
	return style;
}

static Ref<StyleBoxFlat> make_flat_stylebox(Color p_color, float p_margin_left = -1, float p_margin_top = -1, float p_margin_right = -1, float p_margin_bottom = -1) {
	Ref<StyleBoxFlat> style(memnew(StyleBoxFlat));
	style->set_bg_color(p_color);
	style->set_default_margin(MARGIN_LEFT, p_margin_left * EDSCALE);
	style->set_default_margin(MARGIN_RIGHT, p_margin_right * EDSCALE);
	style->set_default_margin(MARGIN_BOTTOM, p_margin_bottom * EDSCALE);
	style->set_default_margin(MARGIN_TOP, p_margin_top * EDSCALE);
	return style;
}

static Ref<StyleBoxLine> make_line_stylebox(Color p_color, int p_thickness = 1, float p_grow = 1, bool p_vertical = false) {
	Ref<StyleBoxLine> style(memnew(StyleBoxLine));
	style->set_color(p_color);
	style->set_grow(p_grow);
	style->set_thickness(p_thickness);
	style->set_vertical(p_vertical);
	return style;
}

Ref<ImageTexture> editor_generate_icon(int p_index, bool p_convert_color, float p_scale = EDSCALE, bool p_force_filter = false) {

	Ref<ImageTexture> icon = memnew(ImageTexture);
	Ref<Image> img = memnew(Image);

	// dumb gizmo check
	bool is_gizmo = String(editor_icons_names[p_index]).begins_with("Gizmo");

	ImageLoaderSVG::create_image_from_string(img, editor_icons_sources[p_index], p_scale, true, p_convert_color);

	if ((p_scale - (float)((int)p_scale)) > 0.0 || is_gizmo || p_force_filter)
		icon->create_from_image(img); // in this case filter really helps
	else
		icon->create_from_image(img, 0);

	return icon;
}

#ifndef ADD_CONVERT_COLOR
#define ADD_CONVERT_COLOR(dictionary, old_color, new_color) dictionary[Color::html(old_color)] = Color::html(new_color)
#endif

void editor_register_and_generate_icons(Ref<EditorTheme> p_theme, bool p_dark_theme = true, int p_thumb_size = 32, bool p_only_thumbs = false) {

#ifdef SVG_ENABLED
	Dictionary colors_swap;

	colors_swap[Color::html("#cea4f1")] = Color::html("#8b6ce1"); // animation
	colors_swap[Color::html("#fc9c9c")] = Color::html("#f57389"); // spatial
	colors_swap[Color::html("#a5b7f3")] = Color::html("#678ee6"); // 2d
	colors_swap[Color::html("#708cea")] = Color::html("#2c63dd"); // 2d dark
	colors_swap[Color::html("#a5efac")] = Color::html("#54e392"); // control

	// rainbow
	colors_swap[Color::html("#ff7070")] = Color::html("#f57373"); // red
	colors_swap[Color::html("#ffeb70")] = Color::html("#f6c07a"); // yellow
	colors_swap[Color::html("#9dff70")] = Color::html("#67e680"); // green
	colors_swap[Color::html("#70ffb9")] = Color::html("#67e6bb"); // aqua
	colors_swap[Color::html("#70deff")] = Color::html("#78c3f6"); // blue
	colors_swap[Color::html("#9f70ff")] = Color::html("#8b6ce1"); // purple
	colors_swap[Color::html("#ff70ac")] = Color::html("#f57389"); // pink

	// audio gradient
	colors_swap[Color::html("#ff7a7a")] = Color::html("#f57389"); // red
	colors_swap[Color::html("#e1dc7a")] = Color::html("#f6c07a"); // yellow
	colors_swap[Color::html("#66ff9e")] = Color::html("#67e6a4"); // green

	colors_swap[Color::html("#ffd684")] = Color::html("#f6c07a"); // mesh (orange)
	colors_swap[Color::html("#68b6ff")] = Color::html("#61b9f4"); // shape (blue)

	// 3d shapes
	colors_swap[Color::html("#a2d2ff")] = Color::html("#9cd3f8"); // shape (highlight)
	colors_swap[Color::html("#2998ff")] = Color::html("#1296ef"); // shape (shadow)

	// other RGB
	colors_swap[Color::html("#ff7070")] = Color::html("#f57376"); // Color (R)
	colors_swap[Color::html("#7aff70")] = Color::html("#84e667"); // Color (G)
	colors_swap[Color::html("#70bfff")] = Color::html("#678ee6"); // Color (B)

	colors_swap[Color::html("#84c2ff")] = Color::html("#679ee6"); // selection (blue)
	colors_swap[Color::html("#ff8484")] = Color::html("#f57373"); // remove (red)
	colors_swap[Color::html("#84ffb1")] = Color::html("#67e683"); // add (green)

	colors_swap[Color::html("#ea686c")] = Color::html("#f57376"); // key xform (red)

	colors_swap[Color::html("#f57373")] = Color::html("#f57376"); // Color (R)
	colors_swap[Color::html("#67e680")] = Color::html("#84e667"); // Color (G)
	colors_swap[Color::html("#679ee6")] = Color::html("#678ee6"); // Color (B)

	// Variant types
	colors_swap[Color::html("#69ecbd")] = p_theme->get_color("Nil", "Editor");
	colors_swap[Color::html("#8da6f0")] = p_theme->get_color("bool", "Editor");
	colors_swap[Color::html("#7dc6ef")] = p_theme->get_color("int", "Editor");
	colors_swap[Color::html("#61daf4")] = p_theme->get_color("float", "Editor");
	colors_swap[Color::html("#6ba7ec")] = p_theme->get_color("String", "Editor");
	colors_swap[Color::html("#bd91f1")] = p_theme->get_color("Vector2", "Editor");
	colors_swap[Color::html("#f191a5")] = p_theme->get_color("Rect2", "Editor");
	colors_swap[Color::html("#e286f0")] = p_theme->get_color("Vector3", "Editor");
	colors_swap[Color::html("#c4ec69")] = p_theme->get_color("Transform2D", "Editor");
	colors_swap[Color::html("#f77070")] = p_theme->get_color("Plane", "Editor");
	colors_swap[Color::html("#ec69a3")] = p_theme->get_color("Quat", "Editor");
	colors_swap[Color::html("#ee7991")] = p_theme->get_color("AABB", "Editor");
	colors_swap[Color::html("#e3ec69")] = p_theme->get_color("Basis", "Editor");
	colors_swap[Color::html("#f6a86e")] = p_theme->get_color("Transform", "Editor");
	colors_swap[Color::html("#6993ec")] = p_theme->get_color("NodePath", "Editor");
	colors_swap[Color::html("#69ec9a")] = p_theme->get_color("RID", "Editor");
	colors_swap[Color::html("#79f3e8")] = p_theme->get_color("Object", "Editor");
	colors_swap[Color::html("#77edb1")] = p_theme->get_color("Dictionary", "Editor");

	// these ones should be converted even if we are using a dark theme
	colors_swap[Color::html("#ff5d5d")] = p_theme->get_color("error_color", "Editor");
	colors_swap[Color::html("#45ff8b")] = p_theme->get_color("success_color", "Editor");
	colors_swap[Color::html("#ffdd65")] = p_theme->get_color("warning_color", "Editor");

	// missing (Frozen VU)
	// missing (Gizmo)
	// missing (KeyCall)
	// missing (Sky colors)
	// missing (Color Ramp)

	if (!p_dark_theme) {
		colors_swap[Color::html("#e0e0e0")] = Color::html("#4f4f4f"); // common icon color
		colors_swap[Color::html("#ffffff")] = Color::html("#000000"); // white
		colors_swap[Color::html("#b4b4b4")] = Color::html("#000000"); // script darker color
	}

	List<String> exceptions;
	exceptions.push_back("EditorPivot");
	exceptions.push_back("EditorHandle");
	exceptions.push_back("Editor3DHandle");
	exceptions.push_back("Godot");
	exceptions.push_back("PanoramaSky");
	exceptions.push_back("ProceduralSky");
	exceptions.push_back("EditorControlAnchor");
	exceptions.push_back("DefaultProjectIcon");
	exceptions.push_back("GuiCloseCustomizable");
	exceptions.push_back("GuiGraphNodePort");
	exceptions.push_back("GuiResizer");
	exceptions.push_back("ZoomMore");
	exceptions.push_back("ZoomLess");
	exceptions.push_back("ZoomReset");
	exceptions.push_back("LockViewport");
	exceptions.push_back("GroupViewport");

	ImageLoaderSVG::set_convert_colors(&colors_swap);

	// generate icons
	if (!p_only_thumbs)
		for (int i = 0; i < editor_icons_count; i++) {
			List<String>::Element *is_exception = exceptions.find(editor_icons_names[i]);
			if (is_exception) exceptions.erase(is_exception);
			Ref<ImageTexture> icon = editor_generate_icon(i, !is_exception);
			p_theme->set_icon(editor_icons_names[i], "EditorIcons", icon);
		}

	// generate thumb files with the given thumb size
	bool force_filter = !(p_thumb_size == 64 || p_thumb_size == 32); // we don't need filter with original resolution
	if (p_thumb_size >= 64) {
		float scale = (float)p_thumb_size / 64.0 * EDSCALE;
		for (int i = 0; i < editor_bg_thumbs_count; i++) {
			int index = editor_bg_thumbs_indices[i];
			List<String>::Element *is_exception = exceptions.find(editor_icons_names[index]);
			if (is_exception) exceptions.erase(is_exception);
			Ref<ImageTexture> icon = editor_generate_icon(index, !p_dark_theme && !is_exception, scale, force_filter);
			p_theme->set_icon(editor_icons_names[index], "EditorIcons", icon);
		}
	} else {
		float scale = (float)p_thumb_size / 32.0 * EDSCALE;
		for (int i = 0; i < editor_md_thumbs_count; i++) {
			int index = editor_md_thumbs_indices[i];
			List<String>::Element *is_exception = exceptions.find(editor_icons_names[index]);
			if (is_exception) exceptions.erase(is_exception);
			Ref<ImageTexture> icon = editor_generate_icon(index, !p_dark_theme && !is_exception, scale, force_filter);
			p_theme->set_icon(editor_icons_names[index], "EditorIcons", icon);
		}
	}

	ImageLoaderSVG::set_convert_colors(NULL);
#else
	print_line("Sorry no icons for you");
#endif
}

Ref<Theme> create_editor_theme(const Ref<Theme> p_theme) {

	const float default_contrast = 0.25;

	//Theme settings
	Color accent_color = EDITOR_DEF("interface/theme/accent_color", Color::html("#699ce8"));
	Color primary_color = EDITOR_DEF("interface/theme/base_color", Color::html("#323b4f"));
	float contrast = EDITOR_DEF("interface/theme/contrast", default_contrast);

	int preset = EDITOR_DEF("interface/theme/preset", 0);
	int icon_font_color_setting = EDITOR_DEF("interface/theme/icon_and_font_color", 0);
	bool highlight_tabs = EDITOR_DEF("interface/theme/highlight_tabs", false);
	int border_size = EDITOR_DEF("interface/theme/border_size", 1);

	bool use_gn_headers = EDITOR_DEF("interface/theme/use_graph_node_headers", false);

	Color script_bg_color = EDITOR_DEF("text_editor/highlighting/background_color", Color(0, 0, 0, 0));

	Color preset_accent_color;
	Color preset_base_color;
	float preset_contrast;
	switch (preset) {
		case 0: { // Default
			preset_accent_color = Color::html("#699ce8");
			preset_base_color = Color::html("#323b4f");
			preset_contrast = default_contrast;
		} break;
		case 1: { // Grey
			preset_accent_color = Color::html("#b8e4ff");
			preset_base_color = Color::html("#3d3d3d");
			preset_contrast = 0.2;
		} break;
		case 2: { // Godot 2
			preset_accent_color = Color::html("#86ace2");
			preset_base_color = Color::html("#3C3A44");
			preset_contrast = 0.25;
		} break;
		case 3: { // Arc
			preset_accent_color = Color::html("#5294e2");
			preset_base_color = Color::html("#383c4a");
			preset_contrast = 0.25;
		} break;
		case 4: { // Light
			preset_accent_color = Color::html("#3f75ed");
			preset_base_color = Color::html("#eff1f5");
			preset_contrast = 0.08;
		} break;
		case 5: { // Alien
			preset_accent_color = Color::html("#1bfe99");
			preset_base_color = Color::html("#2f373f");
			preset_contrast = 0.25;
		}
		default: { // Custom
			accent_color = EDITOR_DEF("interface/theme/accent_color", Color::html("#699ce8"));
			primary_color = EDITOR_DEF("interface/theme/base_color", Color::html("#323b4f"));
			contrast = EDITOR_DEF("interface/theme/contrast", default_contrast);
		}
	}

	if (preset != 6) {
		accent_color = preset_accent_color;
		primary_color = preset_base_color;
		contrast = preset_contrast;
		EditorSettings::get_singleton()->set_initial_value("interface/theme/accent_color", accent_color);
		EditorSettings::get_singleton()->set_initial_value("interface/theme/base_color", primary_color);
		EditorSettings::get_singleton()->set_initial_value("interface/theme/contrast", contrast);
	}

	EditorSettings::get_singleton()->set_manually("interface/theme/preset", preset);
	EditorSettings::get_singleton()->set_manually("interface/theme/accent_color", accent_color);
	EditorSettings::get_singleton()->set_manually("interface/theme/base_color", primary_color);
	EditorSettings::get_singleton()->set_manually("interface/theme/contrast", contrast);

	//Colors
	int AUTO_COLOR = 0;
	int LIGHT_COLOR = 2;
	bool dark_theme = (icon_font_color_setting == AUTO_COLOR && ((primary_color.r + primary_color.g + primary_color.b) / 3.0) < 0.5) || icon_font_color_setting == LIGHT_COLOR;

	const Color dark_color_1 = primary_color.linear_interpolate(Color(0, 0, 0, 1), contrast);
	const Color dark_color_2 = primary_color.linear_interpolate(Color(0, 0, 0, 1), contrast * 1.5);
	const Color dark_color_3 = primary_color.linear_interpolate(Color(0, 0, 0, 1), contrast * 2);

	const Color background_color = dark_color_2;

	// white (dark theme) or black (light theme), will be used to generate the rest of the colors
	const Color mono_color = dark_theme ? Color(1, 1, 1) : Color(0, 0, 0);

	const Color contrast_color_1 = primary_color.linear_interpolate(mono_color, MAX(contrast, default_contrast));
	const Color contrast_color_2 = primary_color.linear_interpolate(mono_color, MAX(contrast * 1.5, default_contrast * 1.5));

	const Color font_color = mono_color.linear_interpolate(primary_color, 0.25);
	const Color font_color_hl = mono_color.linear_interpolate(primary_color, 0.15);
	const Color font_color_disabled = Color(mono_color.r, mono_color.g, mono_color.b, 0.3);
	const Color font_color_selection = Color::html("#7d7d7d");
	const Color color_disabled = mono_color.inverted().linear_interpolate(primary_color, 0.7);
	const Color color_disabled_bg = mono_color.inverted().linear_interpolate(primary_color, 0.9);

	const Color separator_color = Color(mono_color.r, mono_color.g, mono_color.b, 0.1);

	const Color highlight_color = Color(mono_color.r, mono_color.g, mono_color.b, 0.2);

	// theme->set_color("accent_color", "Editor", accent_color);
	// theme->set_color("highlight_color", "Editor", highlight_color);
	// theme->set_color("base_color", "Editor", base_color);
	// theme->set_color("dark_color_1", "Editor", dark_color_1);
	// theme->set_color("dark_color_2", "Editor", dark_color_2);
	// theme->set_color("dark_color_3", "Editor", dark_color_3);
	// theme->set_color("contrast_color_1", "Editor", contrast_color_1);
	// theme->set_color("contrast_color_2", "Editor", contrast_color_2);

	// theme->set_color("font_color", "Editor", font_color);
	// theme->set_color("highlighted_font_color", "Editor", font_color_hl);
	// theme->set_color("disabled_font_color", "Editor", font_color_disabled);
	// theme->set_color("select_color", "Editor", accent_color);
	// theme->set_color("mono_color", "Editor", mono_color);

	// Status colors
	Color success_color = Color::html("#57eb78");
	Color warning_color = Color::html("#f0c151");
	Color error_color = Color::html("#f05d5d");
	// theme->set_color("success_color", "Editor", success_color);
	// theme->set_color("warning_color", "Editor", warning_color);
	// theme->set_color("error_color", "Editor", error_color);

	// // label colors
	// theme->set_color("x", "Editor", Color(1, .1, .1).linear_interpolate(accent_color, 0.3));
	// theme->set_color("y", "Editor", Color(.1, .9, .1).linear_interpolate(accent_color, 0.3));
	// theme->set_color("z", "Editor", Color(0, 0.3, 1).linear_interpolate(accent_color, 0.3));

	// // Variant type colors
	// theme->set_color("Nil", "Editor", Color::html("#67e6bb")); // Any
	// theme->set_color("bool", "Editor", Color::html("#678ee6"));
	// theme->set_color("int", "Editor", Color::html("#78ccf6"));
	// theme->set_color("float", "Editor", Color::html("#78e5f6"));
	// theme->set_color("String", "Editor", Color::html("#6777e6"));
	// theme->set_color("Vector2", "Editor", Color::html("#8b6ce1"));
	// theme->set_color("Rect2", "Editor", Color::html("#f57389"));
	// theme->set_color("Vector3", "Editor", Color::html("#b66ce1"));
	// theme->set_color("Transform2D", "Editor", Color::html("#84e667"));
	// theme->set_color("Plane", "Editor", Color::html("#f57376"));
	// theme->set_color("Quat", "Editor", Color::html("#f573b0"));
	// theme->set_color("AABB", "Editor", Color::html("#f573a1"));
	// theme->set_color("Basis", "Editor", Color::html("#e6c167"));
	// theme->set_color("Transform", "Editor", Color::html("#f8aa76"));
	// theme->set_color("Color", "Editor", Color::html("#719fc0"));
	// theme->set_color("NodePath", "Editor", Color::html("#6f67e6"));
	// theme->set_color("RID", "Editor", Color::html("#67e695"));
	// theme->set_color("Object", "Editor", Color::html("#67e67a"));
	// theme->set_color("Dictionary", "Editor", Color::html("#67e69b"));
	// theme->set_color("Array", "Editor", Color::html("#92adc1"));
	// theme->set_color("PoolByteArray", "Editor", Color::html("#93f1b9"));
	// theme->set_color("PoolIntArray", "Editor", Color::html("#99d9f8"));
	// theme->set_color("PoolRealArray", "Editor", Color::html("#8ae9f7"));
	// theme->set_color("PoolStringArray", "Editor", Color::html("#919ced"));
	// theme->set_color("PoolVector2Array", "Editor", Color::html("#9e84e6"));
	// theme->set_color("PoolVector3Array", "Editor", Color::html("#c182e5"));
	// theme->set_color("PoolColorArray", "Editor", Color::html("#adc8db"));

	// REMOVE
	const int default_margin_size = 4 * EDSCALE;
	const int popup_margin_size = default_margin_size * 2;
	const int tab_default_margin_side = 10 * EDSCALE * 2;
	const int tab_default_margin_vertical = 5 * EDSCALE * 2;
	const int border_width = 1 * EDSCALE;
	Color shadow_color = Color(0, 0, 0, .1);

	const int thumb_size = EDITOR_DEF("filesystem/file_dialog/thumbnail_size", 64);

	Ref<EditorTheme> theme;
	if (p_theme != NULL) {
		theme = Object::cast_to<EditorTheme>(*p_theme);
		theme->set_primary_color(primary_color);
		theme->set_accent_color(accent_color);
		theme->set_thumb_size(thumb_size);
		theme->set_scale(EDSCALE);
	} else {
		theme = Ref<EditorTheme>(memnew(EditorTheme(Color::html("#3c4571"), accent_color, EDSCALE, thumb_size)));
	}

	// 2d grid color
	const Color grid_minor_color = mono_color * Color(1.0, 1.0, 1.0, 0.07);
	const Color grid_major_color = Color(font_color_disabled.r, font_color_disabled.g, font_color_disabled.b, 0.15);
	theme->set_color("grid_major_color", "Editor", grid_major_color);
	theme->set_color("grid_minor_color", "Editor", grid_minor_color);

	bool keep_icons = false;
	bool keep_thumbs = false;
	if (p_theme != NULL) {
		if (p_theme->has_constant("scale", "Editor") && p_theme->has_constant("dark_theme", "Editor"))
			keep_icons = (fabs(p_theme->get_constant("scale", "Editor") - EDSCALE) < 0.00001 && p_theme->get_constant("dark_theme", "Editor") == dark_theme);
		if (p_theme->has_constant("thumb_size", "Editor"))
			keep_thumbs = (fabs((double)p_theme->get_constant("thumb_size", "Editor") - thumb_size) < 0.00001);
	}

	// the resolution and the icon color (dark_theme bool) has changed, so we do not regenerate the icons
	if (!keep_icons)
		editor_register_and_generate_icons(theme, dark_theme, thumb_size);

	// thumbnail size has changed, so we regenerate the medium sizes
	if (!keep_thumbs)
		editor_register_and_generate_icons(theme, dark_theme, thumb_size, true);

	editor_register_fonts(theme);

	// Highlighted tabs and border width
	Color tab_color = highlight_tabs ? primary_color.linear_interpolate(font_color, contrast) : primary_color;

	Ref<StyleBoxLine> style_popup_separator(memnew(StyleBoxLine));
	style_popup_separator->set_color(separator_color);
	style_popup_separator->set_grow(popup_margin_size - MAX(EDSCALE, border_width));
	style_popup_separator->set_thickness(MAX(EDSCALE, border_width));

	Ref<StyleBoxEmpty> style_empty = make_empty_stylebox(default_margin_size * EDSCALE, default_margin_size * EDSCALE, default_margin_size * EDSCALE, default_margin_size * EDSCALE);
	Ref<StyleBoxFlat> style_fempty = make_flat_stylebox(Color(0, 0, 0, 0), default_margin_size * EDSCALE, default_margin_size * EDSCALE, default_margin_size * EDSCALE, default_margin_size * EDSCALE);
	theme->set_stylebox("Empty", "EditorStyles", style_fempty);

	// H/VSplitContainer
	// theme->set_stylebox("bg", "VSplitContainer", make_stylebox(theme->get_icon("GuiVsplitBg", "EditorIcons"), 1, 1, 1, 1));
	// theme->set_stylebox("bg", "HSplitContainer", make_stylebox(theme->get_icon("GuiHsplitBg", "EditorIcons"), 1, 1, 1, 1));

	// HSlider
	theme->set_stylebox("slider", "HSlider", make_flat_stylebox(dark_color_3, 0, default_margin_size / 2, 0, default_margin_size / 2));
	theme->set_stylebox("grabber_area", "HSlider", make_flat_stylebox(contrast_color_1, 0, default_margin_size / 2, 0, default_margin_size / 2));

	// VSlider
	theme->set_stylebox("slider", "VSlider", make_flat_stylebox(dark_color_3, default_margin_size / 2, 0, default_margin_size / 2, 0));
	theme->set_stylebox("grabber_area", "VSlider", make_flat_stylebox(contrast_color_1, default_margin_size / 2, 0, default_margin_size / 2, 0));

	// GraphEdit
	theme->set_color("grid_major", "GraphEdit", grid_major_color);
	theme->set_color("grid_minor", "GraphEdit", grid_minor_color);

	// GraphNode

	const float mv = dark_theme ? 0.0 : 1.0;
	const float mv2 = 1.0 - mv;
	const int gn_margin_side = 28;
	Ref<StyleBoxFlat> graphsb = make_flat_stylebox(Color(mv, mv, mv, 0.7), gn_margin_side, 24, gn_margin_side, 5);
	graphsb->set_border_width_all(border_width);
	graphsb->set_border_color_all(Color(mv2, mv2, mv2, 0.9));
	Ref<StyleBoxFlat> graphsbselected = make_flat_stylebox(Color(mv, mv, mv, 0.9), gn_margin_side, 24, gn_margin_side, 5);
	graphsbselected->set_border_width_all(border_width);
	graphsbselected->set_border_color_all(Color(accent_color.r, accent_color.g, accent_color.b, 0.9));
	graphsbselected->set_shadow_size(8 * EDSCALE);
	graphsbselected->set_shadow_color(shadow_color);
	Ref<StyleBoxFlat> graphsbcomment = make_flat_stylebox(Color(mv, mv, mv, 0.3), gn_margin_side, 24, gn_margin_side, 5);
	graphsbcomment->set_border_width_all(border_width);
	graphsbcomment->set_border_color_all(Color(mv2, mv2, mv2, 0.9));
	Ref<StyleBoxFlat> graphsbcommentselected = make_flat_stylebox(Color(mv, mv, mv, 0.4), gn_margin_side, 24, gn_margin_side, 5);
	graphsbcommentselected->set_border_width_all(border_width);
	graphsbcommentselected->set_border_color_all(Color(mv2, mv2, mv2, 0.9));
	Ref<StyleBoxFlat> graphsbbreakpoint = graphsbselected->duplicate();
	graphsbbreakpoint->set_draw_center(false);
	graphsbbreakpoint->set_border_color_all(warning_color);
	graphsbbreakpoint->set_shadow_color(warning_color * Color(1.0, 1.0, 1.0, 0.1));
	Ref<StyleBoxFlat> graphsbposition = graphsbselected->duplicate();
	graphsbposition->set_draw_center(false);
	graphsbposition->set_border_color_all(error_color);
	graphsbposition->set_shadow_color(error_color * Color(1.0, 1.0, 1.0, 0.2));

	if (use_gn_headers) {
		graphsb->set_border_width(MARGIN_TOP, 24 * EDSCALE);
		graphsbselected->set_border_width(MARGIN_TOP, 24 * EDSCALE);
		graphsbcomment->set_border_width(MARGIN_TOP, 24 * EDSCALE);
		graphsbcommentselected->set_border_width(MARGIN_TOP, 24 * EDSCALE);
	}

	theme->set_stylebox("frame", "GraphNode", graphsb);
	theme->set_stylebox("selectedframe", "GraphNode", graphsbselected);
	theme->set_stylebox("comment", "GraphNode", graphsbcomment);
	theme->set_stylebox("commentfocus", "GraphNode", graphsbcommentselected);
	theme->set_stylebox("breakpoint", "GraphNode", graphsbbreakpoint);
	theme->set_stylebox("position", "GraphNode", graphsbposition);

	Color default_node_color = Color(mv2, mv2, mv2);
	theme->set_color("title_color", "GraphNode", default_node_color);
	default_node_color.a = 0.7;
	theme->set_color("close_color", "GraphNode", default_node_color);

	// Information on 3D viewport TODO: ADD to editor_theme
	// Ref<StyleBoxFlat> style_info_3d_viewport = style_default->duplicate();
	// style_info_3d_viewport->set_bg_color(style_info_3d_viewport->get_bg_color() * Color(1, 1, 1, 0.5));
	// style_info_3d_viewport->set_border_width_all(0);
	// theme->set_stylebox("Information3dViewport", "EditorStyles", style_info_3d_viewport);

	// adaptive script theme constants
	// for comments and elements with lower relevance
	const Color dim_color = Color(font_color.r, font_color.g, font_color.b, 0.5);

	const float mono_value = mono_color.r;
	const Color alpha1 = Color(mono_value, mono_value, mono_value, 0.07);
	const Color alpha2 = Color(mono_value, mono_value, mono_value, 0.14);
	const Color alpha3 = Color(mono_value, mono_value, mono_value, 0.5);
	const Color alpha4 = Color(mono_value, mono_value, mono_value, 0.7);

	// editor main color
	const Color main_color = Color::html(dark_theme ? "#57b3ff" : "#0480ff");

	const Color symbol_color = Color::html("#5792ff").linear_interpolate(mono_color, dark_theme ? 0.5 : 0.3);
	const Color keyword_color = Color::html("#ff7185");
	const Color basetype_color = Color::html(dark_theme ? "#42ffc2" : "#00c161");
	const Color type_color = basetype_color.linear_interpolate(mono_color, dark_theme ? 0.7 : 0.5);
	const Color comment_color = dim_color;
	const Color string_color = Color::html(dark_theme ? "#ffd942" : "#ffd118").linear_interpolate(mono_color, dark_theme ? 0.5 : 0.3);

	const Color function_definition_color = Color::html(dark_theme ? "#01e1ff" : "#00a5ba");
	const Color node_path_color = Color::html(dark_theme ? "64c15a" : "#518b4b");

	const Color te_background_color = Color(0, 0, 0, 0);
	const Color completion_background_color = primary_color;
	const Color completion_selected_color = alpha1;
	const Color completion_existing_color = alpha2;
	const Color completion_scroll_color = alpha1;
	const Color completion_font_color = font_color;
	const Color text_color = font_color;
	const Color line_number_color = dim_color;
	const Color caret_color = mono_color;
	const Color caret_background_color = mono_color.inverted();
	const Color text_selected_color = dark_color_3;
	const Color selection_color = alpha2;
	const Color brace_mismatch_color = error_color;
	const Color current_line_color = alpha1;
	const Color line_length_guideline_color = warning_color;
	const Color word_highlighted_color = alpha1;
	const Color number_color = basetype_color.linear_interpolate(mono_color, dark_theme ? 0.5 : 0.3);
	const Color function_color = main_color;
	const Color member_variable_color = main_color.linear_interpolate(mono_color, 0.6);
	const Color mark_color = Color(error_color.r, error_color.g, error_color.b, 0.3);
	const Color breakpoint_color = error_color;
	const Color code_folding_color = alpha4;
	const Color search_result_color = alpha1;
	const Color search_result_border_color = alpha4;

	EditorSettings *setting = EditorSettings::get_singleton();
	String text_editor_color_theme = setting->get("text_editor/theme/color_theme");
	if (text_editor_color_theme == "Adaptive") {
		setting->set_initial_value("text_editor/highlighting/symbol_color", symbol_color, true);
		setting->set_initial_value("text_editor/highlighting/keyword_color", keyword_color, true);
		setting->set_initial_value("text_editor/highlighting/base_type_color", basetype_color, true);
		setting->set_initial_value("text_editor/highlighting/engine_type_color", type_color, true);
		setting->set_initial_value("text_editor/highlighting/comment_color", comment_color, true);
		setting->set_initial_value("text_editor/highlighting/string_color", string_color, true);
		setting->set_initial_value("text_editor/highlighting/background_color", background_color, true);
		setting->set_initial_value("text_editor/highlighting/completion_background_color", completion_background_color, true);
		setting->set_initial_value("text_editor/highlighting/completion_selected_color", completion_selected_color, true);
		setting->set_initial_value("text_editor/highlighting/completion_existing_color", completion_existing_color, true);
		setting->set_initial_value("text_editor/highlighting/completion_scroll_color", completion_scroll_color, true);
		setting->set_initial_value("text_editor/highlighting/completion_font_color", completion_font_color, true);
		setting->set_initial_value("text_editor/highlighting/text_color", text_color, true);
		setting->set_initial_value("text_editor/highlighting/line_number_color", line_number_color, true);
		setting->set_initial_value("text_editor/highlighting/caret_color", caret_color, true);
		setting->set_initial_value("text_editor/highlighting/caret_background_color", caret_background_color, true);
		setting->set_initial_value("text_editor/highlighting/text_selected_color", text_selected_color, true);
		setting->set_initial_value("text_editor/highlighting/selection_color", selection_color, true);
		setting->set_initial_value("text_editor/highlighting/brace_mismatch_color", brace_mismatch_color, true);
		setting->set_initial_value("text_editor/highlighting/current_line_color", current_line_color, true);
		setting->set_initial_value("text_editor/highlighting/line_length_guideline_color", line_length_guideline_color, true);
		setting->set_initial_value("text_editor/highlighting/word_highlighted_color", word_highlighted_color, true);
		setting->set_initial_value("text_editor/highlighting/number_color", number_color, true);
		setting->set_initial_value("text_editor/highlighting/function_color", function_color, true);
		setting->set_initial_value("text_editor/highlighting/member_variable_color", member_variable_color, true);
		setting->set_initial_value("text_editor/highlighting/mark_color", mark_color, true);
		setting->set_initial_value("text_editor/highlighting/breakpoint_color", breakpoint_color, true);
		setting->set_initial_value("text_editor/highlighting/code_folding_color", code_folding_color, true);
		setting->set_initial_value("text_editor/highlighting/search_result_color", search_result_color, true);
		setting->set_initial_value("text_editor/highlighting/search_result_border_color", search_result_border_color, true);

		setting->set_initial_value("text_editor/highlighting/gdscript/function_definition_color", function_definition_color, true);
		setting->set_initial_value("text_editor/highlighting/gdscript/node_path_color", node_path_color, true);
	} else if (text_editor_color_theme == "Default") {
		setting->set_initial_value("text_editor/highlighting/symbol_color", Color::html("badfff"), true);
		setting->set_initial_value("text_editor/highlighting/keyword_color", Color::html("ffffb3"), true);
		setting->set_initial_value("text_editor/highlighting/base_type_color", Color::html("a4ffd4"), true);
		setting->set_initial_value("text_editor/highlighting/engine_type_color", Color::html("83d3ff"), true);
		setting->set_initial_value("text_editor/highlighting/comment_color", Color::html("676767"), true);
		setting->set_initial_value("text_editor/highlighting/string_color", Color::html("ef6ebe"), true);
		setting->set_initial_value("text_editor/highlighting/background_color", Color::html("3b000000"), true);
		setting->set_initial_value("text_editor/highlighting/completion_background_color", Color::html("2C2A32"), true);
		setting->set_initial_value("text_editor/highlighting/completion_selected_color", Color::html("434244"), true);
		setting->set_initial_value("text_editor/highlighting/completion_existing_color", Color::html("21dfdfdf"), true);
		setting->set_initial_value("text_editor/highlighting/completion_scroll_color", Color::html("ffffff"), true);
		setting->set_initial_value("text_editor/highlighting/completion_font_color", Color::html("aaaaaa"), true);
		setting->set_initial_value("text_editor/highlighting/text_color", Color::html("aaaaaa"), true);
		setting->set_initial_value("text_editor/highlighting/line_number_color", Color::html("66aaaaaa"), true);
		setting->set_initial_value("text_editor/highlighting/caret_color", Color::html("aaaaaa"), true);
		setting->set_initial_value("text_editor/highlighting/caret_background_color", Color::html("000000"), true);
		setting->set_initial_value("text_editor/highlighting/text_selected_color", Color::html("000000"), true);
		setting->set_initial_value("text_editor/highlighting/selection_color", Color::html("6ca9c2"), true);
		setting->set_initial_value("text_editor/highlighting/brace_mismatch_color", Color(1, 0.2, 0.2), true);
		setting->set_initial_value("text_editor/highlighting/current_line_color", Color(0.3, 0.5, 0.8, 0.15), true);
		setting->set_initial_value("text_editor/highlighting/line_length_guideline_color", Color(0.3, 0.5, 0.8, 0.1), true);
		setting->set_initial_value("text_editor/highlighting/word_highlighted_color", Color(0.8, 0.9, 0.9, 0.15), true);
		setting->set_initial_value("text_editor/highlighting/number_color", Color::html("EB9532"), true);
		setting->set_initial_value("text_editor/highlighting/function_color", Color::html("66a2ce"), true);
		setting->set_initial_value("text_editor/highlighting/member_variable_color", Color::html("e64e59"), true);
		setting->set_initial_value("text_editor/highlighting/mark_color", Color(1.0, 0.4, 0.4, 0.4), true);
		setting->set_initial_value("text_editor/highlighting/breakpoint_color", Color(0.8, 0.8, 0.4, 0.2), true);
		setting->set_initial_value("text_editor/highlighting/code_folding_color", Color(0.8, 0.8, 0.8, 0.8), true);
		setting->set_initial_value("text_editor/highlighting/search_result_color", Color(0.05, 0.25, 0.05, 1), true);
		setting->set_initial_value("text_editor/highlighting/search_result_border_color", Color(0.1, 0.45, 0.1, 1), true);

		setting->set_initial_value("text_editor/highlighting/gdscript/function_definition_color", Color::html("#01e1ff"), true);
		setting->set_initial_value("text_editor/highlighting/gdscript/node_path_color", Color::html("#64c15a"), true);
	}

	return theme;
}

Ref<Theme> create_custom_theme(const Ref<Theme> p_theme) {
	Ref<Theme> theme;

	String custom_theme = EditorSettings::get_singleton()->get("interface/theme/custom_theme");
	if (custom_theme != "") {
		theme = ResourceLoader::load(custom_theme);
	}

	if (!theme.is_valid()) {
		theme = create_editor_theme(p_theme);
	}

	return theme;
}
