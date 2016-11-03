#pragma once

#include <QObject>
#include <ogr_spatialref.h>

class EpsgConversor : public QObject
{
	Q_OBJECT

public:
	EpsgConversor(QObject *parent);
	bool transformCoordinates(double x, double y, double &xOut, double &yOut);
};
