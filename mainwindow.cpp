#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QCameraViewfinder>
#include<QCameraImageCapture>
#include<QVBoxLayout>
#include<QMenu>
#include<QAction>
#include<QFileDialog>
#include "qmessagebox.h"
#include "connection.h"
#include <QIntValidator>
#include <QTableView>
#include <QMessageBox>
#include <QPixmap>
#include<QPrinter>
#include<QPainter>
#include<QPrintDialog>
#include <QPrintPreviewDialog>
#include <QPdfWriter>
#include <QtCharts>
#include <QDesktopServices>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QPieSlice>
#include <QPieSeries>
#include <QChartView>

#include <QPrintDialog>
#include <QFileDialog>
#include <QPieSlice>
#include <QPieSeries>
#include <QChartView>


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
    // Réinitialisez les étiquettes d'erreur à vide
        ui->label_id->setText("");
        ui->label_nom->setText("");
        ui->label_prenom->setText("");
        ui->label_email->setText("");
        ui->label_specialite->setText("");
        ui->label_ntel->setText("");


    int id_formateur=ui->lineEdit_id->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    QString email = ui->lineEdit_email->text();
    QString specialite = ui->comboBox_specialite->currentText();
    QString ntel = ui->lineEdit_ntel->text();

    // Validez les champs d'entrée
        bool isValid = true;
        QString id_formateurString = QString::number(id_formateur);
        if (id_formateurString.isEmpty())
        {
            ui->label_id->setText("<font color='red'>ID formateur ne peut pas être vide!!!!</font>");
            isValid = false;
        }

        if (nom.isEmpty()) {
            ui->label_nom->setText("<font color='red'>nom ne peut pas être vide!!!</font>");
            isValid = false;
        }

        if (prenom.isEmpty()) {
            ui->label_prenom->setText("<font color='red'>prenom ne peut pas être vide!!!</font>");
            isValid = false;
        }
        if (email.isEmpty()) {
            ui->label_email->setText("<font color='red'>email ne peut pas être vide!!!</font>");
            isValid = false;
        }
        if (specialite.isEmpty()) {
            ui->label_specialite->setText("<font color='red'>specialite ne peut pas être vide!!!</font>");
            isValid = false;
        }
        if (ntel.isEmpty()) {
            ui->label_ntel->setText("<font color='red'>num tel ne peut pas être vide!!!</font>");
            isValid = false;
        }

        // Ajouter une vérification de l'existence de l'ID dans la base de données
        QSqlQuery checkQuery;
        checkQuery.prepare("SELECT id_formateur FROM FORMATEURS WHERE id_formateur = :id_formateur");
        checkQuery.bindValue(":id_formateur", id_formateur);
        if (checkQuery.exec() && checkQuery.next()) {
            ui->label_id->setText("<font color='red'>ID formateur existe déjà!!!!</font>");
            isValid = false;
        }

        // Continuez avec les autres validations d'entrée...

        if (isValid)
        {

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

             ui->label_id->clear();
             ui->label_nom->clear();
             ui->label_prenom->clear();
             ui->label_email->clear();
             ui->label_specialite->clear();
             ui->label_ntel->clear();
           }


            else

             QMessageBox::critical(nullptr, QObject::tr("not ok"),
             QObject::tr("ajout non effectué.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);


           }
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
         ui->tableView_formateurs->setModel(F.afficher());//refresh

      }
       else
         QMessageBox::critical(nullptr, QObject::tr("not ok"),
         QObject::tr("suppression non effectué.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);



}
void MainWindow::on_pushButton_ajouter_2_clicked()
{
    // Réinitialisez les étiquettes d'erreur à vide
    ui->label_id_formateur->setText("");
    ui->label_titre->setText("");
    ui->label_datedebut->setText("");
    ui->label_datefin->setText("");
    ui->label_duree->setText("");
    ui->label_nbrplace->setText("");
    ui->label_type->setText("");
    ui->label_id_formation->setText("");

    bool isValid = true;

    // Validez les champs d'entrée avant de convertir en int
    QString id_formationStr = ui->lineEdit_id_formation->text();
    QString titre = ui->lineEdit_titre->text();
    QString duree = ui->lineEdit_duree->text();
    QString nbrplaceStr = ui->lineEdit_nbrplace->text();
    QString typeformation = ui->comboBox_type->currentText();
    QString id_formateurStr = ui->lineEdit_id_formateur->text();

    if (id_formationStr.isEmpty()) {
        ui->label_id_formation->setText("<font color='red'>ID formation ne peut pas être vide!!!!</font>");
        isValid = false;
    }
    if (titre.isEmpty()) {
        ui->label_titre->setText("<font color='red'>Titre ne peut pas être vide!!!</font>");
        isValid = false;
    }
    if (duree.isEmpty()) {
        ui->label_duree->setText("<font color='red'>Durée ne peut pas être vide!!!</font>");
        isValid = false;
    }
    if (nbrplaceStr.isEmpty()) {
        ui->label_nbrplace->setText("<font color='red'>Nombre de places ne peut pas être vide!!!</font>");
        isValid = false;
    }
    if (typeformation.isEmpty()) {
        ui->label_type->setText("<font color='red'>Type ne peut pas être vide!!!</font>");
        isValid = false;
    }
    if (id_formateurStr.isEmpty()) {
        ui->label_id_formateur->setText("<font color='red'>ID formateur ne peut pas être vide!!!</font>");
        isValid = false;
    }

    // Convertissez les valeurs après la validation
    int id_formation = id_formationStr.toInt();
    int nbrplace = nbrplaceStr.toInt();
    int id_formateur = id_formateurStr.toInt();
    QDate datedebut = ui->dateEdit_debut->date();
    QDate datefin = ui->dateEdit_fin->date();

    // Ajouter une vérification de l'existence de l'ID dans la base de données
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT id_formation FROM FORMATIONS WHERE id_formation = :id_formation");
    checkQuery.bindValue(":id_formation", id_formation);
    if (checkQuery.exec() && checkQuery.next()) {
        ui->label_id_formation->setText("<font color='red'>ID formation existe déjà!!!!</font>");
        isValid = false;
    }

    // Continuez avec l'ajout si toutes les validations sont correctes
    if (isValid) {
        FORMATIONS F1(id_formation, titre, datedebut, datefin, duree, nbrplace, typeformation, id_formateur);
        bool test = F1.ajouter();
        if (test) {
            ui->tableView_formations->setModel(F1.afficher());

            QMessageBox::information(nullptr, QObject::tr("ok"),
                                     QObject::tr("Ajout effectué.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);

            ui->lineEdit_id_formation->clear();
            ui->lineEdit_titre->clear();
            ui->lineEdit_duree->clear();
            ui->lineEdit_nbrplace->clear();
            ui->comboBox_type->setCurrentIndex(0);
            ui->lineEdit_id_formateur->clear();

            ui->label_id_formation->clear();
            ui->label_titre->clear();
            ui->label_duree->clear();
            ui->label_nbrplace->clear();
            ui->label_type->clear();
            ui->label_id_formateur->clear();
        } else {
            QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                  QObject::tr("Ajout non effectué.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
        }
    }
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
         QMessageBox::information(nullptr, QObject::tr("ok"),
         QObject::tr("suppression effectué.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
         ui->tableView_formations->setModel(F1.afficher());//refresh
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

void MainWindow::on_statistique_clicked()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM FORMATEURS WHERE specialite='Intelligence artificielle'");
    float dispo1 = model->rowCount();

    model->setQuery("SELECT * FROM FORMATEURS WHERE specialite='Developpement web'");
    float dispo = model->rowCount();

    model->setQuery("SELECT * FROM FORMATEURS WHERE specialite='mobile'");
    float dispo2 = model->rowCount();

    float total = dispo1 + dispo + dispo2;
    QString a = QString("Intelligence artificielle  " + QString::number((dispo1 * 100) / total, 'f', 2) + "%");
    QString b = QString("Developpement web" + QString::number((dispo * 100) / total, 'f', 2) + "%");
    QString c = QString("mobile" + QString::number((dispo2 * 100) / total, 'f', 2) + "%");

    QPieSeries *series = new QPieSeries();
    series->append(a, dispo1);
    series->append(b, dispo);
    series->append(c, dispo2);

    if (dispo1 != 0)
    {
        QPieSlice *slice = series->slices().at(0);
        slice->setLabelVisible();
        slice->setPen(QPen());
    }

    if (dispo != 0)
    {
        QPieSlice *slice1 = series->slices().at(1);
        slice1->setLabelVisible();
    }
    if (dispo2 != 0)
    {
        QPieSlice *slice = series->slices().at(0);
        slice->setLabelVisible();
        slice->setPen(QPen());
    }



    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("SPECIALITE : nombre de formateurs " + QString::number(total));

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1000, 500);
    chartView->show();
}

void MainWindow::on_statistique_2_clicked()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM FORMATIONS WHERE typeformation='mobile'");
    float dispo1 = model->rowCount();

    model->setQuery("SELECT * FROM FORMATIONS WHERE typeformation='full stack'");
    float dispo = model->rowCount();

    model->setQuery("SELECT * FROM FORMATIONS WHERE typeformation='marketing'");
    float dispo2 = model->rowCount();

    float total = dispo1 + dispo + dispo2;
    QString a = QString("mobile " + QString::number((dispo1 * 100) / total, 'f', 2) + "%");
    QString b = QString("full stack" + QString::number((dispo * 100) / total, 'f', 2) + "%");
    QString c = QString("marketing" + QString::number((dispo2 * 100) / total, 'f', 2) + "%");

    QPieSeries *series = new QPieSeries();
    series->append(a, dispo1);
    series->append(b, dispo);
    series->append(c, dispo2);

    if (dispo1 != 0)
    {
        QPieSlice *slice = series->slices().at(0);
        slice->setLabelVisible();
        slice->setPen(QPen());
    }

    if (dispo != 0)
    {
        QPieSlice *slice1 = series->slices().at(1);
        slice1->setLabelVisible();
    }
    if (dispo2 != 0)
    {
        QPieSlice *slice = series->slices().at(0);
        slice->setLabelVisible();
        slice->setPen(QPen());
    }



    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("TYPE DE FORMATIONS : nombre de formations " + QString::number(total));

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1000, 500);
    chartView->show();
}



void MainWindow::on_pushButton_recherche_clicked()
{
    FORMATEURS F;

        int index = ui->comboBox_recherche->currentIndex();
        QString wh;
        QSqlQueryModel* model = new QSqlQueryModel();
        QString k = ui->lineEdit_recherche->text().trimmed(); // Trimmed to remove leading and trailing whitespace

        if (k.isEmpty()) {
            QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("champs vide"), QMessageBox::Cancel);
            return;
        }

        if (index == 0) {
            if (!F.idDisponible(k.toInt())) {
                QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("ID n'existe pas"), QMessageBox::Cancel);
                return;
            }
            wh = "id_formateur=" + k;
        } else if (index == 1) {
            wh = "nom='" + k + "'";
        } else if (index == 2) {
            wh = "specialite='" + k + "'";
        }
        if (F.rech(wh)) {
            QMessageBox::information(nullptr, QObject::tr("succes"), QObject::tr("Reherche validee"), QMessageBox::Cancel);
            model->setQuery("SELECT * FROM FORMATEURS WHERE " + wh);
            ui->tableView_formateurs->setModel(model);
        } else {
            QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("Recherche non validee"), QMessageBox::Cancel);
        }

}

