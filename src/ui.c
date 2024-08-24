#include "ui.h"
#include "gtk/gtk.h"
#include <glib.h>

const int PADDING = 16;

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
  gtk_widget_set_margin_top(box, PADDING);
  gtk_widget_set_margin_bottom(box, PADDING);
  gtk_widget_set_margin_start(box, PADDING);
  gtk_widget_set_margin_end(box, PADDING);

  const gchar *content;
  switch (expr) {
  case All:
    content = "This is the entire content!";
    break;
  case Happy:
    content = "This is the happy content!";
    break;
  case Sad:
    content = "This is the sad content.";
    break;
  case Angry:
    content = "This is the angry content!";
    break;
  case Misc:
    content = "This is the misc content!";
    break;
  }

  GtkWidget *label = gtk_label_new(content);
  gtk_label_set_wrap(GTK_LABEL(label), TRUE);
  gtk_label_set_xalign(GTK_LABEL(label), 0.0);

  gtk_box_append(GTK_BOX(box), label);

  GtkWidget *scrolled_window = gtk_scrolled_window_new();
  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), box);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                 GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  return scrolled_window;
}
