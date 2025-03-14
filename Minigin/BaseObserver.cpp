#include "BaseObserver.h"

namespace dae
{
	unsigned int sdbm_hash(const char* str) {
		unsigned int hash = 0;
		int c;

		while (*str) {
			c = *str++;
			hash = c + (hash << 6) + (hash << 16) - hash;
		}

		return hash;
	}
}