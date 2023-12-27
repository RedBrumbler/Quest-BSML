#pragma once

#include "beatsaber-hook/shared/utils/typedefs.h"
#include "beatsaber-hook/shared/utils/il2cpp-type-check.hpp"
#include "System/Collections/Generic/List_1.hpp"
#include "System/String.hpp"

namespace BSML {
    template<typename T>
    struct SListW : public ListW<T, System::Collections::Generic::List_1<T>*> {
        using Base = ListW<T, System::Collections::Generic::List_1<T>*>;
        using ListW<T, System::Collections::Generic::List_1<T>*>::ListW;

        constexpr SListW(ListW<T> i) : ListW<T, System::Collections::Generic::List_1<T>*>(i) {}

        constexpr inline operator ListW<T>() const noexcept {
            return ListW<T>(this->convert());
        }

        static SListW New_ctor() {
            return SListW(System::Collections::Generic::List_1<T>::New_ctor());
        }
    };
    static_assert(sizeof(SListW<int>) == sizeof(void*));

    struct SStringW : public StringWrapper<System::String*> {
        using StringWrapper<System::String*>::StringWrapper;

        constexpr SStringW(StringW i) noexcept : StringWrapper<System::String*>(i) {}

        constexpr inline operator StringW() const noexcept {
            return StringW(this->convert());
        }
    };
    static_assert(sizeof(SStringW) == sizeof(void*));
}
MARK_GEN_REF_T(BSML::SListW);
MARK_REF_T(BSML::SStringW);

static_assert(il2cpp_utils::has_il2cpp_conversion<BSML::SListW<int>>);
static_assert(il2cpp_utils::has_il2cpp_conversion<BSML::SStringW>);

template <class T>
struct BS_HOOKS_HIDDEN ::il2cpp_utils::il2cpp_type_check::need_box<BSML::SListW<T>> {
    constexpr static bool value = false;
};

template<class T>
struct ::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<BSML::SListW<T>> {
    static inline Il2CppClass* get() {
        return classof(typename BSML::SListW<T>::Base);
    }
};

template <>
struct BS_HOOKS_HIDDEN ::il2cpp_utils::il2cpp_type_check::need_box<BSML::SStringW> {
    constexpr static bool value = false;
};

template<>
struct ::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<BSML::SStringW> {
    static inline Il2CppClass* get() {
        return classof(System::String*);
    }
};
