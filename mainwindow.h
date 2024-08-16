#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "formateurs.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_ajouter_clicked();

    void on_pushButton_supprimer_clicked();

private:
    Ui::MainWindow *ui;
    FORMATEURS F;
};

#endif // MAINWINDOW_H
