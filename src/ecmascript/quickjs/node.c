/* The QuickJS node implementation. */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef CONFIG_LIBDOM
#include <dom/dom.h>
#include <dom/bindings/hubbub/parser.h>
#endif

#include "elinks.h"

#include "ecmascript/ecmascript.h"
#include "ecmascript/quickjs/mapa.h"
#include "ecmascript/quickjs.h"
#include "ecmascript/quickjs/element.h"
#include "ecmascript/quickjs/nodelist.h"


#define countof(x) (sizeof(x) / sizeof((x)[0]))

static JSClassID js_node_class_id;

enum {
	ELEMENT_NODE = 1,
	ATTRIBUTE_NODE = 2,
	TEXT_NODE = 3,
	CDATA_SECTION_NODE = 4,
	PROCESSING_INSTRUCTION_NODE = 7,
	COMMENT_NODE = 8,
	DOCUMENT_NODE = 9,
	DOCUMENT_TYPE_NODE = 10,
	DOCUMENT_FRAGMENT_NODE = 11
};

static const JSCFunctionListEntry node_class_funcs[] = {
	JS_PROP_INT32_DEF("ELEMENT_NODE", ELEMENT_NODE, JS_PROP_ENUMERABLE),
	JS_PROP_INT32_DEF("ATTRIBUTE_NODE", ATTRIBUTE_NODE, JS_PROP_ENUMERABLE),
	JS_PROP_INT32_DEF("TEXT_NODE", TEXT_NODE, JS_PROP_ENUMERABLE),
	JS_PROP_INT32_DEF("CDATA_SECTION_NODE", CDATA_SECTION_NODE, JS_PROP_ENUMERABLE),
	JS_PROP_INT32_DEF("PROCESSING_INSTRUCTION_NODE", PROCESSING_INSTRUCTION_NODE, JS_PROP_ENUMERABLE),
	JS_PROP_INT32_DEF("COMMENT_NODE", COMMENT_NODE, JS_PROP_ENUMERABLE),
	JS_PROP_INT32_DEF("DOCUMENT_NODE", DOCUMENT_NODE, JS_PROP_ENUMERABLE),
	JS_PROP_INT32_DEF("DOCUMENT_TYPE_NODE", DOCUMENT_TYPE_NODE, JS_PROP_ENUMERABLE),
	JS_PROP_INT32_DEF("DOCUMENT_FRAGMENT_NODE", DOCUMENT_FRAGMENT_NODE, JS_PROP_ENUMERABLE),
};

static JSClassDef node_class = {
	"Node",
};

static JSValue
node_constructor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv)
{
#ifdef ECMASCRIPT_DEBUG
	fprintf(stderr, "%s:%s\n", __FILE__, __FUNCTION__);
#endif
	return JS_NULL;
}

static void
JS_NewGlobalCConstructor2(JSContext *ctx, JSValue func_obj, const char *name, JSValueConst proto)
{
	REF_JS(func_obj);
	REF_JS(proto);

	JSValue global_object = JS_GetGlobalObject(ctx);

	JS_DefinePropertyValueStr(ctx, global_object, name,
		JS_DupValue(ctx, func_obj), JS_PROP_WRITABLE | JS_PROP_CONFIGURABLE);
	JS_SetConstructor(ctx, func_obj, proto);
	JS_FreeValue(ctx, func_obj);
	JS_FreeValue(ctx, global_object);
}

static JSValueConst
JS_NewGlobalCConstructor(JSContext *ctx, const char *name, JSCFunction *func, int length, JSValueConst proto)
{
	JSValue func_obj;
	func_obj = JS_NewCFunction2(ctx, func, name, length, JS_CFUNC_constructor_or_func, 0);
	REF_JS(func_obj);
	REF_JS(proto);

	JS_NewGlobalCConstructor2(ctx, func_obj, name, proto);

	return func_obj;
}

int
js_node_init(JSContext *ctx)
{
#ifdef ECMASCRIPT_DEBUG
	fprintf(stderr, "%s:%s\n", __FILE__, __FUNCTION__);
#endif
	JSValue proto, obj;

	/* Node class */
	JS_NewClassID(&js_node_class_id);
	JS_NewClass(JS_GetRuntime(ctx), js_node_class_id, &node_class);
	proto = JS_NewObject(ctx);
	REF_JS(proto);

	JS_SetClassProto(ctx, js_node_class_id, proto);

	/* Node object */
	obj = JS_NewGlobalCConstructor(ctx, "Node", node_constructor, 1, proto);
	REF_JS(obj);

	JS_SetPropertyFunctionList(ctx, obj, node_class_funcs, countof(node_class_funcs));

	return 0;
}