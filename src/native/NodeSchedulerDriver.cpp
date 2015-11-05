#include "NodeSchedulerDriver.hpp"
#include "Common.hpp"
#include "Macros.hpp"
#include "MesosAsyncWorker.hpp"

Nan::Persistent<v8::Function> NodeSchedulerDriver::_constructor;

NodeSchedulerDriver::NodeSchedulerDriver(NodeScheduler* scheduler, const FrameworkInfo& framework,
		const std::string& master, bool implicitAcknowlegements, const Credential& credential) :
		_scheduler(scheduler), _schedulerDriver(
				new MesosSchedulerDriver(_scheduler, framework, master, implicitAcknowlegements, credential)) {
}

NodeSchedulerDriver::NodeSchedulerDriver(NodeScheduler* scheduler, const FrameworkInfo& framework,
		const std::string& master, bool implicitAcknowlegements) :
		_scheduler(scheduler), _schedulerDriver(
				new MesosSchedulerDriver(_scheduler, framework, master, implicitAcknowlegements)) {
}

NodeSchedulerDriver::~NodeSchedulerDriver() {
	delete _schedulerDriver;
	delete _scheduler;
}

v8::Local<v8::Value> NodeSchedulerDriver::MesosStatusToJs(mesos::Status status){
	return Nan::New(status);  //TODO: convert to proper Mesos proto object (i.e. not Int32)
}

void NodeSchedulerDriver::Init(v8::Local<v8::Object> exports) {
	Nan::HandleScope scope;

	// constructor template
	v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
	tpl->SetClassName(Nan::New("MesosSchedulerDriver").ToLocalChecked());

	// prototype
	Nan::SetPrototypeMethod(tpl, "start", Start);
	Nan::SetPrototypeMethod(tpl, "stop", Stop);
	Nan::SetPrototypeMethod(tpl, "abort", Abort);
	Nan::SetPrototypeMethod(tpl, "join", Join);
	Nan::SetPrototypeMethod(tpl, "run", Run);
	Nan::SetPrototypeMethod(tpl, "requestResources", RequestResources);
	Nan::SetPrototypeMethod(tpl, "launchTasks", LaunchTasks);
	Nan::SetPrototypeMethod(tpl, "killTask", KillTask);
	Nan::SetPrototypeMethod(tpl, "acceptOffers", AcceptOffers);
	Nan::SetPrototypeMethod(tpl, "declineOffer", DeclineOffer);
	Nan::SetPrototypeMethod(tpl, "reviveOffers", ReviveOffers);
	Nan::SetPrototypeMethod(tpl, "suppressOffers", SuppressOffers);
	Nan::SetPrototypeMethod(tpl, "acknowledgeStatusUpdate", AcknowledgeStatusUpdate);
	Nan::SetPrototypeMethod(tpl, "sendFrameworkMessage", SendFrameworkMessage);
	Nan::SetPrototypeMethod(tpl, "reconcileTasks", ReconcileTasks);

	_constructor.Reset(tpl->GetFunction());
	exports->Set(Nan::New("MesosSchedulerDriver").ToLocalChecked(), tpl->GetFunction());
}

void NodeSchedulerDriver::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS_OR(5, 6)
	Nan::HandleScope scope;

	int argc = info.Length();

	if (info.IsConstructCall()) {
		REQUIRE_ARGUMENT_OBJECT(0, jsProtosBuilder)
		REQUIRE_ARGUMENT_OBJECT(1, jsScheduler)
		REQUIRE_ARGUMENT_OBJECT(2, jsFrameworkInfo)
		REQUIRE_ARGUMENT_STRING(3, jsMaster)
		REQUIRE_ARGUMENT_BOOLEAN(4, jsImplicitAcknowlegements)
		v8::Local<v8::Object> jsSchedulerDriver = info.This();

		mesos::FrameworkInfo frameworkInfo = CreateProtoMessage<mesos::FrameworkInfo>(jsFrameworkInfo);
		std::string master(*jsMaster, jsMaster.length());
		bool implicitAcknowlegements = jsImplicitAcknowlegements->BooleanValue();

		NodeScheduler* scheduler = new NodeScheduler(jsSchedulerDriver, jsScheduler, jsProtosBuilder);
		NodeSchedulerDriver* schedulerDriver;

		if (argc == 6) {
			REQUIRE_ARGUMENT_OBJECT(5, jsCredential)
			mesos::Credential credential = CreateProtoMessage<mesos::Credential>(jsCredential);
			schedulerDriver = new NodeSchedulerDriver(scheduler, frameworkInfo, master, implicitAcknowlegements,
					credential);
		} else {
			schedulerDriver = new NodeSchedulerDriver(scheduler, frameworkInfo, master, implicitAcknowlegements);
		}

		schedulerDriver->Wrap(jsSchedulerDriver);
		info.GetReturnValue().Set(jsSchedulerDriver);
	} else {
		v8::Local<v8::Value> argv[argc] = { info[0], info[1], info[2], info[3], info[4] };
		if (argc == 6)
			argv[5] = info[5];

		v8::Local<v8::Function> cons = Nan::New<v8::Function>(_constructor);
		info.GetReturnValue().Set(cons->NewInstance(argc, argv));
	}
}

