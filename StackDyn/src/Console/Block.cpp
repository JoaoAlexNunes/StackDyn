#include "Block.h"


Block::Block(int bId, double tr, double dd, std::string r)
{
	BlockID = bId;
	Time_Release = tr;
	Due_Date = dd;
	Ready = r;
}

Block::~Block()
{
}
