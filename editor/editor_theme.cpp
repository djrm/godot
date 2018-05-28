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

void EditorTheme::_set_colors() {

	// Editor background
	style_background->set_bg_color(background_color);

	// base styles
	style_container->set_bg_color(primary_color);
	style_container->set_border_color_all(separator_color);
	style_panel->set_bg_color(base_color);

	// tab
	style_tab_selected->set_bg_color(primary_color);
	style_tab_selected->set_border_color_all(separator_color);
	set_color("font_color_fg", "TabContainer", font_color);
	set_color("font_color_bg", "TabContainer", font_color_muted);
	set_color("font_color_fg", "Tabs", font_color);
	set_color("font_color_bg", "Tabs", font_color_muted);

	// BUTTONS
	style_button->set_bg_color(contrast_color);
	style_button_pressed->set_bg_color(accent_color);
	style_button_focused->set_bg_color(contrast_color_strong);
	style_button_hovered->set_bg_color(contrast_color_strong);
	// style_button_disabled->set_bg_color(contrast_color_strong);
	// make icon color value bigger because icon image is not complete white (TODO: maybe we dont need this)
	set_color("icon_color_pressed", "Button", Color(accent_color.r * 1.15, accent_color.g * 1.15, accent_color.b * 1.15, accent_color.a));

	set_color("font_color", "Button", base_color);
	set_color("font_color_hover", "Button", base_color);
	set_color("font_color_pressed", "Button", accent_color);
	set_color("font_color_disabled", "Button", primary_color);
	set_color("icon_color_hover", "Button", base_color);
	set_color("font_color", "OptionButton", base_color);
	set_color("font_color_hover", "OptionButton", base_color);
	set_color("font_color_pressed", "OptionButton", accent_color);
	set_color("font_color_disabled", "OptionButton", primary_color);
	set_color("icon_color_hover", "OptionButton", base_color);

	const String classes[] = { "CheckButton", "CheckBox", "MenuButton", "ToolButton", "LinkButton" };
	for (int i = 0; i < 5; i++) {
		set_color("font_color", classes[i], font_color);
		set_color("font_color_hover", classes[i], font_color_strong);
		set_color("font_color_pressed", classes[i], accent_color);
		set_color("font_color_disabled", classes[i], font_color_muted);
		set_color("icon_color_hover", classes[i], font_color_strong);
	}

	// INPUTS (LINE EDIT + TEXT EDIT)
	style_input->set_bg_color(separation_color);
	style_input->set_border_color_all(separator_color);
	style_input_focused->set_border_color_all(accent_color);
	// style_input_disabled->set_border_color_all(font_color_muted);
	set_color("read_only", "LineEdit", font_color_muted);
	set_color("font_color", "LineEdit", font_color);
	set_color("cursor_color", "LineEdit", accent_color);
	set_color("selection_color", "LineEdit", accent_color);

	set_color("font_color", "TextEdit", font_color);
	set_color("caret_color", "TextEdit", accent_color);
	set_color("selection_color", "TextEdit", accent_color);

	style_popup->set_bg_color(primary_color);
	style_popup->set_border_color_all(contrast_color);
	const Color shadow_color = Color(0, 0, 0, dark_theme ? 0.3 : 0.1);
	style_popup->set_shadow_color(shadow_color);

	set_color("font_color", "PopupMenu", font_color);
	set_color("font_color_hover", "PopupMenu", font_color_strong);
	set_color("font_color_accel", "PopupMenu", font_color_muted);
	set_color("font_color_disabled", "PopupMenu", font_color_muted);

	style_window->set_bg_color(primary_color);
	set_color("title_color", "WindowDialog", font_color);
	style_special_window->set_bg_color(background_color);
	//style_special_window->set_border_color_all(highlight_tabs ? tab_color : dark_color_2);

	set_color("font_color", "Label", font_color);
	set_color("font_color_shadow", "Label", Color(0, 0, 0, 0));

	set_color("default_color", "RichTextLabel", font_color);
	set_color("font_color_shadow", "RichTextLabel", Color(0, 0, 0, 0));

	// Inspector (TODO: check)
	set_color("font_color", "Inspector", font_color);
	//depth colors
	int max_depth = 10;
	for (int depth = 0; depth < max_depth; depth++) {
		Color depth_color = accent_color;
		float h = (float)(depth + 1) / (float)(max_depth + 1);
		float s = depth_color.get_s() * 0.7;
		float v = depth_color.get_v() * 1.2;
		depth_color.set_hsv(h, s, v);
		set_color("depth" + itos(depth), "Inspector", depth_color);
	}
	set_color("category_bg", "Inspector", Color(0.0, 0.0, 0.0, 0.5));
	set_color("category_font_color", "Inspector", font_color);
	set_color("section_bg_color", "Inspector", mono_color * Color(1, 1, 1, 0.03));
	set_color("section_font_color", "Inspector", mono_color * Color(1, 1, 1, 0.3));
	set_color("section_font_hl_color", "Inspector", mono_color * Color(1, 1, 1, 0.4));

	set_color("files_disabled", "FileDialog", font_color_muted);

	set_color("headline_color", "EditorHelp", mono_color);

	// Tree
	set_color("custom_button_font_highlight", "Tree", font_color_strong);
	set_color("font_color", "Tree", font_color);
	set_color("font_color_selected", "Tree", accent_color);
	set_color("title_button_color", "Tree", font_color);
	set_color("guide_color", "Tree", separator_color);
	set_color("drop_position_color", "Tree", accent_color);

	// TODO: change this
	Color prop_category_color = base_color.linear_interpolate(mono_color, 0.12);
	Color prop_section_color = base_color.linear_interpolate(mono_color, 0.09);
	Color prop_subsection_color = base_color.linear_interpolate(mono_color, 0.06);
	set_color("prop_category", "Editor", prop_category_color);
	set_color("prop_section", "Editor", prop_section_color);
	set_color("prop_subsection", "Editor", prop_subsection_color);
	set_color("drop_position_color", "Tree", accent_color);

	// ItemList
	set_color("font_color", "ItemList", font_color);
	set_color("font_color_selected", "ItemList", font_color_strong);
	set_color("guide_color", "ItemList", separator_color);

	style_cursor->set_border_color_all(contrast_color_strong);

	// Tooltip
	style_tooltip->set_bg_color(Color(mono_color.r, mono_color.g, mono_color.b, 0.9));
	style_tooltip->set_border_color_all(mono_color);
	set_color("font_color", "TooltipLabel", font_color.inverted());
	set_color("font_color_shadow", "TooltipLabel", mono_color.inverted() * Color(1, 1, 1, 0.1));

	set_color("font_color", "ProgressBar", font_color);
}

