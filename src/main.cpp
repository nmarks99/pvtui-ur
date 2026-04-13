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

    pvtui::App app(argc, argv, {"--prefix"});

    // PV names to monitor are passed as positional arguments
    auto pos_args = app.args.positional_args();
    std::string prefix = app.args.param("--prefix");

    auto dashboard = Make<Dashboard>(app, prefix);
    auto status = Make<Status>(app, prefix);
    auto control = Make<Control>(app, prefix);

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
        Menu(&tab_values, &selected_tab, op) | Renderer([&](Element inner){
            return hbox({
                inner,
                filler(),
                text(prefix)
            });
        }),
        Renderer([]{return separatorEmpty();}),
        tab_container
    });

    app.run(container);
}
