#ifndef COMMON_HPP_
#define COMMON_HPP_

#include <string>
#include <google/protobuf/message.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <nan.h>

v8::Local<v8::Value> CallFunction(const v8::Local<v8::Object>& object, const std::string& functionName, int argc, v8::Local<v8::Value> argv[]);
v8::Local<v8::Value> CallFunction(const v8::Local<v8::Object>& object, const std::string& functionName);

v8::Local<v8::Object> CreateBuffer(const std::string& data);

void EmitEvent(const v8::Local<v8::Object>& eventEmitter, const std::string& eventName, int argc, v8::Local<v8::Value> argv[]);

v8::Local<v8::Object> CreateProtoObject(const google::protobuf::Message& message, const v8::Local<v8::Object>& protosRoot,
		const std::string& protoClassPath);

template<class T>
v8::Local<v8::Array> CreateProtoObjectArray(const std::vector<T>& messages, const v8::Local<v8::Object>& protosRoot,
		const std::string& protoClassPath) {
	Nan::EscapableHandleScope scope;

	int size = messages.size();
	v8::Local<v8::Array> result = v8::Array::New(v8::Isolate::GetCurrent(), size);

	for (int i = 0; i < size; i++) {
		T message = messages[i];
		v8::Local<v8::Object> object = CreateProtoObject(message, protosRoot, protoClassPath);
		result->Set(i, object);
	}

	return scope.Escape(result);
}

template<class T>
T CreateProtoMessage(const v8::Local<v8::Object>& protoObject) {
	Nan::HandleScope scope;

	assert(!protoObject.IsEmpty());

	v8::Local<v8::Value> callResult = CallFunction(protoObject, "toArrayBuffer");
	assert(!callResult.IsEmpty());

	v8::Local<v8::ArrayBuffer> arrayBuffer = v8::Local<v8::ArrayBuffer>::Cast(callResult);
	assert(!arrayBuffer.IsEmpty());

	v8::ArrayBuffer::Contents contents = arrayBuffer->GetContents();
	int size = contents.ByteLength();
	char* data = (char*) contents.Data();

	google::protobuf::io::ArrayInputStream stream(data, size);
	T result;
	bool parsed = result.ParseFromZeroCopyStream(&stream);
	assert(parsed);
	return result;
}

template<class T>
std::vector<T> CreateProtoMessageVector(const v8::Local<v8::Array>& protoObjectArray) {
	int size = protoObjectArray->Length();

	std::vector<T> result;
	for (int i = 0; i < size; i++) {
		v8::Local<v8::Value> item = protoObjectArray->Get(i);
		v8::Local<v8::Object> protoObject = v8::Local<v8::Object>::Cast(item);
		assert(!protoObject.IsEmpty());

		T message = CreateProtoMessage<T>(protoObject);
		result.push_back(message);
	}

	return result;
}

#define REQUIRE_ARGUMENTS(n)                                                   \
    if (info.Length() != (n)) {                                                \
        return Nan::ThrowTypeError("Expected " #n "arguments");                \
    }

#define REQUIRE_ARGUMENT_FUNCTION(i, var)                                      \
    if (info.Length() <= (i) || !info[i]->IsFunction()) {                      \
        return Nan::ThrowTypeError("Argument " #i " must be a function.");     \
    }                                                                          \
	v8::Local<v8::Function> var = v8::Local<v8::Function>::Cast(info[i]);

#define REQUIRE_ARGUMENT_OBJECT(i, var)                                        \
    if (info.Length() <= (i) || !info[i]->IsObject()) {                        \
        return Nan::ThrowTypeError("Argument " #i " must be an object.");      \
    }                                                                          \
    v8::Local<v8::Object> var = v8::Local<v8::Object>::Cast(info[i]);

#define REQUIRE_ARGUMENT_ARRAY(i, var)                                         \
    if (info.Length() <= (i) || !info[i]->IsArray()) {                         \
        return Nan::ThrowTypeError("Argument " #i " must be an array.");       \
    }                                                                          \
    v8::Local<v8::Array> var = v8::Local<v8::Array>::Cast(info[i]);

#define REQUIRE_ARGUMENT_BOOLEAN(i, var)                                       \
    if (info.Length() <= (i) || !info[i]->IsBoolean()) {                       \
        return Nan::ThrowTypeError("Argument " #i " must be a boolean.");      \
    }                                                                          \
    v8::Local<v8::Boolean> var = v8::Local<v8::Boolean>::Cast(info[i]);

#define REQUIRE_ARGUMENT_STRING(i, var)                                        \
    if (info.Length() <= (i) || !info[i]->IsString()) {                        \
        return Nan::ThrowTypeError("Argument " #i " must be a string.");       \
    }                                                                          \
    Nan::Utf8String var(info[i]);

#endif /* COMMON_HPP_ */
