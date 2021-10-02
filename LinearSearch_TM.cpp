#include <bits/stdc++.h>

#define X 2
#define B 3
#define R 1
#define L - 1
#define INV {-1, -1, -1}
//INV = { -1,-1,-1} -> invalid function

using namespace std;

struct transition {
   int state;
   int tape_symbol;
   int direction;
};

class LinearSearch {
   public:
      int tape[1000];
   //Transition Function Table
    transition transition_function[19][4]={
    //  0   ,     1   ,     X   ,     B   ,
    {{ 1,B,R}, { 5,B,R},      INV,      INV}, // q0
    {{ 1,0,R}, { 2,1,R},      INV,      INV}, // q1
    { {1,0,R}, { 3,1,R},      INV,      INV}, // q2
    { {4,X,L}, {14,1,R}, { 3,X,R},      INV}, // q3
    { {4,0,L}, { 4,1,L}, { 4,X,L}, { 0,B,R}}, // q4
    {{ 6,0,R}, { 8,1,R},      INV,      INV}, // q5
    {{ 6,0,R}, { 7,1,R},      INV, {17,1,L}}, // q6
    {{ 6,0,R}, { 8,1,R},      INV,      INV}, // q7
    {{ 9,0,R}, {11,1,R}, { 8,X,R},      INV}, // q8
    {{ 9,0,R}, { 9,1,R},      INV, {10,0,L}}, // q9
    {{10,0,L}, {10,1,L}, {10,0,L}, { 0,B,R}}, // q10
    {{11,0,R},      INV,      INV, {12,0,L}}, // q11
    {{12,0,L}, {13,B,L},      INV,      INV}, // q12
    {{13,B,L}, {13,B,L}, {13,B,L}, {18,B,R}}, // q13
    {{14,0,R},      INV,      INV, {15,0,L}}, // q14
    {{15,0,L}, {15,1,L}, {15,0,L}, {16,B,R}}, // q15
    {{16,B,R}, { 0,B,R},      INV,      INV}, // q16
   { {17,B,L}, {17,B,L},      INV, {18,B,R}}, // q17
        { INV,      INV,      INV,      INV}  // q18
};

   int head;
   int c; //Ending non-blank index of tape (Not considering appending zeroes)

   LinearSearch(int ip_elements[], int size, int key) {
      head = 100;
      for (int i = 0; i < 1000; i++)
         tape[i] = B;

      intialize_tape(ip_elements, size, key);
   }

   // initialize_tape() loads the input record of elements onto the infinite tape
   void intialize_tape(int ip_elements[], int size, int key) //ip_element ->input_elements
   {
      c = head;

      for (int i = 0; i < size; i++) {
         while (ip_elements[i]--) {
            tape[c++] = 0;
         }
         tape[c++] = 1; //End of a particular element
      }

      tape[c++] = 1; //End of all elements

      while (key--) {
         tape[c++] = 0; //key to be searched
      }

      tape[c++] = 1; // Final 1, after which index is stored if an element exists

      cout << "Elements have been loaded unto the tape....\n";
      cout<<"Initial State of ";
      print_tape(head - 1, c + 1);
      cout<<"\n--------------------------------------------------------------\n";

   }

   // simulate_TM() - simulates the actual working of a TM for linear search
   void simulate_TM(int ip_elements[], int size, int key, int sum) {

      int q_cur = 0; //current state
      int j = head; //j -> current index under observation
      int dir; //direction to move to from current state
	  int i=0; //Iterator to simply keep track of steps for illustrative purposes only
	  
      while (q_cur != 18 && transition_function[q_cur][tape[j]].state != -1) //handle invalid state too? Check Dom
      {
         dir = transition_function[q_cur][tape[j]].direction;

         int temp = transition_function[q_cur][tape[j]].state; //temp variable to store q_cur so does not affect next line

         tape[j] = transition_function[q_cur][tape[j]].tape_symbol;

         q_cur = temp;

         j = j + dir; //Moving Finite control according to Tranition Function
         
         cout<<"Step "<<i++<<" - ";
         print_tape(head-1,c+size);

      }
		cout<<"\n--------------------------------------------------------------\n";
		cout<<"Final State of ";
		print_tape(head - 1, c + sum);
		
      if (q_cur != 18 && transition_function[q_cur][tape[j]].state == -1) {

         cout << "Invalid Entry! Do retry!";
        
      } else {
		 
		 int index=scan_tape();
		 if(index==-1)  //Not needed though
         cout<<"The desired element cannot be found";
         else
         cout << "The element has been found at index :" << index << endl;

      }

      
   }

   //helper function to return index at which element exists
   int scan_tape() {
      int index = 0;
      int done = 0; //Signals if we have reached stream of zeroes that signify the index of searched element

      for (int i = head; i < 200; i++) //max- 200 for now
      {
         if (tape[i] == B & done == 0)
            continue;
         if (tape[i] == B & done == 1)
            break;
         if (tape[i == 0]) {
            index++; //Increment index for as many no of zeroes there are
            done = 1;
         }
         if (tape[i] == 1) {
            return -1; // Returns -1 if not found
            break;
         }

      }

      return index;
   }

//Helper function to print the infinite tape
   void print_tape(int low, int high) {
      cout << "Tape :- \n";

      for (int i = low; i < high; i++) {
         if (tape[i] == B) {
            cout << "B";
         } else if (tape[i] == X) {
            cout << "X";
         } else
            cout << tape[i];
      }
      cout << "\n";
   }

};

int main() {

   int size, key, sum;
   cout << "Enter the number of elements \n";
   cin >> size;
   int * tape_elements = (int * ) malloc(sizeof(int) * size);

   cout << "Enter the Elements \n";
   for (int i = 0; i < size; i++) {
      cin >> tape_elements[i];
      if (tape_elements[i] < 0) {
         cout << "Enter a Positive Number \n";
         cin >> tape_elements[i];
      }
      sum=sum+tape_elements[i];
   }

   cout << "Enter the element to be searched \n";
   cin >> key;

cout<<"\n--------------------------------------------------------------\n";
cout<<"\t  THE TURING MACHINE MAGIC BEGINS!\n";
   LinearSearch ls(tape_elements, size, key); //Instance of Linear Search Class
   ls.simulate_TM(tape_elements, size, key,sum);

}
