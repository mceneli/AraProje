#include "resultwindow.h"
#include "ui_resultwindow.h"
#include "detailwindow.h"

ResultWindow::ResultWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResultWindow)
{
    ui->setupUi(this);
}

ResultWindow::ResultWindow(std::vector<std::string> &codeFileList, std::string &docType, int k, int w): ResultWindow()
{
    this->codeFileList = codeFileList;
    this->docType = docType;
    this->k = k;
    this->w = w;

    codes = docType == "C" ? getCodes(codeFileList, k, w) : getDocs(codeFileList, k, w);
    std::vector <CodePair> similarities = calculateSimilarities(codes);
    std::sort(similarities.begin(), similarities.end(),
              [] (const CodePair &lhs, const CodePair &rhs) { return lhs.sim1 > rhs.sim1; });

    fillTable(codes, similarities);
}

ResultWindow::~ResultWindow()
{
    delete ui;
}

void ResultWindow::resizeTable()
{
    ui->tableCodes->verticalHeader()->setVisible(false);

    ui->tableCodes->setColumnWidth(0, 70);
    ui->tableCodes->setColumnWidth(1, 325);
    ui->tableCodes->setColumnWidth(2, 82);
    ui->tableCodes->setColumnWidth(3, 325);
    ui->tableCodes->setColumnWidth(4, 82);
    ui->tableCodes->setColumnWidth(5, 0);
    ui->tableCodes->setColumnWidth(6, 0);
    ui->tableCodes->setColumnWidth(7, 0);

    this->setMaximumWidth(ui->tableCodes->width());
    this->setMinimumWidth(ui->tableCodes->width());

    ui->tableCodes->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

}

void ResultWindow::fillTable(std::vector <Code> &codes, std::vector <CodePair> &similarities)
{
    resizeTable();
    ui->tableCodes->setHorizontalHeaderLabels(QStringList()
                                              << "Sıra" << "1. Kod" << "Benzerlik" << "2. Kod" << "Benzerlik");

    QTableWidgetItem *tableItem = new QTableWidgetItem();
    tableItem->setTextAlignment(Qt::AlignCenter);
    tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);

    for (size_t i = 0; i < similarities.size(); ++i)
    {
        ui->tableCodes->insertRow(ui->tableCodes->rowCount());

        int x = similarities[i].x;
        int y = similarities[i].y;
        int sim1 = similarities[i].sim1;
        int sim2 = similarities[i].sim2;

        QTableWidgetItem *newitem = tableItem->clone();
        newitem->setText(QString::number(i+1));
        ui->tableCodes->setItem(i, 0, newitem);

        newitem = tableItem->clone();
        newitem->setText(QString::fromStdString(codes[x].fileName));
        ui->tableCodes->setItem(i, 1, newitem);

        newitem = tableItem->clone();
        newitem->setText("%" + QString::number(sim1));
        ui->tableCodes->setItem(i, 2, newitem);

        newitem = tableItem->clone();
        newitem->setText(QString::fromStdString(codes[y].fileName));
        ui->tableCodes->setItem(i, 3, newitem);

        newitem = tableItem->clone();
        newitem->setText("%" + QString::number(sim2));
        ui->tableCodes->setItem(i, 4, newitem);

        newitem = tableItem->clone();
        newitem->setText(QString::number(x));
        ui->tableCodes->setItem(i, 5, newitem);

        newitem = tableItem->clone();
        newitem->setText(QString::number(y));
        ui->tableCodes->setItem(i, 6, newitem);

        newitem = tableItem->clone();
        newitem->setText(QString::number(similarities[i].sameFingerprints));
        ui->tableCodes->setItem(i, 7, newitem);
    }
}

std::vector <CodePair> ResultWindow::calculateSimilarities(std::vector<Code> &codes)
{
    std::vector <CodePair> similarities;

    for (size_t i = 0; i < codes.size()-1; ++i)
    {
        for (size_t j = i+1; j < codes.size(); ++j)
        {
            int sameFingerprints = compareCodes(codes[i], codes[j]);
            size_t less, bigger;

            if (codes[i].numOfSelectedFingerPrints < codes[j].numOfSelectedFingerPrints)
                less = j, bigger = i;
            else
                less = i, bigger = j;

            similarities.emplace_back(bigger, less, sameFingerprints, 100 * sameFingerprints / codes[bigger].numOfSelectedFingerPrints,
                                      100 * sameFingerprints / codes[less].numOfSelectedFingerPrints);
        }
    }

    return similarities;
}

void ResultWindow::on_tableCodes_cellDoubleClicked(int row, int column)
{
    int x = ui->tableCodes->item(row, 5)->text().toInt();
    int y = ui->tableCodes->item(row, 6)->text().toInt();
    int matchedFP = ui->tableCodes->item(row, 7)->text().toInt();
    int sim1 = std::stoi(ui->tableCodes->item(row, 2)->text().toStdString().substr(1));
    int sim2 = std::stoi(ui->tableCodes->item(row, 4)->text().toStdString().substr(1));

    DetailWindow *window = new DetailWindow(codes[x], codes[y], docType, matchedFP, sim1, sim2, k);
    window->show();
}
