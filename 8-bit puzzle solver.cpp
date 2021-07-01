#include<iostream>
using namespace std;
class puzzle{
    private:
    	struct Node{
    		int matrix[9];
			Node *next=NULL;	
		}*initial,*head,*temphead;
        string data;
		int goal[9];
		int moves;
		
    public:
    	puzzle(){
    		bool flag;
    		flag=genratePuzzle();
    		if(flag){
    		int puzzle[3][3];
    		int a=0;
    		for(int i=0;i<3;i++){
    			for(int j=0;j<3;j++){
    				puzzle[i][j]=initial->matrix[a];
    				a++;}}
    		if(isSolvable(puzzle)==false)
    		cout<<"\n         Insolveable condition!!!\n";
    		if(isSolvable(puzzle)){
    		initial->next=NULL;
    		head=initial;
    		temphead=head;
    		head->next=NULL;
    		temphead->next=NULL;
    		for(int i=0;i<9;i++)
    		goal[i]=i;
    		moves=0;;
			bool flag=check_goal(initial);
			if(flag==false)	
			solve();	}}
		}
		int getInvCount(int arr[]);
		bool isSolvable(int puzzle[3][3]);
        bool  genratePuzzle();
        bool check_goal(struct Node *ptr);
		void possiblemoves(struct Node *ptr);
		int calculateCost(struct Node* ptr);
		void up(struct Node *ptr,int a);
		void down(struct Node *ptr,int a);
		void right(struct Node *ptr,int a);
		void left(struct Node *ptr,int a);
		void choosemove(struct Node *ptr);
		void solve();
		void display(struct Node *ptr);
		bool check(struct Node *n);
};
int main(){
		puzzle p1;
}
void puzzle::display(struct Node *ptr){
	cout<<"               ";
	for(int i=0;i<9;i++){
		cout<<ptr->matrix[i]<<"  ";
		if((i-2)%3==0)
		cout<<endl<<"               ";
	}
}
bool puzzle::genratePuzzle(){
    cout<<"********** The A* algorith**********\n";
    cout<<"   ***Create initial state 0-8***\n";
    bool flag=true;
	for(int i=0;i<9;i++){
      cout<<"          Enter value "<<i+1<<": ";
      cin>>initial->matrix[i];
      for(int j=0;j<i;j++){
      	if(initial->matrix[i]==initial->matrix[j]){
      	cout<<"\n\n          repeated value ";
      	flag=false;
		break;
		}}
      	if(initial->matrix[i]<0 ||initial->matrix[i]> 8){
        	cout<<"\n\n          Invalid value  ";
			flag=false;		
			break;
		}
    }
    return flag;
}
bool puzzle::check_goal(struct Node *ptr){
    bool check = true;
    for(int i=0;i<9;i++){
        if(ptr->matrix[i] != goal[i]){
            check = false;
            break;
        }
    }
    return check;
}
void puzzle::possiblemoves(struct Node *ptr){
			int i=0;
			for(;i<9;i++){
				if(ptr->matrix[i]==0)
				break;
			}
			Node *t= new Node;
			for(int j=0;j<9;j++)
				t->matrix[j]=ptr->matrix[j];
			switch(i){
				case 0:{
					down(t,0);
					right(t,0);
					break;
				}
				case 1:{
						left(t,1);
						right(t,1);
						down(t,1);
					break;
				}
				case 2:{
						left(t,2);
						down(t,2);
					break;
				}
				case 3:{
						up(t,3);
						right(t,3);
						down(t,3);
					break;
				}
				case 4:{
						up(t,4);
						right(t,4);
						down(t,4);
						left(t,4);
					break;
				}
				case 5:{
						up(t,5);
						left(t,5);
						down(t,5);
					break;
				}
				case 6:{
						up(t,6);
						right(t,6);
					break;
				}
				case 7:{
						up(t,7);
						left(t,7);
						right(t,7);
					break;
				}
				case 8:
						up(t,8);
						left(t,8);
			}
			choosemove(t);
		}
int puzzle::calculateCost(struct Node* ptr) {
	int count = 0; 
	for (int i = 0; i < 9; i++){
		if (i>0 && ptr->matrix[i] != goal[i]) 
			count=count+2; 
		else if(ptr->matrix[i] != goal[i])
		count++;}
	return count; 
		} 
void puzzle::up(struct Node *ptr,int a){
			ptr->matrix[a]=ptr->matrix[a-3];
			ptr->matrix[a-3]=0;
		}	
void puzzle::down(struct Node *ptr,int a){
			ptr->matrix[a]=ptr->matrix[a+3];
			ptr->matrix[a+3]=0;
		}
void puzzle::right(struct Node *ptr,int a){
			ptr->matrix[a]=ptr->matrix[a+1];
			ptr->matrix[a+1]=0;
		}
void puzzle::left(struct Node *ptr,int a){
			ptr->matrix[a]=ptr->matrix[a-1];
			ptr->matrix[a-1]=0;
		}
void puzzle::choosemove(struct Node *ptr){
	Node *temp = new Node;
	temp=ptr->next;
	Node *temp1 = new Node;
	temp1=ptr->next;
	int i=100;
	while(temp){
		if(calculateCost(temp)<i){
			i=calculateCost(temp);
			temp1=temp;
		}
		temp=temp->next;
	}
	head->next=temp1;
	head=temp1;
	temphead=temp1;
}
void puzzle::solve(){
	Node *temp=new Node;
	temp=initial;
	bool flag=false;
	while(temp){
		display(temp);
		possiblemoves(temp);
		flag=check_goal(temp);
		if(flag)
		break;
		cout<<"   |\n                  |\n                 \\ /"<<endl;
		temp=temp->next;
	}
}
int puzzle::getInvCount(int arr[]) 
{ 
    int inv_count = 0; 
    for (int i = 0; i < 9 - 1; i++) 
        for (int j = i+1; j < 9; j++)  
            if (arr[j] && arr[i] &&  arr[i] > arr[j]) 
            	inv_count++; 
    return inv_count; 
} 
bool puzzle::isSolvable(int puzzle[3][3]) {
    int invCount = getInvCount((int *)puzzle); 
    return (invCount%2 == 0); 
}
