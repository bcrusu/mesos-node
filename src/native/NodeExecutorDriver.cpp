#include "NodeExecutorDriver.hpp"
#include "Common.hpp"

NodeExecutorDriver::NodeExecutorDriver(NodeExecutor* executor) :
		_executor(executor), _executorDriver(new MesosExecutorDriver(_executor)) {
}

NodeExecutorDriver::~NodeExecutorDriver() {
	delete _executorDriver;
	delete _executor;
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
	driver->_executorDriver->start();
}

void NodeExecutorDriver::Stop(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS(0)
	NodeExecutorDriver* driver = ObjectWrap::Unwrap<NodeExecutorDriver>(info.Holder());
	driver->_executorDriver->stop();
}

void NodeExecutorDriver::Abort(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS(0)
	NodeExecutorDriver* driver = ObjectWrap::Unwrap<NodeExecutorDriver>(info.Holder());
	driver->_executorDriver->abort();
}

void NodeExecutorDriver::Join(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS(0)
	NodeExecutorDriver* driver = ObjectWrap::Unwrap<NodeExecutorDriver>(info.Holder());
	driver->_executorDriver->join();
}

void NodeExecutorDriver::Run(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS(0)
	NodeExecutorDriver* driver = ObjectWrap::Unwrap<NodeExecutorDriver>(info.Holder());
	driver->_executorDriver->run();
}

void NodeExecutorDriver::SendStatusUpdate(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	Nan::HandleScope scope;

	REQUIRE_ARGUMENTS(1)
	REQUIRE_ARGUMENT_OBJECT(0, jsTaskStatus)
	mesos::TaskStatus taskStatus = CreateProtoMessage<mesos::TaskStatus>(jsTaskStatus);

	NodeExecutorDriver* driver = ObjectWrap::Unwrap<NodeExecutorDriver>(info.Holder());
	driver->_executorDriver->sendStatusUpdate(taskStatus);
}

void NodeExecutorDriver::SendFrameworkMessage(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	Nan::HandleScope scope;

	REQUIRE_ARGUMENTS(1)
	REQUIRE_ARGUMENT_ARRAYBUFFER(0, jsMessage)
	std::string message = ArrayBufferToString(jsMessage);

	NodeExecutorDriver* driver = ObjectWrap::Unwrap<NodeExecutorDriver>(info.Holder());
	driver->_executorDriver->sendFrameworkMessage(message);
}
