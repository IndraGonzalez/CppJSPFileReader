#pragma once

#include <QObject>
#include <QThread>
#include <QFile>

class Reader : public QThread
{
	Q_OBJECT

public:
	Reader(QObject *parent);
	~Reader();

	
private:
	int bytes;
	QFile *file;
	QDataStream *in;
	typedef unsigned short Crc16;
	struct NT
	{
		int timeHour;
		int timeMin;
		double timeSec;

		QChar ns;
		int latitudeD;
		int latitudeM;
		double latitudeS;

		QChar ew;
		int longitudeD;
		int longitudeM;
		double longitudeS;

		double altitude;

		int cs;
	};
	NT nt;
	QList<NT> nts;
	
	Crc16 crc16(Crc16 crc, void const* src, int cnt);
	void crc16init(void);
	bool calculateChecksum();
	u1 cs(u1 const* src, int count);

	void readPackage(QFile *file, QDataStream *in, int goForward);
	void readTime(QFile *file, QDataStream *in);
	void goToNextField(QFile *file, QDataStream *in);
	void readCoordinates(QFile *file, QDataStream *in);
	
protected:
	void run() Q_DECL_OVERRIDE;

};



