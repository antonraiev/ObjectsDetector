#ifndef SNAPSHOT_H
#define SNAPSHOT_H
#include <qimage.h>
#include <qdatetime.h>
struct Snapshot
{
	int id;
	QImage image;
	int width;
	int height;
	QDateTime created;
	bool in_scene;
};
struct Scene
{
	int id;
	QPixmap pixmap;
	QDateTime created;
	bool have_map;
};
struct Description
{
	int id;
	QString name;
	QString description;
};
struct Object
{
	int id;
	QImage object;
	int phys_height;
	Description descr;
};
#endif // SNAPSHOT_H