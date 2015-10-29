#include "Common.hpp"

ScopedByteArray::ScopedByteArray(ByteArray* byteArray) {
	_byteArray = byteArray;
}

ScopedByteArray::~ScopedByteArray() {
	delete[] _byteArray->Data;
	delete _byteArray;
}

ByteArray* ScopedByteArray::Ptr() {
	return _byteArray;
}

ScopedByteArrayCollection::ScopedByteArrayCollection(ByteArrayCollection* byteArrayCollection) {
	_byteArrayCollection = byteArrayCollection;
}

ScopedByteArrayCollection::~ScopedByteArrayCollection() {
	int size = _byteArrayCollection->Size;
	ByteArray** items = _byteArrayCollection->Items;
	for (int i = 0; i < size; i++) {
		ByteArray* item = items[i];
		delete[] item->Data;
		delete item;
	}

	delete _byteArrayCollection;
}

ByteArrayCollection* ScopedByteArrayCollection::Ptr() {
	return _byteArrayCollection;
}

v8::Local<v8::Object> CreateBuffer(const std::string& str) {
	Nan::EscapableHandleScope scope;

	int size = str.size();
	char* data = str.c_str();
	v8::MaybeLocal<v8::Object> buffer = Nan::NewBuffer(data, size);   // buffer free callback is not required here
	if (buffer.IsEmpty())
		Nan::ThrowError(Nan::New("Could not create buffer for string.").ToLocalChecked());

	return scope.Escape(buffer.ToLocalChecked());
}

void BufferFreeCallback(char* data, void* hint) {
	delete[] data;
}

v8::Local<v8::Object> CreateProtoObject(const google::protobuf::Message& message, const v8::Local<v8::Object>& protosRoot,
		const std::string& protoClassPath) {
	Nan::EscapableHandleScope scope;

	v8::Local<v8::Object> proto = GetObjectForPath(protosRoot, protoClassPath);

	int size = message.ByteSize();
	char* data = new char[size];
	message.SerializeToArray(data, size);

	v8::MaybeLocal<v8::Object> buffer = Nan::NewBuffer(data, size, BufferFreeCallback, 0);

	v8::Local<v8::Value> argv[1] = { buffer };
	v8::Local<v8::Value> decodeResult = CallFunction(proto, "decode", 1, argv);

	v8::Local<v8::Object> result = v8::Local<v8::Object>::Cast(decodeResult);
	if (result.IsEmpty())
		Nan::ThrowError(Nan::New("Invalid decode result. Not an Object.").ToLocalChecked());

	return scope.Escape(result);
}

void EmitEvent(const v8::Local<v8::Object>& eventEmitter, const std::string& eventName, int argc, v8::Local<v8::Value> argv[]) {
	CallFunction(eventEmitter, "emit", argc, argv);
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
	for (int i = 0; i < parts.size(); i++) {
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

v8::Local<v8::Value> CallFunction(const v8::Local<v8::Object>& object, const std::string& functionName, int argc, v8::Local<v8::Value> argv[]) {
	Nan::EscapableHandleScope scope;

	v8::MaybeLocal<v8::Value> maybe = Nan::Get(object, Nan::New(functionName).ToLocalChecked());
	if (maybe.IsEmpty())
		Nan::ThrowError(Nan::New("Could not find function '" + functionName + "'.").ToLocalChecked());

	v8::Local<v8::Function> function = v8::Local<v8::Function>::Cast(maybe.ToLocalChecked());
	if (function.IsEmpty())
		Nan::ThrowError(Nan::New("Invalid property '" + functionName + "'. Not a function.").ToLocalChecked());

	v8::MaybeLocal<v8::Value> result = function->Call(v8::Isolate::GetCurrent()->GetCurrentContext()->Global(), object, argc, argv);

	return scope.Escape(result.ToLocalChecked());
}

namespace protobuf {

ScopedByteArray Serialize(const google::protobuf::Message& message) {
	int size = message.ByteSize();
	char *buffer = new char[size];

	message.SerializeToArray(buffer, size);

	ByteArray* byteArray = new ByteArray;
	byteArray->Size = size;
	byteArray->Data = buffer;

	ScopedByteArray result(byteArray);
	return result;
}
}
