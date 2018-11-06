#pragma once

#include "export.h"

namespace ns_test {
	namespace ns_log {
		class mylog {
		public: 
			void dolog();
		};

#ifdef __cplusplus
		
		extern "C" {
#endif
			MY_API void domylog();
#ifdef __cplusplus
		}
#endif // __cpluscplus

	};

	using ns_log::mylog;
};
