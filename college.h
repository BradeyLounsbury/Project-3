/**
 *      Name: Bradey Lounsbury
 *      Date: February 28, 2020
 *      Desc: Container class that stores course objects in a linked list.
 *      Has funcs to add and remove courses as well as funcs to display, 
 *      load (from a file), and save (to a file), the list.  It also has 
 *      funcs to calculate hours taken and gpa of the list.
 */

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
    void remove(string coursename);

    //helpers
    void display(ostream& outs);
    void load(istream& fin);
    void save(ostream& fout);
    double hours() const;
    double gpa() const;

    private:
    string name;
    node* head;
};

#endif