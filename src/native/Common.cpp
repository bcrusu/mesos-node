#include <sstream>
#include "Common.hpp"

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
		if (maybeValue.IsEmpty())
			Nan::ThrowError(Nan::New("Could not find path object '" + part + "'.").ToLocalChecked());

		v8::MaybeLocal<v8::Object> maybeObject = v8::Local<v8::Object>::Cast(maybeValue.ToLocalChecked());
		if (maybeObject.IsEmpty())
			Nan::ThrowError(Nan::New("Path is not an object '" + path + "'.").ToLocalChecked());

		currentValue = maybeObject.ToLocalChecked();
	}

	return scope.Escape(currentValue);
}

void BufferFreeCallback(char* data, void* hint) {
	delete[] data;
}

v8::Local<v8::Object> CreateBuffer(const std::string& str) {
	Nan::EscapableHandleScope scope;

	int size = str.size();
	char* data = (char*)str.c_str();

	v8::MaybeLocal<v8::Object> buffer = Nan::NewBuffer(data, size);
	if (buffer.IsEmpty())
		Nan::ThrowError(Nan::New("Could not create buffer for string.").ToLocalChecked());

	return scope.Escape(buffer.ToLocalChecked());
}

v8::Local<v8::Object> CreateProtoObject(const google::protobuf::Message& message, const v8::Local<v8::Object>& protosRoot,
		const std::string& protoClassPath) {
	Nan::EscapableHandleScope scope;

	v8::Local<v8::Object> proto = GetObjectForPath(protosRoot, protoClassPath);

	int size = message.ByteSize();
	char* data = new char[size];
	message.SerializeToArray(data, size);

	v8::MaybeLocal<v8::Object> buffer = Nan::NewBuffer(data, size, BufferFreeCallback, 0);
	assert(!buffer.IsEmpty());

	v8::Local<v8::Value> argv[1] = { buffer.ToLocalChecked() };
	v8::Local<v8::Value> decodeResult = CallFunction(proto, "decode", 1, argv);

	v8::Local<v8::Object> result = v8::Local<v8::Object>::Cast(decodeResult);
	if (result.IsEmpty())
		Nan::ThrowError(Nan::New("Invalid decode result. Not an Object.").ToLocalChecked());

	return scope.Escape(result);
}

void EmitEvent(const v8::Local<v8::Object>& eventEmitter, const std::string& eventName, int argc, v8::Local<v8::Value> argv[]) {
	CallFunction(eventEmitter, "emit", argc, argv);
}

v8::Local<v8::Value> CallFunction(const v8::Local<v8::Object>& object, const std::string& functionName, int argc, v8::Local<v8::Value> argv[]) {
	Nan::EscapableHandleScope scope;

	v8::MaybeLocal<v8::Value> maybe = Nan::Get(object, Nan::New(functionName).ToLocalChecked());
	if (maybe.IsEmpty())
		Nan::ThrowError(Nan::New("Could not find function '" + functionName + "'.").ToLocalChecked());

	v8::Local<v8::Function> function = v8::Local<v8::Function>::Cast(maybe.ToLocalChecked());
	if (function.IsEmpty())
		Nan::ThrowError(Nan::New("Invalid property '" + functionName + "'. Not a function.").ToLocalChecked());

	v8::MaybeLocal<v8::Value> result = function->Call(v8::Isolate::GetCurrent()->GetCurrentContext(), object, argc, argv);

	return scope.Escape(result.ToLocalChecked());
}

v8::Local<v8::Value> CallFunction(const v8::Local<v8::Object>& object, const std::string& functionName) {
	v8::Local<v8::Value> argv[0] = {};
	return CallFunction(object, functionName, 0, argv);
}
