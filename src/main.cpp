#include <ftxui/component/component.hpp>
#include <pvtui/pvtui.hpp>

#include "dashboard.hpp"

using namespace ftxui;
using namespace pvtui;

int main(int argc, char *argv[]) {

    pvtui::App app(argc, argv);

    // Monitor<std::string> mode(app, "bcur:Dashboard:RobotMode.VAL");
    // Monitor<std::string> safety_str(app, "bcur:Dashboard:SafetyStatus.VAL");
    // Monitor<std::string> connected(app, "bcur:Dashboard:Connected.RVAL");
    // Monitor<std::string> remote(app, "bcur:Dashboard:IsInRemoteControl.RVAL");
    BitsWidget safety_bits(app, "bcur:Receive:SafetyStatusBits.VAL", 11);

    auto dashboard = Make<Dashboard>(app, "bcur:");

    std::vector<std::string> tab_values {
      "Dashboard", " Status ", "Control "
    };
    int selected_tab = 0;

    auto recv_container = Renderer([&]{
        return vbox({
            safety_bits.component()->Render(),
        }) | center;
    });

    auto tab_container = Container::Tab({
        dashboard,
        recv_container,
    }, &selected_tab);

    auto container = Container::Vertical({
        Menu(&tab_values, &selected_tab, MenuOption::HorizontalAnimated()),
        tab_container
    });

    app.run(container);
}
