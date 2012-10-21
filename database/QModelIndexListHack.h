// hack for QModelIndexList in Qt Libraries 4.8. 
//Fix "Asserion failed" error, when QModelIndexList declaration goes out of scope
#ifndef QMILHACK_H
#define QMILHACK_H
#include <QtGui>
QModelIndexList selectedIndexes(QTableWidget *table);
#endif