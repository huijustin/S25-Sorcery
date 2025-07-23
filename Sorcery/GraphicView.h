#ifndef GRAPHICVIEW_H
#define GRAPHICVIEW_H
#include "Observer.h"

class GraphicView : public Observer {
public:
    void notify() override;
};

#endif
