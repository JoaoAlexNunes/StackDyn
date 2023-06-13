#include "Stack.h"

Stack::Stack(int sId, int w):StackID(sId), Weigth(w)
{
	Blocklist = new int[Weigth];
}

Stack::~Stack()
{

}
