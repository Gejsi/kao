#include "ui.h"
#include "gtk/gtk.h"
#include <glib.h>

const int ROOT_SIZE = 16;

GtkWidget *build_ui_wrapper(void) {
  GtkWidget *notebook = gtk_notebook_new();

  GtkWidget *happy_tab = build_scrollable_tab(Happy);
  GtkWidget *sad_tab = build_scrollable_tab(Sad);
  GtkWidget *angry_tab = build_scrollable_tab(Angry);

  gtk_notebook_append_page(GTK_NOTEBOOK(notebook), happy_tab,
                           gtk_label_new("Happy"));
  gtk_notebook_append_page(GTK_NOTEBOOK(notebook), sad_tab,
                           gtk_label_new("Sad"));
  gtk_notebook_append_page(GTK_NOTEBOOK(notebook), angry_tab,
                           gtk_label_new("Angry"));

  return notebook;
}

GtkWidget *build_scrollable_tab(Expr expr) {
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_widget_set_margin_top(box, ROOT_SIZE);
  gtk_widget_set_margin_bottom(box, ROOT_SIZE);
  gtk_widget_set_margin_start(box, ROOT_SIZE);
  gtk_widget_set_margin_end(box, ROOT_SIZE);

  GtkWidget *grid = build_grid(expr);
  gtk_box_append(GTK_BOX(box), grid);

  GtkWidget *scrolled_window = gtk_scrolled_window_new();
  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), box);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                 GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  return scrolled_window;
}

void handle_copy(GtkWidget *button, gpointer data) {
  const char *emoji = gtk_button_get_label(GTK_BUTTON(button));
  GdkDisplay *display = gdk_display_get_default();
  GdkClipboard *clipboard = gdk_display_get_clipboard(display);
  GType clipboard_type = gdk_clipboard_get_type();

  gdk_clipboard_set_text(clipboard, emoji);

  // TODO: maybe add a toast notification?
  g_print("Copied to clipboard: %s\n", emoji);
}

GtkWidget *build_grid(Expr expr) {
  GtkWidget *grid = gtk_grid_new();
  gtk_grid_set_row_spacing(GTK_GRID(grid), ROOT_SIZE * 0.5);
  gtk_grid_set_column_spacing(GTK_GRID(grid), ROOT_SIZE * 0.5);

  const int GRID_LENGTH = 3;
  const gchar *button_labels[GRID_LENGTH][GRID_LENGTH];

  if (expr == Happy) {
    button_labels[0][0] = ":)";
    button_labels[0][1] = ":D";
    button_labels[0][2] = "😊";
    button_labels[1][0] = "😄";
    button_labels[1][1] = "😁";
    button_labels[1][2] = "😃";
    button_labels[2][0] = "😆";
    button_labels[2][1] = "😂";
    button_labels[2][2] = "😹";
  } else if (expr == Sad) {
    button_labels[0][0] = ":(";
    button_labels[0][1] = ":'(";
    button_labels[0][2] = "😢";
    button_labels[1][0] = "😭";
    button_labels[1][1] = "😞";
    button_labels[1][2] = "😔";
    button_labels[2][0] = "😟";
    button_labels[2][1] = "😕";
    button_labels[2][2] = "😣";
  } else if (expr == Angry) {
    button_labels[0][0] = ">:(";
    button_labels[0][1] = "😠";
    button_labels[0][2] = "😡";
    button_labels[1][0] = "😤";
    button_labels[1][1] = "😾";
    button_labels[1][2] = "😒";
    button_labels[2][0] = "👿";
    button_labels[2][1] = "💢";
    button_labels[2][2] = "😑";
  }

  for (int i = 0; i < GRID_LENGTH; i++) {
    for (int j = 0; j < GRID_LENGTH; j++) {
      GtkWidget *button = gtk_button_new_with_label(button_labels[i][j]);
      gtk_widget_set_hexpand(button, TRUE);
      g_signal_connect(button, "clicked", G_CALLBACK(handle_copy), NULL);
      gtk_grid_attach(GTK_GRID(grid), button, j, i, 1, 1);
    }
  }

  return grid;
}
