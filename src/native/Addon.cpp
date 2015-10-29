#include <nan.h>
#include "NodeSchedulerDriver.hpp"
#include "NodeExecutorDriver.hpp"

void InitAll(v8::Local<v8::Object> exports, v8::Local<v8::Object> module) {
	NodeSchedulerDriver::Init(exports);
	NodeExecutorDriver::Init(exports);
}

NODE_MODULE(mesosApi, InitAll)
