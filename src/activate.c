#include "activate.h"

static void print_hello(GtkWidget *widget, gpointer data) {
  g_print("Hello World\n");
}

void activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Hello");
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 500);
  gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
  gtk_window_set_modal(GTK_WINDOW(window), TRUE);

  GtkWidget *button;
  button = gtk_button_new_with_label("Hello World!!!");
  g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);
  gtk_window_set_child(GTK_WINDOW(window), button);

  gtk_window_present(GTK_WINDOW(window));
}
