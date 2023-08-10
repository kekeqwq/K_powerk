#include <stdlib.h>
#include <gtk/gtk.h>

static void exec_foot(void)
{
  system("foot & pkill k_powerk");
}

static void keyboard_show(void)
{
  system("pkill k_powerk & sleep 1 ; busctl call --user sm.puri.OSK0 /sm/puri/OSK0 sm.puri.OSK0 SetVisible b true");
}


static void
activate (GtkApplication *app,
          gpointer        user_data)
{
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;

  /* create a new window, and set its title */
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "K Powerkey Tools");

  /* Here we construct the container that is going pack our buttons */
  grid = gtk_grid_new ();

  /* Pack the container in the window */
  gtk_window_set_child (GTK_WINDOW (window), grid);

  button = gtk_button_new_with_label ("Foot");
  g_signal_connect (button, "clicked", G_CALLBACK (exec_foot), NULL);

  /* Place the first button in the grid cell (0, 0), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */
  gtk_grid_attach (GTK_GRID (grid), button, 0, 0, 1, 1);

  button = gtk_button_new_with_label ("Keyboard");
  g_signal_connect (button, "clicked", G_CALLBACK (keyboard_show), NULL);

  /* Place the second button in the grid cell (1, 0), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */
  gtk_grid_attach (GTK_GRID (grid), button, 1, 0, 1, 1);

  button = gtk_button_new_with_label ("Quit");
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_window_destroy), window);

  /* Place the Quit button in the grid cell (0, 1), and make it
   * span 2 columns.
   */
  gtk_grid_attach (GTK_GRID (grid), button, 0, 1, 2, 1);

  gtk_widget_show (window);

}

int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.kpowerk", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
