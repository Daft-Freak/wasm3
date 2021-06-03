#pragma once
#include <cstdint>

#include "wasm3.h"

// this is stolen from platforms/cpp/wasm3_cpp/include/wasm3_cpp.h

typedef uint64_t *stack_type;
typedef void *mem_type;

template<typename T>
void arg_from_stack(T &dest, stack_type &_sp, mem_type mem) {
    m3ApiGetArg(T, tmp);
    dest = tmp;
}

template<typename T>
void arg_from_stack(T* &dest, stack_type &_sp, mem_type _mem) {
    m3ApiGetArgMem(T*, tmp);
    dest = tmp;
};

template<typename T>
void arg_from_stack(const T* &dest, stack_type &_sp, mem_type _mem) {
    m3ApiGetArgMem(const T*, tmp);
    dest = tmp;
};

template <typename ...Args>
static void get_args_from_stack(stack_type &sp, mem_type mem, std::tuple<Args...> &tuple) {
    std::apply([&](auto &... item) {
        (arg_from_stack(item, sp, mem), ...);
    }, tuple);
}

template<typename Func>
struct wrap_helper;

template <typename Ret, typename ...Args>
struct wrap_helper<Ret(Args...)> {
    using Func = Ret(Args...);
    static const void *wrap_fn(IM3Runtime rt, IM3ImportContext _ctx, stack_type _sp, mem_type mem) {
        std::tuple<Args...> args;
        // The order here matters: m3ApiReturnType should go before calling get_args_from_stack,
        // since both modify `_sp`, and the return value on the stack is reserved before the arguments.
        m3ApiReturnType(Ret);
        get_args_from_stack(_sp, mem, args);
        Func* function = reinterpret_cast<Func*>(_ctx->userdata);
        Ret r = std::apply(function, args);
        m3ApiReturn(r);
    }
};

template <typename ...Args>
struct wrap_helper<void(Args...)> {
    using Func = void(Args...);
    static const void *wrap_fn(IM3Runtime rt, IM3ImportContext _ctx, stack_type sp, mem_type mem) {
        std::tuple<Args...> args;
        get_args_from_stack(sp, mem, args);
        Func* function = reinterpret_cast<Func*>(_ctx->userdata);
        std::apply(function, args);
        m3ApiSuccess();
    }
};