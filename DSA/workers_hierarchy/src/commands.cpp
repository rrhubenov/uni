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
    std::string input;
    std::cout << "> ";
    while(getline(cin, input)) {

        std::stringstream ss(input);

        std::string command_name;
        std::string arg;
        std::vector<std::string> args;

        std::getline(ss, command_name, ' ');

        while(std::getline(ss, arg, ' ')) {
            args.push_back(arg);
        }

        this->execute_command(command_name, args);
        std::cout << "> ";
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

Exit::Exit(vector<pair<string, Hierarchy>>& hierarchies, CLIController* cliController): hierarchies(hierarchies), cliController(cliController) {}
void Exit::execute(vector<string> args) { 
    for(vector<pair<string, Hierarchy>>::iterator it = hierarchies.begin(); it != hierarchies.end(); ++it) {
        if(it->second.modified()) {
            cout << it->first << " is modified but not saved" << endl;
            cout << "Enter file name to save it: " << endl;
            string fName;
            cin >> fName;
            vector<string> saveArgs;
            saveArgs.push_back(it->first);
            saveArgs.push_back(fName);
            cliController->execute_command("save", saveArgs);
        }
    }
    cout << "Goodbye!" << endl;
    exit(EXIT_SUCCESS); 
}
string Exit::getName() { return "exit"; }
string Exit::getDetails() { return "exit: close the program"; }

Load::Load(vector<pair<string, Hierarchy>>& hierarchies): hierarchies(hierarchies) {}
string Load::getName() { return "load"; }
string Load::getDetails() { return "load: read from file/stdin and create a new hierarchy, <hierachy_name, file_name>"; }
void Load::execute(vector<string> args) {
    // TODO: Allow read from stdin
    // TODO: Check that object name is correctly named
    string objectName = args[0];
    string buffer;

    if(args.size() == 1) {
        // Problems using EOF. Sending an EOF character causes the whole program to exit.
        // Could not figure out a fix.
        // On empty line the input concludes.
        string line;
        getline(cin, line);
        while(line != "") {
            buffer += line += "\n";
            getline(cin, line);
        }
    } else {
        string fileName = args[1];
        fstream file;
        file.open(fileName, ios::in);
        if(file.is_open()) {
            string line;
            while(getline(file, line)) {
                buffer += line += "\n";
            }
        } else {
            cout << "Failed to open file" << endl;
            return;
        }
    }

    Hierarchy h = Hierarchy(buffer);
    hierarchies.push_back(make_pair(objectName, h));

    cout << objectName << " loaded successfully!" << endl;
}

Save::Save(vector<pair<string, Hierarchy>>& hierarchies): hierarchies(hierarchies) {}
string Save::getName() { return "save"; }
string Save::getDetails() { return "save: write object to a given file/stdout, <hierarchy_name, file_name>"; }
void Save::execute(vector<string> args) {
    // TODO: Allow read from stdin
    // TODO: Check that object name is correctly named
    string objectName = args[0];
    string buffer;

    for(vector<pair<string, Hierarchy>>::iterator it = hierarchies.begin(); it != hierarchies.end(); ++it) {
        if(it->first == objectName) {
            buffer = it->second.print();
            if(args.size() == 2) {
                fstream file;
                file.open(args[1], ios::out);
                if(file.is_open()) {
                    file << buffer;
                } else {
                    cout << "Failed to open file" << endl;
                }
            } else {
                cout << buffer;
            }
            it->second.unmodify();
            return;
        }
    }

    cout << "Object not found" << endl;
}

Find::Find(vector<pair<string, Hierarchy>>& hierarchies): hierarchies(hierarchies) {}
string Find::getName() { return "find"; }
string Find::getDetails() { return "find: find a worker in a given hierarchy <hierarchy_name, worker_name>"; }
void Find::execute(vector<string> args) {
    string hName = args[0];
    string wName = args[1];
    for(vector<pair<string, Hierarchy>>::const_iterator it = hierarchies.cbegin(); it != hierarchies.cend(); ++it) {
        if(it->first == hName) {
            if(it->second.find(wName)) {
                cout << wName << " is employed in " << hName << endl;
            } else {
                cout << wName << " is NOT employed in " << hName << endl;
            }
            return;
        }
    }

    cout << "Hierarchy not found" << endl;
}

NumSubordinates::NumSubordinates(vector<pair<string, Hierarchy>>& hierarchies): hierarchies(hierarchies) {}
string NumSubordinates::getName() { return "num_subordinates"; }
string NumSubordinates::getDetails() { return "num_subordinates: get number of subordinates for worker, <hierarchy_name, worker_name>"; }
void NumSubordinates::execute(vector<string> args) {
    string hName = args[0];
    string wName = args[1];
    for(vector<pair<string, Hierarchy>>::const_iterator it = hierarchies.cbegin(); it != hierarchies.cend(); ++it) {
        if(it->first == hName) {
            unsigned subordinates = it->second.num_subordinates(wName);
            if(subordinates == 0) {
                cout << wName << " has not subordinates." << endl;
            } else {
                cout << wName << " has " << subordinates << " subordinates" << endl;
            }
            return;
        }
    }

    cout << "Hierarchy not found" << endl;
}

Manager::Manager(vector<pair<string, Hierarchy>>& hierarchies): hierarchies(hierarchies) {}
string Manager::getName() { return "manager"; }
string Manager::getDetails() { return "manager: get manager of given worker, <hierarchy_name, worker_name>"; }
void Manager::execute(vector<string> args) {
    string hName = args[0];
    string wName = args[1];
    for(vector<pair<string, Hierarchy>>::const_iterator it = hierarchies.cbegin(); it != hierarchies.cend(); ++it) {
        if(it->first == hName) {
            cout << it->second.manager(wName) << endl;
            return;
        }
    }

    cout << "Hierarchy not found" << endl;
}

NumEmployees::NumEmployees(vector<pair<string, Hierarchy>>& hierarchies): hierarchies(hierarchies) {}
string NumEmployees::getName() { return "num_employees"; }
string NumEmployees::getDetails() { return "num_employees: get number of employees of the given hierarchy, <hierarchy_name>"; }
void NumEmployees::execute(vector<string> args) {
    string hName = args[0];
    for(vector<pair<string, Hierarchy>>::const_iterator it = hierarchies.cbegin(); it != hierarchies.cend(); ++it) {
        if(it->first == hName) {
            cout << it->second.num_employees() << endl;
            return;
        }
    }

    cout << "Hierarchy not found" << endl;
}

Overloaded::Overloaded(vector<pair<string, Hierarchy>>& hierarchies): hierarchies(hierarchies) {}
string Overloaded::getName() { return "overloaded"; }
string Overloaded::getDetails() { return "overloaded: get number of overloaded workers, <hierarchy_name>"; }
void Overloaded::execute(vector<string> args) {
    string hName = args[0];
    for(vector<pair<string, Hierarchy>>::const_iterator it = hierarchies.cbegin(); it != hierarchies.cend(); ++it) {
        if(it->first == hName) {
            cout << it->second.num_overloaded() << endl;
            return;
        }
    }

    cout << "Hierarchy not found" << endl;
}

Join::Join(vector<pair<string, Hierarchy>>& hierarchies): hierarchies(hierarchies) {}
string Join::getName() { return "join"; }
string Join::getDetails() { return "join: join two hierarchies, <hierarchy1_name, hierarchy2_name, resulting_name>"; }
void Join::execute(vector<string> args) {
    string h1Name = args[0];
    string h2Name = args[1];
    string resultName = args[2];

    const Hierarchy* h1 = nullptr;
    const Hierarchy* h2 = nullptr;

    for(vector<pair<string, Hierarchy>>::const_iterator it = hierarchies.cbegin(); it != hierarchies.cend(); ++it) {
        if(it->first == h1Name) {
            h1 = &(it->second);
        } else if(it->first == h2Name) {
            h2 = &(it->second);
        }
    }

    if(h1 == nullptr || h2 == nullptr) {
        cout << "Hierarchy not found" << endl;
        return;
    }
    Hierarchy h3 = h1->join(*h2);
    h3.modify();
    hierarchies.push_back(make_pair(resultName, h3));
}


Fire::Fire(vector<pair<string, Hierarchy>>& hierarchies): hierarchies(hierarchies) {}
string Fire::getName() { return "fire"; }
string Fire::getDetails() { return "fire: remove worker from hierarchy, <hierarchy_name, worker_name>"; }
void Fire::execute(vector<string> args) {
    string hName = args[0];
    string wName = args[1];
    for(vector<pair<string, Hierarchy>>::iterator it = hierarchies.begin(); it != hierarchies.end(); ++it) {
        if(it->first == hName) {
            it->second.fire(wName);
            it->second.modify();
            return;
        }
    }

    cout << "Hierarchy not found" << endl;
}

Hire::Hire(vector<pair<string, Hierarchy>>& hierarchies): hierarchies(hierarchies) {}
string Hire::getName() { return "hire"; }
string Hire::getDetails() { return "hire: add new worker, <hierarchy_name, worker_name, boss_name>"; }
void Hire::execute(vector<string> args) {
    string hName = args[0];
    string wName = args[1];
    string bName = args[2];
    for(vector<pair<string, Hierarchy>>::iterator it = hierarchies.begin(); it != hierarchies.end(); ++it) {
        if(it->first == hName) {
            it->second.hire(wName, bName);
            it->second.modify();
            return;
        }
    }

    cout << "Hierarchy not found" << endl;
}


Salary::Salary(vector<pair<string, Hierarchy>>& hierarchies): hierarchies(hierarchies) {}
string Salary::getName() { return "salary"; }
string Salary::getDetails() { return "salary: get salary of worker, <hierarchy_name, worker_name>"; }
void Salary::execute(vector<string> args) {
    string hName = args[0];
    string wName = args[1];
    for(vector<pair<string, Hierarchy>>::iterator it = hierarchies.begin(); it != hierarchies.end(); ++it) {
        if(it->first == hName) {
            cout << it->second.getSalary(wName) << endl;
            return;
        }
    }

    cout << "Hierarchy not found" << endl;
}

Incorporate::Incorporate(vector<pair<string, Hierarchy>>& hierarchies): hierarchies(hierarchies) {}
string Incorporate::getName() { return "incorporate"; }
string Incorporate::getDetails() { return "incorporate: incorporate a hierarchy, <hierarchy_name>"; }
void Incorporate::execute(vector<string> args) {
    string hName = args[0];
    for(vector<pair<string, Hierarchy>>::iterator it = hierarchies.begin(); it != hierarchies.end(); ++it) {
        if(it->first == hName) {
            it->second.incorporate();
            it->second.modify();
            return;
        }
    }

    cout << "Hierarchy not found" << endl;
}

Modernize::Modernize(vector<pair<string, Hierarchy>>& hierarchies): hierarchies(hierarchies) {}
string Modernize::getName() { return "modernize"; }
string Modernize::getDetails() { return "modernize: modernize a hierarchy, <hierarchy_name>"; }
void Modernize::execute(vector<string> args) {
    string hName = args[0];
    for(vector<pair<string, Hierarchy>>::iterator it = hierarchies.begin(); it != hierarchies.end(); ++it) {
        if(it->first == hName) {
            it->second.modernize();
            it->second.modify();
            return;
        }
    }

    cout << "Hierarchy not found" << endl;
}
