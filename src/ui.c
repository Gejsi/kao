#include "ui.h"
#include "hs.h"

const uint32_t ROOT_SIZE = 16;

GtkWidget *build_ui_wrapper(Context *ctx) {
  GtkWidget *notebook = gtk_notebook_new();

  GtkWidget *happy_tab = build_scrollable_tab(ctx, Happy);
  GtkWidget *sad_tab = build_scrollable_tab(ctx, Sad);
  GtkWidget *angry_tab = build_scrollable_tab(ctx, Angry);

  gtk_notebook_append_page(GTK_NOTEBOOK(notebook), happy_tab,
                           gtk_label_new("Happy"));
  gtk_notebook_append_page(GTK_NOTEBOOK(notebook), sad_tab,
                           gtk_label_new("Sad"));
  gtk_notebook_append_page(GTK_NOTEBOOK(notebook), angry_tab,
                           gtk_label_new("Angry"));

  return notebook;
}

GtkWidget *build_scrollable_tab(Context *ctx, Expr expr) {
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_widget_set_margin_top(box, ROOT_SIZE);
  gtk_widget_set_margin_bottom(box, ROOT_SIZE);
  gtk_widget_set_margin_start(box, ROOT_SIZE);
  gtk_widget_set_margin_end(box, ROOT_SIZE);

  GtkWidget *grid = build_grid(ctx, expr);
  gtk_box_append(GTK_BOX(box), grid);

  GtkWidget *scrolled_window = gtk_scrolled_window_new();
  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), box);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                 GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  return scrolled_window;
}

void handle_toast_dismiss(AdwToast *toast, gpointer data) {
  Context *ctx = data;
  ctx->current_toast = NULL;
}

void handle_copy(GtkWidget *button, gpointer data) {
  Context *ctx = data;

  GdkClipboard *clipboard =
      gdk_display_get_clipboard(gdk_display_get_default());
  const char *emoji_str = gtk_button_get_label(GTK_BUTTON(button));

  gdk_clipboard_set_text(clipboard, emoji_str);

  String toast_msg;
  String_init(&toast_msg);
  String_push(&toast_msg, "Copied ");
  String_push(&toast_msg, emoji_str);

  if (ctx->current_toast == NULL) {
    ctx->current_toast = adw_toast_new(toast_msg.value);
    adw_toast_overlay_add_toast(ctx->toast_overlay, ctx->current_toast);
    g_signal_connect(ctx->current_toast, "dismissed",
                     G_CALLBACK(handle_toast_dismiss), ctx);
  } else {
    adw_toast_set_title(ctx->current_toast, toast_msg.value);
  }

  String_free(&toast_msg);
}

GtkWidget *build_grid(Context *ctx, Expr expr) {
  GtkWidget *grid = gtk_grid_new();
  gtk_grid_set_row_spacing(GTK_GRID(grid), ROOT_SIZE * 0.5);
  gtk_grid_set_column_spacing(GTK_GRID(grid), ROOT_SIZE * 0.5);

  const uint32_t GRID_LENGTH = 3;
  const gchar *button_labels[GRID_LENGTH][GRID_LENGTH];

  if (expr == Happy) {
    button_labels[0][0] = ":)";
    button_labels[0][1] = ":D";
    button_labels[0][2] = "( ﾟдﾟ)";
    button_labels[1][0] = "😄";
    button_labels[1][1] = "( ﾟヮﾟ)";
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

  for (uint32_t i = 0; i < GRID_LENGTH * 4; i++) {
    for (uint32_t j = 0; j < GRID_LENGTH; j++) {
      GtkWidget *button =
          gtk_button_new_with_label(button_labels[i % GRID_LENGTH][j]);
      gtk_widget_set_size_request(
          button, (400 - (ROOT_SIZE * 2) - (ROOT_SIZE * 0.5 * GRID_LENGTH)) / 3,
          50);
      gtk_widget_set_hexpand(button, TRUE);
      g_signal_connect(button, "clicked", G_CALLBACK(handle_copy), ctx);
      gtk_grid_attach(GTK_GRID(grid), button, j, i, 1, 1);
    }
  }

  return grid;
}
