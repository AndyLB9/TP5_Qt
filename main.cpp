#include "widget.h"
#include <QSqlError>
#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtDebug>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QTableView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("localhost");
    db.setDatabaseName("TP5");
    db.setUserName("etudiant");
    db.setPassword("Passciel2");
    db.setPort(3306);             // Le port par défaut de MySQL est 3306

    if (db.open()) {
        qDebug() << "Vous êtes maintenant connecté à" << db.hostName();

        QSqlTableModel *model = new QSqlTableModel(&w);
        model->setTable("jeu");  // Nom de la table qu'on veut afficher
        model->select();         // Charger les données de la table

        // Créer un QTableView pour afficher les données
        QTableView *view = new QTableView();
        view->setModel(model);  // Lier le modèle au view
        view->resize(600, 400); // Définir la taille du tableau
        view->show();           // Afficher le tableau dans la fenêtre

        qDebug() << "Requête OK !";
    } else {
        qDebug() << "La connexion a échoué," << db.lastError().text();
    }

    w.show();
    return a.exec();
}
