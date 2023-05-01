#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDir>

bool NO_OPTI = 1;
bool OPTI = 0;


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

//       bool choice = OPTI;

//       if(choice == OPTI)
//       {


           foreach (QString line, lines) {
               bool found_number = false;
               QString number_str;
               for (auto it = line.begin(); it != line.end(); ++it) {
                   if (it->isDigit()) {
                       number_str.append(*it);
                       found_number = true;
                   } else if (found_number) {
                       uint8_t value = number_str.toUInt();
                       numbers += QChar(value);
                       number_str.clear();
                       found_number = false;
                       break;
                   }
               }
           }
//       }
//       else{

//           foreach (QString line, lines)
//           {
//               for (uint8_t i = 0; i < line.size(); i++)
//               {

//                   if (line[i].isDigit())
//                   {
//                       current_number += line[i];
//                   }
//                   else if (!current_number.isEmpty())
//                   {
//                       uint8_t value = current_number.toInt();
//                        numbers += QString(QChar::fromLatin1(value));
//                           current_number.clear();
//                           break;
//                       current_number.clear();
//                   }

//               }
//           }

//       }




       return numbers;

}

MainWindow::~MainWindow()
{
    delete ui;
}

