#include "ScenesDialog.h"

ScenesDialog::ScenesDialog(QWidget *parent)
	: QDialog(parent)
{
	setWindowTitle("���������� ����� �� ���� ������");
	resize(580,510);
	QPushButton *add=new QPushButton("��������");
	connect(add,SIGNAL(clicked()),SLOT(accept()));
	QPushButton *cancel=new QPushButton("������");
	connect(cancel,SIGNAL(clicked()),SLOT(reject()));
	QGridLayout *layout=new QGridLayout();
	layout->addWidget(add,5,3,1,1);
	layout->addWidget(cancel,5,4,1,1);
	setLayout(layout);
}
void ScenesDialog::setDbModel(DatabaseModel &dbModel)
{
	this->dbModel=&dbModel;
}
int ScenesDialog::exec()
{
	setCursor(Qt::WaitCursor);
	table=dbModel->scenesTable();
	setCursor(Qt::ArrowCursor);
	connect(table,SIGNAL(itemSelectionChanged()),SLOT(selectionChanged()));
	((QGridLayout*)layout())->addWidget(table,0,0,5,5);
	return QDialog::exec();
}
void ScenesDialog::selectionChanged()
{
	selectedId=table->item(table->selectionModel()->selectedRows().at(0).row(),5)->data(Qt::DisplayRole).toInt();
}
int ScenesDialog::selectedSceneId()
{
	return selectedId;
}
ScenesDialog::~ScenesDialog()
{

}