static void set_default_margins(Ref<StyleBox> p_sb, int p_margin_top, int p_margin_right, int p_margin_bottom, int p_margin_left) {
	p_sb->set_default_margin(MARGIN_TOP, p_margin_top);
	p_sb->set_default_margin(MARGIN_RIGHT, p_margin_right);
	p_sb->set_default_margin(MARGIN_BOTTOM, p_margin_bottom);
	p_sb->set_default_margin(MARGIN_LEFT, p_margin_left);
}
static void set_default_margins_h_v(Ref<StyleBox> p_sb, int p_margin_horizontal, int p_margin_vertical) {
	set_default_margins(p_sb, p_margin_vertical, p_margin_horizontal, p_margin_vertical, p_margin_horizontal);
}
static void set_default_margins_all(Ref<StyleBox> p_sb, int p_margin) {
	set_default_margins(p_sb, p_margin, p_margin, p_margin, p_margin);
}

// sets the constants and metrics
void EditorTheme::_set_constants() {

	const int base_margin = 4 * scale;

	const int tab_default_margin_side = base_margin * 2;
	const int tab_default_margin_vertical = base_margin;

	const int border_width = 1 * scale;

	const int spacing = 4 * scale;
	const int spacing_large = 6 * scale;
	const int spacing_x_large = 8 * scale;
	const int spacing_xx_large = 12 * scale;

	const int spacing_popup = spacing_large;

	//const int margin_size_extra = base_margin + CLAMP(border_size, 0, 3);

	set_default_margins_all(style_base, spacing);
	set_default_margins_all(style_background, spacing);
	set_default_margins_all(style_container, 0);
	set_default_margins_all(style_input, spacing);
	set_default_margins_all(style_input_focused, spacing);
	set_default_margins_all(style_input_disabled, spacing);

	style_container->set_border_width_all(border_width);

	set_constant("hseparation", "Tabs", 4 * scale);

	set_default_margins_h_v(style_tab_selected, tab_default_margin_side, tab_default_margin_vertical);
	style_tab_selected->set_expand_margin_size(MARGIN_BOTTOM, border_width);
	set_default_margins_h_v(style_tab_unselected, tab_default_margin_side, tab_default_margin_vertical);
	style_tab_unselected->set_expand_margin_size(MARGIN_BOTTOM, border_width);

	int stylebox_offset = get_font("tab_fg", "TabContainer")->get_height() + style_tab_selected->get_minimum_size().height + style_container->get_default_margin(MARGIN_TOP);

	set_default_margins_h_v(style_button, spacing_large, spacing);
	set_default_margins_h_v(style_button_pressed, spacing_large, spacing);
	set_default_margins_h_v(style_button_focused, spacing_large, spacing);
	set_default_margins_h_v(style_button_hovered, spacing_large, spacing);
	set_default_margins_h_v(style_button_disabled, spacing_large, spacing);
	set_default_margins_h_v(style_button_flat, spacing_large, spacing);
	set_default_margins_h_v(style_button_flat_pressed, spacing_large, spacing);
	set_default_margins_h_v(style_button_flat_focused, spacing_large, spacing);
	set_default_margins_h_v(style_button_flat_hovered, spacing_large, spacing);
	set_default_margins_h_v(style_button_flat_disabled, spacing_large, spacing);
	set_constant("arrow_margin", "OptionButton", spacing);
	set_constant("modulate_arrow", "OptionButton", true);

	set_constant("hseparation", "CheckButton", spacing);
	set_constant("check_vadjust", "CheckButton", 0 * scale);

	set_constant("hseparation", "CheckBox", spacing);
	set_constant("check_vadjust", "CheckBox", 0 * scale);

	style_input->set_border_width_all(border_width);
	set_constant("side_margin", "TabContainer", 0);

	// Popup
	set_default_margins_all(style_popup, spacing_popup);
	style_popup->set_border_width_all(MAX(scale, border_width));
	style_popup->set_shadow_size(spacing);

	set_constant("vseparation", "PopupMenu", spacing);

	style_window->set_border_width(MARGIN_TOP, 24 * scale);
	style_window->set_expand_margin_size(MARGIN_TOP, 24 * scale);
	set_constant("close_h_ofs", "WindowDialog", 22 * scale);
	set_constant("close_v_ofs", "WindowDialog", 20 * scale);
	set_constant("title_height", "WindowDialog", 24 * scale);

	set_constant("separation", "HSplitContainer", spacing);
	set_constant("separation", "VSplitContainer", spacing);

	// Containers
	set_constant("separation", "BoxContainer", spacing);
	set_constant("separation", "HBoxContainer", spacing);
	set_constant("separation", "VBoxContainer", spacing);
	set_constant("margin_left", "MarginContainer", 0);
	set_constant("margin_top", "MarginContainer", 0);
	set_constant("margin_right", "MarginContainer", 0);
	set_constant("margin_bottom", "MarginContainer", 0);
	set_constant("hseparation", "GridContainer", spacing);
	set_constant("vseparation", "GridContainer", spacing);

	set_constant("shadow_offset_x", "RichTextLabel", 1 * scale);
	set_constant("shadow_offset_y", "RichTextLabel", 1 * scale);
	set_constant("shadow_as_outline", "RichTextLabel", 0 * scale);

	set_constant("shadow_offset_x", "Label", 1 * scale);
	set_constant("shadow_offset_y", "Label", 1 * scale);
	set_constant("shadow_as_outline", "Label", 0 * scale);
	set_constant("line_spacing", "Label", 3 * scale);

	set_constant("hseparation", "Inspector", base_margin);
	set_constant("vseparation", "Inspector", base_margin);
	set_constant("item_separation", "Inspector", base_margin);
	set_constant("category_separation", "Inspector", base_margin * 4);
	set_constant("group_ruler_size", "Inspector", 2 * scale);

	set_constant("bezier_len_pos", "GraphEdit", 80 * scale);
	set_constant("bezier_len_neg", "GraphEdit", 160 * scale);

	set_constant("port_offset", "GraphNode", 14 * scale);
	set_constant("title_h_offset", "GraphNode", -16 * scale);
	set_constant("close_h_offset", "GraphNode", 20 * scale);
	set_constant("close_offset", "GraphNode", 20 * scale);

	set_constant("margin", "ColorPicker", spacing_popup);
	set_constant("sv_width", "ColorPicker", 256 * scale);
	set_constant("sv_height", "ColorPicker", 256 * scale);
	set_constant("h_width", "ColorPicker", 30 * scale);
	set_constant("label_width", "ColorPicker", 10 * scale);

	// Tree
	set_constant("vseparation", "Tree", spacing);
	set_constant("hseparation", "Tree", spacing);
	set_constant("guide_width", "Tree", border_width);
	set_constant("item_margin", "Tree", 3 * spacing);
	set_constant("button_margin", "Tree", spacing);
	set_constant("draw_relationship_lines", "Tree", 0);
	set_constant("scroll_border", "Tree", spacing);
	set_constant("scroll_speed", "Tree", 12);

	// ItemList
	set_constant("vseparation", "ItemList", 2 * scale);
	set_constant("hseparation", "ItemList", 2 * scale);
	set_constant("icon_margin", "ItemList", spacing);
	set_constant("line_separation", "ItemList", 2 * scale);

	// tooltip
	style_tooltip->set_border_width_all(border_width);

	// extras TODO: move

	// this is the stylebox used in 3d and 2d viewports (no borders)
	Ref<StyleBoxFlat> style_content_panel_vp = style_container->duplicate();
	set_default_margins_all(style_content_panel_vp, 0);
	// style_content_panel_vp->set_default_margin(MARGIN_LEFT, border_width * 2);
	// style_content_panel_vp->set_default_margin(MARGIN_TOP, base_margin);
	// style_content_panel_vp->set_default_margin(MARGIN_RIGHT, border_width * 2);
	// style_content_panel_vp->set_default_margin(MARGIN_BOTTOM, border_width * 2);
	set_stylebox("Content", "EditorStyles", style_content_panel_vp);

	// Debugger
	Ref<StyleBoxFlat> style_panel_debugger = style_container->duplicate();
	style_panel_debugger->set_border_width(MARGIN_BOTTOM, 0);
	set_stylebox("DebuggerPanel", "EditorStyles", style_panel_debugger);

	Ref<StyleBoxFlat> style_panel_invisible_top = style_container->duplicate();
	style_panel_invisible_top->set_expand_margin_size(MARGIN_TOP, -stylebox_offset);
	set_stylebox("BottomPanelDebuggerOverride", "EditorStyles", style_panel_invisible_top);

	Ref<StyleBoxFlat> style_inspector_category = style_base->duplicate();
	style_inspector_category->set_draw_center(false);
	set_stylebox("category", "Inspector", style_inspector_category);

	Ref<StyleBoxFlat> style_inspector_section = style_base->duplicate();
	style_inspector_section->set_draw_center(false);
	style_inspector_section->set_border_width(MARGIN_LEFT, 0);
	style_inspector_section->set_border_width(MARGIN_RIGHT, 0);
	//style_inspector_section->set_border_color_all(base_color);
	set_stylebox("section", "Inspector", style_inspector_section);
}

