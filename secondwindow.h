#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QDialog>
#include <QTableView>
#include <QStandardItemModel>
#include "mainwindow.h"
#include "fileworker.h"

namespace Ui {
class SecondWindow;
}

class SecondWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = nullptr);
    ~SecondWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    // построение таблицы
    void buidTable();

    Ui::SecondWindow *ui;

    QStandardItemModel* model;  // модель "таблца"

    int page; // номер страницы для пагинации

    FILE *f_logs; // файл кэш

    QModelIndex index;
};

#endif // SECONDWINDOW_H
