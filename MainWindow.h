#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Client.h"
#include <QMainWindow>
#include <inttypes.h> //uint_t* and int_t* types
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
		Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

	private slots:
		void on_pushButton_clicked();

		void on_pushButton_2_clicked();

	private:
		uint8_t CalculateFileDataChecksum(QByteArray aData);
		Ui::MainWindow *ui;
		Client *vClient;
};

#endif // MAINWINDOW_H
