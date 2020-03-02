/**
 *      Name: Bradey Lounsbury
 *      Date: February 28, 2020
 *      Desc: Implementation of college.h file
 */
#include "college.h"
#include "node.h"
using namespace std;

//Big 3
College::~College() {
    node* rmptr;
    while (head != NULL)
    {
        rmptr = head;
        head = head->link();
        delete rmptr;
        // cout << "Erased" << endl;
    }
}

College::College(const College& other) {
    if (other.head == NULL)
    {
        head = NULL;
    }
    else
    {
        node* ptr1;
        node* ptr2;
        head = new node;
        head->set_data(other.head->data());
        head->set_link(other.head->link());
        ptr1 = other.head->link();
        ptr2 = head;


        while (ptr1 != NULL)
        {
            ptr2->set_link(new node(ptr1->data()));
            ptr2 = ptr2->link();
            ptr1 = ptr1->link();
        }
    }
}

College& College::operator=(const College& rhs) {
    //checking for self assignment
    if (this == &rhs)
    {
        return *this;
    }


    //erasing existing list
    node* rmptr;
    while (head != NULL)
    {
        rmptr = head;
        head = head->link();
        delete rmptr;
    }


    if (rhs.head == NULL)
    {
        head = new node(rhs.head->data());
        const node* ptr1;
        node* ptr2;
        ptr1 = rhs.head->link();
        ptr2 = head;
        while (ptr1 != NULL)
        {
            ptr2->set_link(new node(ptr1->data()));
            ptr2 = ptr2->link();
            ptr1 = ptr1->link();
        }
    }
    return *this;
}


//setter
void College::set_name(string new_name) {
    name = new_name;
}


//mutators
void College::add(course& c) {
    if (head == NULL)
    {
        head = new node(c, head);
    }
    else
    {
        node* cursor = head;
        node* tmp = head;
        
        //puts course at beginning of list
        if (head->data().get_course_number() >= c.get_course_number())
        {
            head = new node(c, head);
        }
        else
        {
            while (cursor != NULL)
            {
                //puts course before its alphabetically superior peer
                if (cursor->data().get_course_number() >= c.get_course_number())
                {
                    tmp->set_link(new node(c, cursor));
                    return;
                }
                tmp = cursor;
                cursor = cursor->link();
            }
            //puts course at end of list
            tmp->set_link(new node(c, cursor));
        }
    }
}

void College::remove(string coursename) {
    if (head == NULL)
    {
        cout << "No courses taken :(";
        return;
    }
    
    for (size_t i = 0; i < coursename.length(); i++)
    {
        coursename[i] = toupper(coursename[i]);
    }
    
    node* tmp = head;
    //removes first course(s)
    while(head->data().get_course_number() == coursename)
    {
        head = head->link();
        delete tmp;
        tmp = head;
    }

    bool deleted = false;
    node* cursor = head->link();
    tmp = head;
    while (cursor != NULL)
    {
        if (cursor->data().get_course_number() == coursename)
        {
            tmp->set_link(cursor->link());
            delete cursor;
            cursor = tmp->link();
            deleted = true;
        }
        else
        {
            tmp = cursor;
            cursor = cursor->link();
        }
    }
    if (!deleted)
    {
        cout << "Course not found" << endl;
    }
    return;
}


//helpers
void College::display(ostream& outs) {
    if (&outs == &cout)
    {
        if (head == NULL)
        {
            outs << "No courses taken :(\n";
        }
        else
        {
            node* cursor = head;
            while (cursor != NULL)
            {
                outs << cursor->data() << endl;
                cursor = cursor->link();
            }
        }
    }
}

void College::load(istream& fin) {
    getline(fin, name);
    course c;
    fin >> c;
    
    head = new node(c);
    node* cursor = head;
    while (fin >> c)
    {
        cursor->set_link(new node(c));
        cursor = cursor->link();
    }
}

void College::save(ostream& fout) {
    fout << name << endl;
    node* cursor = head;
    if (head == NULL)
    {
        return;
    }
    
    while (cursor != NULL)
    {
        fout << cursor->data();
        cursor = cursor->link();
    }
}

double College::hours() const {
    if (head == NULL)
    {
        cout << "No courses taken :(" << endl;
        return 0;
    }
    
    node* cursor = head;
    double hours = 0;
    while (cursor != NULL)
    {
        hours += cursor->data().get_hours();
        cursor = cursor->link();
    }
    return hours;
}

double College::gpa() const {
    if (head == NULL)
    {
        cout << "No courses taken :(" << endl;
        return 0;
    }
    
    node* cursor = head;
    double gpa = 0;
    double course_hours = 0;
    while (cursor != NULL)
    {
        gpa += (cursor->data().get_number_grade() * cursor->data().get_hours());
        course_hours += cursor->data().get_hours();
        cursor = cursor->link();
    }
    return gpa/course_hours;
}