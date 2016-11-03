#pragma once

#include <QObject>
#include <QThread>
#include <QFile>
#include <EpsgConversor.h>

class Reader : public QThread
{
	Q_OBJECT

public:
	Reader(QObject *parent);

	
private:
	int bytes;
	QFile *file;
	QDataStream *in;
	typedef unsigned short Crc16;
	struct NP
	{
		int timeHour;
		int timeMin;
		double timeSec;

		double time;

		QChar ns;
		int latitudeD;
		int latitudeM;
		double latitudeS;

		double latitude;

		QChar ew;
		int longitudeD;
		int longitudeM;
		double longitudeS;

		double longitude;

		double altitude;

		int cs;
	};
	NP np;
	QList<NP> nps;

	void readPackage(QFile *file, QDataStream *in, int goForward);
	void readTime(QFile *file, QDataStream *in);
	void goToNextField(QFile *file, QDataStream *in);
	void readCoordinates(QFile *file, QDataStream *in);
	void writeDataFile();
	int getDayOfWeek(int year, int month, int day);
	
protected:
	void run() Q_DECL_OVERRIDE;

};



