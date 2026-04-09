#include "dashboard.hpp"

Dashboard::Dashboard(pvtui::App& app, const std::string& prefix) :
    prefix(prefix),
    mode(app, prefix + "Dashboard:RobotMode.VAL"),
    safety_str(app, prefix + "Dashboard:SafetyStatus.VAL"),
    connected(app, prefix + "Dashboard:Connected.RVAL"),
    remote(app, prefix + "Dashboard:IsInRemoteControl.RVAL"),
    safety(app, prefix + "Dashboard:SafetyStatus.VAL"),
    prog(app, prefix + "Dashboard:LoadedProgram.VAL"),
    progstate(app, prefix + "Dashboard:ProgramState.VAL")
{

    using namespace ftxui;
    using namespace pvtui;

    auto readback_style = [](const WidgetBase& w){
        return EPICSColor::custom(w, color(Color::Blue));
    };

    auto container = Container::Vertical({});
    container |= Renderer([&](Element){
        return vbox({

            vbox({
                text(prog.value()) | readback_style(remote),
                text(progstate.value()) | readback_style(remote),
            }) | border,

            vbox({
                hbox({
                    text(" Connected: "),
                    text(connected.value()) | readback_style(connected),
                }),
                hbox({
                    text("    Remote: "),
                    text(remote.value()) |  readback_style(remote),
                }),
                hbox({
                    text("Robot Mode: "),
                    text(mode.value()) | readback_style(mode),
                }),
                hbox({
                    text("    Safety: "),
                    text(safety.value()) | readback_style(safety),
                })
            }) | border

        }) | size(WIDTH, EQUAL, 50);
    });

    Add(container);

}
