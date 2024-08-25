#ifndef UI_H
#define UI_H

#include "adwaita.h"

typedef enum { All, Happy, Sad, Angry, Misc } Expr;

GtkWidget *build_ui_wrapper(AdwToastOverlay *overlay);
GtkWidget *build_scrollable_tab(Expr expr, AdwToastOverlay *overlay);
GtkWidget *build_grid(Expr expr, AdwToastOverlay *overlay);

#endif // UI_H
