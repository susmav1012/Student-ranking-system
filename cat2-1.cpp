#include <iostream>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
using namespace std;

void reset()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 15);	//sets the colour to default colour(black)
}

void red1()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 4);	//sets the colour to red
}

void green()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 2);	//sets the colour to Green
}

int n = 0;
enum Colour
{
	red,
	black
};

struct student
{
	int roll_no;
	char student_name[20];
	char dept[50];
	char tutname[20];
	char phnum[11];
	char bldgrp[10];
	float tamil, english, maths, science, social_science;
	float total;
	float avg;
};

struct node
{
	struct student e;
	Colour colour;
	struct node * left;
	struct node * right;
	struct node * parent;

	public:
		node() {}

	node(struct student e1)
	{
		e = e1;
		this->colour = red;
		left = right = parent = NULL;
	}

	void moveDown(struct node *nParent);
	bool isOnLeft();
	struct node* sibling();
	bool hasRedChild();
};

struct heaprank
{
	int rollno;
	int mark;
}

marks[30];

class tree
{
	public:
		struct node * root;
	tree()
	{
		root = NULL;
	}

	struct node* insert1_tree(struct node *root, struct node *pt);
	void fixtree(node* &root, node* &pt);
	void rotate_right(struct node *x);
	void rotate_left(struct node *x);
	void get_details();
	void printInorder(struct node *temp);
	void insert1(struct student s);
	void delete1();
	void fixDoubleBlack(struct node *x);
	void delete_val(int x);
	struct node* search(int x);
	void delete_val_node(struct node *ptr);
	struct node* replacing_node(struct node *);
	void swapColors(struct node *u, struct node *v);
	void swapValues(struct node *u, struct node *v);
	struct node* succesor(struct node *);
	int checkrno(struct node *ptr, int rno, int check);
	void display1(struct node *temp);
	void display();
	void searchrec(int rno);

};

class ranklist
{
	private:
		struct heaprank * root1;

	public:
		ranklist()
		{
			root1 = NULL;
		}

	void insertheap(int mark, int rno, int loc);
	void delheap(int num);
	void heapify(struct heaprank marks[], int n, int i);
	void heapSort(struct heaprank marks[], int n);
	void displayheap();
};

void ranklist::insertheap(int mark, int rno, int loc)
{
	int par;
	while (loc > 0)
	{
		par = (loc - 1) / 2;
		if (mark <= marks[par].mark)
		{
			marks[loc].rollno = rno;
			marks[loc].mark = mark;
			return;
		}

		marks[loc].mark = marks[par].mark;
		marks[loc].rollno = marks[par].rollno;
		loc = par;
	}

	marks[0].mark = mark;
	marks[0].rollno = rno;
}

void ranklist::delheap(int num)
{
	int left, right, i, temp, par, tempr;
	for (i = 0; i < n; i++)
	{
		if (num == marks[i].rollno)
		{
			num = marks[i].mark;
			break;
		}
	}

	if (num != marks[i].mark)
	{
		return;
	}

	marks[i] = marks[n - 1];
	n = n - 1;
	par = (i - 1) / 2;
	if (marks[i].mark > marks[par].mark)
	{
		insertheap(marks[i].mark, marks[i].rollno, i);
		return;
	}

	left = 2 *i + 1;
	right = 2 *i + 2;
	while (right < n)
	{
		if (marks[i].mark >= marks[left].mark && marks[i].mark >= marks[right].mark)
			return;
		if (marks[right].mark <= marks[left].mark)
		{
			temp = marks[i].mark;
			tempr = marks[i].rollno;
			marks[i].mark = marks[left].mark;
			marks[i].rollno = marks[left].rollno;
			marks[left].mark = temp;
			marks[left].rollno = tempr;
			i = left;
		}
		else
		{
			temp = marks[i].mark;
			tempr = marks[i].rollno;
			marks[i].mark = marks[right].mark;
			marks[i].rollno = marks[right].rollno;
			marks[right].mark = temp;
			marks[right].rollno = tempr;
			i = right;
		}

		left = 2 *i + 1;
		right = 2 *i + 2;
	}

	if (left == n - 1 && marks[i].mark < marks[left].mark)
	{
		temp = marks[i].mark;
		tempr = marks[i].rollno;
		marks[i].mark = marks[left].mark;
		marks[i].rollno = marks[left].rollno;
		marks[left].mark = temp;
		marks[left].rollno = tempr;
	}
}

