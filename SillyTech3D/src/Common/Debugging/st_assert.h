#ifndef __st_assert__
#define __st_assert__

#include <assert.h>
#include "debug.h"

#define __Assert(expr) \
	if(!(expr)) \
		LOG_ERROR() << "Assertion error: " << #expr; \
	assert(expr);

#define __AssertComment(expr, comment) \
	if(!(expr)) \
		LOG_ERROR() << "Assertion error: " << #expr << "\n" << comment; \
	assert(expr);
	


#endif