#include "Client.h"

static inline QByteArray IntToArray(int32_t source);

Client::Client(QObject *parent) : QObject(parent) {
		socket = new QTcpSocket(this);
}

bool Client::connectToHost(QString host) {
		socket->connectToHost(host, 1234);
		return socket->waitForConnected();
}

bool Client::writeData(QByteArray data) {
		if (socket->state() == QAbstractSocket::ConnectedState) {
				socket->write(IntToArray(data.size())); //write size of data
				socket->write(data); //write the data itself
				return socket->waitForBytesWritten();
		} else {
				return false;
		}
}

bool Client::writeMessage(QByteArray data)
{
	if (socket->state() == QAbstractSocket::ConnectedState) {
			socket->write(data); //write the data itself
			return socket->waitForBytesWritten();
	} else {
			return false;
	}

//	// if (socket->state() == QAbstractSocket::ConnectedState) {
//			 //	socket->write(IntToArray(data.size())); //write size of data

//			 aData.insert(0, '>');
//			 qDebug()<< aData;
//			 u_int8_t vMessageCheckSum = CalculateMessageChecksum(aData);

//			 qDebug()<< aData;
//			 socket->write(aData); //write the data itself
//			 return socket->waitForBytesWritten();
////    } else {
////        return false;
////    }
}

uint8_t Client::CalculateMessageChecksum(QByteArray aData) {
	uint8_t sum = 0;

	for (int i = 0; i < aData.length(); ++i) {
		sum += aData[i];
	}

	return sum;
}
QByteArray IntToArray(int32_t source) { //Use qint32 to ensure that the number have 4 bytes
		//Avoid use of cast, this is the Qt way to serialize objects
		QByteArray temp;
		QDataStream data(&temp, QIODevice::ReadWrite);
		data << source;
		return temp;
}
