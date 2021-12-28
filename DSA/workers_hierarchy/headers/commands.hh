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

    public:

        void execute_command(string command_name,
                vector<string> args); 
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
    private:
        vector<pair<string, Hierarchy>>& hierarchies;
        CLIController* cliController;
    public:
        Exit(vector<pair<string, Hierarchy>>& hierarchies, CLIController* cliController);

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

class Find: public ICommand {
    private:
        vector<pair<string, Hierarchy>>& hierarchies;

    public:
        Find(vector<pair<string, Hierarchy>>& hierarchies);

        void execute(vector<string> args);
        string getName();
        string getDetails();
};

class NumSubordinates: public ICommand {
    private:
        vector<pair<string, Hierarchy>>& hierarchies;

    public:
        NumSubordinates(vector<pair<string, Hierarchy>>& hierarchies);

        void execute(vector<string> args);
        string getName();
        string getDetails();
};

class Manager: public ICommand {
    private:
        vector<pair<string, Hierarchy>>& hierarchies;

    public:
        Manager(vector<pair<string, Hierarchy>>& hierarchies);

        void execute(vector<string> args);
        string getName();
        string getDetails();
};

class NumEmployees: public ICommand {
    private:
        vector<pair<string, Hierarchy>>& hierarchies;

    public:
        NumEmployees(vector<pair<string, Hierarchy>>& hierarchies);

        void execute(vector<string> args);
        string getName();
        string getDetails();
};

class Overloaded: public ICommand {
    private:
        vector<pair<string, Hierarchy>>& hierarchies;

    public:
        Overloaded(vector<pair<string, Hierarchy>>& hierarchies);

        void execute(vector<string> args);
        string getName();
        string getDetails();
};

class Join: public ICommand {
    private:
        vector<pair<string, Hierarchy>>& hierarchies;

    public:
        Join(vector<pair<string, Hierarchy>>& hierarchies);

        void execute(vector<string> args);
        string getName();
        string getDetails();
};

class Fire: public ICommand {
    private:
        vector<pair<string, Hierarchy>>& hierarchies;

    public:
        Fire(vector<pair<string, Hierarchy>>& hierarchies);

        void execute(vector<string> args);
        string getName();
        string getDetails();
};

class Hire: public ICommand {
    private:
        vector<pair<string, Hierarchy>>& hierarchies;

    public:
        Hire(vector<pair<string, Hierarchy>>& hierarchies);

        void execute(vector<string> args);
        string getName();
        string getDetails();
};

class Salary: public ICommand {
    private:
        vector<pair<string, Hierarchy>>& hierarchies;

    public:
        Salary(vector<pair<string, Hierarchy>>& hierarchies);

        void execute(vector<string> args);
        string getName();
        string getDetails();
};

class Incorporate: public ICommand {
    private:
        vector<pair<string, Hierarchy>>& hierarchies;

    public:
        Incorporate(vector<pair<string, Hierarchy>>& hierarchies);

        void execute(vector<string> args);
        string getName();
        string getDetails();
};

class Modernize: public ICommand {
    private:
        vector<pair<string, Hierarchy>>& hierarchies;

    public:
        Modernize(vector<pair<string, Hierarchy>>& hierarchies);

        void execute(vector<string> args);
        string getName();
        string getDetails();
};