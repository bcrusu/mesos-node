#include "Common.hpp"
#include "NodeExecutor.hpp"

NodeExecutor::NodeExecutor(const v8::Local<v8::Object>& jsExecutorDriver, v8::Local<v8::Object> jsExecutor, v8::Local<v8::Object> protosBuilder) :
		_jsExecutorDriver(jsExecutorDriver), _jsExecutor(jsExecutor), _protosBuilder(protosBuilder) {
}

void NodeExecutor::registered(ExecutorDriver* driver, const ExecutorInfo& executorInfo, const FrameworkInfo& frameworkInfo,
		const SlaveInfo& slaveInfo) {
	v8::Locker locker(_jsExecutorDriver->GetIsolate());

	Nan::HandleScope scope;
	v8::Local<v8::Object> jsExecutorInfo = CreateProtoObject(executorInfo, _protosBuilder, "mesos.ExecutorInfo");
	v8::Local<v8::Object> jsFrameworkInfo = CreateProtoObject(frameworkInfo, _protosBuilder, "mesos.FrameworkInfo");
	v8::Local<v8::Object> jsSlaveInfo = CreateProtoObject(slaveInfo, _protosBuilder, "mesos.SlaveInfo");

	int argc = 4;
	v8::Local<v8::Value> argv[argc] = { _jsExecutorDriver, jsExecutorInfo, jsFrameworkInfo, jsSlaveInfo };
	EmitEvent(_jsExecutor, "registered", argc, argv);
}

void NodeExecutor::reregistered(ExecutorDriver* driver, const SlaveInfo& slaveInfo) {
	v8::Locker locker(_jsExecutorDriver->GetIsolate());

	Nan::HandleScope scope;
	v8::Local<v8::Object> jsSlaveInfo = CreateProtoObject(slaveInfo, _protosBuilder, "mesos.SlaveInfo");

	int argc = 2;
	v8::Local<v8::Value> argv[argc] = { _jsExecutorDriver, jsSlaveInfo };
	EmitEvent(_jsExecutor, "reregistered", argc, argv);
}

void NodeExecutor::disconnected(ExecutorDriver* driver) {
	v8::Locker locker(_jsExecutorDriver->GetIsolate());

	int argc = 1;
	v8::Local<v8::Value> argv[argc] = { _jsExecutorDriver };
	EmitEvent(_jsExecutor, "disconnected", argc, argv);
}

void NodeExecutor::launchTask(ExecutorDriver* driver, const TaskInfo& task) {
	v8::Locker locker(_jsExecutorDriver->GetIsolate());

	Nan::HandleScope scope;
	v8::Local<v8::Object> jsTaskInfo = CreateProtoObject(task, _protosBuilder, "mesos.TaskInfo");

	int argc = 2;
	v8::Local<v8::Value> argv[argc] = { _jsExecutorDriver, jsTaskInfo };
	EmitEvent(_jsExecutor, "launchTask", argc, argv);
}

void NodeExecutor::killTask(ExecutorDriver* driver, const TaskID& taskId) {
	v8::Locker locker(_jsExecutorDriver->GetIsolate());

	Nan::HandleScope scope;
	v8::Local<v8::Object> jsTaskId = CreateProtoObject(taskId, _protosBuilder, "mesos.TaskID");

	int argc = 2;
	v8::Local<v8::Value> argv[argc] = { _jsExecutorDriver, jsTaskId };
	EmitEvent(_jsExecutor, "killTask", argc, argv);

}

void NodeExecutor::frameworkMessage(ExecutorDriver* driver, const string& data) {
	v8::Locker locker(_jsExecutorDriver->GetIsolate());

	Nan::HandleScope scope;
	v8::Local<v8::Object> jsDataBuffer = CreateBuffer(data);

	int argc = 2;
	v8::Local<v8::Value> argv[argc] = { _jsExecutorDriver, jsDataBuffer };
	EmitEvent(_jsExecutor, "frameworkMessage", argc, argv);
}

void NodeExecutor::shutdown(ExecutorDriver* driver) {
	v8::Locker locker(_jsExecutorDriver->GetIsolate());

	int argc = 1;
	v8::Local<v8::Value> argv[argc] = { _jsExecutorDriver };
	EmitEvent(_jsExecutor, "shutdown", argc, argv);
}

void NodeExecutor::error(ExecutorDriver* driver, const string& message) {
	v8::Locker locker(_jsExecutorDriver->GetIsolate());

	Nan::HandleScope scope;
	v8::MaybeLocal<v8::String> jsMessage = Nan::New(message);

	int argc = 2;
	v8::Local<v8::Value> argv[argc] = { _jsExecutorDriver, jsMessage.ToLocalChecked() };
	EmitEvent(_jsExecutor, "error", argc, argv);
}
