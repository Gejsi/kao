#include "ui.h"
// #include <adwaita.h>

void activate(GtkApplication *app) {
  GtkWidget *window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "kao");
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 500);
  gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
  gtk_window_set_modal(GTK_WINDOW(window), TRUE);

  GtkWidget *ui_wrapper = build_ui_wrapper();
  gtk_window_set_child(GTK_WINDOW(window), ui_wrapper);

  gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
  const char *app_id = "com.picker.kao";
  // g_autoptr(AdwApplication) app = NULL;
  // app = adw_application_new(app_id,
  // G_APPLICATION_DEFAULT_FLAGS); g_signal_connect(app, "activate",
  // G_CALLBACK(activate), NULL); return
  // g_application_run(G_APPLICATION(app), argc, argv);

  GtkApplication *app =
      gtk_application_new(app_id, G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  int status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
