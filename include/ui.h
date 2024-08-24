#ifndef UI_H
#define UI_H

#include <gtk/gtk.h>

typedef enum { All, Happy, Sad, Angry, Misc } Expr;

GtkWidget *build_ui_wrapper(void);
GtkWidget *build_scrollable_tab(Expr expr);
GtkWidget *build_grid(Expr expr);

#endif // UI_H
