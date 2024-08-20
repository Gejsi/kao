#include "ui.h"
#include <glib.h>

GtkWidget *build_ui_wrapper(void) {
  GtkWidget *notebook = gtk_notebook_new();

  GtkWidget *happy_tab = build_tab("Happy");
  GtkWidget *sad_tab = build_tab("Sad");
  GtkWidget *angry_tab = build_tab("Angry");

  gtk_notebook_append_page(GTK_NOTEBOOK(notebook), happy_tab,
                           gtk_label_new("Happy"));
  gtk_notebook_append_page(GTK_NOTEBOOK(notebook), sad_tab,
                           gtk_label_new("Sad"));
  gtk_notebook_append_page(GTK_NOTEBOOK(notebook), angry_tab,
                           gtk_label_new("Angry"));

  return notebook;
}

GtkWidget *build_tab(const gchar *category) {
  // Create a box for vertical stacking of sections
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);

  // Add a section to the box
  GtkWidget *section1 = build_section(category, "Sample Section 1");
  GtkWidget *section2 = build_section(category, "Sample Section 2");

  // Append the sections to the box
  gtk_box_append(GTK_BOX(box), section1);
  gtk_box_append(GTK_BOX(box), section2);

  // Make the box scrollable
  GtkWidget *scrolled_window = gtk_scrolled_window_new();
  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), box);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                 GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  return scrolled_window;
}

GtkWidget *build_section(const gchar *category, const gchar *section_name) {
  GtkWidget *frame = gtk_frame_new(section_name);

  GtkWidget *grid = gtk_grid_new();
  gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
  gtk_grid_set_column_spacing(GTK_GRID(grid), 5);

  GtkWidget *item1 = gtk_button_new_with_label("( ͡° ͜ʖ ͡°)");
  GtkWidget *item2 = gtk_button_new_with_label("¯\\_(ツ)_/¯");
  GtkWidget *item3 = gtk_button_new_with_label(":)");
  GtkWidget *item4 = gtk_button_new_with_label(":D");

  gtk_grid_attach(GTK_GRID(grid), item1, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), item2, 1, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), item3, 0, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), item4, 1, 1, 1, 1);

  gtk_frame_set_child(GTK_FRAME(frame), grid);

  return frame;
}
