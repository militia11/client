#include "Client.h"
#include <QImage>
#include <QImageWriter>
static inline QByteArray IntToArray(int32_t source);

Client::Client(QObject *parent) : QObject(parent) {
    mSocket = new QTcpSocket(this);
		mReceiveBuffer = 0;
		mActualData = 0;
		connect( mSocket, SIGNAL(readyRead()),
						 this, SLOT(ReadData()), Qt::DirectConnection );
}

void Client::ReadData() {
		//while (mSocket->bytesAvailable() > 0) {
		QByteArray vMessageData = mSocket->readAll();
		qDebug() << vMessageData;

		if (vMessageData == QByteArray("SEND")) { // if wiadomość równa 'SEND'
				//writeData(mActualData); // wyślij plik(jego dane binarne) aktualnie sprawdzanego pliku
				//(sprawdzanej jego sumy)


				//	int v = CalculateMessageChecksum(vData);
				//	qDebug() << "suma->" << v;

				WriteData(mSendBuffer);
		}
}

bool Client::ConnectToHost(QString host) {
		mSocket->connectToHost(host, 1234);
		return mSocket->waitForConnected();
}

void Client::ConvertBinaryToHexAscii(const char *aData, int aLen,
																		 char *aTarget) {
		char buffer[3];

		for (int i = 0; i < aLen; ++i) {
				snprintf(buffer, 3, "%02X", aData[i]);
				aTarget[2 * i] = buffer[0];
				aTarget[2 * i + 1] = buffer[1];
		}
}

bool Client::PrepareMessageData() {
		// narazie tak:
		QImage vImage = QImage ("/home/mmichniewski/b.jpeg", "JPEG");
		QBuffer vBuffer;

		QImageWriter vWriter(&vBuffer, "JPEG");
		vWriter.write(vImage);

		QByteArray vData = vBuffer.data();

		ConvertBinaryToHexAscii(vData, vData.length(), mSendBuffer + 2);

		//								// CRC
		//								uint8_t vChecksum = CalculateMessageChecksum(mSendBuffer, 2+2*aLen);
		//								ConvertBinaryToHexAscii(&vChecksum, 1, mSendBuffer+2+aLen*2);

		//								// footer
		//								mSendBuffer[2+2+2*aLen] = 0x0D; // CR
		//								mSendBuffer[2+2+2*aLen+1] = 0x0A; // LF

		//								return 2*aLen + 6;
}

bool Client::WriteData(QByteArray aData) {
		if (mSocket->state() == QAbstractSocket::ConnectedState) {
				char vTar[aData.length()];
				ConvertBinaryToHexAscii(aData, aData.length(),
																vTar);
				qDebug() << vTar;
				char vTar2[aData.length()];
				ConvertHexAsciiToBinary(vTar, 2024,
															 vTar2);
QByteArray databuf;
				databuf = QByteArray(reinterpret_cast<char*>(vTar2), 10);
				mSocket->write(IntToArray(databuf.length())); //write size of data
				mSocket->write(databuf); //write the data itself
				return mSocket->waitForBytesWritten();
		} else {
				return false;

		}
}

bool Client::WriteMessage(QByteArray data) {
    if (mSocket->state() == QAbstractSocket::ConnectedState) {
				mSocket->write(data); //write the data itself
				return mSocket->waitForBytesWritten();
		} else {
				return false;
		}

		//			// if (socket->state() == QAbstractSocket::ConnectedState) {
		//					 //	socket->write(IntToArray(data.size())); //write size of data

		//					 aData.insert(0, '>');
		//					 qDebug()<< aData;
		//					 u_int8_t vMessageCheckSum = CalculateMessageChecksum(aData);

		//					 qDebug()<< aData;
		//					 socket->write(aData); //write the data itself
		//					 return socket->waitForBytesWritten();
		//		//    } else {
		//		//        return false;
		//		//    }
}

uint8_t Client::CalculateMessageChecksum(QByteArray aData) {
		uint8_t sum = 0;

		for (int i = 0; i < aData.length(); ++i) {
				sum += aData[i];
		}

		return sum;
}

void Client::ConvertHexAsciiToBinary(const char *aData, int aLen,
																		 char *aTarget) {
		for (int i = 0; i < aLen - 1; i += 2) {
				char hex[3] = {aData[i], aData[i + 1], 0x00};
				aTarget[i / 2] = static_cast<char>(strtol(hex, NULL, 16));
		}
}
QByteArray IntToArray(int32_t
											source) { //Use qint32 to ensure that the number have 4 bytes
		//Avoid use of cast, this is the Qt way to serialize objects
		QByteArray temp;
		QDataStream data(&temp, QIODevice::ReadWrite);
		data << source;
		return temp;
}
