#pragma once

#include <QtWidgets/QMainWindow>
#include<QDomElement>
#include<QTreeWidget>
#include<QTreeWidgetItem>
#include "ui_DomXML.h"

class DomXML : public QMainWindow
{
	Q_OBJECT

public:
	DomXML(QWidget *parent = Q_NULLPTR);
	~DomXML();

	void readFile();

private:
	void parseRootNode(const QDomElement& rootNode);//分析根节点
	void parseEntryNode(const QDomElement& entryNode,QTreeWidgetItem*parent);
	void parsePageNode(const QDomElement& pageNode, QTreeWidgetItem*parent);

	Ui::DomXMLClass ui;
	QTreeWidget *treeWidget;
};
