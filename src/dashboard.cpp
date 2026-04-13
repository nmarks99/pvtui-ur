#include "common.hpp"
#include "dashboard.hpp"

using namespace ftxui;
using namespace pvtui;

Dashboard::Dashboard(pvtui::App& app, const std::string& prefix) :
    prefix(prefix),
    mode(app, prefix + "Dashboard:RobotMode.VAL"),
    safety_str(app, prefix + "Dashboard:SafetyStatus.VAL"),
    connected(app, prefix + "Dashboard:Connected.RVAL"),
    remote(app, prefix + "Dashboard:IsInRemoteControl.RVAL"),
    safety(app, prefix + "Dashboard:SafetyStatus.VAL"),
    prog(app, prefix + "Dashboard:LoadedProgram.VAL"),
    progstate(app, prefix + "Dashboard:ProgramState.VAL"),
    polyscope_version(app, prefix + "Dashboard:PolyscopeVersion.VAL"),
    serial_number(app, prefix + "Dashboard:SerialNumber.VAL"),
    connect(app, prefix + "Dashboard:Connect.PROC",                      "      Connect       ", ButtonOption::Simple()),
    disconnect(app, prefix + "Dashboard:Disconnect.PROC",                "     Disconnect     ", ButtonOption::Simple()),
    poweron(app, prefix + "Dashboard:PowerOn.PROC",                      "      Power On      ", ButtonOption::Simple()),
    poweroff(app, prefix + "Dashboard:PowerOff.PROC",                    "      Power Off     ", ButtonOption::Simple()),
    shutdown(app, prefix + "Dashboard:Shutdown.PROC",                    "      Shutdown      ", ButtonOption::Simple()),
    close_popup(app, prefix + "Dashboard:ClosePopup.PROC",               "    Close Popup     ", ButtonOption::Simple()),
    close_safety_popup(app, prefix + "Dashboard:CloseSafetyPopup.PROC",  " Close Safety Popup ", ButtonOption::Simple()),
    release_brakes(app, prefix + "Dashboard:BrakeRelease.PROC",         "   Release Brakes   ", ButtonOption::Simple()),
    restart_safety(app, prefix + "Dashboard:RestartSafety.PROC",         "   Restart Safety   ", ButtonOption::Simple()),
    unlock_prot_stop(app, prefix + "Dashboard:UnlockProtectiveStop.PROC","  Unlock Prot. Stop ", ButtonOption::Simple()),
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
        shutdown.component(),
        close_popup.component(),
        close_safety_popup.component(),
        release_brakes.component(),
        restart_safety.component(),
        unlock_prot_stop.component(),
        urp.component(),
        play.component(),
        pause.component(),
        stop.component(),
    });

    container |= Renderer([&](Element){
        return vbox({

            // Buttons
            hbox({
                vbox({
                    close_popup.component()->Render(),
                    close_safety_popup.component()->Render(),
                    unlock_prot_stop.component()->Render(),
                    release_brakes.component()->Render(),
                    restart_safety.component()->Render(),
                }) | size(WIDTH, EQUAL, 22),

                vbox({
                    poweron.component()->Render(),
                    poweroff.component()->Render(),
                    connect.component()->Render(),
                    disconnect.component()->Render(),
                    shutdown.component()->Render(),
                }) | size(WIDTH, EQUAL, 22),
            }),

            // Program
            vbox({
                labelled_rbv(prog),
                labelled_rbv(progstate),
                hbox({
                    urp.component()->Render() | edit_style(urp) | flex,
                    separatorEmpty(),
                    play.component()->Render(),
                    pause.component()->Render(),
                    stop.component()->Render(),
                })
            }) | border,

            // Status
            vbox({
                hbox({
                    text(" Connected: "),
                    connected.value()
                        ? text("") | color(Color::Green)
                        : text("") | color(Color::Red)
                }),
                hbox({
                    text("    Remote: "),
                    remote.value()
                        ? text("") | color(Color::Green)
                        : text("") | color(Color::Red)
                }),
                // labelled_rbv(connected,         " Connected: "),
                // labelled_rbv(remote,            "    Remote: "),
                labelled_rbv(mode,              "Robot Mode: "),
                labelled_rbv(safety,            "    Safety: "),
                labelled_rbv(polyscope_version, " Polyscope: "),
                labelled_rbv(serial_number,     " Serial No: "),
            }) | border
        }) | size(WIDTH, EQUAL, 42);
    });

    Add(container);
}
