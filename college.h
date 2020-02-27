//header file for college class

#include <iostream>
#include "node.h"
#include "course.h"

using namespace std;

#ifndef COLLEGE_H
#define COLLEGE_H

class College {
    public:
    //Constructor
    College() {head = NULL;}
    
    //Big 3
    ~College();
    College(const College& other);
    College& operator = (const College& rhs);

    //setter
    void set_name(string new_name);

    //mutators
    void add(course& c);


    //helpers
    void display(ostream& outs);
    void load(istream& fin);
    void save(ostream& fout);

    private:
    string name;
    node* head;
};

#endif