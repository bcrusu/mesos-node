#include "NodeScheduler.hpp"
#include "Common.hpp"

NodeScheduler::NodeScheduler(const v8::Local<v8::Object>& jsSchedulerDriver, const v8::Local<v8::Object>& jsScheduler,
		const v8::Local<v8::Object>& protosBuilder) :
		_jsSchedulerDriver(jsSchedulerDriver), _jsScheduler(jsScheduler), _protosBuilder(protosBuilder) {
}

void NodeScheduler::registered(SchedulerDriver* driver, const FrameworkID& frameworkId, const MasterInfo& masterInfo) {
	ScopedByteArray frameworkIdBytes = protobuf::Serialize(frameworkId);
	ScopedByteArray masterInfoBytes = protobuf::Serialize(masterInfo);
	//TODO: call _scheduler
}

void NodeScheduler::reregistered(SchedulerDriver*, const MasterInfo& masterInfo) {
	Nan::HandleScope scope;
	v8::Local<v8::Object> jsMasterInfo = protobuf::CreateJsObject(masterInfo, _protosBuilder, "mesos.MasterInfo");

	int argc = 2;
	v8::Local<v8::Value> argv[argc] = { _jsSchedulerDriver, jsMasterInfo };
	EmitEvent(_jsScheduler, "reregistered", argc, argv);
}

void NodeScheduler::disconnected(SchedulerDriver* driver) {
	int argc = 1;
	v8::Local<v8::Value> argv[argc] = { _jsSchedulerDriver };
	EmitEvent(_jsScheduler, "disconnected", argc, argv);
}

void NodeScheduler::resourceOffers(SchedulerDriver* driver, const vector<Offer>& offers) {
	ScopedByteArrayCollection offersCollection = protobuf::SerializeVector(offers);
	//TODO: call _scheduler
}

void NodeScheduler::offerRescinded(SchedulerDriver* driver, const OfferID& offerId) {
	ScopedByteArray offerIdBytes = protobuf::Serialize(offerId);
	//TODO: call _scheduler
}

void NodeScheduler::statusUpdate(SchedulerDriver* driver, const TaskStatus& status) {
	ScopedByteArray statusBytes = protobuf::Serialize(status);
	//TODO: call _scheduler
}

void NodeScheduler::frameworkMessage(SchedulerDriver* driver, const ExecutorID& executorId, const SlaveID& slaveId,
		const string& data) {
	ScopedByteArray executorIdBytes = protobuf::Serialize(executorId);
	ScopedByteArray slaveIdBytes = protobuf::Serialize(slaveId);
	ByteArray dataBytes = StringToByteArray(data);
	//TODO: call _scheduler
}

void NodeScheduler::slaveLost(SchedulerDriver* driver, const SlaveID& slaveId) {
	ScopedByteArray slaveIdBytes = protobuf::Serialize(slaveId);
	//TODO: call _scheduler
}

void NodeScheduler::executorLost(SchedulerDriver* driver, const ExecutorID& executorId, const SlaveID& slaveId,
		int status) {
	ScopedByteArray executorIdBytes = protobuf::Serialize(executorId);
	ScopedByteArray slaveIdBytes = protobuf::Serialize(slaveId);
	//TODO: call _scheduler
}

void NodeScheduler::error(SchedulerDriver* driver, const string& message) {
	Nan::HandleScope scope;
	v8::Local<v8::Object> jsMessage = Nan::New(message);

	int argc = 2;
	v8::Local<v8::Value> argv[argc] = { _jsSchedulerDriver, jsMessage };
	EmitEvent(_jsScheduler, "error", argc, argv);
}
