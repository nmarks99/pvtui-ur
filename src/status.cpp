#include "common.hpp"
#include "status.hpp"

using namespace pvtui;
using namespace ftxui;

Status::Status(pvtui::App& app, const std::string& prefix)
    : prefix(prefix),
    reconnect(app, prefix+"Receive:Reconnect.PROC",   "  Connect   "),
    disconnect(app, prefix+"Receive:Disconnect.PROC", " Disconnect "),
    safety_bits(app, prefix+"Receive:SafetyStatusBits.VAL", 11, Color::Yellow),
    uptime(app, prefix+"Receive:ControllerTimestamp.VAL"),
    runtime_state(app, prefix+"Receive:RuntimeState.VAL"),
    connected(app, prefix+"Receive:Connected.RVAL"),
    joint1(app, prefix+"Receive:Joint1.VAL"),
    joint2(app, prefix+"Receive:Joint2.VAL"),
    joint3(app, prefix+"Receive:Joint3.VAL"),
    joint4(app, prefix+"Receive:Joint4.VAL"),
    joint5(app, prefix+"Receive:Joint5.VAL"),
    joint6(app, prefix+"Receive:Joint6.VAL"),
    pose1(app, prefix+"Receive:PoseX.VAL"),
    pose2(app, prefix+"Receive:PoseY.VAL"),
    pose3(app, prefix+"Receive:PoseZ.VAL"),
    pose4(app, prefix+"Receive:PoseRoll.VAL"),
    pose5(app, prefix+"Receive:PosePitch.VAL"),
    pose6(app, prefix+"Receive:PoseYaw.VAL")
{

    auto container = Container::Vertical({
        reconnect.component(),
        disconnect.component()
    });

    auto renderer = Renderer(container, [this]{
        return vbox({

            (connected.value()
                 ? text("Connected") | color(Color::Green)
                 : text("Disconnected") | color(Color::Red)) | bold,
            hbox({
                reconnect.component()->Render()
                    | edit_style(reconnect)
                    | size(WIDTH, EQUAL, 14),
                separatorEmpty(),
                disconnect.component()->Render()
                    | edit_style(disconnect)
                    | size(WIDTH, EQUAL, 14)
            }),

            labelled_rbv(uptime, "Uptime: "),
            labelled_rbv(runtime_state, "Runtime state: "),
            separatorEmpty(),

            hbox({
                separatorEmpty(),
                safety_bits.component()->Render(),
                vbox({
                    text("Normal"),
                    text("Reduced"),
                    text("Protective Stopped"),
                    text("Recovery Mode"),
                    text("Safegaurd Stopped"),
                    text("System Emergency Stopped"),
                    text("Robot Emergency Stopped"),
                    text("Emergency Stopped"),
                    text("Violation"),
                    text("Fault"),
                    text("Stopped Due to Safety"),
                }),
            }),
            separatorEmpty(),
            hbox({
                vbox({
                    labelled_rbv(pose1, "    X: "),
                    labelled_rbv(pose2, "    Y: "),
                    labelled_rbv(pose3, "    Z: "),
                    labelled_rbv(pose4, " Roll: "),
                    labelled_rbv(pose5, "Pitch: "),
                    labelled_rbv(pose6, "  Yaw: ")
                }),

                separatorEmpty(),
                separator(),
                separatorEmpty(),

                vbox({
                    labelled_rbv(joint1, "Joint 1: "),
                    labelled_rbv(joint2, "Joint 2: "),
                    labelled_rbv(joint3, "Joint 3: "),
                    labelled_rbv(joint4, "Joint 4: "),
                    labelled_rbv(joint5, "Joint 5: "),
                    labelled_rbv(joint6, "Joint 6: ")
                }),
            }),
        });
    });

    Add(renderer);
}
