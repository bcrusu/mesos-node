#include "NodeExecutorDriver.hpp"
#include "Common.hpp"
#include "Macros.hpp"
#include "NodeAsyncWorker.hpp"

Nan::Persistent<v8::Function> NodeExecutorDriver::_constructor;

NodeExecutorDriver::NodeExecutorDriver(NodeExecutor* executor) :
		_executor(executor), _executorDriver(new MesosExecutorDriver(_executor)) {
}

NodeExecutorDriver::~NodeExecutorDriver() {
	delete _executorDriver;
	delete _executor;
}

v8::Local<v8::Value> NodeExecutorDriver::MesosStatusToJs(mesos::Status status){
	return Nan::New(status);  //TODO: convert to proper Mesos proto object (i.e. not Int32)
}

void NodeExecutorDriver::Init(v8::Local<v8::Object> exports) {
	Nan::HandleScope scope;

	// constructor template
	v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
	tpl->SetClassName(Nan::New("MesosExecutorDriver").ToLocalChecked());
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	// prototype
	Nan::SetPrototypeMethod(tpl, "start", Start);
	Nan::SetPrototypeMethod(tpl, "stop", Stop);
	Nan::SetPrototypeMethod(tpl, "abort", Abort);
	Nan::SetPrototypeMethod(tpl, "join", Join);
	Nan::SetPrototypeMethod(tpl, "run", Run);
	Nan::SetPrototypeMethod(tpl, "sendStatusUpdate", SendStatusUpdate);
	Nan::SetPrototypeMethod(tpl, "sendFrameworkMessage", SendFrameworkMessage);

	_constructor.Reset(tpl->GetFunction());
	exports->Set(Nan::New("MesosExecutorDriver").ToLocalChecked(), tpl->GetFunction());
}

void NodeExecutorDriver::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS(2)

	Nan::HandleScope scope;

	if (info.IsConstructCall()) {
		REQUIRE_ARGUMENT_OBJECT(0, jsProtosBuilder)
		REQUIRE_ARGUMENT_OBJECT(1, jsExecutor)
		v8::Local<v8::Object> jsExecutorDriver = info.This();

		NodeExecutor* executor = new NodeExecutor(jsExecutorDriver, jsExecutor, jsProtosBuilder);
		NodeExecutorDriver* executorDriver = new NodeExecutorDriver(executor);

		executorDriver->Wrap(jsExecutorDriver);
		info.GetReturnValue().Set(jsExecutorDriver);
	} else {
		const int argc = 2;
		v8::Local<v8::Value> argv[argc] = { info[0], info[1] };
		v8::Local<v8::Function> cons = Nan::New<v8::Function>(_constructor);
		info.GetReturnValue().Set(cons->NewInstance(argc, argv));
	}
}

void NodeExecutorDriver::Start(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS(0)
	NodeExecutorDriver* driver = ObjectWrap::Unwrap<NodeExecutorDriver>(info.Holder());

	auto worker = new NodeAsyncWorker<mesos::Status>([driver] {return driver->_executorDriver->start();}, MesosStatusToJs);
	worker->Run();
	info.GetReturnValue().Set(worker->GetPromise());
}

void NodeExecutorDriver::Stop(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS(0)
	NodeExecutorDriver* driver = ObjectWrap::Unwrap<NodeExecutorDriver>(info.Holder());

	auto worker = new NodeAsyncWorker<mesos::Status>([driver] {return driver->_executorDriver->stop();}, MesosStatusToJs);
	worker->Run();
	info.GetReturnValue().Set(worker->GetPromise());
}

void NodeExecutorDriver::Abort(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS(0)
	NodeExecutorDriver* driver = ObjectWrap::Unwrap<NodeExecutorDriver>(info.Holder());

	auto worker = new NodeAsyncWorker<mesos::Status>([driver] {return driver->_executorDriver->abort();}, MesosStatusToJs);
	worker->Run();
	info.GetReturnValue().Set(worker->GetPromise());
}

void NodeExecutorDriver::Join(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS(0)
	NodeExecutorDriver* driver = ObjectWrap::Unwrap<NodeExecutorDriver>(info.Holder());

	auto worker = new NodeAsyncWorker<mesos::Status>([driver] {return driver->_executorDriver->join();}, MesosStatusToJs);
	worker->Run();
	info.GetReturnValue().Set(worker->GetPromise());
}

void NodeExecutorDriver::Run(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS(0)
	NodeExecutorDriver* driver = ObjectWrap::Unwrap<NodeExecutorDriver>(info.Holder());

	auto worker = new NodeAsyncWorker<mesos::Status>([driver] {return driver->_executorDriver->run();}, MesosStatusToJs);
	worker->Run();
	info.GetReturnValue().Set(worker->GetPromise());
}

void NodeExecutorDriver::SendStatusUpdate(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	Nan::HandleScope scope;
	NodeExecutorDriver* driver = ObjectWrap::Unwrap<NodeExecutorDriver>(info.Holder());

	REQUIRE_ARGUMENTS(1)
	REQUIRE_ARGUMENT_OBJECT(0, jsTaskStatus)
	mesos::TaskStatus taskStatus = CreateProtoMessage<mesos::TaskStatus>(jsTaskStatus);

	auto worker = new NodeAsyncWorker<mesos::Status>([driver, taskStatus] {return driver->_executorDriver->sendStatusUpdate(taskStatus);}, MesosStatusToJs);
	worker->Run();
	info.GetReturnValue().Set(worker->GetPromise());
}

void NodeExecutorDriver::SendFrameworkMessage(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	Nan::HandleScope scope;
	NodeExecutorDriver* driver = ObjectWrap::Unwrap<NodeExecutorDriver>(info.Holder());

	REQUIRE_ARGUMENTS(1)
	REQUIRE_ARGUMENT_ARRAYBUFFER(0, jsMessage)
	std::string message = ArrayBufferToString(jsMessage);

	auto worker = new NodeAsyncWorker<mesos::Status>([driver, message = std::move(message)] {return driver->_executorDriver->sendFrameworkMessage(message);}, MesosStatusToJs);
	worker->Run();
	info.GetReturnValue().Set(worker->GetPromise());
}
