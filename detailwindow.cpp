#include "detailwindow.h"
#include "ui_detailwindow.h"

#include <QDesktopServices>

DetailWindow::DetailWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DetailWindow)
{
    ui->setupUi(this);
}

DetailWindow::DetailWindow(const Code &code1, const Code &code2, int matchedFP, int sim1, int sim2, int k): DetailWindow()
{
    this->code1 = code1;
    this->code2 = code2;
    this->matchedFP = matchedFP;
    this->sim1 = sim1;
    this->sim2 = sim2;
    this->k = k;

    fillDetails();
}

DetailWindow::~DetailWindow()
{
    delete ui;
}

void DetailWindow::fillDetails()
{
    this->setWindowTitle(QString::fromStdString(code1.fileName) + " vs " + QString::fromStdString(code2.fileName));
    ui->code1_label->setText(QString::fromStdString(code1.fileName));
    ui->code2_label->setText(QString::fromStdString(code2.fileName));

    ui->simBar1->setValue(sim1);
    ui->simBar2->setValue(sim2);

    ui->code1_simple->setPlainText(QString::fromStdString(code1.pureCode));
    ui->code2_simple->setPlainText(QString::fromStdString(code2.pureCode));

    ui->code1_skeleton->setPlainText(QString::fromStdString(code1.skeleton));
    ui->code2_skeleton->setPlainText(QString::fromStdString(code2.skeleton));

    ui->code1_totalFP->setText(QString::number(code1.skeleton.size()-k+1));
    ui->code1_selectedFP->setText(QString::number(code1.numOfSelectedFingerPrints));
    ui->code1_matchedFP->setText(QString::number(matchedFP));

    ui->code2_totalFP->setText(QString::number(code2.skeleton.size()-k+1));
    ui->code2_selectedFP->setText(QString::number(code2.numOfSelectedFingerPrints));
    ui->code2_matchedFP->setText(QString::number(matchedFP));
}

void DetailWindow::on_code1_push_clicked()
{
    QDesktopServices::openUrl(QUrl("file://" + QString::fromStdString(code1.filePath.substr(1, code1.filePath.size()-2))));
}

void DetailWindow::on_code2_push_clicked()
{
    QDesktopServices::openUrl(QUrl("file://" + QString::fromStdString(code2.filePath.substr(1, code2.filePath.size()-2))));
}
