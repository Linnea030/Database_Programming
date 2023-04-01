#include "exerciser.h"

void exercise(connection *C) {
    query1(C, 1, 35, 40, 0, 0, 0, 0, 5, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    query1(C, 0, 35, 40, 0, 0, 0, 1, 5, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    query2(C, "Green");
    query2(C, "Orange");
    query3(C, "Duke");
    query3(C, "UNC");
    query4(C, "MA", "Maroon");
    query4(C, "NC", "DarkBlue");
    query5(C, 13);
    query5(C, 10);
/*
    query1(C, 1, 35, 40, 0, 0, 0, 0, 10, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    cout<<"----------------after 1--------------"<<endl;
    query1(C, 0, 20, 40, 0, 0, 0, 1, 3, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    query1(C, 0, 35, 36, 0, 0, 0, 0, 2, 6, 0, 0, 0, 1, 0, 0, 0, 0, 0);
    query1(C, 0, 35, 20, 0, 0, 0, 0, 5, 6, 0, 0, 0, 0, 0, 0, 1, 0, 0);
    cout<<"---------------after 2--------------"<<endl;
    query2(C, "Green");
    query2(C,"DarkBlue");
    query2(C,"LightBlue");
    query2(C, "Orange");
    query2(C,"Black");
    cout<<"---------------after 3--------------"<<endl;
    query3(C, "Duke");
    query3(C,"Syracuse");
    query3(C,"shdjbjusbiu");
    query3(C, "UNC");
    cout<<"---------------after 4--------------"<<endl;
    query4(C, "NC", "DarkBlue");
    query4(C, "MA", "Maroon");
    query4(C, "SX", "White");
    query4(C, "MA", "Maroon");
    query4(C, "NY", "Green");
    cout<<"---------------after 5--------------"<<endl;
    query5(C,10);
    query5(C, 16);
    query5(C, 20);
    query5(C,100);
    cout<<"---------------after 6--------------"<<endl;
    
    cout<<"---------------after 7--------------"<<endl;
    
    cout<<"---------------after 8--------------"<<endl;
    
    cout<<"---------------after 9--------------"<<endl;

    cout<<"---------------after 10--------------"<<endl;
    */
    
}