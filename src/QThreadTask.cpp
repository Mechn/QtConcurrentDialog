#include "QThreadTask.h"
#include "AsyncTaskExecutor.h"

#include <QProgressBar>
#include <QVBoxLayout>
#include <QTimer>
#include <QVector>


//Q_DECLARE_METATYPE(MyStruct*)

QThreadTask::QThreadTask(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

QThreadTask::~QThreadTask()
{}

void square(int& x)
{
    QThread::sleep(2);
    x*=x;
    qDebug() << x<< QThread::currentThreadId();
}

void QThreadTask::test()
{
    AsyncTaskExecutor* executor = new AsyncTaskExecutor(this);
    // �����ź��Դ�����ɻ����
    connect(executor, &AsyncTaskExecutor::done, [](const QVariant& result) {
        qDebug() << "������ɣ�����ֵ:" << result.toInt();
        });
    connect(executor, &AsyncTaskExecutor::error, [](const QString& msg) {
        qDebug() << "�����쳣��" << msg;
        });

    // run����
    //int a = 1;
    //executor->run(this, &QThreadTask::doSomething, &a, 2.1);
    //qDebug() << "a=" << a;

    // map����
    QVector<int> seq;
    for (int i = 0; i < 100; ++i)
    {
        seq.append(i);
    }

    executor->map(seq, square);

    for (auto& p : seq)
    {
        qDebug() << p;
    }

}

void QThreadTask::on_pushButton_clicked()
{
    test();
}

int QThreadTask::doSomething(int* a, double b)
{
    QThread::sleep(5);
    (*a)++;
    return *a;
}
