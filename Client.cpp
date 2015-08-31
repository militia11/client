#include "Client.h"

static inline QByteArray IntToArray(int32_t source);

Client::Client(QObject *parent) : QObject(parent) {
    mSocket = new QTcpSocket(this);
mReceiveBuffer = 0;
mData = 0;
}

bool Client::readData()
{	//while (mSocket->bytesAvailable() > 0) {
                QByteArray vData = mSocket->readAll();
                for(int i=0;i<vData.size();i++) {
                    qDebug() << vData[i];
                }
                // if wiadomość równa '<'
                // wyślij dane aktualnie sprawdzanego pliku
                //(sprawdzanej jego sumy)

//				mReceiveBuffer->append(vData);

//				for (int i = 0; i < vData.length(); i++) {

//						char vTargetSign = vData[i];

//						switch (vTargetSign) {

//								case '>':					// początek komunikatu "suma pliku"
//										mReceiveDataMode = Mode_Receive_File_CheckSum;
//										mReceiveByteCnt = 0;
//										break;

//								default:
//										break;
//						}

//						RouteData(vTargetSign);
//				}
//		}
}

bool Client::connectToHost(QString host) {
        mSocket->connectToHost(host, 1234);
        return mSocket->waitForConnected();
}

bool Client::writeData(QByteArray data) {
        if (mSocket->state() == QAbstractSocket::ConnectedState) {
                mSocket->write(IntToArray(data.size())); //write size of data
                mSocket->write(data); //write the data itself
                return mSocket->waitForBytesWritten();
		} else {
				return false;
		}
}

bool Client::writeMessage(QByteArray data)
{
    if (mSocket->state() == QAbstractSocket::ConnectedState) {
            mSocket->write(data); //write the data itself
            return mSocket->waitForBytesWritten();
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
