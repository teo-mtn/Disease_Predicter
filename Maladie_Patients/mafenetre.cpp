#include "mafenetre.h"
#include "charger_csv.h"

MaFenetre::MaFenetre(QWidget *parent) : QMainWindow(parent)
{
    read_csv (m_mat, m_vet, "/amuhome/m17015514/Bureau/data.csv");

    setFixedSize(800,600);
    title = new QLabel ("Logiciel de prédiction des maladies", this);
    title->setFont(QFont("Garamond",24, true, QFont::Bold));
    title->setGeometry(100, 25, 600, 50);

    feverLabel = new QLabel("Fever", this);
    feverLabel->setFont(QFont("Garamond",10, true));
    feverLabel->setGeometry(100, 75, 100, 75);

    painLabel = new QLabel("Pain", this);
    painLabel->setFont(QFont("Garamond",10, true));
    painLabel->setGeometry(225, 75, 100, 75);

    coughLabel = new QLabel("Cough", this);
    coughLabel->setFont(QFont("Garamond",10, true));
    coughLabel->setGeometry(350, 75, 100, 75);

    tabLabel = new QLabel("Database's Table", this);
    tabLabel->setFont(QFont("Garamond", 10, true));
    tabLabel->setGeometry(20, 250, 100, 75);

    quit = new QPushButton("Quit", this);
    quit->setGeometry(700,550,100,50);

    predict = new QPushButton("Predict", this);
    predict->setGeometry(500, 125, 100, 50);

    fever = new QComboBox(this);
    fever-> setGeometry(100,125,100,50);
    fever->addItem("NULL");

    pain = new QComboBox(this);
    pain-> setGeometry(225,125,100,50);
    pain->addItem("NULL");

    cough = new QComboBox(this);
    cough-> setGeometry(350,125,100,50);
    cough->addItem("NULL");

    tabBD = new QTableWidget;
    tabBD->setGeometry(20, 275, 600, 300);

    for (unsigned int i = 0; i <= m_vet[i].size()-1; ++i){
        if (fever->findText(QString::fromStdString(m_mat[i][0])) == -1)
            fever->addItem(QString::fromStdString(m_mat[i][0]));
        if (pain->findText(QString::fromStdString(m_mat[i][1])) == -1)
            pain->addItem(QString::fromStdString(m_mat[i][1]));
        if (cough->findText(QString::fromStdString(m_mat[i][2])) == -1)
            cough->addItem(QString::fromStdString(m_mat[i][2]));
    }


    for (unsigned int j = 0; j<= m_vet[j].size()-1; ++j) {
        tabBD->insertColumn(j);
        for (unsigned int k = 0; k <= m_mat[j].size()-1; ++k) {
            tabBD->insertRow(k);
            tabBD->setItem(k,j, new QTableWidgetItem(QString::fromStdString(m_mat[j][k])));
        }
    }

    connect(quit, SIGNAL(clicked()),
            this, SLOT(setQuitter()));
}

void MaFenetre::setQuitter()
{
    exit(0);
}

