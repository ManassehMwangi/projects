#include <iostream>
#include "NumberList.h"
using namespace std;

int main()
{
    NumberList list1;
    
    list1.appendNode(1.6);
    list1.appendNode(4.8);
    list1.appendNode(7.9);
    
    cout << "The expected output is shown below: " << endl << endl;
    
    cout << "List1 is: " << endl;
    list1.displayList();
    cout << endl;
    
    NumberList list2 = list1; // Test the copy constructor
    
    list2.insertNode(2.3);
    
    cout << "After inserting 2.3 to list2, List1 is: " << endl;
    list1.displayList();
    cout << endl;
	
    cout << "After inserting 2.3 to list2, List2 is: " << endl;
    list2.displayList();
    cout << endl;
    
    NumberList list3, list4;
    
    list4 = list3 = list1; // Test the overloaded assignment operator
    
    list4.insertNode(5.5);
    
    cout << "After inserting 5.5 to list4, List1 is: "  << endl;
    list1.displayList();
    cout << endl;
    
    cout << "After inserting 5.5 to list4, List3 is: " << endl;
    list3.displayList();
    cout << endl;
    
    cout << "After inserting 5.5 to list4, List4 is: " << endl;
    list4.displayList();
    cout << endl;
    
    return 0;
   
}