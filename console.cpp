#include "linked_list.cpp"

using namespace list;

int main() {

	LinkedList<int> l;
	/*Node<int>* x = new Node(1);
	Node<int>* y = new Node(-2);
	Node<int>* z = new Node(3);*/

	LinkedList<int> l2;
	/*Node<int>* a = new Node(4);
	Node<int>* b = new Node(6);
	Node<int>* c = new Node(-7);*/

	LinkedList<int> l4;
	/*Node<int>* e = new Node(10);
	Node<int>* s = new Node(41);
	Node<int>* q = new Node(-77);*/

	l.push_head(1);
	l.push_tail(3);
	l.push_head(-2);

	/*cout << l;*/

	l2.push_head(4);
	l2.push_tail(6);
	l2.push_head(-77);

	l4.push_head(10);
	l4.push_tail(11);
	l4.push_head(-77);

	//cout << l4 << endl;

	/*cout << l << endl;
	cout << l2 << endl;
	cout << l4 << endl;

	LinkedList<int> l5;
	l5 = l2;

	cout << l5 << endl;

	cout << l5.get_elem() << endl;

	l.delete_node(3);

	cout << l << endl;

	l2.push_tail(l);
	l5.push_head(l4);

	cout << l5 << endl;
	cout << l2 << endl;*/

	LinkedList<int> l3;
	l3 = merge(l4, l2);
	removeDuplicates(l3);
	cout << l3 << endl;

	/*cout << l3[0];*/
	
	return 0;
}