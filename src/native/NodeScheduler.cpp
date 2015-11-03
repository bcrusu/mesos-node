#include "NodeScheduler.hpp"
#include "Common.hpp"

NodeScheduler::NodeScheduler(const v8::Local<v8::Object>& jsSchedulerDriver, const v8::Local<v8::Object>& jsScheduler,
		const v8::Local<v8::Object>& protosBuilder) :
		_jsSchedulerDriver(jsSchedulerDriver), _jsScheduler(jsScheduler), _protosBuilder(protosBuilder) {
}

void NodeScheduler::registered(SchedulerDriver* driver, const FrameworkID& frameworkId, const MasterInfo& masterInfo) {
	v8::Locker locker(_jsSchedulerDriver->GetIsolate());

	Nan::HandleScope scope;
	v8::Local<v8::Object> jsframeworkId = CreateProtoObject(frameworkId, _protosBuilder, "mesos.FrameworkID");
	v8::Local<v8::Object> jsMasterInfo = CreateProtoObject(masterInfo, _protosBuilder, "mesos.MasterInfo");

	int argc = 3;
	v8::Local<v8::Value> argv[argc] = { _jsSchedulerDriver, jsframeworkId, jsMasterInfo };
	EmitEvent(_jsScheduler, "registered", argc, argv);
}

void NodeScheduler::reregistered(SchedulerDriver*, const MasterInfo& masterInfo) {
	v8::Locker locker(_jsSchedulerDriver->GetIsolate());

	Nan::HandleScope scope;
	v8::Local<v8::Object> jsMasterInfo = CreateProtoObject(masterInfo, _protosBuilder, "mesos.MasterInfo");

	int argc = 2;
	v8::Local<v8::Value> argv[argc] = { _jsSchedulerDriver, jsMasterInfo };
	EmitEvent(_jsScheduler, "reregistered", argc, argv);
}

void NodeScheduler::disconnected(SchedulerDriver* driver) {
	v8::Locker locker(_jsSchedulerDriver->GetIsolate());

	int argc = 1;
	v8::Local<v8::Value> argv[argc] = { _jsSchedulerDriver };
	EmitEvent(_jsScheduler, "disconnected", argc, argv);
}

void NodeScheduler::resourceOffers(SchedulerDriver* driver, const std::vector<Offer>& offers) {
	v8::Locker locker(_jsSchedulerDriver->GetIsolate());

	Nan::HandleScope scope;
	v8::Local<v8::Array> jsOffers = CreateProtoObjectArray(offers, _protosBuilder, "mesos.Offer");

	int argc = 2;
	v8::Local<v8::Value> argv[argc] = { _jsSchedulerDriver, jsOffers };
	EmitEvent(_jsScheduler, "resourceOffers", argc, argv);
}

void NodeScheduler::offerRescinded(SchedulerDriver* driver, const OfferID& offerId) {
	v8::Locker locker(_jsSchedulerDriver->GetIsolate());

	Nan::HandleScope scope;
	v8::Local<v8::Object> jsOfferId = CreateProtoObject(offerId, _protosBuilder, "mesos.OfferID");

	int argc = 2;
	v8::Local<v8::Value> argv[argc] = { _jsSchedulerDriver, jsOfferId };
	EmitEvent(_jsScheduler, "offerRescinded", argc, argv);
}

void NodeScheduler::statusUpdate(SchedulerDriver* driver, const TaskStatus& status) {
	v8::Locker locker(_jsSchedulerDriver->GetIsolate());

	Nan::HandleScope scope;
	v8::Local<v8::Object> jsStatus = CreateProtoObject(status, _protosBuilder, "mesos.TaskStatus");

	int argc = 2;
	v8::Local<v8::Value> argv[argc] = { _jsSchedulerDriver, jsStatus };
	EmitEvent(_jsScheduler, "statusUpdate", argc, argv);
}

void NodeScheduler::frameworkMessage(SchedulerDriver* driver, const ExecutorID& executorId, const SlaveID& slaveId, const string& data) {
	v8::Locker locker(_jsSchedulerDriver->GetIsolate());

	Nan::HandleScope scope;
	v8::Local<v8::Object> jsExecutorId = CreateProtoObject(executorId, _protosBuilder, "mesos.ExecutorID");
	v8::Local<v8::Object> jsSlaveId = CreateProtoObject(slaveId, _protosBuilder, "mesos.SlaveID");
	v8::Local<v8::Object> jsDataBuffer = CreateBuffer(data);

	int argc = 4;
	v8::Local<v8::Value> argv[argc] = { _jsSchedulerDriver, jsExecutorId, jsSlaveId, jsDataBuffer };
	EmitEvent(_jsScheduler, "frameworkMessage", argc, argv);
}

void NodeScheduler::slaveLost(SchedulerDriver* driver, const SlaveID& slaveId) {
	v8::Locker locker(_jsSchedulerDriver->GetIsolate());

	Nan::HandleScope scope;
	v8::Local<v8::Object> jsSlaveId = CreateProtoObject(slaveId, _protosBuilder, "mesos.SlaveID");

	int argc = 2;
	v8::Local<v8::Value> argv[argc] = { _jsSchedulerDriver, jsSlaveId };
	EmitEvent(_jsScheduler, "slaveLost", argc, argv);
}

void NodeScheduler::executorLost(SchedulerDriver* driver, const ExecutorID& executorId, const SlaveID& slaveId, int status) {
	v8::Locker locker(_jsSchedulerDriver->GetIsolate());

	Nan::HandleScope scope;
	v8::Local<v8::Object> jsSlaveId = CreateProtoObject(slaveId, _protosBuilder, "mesos.SlaveID");
	v8::Local<v8::Int32> jsStatus = Nan::New(status);

	int argc = 3;
	v8::Local<v8::Value> argv[argc] = { _jsSchedulerDriver, jsSlaveId, jsStatus };
	EmitEvent(_jsScheduler, "executorLost", argc, argv);
}

void NodeScheduler::error(SchedulerDriver* driver, const string& message) {
	v8::Locker locker(_jsSchedulerDriver->GetIsolate());

	Nan::HandleScope scope;
	v8::MaybeLocal<v8::String> jsMessage = Nan::New(message);

	int argc = 2;
	v8::Local<v8::Value> argv[argc] = { _jsSchedulerDriver, jsMessage.ToLocalChecked() };
	EmitEvent(_jsScheduler, "error", argc, argv);
}
