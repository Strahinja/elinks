#ifndef EL__ECMASCRIPT_MUJS_SCREEN_H
#define EL__ECMASCRIPT_MUJS_SCREEN_H

#include <mujs.h>

struct ecmascript_interpreter;

int mjs_screen_init(struct ecmascript_interpreter *interpreter, js_State *J);

#endif