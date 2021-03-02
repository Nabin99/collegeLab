/*
    ***********************************************
    this program doesnot use any library except
    standard iostream
    fill free to explore modify the code
    there are no any copyright restirctions(:-)(:-)
    there are for sure many bugs
    fix them and contribute to this
    lab work
    **********************************************


    *********** Developer Nabin Dhital ************
    ********** Bsc.CSIT student at PMC ************

    ******note this is not a professional work*****
    ******this is the longest *********************
    ******single i have ever written***************
*/




#include <iostream>

using namespace std;

 int l;
 int k=-1,j=0,i=0,n=0,leafcnt=1,c=0,Dtlist=0,scnt=0;
 char regexp[100],operatornode[100], sigma[50];

 struct follow{

    int s=0;
    struct node* nodeptr=NULL;
    int followpos[50];
 };

struct Pos{
    int firstpos[50];
    int lastpos[50];
 };

 struct node{
 bool nullable=false;
 struct Pos flPos;
 char nodevalue;
 int label=-1;
 struct node* parent=NULL;
 struct node* left_child=NULL;
 struct node* right_child=NULL;

 };

struct node nodetree[100];
struct node* calcarr[100];
struct follow fp[50];

struct Dtransition{
    char symbol='\0';
    int followpos[50];
    struct Dtransition* tran1[50];
    bool finalstate=false;
 };

struct Dtransition Dtran[50];

//function defination of findpos which returns true if the current followpos contains the val passed through agrument
bool findpos(int val , int arr[]){
   int temp=0;
   while(arr[temp]!='\0'){
      if(arr[temp]==val)
         return true;
     temp++;
   }
    return false;
}
//end of findpos

bool findpos(char val , char arr[]){
   int temp=0;
   while(arr[temp]!='\0'){
    if(arr[temp]==val)
        return true;
     temp++;
   }
    return false;
}

bool iseqiv(int arr1[],int arr2[]){
   int c1=0,c2=0;
   int s=0,temp=0;
   while(arr1[c1]!='\0')
    c1++;
   while(arr2[c2]!='\0')
    c2++;
   if(c1<c2)
    c1=c2;
   s=c1;
   c1=0;
    while(c1<s){
       c2=temp=0;
        while(c2<s){
        if(arr1[c1]==arr2[c2]){
            temp++;
            break;
            }
        c2++;
        }
        if (temp==0)
            return false;
        c1++;
    }
    return true;
}

void Dtranstable(){
    int finalstate;
    int *temparr1,m,calcnt=0;
    finalstate=nodetree[l-2].label;
    j=i=0;
    Dtran[Dtlist].symbol='A';
    while(nodetree[l-1].flPos.firstpos[j]!='\0'){
        Dtran[Dtlist].followpos[j]=nodetree[l-1].flPos.firstpos[j];
        if(nodetree[l-1].flPos.firstpos[j]==finalstate)
            Dtran[i].finalstate=true;
        j++;
    }


    while(i<=Dtlist){
    calcnt=0;
     while(calcnt<scnt){
     temparr1=new int[20];
        j=0;m=0;
        while(Dtran[i].followpos[j]!='\0'){


            if(fp[Dtran[i].followpos[j]-1].nodeptr->nodevalue==sigma[calcnt]){

            k=0;
                while(fp[Dtran[i].followpos[j]-1].followpos[k]!='\0'){
                    if(!findpos(fp[Dtran[i].followpos[j]-1].followpos[k],temparr1)){
                        temparr1[m++]=fp[Dtran[i].followpos[j]-1].followpos[k];
                    }
                    k++;
                }
            }


            j++;
        }


        m=0;
        int cnt=0;
        while(m<=Dtlist){
        if(iseqiv(temparr1,Dtran[m].followpos)){
            Dtran[i].tran1[calcnt]=&Dtran[m];
            cnt++;
            break;
        }
        m++;
        }
        if(cnt==0){
          ++Dtlist;
           Dtran[Dtlist].symbol= Dtran[Dtlist-1].symbol+1;

           k=0;
           while(temparr1[k]!='\0'){
                Dtran[Dtlist].followpos[k]=temparr1[k];
                if(temparr1[k]==finalstate)
                    Dtran[Dtlist].finalstate=true;
                k++;
           }
           Dtran[i].tran1[calcnt]=&Dtran[Dtlist];
        }

         calcnt++;
        }

        i++;
    }

}

