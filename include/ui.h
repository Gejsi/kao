#ifndef UI_H
#define UI_H

#include <gtk/gtk.h>

GtkWidget *build_ui_wrapper(void);
GtkWidget *build_tab(const gchar *category);
GtkWidget *build_section(const gchar *category, const gchar *section_name);

#endif // UI_H
