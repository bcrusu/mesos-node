#include "NodeExecutorDriver.hpp"
#include "Common.hpp"

Nan::Persistent<v8::Function> NodeExecutorDriver::_constructor;

NodeExecutorDriver::NodeExecutorDriver(v8::Object jsExecutor) :
		_executor(new NodeExecutor(jsExecutor)), _executorDriver(new MesosExecutorDriver(_executor)) {
}

NodeExecutorDriver::~NodeExecutorDriver() {
	//TODO: free _executorDriver
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
	//TODO
}

void NodeExecutorDriver::Stop(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	//TODO
}

void NodeExecutorDriver::Abort(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	//TODO
}

void NodeExecutorDriver::Join(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	//TODO
}

void NodeExecutorDriver::Run(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	//TODO
}

void NodeExecutorDriver::SendStatusUpdate(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	//TODO
}

void NodeExecutorDriver::SendFrameworkMessage(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	//TODO
}
