#include "ui.h"
#include "gdk/gdk.h"
#include "glib.h"
#include <stdio.h>

void get_width(GtkWidget *widget, gpointer user_data) {
  printf("width %d\n", gtk_widget_get_width(widget));
}

GtkWidget *build_ui_wrapper(Context *ctx) {
  GtkWidget *notebook = gtk_notebook_new();

  GtkWidget *happy_tab = build_scrollable_tab(ctx, Happy);
  // GtkWidget *sad_tab = build_scrollable_tab(ctx, Sad);
  // GtkWidget *angry_tab = build_scrollable_tab(ctx, Angry);

  gtk_notebook_append_page(GTK_NOTEBOOK(notebook), happy_tab,
                           gtk_label_new("Happy"));
  // gtk_notebook_append_page(GTK_NOTEBOOK(notebook), sad_tab,
  //                          gtk_label_new("Sad"));
  // gtk_notebook_append_page(GTK_NOTEBOOK(notebook), angry_tab,
  //                          gtk_label_new("Angry"));

  return notebook;
}

GtkWidget *build_scrollable_tab(Context *ctx, Expr expr) {
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_widget_set_margin_top(box, ROOT_SIZE * 0);
  gtk_widget_set_margin_bottom(box, ROOT_SIZE * 0);
  gtk_widget_set_margin_start(box, ROOT_SIZE * 0);
  gtk_widget_set_margin_end(box, ROOT_SIZE * 0);

  GtkWidget *grid = build_grid(ctx, expr);
  gtk_box_append(GTK_BOX(box), grid);

  GtkWidget *scrolled_window = gtk_scrolled_window_new();
  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), box);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                 GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  return scrolled_window;
}

void on_toast_dismiss(AdwToast *toast, gpointer data) {
  Context *ctx = data;
  ctx->current_toast = NULL;
}

void on_copy(GtkWidget *button, gpointer data) {
  printf("Width: %d\n", gtk_widget_get_width(button));
  Context *ctx = data;

  GdkClipboard *clipboard =
      gdk_display_get_clipboard(gdk_display_get_default());
  const char *emoji = gtk_button_get_label(GTK_BUTTON(button));
  size_t emoji_len = strlen(emoji);

  gdk_clipboard_set_text(clipboard, emoji);

  const char *toast_prefix = "Copied ";
  size_t toast_prefix_len = strlen(toast_prefix);

  // concatenate toast message
  char toast_msg[toast_prefix_len + emoji_len + 1];
  memcpy(toast_msg, toast_prefix, toast_prefix_len);
  memcpy(toast_msg + toast_prefix_len, emoji, emoji_len);
  toast_msg[toast_prefix_len + emoji_len] = '\0';
  GtkWidget *label = gtk_label_new(toast_msg);

  if (ctx->current_toast == NULL) {
    ctx->current_toast = adw_toast_new("");
    adw_toast_set_custom_title(ctx->current_toast, label);

    adw_toast_overlay_add_toast(ctx->toast_overlay, ctx->current_toast);
    g_signal_connect(ctx->current_toast, "dismissed",
                     G_CALLBACK(on_toast_dismiss), ctx);
  } else {
    adw_toast_set_custom_title(ctx->current_toast, label);
  }
}

static const char *happy_emojis[] = {
    "( ͡° ͜ʖ ͡°)",    "ಠ_ಠ",     "(͡° ͜ʖ ͡°)",     "(ಠ‿ಠ)", "(▀̿Ĺ̯▀̿ ̿)",
    "ʕ•ᴥ•ʔ",       "(◕‿◕✿)",  "¯\\_(ツ)_/¯", "(¬‿¬)", "(>_<)",
    "ヽ(￣д￣)ノ", "(•_•)",   "ಠ_ಠ",         "(ಠ‿ಠ)", "(╯°□°）╯︵ ┻━┻",
    "(◕︵◕)",      "(͡° ͜ʖ ͡°)", "༼つ◕_◕༽つ"};

gboolean check_button_width(gpointer data) {
  GtkWidget *button = GTK_WIDGET(data);
  int width = gtk_widget_get_width(button);

  if (width > 0) {
    printf("Button width: %d\n", width);
    return G_SOURCE_REMOVE; // Stop the idle handler
  }

  return G_SOURCE_CONTINUE; // Keep checking until width is allocated
}

GtkWidget *build_grid(Context *ctx, Expr expr) {
  GtkWidget *wrapper = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  size_t happy_emojis_len = G_N_ELEMENTS(happy_emojis);
  // int breakpoints[256] = {};

  GtkWidget *flexbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

  for (int i = 0, width = 0; i < happy_emojis_len; i++) {
    GtkWidget *button = gtk_button_new_with_label(happy_emojis[i]);
    g_signal_connect(button, "clicked", G_CALLBACK(on_copy), ctx);
    // printf("Visible %b, index %d\n", gtk_widget_get_visible(button), i);
    width += gtk_widget_get_width(button);
    // printf("index %d, width %d\n", i, width);
    // idle function to check the allocated width after the layout process
    g_idle_add(check_button_width, button);

    if (width > 400) {
      printf("Broke at index %d\n", i);
      width = 0;
    }

    gtk_box_append(GTK_BOX(flexbox), button);
  }

  // int breakpoints[] = {5, 9, 11};
  // int j = 0;
  // for (int i = 0; i < G_N_ELEMENTS(breakpoints); i++) {
  //   GtkWidget *flexbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  //   for (; j < breakpoints[i]; j++) {
  //     GtkWidget *button = gtk_button_new_with_label(happy_emojis[j]);
  //     g_signal_connect(button, "clicked", G_CALLBACK(on_copy), ctx);
  //     gtk_box_append(GTK_BOX(flexbox), button);
  //   }

  //   gtk_box_append(GTK_BOX(wrapper), flexbox);
  // }

  // return wrapper;
  return flexbox;
}