void EditorTheme::_set_icons() {

	// Tabs
	set_icon("menu", "TabContainer", get_icon("GuiTabMenu", "EditorIcons"));
	set_icon("menu_hl", "TabContainer", get_icon("GuiTabMenu", "EditorIcons"));
	set_icon("close", "Tabs", get_icon("GuiClose", "EditorIcons"));
	set_icon("increment", "TabContainer", get_icon("GuiScrollArrowRight", "EditorIcons"));
	set_icon("decrement", "TabContainer", get_icon("GuiScrollArrowLeft", "EditorIcons"));
	set_icon("increment", "Tabs", get_icon("GuiScrollArrowRight", "EditorIcons"));
	set_icon("decrement", "Tabs", get_icon("GuiScrollArrowLeft", "EditorIcons"));
	set_icon("increment_highlight", "Tabs", get_icon("GuiScrollArrowRight", "EditorIcons"));
	set_icon("decrement_highlight", "Tabs", get_icon("GuiScrollArrowLeft", "EditorIcons"));
	set_icon("increment_highlight", "TabContainer", get_icon("GuiScrollArrowRight", "EditorIcons"));
	set_icon("decrement_highlight", "TabContainer", get_icon("GuiScrollArrowLeft", "EditorIcons"));

	// Buttons
	set_icon("arrow", "OptionButton", get_icon("GuiOptionArrow", "EditorIcons"));

	set_icon("on", "CheckButton", get_icon("GuiToggleOn", "EditorIcons"));
	set_icon("off", "CheckButton", get_icon("GuiToggleOff", "EditorIcons"));

	set_icon("checked", "CheckBox", get_icon("GuiChecked", "EditorIcons"));
	set_icon("unchecked", "CheckBox", get_icon("GuiUnchecked", "EditorIcons"));
	set_icon("radio_checked", "CheckBox", get_icon("GuiRadioChecked", "EditorIcons"));
	set_icon("radio_unchecked", "CheckBox", get_icon("GuiRadioUnchecked", "EditorIcons"));

	// Inputs
	set_icon("tab", "TextEdit", get_icon("GuiTab", "EditorIcons"));

	// windows and popups
	set_icon("checked", "PopupMenu", get_icon("GuiChecked", "EditorIcons"));
	set_icon("unchecked", "PopupMenu", get_icon("GuiUnchecked", "EditorIcons"));
	set_icon("radio_checked", "PopupMenu", get_icon("GuiRadioChecked", "EditorIcons"));
	set_icon("radio_unchecked", "PopupMenu", get_icon("GuiRadioUnchecked", "EditorIcons"));
	set_icon("submenu", "PopupMenu", get_icon("ArrowRight", "EditorIcons"));
	set_icon("visibility_hidden", "PopupMenu", get_icon("GuiVisibilityHidden", "EditorIcons"));
	set_icon("visibility_visible", "PopupMenu", get_icon("GuiVisibilityVisible", "EditorIcons"));
	set_icon("visibility_xray", "PopupMenu", get_icon("GuiVisibilityXray", "EditorIcons"));

	set_icon("close", "WindowDialog", get_icon("GuiClose", "EditorIcons"));
	set_icon("close_highlight", "WindowDialog", get_icon("GuiClose", "EditorIcons"));

	Ref<Texture> empty_icon = memnew(ImageTexture);
	set_icon("grabber", "VSplitContainer", get_icon("GuiVsplitter", "EditorIcons"));
	set_icon("grabber", "HSplitContainer", get_icon("GuiHsplitter", "EditorIcons"));

	set_icon("increment", "HScrollBar", empty_icon);
	set_icon("increment_highlight", "HScrollBar", empty_icon);
	set_icon("decrement", "HScrollBar", empty_icon);
	set_icon("decrement_highlight", "HScrollBar", empty_icon);

	set_icon("increment", "VScrollBar", empty_icon);
	set_icon("increment_highlight", "VScrollBar", empty_icon);
	set_icon("decrement", "VScrollBar", empty_icon);
	set_icon("decrement_highlight", "VScrollBar", empty_icon);

	set_icon("grabber_highlight", "HSlider", get_icon("GuiSliderGrabberHl", "EditorIcons"));
	set_icon("grabber", "HSlider", get_icon("GuiSliderGrabber", "EditorIcons"));

	set_icon("grabber", "VSlider", get_icon("GuiSliderGrabber", "EditorIcons"));
	set_icon("grabber_highlight", "VSlider", get_icon("GuiSliderGrabberHl", "EditorIcons"));

	set_icon("updown", "SpinBox", get_icon("GuiSpinboxUpdown", "EditorIcons"));

	set_icon("minus", "GraphEdit", get_icon("ZoomLess", "EditorIcons"));
	set_icon("more", "GraphEdit", get_icon("ZoomMore", "EditorIcons"));
	set_icon("reset", "GraphEdit", get_icon("ZoomReset", "EditorIcons"));
	set_icon("snap", "GraphEdit", get_icon("SnapGrid", "EditorIcons"));

	set_icon("close", "GraphNode", get_icon("GuiCloseCustomizable", "EditorIcons"));
	set_icon("resizer", "GraphNode", get_icon("GuiResizer", "EditorIcons"));
	set_icon("port", "GraphNode", get_icon("GuiGraphNodePort", "EditorIcons"));

	set_icon("folder", "FileDialog", get_icon("Folder", "EditorIcons"));

	set_icon("screen_picker", "ColorPicker", get_icon("ColorPick", "EditorIcons"));
	set_icon("add_preset", "ColorPicker", get_icon("Add", "EditorIcons"));
	set_icon("preset_bg", "ColorPicker", get_icon("GuiMiniCheckerboard", "EditorIcons"));

	set_icon("bg", "ColorPickerButton", get_icon("GuiMiniCheckerboard", "EditorIcons"));

	// Tree
	set_icon("checked", "Tree", get_icon("GuiChecked", "EditorIcons"));
	set_icon("unchecked", "Tree", get_icon("GuiUnchecked", "EditorIcons"));
	set_icon("arrow", "Tree", get_icon("GuiTreeArrowDown", "EditorIcons"));
	set_icon("arrow_collapsed", "Tree", get_icon("GuiTreeArrowRight", "EditorIcons"));
	set_icon("updown", "Tree", get_icon("GuiTreeUpdown", "EditorIcons"));
	set_icon("select_arrow", "Tree", get_icon("GuiDropdown", "EditorIcons"));
	set_icon("select_option", "Tree", get_icon("GuiTreeOption", "EditorIcons"));

	style_scroll_bg->set_texture(get_icon("GuiScrollBg", "EditorIcons"));
	style_scroll_grabber->set_texture(get_icon("GuiScrollGrabber", "EditorIcons"));
	style_scroll_grabber_hover->set_texture(get_icon("GuiScrollGrabberHl", "EditorIcons"));
	style_scroll_grabber_pressed->set_texture(get_icon("GuiScrollGrabberPressed", "EditorIcons"));

	style_progress_bg->set_texture(get_icon("GuiProgressBar", "EditorIcons"));
	style_progress_fill->set_texture(get_icon("GuiProgressFill", "EditorIcons"));

	set_font("title_font", "WindowDialog", get_font("title", "EditorFonts"));
	// EditorSpinSlider
	set_font("label", "EditorSpinSlider", get_font("monospace", "EditorFonts"));
	// Inspector
	set_font("font", "Inspector", get_font("small", "EditorFonts"));

	set_font("section_font", "Inspector", get_default_theme_font());
	set_font("category_font", "Inspector", get_font("bold", "EditorFonts"));
}