//function defination of followp which calculates the followpos
void followp(){
   int i=0;
   //below loop runs for every node in nodetree[]
  while(i<l)  {
        if(nodetree[i].nodevalue=='.'){
            //code here runs for every '.' node
            j=0;
            //below loop runs for every lastpos element of left_child
            while(nodetree[i].left_child->flPos.lastpos[j]!='\0'){
                    k=0;
            //below loop runs for every firstpos element of right_child
                  while(nodetree[i].right_child->flPos.firstpos[k]!='\0') {
               if(!findpos(nodetree[i].right_child->flPos.firstpos[k],fp[nodetree[i].flPos.lastpos[j]-1].followpos)){
                    fp[nodetree[i].left_child->flPos.lastpos[j]-1].followpos[fp[nodetree[i].left_child->flPos.lastpos[j]-1].s++]=
                   nodetree[i].right_child->flPos.firstpos[k];//adds every non repeating element of firstpos of right_child to followpos
                   //of every element of left_child

                }

                k++;
                  }
                  j++;
            }
        }
        else if(nodetree[i].nodevalue=='*'){
                //code here runs for every '*' node
                j=0;
                //below loop runs for every element of lastpos
            while(nodetree[i].flPos.lastpos[j]!='\0'){
                    k=0;
                    //below loop runs for every elements of firstpos
                  while(nodetree[i].flPos.firstpos[k]!='\0') {
               if(!findpos(nodetree[i].flPos.firstpos[k],fp[nodetree[i].flPos.lastpos[j]-1].followpos)){
                    fp[nodetree[i].flPos.lastpos[j]-1].followpos[fp[nodetree[i].flPos.lastpos[j]-1].s++]=
                    nodetree[i].flPos.firstpos[k];//adds every non repeating element of firstpos of right_child to followpos
                   //of every element of left_child
                }

                k++;
                  }
                  j++;
            }
        }

i++;
  }
}
//end of followp

//function defination of leafnode
void leafnode(){
            nodetree[j].nodevalue=regexp[i];// adds current char to nodetree[j]
            nodetree[j].label=leafcnt;
            nodetree[j].flPos.lastpos[0]=
            nodetree[j].flPos.firstpos[0]=leafcnt++;//calculates firstpos and lastpos of current nodetree[j]
            fp[leafcnt-2].nodeptr=calcarr[c++] = &nodetree[j++];//adds the address of current nodetree[j] to top of stack calcarr[c]
           if(regexp[i]!='#'){
            if(!findpos(regexp[i],sigma)){
                sigma[scnt++]=regexp[i];
            }
            }

}
//end of leafnode

//function defination of catnode of which calculates the firstpos and lastpos of '.' node
void catnode(){
            nodetree[j].nodevalue=operatornode[k--];// adds top of operatornode stack to nodetree[j]
            nodetree[j].left_child=calcarr[c-2];//adds address in calcarr[c-2] to left_child of current nodetree[j]
            nodetree[j].right_child=calcarr[c-1];//adds address of calcarr[c-1] to right_child of current nodetree[j]
            calcarr[c-2]->parent=calcarr[c-1]->parent=&nodetree[j];//adds parent for top two calcarr stack with address of nodetree[j]
            nodetree[j].nullable=nodetree[j].left_child->nullable&nodetree[j].right_child->nullable;
            int m=n=0;
//calculation of firstpos starts here
            while(calcarr[c-2]->flPos.firstpos[n]!='\0'){

                nodetree[j].flPos.firstpos[m++]= calcarr[c-2]->flPos.firstpos[n++];

            }

            if(calcarr[c-2]->nullable){
               n=0;
            while(calcarr[c-1]->flPos.firstpos[n]!='\0'){

                nodetree[j].flPos.firstpos[m++] =calcarr[c-1]->flPos.firstpos[n++];

            }
            }
            //calculation of firstpos ends here

            m=n=0;
            //calculation of lastpos starts here
            if(calcarr[c-1]->nullable){
            while(calcarr[c-2]->flPos.lastpos[n]!='\0'){

                nodetree[j].flPos.lastpos[m++]= calcarr[c-2]->flPos.lastpos[n++];

            }
            }

            n=0;
            while(calcarr[c-1]->flPos.lastpos[n]!='\0'){

                nodetree[j].flPos.lastpos[m++] =calcarr[c-1]->flPos.lastpos[n++];

                }
                //calculation of lastpos ends here
            c-=2;//decrement the stack top by 2
            calcarr[c++]=&nodetree[j++];//then adds the adderess of nodetree[j] to top of calcarr

}
//end of catnode

