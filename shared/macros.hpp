#pragma once


// Use this macro in combination with BSML settings to declare the proper setters and getters, make sure that the id of the setting is the same as what you pass as name
#define BSML_PROPERTY(type, name)                                                                              \
DECLARE_INSTANCE_FIELD(type, _##name);                                                                              \
public:                                                                                                                 \
type get_##name() { return _##name; }                                                                               \
___CREATE_INSTANCE_METHOD(get_##name, "get_" #name, METHOD_ATTRIBUTE_PUBLIC | METHOD_ATTRIBUTE_HIDE_BY_SIG, nullptr);   \
void set_##name(type value) { _##name = value; }                                                                    \
___CREATE_INSTANCE_METHOD(set_##name, "set_" #name, METHOD_ATTRIBUTE_PUBLIC | METHOD_ATTRIBUTE_HIDE_BY_SIG, nullptr)

// The same as BSML_PROPERTY, but makes you define a name_changed method that is called when the value is changed
#define BSML_PROPERTY_ONCHANGED(type, name)                                                                    \
DECLARE_INSTANCE_FIELD(type, _##name);                                                                              \
public:                                                                                                                 \
type get_##name() { return _##name; }                                                                               \
___CREATE_INSTANCE_METHOD(get_##name, "get_" #name, METHOD_ATTRIBUTE_PUBLIC | METHOD_ATTRIBUTE_HIDE_BY_SIG, nullptr);   \
void set_##name(type value) { name##_changed(value); _##name = value; }                                             \
___CREATE_INSTANCE_METHOD(set_##name, "set_" #name, METHOD_ATTRIBUTE_PUBLIC | METHOD_ATTRIBUTE_HIDE_BY_SIG, nullptr);   \
void name##_changed(type value);                                                                                        \
___CREATE_INSTANCE_METHOD(name##_changed, #name "_changed", METHOD_ATTRIBUTE_PUBLIC | METHOD_ATTRIBUTE_HIDE_BY_SIG, nullptr)