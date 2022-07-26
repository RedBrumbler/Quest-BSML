#pragma once

        
#define GET_BSML_FLOAT_INDIRECT(identifier, store)  \
{                                                   \
    float temp_##store;                             \
    if (!GET_BSML_FLOAT(identifier, temp_##store))  \
        store = temp_##store;                       \
}

#define GET_BSML_FLOAT(identifier, store) elem.QueryFloatAttribute(identifier, &store)
#define GET_BSML_FLOAT_OPT(identifier, store) GET_BSML_FLOAT_INDIRECT(identifier, store)

#define GET_BSML_INT_INDIRECT(identifier, store)    \
{                                                   \
    int temp_##store;                               \
    if (!GET_BSML_INT(identifier, temp_##store))    \
        store = temp_##store;                       \
}

#define GET_BSML_INT(identifier, store) elem.QueryIntAttribute(identifier, &store)
#define GET_BSML_INT_OPT(identifier, store) GET_BSML_INT_INDIRECT(identifier, store)

#define GET_BSML_BOOL_INDIRECT(identifier, store)   \
{                                                   \
    bool temp_##store;                              \
    if (!GET_BSML_BOOL(identifier, temp_##store))   \
        store = temp_##store;                       \
}

#define GET_BSML_BOOL(identifier, store) elem.QueryBoolAttribute(identifier, &store)
#define GET_BSML_BOOL_OPT(identifier, store) GET_BSML_BOOL_INDIRECT(identifier, store)

#define GET_BSML_STRING(identifier, store)                      \
{                                                               \
    const char* temp_##store = nullptr;                         \
    if (!elem.QueryStringAttribute(identifier, &temp_##store))  \
        store = std::string_view(temp_##store);                 \
}