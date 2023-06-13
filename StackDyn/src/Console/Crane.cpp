#include "Crane.h"

class Crane {
public:
    int LocationID;
    int Load;                        //Que block carrega
    std::string Schedule;            //EmptyMove ou nao
    int HorizontalPosition;            //Na grid
    int VerticalPosition;
    std::string SequenceNr;            //lista de moves feitos
};