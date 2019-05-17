#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "resultwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setTweaks();
    initializeComboBox();
    initializeExtensions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushDir_clicked()
{
    currExtension = ui->radio_C->isChecked() ? "C" : ui->radio_TXT->isChecked() ?
                                                   "TXT" : ui->comboBox->currentText().toStdString();

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
    QStringList codeFiles = directory.entryList(extensions[currExtension], QDir::Files);

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

        ResultWindow *window = new ResultWindow(codeFileList, currExtension, k, w);
        window->show();
    }
}

void MainWindow::setTweaks()
{
    ui->text_k->setReadOnly(true);
    ui->text_w->setReadOnly(true);

    ui->text_k->setText(QString::number(ui->slider_k->value()));
    ui->text_w->setText(QString::number(ui->slider_w->value()));

    ui->label_k->setEnabled(false);
    ui->label_w->setEnabled(false);
    ui->text_k->setEnabled(false);
    ui->text_w->setEnabled(false);
    ui->slider_k->setEnabled(false);
    ui->slider_w->setEnabled(false);
}

void MainWindow::initializeComboBox()
{
    ui->comboBox->addItem("Python");
    ui->comboBox->addItem("C++");
    ui->comboBox->addItem("Java");
    ui->comboBox->addItem("C#");
    ui->comboBox->addItem("JavaScript");
    ui->comboBox->addItem("Pascal");
    ui->comboBox->addItem("Go");
    ui->comboBox->addItem("Assembly");
    ui->comboBox->addItem("MatLAB/Octave");
    ui->comboBox->addItem("Perl");
    ui->comboBox->addItem("Haskell");
    ui->comboBox->addItem("Lisp");
    ui->comboBox->addItem("FORTRAN");
    ui->comboBox->addItem("PHP");
    ui->comboBox->addItem("HTML");
    ui->comboBox->addItem("CSS");
    ui->comboBox->addItem("XML");
    ui->comboBox->addItem("Diğer *");
}

void MainWindow::initializeExtensions()
{
    currExtension = "C";

    extensions = { {"C", {"*.c", "*.h"}},
                   {"TXT", {"*.txt"}},
                   {"Python", {"*.py"}},
                   {"C++", {"*.cpp", "*.hpp", "*.c", "*.h"}},
                   {"Java", {"*.java"}},
                   {"C#", {"*.cs"}},
                   {"JavaScript", {"*.js"}},
                   {"Pascal", {"*.pas"}},
                   {"Go", {"*.go"}},
                   {"Assembly", {"*.asm", "*.s", "*.masm", "*.nasm"}},
                   {"MatLAB/Octave", {"*.m", "*.mat"}},
                   {"Perl", {"*.pl"}},
                   {"Haskell", {"*.hs", "*.lhs"}},
                   {"Lisp", {"*.lisp", "*.cl"}},
                   {"FORTRAN", {"*.f", "*.for", "*.f90", "*.f95", "*.f03", "*.f15"}},
                   {"PHP", {"*.php"}},
                   {"HTML", {"*.html"}},
                   {"CSS", {"*.css"}},
                   {"XML", {"*.xml"}},
                   {"Diğer *", {"*.*"}} };
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
        ui->slider_k->setValue(25);
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

void MainWindow::on_radio_Other_toggled(bool checked)
{
    ui->comboBox->setEnabled(checked);
}
