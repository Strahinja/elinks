#ifndef EL__JS_MUJS_NODELIST_H
#define EL__JS_MUJS_NODELIST_H

#include <mujs.h>

#ifdef __cplusplus
extern "C" {
#endif

void mjs_push_nodelist(js_State *J, void *node);

#ifdef __cplusplus
}
#endif

#endif