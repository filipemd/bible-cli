#include <gtkmm-4.0/gtkmm.h>

extern "C" {
class BibleApp : public Gtk::Window
{
public:
  BibleApp();
};

BibleApp::BibleApp()
{
  set_title("Bible App");
  set_default_size(200, 200);
}

int gui_main(int argc, char* argv[])
{
  auto app = Gtk::Application::create("org.gtkmm.examples.base");

  return app->make_window_and_run<BibleApp>(argc, argv);
}
};