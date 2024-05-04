#include "gui/bible-desktop.h"
#include <gtkmm/application.h>

extern "C" {
int gui_main(int argc, char* argv[])
{
  auto app = Gtk::Application::create("org.filipemd.bible-desktop");

  return app->make_window_and_run<BibleApp>(argc, argv);
}
};