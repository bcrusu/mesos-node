#include "Common.hpp"
#include "NodeExecutor.hpp"

NodeExecutor::NodeExecutor(v8::Object jsExecutor) :
		_jsExecutor(jsExecutor) {
	//TODO: validate JS executor instance
}

void NodeExecutor::registered(ExecutorDriver* driver, const ExecutorInfo& executorInfo, const FrameworkInfo& frameworkInfo,
		const SlaveInfo& slaveInfo) {
	ScopedByteArray executorInfoBytes = protobuf::Serialize(executorInfo);
	ScopedByteArray frameworkInfoBytes = protobuf::Serialize(frameworkInfo);
	ScopedByteArray slaveInfoBytes = protobuf::Serialize(slaveInfo);

	//TODO: call _executor
}

void NodeExecutor::reregistered(ExecutorDriver* driver, const SlaveInfo& slaveInfo) {
	ScopedByteArray slaveInfoBytes = protobuf::Serialize(slaveInfo);
	//TODO: call _executor
}

void NodeExecutor::disconnected(ExecutorDriver* driver) {
	//TODO: call _executor
}

void NodeExecutor::launchTask(ExecutorDriver* driver, const TaskInfo& task) {
	ScopedByteArray taskBytes = protobuf::Serialize(task);
	//TODO: call _executor
}

void NodeExecutor::killTask(ExecutorDriver* driver, const TaskID& taskId) {
	ScopedByteArray taskIdBytes = protobuf::Serialize(taskId);
	//TODO: call _executor

}

void NodeExecutor::frameworkMessage(ExecutorDriver* driver, const string& data) {
	ByteArray dataBytes = StringToByteArray(data);
	//TODO: call _executor
}

void NodeExecutor::shutdown(ExecutorDriver* driver) {
	//TODO: call _executor
}

void NodeExecutor::error(ExecutorDriver* driver, const string& message) {
	//TODO: call _executor
}
