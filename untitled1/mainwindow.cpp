#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QTextStream>
#include <QString>
#include<QDir>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textBrowser->setText(extraxt_text());

}
QString MainWindow::extraxt_text()
{
    QDir workingDir = QDir::current();
    QString path = workingDir.absolutePath();

    QFile file(path+"/../liste_de_course.txt");
       if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
           return path;

       QTextStream in(&file);
       QString content = in.readAll();
       QStringList lines = content.split("\n");
       QString numbers;
       QString current_number;

        foreach (QString line, lines)
        {
            for (int i = 0; i < line.size(); i++)
            {

                if (line[i].isDigit())
                {
                    current_number += line[i];
                }
                else if (!current_number.isEmpty())
                {
                    int value = current_number.toInt();
                    if (value >= 0 && value <= 255)
                    {



                        numbers += QString(QChar::fromLatin1(value));
                        current_number.clear();
                        break;
                    }
                    current_number.clear();
                }

            }
        }


       return numbers;

}

MainWindow::~MainWindow()
{
    delete ui;
}

