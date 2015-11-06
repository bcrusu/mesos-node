#include <sstream>
#include "Common.hpp"

namespace mesosNode {

void KickNextTick(){
	Nan::HandleScope scope;
	Nan::Callback(Nan::New<v8::Function>([](const Nan::FunctionCallbackInfo<v8::Value>& info){}, Nan::Null())).Call(0, nullptr);
}

std::string ArrayBufferToString(v8::Local<v8::ArrayBuffer> arrayBuffer) {
	v8::ArrayBuffer::Contents contents = arrayBuffer->GetContents();
	int size = contents.ByteLength();
	char* data = (char*) contents.Data();

	std::string result(data, size);
	return result;
}

std::vector<std::string> SplitString(const std::string &s, char delim) {
	std::vector<std::string> result;
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		result.push_back(item);
	}

	return result;
}

v8::Local<v8::Object> GetObjectForPath(const v8::Local<v8::Object>& root, const std::string& path) {
	Nan::EscapableHandleScope scope;

	std::vector<std::string> parts = SplitString(path, '.');

	v8::Local<v8::Object> currentValue = root;
	for (unsigned int i = 0; i < parts.size(); i++) {
		std::string part = parts[i];

		v8::MaybeLocal<v8::Value> maybeValue = Nan::Get(currentValue, Nan::New(part).ToLocalChecked());
		assert(!maybeValue.IsEmpty());

		v8::MaybeLocal<v8::Object> maybeObject = v8::Local<v8::Object>::Cast(maybeValue.ToLocalChecked());
		assert(!maybeObject.IsEmpty());

		currentValue = maybeObject.ToLocalChecked();
	}

	return scope.Escape(currentValue);
}

//TODO: verify
void BufferFreeCallback(char* data, void* hint) {
	if (hint) {
		delete[] data;
	}
}

v8::Local<v8::Object> CreateBuffer(const std::string& str) {
	Nan::EscapableHandleScope scope;

	int size = str.size();
	char* data = (char*) str.c_str();

	v8::MaybeLocal<v8::Object> buffer = Nan::NewBuffer(data, size, BufferFreeCallback, NULL);
	assert(!buffer.IsEmpty());

	return scope.Escape(buffer.ToLocalChecked());
}

v8::Local<v8::Object> CreateProtoObject(const google::protobuf::Message& message, const v8::Local<v8::Object>& protosRoot,
		const std::string& protoClassPath) {
	Nan::EscapableHandleScope scope;

	v8::Local<v8::Object> proto = GetObjectForPath(protosRoot, protoClassPath);

	int size = message.ByteSize();
	char* data = new char[size];
	message.SerializeToArray(data, size);

	v8::MaybeLocal<v8::Object> buffer = Nan::NewBuffer(data, size, BufferFreeCallback, data);
	assert(!buffer.IsEmpty());

	v8::Local<v8::Value> argv[1] = { buffer.ToLocalChecked() };
	v8::Local<v8::Value> decodeResult = CallFunction(proto, "decode", 1, argv);

	v8::Local<v8::Object> result = v8::Local<v8::Object>::Cast(decodeResult);
	assert(!result.IsEmpty());

	return scope.Escape(result);
}

void EmitEvent(const Nan::Persistent<v8::Object>& eventEmitter, const std::string& eventName, int argc, v8::Local<v8::Value> argv[]) {
	Nan::HandleScope scope;

	int emitArgc = argc + 1;
	v8::Local<v8::Value> emitArgv[emitArgc];

	emitArgv[0] = Nan::New(eventName).ToLocalChecked();
	for (int i = 0; i < argc; i++) {
		emitArgv[i + 1] = argv[i];
	}

	CallFunction(Nan::New(eventEmitter), "emit", emitArgc, emitArgv);
}

v8::Local<v8::Value> CallFunction(const v8::Local<v8::Object>& object, const std::string& functionName, int argc, v8::Local<v8::Value> argv[]) {
	Nan::EscapableHandleScope scope;
	v8::Isolate* isolate = v8::Isolate::GetCurrent();

	v8::MaybeLocal<v8::Value> maybeFunction = Nan::Get(object, Nan::New(functionName).ToLocalChecked());
	assert(!maybeFunction.IsEmpty());

	v8::Local<v8::Function> function = v8::Local<v8::Function>::Cast(maybeFunction.ToLocalChecked());
	assert(!function.IsEmpty());

	v8::MaybeLocal<v8::Value> maybeResult = function->Call(isolate->GetCurrentContext(), object, argc, argv);

	if (!maybeResult.IsEmpty()) {
		return scope.Escape(maybeResult.ToLocalChecked());
	} else {
		// dummy result for void functions
		return scope.Escape(v8::Null(isolate));
	}
}

v8::Local<v8::Value> CallFunction(const v8::Local<v8::Object>& object, const std::string& functionName) {
	v8::Local<v8::Value> argv[0] = { };
	return CallFunction(object, functionName, 0, argv);
}

}
