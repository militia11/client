#ifndef CLIENT_H
#define CLIENT_H
#include <QtCore>
#include <QtNetwork>
#include <inttypes.h> //uint_t* and int_t* types

class Client : public QObject
{
		Q_OBJECT
public:
		explicit Client(QObject *parent = 0);

public slots:
		bool connectToHost(QString host);
		bool writeData(QByteArray data);
		bool writeMessage(QByteArray aData);
		uint8_t CalculateMessageChecksum(QByteArray aData);
private:
		QTcpSocket *socket;
};
#endif // CLIENT_H
