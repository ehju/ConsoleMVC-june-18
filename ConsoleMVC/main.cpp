#include "Controller.h"
#include "Model.h"
#include "View.h"

int main()
{
    Model model;
    View view;
    Controller controller(model, view);

    controller.Run();

    return 0;
}