void ranklist::heapify(struct heaprank marks[], int n, int i)
{
	int smallest = i;
	int l = 2 *i + 1;
	int r = 2 *i + 2;
	if (l < n && marks[l].mark < marks[smallest].mark)
		smallest = l;
	if (r < n && marks[r].mark < marks[smallest].mark)
		smallest = r;
	if (smallest != i)
	{
		swap(marks[i].mark, marks[smallest].mark);
		swap(marks[i].rollno, marks[smallest].rollno);
		heapify(marks, n, smallest);
	}
}

void ranklist::heapSort(struct heaprank marks[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		heapify(marks, n, i);
	}

	for (int i = n - 1; i > 0; i--)
	{
		swap(marks[0], marks[i]);
		heapify(marks, i, 0);
	}
}

void ranklist::displayheap()
{
	int i;
	if (n == 0)
	{
		cout << "\n\n\n\t\t\t\t\t\t\t\t\t=======================================" << endl;
		red1();
		cout << "\t\t\t\t\t\t\t\t\t\tRANK LIST IS EMPTY\n";
		reset();
		cout << "\t\t\t\t\t\t\t\t\t=======================================" << endl;
		return;
	}

	heapSort(marks, n);
	green();
	cout << "\n\n\n\n\n\t\t\t\t\t\t\t\t\t\tRANK\tROLLNO\tMARK" << endl;
	
	reset();
	 cout << "\n\t\t\t\t\t\t\t\t\t---------------------------------------------------------------" << endl;
	for (i = 0; i < n; i++)
	{
		cout << "\n\n\n\n\t\t\t\t\t\t\t\t\t\t" <<
			i + 1;
		cout << "\t" << marks[i].rollno;
		cout << "\t" << marks[i].mark;
		cout << "\n";
	}

	cout << "\n";
}

void tree::swapValues(struct node *u, struct node *v)
{
	int temp = 0;
	temp = u->e.roll_no;
	u->e.roll_no = v->e.roll_no;
	v->e.roll_no = temp;
}

void tree::swapColors(struct node *u, struct node *v)
{
	Colour temp;
	temp = u->colour;
	u->colour = v->colour;
	v->colour = temp;
}

bool node::hasRedChild()
{
	return (left != NULL && left->colour == red) || (right != NULL && right->colour == red);
}

bool node::isOnLeft()
{
	return this == parent->left;
}

struct node *node::sibling()
{
	if (parent == NULL)
	{
		return NULL;
	}

	if (isOnLeft())
	{
		return parent->right;
	}
	else
	{
		return parent->left;
	}
}

struct node *tree::succesor(struct node *x)
{
	struct node *ptr = x;
	struct node * temp;
	while (ptr != NULL)
	{
		temp = ptr;
		ptr = ptr->left;
	}

	// cout<<temp->data<<endl;
	return temp;
}

int tree::checkrno(struct node *ptr, int rno, int check)
{
	if (ptr != NULL)
	{
		checkrno(ptr->left, rno, check);
		if (rno == ptr->e.roll_no)
			check = 1;
		checkrno(ptr->right, rno, check);
	}

	return check;
}

