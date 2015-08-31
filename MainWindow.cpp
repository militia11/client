#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <iostream>
#include <QTimer>
#include <QFile>
#include <QImage>
#include <QImageWriter>

MainWindow::MainWindow(QWidget *parent) :
		QMainWindow(parent),
		ui(new Ui::MainWindow) {
		ui->setupUi(this);
		vClient = new Client;
		vClient->ConnectToHost("localhost");

		//image.loadFromData(QByteArray data);

		//write
		//		QFile File("/home/mmichniewski/b.txt");//pobranyPies.jpg");

		//		if (!File.open(QIODevice::WriteOnly)) {
		//				qDebug() << "Nie można otworzyć pliku";
		//		}

		//		QByteArray aData("sex");
		//		QDataStream out(&File);
		//		QByteArray s("slsus");
		//		out << s;
		//		File.close();
}

MainWindow::~MainWindow() {
		delete ui;
}

void MainWindow::on_pushButton_clicked() {
		QByteArray vMessageData(">336<");
		qDebug() << "sumaFile->" << vMessageData;
		vClient->WriteMessage(vMessageData);
}

void MainWindow::on_pushButton_2_clicked() {
		QImage vImage = QImage ("/home/mmichniewski/b.jpeg", "JPEG");
		QBuffer vBuffer;

		QImageWriter vWriter(&vBuffer, "JPEG");
		vWriter.write(vImage);

		QByteArray vData = vBuffer.data();

		int v = CalculateFileDataChecksum(vData);
		qDebug() << "suma->" << v;

		vClient->WriteData(vData);
}

uint8_t MainWindow::CalculateFileDataChecksum(QByteArray aData) {
		uint8_t vSum = 0;

		for (int i = 0; i < aData.length(); ++i) {
				vSum += aData[i];
		}

		return vSum;
}
