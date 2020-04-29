#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_DomXML.h"

class DomXML : public QMainWindow
{
	Q_OBJECT

public:
	DomXML(QWidget *parent = Q_NULLPTR);

private:
	Ui::DomXMLClass ui;
};
