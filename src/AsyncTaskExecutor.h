#pragma once
#include <QThread>
#include <QProgressBar>
#include <QProgressDialog>
#include <QFuture>
#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrent>

#include <iostream>
#include <functional>
#include <utility>

enum TaskType
{
	TASK_Run,
	TASK_Map,
	TASK_Reduce,
};


class AsyncTaskExecutor : public QWidget
{
	Q_OBJECT
public:
	explicit AsyncTaskExecutor(QWidget* parent=nullptr);
	~AsyncTaskExecutor();

	// 运行任意函数
	template<typename ReturnType, typename ClassType, typename... Args>
	void run(ClassType* obj, ReturnType(ClassType::* func)(Args... args), Args&&...args);

	// 对容器中元素执行指定映射
    template<typename Container, typename Functor_,
        typename std::enable_if<!std::is_same<Functor_, void(int)>::value, int>::type = 0>
    void map(Container& container, Functor_ func);


signals:
	void done(const QVariant& result);
	void error(const QString& message);

private slots:
	void onTaskFinished();
	void onTaskCanceled();

private:
	QProgressDialog* dialog;
	QFutureWatcher<QVariant>* futureWatcher;
    QFutureWatcher<void>* fw;
};

template<typename ReturnType, typename ClassType, typename... Args>
void AsyncTaskExecutor::run(ClassType* obj, ReturnType(ClassType::* func)(Args...), Args&&... args)
{
    auto future = QtConcurrent::run([=]() -> QVariant {
        try {
            ReturnType result = (obj->*func)(args...);
            return QVariant::fromValue(result);
        }
        catch (const std::exception& e) {
            emit error(QString::fromStdString(e.what()));
            return QVariant();
        }
        });

    futureWatcher->setFuture(future);

	dialog->exec();

	futureWatcher->waitForFinished();
   
}

// 对容器中元素执行指定映射
template<typename Container, typename Functor_,
    typename std::enable_if<!std::is_same<Functor_, void(int)>::value, int>::type>
void AsyncTaskExecutor::map(Container& container, Functor_ func)
{
    auto future = QtConcurrent::map(container, func);
    fw->setFuture(future);

    dialog->exec();

    fw->waitForFinished();
}

