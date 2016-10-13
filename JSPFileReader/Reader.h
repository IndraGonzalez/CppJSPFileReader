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
		qint16 time [3];
		QChar ns;
		quint16 latitudeD;
		quint16 latitudeM;
		quint64 latitudeS;
		QChar ew;
		quint16 longitudeD;
		quint16 longitudeM;
		quint64 longitudeS;
		quint16 cs;
	};
	NT nt;
	QList<NT> nts;
	Crc16 crc16(Crc16 crc, void const* src, int cnt);
	void crc16init(void);
	bool calculateChecksum();
	void readPackage(QFile *file, QDataStream *in);
	int calculateValue(char value1, char value2, char value3);
	int calculateValue(char value1, char value2);
	int getValue(char size);
	
protected:
	void run() Q_DECL_OVERRIDE;

};



