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
    // 连接信号以处理完成或错误
    connect(executor, &AsyncTaskExecutor::done, [](const QVariant& result) {
        qDebug() << "任务完成，返回值:" << result.toInt();
        });
    connect(executor, &AsyncTaskExecutor::error, [](const QString& msg) {
        qDebug() << "任务异常：" << msg;
        });

    // run任务
    //int a = 1;
    //executor->run(this, &QThreadTask::doSomething, &a, 2.1);
    //qDebug() << "a=" << a;

    // map任务
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
