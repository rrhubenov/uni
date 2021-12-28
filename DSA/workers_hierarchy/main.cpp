#include "headers/commands.hh"
#include "headers/interface.h"

#include <iostream>
#include <string>

vector<pair<string, Hierarchy>> hierarchies;

int main(int argc, char **argv) {
    CLIController cli_controller;

    Help* helpCommand = new Help(&cli_controller);
    Exit* exitCommand = new Exit();
    Load* loadCommand = new Load(hierarchies);
    Save* saveCommand = new Save(hierarchies);

    cli_controller.register_command(helpCommand);
    cli_controller.register_command(exitCommand);
    cli_controller.register_command(loadCommand);
    cli_controller.register_command(saveCommand);

    cli_controller.begin_reading();

    return 0;
}