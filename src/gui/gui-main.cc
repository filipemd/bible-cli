#include <QApplication>

#include "window.h"

int gui_main(int argc, char **argv) {
	QApplication app (argc, argv);

	Window window;
	window.show();

	return app.exec();
}