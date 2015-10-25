#ifndef NODEEXECUTOR_HPP_
#define NODEEXECUTOR_HPP_

#include <string>
#include <mesos/executor.hpp>
#include <nan.h>

using std::string;
using namespace mesos;

class NodeExecutor: public Executor {
public:
	NodeExecutor(v8::Object jsExecutor);

	virtual void registered(ExecutorDriver* driver, const ExecutorInfo& executorInfo, const FrameworkInfo& frameworkInfo, const SlaveInfo& slaveInfo);
	virtual void reregistered(ExecutorDriver* driver, const SlaveInfo& slaveInfo);
	virtual void disconnected(ExecutorDriver* driver);
	virtual void launchTask(ExecutorDriver* driver, const TaskInfo& task);
	virtual void killTask(ExecutorDriver* driver, const TaskID& taskId);
	virtual void frameworkMessage(ExecutorDriver* driver, const string& data);
	virtual void shutdown(ExecutorDriver* driver);
	virtual void error(ExecutorDriver* driver, const string& message);

private:
	v8::Object _jsExecutor;
};

#endif /* NODEEXECUTOR_HPP_ */
