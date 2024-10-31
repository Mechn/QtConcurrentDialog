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
////![����һ������]
////��ԭ��ʾ���У�����������main��������
//std::function<void(int&)> spin = [](int& iteration) {
//    const int work = 1000 * 1000 * 40;
//    volatile int v = 0;
//    for (int j = 0; j < work; ++j)
//        ++v;
//
//    qDebug() << "iteration" << iteration << "in thread" << QThread::currentThreadId();
//    };
////![����һ������]
////!
//int main(int argc, char** argv)
//{
//
//    QApplication app(argc, argv);
//
//    const int iterations = 1000;
//
//    // ׼������
//    QVector<int> vector;
//    for (int i = 0; i < iterations; ++i)
//        vector.append(i);
//
//    // ��������������
//    QProgressDialog dialog;
//    //ϵͳ�����е������߳�����
//    dialog.setLabelText(QString::fromLocal8Bit("����ʹ�� %1 ���߳̽��д���...").arg(QThread::idealThreadCount()));
//
//    // QFutureWatcher���ṩ�й�QFuture����Ϣ��֪ͨ��
//    // QFuture�����ʾ�첽����Ľ����ʹ��Qt Concurrent����е�һ��api��ʼִ�м���
//    // QtConcurrent���ƿռ��ṩ�˸߼�api��ʹ������ʹ�����绥��������д�����ȴ��������ź����ȵͼ��߳�ԭ��Ϳ��Ա�д���̳߳���
//    // ʹ��setFuture()������ʼ�����ض���QFuture��
//    // ʹ��future()��������setFuture()���õ�future
//    QFutureWatcher<void> futureWatcher;
//    QObject::connect(&futureWatcher, &QFutureWatcher<void>::finished, &dialog, &QProgressDialog::reset);
//    QObject::connect(&dialog, &QProgressDialog::canceled, &futureWatcher, &QFutureWatcher<void>::cancel);
//    QObject::connect(&futureWatcher, &QFutureWatcher<void>::progressRangeChanged, &dialog, &QProgressDialog::setRange);
//    QObject::connect(&futureWatcher, &QFutureWatcher<void>::progressValueChanged, &dialog, &QProgressDialog::setValue);
//
//
//    // ��ʼִ�к���
//    //QtConcurrent::map����˳��Ϊ����1��ÿ�������һ�β���2������
//    //��ʼ�۲������future
//    futureWatcher.setFuture(QtConcurrent::map(vector, spin));
//
//    // ��ʾ�������Ի��򲢿�ʼִ����ѭ��
//    //ִ����Ϻ�������Ի����رգ�����ͨ��dialog.setAutoClose(false)���Զ��ر�;
//    dialog.exec();
//
//    //�ȴ��첽������ɣ�����cancel�������㣩��
//    futureWatcher.waitForFinished();
//
//    // ��ѯfutureֵ������û��Ƿ������ж���ִ�й���.
//    qDebug() << "Canceled?" << futureWatcher.future().isCanceled();
//}






