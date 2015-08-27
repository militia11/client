#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <iostream>
#include <QTimer>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
		QMainWindow(parent),
		ui(new Ui::MainWindow) {
		ui->setupUi(this);
		vClient = new Client;
		vClient->connectToHost("localhost");

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
		QByteArray arx(">183<");
		vClient->writeMessage(arx);
}

void MainWindow::on_pushButton_2_clicked() {
		QFile vFile("/home/mmichniewski/a.txt");  //pies.jpg

		if (!vFile.open(QIODevice::ReadOnly)) {
				qDebug() << "Nie można otworzyć pliku";
		}

		// dane
		QByteArray vData(vFile.readAll());
		qDebug() << vData;
		vFile.close();
		vClient->writeData(vData);
}
