#include "common.hpp"
#include "gripper.hpp"

using namespace pvtui;
using namespace ftxui;

Gripper::Gripper(pvtui::App& app, const std::string& prefix)
    : prefix(prefix),
      connected(app, prefix + "RobotiqGripper:Connected.RVAL"),
      active(app, prefix + "RobotiqGripper:IsActive.RVAL"),
      is_open(app, prefix + "RobotiqGripper:IsOpen.RVAL"),
      is_closed(app, prefix + "RobotiqGripper:IsClosed.RVAL"),
      move_status(app, prefix + "RobotiqGripper:MoveStatus.VAL"),
      position(app, prefix + "RobotiqGripper:CurrentPosition.VAL"),
      connect(app, prefix + "RobotiqGripper:Connect.PROC", "  Connect  ", ButtonOption::Simple()),
      calibrate(app, prefix + "RobotiqGripper:AutoCalibrate.PROC", " Calibrate ", ButtonOption::Simple()),
      activate(app, prefix + "RobotiqGripper:Activate.PROC", "  Activate ", ButtonOption::Simple()),
      open(app, prefix + "RobotiqGripper:Open.PROC", "    Open   ", ButtonOption::Simple()),
      close(app, prefix + "RobotiqGripper:Close.PROC", "   Close   ", ButtonOption::Simple()),
      speed(app, prefix + "RobotiqGripper:SetSpeed.VAL", PVPutType::Double),
      force(app, prefix + "RobotiqGripper:SetForce.VAL", PVPutType::Double)
{
    auto container = Container::Vertical({
        connect.component(),
        calibrate.component(),
        activate.component(),
        open.component(),
        close.component(),
        speed.component(),
        force.component(),
    });

    container |= Renderer([&](Element) {
        auto state_text = [](bool val, const std::string& on, const std::string& off) {
            return val
                ? text(on) | color(Color::Green) | bold
                : text(off) | color(Color::Red) | bold;
        };

        return vbox({
            state_text(connected.value(), "Connected", "Disconnected"),
            state_text(active.value(), "Active", "Not Active"),
            separatorEmpty(),

            hbox({
                text("   State: "),
                is_open.value()
                    ? text("Open") | color(Color::Green)
                    : is_closed.value()
                        ? text("Closed") | color(Color::Red)
                        : emptyElement(),
            }),
            labelled_rbv(move_status, "  Status: "),
            hbox({
                text("Position: "),
                position.component()->Render() | rbv_style(position),
            }),
            separatorEmpty(),

            hbox({
                text("   Speed: "),
                speed.component()->Render()
                    | edit_style(speed)
                    | size(WIDTH, EQUAL, 10),
            }),
            hbox({
                text("   Force: "),
                force.component()->Render()
                    | edit_style(force)
                    | size(WIDTH, EQUAL, 10),
            }),
            separatorEmpty(),

            hbox({
                open.component()->Render(),
                separatorEmpty(),
                close.component()->Render(),
            }),
            hbox({
                connect.component()->Render(),
                separatorEmpty(),
                calibrate.component()->Render(),
                separatorEmpty(),
                activate.component()->Render(),
            }),
        }) | size(WIDTH, EQUAL, 42);
    });

    Add(container);
}
