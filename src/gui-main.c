#include <gtk/gtk.h>

static void activate (GtkApplication* app, gpointer user_data) {
  GtkWidget *window;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Bible");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
  gtk_window_present (GTK_WINDOW (window));
}

int gui_main (int argc, char *argv[]) {
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.filipemd.bible", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