void MainWindow::on_pushButton_recherche_2_clicked()
{
    FORMATIONS F1;

        int index = ui->comboBox_recherche_2->currentIndex();
        QString wh;
        QSqlQueryModel* model = new QSqlQueryModel();
        QString k = ui->lineEdit_recherche_2->text().trimmed(); // Trimmed to remove leading and trailing whitespace

        if (k.isEmpty()) {
            QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("champs vide"), QMessageBox::Cancel);
            return;
        }

        if (index == 0) {
            if (!F1.idDisponible(k.toInt())) {
                QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("ID n'existe pas"), QMessageBox::Cancel);
                return;
            }
            wh = "id_formation=" + k;
        } else if (index == 1) {
            wh = "typeformation='" + k + "'";
        } else if (index == 2) {
            wh = "id_formateur='" + k + "'";
        }
        if (F1.rech(wh)) {
            QMessageBox::information(nullptr, QObject::tr("succes"), QObject::tr("Reherche validee"), QMessageBox::Cancel);
            model->setQuery("SELECT * FROM FORMATIONS WHERE " + wh);
            ui->tableView_formations->setModel(model);
        } else {
            QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("Recherche non validee"), QMessageBox::Cancel);
        }
}

void MainWindow::on_pushButton_refresh_clicked()
{
    ui->tableView_formateurs->setModel(F.afficher());//refresh
}

