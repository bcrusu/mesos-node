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
	delete _scheduler;
	delete _schedulerDriver;
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
	int argc = info.Length();

	if (argc < 5 || argc > 6)
		return Nan::ThrowTypeError("Wrong number of arguments.");

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
	REQUIRE_ARGUMENTS(0)
	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());
	driver->_schedulerDriver->stop();
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
	REQUIRE_ARGUMENTS(1)
	REQUIRE_ARGUMENT_ARRAY(0, requests)

	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());

	//TODO:
	//driver->_schedulerDriver->requestResources();
}

void NodeSchedulerDriver::LaunchTasks(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS(1)
	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());
	//TODO:
	//driver->_schedulerDriver->launchTasks();
}

void NodeSchedulerDriver::KillTask(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS(1)
	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());
	//TODO:
	//driver->_schedulerDriver->killTask();
}

void NodeSchedulerDriver::AcceptOffers(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS(1)
	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());
	//TODO:
	//driver->_schedulerDriver->acceptOffers();
}

void NodeSchedulerDriver::DeclineOffer(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS(1)
	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());
	//TODO:
	//driver->_schedulerDriver->declineOffer();
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
	REQUIRE_ARGUMENTS(1)
	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());
	//TODO:
	//driver->_schedulerDriver->acknowledgeStatusUpdate();
}

void NodeSchedulerDriver::SendFrameworkMessage(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS(1)
	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());
	//TODO:
	//driver->_schedulerDriver->sendFrameworkMessage();
}

void NodeSchedulerDriver::ReconcileTasks(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS(1)
	NodeSchedulerDriver* driver = ObjectWrap::Unwrap<NodeSchedulerDriver>(info.Holder());
	//TODO:
	//driver->_schedulerDriver->reconcileTasks();
}
