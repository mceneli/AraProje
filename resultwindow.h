#ifndef RESULTWINDOW_H
#define RESULTWINDOW_H

#include "winnowing.h"
#include <QTableWidget>
#include <QWidget>

namespace Ui {
class ResultWindow;
}

struct CodePair
{
    int x, y, sameFingerprints, sim1, sim2;
    CodePair(int x, int y, int sameFingerprints, int sim1, int sim2): x(x), y(y),
             sameFingerprints(sameFingerprints), sim1(sim1), sim2(sim2) {}
};

class ResultWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ResultWindow(QWidget *parent = nullptr);

    explicit ResultWindow(std::vector <std::string> &codeFileList, std::string &docType, int k, int w);

    ~ResultWindow();

private slots:
    void on_tableCodes_cellDoubleClicked(int row, int column);

private:
    Ui::ResultWindow *ui;
    void resizeTable();
    void fillTable(std::vector <Code> &codes, std::vector <CodePair> &similarities);
    std::vector <CodePair> calculateSimilarities(std::vector <Code> &codes);

    std::vector <Code> codes;
    std::vector <std::string> codeFileList;
    std::string docType;
    int k, w;
};

#endif // RESULTWINDOW_H
