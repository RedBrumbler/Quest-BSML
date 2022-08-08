#pragma once


// Use this macro in combination with BSML settings to declare the proper setters and getters, make sure that the id of the setting is the same as what you pass as name
#define BSML_PROPERTY(type, name)                                                                              \
DECLARE_INSTANCE_FIELD(type, _##name);                                                                              \
public:                                                                                                                 \
type get_##name();                                                                                                      \
___CREATE_INSTANCE_METHOD(get_##name, "get_" #name, METHOD_ATTRIBUTE_PUBLIC | METHOD_ATTRIBUTE_HIDE_BY_SIG, nullptr);   \
void set_##name(type value);                                                                                            \
___CREATE_INSTANCE_METHOD(set_##name, "set_" #name, METHOD_ATTRIBUTE_PUBLIC | METHOD_ATTRIBUTE_HIDE_BY_SIG, nullptr)

/// method to be used by BSML_OPTIONS_LIST to convert the given options into an on demand getter for options
template<typename T>
inline List<T>* initializer_list_to_List(std::initializer_list<std::string> list) {
    auto result = List<T>::New_ctor();
    result->EnsureCapacity(list.size());
    for (auto& v : list) result->Add(StringW(v));
    return result;
}

// to be used with the various lists in BSML, pass the options as a list of strings, e.g. BSML_OPTIONS_LIST_OBJECT(lyrics, "Never", "Gonna", "Give", "You", "Up");
// the id of the list is the same as what you use for options="listid" in BSML, make sure your IDs are valid c++ identifiers!
#define BSML_OPTIONS_LIST_OBJECT(choices_id, ...) \
public: \
List<Il2CppObject*>* get_##choices_id() { return initializer_list_to_List<Il2CppObject*>({__VA_ARGS__}); };\
___CREATE_INSTANCE_METHOD(get_ ##choices_id, "get_" #choices_id, METHOD_ATTRIBUTE_PUBLIC | METHOD_ATTRIBUTE_HIDE_BY_SIG, nullptr)

// same as BSML_OPTIONS_LIST_OBJECT but returns a List<StringW>* instead of a List<Il2CppObject*>*
#define BSML_OPTIONS_LIST_STRING(choices_id, ...) \
public: \
List<StringW>* get_##choices_id() { return initializer_list_to_List<StringW>({__VA_ARGS__}); };\
___CREATE_INSTANCE_METHOD(get_ ##choices_id, "get_" #choices_id, METHOD_ATTRIBUTE_PUBLIC | METHOD_ATTRIBUTE_HIDE_BY_SIG, nullptr)