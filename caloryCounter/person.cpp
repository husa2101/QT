#include "person.h"


void Person::set_Weigth(double weight)
{
    if(m_weight != weight){
        m_weight = weight;
        emit weightChanged();
    }
}
