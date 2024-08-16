#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView_formateurs->setModel(F.afficher());//refresh
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_ajouter_clicked()
{
    int id_formateur=ui->lineEdit_id->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    QString email = ui->lineEdit_email->text();
    QString specialite = ui->lineEdit_specialite->text();
    QString ntel = ui->lineEdit_ntel->text();

    FORMATEURS F(id_formateur,nom,prenom,email,specialite,ntel);
    bool test=F.ajouter();
    if(test)
   {
        ui->tableView_formateurs->setModel(F.afficher());

      QMessageBox::information(nullptr, QObject::tr("ok"),
      QObject::tr("ajout effectué.\n"
                   "Click Cancel to exit."), QMessageBox::Cancel);

     ui->lineEdit_id->clear();
     ui->lineEdit_nom->clear();
     ui->lineEdit_prenom->clear();
     ui->lineEdit_email->clear();
     ui->lineEdit_specialite->clear();
     ui->lineEdit_ntel->clear();
   }


    else

     QMessageBox::critical(nullptr, QObject::tr("not ok"),
     QObject::tr("ajout non effectué.\n"
                 "Click Cancel to exit."), QMessageBox::Cancel);


}
