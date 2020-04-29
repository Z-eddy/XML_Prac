#include "DomXML.h"
#include<iostream>
#include<QTreeWidgetItem>
#include<QFileDialog>
#include<QFile>
#include<QDomDocument>
using std::cout;
using std::endl;
using std::ends;

DomXML::DomXML(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	/*
	treeWidget = new QTreeWidget(this);
	treeWidget->setHeaderLabels({ "items","pages" });
	this->setCentralWidget(treeWidget);
	*/
	treeWidget = ui.treeWidget;
	readFile();
	cout << treeWidget->topLevelItemCount() << endl;
}

DomXML::~DomXML()
{

}

void DomXML::readFile()
{
	const QString filePath{ QFileDialog::getOpenFileName(this,"open file",QDir::currentPath(),"XML(*.xml)") };
	if (filePath.isEmpty())return;

	QFile file{ filePath };
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		cout << "file open error:" << file.errorString().toStdString() << endl;
		return;
	}

	QDomDocument xmlDom;
	if (!xmlDom.setContent(&file)) {//dom读取整个文档
		file.close();
		cout << "xmlDom setContent error" << endl;
		return;
	}
	file.close();

	QDomElement rootEle{ xmlDom.documentElement() };//获得根节点
	if (rootEle.tagName() != "bookindex") {//检查根节点的字符串是否正确
		cout << "open file error:can't find root node" << endl;
		return;
	}

	parseRootNode(rootEle);
}

void DomXML::parseRootNode(const QDomElement& rootNode)
{
	QDomNode theNode{ rootNode.firstChild() };
	while (!theNode.isNull()) {
		if (theNode.toElement().tagName() == "entry") {
			parseEntryNode(theNode.toElement(), treeWidget->invisibleRootItem());
		}
		theNode = theNode.nextSibling();
	}
}

void DomXML::parseEntryNode(const QDomElement& entryNode, QTreeWidgetItem*parent)
{
	QTreeWidgetItem *item{ new QTreeWidgetItem(parent) };//新建Tree子节点
	item->setText(0, entryNode.attribute("term"));

	QDomNode childNode{ entryNode.firstChild() };
	while (!childNode.isNull()) {
		if (childNode.toElement().tagName() == "entry") {
			parseEntryNode(childNode.toElement(), item);
		}
		else if (childNode.toElement().tagName() == "page") {
			parsePageNode(childNode.toElement(), item);
		}
		childNode = childNode.nextSibling();
	}
}

void DomXML::parsePageNode(const QDomElement& pageNode, QTreeWidgetItem*parent)
{
	QString data{ parent->text(1) };
	if(!data.isEmpty()){
		data += ", ";
	}
	data += pageNode.text();
	parent->setText(1, data);
}