void EditorTheme::set_primary_color(Color p_primary_color) {
	primary_color = p_primary_color;

	float primary_h = primary_color.get_h();

	// calculate the base_color
	Color base_for_dark;
	Color base_for_neutral;
	Color base_for_light;
	float y = (0.299 * p_primary_color.r + 0.587 * p_primary_color.g + 0.114 * p_primary_color.b);
	if (y < 0.1) { // ultra dark (base must be lighter)
		base_color = Color().from_hsv(primary_h, 0.25, 0.123, 1);
	} else if (y < 0.4) { // dark (base must be darker)
		base_color = Color().from_hsv(primary_h, 0.156, 0.2, 1);
	} else if (y < 0.6) { // neutral (base must be lighter)
		base_color = Color().from_hsv(primary_h, 0.9, 0.8, 1);
	} else { // light (base must be darker)
		base_color = Color().from_hsv(primary_h, 0.6, 0.7, 1);
	}
	if (primary_color.get_s() < 0.000001)
		base_color.set_hsv(base_color.get_h(), 0, base_color.get_v()); // grayscale

	dark_theme = y < 0.5;

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

	contrast_color = Color().from_hsv(base_h, base_s, base_v + mono_sgn * 0.8, 1);
	contrast_color_strong = Color().from_hsv(base_h, base_s, base_v + mono_sgn * 0.9, 1);

	float base_alpha = 0.058;
	alpha_color = mono_color * Color(1, 1, 1, base_alpha);

	separation_color = mono_color_inv * Color(1, 1, 1, 0.3);
	separator_color = mono_color_inv * Color(1, 1, 1, 0.4);

	font_color = contrast_color;
	font_color_muted = alpha_color;
	font_color_dim = Color().from_hsv(font_color.get_h(), font_color.get_s(), font_color.get_v() + mono_sgn_inv * 0.4, 1);
	font_color_strong = contrast_color_strong;

	set_color("primary_color", "Editor", primary_color);
	set_color("base_color", "Editor", base_color);
	set_color("base_color_strong", "Editor", base_color_strong);
	set_color("base_color_stronger", "Editor", base_color_stronger);

	set_color("mono_color", "Editor", mono_color);
	set_color("mono_color_inv", "Editor", mono_color_inv);

	set_color("contrast_color", "Editor", contrast_color);
	set_color("contrast_color_strong", "Editor", contrast_color_strong);

	set_color("alpha_color", "Editor", alpha_color);

	set_color("font_color", "Editor", font_color);
	set_color("font_color_muted", "Editor", font_color_muted);
	set_color("font_color_dim", "Editor", font_color_dim);
	set_color("font_color_strong", "Editor", font_color_strong);

	// status colors

	_set_colors();
}

