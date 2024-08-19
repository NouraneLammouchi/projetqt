#ifndef FORMATIONS_H
#define FORMATIONS_H


#include <QDialog>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMainWindow>
#include <QMainWindow>
#include <QMainWindow>
#include <QFileDialog>
#include <QPixmap>
#include <QSqlQuery>
#include <QDateTime>
#include <QFile>
#include <QDebug>
class FORMATIONS
{
    public:
        FORMATIONS();
        FORMATIONS(int,QString,QDate,QDate,QString,int,QString,int);

//getters
        int getid_formation();
        QString gettitre();
        QDate getdatedebut();
        QDate getdatefin();
        QString getduree();
        int getnbrplace();
        QString gettypeformation();
        int getid_formateur();


        void setid_formation(int);
        void settitre(QString);
        void setdatedebut(QDate);
        void setdatefin(QDate);
        void setduree(QString );
        void setnbrplace(int);
        void settypeformation(QString );
        void setid_formateur(int);


        bool ajouter();
        QSqlQueryModel * afficher();
        bool supprimer(int);
        bool modifier(QString);
        bool checkIfIdExists(QString);


        QSqlQueryModel *rechercher(QString);
        QSqlQueryModel *trier(QString);
        QSqlQueryModel* selectformationById(int id_formation);

private:
        int id_formation;
        QString titre;
        QDate datedebut;
        QDate datefin;
        QString duree;
        int nbrplace;
        QString typeformation;
        int id_formateur;



};
#endif // FORMATIONS_H