void MainWindow::on_pushButton_refresh_2_clicked()
{
    ui->tableView_formations->setModel(F1.afficher());//refresh
}

void MainWindow::on_pushButton_tri_clicked()
{
    int index=ui->comboBox_tri->currentIndex();
           QString orderByClause;
           QSqlQueryModel* model=new QSqlQueryModel();
           if (index == 0) {
                       orderByClause = " ORDER BY id_formateur DESC";
                   } else if (index == 1) {
                       orderByClause = " ORDER BY  nom";
                   }

           if (F.tri(orderByClause)) {
               QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("Tri effectue \n""Click cancel to exit ."),QMessageBox::Cancel);
                model->setQuery("SELECT *  FROM FORMATEURS"+orderByClause);
               ui->tableView_formateurs->setModel(model);
           } else {
              QMessageBox::critical(nullptr,QObject::tr(" not ok"),QObject::tr("tri non effectue \n""Click cancel to exit ."),QMessageBox::Cancel);
           }
}

void MainWindow::on_pushButton_tri_2_clicked()
{
    int index=ui->comboBox_tri_2->currentIndex();
           QString orderByClause;
           QSqlQueryModel* model=new QSqlQueryModel();
           if (index == 0) {
                       orderByClause = " ORDER BY id_formation DESC";
                   } else if (index == 1) {
                       orderByClause = " ORDER BY nbrplace ASC";
                   } else if (index == 2) {
                       orderByClause = " ORDER BY id_formateur ASC";
                   }

           if (F1.tri(orderByClause)) {
               QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("Tri effectue \n""Click cancel to exit ."),QMessageBox::Cancel);
                model->setQuery("SELECT *  FROM FORMATIONS"+orderByClause);
               ui->tableView_formations->setModel(model);
           } else {
              QMessageBox::critical(nullptr,QObject::tr(" not ok"),QObject::tr("tri non effectue \n""Click cancel to exit ."),QMessageBox::Cancel);
           }
}
