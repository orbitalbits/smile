
#ifndef __SMILE_SMILETYPES_USEROBJECT_H__
#define __SMILE_SMILETYPES_USEROBJECT_H__

#ifndef __SMILE_SMILETYPES_OBJECT_H__
#include <smile/smiletypes/smileobject.h>
#endif

#ifndef __SMILE_DICT_INT32DICT_H__
#include <smile/dict/int32dict.h>
#endif

//-------------------------------------------------------------------------------------------------
//  Type declarations

struct SmileUserObjectInt {
	DECLARE_BASE_OBJECT_PROPERTIES;
	SmileObject securityKey;
	struct Int32DictInt dict;
};

//-------------------------------------------------------------------------------------------------
//  Public interface

SMILE_API SmileUserObject SmileUserObject_CreateWithSize(SmileObject base, Int initialSize);

SMILE_API Bool SmileUserObject_CompareEqual(SmileUserObject self, SmileObject other);
SMILE_API UInt32 SmileUserObject_Hash(SmileUserObject self);
SMILE_API void SmileUserObject_SetSecurity(SmileUserObject self, Int security, SmileObject securityKey);
SMILE_API Int SmileUserObject_GetSecurity(SmileUserObject self);
SMILE_API SmileObject SmileUserObject_GetProperty(SmileUserObject self, Symbol propertyName);
SMILE_API void SmileUserObject_SetProperty(SmileUserObject self, Symbol propertyName, SmileObject value);
SMILE_API Bool SmileUserObject_HasProperty(SmileUserObject self, Symbol propertyName);
SMILE_API SmileList SmileUserObject_GetPropertyNames(SmileUserObject self);
SMILE_API Bool SmileUserObject_ToBool(SmileUserObject self);
SMILE_API Int32 SmileUserObject_ToInteger32(SmileUserObject self);
SMILE_API Real64 SmileUserObject_ToReal64(SmileUserObject self);
SMILE_API String SmileUserObject_ToString(SmileUserObject self);

Inline SmileUserObject SmileUserObject_Create(SmileObject base)
{
	return SmileUserObject_CreateWithSize(base, 8);
}

#endif