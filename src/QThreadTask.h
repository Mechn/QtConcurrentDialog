#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QThreadTask.h"

#include "AsyncTaskExecutor.h"

#pragma execution_character_set("utf-8")

class QThreadTask : public QMainWindow
{
    Q_OBJECT

public:
    QThreadTask(QWidget *parent = nullptr);
    ~QThreadTask();

public:
    void test();

    int doSomething(int* a, double b);

private slots:
    void on_pushButton_clicked();


private:
    Ui::QThreadTaskClass ui;
};