//function defination for ornode which calculates firstpos and lastpos of '|' / '+' nodes
void ornode(){
            nodetree[j].nodevalue=operatornode[k--];//adds char from top of operatorstack
            nodetree[j].left_child=calcarr[c-2];//adds address in calcarr[c-2] to the left_child of current nodetree
            nodetree[j].right_child=calcarr[c-1];//adds address in calcarr[c-1] to the right_child of current nodetree
            nodetree[j].nullable=nodetree[j].left_child->nullable|nodetree[j].right_child->nullable;

            calcarr[c-2]->parent=calcarr[c-1]->parent=&nodetree[j];//adds address of current nodetree to the parent of calcarr[c-2]and[c-1]
            int m=n=0;
//calculation of firstpos starts here
            while( calcarr[c-2]->flPos.firstpos[n]!='\0'){

                nodetree[j].flPos.firstpos[m++]= calcarr[c-2]->flPos.firstpos[n++];

            }
            n=0;
            while(calcarr[c-1]->flPos.firstpos[n]!='\0'){

                nodetree[j].flPos.firstpos[m++] =calcarr[c-1]->flPos.firstpos[n++];

            }
            //calculation of firstpos ends here

            m=n=0;
//calculation of lastpos starts here
            while(calcarr[c-2]->flPos.lastpos[n]!='\0'){

                nodetree[j].flPos.lastpos[m++]= calcarr[c-2]->flPos.lastpos[n++];

            }
            n=0;
            while(calcarr[c-1]->flPos.lastpos[n]!='\0'){

                nodetree[j].flPos.lastpos[m++] =calcarr[c-1]->flPos.lastpos[n++];

            }
//calculation of lastpos ends here
            c-=2;//decrement the stack top by 2
            calcarr[c++]=&nodetree[j++];//then adds the adderess of nodetree[j] to top of calcarr


}
// function defination of starnode
//which calculates firstpos and lastpos
// of '*' node
void starnode(){
    nodetree[j].nodevalue=operatornode[k--];//adds the poped operator to nodetree[] array
    nodetree[j].nullable=true;
    nodetree[j].left_child=calcarr[c-1];//assign pointer left_child with top address value in calcarr[] stack
    calcarr[c-1]->parent=&nodetree[j];//assign pointer parent(top pointer in calcarr[] stack) with address of current nodetree[j] element
    int m=n=0;
    //calculation of firstpos starts here
    while(calcarr[c-1]->flPos.firstpos[n]!='\0'){

        nodetree[j].flPos.firstpos[m++]= calcarr[c-1]->flPos.firstpos[n++];

    }
    //calculation of firstpos ends here
   m= n=0;
   //calculation of lastpos starts here
    while(calcarr[c-1]->flPos.lastpos[n]!='\0'){

        nodetree[j].flPos.lastpos[m++] =calcarr[c-1]->flPos.lastpos[n++];

    }
    //calcualtion of lastpos ends here
    c--;//decrement top of calcarr stack by 1
    calcarr[c++]=&nodetree[j++];//adds address of nodetree[j] to top of calcarr[] stack

}
// completion of starnode function

//start function defination which calculates firstpos and lastpos of every nodes
int start(){
//below loop runs until we reach the end of string regexp
   while(regexp[i]!='\0'){
       if((regexp[i]>='0'&&regexp[i]<='9')||regexp[i]=='#'||(regexp[i]<='z'&&regexp[i]>='a'))
           leafnode();//function calls when the char is terminal leafnodes

       else if(regexp[i]==')'){
       //below loop runs until we reach char '(' and pops all the char comming in the way performing their
       //specific operations
                    while(operatornode[k]!='('){
                            if(operatornode[k]=='*')
                                starnode();//function calls when the operatornode stack top char is '*'
                            else if(operatornode[k]=='|'||operatornode[k]=='+')
                                ornode();//function calls when the operatornode stack top char is '|'/'+'
                            else
                                catnode();//function calls when the operatornode stack top char is '.'

                          }
                    k--;//this decrement removes '('from top of stack
                    l-=2;//this sets the size of regexp after removing '('and ')'
                }

                //runs bellow code if encounter any operator character
       else if(regexp[i]=='.'||
           regexp[i]=='|'||
           regexp[i]=='*'||
           regexp[i]=='('||
           regexp[i]=='+'){
           //the codes below here follows postfix evaluation
           if((regexp[i]=='.'||regexp[i]=='|'||regexp[i]=='+')&&
               ('*'==operatornode[k]||'|'==operatornode[k]||'.'==operatornode[k]||'+'==operatornode[k])){

                while(('*'==operatornode[k]||'|'==operatornode[k]||
                       '.'==operatornode[k]||
                       '+'==operatornode[k])&&k>-1)
               if(operatornode[k]=='.')
                 catnode();//calls if '.'
                 else if('*'==operatornode[k])
                    starnode();//calls if '*'
                    else
                        ornode();//calls if '|' / '+'

               }
            else if(regexp[i]=='*'&&
                    ('*'==operatornode[k])){

                                starnode();//calls if '*'
                }

            operatornode[++k]=regexp[i];//finally adds current regexp operator to top of operatornode stack
//codes above here follows postfix evaluation
           }

        else{
        //code here runs if it contains unknown characters
           cout<<"***Entered expression contains unknown characters***"<<
                "\n***please enter regular expression correctly***"<<endl;
                return -1;
        }

       i++;

}
//loop below pops all operand nodes in operatornode[]stack
while(k>-1){
    if(operatornode[k]=='*')
        starnode();//calls if '*'
    else if(operatornode[k]=='|'||operatornode[k]=='+')
        ornode();//calls if '|' / '+'
    else
        catnode();//calls if '.'
    k--;

}
return 0;
}
//completion of start function