void EditorTheme::set_accent_color(Color p_accent_color) {
	accent_color = p_accent_color;

	float y = (0.299 * accent_color.r + 0.587 * accent_color.g + 0.114 * accent_color.b);
	accent_color_opt = y < 0.5 ? Color(1, 1, 1, 0.9) : Color(0, 0, 0, 0.9);
	accent_color_opt = accent_color.blend(accent_color);

	// calculate opt variant, for its optional color variation
	set_color("accent_color", "Editor", accent_color);
	set_color("accent_color_opt", "Editor", accent_color_opt);
}

void EditorTheme::set_thumb_size(int p_thumb_size) {
}
void EditorTheme::set_scale(int p_scale) {
	scale = p_scale;
	_set_constants();
}

static Ref<StyleBoxTexture> make_stylebox(float p_left, float p_top, float p_right, float p_botton, float p_margin_left = -1, float p_margin_top = -1, float p_margin_right = -1, float p_margin_botton = -1, int p_scale = 1, bool p_draw_center = true) {
	Ref<StyleBoxTexture> style(memnew(StyleBoxTexture));
	style->set_margin_size(MARGIN_LEFT, p_left * p_scale);
	style->set_margin_size(MARGIN_RIGHT, p_right * p_scale);
	style->set_margin_size(MARGIN_BOTTOM, p_botton * p_scale);
	style->set_margin_size(MARGIN_TOP, p_top * p_scale);
	style->set_default_margin(MARGIN_LEFT, p_margin_left * p_scale);
	style->set_default_margin(MARGIN_RIGHT, p_margin_right * p_scale);
	style->set_default_margin(MARGIN_BOTTOM, p_margin_botton * p_scale);
	style->set_default_margin(MARGIN_TOP, p_margin_top * p_scale);
	style->set_draw_center(p_draw_center);
	return style;
}

