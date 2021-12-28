#include "../headers/commands.hh"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

CLIController::~CLIController() {
    for(vector<ICommand*>::iterator it = commands.begin(); it != commands.end(); ++it) {
        delete *it;
    }
}

void CLIController::begin_reading() {
    while(true) {
        std::string input;

        std::cout << "> ";
        std::getline(std::cin, input);

        std::stringstream ss(input);

        std::string command_name;
        std::string arg;
        std::vector<std::string> args;

        std::getline(ss, command_name, ' ');

        while(std::getline(ss, arg, ' ')) {
            args.push_back(arg);
        }

        this->execute_command(command_name, args);
    }
}

void CLIController::register_command(ICommand* command) {
    this->commands.push_back(command);
}

void CLIController::execute_command(std::string command_name,
        std::vector<std::string> args) {
    for(unsigned i = 0; i < this->commands.size(); i++) {
        if(!this->commands[i]->getName().compare(command_name)) {
            this->commands[i]->execute(args);
            return;
        }
    }
    std::cout << command_name << ": Command not found" << "\n";
}

vector<ICommand*> CLIController::get_commands() {
    return commands;
}

ICommand::~ICommand() = default;

Help::Help(CLIController* cliController): cliController(cliController) {}
string Help::getName() { return "help"; }
string Help::getDetails() { return "help: List available commands and their functions."; }
void Help::execute(vector<string> args) {
    vector<ICommand*> commands = cliController->get_commands();

    for(vector<ICommand*>::const_iterator it = commands.cbegin(); it != commands.cend(); ++it) {
        cout << (*it)->getDetails() << endl;
    }
}

Exit::Exit(){}
void Exit::execute(vector<string> args) { exit(EXIT_SUCCESS); }
string Exit::getName() { return "exit"; }
string Exit::getDetails() { return "exit: close the program"; }

Load::Load(vector<pair<string, Hierarchy>>& hierarchies): hierarchies(hierarchies) {}
string Load::getName() { return "load"; }
string Load::getDetails() { return "load: read from file/stdin and create a new hierarchy"; }
void Load::execute(vector<string> args) {
    // TODO: Allow read from stdin
    // TODO: Check that object name is correctly named
    string objectName = args[0];
    string fileName = args[1];

    fstream file;
    file.open(fileName, ios::in);

    if(file.is_open()) {
        string line;
        string buffer;

        while(getline(file, line)) {
            buffer += line += "\n";
        }

        Hierarchy h = Hierarchy(buffer);
        hierarchies.push_back(make_pair(objectName, h));
    } else {
        cout << "Failed to open file" << endl;
    }
}

Save::Save(vector<pair<string, Hierarchy>>& hierarchies): hierarchies(hierarchies) {}
string Save::getName() { return "save"; }
string Save::getDetails() { return "save: write object to a given file/stdout"; }
void Save::execute(vector<string> args) {
    // TODO: Allow read from stdin
    // TODO: Check that object name is correctly named
    string objectName = args[0];
    string fileName = args[1];

    fstream file;
    file.open(fileName, ios::out);

    if(file.is_open()) {

        for(vector<pair<string, Hierarchy>>::iterator it = hierarchies.begin(); it != hierarchies.end(); ++it) {
            if(it->first == objectName) {
                file << it->second.print();
                return;
            }
        }

        cout << "Object not found" << endl;
    } else {
        cout << "Failed to open file" << endl;
    }
}