//begining of main
int main()
{
int lcount=0;
    cout << "Enter the length of regex[0,100]"<<
            "\n****  including '.' symbol ****"<<
            "\n**** excluding '.#' at end ****" <<endl<<"=>";
    cin >> l;
    if(l<0||l>100){
        cout<<"***please enter the length of string***"<<
        " \n***between 0 to 100***"<<endl;
        return 0;
    }
    cout << "Enter the regular expression" << endl<<"=>";
    cin >> regexp;

    while(regexp[lcount]!='\0')
        lcount++;

    if(l>lcount|| l<lcount){
        cout<<"***please enter the regular expression of length you entered above***"<<endl;
        return 0;
    }

    regexp[l++]='.';//concats '.'
    regexp[l++]='#';//concats '#'

    if(-1 ==
    start()// calculates firstpos and lastpos
    )
    return 0;

    cout<<"The augmented regular expression is: ";
    cout << regexp<<endl;
    cout<<"\n_____________________________________________________________\n";

    //output for firstpos and lastpos starts here
    cout<< "\nNode \t Firstpos \t\t Lastpos \n";
    i=0;
    while(i<l){
        cout<<nodetree[i].nodevalue<<" \t ";
             j=0;
            while(nodetree[i].flPos.firstpos[j]!='\0'){
                cout <<nodetree[i].flPos.firstpos[j]<<", ";
                j++;
            }
            cout <<"\t\t\t";
             j=0;
            while(nodetree[i].flPos.lastpos[j]!='\0'){
                cout <<nodetree[i].flPos.lastpos[j]<<", ";
                j++;
            }
            cout <<" \n";

            i++;
    }
    // output of firstpos and lastpos ends here


    followp(); // calculates followpos
    cout<<"_____________________________________________________________\n";
    i=0;
    //output for followpos starts here
    cout<<"\nNodes \t "<<"       Followpos \n";
    while(i<leafcnt-1){
        cout<<fp[i].nodeptr->nodevalue<<" [ "<<i+1<<" ] \t ";
        k=0;
        while(fp[i].followpos[k]!='\0'){
            cout<<fp[i].followpos[k++]<<",";
        }
        cout<<endl;
        i++;
    }
    //output for followpos ends here
   Dtranstable();
    cout<<"_____________________________________________________________\n";
   j=0;
   cout<<"\nTransition table for DFA"<<endl;
   cout<<"\t";
  while(j<scnt){
    cout<<sigma[j++]<<" \t ";
  }
  cout<<endl;
   j=0;
   cout<<"->";
   while(j <= Dtlist){
    if(Dtran[j].finalstate)
        cout<<" *";
    else
        cout<< " ";

    cout<<Dtran[j].symbol<<"\t";
    k=0;
    while(k<scnt){

        cout<<Dtran[j].tran1[k]->symbol<<"\t";
        k++;
    }
    cout<<endl;

    j++;
   }
   cout<<"\nWhere,\n"<<endl;
   j=0;

   cout<<"->";
   while(j<=Dtlist){
   if(Dtran[j].finalstate)
   cout<<" *";
   else
    cout<<" ";
   cout<<Dtran[j].symbol<<"\t";
   k=0;
   while(Dtran[j].followpos[k]!='\0'){
    cout<<Dtran[j].followpos[k]<<",";
    k++;
   }
   cout<<endl;
   j++;
   }
    cout<<"\n_____________________________________________________________\n";

    return 0;
}
//end of main function