static Ref<StyleBoxFlat> new_stylebox_flat(bool p_filled) {
	Ref<StyleBoxFlat> sb = Ref<StyleBoxFlat>(memnew(StyleBoxFlat));
	sb->set_draw_center(p_filled);
	return sb;
}

EditorTheme::EditorTheme(Color p_primary_color, Color p_accent_color, int p_scale, int p_thumb_size) {
	scale = p_scale;
	thumb_size = p_thumb_size;

	style_base = Ref<StyleBoxFlat>(memnew(StyleBoxFlat));
	style_base->set_draw_center(false);

	style_background = new_stylebox_flat(true);

	style_panel = new_stylebox_flat(true);

	style_container = new_stylebox_flat(true);

	style_tab_selected = new_stylebox_flat(true);

	style_tab_unselected = new_stylebox_flat(false);

	style_button = new_stylebox_flat(true);
	style_button_pressed = new_stylebox_flat(true);
	style_button_focused = new_stylebox_flat(true);
	style_button_hovered = new_stylebox_flat(true);
	style_button_disabled = new_stylebox_flat(true);

	style_button_flat = new_stylebox_flat(false);
	style_button_flat_pressed = new_stylebox_flat(false);
	style_button_flat_focused = new_stylebox_flat(false);
	style_button_flat_hovered = new_stylebox_flat(false);
	style_button_flat_disabled = new_stylebox_flat(false);

	// input
	style_input = new_stylebox_flat(true);
	style_input_focused = new_stylebox_flat(true);
	style_input_disabled = new_stylebox_flat(true);

	// popup
	style_popup = new_stylebox_flat(true);

	// windows (R)
	style_window = new_stylebox_flat(true);
	// complex window, for now only Editor settings and Project settings
	style_special_window = new_stylebox_flat(true);

	style_tooltip = new_stylebox_flat(true);

	style_cursor = new_stylebox_flat(false);

	style_scroll_bg = make_stylebox(5, 5, 5, 5, 0, 0, 0, 0, scale);
	style_scroll_grabber = make_stylebox(6, 6, 6, 6, 2, 2, 2, 2, scale);
	style_scroll_grabber_hover = make_stylebox(5, 5, 5, 5, 2, 2, 2, 2, scale);
	style_scroll_grabber_pressed = make_stylebox(6, 6, 6, 6, 2, 2, 2, 2, scale);

	style_progress_bg = make_stylebox(4, 4, 4, 4, 0, 0, 0, 0, scale);
	style_progress_fill = make_stylebox(6, 6, 6, 6, 2, 1, 2, 1, scale);

	set_stylebox("panel", "PanelContainer", style_panel);

	set_stylebox("Background", "EditorStyles", style_background);
	set_stylebox("SceneTabFG", "EditorStyles", style_tab_selected);
	set_stylebox("SceneTabBG", "EditorStyles", style_tab_unselected);
	set_stylebox("DebuggerTabFG", "EditorStyles", style_tab_selected);
	set_stylebox("DebuggerTabBG", "EditorStyles", style_tab_unselected);
	// Play button group
	set_stylebox("PlayButtonPanel", "EditorStyles", style_button_flat);
	// set_stylebox("MenuHover", "EditorStyles", style_menu_hover_border);
	set_stylebox("MenuPanel", "EditorStyles", style_panel);
	// Script Editor
	set_stylebox("ScriptEditorPanel", "EditorStyles", style_panel);
	set_stylebox("ScriptEditor", "EditorStyles", style_container); // TODO: check this
	set_stylebox("Focus", "EditorStyles", style_cursor);

	set_stylebox("tab_fg", "Tabs", style_tab_selected);
	set_stylebox("tab_bg", "Tabs", style_tab_unselected);
	set_stylebox("button", "Tabs", style_button_flat);
	set_stylebox("button_pressed", "Tabs", style_button_flat_pressed);

	set_stylebox("tab_fg", "TabContainer", style_tab_selected);
	set_stylebox("tab_bg", "TabContainer", style_tab_unselected);
	set_stylebox("panel", "TabContainer", style_container);

	// set_stylebox("separator", "HSeparator", make_line_stylebox(separator_color, border_width));
	// set_stylebox("separator", "VSeparator", make_line_stylebox(separator_color, border_width, 0, true));

	set_stylebox("normal", "Button", style_button);
	set_stylebox("pressed", "Button", style_button_pressed);
	set_stylebox("focus", "Button", style_button_focused);
	set_stylebox("hover", "Button", style_button_hovered);
	set_stylebox("disabled", "Button", style_button_disabled);

	set_stylebox("normal", "OptionButton", style_button);
	set_stylebox("pressed", "OptionButton", style_button_pressed);
	set_stylebox("focus", "OptionButton", style_button_focused);
	set_stylebox("hover", "OptionButton", style_button_hovered);
	set_stylebox("disabled", "OptionButton", style_button_disabled);

	const String classes[] = { "OptionButton", "CheckButton", "CheckBox", "MenuButton", "ToolButton", "LinkButton" };
	for (int i = 0; i < 6; i++) {
		set_stylebox("normal", classes[i], style_button_flat);
		set_stylebox("hover", classes[i], style_button_flat);
		set_stylebox("pressed", classes[i], style_button_flat);
		set_stylebox("focus", classes[i], style_button_flat);
		set_stylebox("disabled", classes[i], style_button_flat);
	}

	set_stylebox("normal", "Label", style_button_flat);

	// LineEdit
	set_stylebox("normal", "LineEdit", style_input);
	set_stylebox("focus", "LineEdit", style_input_focused);
	set_stylebox("read_only", "LineEdit", style_input_disabled);

	// TextEdit
	set_stylebox("normal", "TextEdit", style_input);
	set_stylebox("focus", "TextEdit", style_input_focused);
	set_stylebox("read_only", "TextEdit", style_input_disabled);

	// PopupMenu
	set_stylebox("panel", "PopupMenu", style_popup);
	//set_stylebox("separator", "PopupMenu", style_separator);
	// PopupPanel
	set_stylebox("panel", "PopupPanel", style_popup);

	// Windows
	set_stylebox("panel", "WindowDialog", style_window);
	set_stylebox("panel", "EditorSettingsDialog", style_special_window);
	set_stylebox("panel", "ProjectSettingsEditor", style_special_window);
	set_stylebox("panel", "EditorAbout", style_special_window);

	// Tree & ItemList
	set_stylebox("bg", "Tree", style_panel);
	set_stylebox("bg", "ItemList", style_panel);

	set_stylebox("custom_button", "Tree", style_button);
	set_stylebox("custom_button_pressed", "Tree", style_button_pressed);
	set_stylebox("custom_button_hover", "Tree", style_button_hovered);
	set_stylebox("button_pressed", "Tree", style_button_pressed);
	set_stylebox("selected_focus", "Tree", style_cursor);
	set_stylebox("bg_focus", "Tree", style_cursor);
	set_stylebox("selected", "Tree", style_cursor); // TODO: check this
	set_stylebox("cursor", "Tree", style_cursor);
	set_stylebox("cursor_unfocused", "Tree", style_cursor);
	set_stylebox("title_button_normal", "Tree", style_button);
	set_stylebox("title_button_hover", "Tree", style_button_hovered);
	set_stylebox("title_button_pressed", "Tree", style_button_pressed);

	set_stylebox("cursor", "ItemList", style_cursor);
	set_stylebox("cursor_unfocused", "ItemList", style_cursor);
	set_stylebox("selected_focus", "ItemList", style_cursor);
	set_stylebox("selected", "ItemList", style_cursor);
	set_stylebox("bg_focus", "ItemList", style_cursor);

	set_stylebox("panel", "Panel", style_panel);
	set_stylebox("panel", "TooltipPanel", style_tooltip);

	// HScrollBar
	set_stylebox("scroll", "HScrollBar", style_scroll_bg);
	set_stylebox("scroll_focus", "HScrollBar", style_scroll_bg);
	set_stylebox("grabber", "HScrollBar", style_scroll_grabber);
	set_stylebox("grabber_highlight", "HScrollBar", style_scroll_grabber_hover);
	set_stylebox("grabber_pressed", "HScrollBar", style_scroll_grabber_pressed);
	// VScrollBar
	set_stylebox("scroll", "VScrollBar", style_scroll_bg);
	set_stylebox("scroll_focus", "VScrollBar", style_scroll_bg);
	set_stylebox("grabber", "VScrollBar", style_scroll_grabber);
	set_stylebox("grabber_highlight", "VScrollBar", style_scroll_grabber_hover);
	set_stylebox("grabber_pressed", "VScrollBar", style_scroll_grabber_pressed);
	// ProgressBar
	set_stylebox("bg", "ProgressBar", style_progress_bg);
	set_stylebox("fg", "ProgressBar", style_progress_fill);
	//RichTextLabel
	set_stylebox("focus", "RichTextLabel", style_cursor);
	set_stylebox("normal", "RichTextLabel", style_panel);
	// GraphEdit
	set_stylebox("bg", "GraphEdit", style_panel);

	set_accent_color(p_accent_color);
	set_primary_color(p_primary_color);

	_set_constants();
}