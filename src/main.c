#include "activate.h"
#include <adwaita.h>

int main(int argc, char **argv) {
  g_autoptr(AdwApplication) app = NULL;

  app = adw_application_new("org.example.Hello", G_APPLICATION_DEFAULT_FLAGS);

  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

  return g_application_run(G_APPLICATION(app), argc, argv);
}
