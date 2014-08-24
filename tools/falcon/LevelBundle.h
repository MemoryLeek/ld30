#ifndef LEVELBUNDLE_H
#define LEVELBUNDLE_H

#include <QImage>

#include "Level.h"

class LevelBundle
{
	friend QDataStream &operator <<(QDataStream &stream, const LevelBundle &bundle);

	public:
		LevelBundle();

		void setPreview(const QImage &preview);
		void setLevel1(Level *level1);
		void setLevel2(Level *level2);

	private:
		QImage m_preview;

		Level *m_level1;
		Level *m_level2;
};

#endif // LEVELBUNDLE_H
