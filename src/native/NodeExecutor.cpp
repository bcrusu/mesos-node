#include "Common.hpp"
#include "NodeExecutor.hpp"
#include "NodeSyncWorker.hpp"

namespace mesosNode {

NodeExecutor::NodeExecutor(const v8::Local<v8::Object>& jsExecutorDriver, const v8::Local<v8::Object>& jsExecutor,
		const v8::Local<v8::Object>& protosBuilder) :
	_jsExecutorDriver(jsExecutorDriver), _jsExecutor(jsExecutor), _protosBuilder(protosBuilder) {
}

NodeExecutor::~NodeExecutor(){
	_jsExecutorDriver.Reset();
	_jsExecutor.Reset();
	_protosBuilder.Reset();
}

void NodeExecutor::registered(ExecutorDriver* driver, const ExecutorInfo& executorInfo, const FrameworkInfo& frameworkInfo,
		const SlaveInfo& slaveInfo) {
	auto worker = new NodeSyncWorker([executor = this, executorInfo, frameworkInfo, slaveInfo] {
		Nan::HandleScope scope;
		v8::Local<v8::Object> protosBuilder = Nan::New(executor->_protosBuilder);
		v8::Local<v8::Object> jsExecutorInfo = CreateProtoObject(executorInfo, protosBuilder, "mesos.ExecutorInfo");
		v8::Local<v8::Object> jsFrameworkInfo = CreateProtoObject(frameworkInfo, protosBuilder, "mesos.FrameworkInfo");
		v8::Local<v8::Object> jsSlaveInfo = CreateProtoObject(slaveInfo, protosBuilder, "mesos.SlaveInfo");

		int argc = 4;
		v8::Local<v8::Value> argv[argc] = { Nan::New(executor->_jsExecutorDriver), jsExecutorInfo, jsFrameworkInfo, jsSlaveInfo };
		EmitEvent(executor->_jsExecutor, "registered", argc, argv);
	});

	worker->Run();
}

void NodeExecutor::reregistered(ExecutorDriver* driver, const SlaveInfo& slaveInfo) {
	auto worker = new NodeSyncWorker([executor = this, slaveInfo] {
		Nan::HandleScope scope;
		v8::Local<v8::Object> protosBuilder = Nan::New(executor->_protosBuilder);
		v8::Local<v8::Object> jsSlaveInfo = CreateProtoObject(slaveInfo, protosBuilder, "mesos.SlaveInfo");

		int argc = 2;
		v8::Local<v8::Value> argv[argc] = { Nan::New(executor->_jsExecutorDriver), jsSlaveInfo };
		EmitEvent(executor->_jsExecutor, "reregistered", argc, argv);
	});

	worker->Run();
}

void NodeExecutor::disconnected(ExecutorDriver* driver) {
	auto worker = new NodeSyncWorker([executor = this] {
		Nan::HandleScope scope;
		int argc = 1;
		v8::Local<v8::Value> argv[argc] = { Nan::New(executor->_jsExecutorDriver) };
		EmitEvent(executor->_jsExecutor, "disconnected", argc, argv);
	});

	worker->Run();
}

void NodeExecutor::launchTask(ExecutorDriver* driver, const TaskInfo& task) {
	auto worker = new NodeSyncWorker([executor = this, task] {
		Nan::HandleScope scope;
		v8::Local<v8::Object> protosBuilder = Nan::New(executor->_protosBuilder);
		v8::Local<v8::Object> jsTaskInfo = CreateProtoObject(task, protosBuilder, "mesos.TaskInfo");

		int argc = 2;
		v8::Local<v8::Value> argv[argc] = { Nan::New(executor->_jsExecutorDriver), jsTaskInfo };
		EmitEvent(executor->_jsExecutor, "launchTask", argc, argv);
	});

	worker->Run();
}

void NodeExecutor::killTask(ExecutorDriver* driver, const TaskID& taskId) {
	auto worker = new NodeSyncWorker([executor = this, taskId] {
		Nan::HandleScope scope;
		v8::Local<v8::Object> protosBuilder = Nan::New(executor->_protosBuilder);
		v8::Local<v8::Object> jsTaskId = CreateProtoObject(taskId, protosBuilder, "mesos.TaskID");

		int argc = 2;
		v8::Local<v8::Value> argv[argc] = { Nan::New(executor->_jsExecutorDriver), jsTaskId };
		EmitEvent(executor->_jsExecutor, "killTask", argc, argv);
	});

	worker->Run();
}

void NodeExecutor::frameworkMessage(ExecutorDriver* driver, const std::string& data) {
	auto worker = new NodeSyncWorker([executor = this, data = std::move(data)] {
		Nan::HandleScope scope;
		v8::MaybeLocal<v8::String> jsData = Nan::New(data);

		int argc = 2;
		v8::Local<v8::Value> argv[argc] = { Nan::New(executor->_jsExecutorDriver), jsData.ToLocalChecked() };
		EmitEvent(executor->_jsExecutor, "frameworkMessage", argc, argv);
	});

	worker->Run();
}

void NodeExecutor::shutdown(ExecutorDriver* driver) {
	auto worker = new NodeSyncWorker([executor = this] {
		Nan::HandleScope scope;
		int argc = 1;
		v8::Local<v8::Value> argv[argc] = { Nan::New(executor->_jsExecutorDriver) };
		EmitEvent(executor->_jsExecutor, "shutdown", argc, argv);
	});

	worker->Run();
}

void NodeExecutor::error(ExecutorDriver* driver, const std::string& message) {
	auto worker = new NodeSyncWorker([executor = this, message = std::move(message)] {
		Nan::HandleScope scope;
		v8::MaybeLocal<v8::String> jsMessage = Nan::New(message);

		int argc = 2;
		v8::Local<v8::Value> argv[argc] = { Nan::New(executor->_jsExecutorDriver), jsMessage.ToLocalChecked() };
		EmitEvent(executor->_jsExecutor, "error", argc, argv);
	});

	worker->Run();
}

}
