#pragma once
#include <string>
#include <vector>
#include "interface.h"

using namespace std;


class ICommand {
    public:
        virtual void execute(vector<string> args) = 0;
        virtual string getName() = 0; 
        virtual string getDetails() = 0;

        virtual ~ICommand() = 0;
};

class CLIController {
    private:
        vector<ICommand*> commands; 

        void execute_command(string command_name,
                vector<string> args); 

    public:
        void begin_reading(); 
        void register_command(ICommand* command); 
        vector<ICommand*> get_commands();

        ~CLIController();
};


class Help: public ICommand {
    private:
        CLIController* cliController;

    public:
        Help(CLIController* cliController);

        void execute(vector<string> args);
        string getName();
        string getDetails();
};

class Exit: public ICommand {
    public:
        Exit();

        void execute(vector<string> args);
        string getName();
        string getDetails();
};

class Load: public ICommand {
    private:
        vector<pair<string, Hierarchy>>& hierarchies;

    public:
        Load(vector<pair<string, Hierarchy>>& hierarchies);

        void execute(vector<string> args);
        string getName();
        string getDetails();
};

class Save: public ICommand {
    private:
        vector<pair<string, Hierarchy>>& hierarchies;

    public:
        Save(vector<pair<string, Hierarchy>>& hierarchies);

        void execute(vector<string> args);
        string getName();
        string getDetails();
};
