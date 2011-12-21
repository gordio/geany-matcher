#include <geanyplugin.h>

gboolean on_editor_notify();

GeanyPlugin     *geany_plugin;
GeanyData       *geany_data;
GeanyFunctions  *geany_functions;

PLUGIN_VERSION_CHECK(211)

PLUGIN_SET_INFO("Matcher", "Working with braces",
				"1.0", "Gordio aka Oleg Gordienko <gordio[at]ya.ru>");

PluginCallback plugin_callbacks[] =
{
	{ "editor-notify", (GCallback) &on_editor_notify, FALSE, NULL },
	{ NULL, NULL, FALSE, NULL }
};

static void
work_with_match(ScintillaObject *sci, int pressed, char *ch_open, char *ch_close)
{
	// save current position
	int cur_position = sci_get_current_position(sci);
	int open = (int)*ch_open;
	int close = (int)*ch_close;

	// pressed close
	if (pressed == close) {
		// check if next character is close
		if (sci_get_char_at(sci, cur_position) == close) {
			// set remove regions with backward char
			sci_set_selection_start(sci, cur_position-1);
			sci_set_selection_end(sci, cur_position);
			// and remove last char (realy is replace to empty)
			sci_replace_sel(sci, "");
			// jump cursor to next char
			sci_set_current_position(sci, cur_position, FALSE);
		} else if (pressed == open) {
			// or insert close
			sci_insert_text(sci, cur_position, ch_close);
			// and jump to center
			sci_set_current_position(sci, cur_position, FALSE);
		}
	// pressed open and NOT close (no equal ;Ъ)
	} else if (pressed == open) {
			// or insert close
			sci_insert_text(sci, cur_position, ch_close);
			// and jump to center
			sci_set_current_position(sci, cur_position, FALSE);
	}

	return;
}

gboolean
on_editor_notify(GObject *o, GeanyEditor *e, SCNotification *nt, gpointer d)
{
	work_with_match(e->sci, nt->ch, "\"", "\"");
	work_with_match(e->sci, nt->ch, "'", "'");
	work_with_match(e->sci, nt->ch, "(", ")");
	work_with_match(e->sci, nt->ch, "[", "]");
	work_with_match(e->sci, nt->ch, "{", "}");
	work_with_match(e->sci, nt->ch, "<", ">");

	return FALSE;
}


void
plugin_init(GeanyData *data)
{
	return;
}

void
plugin_cleanup(void)
{
	return;
}

