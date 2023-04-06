#ifndef GLANG_BASE_MACROS_H
#define GLANG_BASE_MACROS_H

#define ENV_DEBUG
#undef  ENV_DEBUG

#define ENV_INSTALL
#undef  ENV_INSTALL

#define ENV_LOCAL
#undef  ENV_LOCAL

#define ENV_SAFE
#undef  ENV_SAFE


// pointers and memory
#define PTR_SIZE sizeof(void*)
#define FREE_BUFFER_ITEMS(b, l, t)      \
    for (Usize x1 = 0; x1 < l; x1++) {  \
        __free__##t(b[x1]);             \
    }
#define FREE_BUFFER_ITEMS_2(b, l, t)    \
    for (Usize x2 = 0; x2 < l; x2++) {  \
    }
#define CAST(type, expr) ((type)(expr))

// (struct) constructor / destructor / variants
#define CONSTRUCTOR(type, name, ...) type __new__##name(__VA_ARGS__)
#define VARIANT_CONSTRUCTOR(type, name, variant, ...) type __new__##name##__##variant(__VA_ARGS__)
#define DESTRUCTOR(name, ...) void __free__##name(__VA_ARGS__)
#define VARIANT_DESTRUCTOR(name, variant, ...) void __free__##name##__##variant(__VA_ARGS__)


#endif // GLANG_BASE_MACROS_H