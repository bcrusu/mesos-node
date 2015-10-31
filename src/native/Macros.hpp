#ifndef MACROS_HPP_
#define MACROS_HPP_

#define REQUIRE_ARGUMENTS(n)                                                   \
    if (info.Length() != (n)) {                                                \
        return Nan::ThrowTypeError("Expected " #n "arguments");                \
    }

#define REQUIRE_ARGUMENTS_OR(n1, n2)                                           \
    if (info.Length() != (n1) && info.Length() != (n2)) {                      \
        return Nan::ThrowTypeError("Expected " #n1 " or " #n2 "arguments");    \
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

#define REQUIRE_ARGUMENT_ARRAYBUFFER(i, var)                                   \
    if (info.Length() <= (i) || !info[i]->IsArrayBuffer()) {                   \
        return Nan::ThrowTypeError("Argument " #i " must be an array buffer.");\
    }                                                                          \
    v8::Local<v8::ArrayBuffer> var = v8::Local<v8::ArrayBuffer>::Cast(info[i]);

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

#endif /* MACROS_HPP_ */
