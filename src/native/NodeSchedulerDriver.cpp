#include "NodeSchedulerDriver.hpp"
#include "Common.hpp"

NodeSchedulerDriver::NodeSchedulerDriver(NodeScheduler* scheduler, const FrameworkInfo& framework, const std::string& master,
		bool implicitAcknowlegements, const Credential& credential) :
		_scheduler(scheduler), _schedulerDriver(new MesosSchedulerDriver(_scheduler, framework, master, implicitAcknowlegements, credential)) {
}

NodeSchedulerDriver::NodeSchedulerDriver(NodeScheduler* scheduler, const FrameworkInfo& framework, const std::string& master,
		bool implicitAcknowlegements) :
		_scheduler(scheduler), _schedulerDriver(new MesosSchedulerDriver(_scheduler, framework, master, implicitAcknowlegements)) {
}

NodeSchedulerDriver::~NodeSchedulerDriver() {
	delete _schedulerDriver;
	delete _scheduler;
}

void NodeSchedulerDriver::Init(v8::Local<v8::Object> exports) {
	Nan::HandleScope scope;

	// constructor template
	v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
	tpl->SetClassName(Nan::New("MesosSchedulerDriver").ToLocalChecked());
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

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
			schedulerDriver = new NodeSchedulerDriver(scheduler, frameworkInfo, master, implicitAcknowlegements, credential);
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
	driver->_schedulerDriver->start();
}

void NodeSchedulerDriver::Stop(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS_OR(0, 1)
	Nan::HandleScope scope;

	bool failover = false;
	if (info.Length() == 1) {
		REQUIRE_ARGUMENT_BOOLEAN(0, jsFailover)
		failover = jsFailover->BooleanValue();
	}

	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());
	driver->_schedulerDriver->stop(failover);
}

void NodeSchedulerDriver::Abort(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS(0)
	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());
	driver->_schedulerDriver->abort();
}

void NodeSchedulerDriver::Join(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS(0)
	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());
	driver->_schedulerDriver->join();
}

void NodeSchedulerDriver::Run(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS(0)
	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());
	driver->_schedulerDriver->run();
}

void NodeSchedulerDriver::RequestResources(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	Nan::HandleScope scope;

	REQUIRE_ARGUMENTS(1)
	REQUIRE_ARGUMENT_ARRAY(0, jsRequests)
	std::vector<mesos::Request> requests = CreateProtoMessageVector<mesos::Request>(jsRequests);

	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());
	driver->_schedulerDriver->requestResources(requests);
}

void NodeSchedulerDriver::LaunchTasks(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS_OR(2, 3)
	Nan::HandleScope scope;

	REQUIRE_ARGUMENT_ARRAY(0, jsOfferIds)
	REQUIRE_ARGUMENT_ARRAY(1, jsTasks)
	std::vector<mesos::OfferID> offerIds = CreateProtoMessageVector<mesos::OfferID>(jsOfferIds);
	std::vector<mesos::TaskInfo> tasks = CreateProtoMessageVector<mesos::TaskInfo>(jsTasks);

	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());

	if (info.Length() == 3) {
		REQUIRE_ARGUMENT_OBJECT(2, jsFilters)
		mesos::Filters filters = CreateProtoMessage<mesos::Filters>(jsFilters);
		driver->_schedulerDriver->launchTasks(offerIds, tasks, filters);
	} else {
		driver->_schedulerDriver->launchTasks(offerIds, tasks);
	}
}

void NodeSchedulerDriver::KillTask(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	Nan::HandleScope scope;

	REQUIRE_ARGUMENTS(1)
	REQUIRE_ARGUMENT_OBJECT(0, jsTaskId)
	mesos::TaskID taskId = CreateProtoMessage<mesos::TaskID>(jsTaskId);

	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());
	driver->_schedulerDriver->killTask(taskId);
}

void NodeSchedulerDriver::AcceptOffers(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS_OR(2, 3)
	Nan::HandleScope scope;

	REQUIRE_ARGUMENT_ARRAY(0, jsOfferIds)
	REQUIRE_ARGUMENT_ARRAY(1, jsOperations)
	std::vector<mesos::OfferID> offerIds = CreateProtoMessageVector<mesos::OfferID>(jsOfferIds);
	std::vector<mesos::Offer::Operation> operations = CreateProtoMessageVector<mesos::Offer::Operation>(jsOperations);

	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());

	if (info.Length() == 3) {
		REQUIRE_ARGUMENT_OBJECT(2, jsFilters)
		mesos::Filters filters = CreateProtoMessage<mesos::Filters>(jsFilters);
		driver->_schedulerDriver->acceptOffers(offerIds, operations, filters);
	} else {
		driver->_schedulerDriver->acceptOffers(offerIds, operations);
	}
}

void NodeSchedulerDriver::DeclineOffer(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS_OR(1, 2)
	Nan::HandleScope scope;

	REQUIRE_ARGUMENT_ARRAY(0, jsOfferId)
	mesos::OfferID offer = CreateProtoMessage<mesos::OfferID>(jsOfferId);

	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());

	if (info.Length() == 2) {
		REQUIRE_ARGUMENT_OBJECT(1, jsFilters)
		mesos::Filters filters = CreateProtoMessage<mesos::Filters>(jsFilters);
		driver->_schedulerDriver->declineOffer(offer, filters);
	} else {
		driver->_schedulerDriver->declineOffer(offer);
	}
}

void NodeSchedulerDriver::ReviveOffers(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS(1)
	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());
	driver->_schedulerDriver->reviveOffers();
}

void NodeSchedulerDriver::SuppressOffers(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS(1)
	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());
	driver->_schedulerDriver->suppressOffers();
}

void NodeSchedulerDriver::AcknowledgeStatusUpdate(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	Nan::HandleScope scope;

	REQUIRE_ARGUMENTS(1)
	REQUIRE_ARGUMENT_OBJECT(0, jsStatus)
	mesos::TaskStatus status = CreateProtoMessage<mesos::TaskStatus>(jsStatus);

	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());
	driver->_schedulerDriver->acknowledgeStatusUpdate(status);
}

void NodeSchedulerDriver::SendFrameworkMessage(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	Nan::HandleScope scope;

	REQUIRE_ARGUMENTS(3)
	REQUIRE_ARGUMENT_OBJECT(0, jsExecutorId)
	REQUIRE_ARGUMENT_OBJECT(1, jsSlaveId)
	REQUIRE_ARGUMENT_ARRAYBUFFER(2, jsData)

	mesos::ExecutorID executorId = CreateProtoMessage<mesos::ExecutorID>(jsExecutorId);
	mesos::SlaveID slaveId = CreateProtoMessage<mesos::SlaveID>(jsSlaveId);
	std::string data = ArrayBufferToString(jsData);

	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());
	driver->_schedulerDriver->sendFrameworkMessage(executorId, slaveId, data);
}

void NodeSchedulerDriver::ReconcileTasks(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	Nan::HandleScope scope;

	REQUIRE_ARGUMENTS(1)
	REQUIRE_ARGUMENT_ARRAY(0, jsStatuses)
	std::vector<mesos::TaskStatus> statuses = CreateProtoMessageVector<mesos::TaskStatus>(jsStatuses);

	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());
	driver->_schedulerDriver->reconcileTasks(statuses);
}
