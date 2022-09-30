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

private:
    void SetStr();
    Ui::TableOfValues *ui;
    QStandardItemModel *model;
    char str[50];
    Deque *head, *tail;
};

#endif // TABLEOFVALUES_H
