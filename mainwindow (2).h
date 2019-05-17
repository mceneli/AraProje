#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <string>
#include <unordered_map>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    std::vector <std::string> getCodeFileList() { return codeFileList; }
    int getK() { return k; }
    int getW() { return w; }

    ~MainWindow();

private slots:
    void on_pushDir_clicked();

    void on_pushStart_clicked();

    void on_checkTweaks_stateChanged(int arg1);

    void on_slider_k_valueChanged(int value);

    void on_slider_w_valueChanged(int value);

    void on_radio_Other_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    void fillTextBrowser(QString dir);
    void setTweaks();
    void initializeComboBox();
    void initializeExtensions();

    std::vector <std::string> codeFileList;
    std::unordered_map <std::string, std::vector QStringList> extensions;
    std::string currExtension;
    int k, w;
};

#endif // MAINWINDOW_H