void tree::display1(struct node *temp)
{
	if (temp != NULL)
	{
		display1(temp->left);
		cout << "\n\n\n\t\t\t\t\t\t\t---------------------------------------------------------------" << endl;
		if (temp->colour == 0)
		{
			cout << "\t\t\t\t\t\t\t\t\t***********************" << endl;
			red1();
			cout << "\t\t\t\t\t\t\t\t\tCOLOUR: RED" << endl;
			reset();
			cout << "\t\t\t\t\t\t\t\t\t***********************" << endl;
		}

		if (temp->colour)
		{
			cout << "\t\t\t\t\t\t\t\t\t***********************" << endl;
			cout << "\t\t\t\t\t\t\t\t\tCOLOUR: BLACK" << endl;
			cout << "\t\t\t\t\t\t\t\t\t***********************" << endl;
		}

		green();
		cout << "\n\n\n\t\t\t\t\t\t\t\t\t\tSTUDENT RECORD:\n";
		reset();
		cout << "\t\t\t\t\t\t\t\t\t=======================================" << endl;
		if (temp->colour == 0)
		{
			red1();
			cout << "\n\t\t\t\t\t\t\t\t\t\tSTUDENT NAME :" << temp->e.student_name <<
			"\n\t\t\t\t\t\t\t\t\t\tROLL NUMBER :" << temp->e.roll_no <<
			"\n\t\t\t\t\t\t\t\t\t\tCLASS :" << temp->e.dept <<
			"\n\t\t\t\t\t\t\t\t\t\tTUTOR NAME:" << temp->e.tutname <<
			"\n\t\t\t\t\t\t\t\t\t\tPHONE NUMBER :" << temp->e.phnum <<
			"\n\t\t\t\t\t\t\t\t\t\tBLOOD GROUP :" << temp->e.bldgrp <<
			"\n\t\t\t\t\t\t\t\t\t\tTOTAL:" << temp->e.total <<
			"\n\t\t\t\t\t\t\t\t\t\tAVERAGE :" << temp->e.avg;
			reset();
		    cout << "\n\t\t\t\t\t\t\t---------------------------------------------------------------" << endl;
		}
		else
		{
			cout << "\n\t\t\t\t\t\t\t\t\t\tSTUDENT NAME :" << temp->e.student_name <<
			"\n\t\t\t\t\t\t\t\t\t\tROLL NUMBER :" << temp->e.roll_no <<
			"\n\t\t\t\t\t\t\t\t\t\tCLASS :" << temp->e.dept <<
			"\n\t\t\t\t\t\t\t\t\t\tTUTOR NAME:" << temp->e.tutname <<
			"\n\t\t\t\t\t\t\t\t\t\tPHONE NUMBER :" << temp->e.phnum <<
			"\n\t\t\t\t\t\t\t\t\t\tBLOOD GROUP :" << temp->e.bldgrp <<
			"\n\t\t\t\t\t\t\t\t\t\tTOTAL:" << temp->e.total <<
			"\n\t\t\t\t\t\t\t\t\t\tAVERAGE :" << temp->e.avg;
		    cout << "\n\t\t\t\t\t\t\t---------------------------------------------------------------" << endl;
			
		}
		
	
		display1(temp->right);
	}
}

void tree::display()
{
	struct node *temp = root;
	if (root == NULL)
	{
		cout << "\n\n\n\t\t\t\t\t\t\t\t\t=======================================" << endl;
		red1();
		cout << "\t\t\t\t\t\t\t\t\t\tTHERE ARE NO RECORDS" << endl;
		reset();
		cout << "\t\t\t\t\t\t\t\t\t=======================================" << endl;
	}

	display1(temp);
}

void node::moveDown(struct node *nParent)
{
	if (parent != NULL)
	{
		if (isOnLeft())
		{
			parent->left = nParent;
		}
		else
		{
			parent->right = nParent;
		}
	}

	nParent->parent = parent;
	parent = nParent;
}

void tree::rotate_left(struct node *x)
{
	struct node *nParent = x->right;
	if (x == root)
		root = nParent;
	x->moveDown(nParent);
	x->right = nParent->left;
	if (nParent->left != NULL)
		nParent->left->parent = x;
	nParent->left = x;
}

void tree::rotate_right(struct node *x)
{
	struct node *nParent = x->left;
	if (x == root)
		root = nParent;
	x->moveDown(nParent);
	x->left = nParent->right;
	if (nParent->right != NULL)
		nParent->right->parent = x;
	nParent->right = x;
}

