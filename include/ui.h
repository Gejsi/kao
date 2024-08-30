#ifndef UI_H
#define UI_H

#include "adwaita.h"

typedef struct {
  AdwToastOverlay *toast_overlay;
  AdwToast *current_toast;
} Context;

typedef enum { All, Happy, Sad, Angry, Misc } Expr;

GtkWidget *build_ui_wrapper(Context *ctx);
GtkWidget *build_scrollable_tab(Context *ctx, Expr expr);
GtkWidget *build_grid(Context *ctx, Expr expr);

#endif // UI_H
