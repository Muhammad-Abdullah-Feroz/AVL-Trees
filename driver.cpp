#include "AVLTree.h"

using namespace std;


int main(){
    AVLTree t;
    t.insertNode(50);
	t.insertNode(30);
	t.insertNode(20);
	t.insertNode(25);
	t.insertNode(40);
	t.insertNode(10);
	t.insertNode(70);
	t.insertNode(60);
	t.insertNode(80);
	t.insertNode(90);
    t.display();
    cout<<endl;
    t.deleteNode(50);
    t.display();


    return 0;
}