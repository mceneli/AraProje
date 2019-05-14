#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "resultwindow.h"

#include <QFileDialog>
#include <QIntValidator>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setTweaks();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushDir_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Klasör Seç"), "/home",
                                                    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (dir.size() > 0)
        ui->pushDir->setText(dir);

    fillTextBrowser(dir);
}

void MainWindow::fillTextBrowser(QString dir)
{
    codeFileList.clear();
    ui->textBrowser->setText("");

    QDir directory(dir);
    QStringList codeFiles = directory.entryList(QStringList() << "*.c" << "*.C", QDir::Files);

    for (auto filename: codeFiles)
    {
        codeFileList.push_back("'" + dir.toStdString() + "/" + filename.toStdString() + "'");
        ui->textBrowser->append(filename);
    }
}

void MainWindow::on_pushStart_clicked()
{
    if (codeFileList.size() > 0)
    {
        k = ui->slider_k->value();
        w = ui->slider_w->value();

        ResultWindow *window = new ResultWindow(codeFileList, k, w);
        window->show();
    }
}

void MainWindow::setTweaks()
{
    /*ui->text_k->setReadOnly(true);
    ui->text_w->setReadOnly(true);*/

    ui->text_k->setText(QString::number(ui->slider_k->value()));
    ui->text_w->setText(QString::number(ui->slider_w->value()));

    ui->text_k->setValidator( new QIntValidator(5, 30, this) );
    ui->text_w->setValidator( new QIntValidator(3, 30, this) );

    ui->label_k->setEnabled(false);
    ui->label_w->setEnabled(false);
    ui->text_k->setEnabled(false);
    ui->text_w->setEnabled(false);
    ui->slider_k->setEnabled(false);
    ui->slider_w->setEnabled(false);
}

void MainWindow::on_checkTweaks_stateChanged(int arg1)
{
    ui->label_k->setEnabled(arg1);
    ui->label_w->setEnabled(arg1);
    ui->text_k->setEnabled(arg1);
    ui->text_w->setEnabled(arg1);
    ui->slider_k->setEnabled(arg1);
    ui->slider_w->setEnabled(arg1);

    if (arg1 == 0)
    {
        ui->slider_k->setValue(20);
        ui->slider_w->setValue(5);
        ui->text_k->setText(QString::number(ui->slider_k->value()));
        ui->text_w->setText(QString::number(ui->slider_w->value()));
    }
}

void MainWindow::on_slider_k_valueChanged(int value)
{
    ui->text_k->setText(QString::number(value));
}

void MainWindow::on_slider_w_valueChanged(int value)
{
    ui->text_w->setText(QString::number(value));
}
