#include "AVLTree.h"

using namespace std;


int main(){
    AVLTree t;
    t.insertNode(3);
	t.insertNode(6);
	t.insertNode(8);
	t.insertNode(10);
	t.insertNode(12);
	t.insertNode(16);
	t.insertNode(20);
	t.insertNode(18);
	t.insertNode(24);
	t.insertNode(19);
    t.display();

    cout<<endl<<endl<<endl;
	t.printTree();
    cout<<endl<<endl<<endl;
    // t.deleteNode(50);
    t.displayPreOrder();


    return 0;
}