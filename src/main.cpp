#include <chrono>
#include <ctime>
#include <ftxui/component/component.hpp>
#include <pvtui/pvtui.hpp>

#include "control.hpp"
#include "dashboard.hpp"
#include "gripper.hpp"
#include "io.hpp"
#include "status.hpp"

using namespace ftxui;
using namespace pvtui;
using namespace std::chrono_literals;

int main(int argc, char *argv[]) {

    pvtui::App app(argc, argv);

    // PV names to monitor are passed as positional arguments
    auto pos_args = app.args.positional_args();
    if (pos_args.size() != 2) {
        std::cout << "Usage: pvtui_sr <IOC prefix>\n";
        return 1;
    }
    std::string prefix = pos_args[1];

    auto dashboard = Make<Dashboard>(app, prefix);
    auto status = Make<Status>(app, prefix);
    auto control = Make<Control>(app, prefix);
    auto gripper = Make<Gripper>(app, prefix);
    auto io = Make<IOTab>(app, prefix);

    Monitor<std::string> tod(app, prefix + "TOD");

    std::vector<std::string> tab_values {
      "Control", "Status", "Dashboard", "Gripper", "I/O"
    };
    int selected_tab = 0;

    auto tab_container = Container::Tab({
        control,
        status,
        dashboard,
        gripper,
        io,
    }, &selected_tab);

    auto op = MenuOption::HorizontalAnimated();
    op.underline.SetAnimationDuration(100ms);
    auto container = Container::Vertical({
        Menu(&tab_values, &selected_tab, op),
        Renderer([]{return separatorEmpty();}),
        tab_container | flex,
        Renderer([&]{
            return vbox({
                separator(),
                hbox({
                    separatorEmpty(),
                    text(prefix),
                    filler(),
                    tod.component()->Render()
                }),
            });
        }),
    });

    app.run(container);
}
