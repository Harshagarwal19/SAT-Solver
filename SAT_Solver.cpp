#include<bits/stdc++.h>
#include <fstream>
using namespace std;

void print_clauses(vector<set<int>>&clauses){
    int rows = clauses.size();
    cout<<"##START##"<<endl;
    for(int i=0;i<rows;i++)
    {
        for (auto it=clauses[i].begin(); it != clauses[i].end(); ++it) 
        {
            cout<<*it<<" ";
        }
        cout<<endl;
    }
    cout<<"##END##"<<endl;
    return;
}
void print_assignmnet(vector<int> &assignment){
    for(int i=0;i<assignment.size();i++)
        cout<<assignment[i]<<" ";
    cout<<endl;
}

int check_empty_clause(vector<set<int>> &clauses){
    int rows = clauses.size();
    for(int i=0;i<rows;i++)
    {
        if(clauses[i].size()==0)
            return 1;
    }
    return 0;
}

void remove_new_p(vector<set<int>>&clauses, vector<int> &assignment){
    int new_p = assignment.back();
    for(int i=0;i<clauses.size();i++)
    {
        if(clauses[i].find(new_p) != clauses[i].end()){
            clauses.erase(clauses.begin()+i);
            i--;
        }
        else if(clauses[i].find(-1*new_p)!=clauses[i].end()){
            clauses[i].erase(clauses[i].find(-1*new_p));
        }
    }
    return;
}

void unit_prop(vector<set<int>> &clauses,vector<int> &assignment){
    int flag=1;
    while(flag==1){
        flag=0;
        int rows = clauses.size();
        for(int i=0;i<rows;i++){
            if(clauses[i].size()==1){
                flag=1;
                set<int>::iterator it = clauses[i].begin();
                clauses.erase(clauses.begin()+i);
                assignment.push_back(*it);
                remove_new_p(clauses,assignment);
                break;
            }
        }
    }
    return;
}

void pure_literal_assign(vector<set<int>> &clauses, vector<int> &assignment, int literals){
    vector<int> check(literals+1, 0);
    int curr_rows = clauses.size();
    for(int i=0;i<curr_rows;i++)
    {
        for (auto it=clauses[i].begin(); it != clauses[i].end(); ++it) 
        {
            int val = *it;
            if(val<0){
                if(check[-1*val]==1)
                    check[-1*val]=2;
                else if(check[-1*val]==0)
                    check[-1*val]=-1;
                else if(check[-1*val]==2)
                    check[-1*val]=2;
            }
            else{
                if(check[val]==-1)
                    check[val]=2;
                else if(check[val]==0)
                    check[val]=1;
                else if(check[val]==2)
                    check[val]=2;
            }
        }
    }
    for(int i=1;i<=literals;i++)
    {
        if(check[i]==1 || check[i]==-1){
            assignment.push_back(check[i]*i);
            remove_new_p(clauses,assignment);
        }
    }
    return;
}

void print_ans(vector<int> &assignment, int literals){
    int size = assignment.size();
    vector<int> solution(literals+1,1);
    for(int i=0;i<size;i++)
    {
        int val = assignment[i];
        if(val<0)
        {
            solution[val*-1]=-1;
        }
    }
    for(int i=1;i<=literals;i++)
    {
        cout<<i*solution[i]<<" ";
    }
    cout<<endl;
    return;
}



bool DPLL_algo(vector<set<int>>clauses,vector<int> assignment,int new_p, int literals){
    
    assignment.push_back(new_p);
    remove_new_p(clauses,assignment);
    unit_prop(clauses,assignment);
    pure_literal_assign(clauses,assignment,literals);
    if(clauses.size()==0){
        print_ans(assignment,literals);
        return true;
    }
    if(check_empty_clause(clauses)==1){
        return false;
    }
    int  newp = *(clauses[0].begin());
    return DPLL_algo(clauses, assignment,newp, literals) || DPLL_algo(clauses,assignment,-1*newp,literals);
}


int main()
{
    ifstream inFile;
    string v,v1;
    string name;
    cout<<"Enter name of file: "<<endl;
    cin>>name;
    inFile.open(name);
    inFile>>v;
    inFile>>v1;
    while(v!="p" || v1!="cnf"){
        v=v1;
        inFile>>v1;
    }
    int literals;
    int rows;
    inFile>> literals;
    inFile>>rows;
    cout<<"No of literals "<<literals<<endl;
    cout<<"No of rows "<<rows<<endl;
    vector<set<int>> clauses(rows);
    int num;
    for(int i=0;i<rows;i++)
    {
        inFile>>num;
        while(num!=0)
        {
            clauses[i].insert(num);
            inFile>>num;
        }
    }
    vector<int> assignment;
    //Algorithm
    unit_prop(clauses,assignment);
    pure_literal_assign(clauses,assignment,literals);
    if(clauses.size()==0){
        print_ans(assignment,literals);
        cout<<"SATISFIABLE"<<endl;
        return 0;
    }
    if(check_empty_clause(clauses)==1){
        cout<<"UNSATISFIABLE"<<endl;
        return 0;
    }
    int  new_p = *(clauses[0].begin());
    bool answer =  DPLL_algo(clauses, assignment,new_p, literals) || DPLL_algo(clauses,assignment,-1*new_p,literals);
    if(answer)
        cout<<"SATISFIABLE"<<endl;
    else   
        cout<<"UNSATISFIABLE"<<endl;
    return 0;
}