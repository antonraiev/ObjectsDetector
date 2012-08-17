#include "mainWindow.h"
#include <QtGui/QApplication>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	mainWindow w;
	w.resize(700,500);
	w.show();
	return a.exec();
}
