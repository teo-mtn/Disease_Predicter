#include <QMessageBox>
#include "mafenetre.h"
#include "charger_csv.h"

MaFenetre::MaFenetre(QWidget *parent) : QMainWindow(parent)
{
    read_csv (m_mat, m_vet, "/amuhome/m17015514/build-Maladie_Patients-Desktop_Qt_5_12_0_GCC_64bit-Debug.2/data.csv");

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
    tabLabel->setGeometry(20, 225, 100, 75);

    result = new QLabel(this);
    result->setFont(QFont("Garamond", 10, true));
    result->setVisible(false);
    result->setGeometry(250, 200, 200, 200);

    quit = new QPushButton("Quit", this);
    quit->setGeometry(700,550,100,50);

    predict = new QPushButton("Predict", this);
    predict->setGeometry(500, 125, 100, 50);

    connect(quit, SIGNAL(clicked()), this, SLOT(setQuitter()));
    connect(predict, SIGNAL(clicked()), this, SLOT(prediction()));

    fever = new QComboBox(this);
    fever-> setGeometry(100,125,100,50);
    fever->addItem("NULL");

    pain = new QComboBox(this);
    pain-> setGeometry(225,125,100,50);
    pain->addItem("NULL");

    cough = new QComboBox(this);
    cough-> setGeometry(350,125,100,50);
    cough->addItem("NULL");

    tabBD = new QTableWidget(m_mat.size(), m_mat[0].size(), this);
    tabBD->setGeometry(20, 275, 450, 300);

    for (unsigned int i = 0; i < m_mat.size(); ++i){
        if (fever->findText(QString::fromStdString(m_mat[i][0])) == -1)
            fever->addItem(QString::fromStdString(m_mat[i][0]));
        if (pain->findText(QString::fromStdString(m_mat[i][1])) == -1)
            pain->addItem(QString::fromStdString(m_mat[i][1]));
        if (cough->findText(QString::fromStdString(m_mat[i][2])) == -1)
            cough->addItem(QString::fromStdString(m_mat[i][2]));
    }

    std::set<std::string> valeursDouleur;

    for (unsigned i=0; i < m_mat.size(); ++i)
       {
          tabBD->setItem(i, 0, new QTableWidgetItem(m_mat[i][0].c_str()));

           tabBD->setItem(i, 1, new QTableWidgetItem(m_mat[i][1].c_str()));
           valeursDouleur.insert(m_mat[i][1]);

           tabBD->setItem(i, 2, new QTableWidgetItem(m_mat[i][2].c_str()));

           tabBD->setItem(i, 3, new QTableWidgetItem(m_mat[i][3].c_str()));
           m_freqMaladie[m_mat[i][3]] += 1;
           m_valeursMaladies.insert(m_mat[i][3]);
       }

    for (const std::string& maladie : m_valeursMaladies)
        m_freqMaladie[maladie] /= m_mat.size();

}

void MaFenetre::setQuitter()
{
    exit(0);
}

void MaFenetre::prediction()
{
    string maladieResult;
        double score = 0;
        cout << "Score: " << score << endl;
        for(const string& maladie : m_valeursMaladies)
        {
            double conf1=0.0, conf2=0.0, conf3=0.0;

            for(int i=0; i < m_mat.size(); ++i)
            {
                if(m_mat[i][3] == maladie)
                {
                    if(m_mat[i][0]==fever->currentText().toStdString())
                        conf1 += 1.0;

                    if(m_mat[i][1]==pain->currentText().toStdString())
                        conf2 += 1.0;

                    if(m_mat[i][2]==cough->currentText().toStdString())
                        conf3 += 1.0;
                }
            }

            double freq = m_freqMaladie[maladie] * m_mat.size();

            if (fever->currentText().toStdString() == "NULL")
                conf1 = 1;
            else
                conf1 /= freq;

            if (pain->currentText().toStdString() == "NULL")
                conf2 = 1;
            else
                conf2 /= freq;

            if (cough->currentText().toStdString() == "NULL")
                conf3 = 1;
            else
                conf3 /= freq;

            if (fever->currentText().toStdString() == "NULL" && fever->currentText().toStdString() == "NULL" && cough->currentText().toStdString() == "NULL")
            {
                maladieResult = "Impossible de trouver la maladie";
                break;
            }

            if(m_freqMaladie[maladie] * conf1 * conf2 * conf3 > score)
            {
                maladieResult = maladie;
                score = m_freqMaladie[maladie] * conf1 * conf2 * conf3;
            }
        }

        result->setText(maladieResult.c_str());
        cout << result << endl;
        result->adjustSize();
        result->update();
        result->setVisible(true);

        QMessageBox msgbox;
           msgbox.setText(maladieResult.c_str());
           msgbox.exec();
}

