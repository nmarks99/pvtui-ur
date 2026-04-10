#include <chrono>
#include <ftxui/component/component.hpp>
#include <pvtui/pvtui.hpp>

#include "dashboard.hpp"
#include "status.hpp"
#include "control.hpp"

using namespace ftxui;
using namespace pvtui;
using namespace std::chrono_literals;

int main(int argc, char *argv[]) {

    pvtui::App app(argc, argv);

    BitsWidget safety_bits(app, "bcur:Receive:SafetyStatusBits.VAL", 11, Color::Yellow);

    auto dashboard = Make<Dashboard>(app, "bcur:");
    auto status = Make<Status>(app, "bcur:");
    auto control = Make<Control>(app, "bcur:");

    std::vector<std::string> tab_values {
      "Control", "Status", "Dashboard"
    };
    int selected_tab = 0;

    auto tab_container = Container::Tab({
        control,
        status,
        dashboard,
    }, &selected_tab);

    auto op = MenuOption::HorizontalAnimated();
    op.underline.SetAnimationDuration(100ms);
    auto container = Container::Vertical({
        Menu(&tab_values, &selected_tab, op),
        tab_container
    });

    app.run(container);
}
