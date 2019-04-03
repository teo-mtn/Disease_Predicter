#ifndef MAFENETRE_H
#define MAFENETRE_H

#include <QWidget>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QTableWidget>

#include <set>
#include "charger_csv.h"

class MaFenetre : public QMainWindow
{
    Q_OBJECT // Macro OBLIGATOIRE

public slots :
    void setQuitter();
    void prediction();


public :
    MaFenetre(QWidget *parent = 0);

private :
    QLabel *title, *feverLabel, *painLabel, *coughLabel, *tabLabel, *result;
    QPushButton *quit, *predict;
    QComboBox *fever;
    QComboBox *pain;
    QComboBox *cough;
    CVString m_vet;
    CMatString m_mat;
    QTableWidget *tabBD;

    std::map<std::string, double> m_freqMaladie;
    std::set<std::string> m_valeursMaladies;
};

#endif // MAFENETRE_H