void NodeSchedulerDriver::Start(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS(0)
	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());

	auto worker = new MesosAsyncWorker<mesos::Status>([driver] {return driver->_schedulerDriver->start();}, MesosStatusToJs);
	Nan::AsyncQueueWorker(worker);
	info.GetReturnValue().Set(worker->GetPromise());
}

void NodeSchedulerDriver::Stop(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS_OR(0, 1)
	Nan::HandleScope scope;
	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());

	bool failover = false;
	if (info.Length() == 1) {
		REQUIRE_ARGUMENT_BOOLEAN(0, jsFailover)
		failover = jsFailover->BooleanValue();
	}

	auto worker = new MesosAsyncWorker<mesos::Status>([driver, failover] {return driver->_schedulerDriver->stop(failover);}, MesosStatusToJs);
	Nan::AsyncQueueWorker(worker);
	info.GetReturnValue().Set(worker->GetPromise());
}

void NodeSchedulerDriver::Abort(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS(0)
	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());

	auto worker = new MesosAsyncWorker<mesos::Status>([driver] {return driver->_schedulerDriver->abort();}, MesosStatusToJs);
	Nan::AsyncQueueWorker(worker);
	info.GetReturnValue().Set(worker->GetPromise());
}

void NodeSchedulerDriver::Join(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS(0)
	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());

	auto worker = new MesosAsyncWorker<mesos::Status>([driver] {return driver->_schedulerDriver->join();}, MesosStatusToJs);
	Nan::AsyncQueueWorker(worker);
	info.GetReturnValue().Set(worker->GetPromise());
}

void NodeSchedulerDriver::Run(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS(0)
	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());

	auto worker = new MesosAsyncWorker<mesos::Status>([driver] {return driver->_schedulerDriver->run();}, MesosStatusToJs);
	Nan::AsyncQueueWorker(worker);
	info.GetReturnValue().Set(worker->GetPromise());
}

void NodeSchedulerDriver::RequestResources(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	Nan::HandleScope scope;
	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());

	REQUIRE_ARGUMENTS(1)
	REQUIRE_ARGUMENT_ARRAY(0, jsRequests)
	std::vector<mesos::Request> requests = CreateProtoMessageVector<mesos::Request>(jsRequests);

	auto worker = new MesosAsyncWorker<mesos::Status>([driver, requests = std::move(requests)] {return driver->_schedulerDriver->requestResources(requests);}, MesosStatusToJs);
	Nan::AsyncQueueWorker (worker);
	info.GetReturnValue().Set(worker->GetPromise());
}

void NodeSchedulerDriver::LaunchTasks(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS_OR(2, 3)
	Nan::HandleScope scope;
	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());

	REQUIRE_ARGUMENT_ARRAY(0, jsOfferIds)
	REQUIRE_ARGUMENT_ARRAY(1, jsTasks)
	std::vector<mesos::OfferID> offerIds = CreateProtoMessageVector<mesos::OfferID>(jsOfferIds);
	std::vector<mesos::TaskInfo> tasks = CreateProtoMessageVector<mesos::TaskInfo>(jsTasks);

	std::function<mesos::Status()> work;
	if (info.Length() == 3) {
		REQUIRE_ARGUMENT_OBJECT(2, jsFilters)
		mesos::Filters filters = CreateProtoMessage<mesos::Filters>(jsFilters);
		work = [driver, offerIds = std::move(offerIds), tasks = std::move(tasks), filters] {return driver->_schedulerDriver->launchTasks(offerIds, tasks, filters);};
	} else {
		work = [driver, offerIds = std::move(offerIds), tasks = std::move(tasks)] {return driver->_schedulerDriver->launchTasks(offerIds, tasks);};
	}

	auto worker = new MesosAsyncWorker<mesos::Status>(std::move(work), MesosStatusToJs);
	Nan::AsyncQueueWorker (worker);
	info.GetReturnValue().Set(worker->GetPromise());
}

void NodeSchedulerDriver::KillTask(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS(1)
	Nan::HandleScope scope;
	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());

	REQUIRE_ARGUMENT_OBJECT(0, jsTaskId)
	mesos::TaskID taskId = CreateProtoMessage<mesos::TaskID>(jsTaskId);

	auto worker = new MesosAsyncWorker<mesos::Status>([driver, taskId] {return driver->_schedulerDriver->killTask(taskId);}, MesosStatusToJs);
	Nan::AsyncQueueWorker(worker);
	info.GetReturnValue().Set(worker->GetPromise());
}

