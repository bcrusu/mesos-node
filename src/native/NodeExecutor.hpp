#ifndef NODEEXECUTOR_HPP_
#define NODEEXECUTOR_HPP_

#include <string>
#include <mesos/executor.hpp>
#include <nan.h>

using std::string;
using namespace mesos;

class NodeExecutor: public Executor {
public:
	explicit NodeExecutor(const v8::Local<v8::Object>& jsExecutorDriver, const v8::Local<v8::Object>& jsExecutor,
			const v8::Local<v8::Object>& protosBuilder);
	~NodeExecutor();

	virtual void registered(ExecutorDriver* driver, const ExecutorInfo& executorInfo, const FrameworkInfo& frameworkInfo, const SlaveInfo& slaveInfo);
	virtual void reregistered(ExecutorDriver* driver, const SlaveInfo& slaveInfo);
	virtual void disconnected(ExecutorDriver* driver);
	virtual void launchTask(ExecutorDriver* driver, const TaskInfo& task);
	virtual void killTask(ExecutorDriver* driver, const TaskID& taskId);
	virtual void frameworkMessage(ExecutorDriver* driver, const string& data);
	virtual void shutdown(ExecutorDriver* driver);
	virtual void error(ExecutorDriver* driver, const string& message);

private:
	Nan::Persistent<v8::Object> _jsExecutorDriver;
	Nan::Persistent<v8::Object> _jsExecutor;
	Nan::Persistent<v8::Object> _protosBuilder;
};

#endif /* NODEEXECUTOR_HPP_ */
