#ifndef NODEEXECUTORDRIVER_HPP_
#define NODEEXECUTORDRIVER_HPP_

#include <nan.h>
#include <mesos/executor.hpp>
#include "NodeExecutor.hpp"

using namespace mesos;

namespace mesosNode {

class NodeExecutorDriver: public Nan::ObjectWrap {
public:
	static void Init(v8::Local<v8::Object> exports);

private:
	explicit NodeExecutorDriver(NodeExecutor* executor);
	~NodeExecutorDriver();

	static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);
	static void Start(const Nan::FunctionCallbackInfo<v8::Value>& info);
	static void Stop(const Nan::FunctionCallbackInfo<v8::Value>& info);
	static void Abort(const Nan::FunctionCallbackInfo<v8::Value>& info);
	static void Join(const Nan::FunctionCallbackInfo<v8::Value>& info);
	static void Run(const Nan::FunctionCallbackInfo<v8::Value>& info);
	static void SendStatusUpdate(const Nan::FunctionCallbackInfo<v8::Value>& info);
	static void SendFrameworkMessage(const Nan::FunctionCallbackInfo<v8::Value>& info);

	static v8::Local<v8::Value> MesosStatusToJs(mesos::Status status);

	static Nan::Persistent<v8::Function> _constructor;
	NodeExecutor* _executor;
	MesosExecutorDriver* _executorDriver;
};

}

#endif /* NODEEXECUTORDRIVER_HPP_ */
