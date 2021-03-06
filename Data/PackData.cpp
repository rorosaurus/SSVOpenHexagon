#include "PackData.h"

namespace hg
{
	PackData::PackData(string mId, string mName, float mPriority) : id{mId}, name{mName}, priority{mPriority} { }

	string PackData::getId() { return id; }
	string PackData::getName() { return name; }
	float PackData::getPriority() { return priority; }
}

