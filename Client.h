#ifndef CLIENT_H
#define CLIENT_H
#include <QtCore>
#include <QtNetwork>
#include <inttypes.h> //uint_t* and int_t* types
#include <QByteArray>

class Client : public QObject {
		Q_OBJECT
	public:
		explicit Client(QObject *parent = 0);
		bool WriteData(QByteArray data);
		bool WriteMessage(QByteArray aData);
	bool PrepareMessageData();

	public slots:
		void ReadData();
		bool ConnectToHost(QString host);


	private:

		uint8_t CalculateMessageChecksum(QByteArray aData);
		void ConvertBinaryToHexAscii(const char *aData, int aLen,
																 char *aTarget);

		QTcpSocket *mSocket;
		QByteArray *mReceiveBuffer;
		QByteArray *mActualData;
		char mSendBuffer[2048];
};
#endif // CLIENT_H
