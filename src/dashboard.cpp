#include "dashboard.hpp"

using namespace ftxui;
using namespace pvtui;

Element render_rbv(WidgetBase& w, const std::string& label = "") {
    return hbox({
        label.length() ? text(label) : emptyElement(),
        w.component()->Render() | EPICSColor::custom(w, color(Color::Blue))
    });
}

Dashboard::Dashboard(App& app, const std::string& prefix) :
    prefix(prefix),
    mode(app, prefix + "Dashboard:RobotMode.VAL"),
    safety_str(app, prefix + "Dashboard:SafetyStatus.VAL"),
    connected(app, prefix + "Dashboard:Connected.RVAL"),
    remote(app, prefix + "Dashboard:IsInRemoteControl.RVAL"),
    safety(app, prefix + "Dashboard:SafetyStatus.VAL"),
    prog(app, prefix + "Dashboard:LoadedProgram.VAL"),
    progstate(app, prefix + "Dashboard:ProgramState.VAL"),
    connect(app, prefix + "Dashboard:Connect.PROC",       " Connect    ", ButtonOption::Simple()),
    disconnect(app, prefix + "Dashboard:Disconnect.PROC", " Disconnect ", ButtonOption::Simple()),
    poweron(app, prefix + "Dashboard:PowerOn.PROC",       " On  ", ButtonOption::Simple()),
    poweroff(app, prefix + "Dashboard:PowerOff.PROC",     " Off ", ButtonOption::Simple()),
    play(app, prefix + "Dashboard:Play.PROC",     "  "),
    pause(app, prefix + "Dashboard:Pause.PROC",   "  "),
    stop(app, prefix + "Dashboard:Stop.PROC",     "  "),
    urp(app, prefix + "Dashboard:LoadURP.VAL", PVPutType::String, Color::Black, Color::White)
{

    auto container = Container::Vertical({
        poweron.component(),
        poweroff.component(),
        connect.component(),
        disconnect.component(),
        urp.component(),
        play.component(),
        pause.component(),
        stop.component(),
    });

    container |= Renderer([&](Element){
        return vbox({
            hbox({
                vbox({
                    text("[   TODO    ]"),
                    text("[   TODO    ]"),
                    text("[   TODO    ]"),
                    text("[   TODO    ]"),
                }),

                filler(),

                vbox({
                    hbox({
                        poweron.component()->Render(),
                        separatorEmpty(),
                        poweroff.component()->Render()
                    }),
                    connect.component()->Render(),
                    disconnect.component()->Render(),
                }),
            }) | border,

            vbox({
                render_rbv(prog),
                render_rbv(progstate),
                hbox({
                    urp.component()->Render() | bgcolor(Color::GrayLight) | flex,
                    separatorEmpty(),
                    play.component()->Render(),
                    pause.component()->Render(),
                    stop.component()->Render(),
                })
            }) | border,

            vbox({
                render_rbv(connected, " Connected: "),
                render_rbv(remote,    "    Remote: "),
                render_rbv(mode,      "Robot Mode: "),
                render_rbv(safety,    "    Safety: "),
            }) | border

        }) | size(WIDTH, EQUAL, 40);
    });

    Add(container);
}
