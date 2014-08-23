#include <QGuiApplication>
#include <QStringList>
#include <QDebug>
#include <QFile>
#include <QDataStream>

#include <tiled/tile.h>
#include <tiled/tilelayer.h>
#include <tiled/tileset.h>
#include <tiled/mapreader.h>
#include <tiled/map.h>
#include <tiled/mapobject.h>
#include <tiled/objectgroup.h>

#include "Level.h"

int main(int argc, char **argv)
{
	QGuiApplication application(argc, argv);
	QStringList arguments = application.arguments();
	QStringList objectTypes =
	{
		"spawn",
		"goal"
	};

	if (arguments.length() > 2)
	{
		const QString &source = arguments[1];
		const QString &target = arguments[2];

		Tiled::MapReader mapReader;
		Tiled::Map *map = mapReader.readMap(source);
		Tiled::Tileset *tileset = map->tilesetAt(0);

		const QString &tilesetFileName = tileset->imageSource();
		const QImage image(tilesetFileName);

		qDebug() << map->width() << map->height();

		Level level(map->width(), map->height(), image);

		for (int x = 0; x < map->width(); x++)
		{
			for (int y = 0; y < map->height(); y++)
			{
				LevelTile levelTile(x, y);

				for (int i = 0; i < map->layerCount(); i++)
				{
					Tiled::Layer *layer = map->layerAt(i);
					Tiled::TileLayer *tileLayer = dynamic_cast<Tiled::TileLayer *>(layer);

					if (tileLayer)
					{
						Tiled::Cell cell = tileLayer->cellAt(x, y);
						Tiled::Tile *tile = cell.tile;

						if (tile)
						{
							if (layer->name() != "Collision")
							{
								const int id = tile->id();

								levelTile.addLayer(id);
							}
							else
							{
								levelTile.setWalkable(false);
							}
						}
					}

					Tiled::ObjectGroup *objectLayer = dynamic_cast<Tiled::ObjectGroup *>(layer);

					if (objectLayer)
					{
						const QList<Tiled::MapObject *> &objects = objectLayer->objects();

						for (Tiled::MapObject *object : objects)
						{
							const QPointF &position = object->position();
							const QPointF current(x, y);

							if (current == position)
							{
								const QString &typeName = object->type();
								const int id = objectTypes.indexOf(typeName);

								levelTile.addMapObject(id);
							}
						}
					}
				}

				level.addTile(levelTile);
			}
		}

		QFile file(target);

		if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
		{
			QDataStream stream(&file);
			stream.setByteOrder(QDataStream::LittleEndian);
			stream << level;
		}
	}
}
