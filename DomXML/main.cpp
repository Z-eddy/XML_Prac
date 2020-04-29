#include "DomXML.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	DomXML w;
	w.show();
	return a.exec();
}
