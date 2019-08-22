#include <list>
#include <iostream>
#include <string>
#include <unistd.h>
#include <sstream>
#include <stdio.h>
#include <fstream>
#include <Windows.h>


//PROGRAM
#ifndef Program_h
#define Program_h

class Program
{
    
public:
    std::string name;
    int length;
    int temperature;
    int energy;
    
    Program(std::string a, int b, int c, int d) {
        name = a;
        length = b;
        temperature = c;
        energy = d;
    };
    ~Program();
    
};

#endif


//CONTROLER
#ifndef Controler_h
#define Controler_h


class Controler
{
public:
    Program* currentProgram;
    std::list<Program*> programs;
    
    Controler() {
        this->loadPrograms();
    };
    ~Controler();
    void setProgram(Program * a);
    void loadPrograms() ;
    
};

void Controler::loadPrograms() {
    {
        int b,c,d;
        std::string a;
        std::string path = "C:\\Users\\CEM\\Desktop\\SEfinal\\programs\\"; 
        std::string filepath;
        for(int i = 0; i<1024; i++) {
            filepath = path;
            filepath += std::to_string(i);
            filepath += ".txt";
            std::ifstream infile(filepath);
            if(infile.is_open()) {
                
   					infile >> a >> b >> c >> d ;
                    Program* p = new Program(a, b, c, d);
                    programs.push_back(p);
                
            }
        }   
        
    }
}

void Controler::setProgram(Program* a) {
    
        this->currentProgram = a;
    
}
#endif


//CONSOLE VIEW
#ifndef ConsoleView_h
#define ConsoleView_h

class ConsoleView {
public:
	
	
    ConsoleView() {
    	std::cout << ".........................." << std::endl; 
        std::cout << "    >>>>    Virtual dishwasher" << std::endl; 
      
    };
    
   
    void showProgram(Program* p) {
        std::cout << "\t "<< p->name << std::endl;
        std::cout << "Length : "<< p->length << " minutes." << std::endl;
        std::cout << "Temperature : "<< p->temperature << " degrees." << std::endl;
        std::cout << "Energy : "<< p->energy << " kVh" << std::endl;
    }
    
    void showControler(Controler* c){
        std::cout << ".........................." << std::endl;
        std::list<Program*>::iterator iter;
    	std::cout << " " << std::endl;
        std::cout << "Avilable programs:" << std::endl;
        std::cout << " " << std::endl;
        iter = c->programs.begin();
        int i = 1;
        while(iter !=  c->programs.end())
        {
            std::cout << i++ << ". ";
            this->showProgram((*iter));
            iter++;
        }
        std::cout<<std::endl;
    }
    
    Program* selectProgram(std::list<Program*> p) {
        int program_number;
        std::cout << "Choose program number" << std::endl;
        std::cin >> program_number;
        std::cout << "Chosen program: " << program_number << std::endl;
        return *std::next(p.begin(), program_number-1);;
    }

    
    int confirm(){
        int n = 0;
        std::cout << "Press 1 to proceed/ press 0 to turn off the dishwasher:" << std::endl;
        std::cin >> n;
        std::cout << std::endl;
		return n;
    }
    ~ConsoleView();
};

#endif



//DISHWASHER SIMULATION
#ifndef Dishwasher_h
#define Dishwasher_h
#ifndef ConsoleView_h

#endif
class Dishwasher
{
private:
    Controler* controler;
    ConsoleView* view;


public:
    bool working;
    void selectProgram();
    int confirm();
    void run(ConsoleView* v);
    bool progress() ;
    void refresh();
    Dishwasher(){};
    ~Dishwasher(){};
    
};

void Dishwasher::run(ConsoleView* v) {
    
        this->working = false;
        this->view = v;
        this->controler = new Controler();
        while(true) {
            this->view->showControler(this->controler);
            this->selectProgram();
            this->view->showProgram(this->controler->currentProgram);
            int c = this->confirm();
            if(c > 0)
                while(this->progress()) { }
				
						
	           else if(c = 0) {
                break;
            }
            this->working = false;
            this->refresh();
        }
        
}


bool Dishwasher::progress() {
    
        this->working = true;
        //simulation
        std::cout << "PRE-WASH"<< std::endl;
        Sleep(1500);
        std::cout << "WASHING" << std::endl;
        Sleep(1500);
        std::cout << "STEAMING" << std::endl;
        Sleep(1000);
        std::cout << "RINSING" << std::endl;
        Sleep(500);
        std::cout << "DRYING" << std::endl;
        Sleep(500);
        std::cout << "FINISH" << std::endl;
        Sleep(1500);

        return false;
    
}

int Dishwasher::confirm() {
    int c = this->view->confirm();
    return c;
    return false;
}

void Dishwasher::refresh()
{
    this->controler->currentProgram = nullptr;
}

void Dishwasher::selectProgram() {
    Program* selected;
    selected = this->view->selectProgram(controler->programs);
    this->controler->setProgram(selected);
}
#endif

//MAIN
int main(int argc, char const *argv[])
{
    ConsoleView* v;
    Dishwasher* d;
    v = new ConsoleView();
    d = new Dishwasher();
    d->run(v);
    
    return 0;
}