void tree::fixtree(node* &root, node* &pt)
{
	struct node *parent_pt = NULL;
	struct node *grand_parent = NULL;
	while ((pt != root) && (pt->colour != black) && (pt->parent->colour == red))
	{
		parent_pt = pt->parent;
		grand_parent = pt->parent->parent;
		if (parent_pt == grand_parent->left)
		{
			struct node *sibling = grand_parent->right;
			if (sibling != NULL && sibling->colour == red)
			{
				grand_parent->colour = red;
				parent_pt->colour = black;
				sibling->colour = black;
				pt = grand_parent;
			}
			else
			{
				if (pt == parent_pt->right)
				{
					rotate_left(parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}

				rotate_right(grand_parent);
				swap(parent_pt->colour, grand_parent->colour);
				pt = parent_pt;
			}
		}
		else
		{
			struct node *sibling = grand_parent->left;
			if ((sibling != NULL) && (sibling->colour == red))
			{
				grand_parent->colour = red;
				parent_pt->colour = black;
				sibling->colour = black;
				pt = grand_parent;
			}
			else
			{
				if (pt == parent_pt->left)
				{
					rotate_right(parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}

				rotate_left(grand_parent);
				swap(parent_pt->colour, grand_parent->colour);
				pt = parent_pt;
			}
		}
	}

	root->colour = black;
}

struct node *tree::insert1_tree(struct node *root, struct node *pt)
{
	if (root == NULL)
		return pt;
	if (pt->e.roll_no < root->e.roll_no)
	{
		root->left = insert1_tree(root->left, pt);
		root->left->parent = root;
	}
	else if (pt->e.roll_no > root->e.roll_no)
	{
		root->right = insert1_tree(root->right, pt);
		root->right->parent = root;
	}

	return root;
}

void tree::get_details()
{
	ranklist r;
	struct student s;
	fflush(stdin);
	int check = 0;
	cout << "\n\n\t\t\t\t\t\t\t\t\tENTER THE STUDENT ROLL NUMBER:";
	cin >> s.roll_no;
	int checkrollnumber = checkrno(root, s.roll_no, check);
	if (checkrollnumber == 0)
	{
		fflush(stdin);
		cout << "\n\t\t\t\t\t\t\t\t\tENTER NAME:";
		cin >> s.student_name;
		fflush(stdin);
		cout << "\n\t\t\t\t\t\t\t\t\tENTER THE CLASS:";
		cin >> s.dept;
		fflush(stdin);
		cout << "\n\t\t\t\t\t\t\t\t\tENTER THE TUTOR NAME:";
		cin >> s.tutname;
		fflush(stdin);
		cout << "\n\t\t\t\t\t\t\t\t\tENTER THE PHONE NUMBER:";
		cin >> s.phnum;
		while ((strlen(s.phnum) != 10))
		{
			red1();
			cout << "\t\t\t\t\t\t\t\t\tENTER VALID PHONE NUMBER: ";
			reset();
			cin >> s.phnum;
		}

		fflush(stdin);
		cout << "\n\t\t\t\t\t\t\t\t\tENTER BLOOD GROUP:";
		cin >> s.bldgrp;
		fflush(stdin);
		cout << "\n\t\t\t\t\t\t\t\t\tENTER TAMIL MARK:";
		cin >> s.tamil;
		while (s.tamil <= 0 || s.tamil > 100)
		{
			red1();
			cout << "\n\t\t\t\t\t\t\t\t\tYOUR MARK IS INVALID\n\t\t\t\t\t\t\t\t\t ENTER VALID MARKS(1 to 100):";
			reset();
			cin >> s.tamil;
		}

		fflush(stdin);
		cout << "\n\t\t\t\t\t\t\t\t\tENTER ENGLISH MARK:";
		cin >> s.english;
		while (s.english <= 0 || s.english > 100)
		{
			red1();
			cout << "\n\t\t\t\t\t\t\t\t\tYOUR MARK IS INVALID\n\t\t\t\t\t\t\t\t\t ENTER VALID MARKS(1 to 100):";
			reset();
			cin >> s.english;
		}

		fflush(stdin);
		cout << "\n\t\t\t\t\t\t\t\t\tENTER MATHS MARK:";
		cin >> s.maths;
		while (s.maths <= 0 || s.maths > 100)
		{
			red1();
			cout << "\n\t\t\t\t\t\t\t\t\tYOUR MARK IS INVALID\n\t\t\t\t\t\t\t\t\t ENTER VALID MARKS(1 to 100):";
			reset();
			cin >> s.maths;
		}

		fflush(stdin);
		cout << "\n\t\t\t\t\t\t\t\t\tENTER SCIENCE MARK:";
		cin >> s.science;
		while (s.science <= 0 || s.science > 100)
		{
			red1();
			cout << "\n\t\t\t\t\t\t\t\t\tYOUR MARK IS INVALID\n\t\t\t\t\t\t\t\t\t ENTER VALID MARKS(1 to 100):";
			reset();
			cin >> s.science;
		}

		fflush(stdin);
		cout << "\n\t\t\t\t\t\t\t\t\tENTER SOCIAL SCIENCE MARK:";
		cin >> s.social_science;
		while (s.social_science <= 0 || s.social_science > 100)
		{
			red1();
			cout << "\n\t\t\t\t\t\t\t\t\tYOUR MARK IS INVALID\n\t\t\t\t\t\t\t\t\t ENTER VALID MARKS(1 to 100):";
			reset();
			cin >> s.social_science;
		}

		fflush(stdin);
		s.total = s.tamil + s.english + s.maths + s.science + s.social_science;
		cout << "\n\n\n\t\t\t\t\t\t\t\t\tTOTAL: " << s.total;
		s.avg = s.total / 5;
		cout << "\n";
		cout << "\t\t\t\t\t\t\t\t\tAVERAGE: " << s.avg<<endl;
		fflush(stdin);
		r.insertheap(s.total, s.roll_no, n);
		n = n + 1;
		insert1(s);
	}
	else
	{
		cout << "\n\n\n\n\t\t\t\t\t\t\t\t\t==========================================================" << endl;
		red1();
		cout << endl << "\t\t\t\t\t\t\t\t\t\tTHE ENTERED ROLL NUMBER IS PRESENT ALREADY!!";
		reset();
		cout << "\t\t\t\t\t\t\t\t\t==========================================================" << endl;
	}
}

void tree::insert1(struct student s)
{
	struct node *temp = new node(s);
	root = insert1_tree(root, temp);
	fixtree(root, temp);
}

struct node *tree::search(int x)
{
	struct node *temp = root;
	while (temp != NULL)
	{
		if (x < temp->e.roll_no)
		{
			if (temp->left == NULL)
			{
				break;
			}
			else
			{
				temp = temp->left;
			}
		}
		else if (x == temp->e.roll_no)
		{
			break;
		}
		else
		{
			if (temp->right == NULL)
			{
				break;
			}
			else
			{
				temp = temp->right;
			}
		}
	}

	return temp;
}

void tree::searchrec(int rno)
{
	struct node *ptr = search(rno);
	if (ptr == NULL)
	{
		cout << "\n\n\n\n\t\t\t\t\t\t\t\t\t=======================================" << endl;
		red1();
		cout << "\t\t\t\t\t\t\t\t\t\tTHERE ARE NO RECORDS" << endl;
		reset();
		cout << "\t\t\t\t\t\t\t\t\t=======================================" << endl;
		return;
	}

	if (rno != ptr->e.roll_no)
	{
		cout << "\n\n\n\n\t\t\t\t\t\t\t\t\t=======================================" << endl;
		red1();
		cout << "\t\t\t\t\t\t\t\t\t\tROLL NUMBER DOES NOT EXIST" << endl;
		reset();
		cout << "\t\t\t\t\t\t\t\t\t=======================================" << endl;
		return;
	}
	else
	{
		cout << "\t\t\t\t\t\t\t---------------------------------------------------------------" << endl;
		cout << ptr->colour << endl;
		if (ptr->colour == 0)
		{
			cout << "\t\t\t\t\t\t\t\t\t***********************" << endl;
			red1();
			cout << "\t\t\t\t\t\t\t\t\tCOLOUR: RED" << endl;
			reset();
			cout << "\t\t\t\t\t\t\t\t\t***********************" << endl;
		}

		if (ptr->colour == 1)
		{
			cout << "\t\t\t\t\t\t\t\t\t***********************" << endl;
			cout << "\t\t\t\t\t\t\t\t\tCOLOUR: BLACK" << endl;
			cout << "\t\t\t\t\t\t\t\t\t***********************" << endl;
		}

		green();
		cout << "\t\t\t\t\t\t\t\t\t\tSTUDENT RECORD:\n";
		reset();
		cout << "\t\t\t\t\t\t\t\t=======================================" << endl;
		cout << "\n\t\t\t\t\t\t\t\t\t\tSTUDENT NAME :" << ptr->e.student_name <<
			"\n\t\t\t\t\t\t\t\t\t\tROLL NUMBER :" << ptr->e.roll_no <<
			"\n\t\t\t\t\t\t\t\t\t\tCLASS :" << ptr->e.dept <<
			"\n\t\t\t\t\t\t\t\t\t\tTUTOR NAME:" << ptr->e.tutname <<
			"\n\t\t\t\t\t\t\t\t\t\tPHONE NUMBER :" << ptr->e.phnum <<
			"\n\t\t\t\t\t\t\t\t\t\tBLOOD GROUP :" << ptr->e.bldgrp <<
			"\n\t\t\t\t\t\t\t\t\t\tTOTAL:" << ptr->e.total <<
			"\n\t\t\t\t\t\t\t\t\t\tAVERAGE :" << ptr->e.avg;
		cout << "\n\t\t\t\t\t\t\t---------------------------------------------------------------" << endl;

	}
}

void tree::fixDoubleBlack(struct node *x)
{
	if (x == root)
		return;
	struct node *sibling = x->sibling(), *parent = x->parent;
	if (sibling == NULL)
	{
		fixDoubleBlack(parent);	// No sibiling, double black pushed up
	}
	else
	{
		if (sibling->colour == red)
		{
			parent->colour = red;	// Sibling red
			sibling->colour = black;
			if (sibling->isOnLeft())
			{
				rotate_right(parent);	// left case
			}
			else
			{
				rotate_left(parent);	// right case
			}

			fixDoubleBlack(x);
		}
		else
		{
			if (sibling->hasRedChild())	// Sibling black
			{
				if (sibling->left != NULL and sibling->left->colour == red)	// at least 1 red children
				{
					if (sibling->isOnLeft())
					{
						sibling->left->colour = sibling->colour;	// left left
						sibling->colour = parent->colour;
						rotate_right(parent);
					}
					else
					{
						sibling->left->colour = parent->colour;	// right left
						rotate_right(sibling);
						rotate_left(parent);
					}
				}
				else
				{
					if (sibling->isOnLeft())
					{
						sibling->right->colour = parent->colour;	// left right
						rotate_left(sibling);
						rotate_right(parent);
					}
					else
					{
						sibling->right->colour = sibling->colour;	// right right
						sibling->colour = parent->colour;
						rotate_left(parent);
					}
				}

				parent->colour = black;
			}
			else
			{
				sibling->colour = red;	// 2 black children
				if (parent->colour == black)
					fixDoubleBlack(parent);
				else
					parent->colour = black;
			}
		}
	}
}

struct node *tree::replacing_node(struct node *ptr)
{
	if (ptr->left != NULL && ptr->right != NULL)
	{
		return succesor(ptr->right);
	}

	if (ptr->left == NULL && ptr->right == NULL)
	{
		return NULL;
	}

	if ((ptr->left != NULL))
	{
		return ptr->left;
	}
	else
	{
		return ptr->right;
	}
}

void tree::delete_val_node(struct node *ptr)
{
	struct node *u = replacing_node(ptr);
	bool dbblack = ((u == NULL || u->colour == black) && (ptr->colour == black));
	struct node *parent = ptr->parent;
	if (u == NULL)
	{
		if (ptr == root)
		{
			root = NULL;
		}
		else
		{
			if (dbblack)
			{
				fixDoubleBlack(ptr);
			}
			else
			{
				if (ptr->sibling() != NULL)	// u or v is red

					ptr->sibling()->colour = red;	// sibling is not null, make it red" }

			if (ptr->isOnLeft())	// delete v from the tree
			{
				parent->left = NULL;
			}
			else
			{
				parent->right = NULL;
			}
		}

		delete ptr;
		return;
	}

	if (ptr->left == NULL || ptr->right == NULL)
	{
		if (ptr == root)	// v has 1 child
		{
			ptr->e.roll_no = u->e.roll_no;	// v is root, assign the value of u to v, and delete u
			ptr->left = ptr->right = NULL;
			delete u;
		}
		else
		{
			if (ptr->isOnLeft())	// Detach v from tree and move u up
			{
				parent->left = u;
			}
			else
			{
				parent->right = u;
			}

			delete ptr;
			u->parent = parent;
			if (dbblack)
			{
				fixDoubleBlack(u);	// u and v both black, fix double black at u
			}
			else
			{
				u->colour = black;	// u or v red, color u black
			}
		}

		return;
	}

	swapValues(u, ptr);	// v has 2 children, swap values with successor and recurse
	delete_val_node(u);
}
}

void tree::delete1()
{
	int x = 0;
	cout << "\n\n\n\t\t\t\t\t\t\t\t\tENTER THE ROLL NUMBER TO BE DELETED:";
	cin >> x;
	if (root == NULL)
	{
		cout << "\n\n\n\t\t\t\t\t\t\t\t\t=======================================" << endl;
		red1();
		cout << "\t\t\t\t\t\t\t\t\t\tTHERE ARE NO RECORDS " << endl;
		reset();
		cout << "\t\t\t\t\t\t\t\t\t=======================================" << endl;
		return;
	}
	else
	{
		delete_val(x);
	}
}

void tree::delete_val(int x)
{
	struct node *ptr = search(x);
	ranklist r;
	if (x != ptr->e.roll_no)
	{
		cout << "\n\n\n\t\t\t\t\t\t\t\t\t=======================================" << endl;
		red1();
		cout << "\t\t\t\t\t\t\t\t\t\tROLL NUMBER DOES NOT EXIST" << endl;
		reset();
		cout << "\t\t\t\t\t\t\t\t\t=======================================" << endl;
		return;
	}
	else
	{
		delete_val_node(ptr);
		r.delheap(x);
		cout << "\n\n\n\t\t\t\t\t\t\t\t\t=======================================" << endl;
		red1();
		cout << "\t\t\t\t\t\t\t\t\t\tRECORD DELETED SUCCESSFULLY " << endl;
		reset();
		cout << "\t\t\t\t\t\t\t\t\t=======================================" << endl;
	}
}

int main()
{
	tree t;
	ranklist r;
	int choice = 0;
	int rno;
	while (true)
	{
		cout << endl << endl;
		green();
		cout << "\t\t\t\t\t\t\t\t\t\tSTUDENT MANAGEMENT SYSTEM" << endl;
		reset();
		cout << "\t\t\t\t\t\t\t\t\t=======================================" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t1.INSERT RECORD" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t2.DISPLAY RECORD" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t3.DELETE A RECORD" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t4.DISPLAY RANK LIST" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t5.SEARCH A RECORD" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t6.EXIT" << endl;
		cout << "\t\t\t\t\t\t\t\t\t=======================================" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\tENTER YOUR CHOICE:";
		cin >> choice;
		switch (choice)
		{
			case 1:
				{
					t.get_details();
					system("pause");
				    system("cls");
					break;
				}

			case 2:
				{
					t.display();
					system("pause");
				    system("cls");
					break;
				}

			case 3:
				{
					t.delete1();
					system("pause");
				    system("cls");
					break;
				}

			case 4:
				{
					r.displayheap();
					system("pause");
				    system("cls");
					break;
				}

			case 5:
				{
					cout << endl << "\n\n\n\t\t\t\t\t\t\t\t\tENTER THE ROLL NUMBER TO DISPLAY THE RECORD:";
					cin >> rno;
					t.searchrec(rno);
					system("pause");
				    system("cls");
					break;
				}

			case 6:
				{
					exit(0);
					break;
				}

			default:
			    cout << "\n\n\n\t\t\t\t\t\t\t\t\t==========================================" << endl;
				red1();
				cout << "\t\t\t\t\t\t\t\t\t\tENTER VALID CHOICE!!!!" << endl;
				reset();
				cout << "\t\t\t\t\t\t\t\t\t==========================================" << endl;
				system("pause");
				system("cls");
		}
	}

	return 0;
}