void NodeSchedulerDriver::AcceptOffers(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS_OR(2, 3)
	Nan::HandleScope scope;
	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());

	REQUIRE_ARGUMENT_ARRAY(0, jsOfferIds)
	REQUIRE_ARGUMENT_ARRAY(1, jsOperations)
	std::vector<mesos::OfferID> offerIds = CreateProtoMessageVector<mesos::OfferID>(jsOfferIds);
	std::vector<mesos::Offer::Operation> operations = CreateProtoMessageVector<mesos::Offer::Operation>(jsOperations);

	std::function<mesos::Status()> work;
	if (info.Length() == 3) {
		REQUIRE_ARGUMENT_OBJECT(2, jsFilters)
		mesos::Filters filters = CreateProtoMessage<mesos::Filters>(jsFilters);
		work = [driver, offerIds = std::move(offerIds), operations = std::move(operations), filters] {return driver->_schedulerDriver->acceptOffers(offerIds, operations, filters);};
	} else {
		work = [driver, offerIds = std::move(offerIds), operations = std::move(operations)] {return driver->_schedulerDriver->acceptOffers(offerIds, operations);};
	}

	auto worker = new MesosAsyncWorker<mesos::Status>(std::move(work), MesosStatusToJs);
	Nan::AsyncQueueWorker (worker);
	info.GetReturnValue().Set(worker->GetPromise());
}

void NodeSchedulerDriver::DeclineOffer(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS_OR(1, 2)
	Nan::HandleScope scope;
	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());

	REQUIRE_ARGUMENT_OBJECT(0, jsOfferId)
	mesos::OfferID offer = CreateProtoMessage<mesos::OfferID>(jsOfferId);

	std::function<mesos::Status()> work;
	if (info.Length() == 2) {
		REQUIRE_ARGUMENT_OBJECT(1, jsFilters)
		mesos::Filters filters = CreateProtoMessage<mesos::Filters>(jsFilters);
		work = [driver, offer, filters] {return driver->_schedulerDriver->declineOffer(offer, filters);};
	} else {
		work = [driver, offer] {return driver->_schedulerDriver->declineOffer(offer);};
	}

	auto worker = new MesosAsyncWorker<mesos::Status>(std::move(work), MesosStatusToJs);
	Nan::AsyncQueueWorker (worker);
	info.GetReturnValue().Set(worker->GetPromise());
}

void NodeSchedulerDriver::ReviveOffers(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS(0)
	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());

	auto worker = new MesosAsyncWorker<mesos::Status>([driver] {return driver->_schedulerDriver->reviveOffers();}, MesosStatusToJs);
	Nan::AsyncQueueWorker(worker);
	info.GetReturnValue().Set(worker->GetPromise());
}

void NodeSchedulerDriver::SuppressOffers(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS(0)
	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());

	auto worker = new MesosAsyncWorker<mesos::Status>([driver] {return driver->_schedulerDriver->suppressOffers();}, MesosStatusToJs);
	Nan::AsyncQueueWorker(worker);
	info.GetReturnValue().Set(worker->GetPromise());
}

void NodeSchedulerDriver::AcknowledgeStatusUpdate(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	Nan::HandleScope scope;
	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());

	REQUIRE_ARGUMENTS(1)
	REQUIRE_ARGUMENT_OBJECT(0, jsStatus)
	mesos::TaskStatus taskStatus = CreateProtoMessage<mesos::TaskStatus>(jsStatus);

	auto worker = new MesosAsyncWorker<mesos::Status>([driver, taskStatus] {return driver->_schedulerDriver->acknowledgeStatusUpdate(taskStatus);}, MesosStatusToJs);
	Nan::AsyncQueueWorker(worker);
	info.GetReturnValue().Set(worker->GetPromise());
}

void NodeSchedulerDriver::SendFrameworkMessage(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	Nan::HandleScope scope;
	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());

	REQUIRE_ARGUMENTS(3)
	REQUIRE_ARGUMENT_OBJECT(0, jsExecutorId)
	REQUIRE_ARGUMENT_OBJECT(1, jsSlaveId)
	REQUIRE_ARGUMENT_ARRAYBUFFER(2, jsData)

	mesos::ExecutorID executorId = CreateProtoMessage<mesos::ExecutorID>(jsExecutorId);
	mesos::SlaveID slaveId = CreateProtoMessage<mesos::SlaveID>(jsSlaveId);
	std::string data = ArrayBufferToString(jsData);

	auto worker = new MesosAsyncWorker<mesos::Status>([driver, executorId, slaveId, data = std::move(data)] {return driver->_schedulerDriver->sendFrameworkMessage(executorId, slaveId, data);}, MesosStatusToJs);
	Nan::AsyncQueueWorker(worker);
	info.GetReturnValue().Set(worker->GetPromise());
}

void NodeSchedulerDriver::ReconcileTasks(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	Nan::HandleScope scope;
	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());

	REQUIRE_ARGUMENTS(1)
	REQUIRE_ARGUMENT_ARRAY(0, jsStatuses)
	std::vector<mesos::TaskStatus> statuses = CreateProtoMessageVector<mesos::TaskStatus>(jsStatuses);

	auto worker = new MesosAsyncWorker<mesos::Status>([driver, statuses = std::move(statuses)] {return driver->_schedulerDriver->reconcileTasks(statuses);}, MesosStatusToJs);
	Nan::AsyncQueueWorker(worker);
	info.GetReturnValue().Set(worker->GetPromise());
}
