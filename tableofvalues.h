#ifndef TABLEOFVALUES_H
#define TABLEOFVALUES_H

#include <QDialog>
#include "parse_str.h"
#include "calculate.h"
#include "deque.h"
#include "stack.h"
#include <QTableView>
#include <QStandardItemModel>
#include <QMessageBox>
#include <iostream>
namespace Ui {
class TableOfValues;
}

class TableOfValues : public QDialog
{
    Q_OBJECT

public:
    explicit TableOfValues(QWidget *parent = nullptr);
    ~TableOfValues();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

private:
    void calculateTable(int count, bool options);
    void clearWindow();
    void SetAtributes();
    Ui::TableOfValues *ui;
    QStandardItemModel *model;
    char str[50];
    bool ok_lg = false, ok_rg = false, ok_count = false, radioButtonChecked_1 = false, radioButtonChecked_2 = false;
    Deque *head, *tail;
    double xmin = -10.0, xmax = 10.0;
    int count = 20;
};

#endif // TABLEOFVALUES_H
