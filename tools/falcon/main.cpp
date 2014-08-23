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

#include "Level.h"

int main(int argc, char **argv)
{
	QGuiApplication application(argc, argv);
	QStringList arguments = application.arguments();

	if (arguments.length() > 2)
	{
		const QString &source = arguments[1];
		const QString &target = arguments[2];

		Tiled::MapReader mapReader;
		Tiled::Map *map = mapReader.readMap(source);
		Tiled::Tileset *tileset = map->tilesetAt(0);

		Tiled::Layer *layer = map->layerAt(0);
		Tiled::TileLayer *tileLayer = dynamic_cast<Tiled::TileLayer *>(layer);

		if (tileLayer)
		{
			const QString &tilesetFileName = tileset->imageSource();
			const QImage image(tilesetFileName);

			qDebug() << map->width() << map->height();

			Level level(map->width(), map->height(), image);

			for (int x = 0; x < map->width(); x++)
			{
				for (int y = 0; y < map->height(); y++)
				{
					Tiled::Cell cell = tileLayer->cellAt(x, y);
					Tiled::Tile *tile = cell.tile;

					if (tile)
					{
						LevelTile levelTile(tile->id(), x, y);
						level.addTile(levelTile);
					}
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
}
