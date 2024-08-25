#include "ui.h"

void activate(GtkApplication *app) {
  GtkWidget *window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "kao");
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 500);
  gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
  gtk_window_set_modal(GTK_WINDOW(window), TRUE);

  AdwToastOverlay *overlay = ADW_TOAST_OVERLAY(adw_toast_overlay_new());
  GtkWidget *ui_wrapper = build_ui_wrapper(overlay);
  adw_toast_overlay_set_child(overlay, ui_wrapper);
  gtk_window_set_child(GTK_WINDOW(window), GTK_WIDGET(overlay));

  gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
  g_autoptr(AdwApplication) app =
      adw_application_new("com.picker.kao", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

  return g_application_run(G_APPLICATION(app), argc, argv);
}
