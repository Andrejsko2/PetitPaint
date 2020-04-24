#include "CompositeOperation.h"
#include<algorithm>

CompositeOperation::CompositeOperation(std::string _label, std::vector<Selection>* _selections):
    Operation(_label, _selections, nullptr)
{
    //ctor
}

CompositeOperation::~CompositeOperation()
{
    std::for_each(operations.begin(), operations.end(), [](Operation* o){delete o;});
    operations.clear();
}

void CompositeOperation::operator()(std::vector<Pixel>& pixels, int w)
{
    for(Operation* o:operations)
    {
        (*o)(pixels, w);
    }
}

std::string CompositeOperation::get_all_ops()
{
    std::string s="";
    s+=get_label();
    s+=":[ ";

    for(Operation* o:operations)
    {
        s+=o->get_label();
        s+=", ";
    }
    s+="] ";
    return s;
}

void CompositeOperation::erase(std::string _label)
{
    auto it=operations.begin();
    for(it; it!=operations.end(); ++it)
    {
        if((*it)->get_label()==_label)
            operations.erase(it), it=operations.begin();
    }
}
