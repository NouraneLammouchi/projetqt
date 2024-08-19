#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView_formateurs->setModel(F.afficher());//refresh
    ui->tableView_formations->setModel(F1.afficher());//refresh
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
    QString specialite = ui->comboBox_specialite->currentText();
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
     ui->comboBox_specialite->setCurrentIndex(0);
     ui->lineEdit_ntel->clear();
   }


    else

     QMessageBox::critical(nullptr, QObject::tr("not ok"),
     QObject::tr("ajout non effectué.\n"
                 "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_pushButton_supprimer_clicked()
{
    QModelIndexList selectedRows = ui->tableView_formateurs->selectionModel()->selectedRows();
        if (selectedRows.isEmpty()) {
            QMessageBox::warning(this, tr("Aucune ligne sélectionnée"),
                                 tr("Veuillez sélectionner une ligne à supprimer."),
                                 QMessageBox::Ok);
            return;
        }


        int id_formateur = selectedRows.at(0).data().toInt();
       FORMATEURS F;

       bool test=F.supprimer(id_formateur);
       if(test)
      {
          ui->tableView_formateurs->setModel(F.selectformateurById(id_formateur));//refresh
         QMessageBox::information(nullptr, QObject::tr("ok"),
         QObject::tr("suppression effectué.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
    ui->tableView_formateurs->setModel(F.selectformateurById(id_formateur));//refresh
      }
       else
         QMessageBox::critical(nullptr, QObject::tr("not ok"),
         QObject::tr("suppression non effectué.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_pushButton_ajouter_2_clicked()
{
    int id_formation=ui->lineEdit_id_formation->text().toInt();
    QString titre=ui->lineEdit_titre->text();
    QDate datedebut = ui->dateEdit_debut->date();
    QDate datefin = ui->dateEdit_fin->date();
    QString duree = ui->lineEdit_duree->text();
    int nbrplace = ui->lineEdit_nbrplace->text().toInt();
    QString typeformation = ui->comboBox_type->currentText();
    int id_formateur = ui->lineEdit_id_formateur->text().toInt();

    FORMATIONS F1(id_formation, titre, datedebut, datefin, duree, nbrplace, typeformation, id_formateur);
    bool test=F1.ajouter();
    if(test)
   {
        ui->tableView_formations->setModel(F1.afficher());

      QMessageBox::information(nullptr, QObject::tr("ok"),
      QObject::tr("ajout effectué.\n"
                   "Click Cancel to exit."), QMessageBox::Cancel);

     ui->lineEdit_id_formation->clear();
     ui->lineEdit_titre->clear();
     ui->lineEdit_duree->clear();
     ui->lineEdit_nbrplace->clear();
     ui->comboBox_type->setCurrentIndex(0);
     ui->lineEdit_id_formateur->clear();

   }


    else

     QMessageBox::critical(nullptr, QObject::tr("not ok"),
     QObject::tr("ajout non effectué.\n"
                 "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_pushButton_supprimer_2_clicked()
{
    QModelIndexList selectedRows = ui->tableView_formations->selectionModel()->selectedRows();
        if (selectedRows.isEmpty()) {
            QMessageBox::warning(this, tr("Aucune ligne sélectionnée"),
                                 tr("Veuillez sélectionner une ligne à supprimer."),
                                 QMessageBox::Ok);
            return;
        }


        int id_formation = selectedRows.at(0).data().toInt();
       FORMATIONS F1;

       bool test=F1.supprimer(id_formation);
       if(test)
      {
          ui->tableView_formations->setModel(F1.selectformationById(id_formation));//refresh
         QMessageBox::information(nullptr, QObject::tr("ok"),
         QObject::tr("suppression effectué.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
    ui->tableView_formations->setModel(F1.selectformationById(id_formation));//refresh
      }
       else
         QMessageBox::critical(nullptr, QObject::tr("not ok"),
         QObject::tr("suppression non effectué.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_tableView_formateurs_clicked(const QModelIndex &index)
{


       // Get data from the selected index
        int id_formateur = index.sibling(index.row(), 0).data().toInt();
        QString nom = index.sibling(index.row(), 1).data().toString();
        QString prenom = index.sibling(index.row(), 2).data().toString();
        QString email = index.sibling(index.row(), 3).data().toString();
        QString specialite = index.sibling(index.row(), 4).data().toString();
        QString ntel = index.sibling(index.row(), 5).data().toString();

        // Populate line edit fields with the retrieved data
        ui->lineEdit_id->setText(QString::number(id_formateur));
        ui->lineEdit_nom->setText(nom);
        ui->lineEdit_prenom->setText(prenom);
        ui->lineEdit_email->setText(email);
        ui->comboBox_specialite->setCurrentText(specialite);
        ui->lineEdit_ntel->setText(ntel);
}

void MainWindow::on_tableView_formations_clicked(const QModelIndex &index)
{


       // Get data from the selected index
        int id_formation = index.sibling(index.row(), 0).data().toInt();
        QString titre = index.sibling(index.row(), 1).data().toString();
        QDate datedebut = index.sibling(index.row(), 2).data().toDate();
        QDate datefin = index.sibling(index.row(), 3).data().toDate();
        QString duree = index.sibling(index.row(), 4).data().toString();
        int nbrplace = index.sibling(index.row(), 5).data().toInt();
        QString typeformation = index.sibling(index.row(), 6).data().toString();
        int id_formateur = index.sibling(index.row(), 7).data().toInt();

        // Populate line edit fields with the retrieved data
        ui->lineEdit_id_formation->setText(QString::number(id_formation));
        ui->lineEdit_titre->setText(titre);
        ui->dateEdit_debut->setDate(datedebut);
        ui->dateEdit_fin->setDate(datefin);
        ui->lineEdit_duree->setText(duree);
        ui->lineEdit_nbrplace->setText(QString::number(nbrplace));
        ui->lineEdit_id_formateur->setText(QString::number(id_formateur));
}





void MainWindow::on_pushButton_modifier_clicked()
{
    int id_formateur=ui->lineEdit_id->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    QString email = ui->lineEdit_email->text();
    QString specialite = ui->comboBox_specialite->currentText();
    QString ntel = ui->lineEdit_ntel->text();

    FORMATEURS F(id_formateur,nom,prenom,email,specialite,ntel);
    bool test=F.modifier(id_formateur);
    if(test)
   {
        ui->tableView_formateurs->setModel(F.afficher());

      QMessageBox::information(nullptr, QObject::tr("ok"),
      QObject::tr("modification effectué.\n"
                   "Click Cancel to exit."), QMessageBox::Cancel);

     ui->lineEdit_id->clear();
     ui->lineEdit_nom->clear();
     ui->lineEdit_prenom->clear();
     ui->lineEdit_email->clear();
     ui->comboBox_specialite->setCurrentIndex(0);
     ui->lineEdit_ntel->clear();
    }

 }

void MainWindow::on_pushButton_modifier_2_clicked()
{
    int id_formation=ui->lineEdit_id_formation->text().toInt();
    QString titre=ui->lineEdit_titre->text();
    QDate datedebut = ui->dateEdit_debut->date();
    QDate datefin = ui->dateEdit_fin->date();
    QString duree = ui->lineEdit_duree->text();
    int nbrplace = ui->lineEdit_nbrplace->text().toInt();
    QString typeformation = ui->comboBox_type->currentText();
    int id_formateur = ui->lineEdit_id_formateur->text().toInt();

    FORMATIONS F1(id_formation, titre, datedebut, datefin, duree, nbrplace, typeformation, id_formateur);
    bool test=F1.modifier(id_formation);
    if(test)
   {
        ui->tableView_formations->setModel(F1.afficher());

      QMessageBox::information(nullptr, QObject::tr("ok"),
      QObject::tr("modification effectué.\n"
                   "Click Cancel to exit."), QMessageBox::Cancel);

     ui->lineEdit_id_formation->clear();
     ui->lineEdit_titre->clear();
     ui->lineEdit_duree->clear();
     ui->lineEdit_nbrplace->clear();
     ui->comboBox_type->setCurrentIndex(0);
     ui->lineEdit_id_formateur->clear();

}
}
