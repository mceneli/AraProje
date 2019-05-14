#ifndef DETAILWINDOW_H
#define DETAILWINDOW_H

#include <QWidget>
#include "resultwindow.h"

namespace Ui {
class DetailWindow;
}

class DetailWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DetailWindow(QWidget *parent = nullptr);

    explicit DetailWindow(const Code &code1, const Code &code2, int matchedFP, int sim1, int sim2, int k);

    ~DetailWindow();

private slots:

    void on_code1_push_clicked();

    void on_code2_push_clicked();

private:
    Ui::DetailWindow *ui;
    void fillDetails();

    Code code1, code2;
    int matchedFP, sim1, sim2, k;
};

#endif // DETAILWINDOW_H
