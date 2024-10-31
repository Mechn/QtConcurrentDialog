#include "QThreadTask.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QThreadTask w;
    w.show();
    return a.exec();
}


//
//#include <QtWidgets>
//#include <QtConcurrent/QtConcurrent>
//
//#include <functional>
//#include <iostream>
//
//using namespace QtConcurrent;
//
////![定义一个函数]
////是原版示例中，函数定义在main函数里面
//std::function<void(int&)> spin = [](int& iteration) {
//    const int work = 1000 * 1000 * 40;
//    volatile int v = 0;
//    for (int j = 0; j < work; ++j)
//        ++v;
//
//    qDebug() << "iteration" << iteration << "in thread" << QThread::currentThreadId();
//    };
////![定义一个函数]
////!
//int main(int argc, char** argv)
//{
//
//    QApplication app(argc, argv);
//
//    const int iterations = 1000;
//
//    // 准备数据
//    QVector<int> vector;
//    for (int i = 0; i < iterations; ++i)
//        vector.append(i);
//
//    // 创建进度条窗口
//    QProgressDialog dialog;
//    //系统上运行的理想线程数。
//    dialog.setLabelText(QString::fromLocal8Bit("正在使用 %1 个线程进行处理...").arg(QThread::idealThreadCount()));
//
//    // QFutureWatcher：提供有关QFuture的信息和通知。
//    // QFuture：类表示异步计算的结果。使用Qt Concurrent框架中的一个api开始执行计算
//    // QtConcurrent名称空间提供了高级api，使得无需使用诸如互斥锁、读写锁、等待条件或信号量等低级线程原语就可以编写多线程程序。
//    // 使用setFuture()函数开始监视特定的QFuture。
//    // 使用future()函数返回setFuture()设置的future
//    QFutureWatcher<void> futureWatcher;
//    QObject::connect(&futureWatcher, &QFutureWatcher<void>::finished, &dialog, &QProgressDialog::reset);
//    QObject::connect(&dialog, &QProgressDialog::canceled, &futureWatcher, &QFutureWatcher<void>::cancel);
//    QObject::connect(&futureWatcher, &QFutureWatcher<void>::progressRangeChanged, &dialog, &QProgressDialog::setRange);
//    QObject::connect(&futureWatcher, &QFutureWatcher<void>::progressValueChanged, &dialog, &QProgressDialog::setValue);
//
//
//    // 开始执行函数
//    //QtConcurrent::map：按顺序为参数1的每个项，调用一次参数2函数。
//    //开始观察给定的future
//    futureWatcher.setFuture(QtConcurrent::map(vector, spin));
//
//    // 显示进度条对话框并开始执行主循环
//    //执行完毕后进度条对话框会关闭，可以通过dialog.setAutoClose(false)不自动关闭;
//    dialog.exec();
//
//    //等待异步计算完成（包括cancel（）计算）。
//    futureWatcher.waitForFinished();
//
//    // 查询future值，检查用户是否主动中断了执行过程.
//    qDebug() << "Canceled?" << futureWatcher.future().isCanceled();
//}






