#ifndef COMMON_HPP_
#define COMMON_HPP_

#include <string>
#include <google/protobuf/message.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <nan.h>

std::string ArrayBufferToString(v8::Local<v8::ArrayBuffer> arrayBuffer);

v8::Local<v8::Value> CallFunction(const v8::Local<v8::Object>& object, const std::string& functionName, int argc,
		v8::Local<v8::Value> argv[]);
v8::Local<v8::Value> CallFunction(const v8::Local<v8::Object>& object, const std::string& functionName);

v8::Local<v8::Object> CreateBuffer(const std::string& data);

void EmitEvent(const v8::Local<v8::Object>& eventEmitter, const std::string& eventName, int argc,
		v8::Local<v8::Value> argv[]);

v8::Local<v8::Object> CreateProtoObject(const google::protobuf::Message& message,
		const v8::Local<v8::Object>& protosRoot, const std::string& protoClassPath);

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

	Nan::TryCatch tryCatch;
	v8::Local<v8::Value> callResult = CallFunction(protoObject, "toArrayBuffer");
	v8::Local<v8::ArrayBuffer> arrayBuffer;

	if (!tryCatch.HasCaught()) {
		assert(!callResult.IsEmpty());
		arrayBuffer = v8::Local<v8::ArrayBuffer>::Cast(callResult);
	} else {
		v8::Local<v8::Value> exception = tryCatch.Exception();
		if (exception->IsObject()) {
			v8::Local<v8::Object> exceptionObject = v8::Local<v8::Object>::Cast(exception);
			v8::MaybeLocal<v8::Value> encodedMaybe = Nan::Get(exceptionObject, Nan::New("encoded").ToLocalChecked());
			if (!encodedMaybe.IsEmpty()) {
				arrayBuffer = v8::Local<v8::ArrayBuffer>::Cast(encodedMaybe.ToLocalChecked());
			}
		}

		tryCatch.Reset();
	}

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

#endif /* COMMON_HPP_ */
