#include <QGuiApplication>
#include <QStringList>
#include <QDebug>
#include <QFile>
#include <QDataStream>
#include <QDomDocument>
#include <QFileInfo>

#include <tiled/tile.h>
#include <tiled/tilelayer.h>
#include <tiled/tileset.h>
#include <tiled/mapreader.h>
#include <tiled/map.h>
#include <tiled/mapobject.h>
#include <tiled/objectgroup.h>

#include "Level.h"
#include "LevelBundle.h"

Level *loadLevel(const QString &fileName)
{
	Tiled::MapReader mapReader;
	Tiled::Map *map = mapReader.readMap(fileName);
	Tiled::Tileset *tileset = map->tilesetAt(0);

	const QString &tilesetFileName = tileset->imageSource();
	const QImage image(tilesetFileName);
	const QStringList objectTypes =
	{
		"spawn",
		"goal"
	};

	Level *level = new Level(map->width(), map->height(), image);

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

			level->addTile(levelTile);
		}
	}

	return level;
}

int main(int argc, char **argv)
{
	QGuiApplication application(argc, argv);
	QStringList arguments = application.arguments();

	if (arguments.length() > 1)
	{
		QString sourceFileName = arguments[1];
		QFile input (sourceFileName);
		QDomDocument document;

		if (input.open(QIODevice::ReadOnly))
		{
			document.setContent(&input);

			const QDomElement &root = document
				.namedItem("level")
				.toElement();

			const QString &fileName1 = root
				.firstChildElement("file1")
				.text();

			const QString &fileName2 = root
				.firstChildElement("file2")
				.text();

			const QString &previewFileName = root
				.firstChildElement("preview")
				.text();

			const QImage preview(previewFileName);

			Level *level1 = loadLevel(fileName1);
			Level *level2 = loadLevel(fileName2);

			LevelBundle bundle;
			bundle.setLevel1(level1);
			bundle.setLevel2(level2);
			bundle.setPreview(preview);

			QFileInfo fileInfo(sourceFileName);
			QString targetFileName = fileInfo.baseName() + ".level";
			QFile file(targetFileName);

			if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
			{
				QDataStream stream(&file);
				stream.setByteOrder(QDataStream::LittleEndian);
				stream << bundle;
			}
		}
	}
}
