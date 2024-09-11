#include "ui.h"

void activate(GtkApplication *app) {
  GtkWidget *window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "kao");
  gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
  gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
  gtk_window_set_modal(GTK_WINDOW(window), TRUE);
  AdwStyleManager *theme = adw_style_manager_get_default();
  adw_style_manager_set_color_scheme(theme, ADW_COLOR_SCHEME_PREFER_DARK);

  AdwToastOverlay *overlay = ADW_TOAST_OVERLAY(adw_toast_overlay_new());
  Context *ctx = g_new0(Context, 1);
  ctx->toast_overlay = overlay;

  GtkWidget *ui_wrapper = build_ui_wrapper(ctx);
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
