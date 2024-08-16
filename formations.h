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
        int getID_formation();
        QString gettitre();
        QDate getdatedebut();
        QDate getdatefin();
        QString getduree();
        int getnbrplace();
        QString gettypeformation();
        int getID_formateur();


        void setID_formation(int);
        void settitre(QString);
        void setdatedebut(QDate);
        void setdatefin(QDate);
        void setduree(QString );
        void setnbrplace(int);
        void settypeformation(QString );
        void setID_formateur(int);


        bool ajouter();
        QSqlQueryModel * afficher();
        bool supprimer(QString);
        bool modifier(QString);
        bool checkIfIdExists(QString);


        QSqlQueryModel *rechercher(QString);
        QSqlQueryModel *trier(QString);

private:
        int ID_formation;
        QString titre;
        QDate datedebut;
        QDate datefin;
        QString duree;
        int nbrplace;
        QString typeformation;
        int ID_formateur;



};
#endif // FORMATIONS_H
