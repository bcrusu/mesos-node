#include "Common.hpp"
#include "NodeScheduler.hpp"
#include "NodeSyncWorker.hpp"

namespace mesosNode {

NodeScheduler::NodeScheduler(const v8::Local<v8::Object>& jsSchedulerDriver, const v8::Local<v8::Object>& jsScheduler,
		const v8::Local<v8::Object>& protosBuilder) :
		_jsSchedulerDriver(jsSchedulerDriver), _jsScheduler(jsScheduler), _protosBuilder(protosBuilder) {
}

NodeScheduler::~NodeScheduler(){
	_jsSchedulerDriver.Reset();
	_jsScheduler.Reset();
	_protosBuilder.Reset();
}

void NodeScheduler::registered(SchedulerDriver* driver, const FrameworkID& frameworkId, const MasterInfo& masterInfo) {
	auto worker = new NodeSyncWorker([scheduler = this, frameworkId, masterInfo] {
		Nan::HandleScope scope;
		v8::Local<v8::Object> protosBuilder = Nan::New(scheduler->_protosBuilder);
		v8::Local<v8::Object> jsframeworkId = CreateProtoObject(frameworkId, protosBuilder, "mesos.FrameworkID");
		v8::Local<v8::Object> jsMasterInfo = CreateProtoObject(masterInfo, protosBuilder, "mesos.MasterInfo");

		int argc = 3;
		v8::Local<v8::Value> argv[argc] = { Nan::New(scheduler->_jsSchedulerDriver), jsframeworkId, jsMasterInfo };
		EmitEvent(scheduler->_jsScheduler, "registered", argc, argv);
	});

	worker->Run();
}

void NodeScheduler::reregistered(SchedulerDriver*, const MasterInfo& masterInfo) {
	auto worker = new NodeSyncWorker([scheduler = this, masterInfo] {
		Nan::HandleScope scope;
		v8::Local<v8::Object> protosBuilder = Nan::New(scheduler->_protosBuilder);
		v8::Local<v8::Object> jsMasterInfo = CreateProtoObject(masterInfo, protosBuilder, "mesos.MasterInfo");

		int argc = 2;
		v8::Local<v8::Value> argv[argc] = { Nan::New(scheduler->_jsSchedulerDriver), jsMasterInfo };
		EmitEvent(scheduler->_jsScheduler, "reregistered", argc, argv);
	});

	worker->Run();
}

void NodeScheduler::disconnected(SchedulerDriver* driver) {
	auto worker = new NodeSyncWorker([scheduler = this] {
		Nan::HandleScope scope;
		int argc = 1;
		v8::Local<v8::Value> argv[argc] = { Nan::New(scheduler->_jsSchedulerDriver) };
		EmitEvent(scheduler->_jsScheduler, "disconnected", argc, argv);
	});

	worker->Run();
}

void NodeScheduler::resourceOffers(SchedulerDriver* driver, const std::vector<Offer>& offers) {
	auto worker = new NodeSyncWorker([scheduler = this, offers = std::move(offers)] {
		Nan::HandleScope scope;
		v8::Local<v8::Object> protosBuilder = Nan::New(scheduler->_protosBuilder);
		v8::Local<v8::Array> jsOffers = CreateProtoObjectArray(offers, protosBuilder, "mesos.Offer");

		int argc = 2;
		v8::Local<v8::Value> argv[argc] = { Nan::New(scheduler->_jsSchedulerDriver), jsOffers };
		EmitEvent(scheduler->_jsScheduler, "resourceOffers", argc, argv);
	});

	worker->Run();
}

void NodeScheduler::offerRescinded(SchedulerDriver* driver, const OfferID& offerId) {
	auto worker = new NodeSyncWorker([scheduler = this, offerId] {
		Nan::HandleScope scope;
		v8::Local<v8::Object> protosBuilder = Nan::New(scheduler->_protosBuilder);
		v8::Local<v8::Object> jsOfferId = CreateProtoObject(offerId, protosBuilder, "mesos.OfferID");

		int argc = 2;
		v8::Local<v8::Value> argv[argc] = { Nan::New(scheduler->_jsSchedulerDriver), jsOfferId };
		EmitEvent(scheduler->_jsScheduler, "offerRescinded", argc, argv);
	});

	worker->Run();
}

void NodeScheduler::statusUpdate(SchedulerDriver* driver, const TaskStatus& status) {
	auto worker = new NodeSyncWorker([scheduler = this, status] {
		Nan::HandleScope scope;
		v8::Local<v8::Object> protosBuilder = Nan::New(scheduler->_protosBuilder);
		v8::Local<v8::Object> jsStatus = CreateProtoObject(status, protosBuilder, "mesos.TaskStatus");

		int argc = 2;
		v8::Local<v8::Value> argv[argc] = { Nan::New(scheduler->_jsSchedulerDriver), jsStatus };
		EmitEvent(scheduler->_jsScheduler, "statusUpdate", argc, argv);
	});

	worker->Run();
}

void NodeScheduler::frameworkMessage(SchedulerDriver* driver, const ExecutorID& executorId, const SlaveID& slaveId, const std::string& data) {
	auto worker = new NodeSyncWorker([scheduler = this, executorId, slaveId, data = std::move(data)] {
		Nan::HandleScope scope;
		v8::Local<v8::Object> protosBuilder = Nan::New(scheduler->_protosBuilder);
		v8::Local<v8::Object> jsExecutorId = CreateProtoObject(executorId, protosBuilder, "mesos.ExecutorID");
		v8::Local<v8::Object> jsSlaveId = CreateProtoObject(slaveId, protosBuilder, "mesos.SlaveID");
		v8::MaybeLocal<v8::String> jsData = Nan::New(data);

		int argc = 4;
		v8::Local<v8::Value> argv[argc] = { Nan::New(scheduler->_jsSchedulerDriver), jsExecutorId, jsSlaveId, jsData.ToLocalChecked() };
		EmitEvent(scheduler->_jsScheduler, "frameworkMessage", argc, argv);
	});

	worker->Run();
}

void NodeScheduler::slaveLost(SchedulerDriver* driver, const SlaveID& slaveId) {
	auto worker = new NodeSyncWorker([scheduler = this, slaveId] {
		Nan::HandleScope scope;
		v8::Local<v8::Object> protosBuilder = Nan::New(scheduler->_protosBuilder);
		v8::Local<v8::Object> jsSlaveId = CreateProtoObject(slaveId, protosBuilder, "mesos.SlaveID");

		int argc = 2;
		v8::Local<v8::Value> argv[argc] = { Nan::New(scheduler->_jsSchedulerDriver), jsSlaveId };
		EmitEvent(scheduler->_jsScheduler, "slaveLost", argc, argv);
	});

	worker->Run();
}

void NodeScheduler::executorLost(SchedulerDriver* driver, const ExecutorID& executorId, const SlaveID& slaveId, int status) {
	auto worker = new NodeSyncWorker([scheduler = this, executorId, slaveId, status] {
		Nan::HandleScope scope;
		v8::Local<v8::Object> protosBuilder = Nan::New(scheduler->_protosBuilder);
		v8::Local<v8::Object> jsSlaveId = CreateProtoObject(slaveId, protosBuilder, "mesos.SlaveID");
		v8::Local<v8::Int32> jsStatus = Nan::New(status);

		int argc = 3;
		v8::Local<v8::Value> argv[argc] = { Nan::New(scheduler->_jsSchedulerDriver), jsSlaveId, jsStatus };
		EmitEvent(scheduler->_jsScheduler, "executorLost", argc, argv);
	});

	worker->Run();
}

void NodeScheduler::error(SchedulerDriver* driver, const std::string& message) {
	auto worker = new NodeSyncWorker([scheduler = this, message = std::move(message)] {
		Nan::HandleScope scope;
		v8::MaybeLocal<v8::String> jsMessage = Nan::New(message);

		int argc = 2;
		v8::Local<v8::Value> argv[argc] = { Nan::New(scheduler->_jsSchedulerDriver), jsMessage.ToLocalChecked() };
		EmitEvent(Nan::New(scheduler->_jsScheduler), "error", argc, argv);
	});

	worker->Run();
}

}
