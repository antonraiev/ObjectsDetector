#include "SnapshotsDialog.h"
#include "../database/QModelIndexListHack.h"
SnapshotsDialog::SnapshotsDialog(QWidget *parent)
	: QDialog(parent)
{
	setWindowTitle("Добавление снимка из базы данных");
	resize(580,450);
	QPushButton *add=new QPushButton("Добавить");
	connect(add,SIGNAL(clicked()),SLOT(accept()));
	QPushButton *cancel=new QPushButton("Отмена");
	connect(cancel,SIGNAL(clicked()),SLOT(reject()));
	QGridLayout *layout=new QGridLayout();
	layout->addWidget(add,5,3,1,1);
	layout->addWidget(cancel,5,4,1,1);
	setLayout(layout);
}

int SnapshotsDialog::exec()
{
	setCursor(Qt::WaitCursor);
	table = DatabaseView::getInstance().getTable(SNAPSHOTS);
	setCursor(Qt::ArrowCursor);
	connect(table, SIGNAL(itemSelectionChanged()), SLOT(selectionChanged()));
	((QGridLayout*)layout())->addWidget(table, 0, 0, 5, 5);
	table->show();
	return QDialog::exec();
}
void SnapshotsDialog::selectionChanged()
{
	selectedId.clear();
	QModelIndexList list = selectedIndexes(table);
	for(int i=0; i<list.count(); i++)
	{
		selectedId.push_back(table->item(list.at(i).row(),5)->data(Qt::DisplayRole).toInt());
	}
}
QList<int> SnapshotsDialog::selectedIdentifiers()
{
	return selectedId;
}
SnapshotsDialog::~SnapshotsDialog()
{

}
