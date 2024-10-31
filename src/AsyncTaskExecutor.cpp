#include "AsyncTaskExecutor.h"

AsyncTaskExecutor::AsyncTaskExecutor(QWidget* parent)
    : QWidget(parent)
    , dialog(new QProgressDialog(parent))
    , futureWatcher(new QFutureWatcher<QVariant>(this))
    , fw(new QFutureWatcher<void>(this))
{
    dialog->resize(300, 80);

    QObject::connect(futureWatcher, &QFutureWatcher<QVariant>::finished, this, &AsyncTaskExecutor::onTaskFinished);
    QObject::connect(dialog, &QProgressDialog::canceled, futureWatcher, &QFutureWatcher<void>::cancel);
    QObject::connect(futureWatcher, &QFutureWatcher<QVariant>::progressRangeChanged, dialog, &QProgressDialog::setRange);
    QObject::connect(futureWatcher, &QFutureWatcher<QVariant>::progressValueChanged, dialog, &QProgressDialog::setValue);

    QObject::connect(fw, &QFutureWatcher<QVariant>::finished, this, &AsyncTaskExecutor::onTaskFinished);
    QObject::connect(dialog, &QProgressDialog::canceled, fw, &QFutureWatcher<void>::cancel);
    QObject::connect(fw, &QFutureWatcher<QVariant>::progressRangeChanged, dialog, &QProgressDialog::setRange);
    QObject::connect(fw, &QFutureWatcher<QVariant>::progressValueChanged, dialog, &QProgressDialog::setValue);
}

AsyncTaskExecutor::~AsyncTaskExecutor()
{
    
}



void AsyncTaskExecutor::onTaskFinished()
{
    //QVariant result = futureWatcher->result();
    //emit done(result);

    if (dialog) {
        dialog->deleteLater();
        dialog = nullptr;
    }
}

void AsyncTaskExecutor::onTaskCanceled()
{
    if (dialog) {
        dialog->deleteLater();
        dialog = nullptr;
    }
}