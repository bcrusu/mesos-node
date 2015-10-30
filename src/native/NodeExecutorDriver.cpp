#include "NodeExecutorDriver.hpp"
#include "Common.hpp"

NodeExecutorDriver::NodeExecutorDriver(v8::Local<v8::Object> jsExecutor) :
		_executor(new NodeExecutor(jsExecutor, this)), _executorDriver(new MesosExecutorDriver(_executor)) {
}

NodeExecutorDriver::~NodeExecutorDriver() {
	delete _executor;
	delete _executorDriver;
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
	REQUIRE_ARGUMENTS(1)

	if (info.IsConstructCall()) {
		REQUIRE_ARGUMENT_OBJECT(0, executor)

		NodeExecutorDriver* driver = new NodeExecutorDriver(executor);
		driver->Wrap(info.This());
		info.GetReturnValue().Set(info.This());
	} else {
		const int argc = 1;
		v8::Local<v8::Value> argv[argc] = { info[0] };
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
	REQUIRE_ARGUMENTS(1)
	NodeExecutorDriver* driver = ObjectWrap::Unwrap<NodeExecutorDriver>(info.Holder());
	//TODO:
	//driver->_executorDriver->sendStatusUpdate();
}

void NodeExecutorDriver::SendFrameworkMessage(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	REQUIRE_ARGUMENTS(1)
	NodeExecutorDriver* driver = ObjectWrap::Unwrap<NodeExecutorDriver>(info.Holder());
	//TODO:
	//driver->_executorDriver->sendFrameworkMessage();
}
