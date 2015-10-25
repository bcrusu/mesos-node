#ifndef COMMON_HPP_
#define COMMON_HPP_

#include <google/protobuf/message.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

struct ByteArray {
public:
	int Size;
	const char *Data;
};

struct ByteArrayCollection {
public:
	int Size;
	ByteArray **Items;
};

class ScopedByteArray {
public:
	ScopedByteArray(ByteArray* byteArray);
	~ScopedByteArray();

	ByteArray* Ptr();

private:
	ByteArray* _byteArray;
};

class ScopedByteArrayCollection {
public:
	ScopedByteArrayCollection(ByteArrayCollection* byteArrayCollection);
	~ScopedByteArrayCollection();

	ByteArrayCollection* Ptr();

private:
	ByteArrayCollection* _byteArrayCollection;
};

ByteArray StringToByteArray(const std::string& str);

namespace protobuf {

ScopedByteArray Serialize(const google::protobuf::Message& message);

template<class T>
ScopedByteArrayCollection SerializeVector(const std::vector<T>& vector) {
	typedef typename std::vector<T>::size_type vector_size_type;

	ByteArrayCollection* collection = new ByteArrayCollection;
	collection->Size = vector.size();
	ByteArray** items = new ByteArray*[vector.size()];

	for (vector_size_type i = 0; i < vector.size(); i++) {
		T item = vector[i];
		int size = item.ByteSize();
		char *buffer = new char[size];

		item.SerializeToArray(buffer, size);

		ByteArray* byteArray = new ByteArray;
		byteArray->Size = size;
		byteArray->Data = buffer;

		items[i] = byteArray;
	}

	collection->Items = items;

	ScopedByteArrayCollection result(collection);
	return result;
}

template<class T>
T Deserialize(ByteArray* bytes) {
	assert(bytes);
	google::protobuf::io::ArrayInputStream stream(bytes->Data, bytes->Size);
	T result;
	bool parsed = result.ParseFromZeroCopyStream(&stream);
	assert(parsed);
	return result;
}

template<class T>
std::vector<T> DeserializeVector(ByteArrayCollection* collection) {
	int size = collection->Size;
	ByteArray** items = (ByteArray**) collection->Items;

	std::vector<T> result;
	for (int i = 0; i < size; i++) {
		ByteArray* itemBytes = items[i];
		const T& item = Deserialize<T>(itemBytes);
		result.push_back(item);
	}

	return result;
}

}

#define REQUIRE_ARGUMENTS(n)                                                   \
    if (info.Length() != (n)) {                                                \
        return Nan::ThrowTypeError("Expected " #n "arguments");                \
    }

#define REQUIRE_ARGUMENT_FUNCTION(i, var)                                      \
    if (info.Length() <= (i) || !info[i]->IsFunction()) {                      \
        return Nan::ThrowTypeError("Argument " #i " must be a function");      \
    }                                                                          \
    Local<v8::Function> var = Local<v8::Function>::Cast(info[i]);

#define REQUIRE_ARGUMENT_OBJECT(i, var)                                        \
    if (info.Length() <= (i) || !info[i]->IsObject()) {                        \
        return Nan::ThrowTypeError("Argument " #i " must be an object");       \
    }                                                                          \
    Local<v8::Object> var = Local<v8::Object>::Cast(info[i]);


#define REQUIRE_ARGUMENT_STRING(i, var)                                        \
    if (info.Length() <= (i) || !info[i]->IsString()) {                        \
        return Nan::ThrowTypeError("Argument " #i " must be a string");        \
    }                                                                          \
    Nan::Utf8String var(info[i]);

#endif /* COMMON_HPP_ */
