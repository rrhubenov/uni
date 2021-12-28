#include "headers/commands.hh"
#include "headers/interface.h"

#include <iostream>
#include <string>

vector<pair<string, Hierarchy>> hierarchies;

int main(int argc, char **argv) {
    CLIController cli_controller;

    Help* helpCommand = new Help(&cli_controller);
    Exit* exitCommand = new Exit(hierarchies, &cli_controller);
    Load* loadCommand = new Load(hierarchies);
    Save* saveCommand = new Save(hierarchies);
    Find* findCommand = new Find(hierarchies);
    NumSubordinates* numSubordinatesCommand = new NumSubordinates(hierarchies);
    Manager* managerCommand = new Manager(hierarchies);
    NumEmployees* numEmployeesCommand = new NumEmployees(hierarchies);
    Overloaded* overloadedCommand = new Overloaded(hierarchies);
    Join* joinCommand = new Join(hierarchies);
    Fire* fireCommand = new Fire(hierarchies);
    Hire* hireCommand = new Hire(hierarchies);
    Salary* salaryCommand = new Salary(hierarchies);
    Incorporate* incorporateCommand = new Incorporate(hierarchies);
    Modernize* modernizeCommand = new Modernize(hierarchies);

    cli_controller.register_command(helpCommand);
    cli_controller.register_command(exitCommand);
    cli_controller.register_command(loadCommand);
    cli_controller.register_command(saveCommand);
    cli_controller.register_command(findCommand);
    cli_controller.register_command(numSubordinatesCommand);
    cli_controller.register_command(managerCommand);
    cli_controller.register_command(numEmployeesCommand);
    cli_controller.register_command(overloadedCommand);
    cli_controller.register_command(joinCommand);
    cli_controller.register_command(fireCommand);
    cli_controller.register_command(hireCommand);
    cli_controller.register_command(salaryCommand);
    cli_controller.register_command(incorporateCommand);
    cli_controller.register_command(modernizeCommand);

    cli_controller.begin_reading();

    return 0;
}