// hack for QModelIndexList in Qt Libraries 4.8. 
//Fix "Asserion failed" error, when QModelIndexList declaration goes out of scope
#include <QtGui>
QModelIndexList selectedIndexes(QTableWidget *table)
{
	QModelIndexList list;
	for (int row = 0; row < table->model()->rowCount(table->rootIndex()); ++row)
	{
		QModelIndex index = table->model()->index(row, 1, table->rootIndex());
		if (table->selectionModel()->isSelected(index))
			list.push_back(index);
	}
	return list;
}