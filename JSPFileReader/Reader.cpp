#include "Reader.h"
#include<qfile.h>
#include<qdatastream.h>
#include<qdebug.h>
#include <stdio.h>
#include <time.h>

Reader::Reader(QObject *parent)
	: QThread(parent)
{}

void Reader::run()
{
	/*
	No funciona el checksum (el método)
	*/
	QString path = "//srv01/PracticasProgramacion/Datos/Kalman/20160809_141551.JPS";
	file = new QFile(path);
	
	if (file->open(QIODevice::ReadOnly))
	{
		in = new QDataStream(file);
		in->setByteOrder(QDataStream::LittleEndian);

		while (!in->atEnd())
		{
			char *type1 = new char[1];
			in->readRawData(type1, 1);
			
			if (*type1 == 'N')
			{
				char *type2 = new char[1];
				in->readRawData(type2, 1);
				if (*type2 == 'P') {
					char *type2 = new char[1];
					int start = file->pos();
					int goBack = file->pos() + 4;

					QByteArray strSize(3, '0');
					in->readRawData(strSize.data(), 3);
					bool ok;
					int size = strSize.toInt(&ok, 16);

					int goForward = file->pos() + size - 3;
					file->seek(goForward);

					char *at = new char[1];
					in->readRawData(at, 1);
					if (*at == '@')
					{
						QByteArray strCS(2, '0');
						in->readRawData(strCS.data(), 2);
						bool ok;
						np.cs = strCS.toInt(&ok, 16);

						file->seek(goBack);
						readPackage(file, in, goForward);
					}
					delete at;
				}
				delete type2;
			}
			delete type1;
		}
		//qDebug() << file->pos() << endl;
		file->close();
		delete in;
	}
	delete file;
	writeDataFile();
}


void Reader::readPackage(QFile *file, QDataStream *in, int goForward)
{
	//qDebug() << "Estoy leyendo el paquete
	// Saltar hasta el marcador de válido (tamaño fijo)
	file->seek(file->pos() + 7);

	char *valid = new char[1];
	in->readRawData(valid, 1);
	file->seek(file->pos() + 1);
	
	if (*valid == 'V') 
		readTime(file, in);
	else
		goToNextField(file,in);

	for (int i = 0; i < 5; i++) goToNextField(file,in);

	readCoordinates(file, in);
	
	nps.append(np);

	file->seek(goForward + 3);
	delete valid;
}

void Reader::readTime(QFile *file, QDataStream *in) {
	bool ok;
	QByteArray time(2, '0');

	int year = 2016;
	int month = 8;
	int day = 9;
	int daysOfWeek = getDayOfWeek(year,month,day);

	in->readRawData(time.data(), 2);
	np.timeHour = time.toInt(&ok, 10);

	in->readRawData(time.data(), 2);
	np.timeMin = time.toInt(&ok, 10);

	QByteArray timeSec(5, '0');
	in->readRawData(timeSec.data(), 5);
	np.timeSec = timeSec.toDouble();
	file->seek(file->pos() + 1);

	np.time = (daysOfWeek*24*60*60) + (np.timeHour * 60 * 60) + (np.timeMin * 60) + np.timeSec;
}

void Reader::goToNextField(QFile * file, QDataStream * in)
{
	bool stop = false;
	char *next = new char[1];
	while (!stop) {
		int pos = file->pos();
		in->readRawData(next, 1);
		if (*next == ',') 
			stop = true;
	}
	delete next;
}

void Reader::readCoordinates(QFile * file, QDataStream * in)
{
	char *charNS = new char[1];
	in->readRawData(charNS, 1);
	QChar ns(*charNS);
	np.ns = ns;

	bool ok;
	QByteArray latitude(2, '0');
	in->readRawData(latitude.data(), 2);
	np.latitudeD = latitude.toInt(&ok, 10);

	file->seek(file->pos() + 1);

	in->readRawData(latitude.data(), 2);
	np.latitudeM = latitude.toInt(&ok, 10);

	file->seek(file->pos() + 1);

	QByteArray latitudeSec(9, '0');
	in->readRawData(latitudeSec.data(), 9);
	np.latitudeS = latitudeSec.toDouble();

	np.latitude = np.latitudeD + (np.latitudeM/60) + (np.latitudeS/3600);
	if (np.ns == 'S') {
		np.latitude *= -1;
	}

	file->seek(file->pos() + 2);

	char *charEW = new char[1];
	in->readRawData(charEW, 1);
	QChar ew(*charEW);
	np.ew = ew;

	QByteArray longitudeDeg(3, '0');
	in->readRawData(longitudeDeg.data(), 3);
	np.longitudeD = longitudeDeg.toInt(&ok, 10);

	file->seek(file->pos() + 1);

	QByteArray longitudeMin(2, '0');
	in->readRawData(longitudeMin.data(), 2);
	np.longitudeM = longitudeMin.toInt(&ok, 10);

	file->seek(file->pos() + 1);

	QByteArray longitudeSec(9, '0');
	in->readRawData(longitudeSec.data(), 9);
	np.longitudeS = longitudeSec.toDouble();

	np.longitude = np.longitudeD + (np.longitudeM / 60) + (np.longitudeS / 3600);
	if (np.ew == 'W') {
		np.longitude *= -1;
	}
	
	file->seek(file->pos() + 3);

	QByteArray altitude(10, '0');
	in->readRawData(altitude.data(), 10);
	np.altitude = altitude.toDouble();

	EpsgConversor conversor(NULL);
	double xOut, yOut;
	conversor.transformCoordinates(np.longitude, np.latitude, xOut, yOut);
	np.latitude = xOut;
	np.longitude = yOut;
	delete charEW, charNS;
}

void Reader::writeDataFile() {

	QFile file("C:/Users/igonzalez/Desktop/DatosKalman/datosGPS.txt");
	if (file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QTextStream out(&file);

		for (int i = 0; i < nps.length(); i++)
		{
			out.setRealNumberNotation(QTextStream::FixedNotation);
			out.setRealNumberPrecision(2);
			out << nps[i].time << "\t";
			out.setRealNumberPrecision(4);
			out << nps[i].latitude << "\t";
			out.setRealNumberPrecision(8);
			out << nps[i].longitude << "\t";
			out.setRealNumberPrecision(4);
			out << nps[i].altitude << endl;
		}
	}
	//qDebug() << nps.length() << endl;
	file.close();
}

int Reader::getDayOfWeek(int year, int month, int day) {
	tm timeStruct = {};
	timeStruct.tm_year = year - 1900;
	timeStruct.tm_mon = month - 1;
	timeStruct.tm_mday = day;
	timeStruct.tm_hour = 12;
	mktime(&timeStruct);
	return timeStruct.tm_wday;
}
