#include<bits/stdc++.h>
#include <iomanip>
#include <fstream>

using namespace std;

void rmv(vector< vector <int> > &var , vector <int> &s)
{

  for(int t=0;t<var.size();t++)
  {
      int flag=0;
      if(var[t].size()==2)
      {
          flag=1;
          int value=var[t][0];
          s.push_back(value);
          for(int i1=0;i1<var.size();i1++)
          {
              for(int j=0;i1<var.size() && j<var[i1].size();j++)
              {
                  if(var[i1][j]==value)
                  {
                      //cout<<"ERASE"<<endl;
                      var.erase(var.begin()+i1);
                      //i1=i1-1;
                      j=-1;
                      continue;
                  }
                  if(var[i1][j]== -1*value)
                  {
                      var[i1].erase(var[i1].begin()+j);
                      j=j-1;
                  }
              }
          }
      }
      if(flag==1)
        t=-1;
  }

}



int check_contradiction(vector<vector<int>> &var)
{
    int contra=0;
        for(int i1=0;i1<var.size();i1++)                 //checking contradiction
        {
	    //cout<<var[i1].size()<<" size of rows"<<endl;
            if(var[i1].size()==1)
            {
              //cout<<"Again contradiction"<<endl;
                contra=1;
                break;
            }
        }
    if(contra==1)
        return 1;
    else
        return 0;
}


int rec(vector <vector<int > > &var,vector<vector < vector <int> > > &p_var,vector<int> &count_stack,int value,int i,vector<int> &s1,vector<int> &index,vector<int> &length)
{
  int count=1;
    if(length.size()!=0)
    {
        int rows = var.size();
        vector <vector <int> > cvar(rows);
        for(int i1=0;i1<var.size();i1++)
        {
            for(int j=0;j<var[i1].size();j++)
            {
                cvar[i1].push_back(var[i1][j]);
            }
        }
        


        if(value==0)
        {
          return 0;
        }
        
        
        int contra=0;
     
        for(int i1=0;i1<var.size();i1++)
        {
   
            for(int j=0;i1<var.size() && j<var[i1].size();j++)
            {
            
                if(var[i1][j]==value)
                {

                 
                    var.erase(var.begin()+i1);
                                       //i=i-1;   //check this after wards
                    j=-1;
                    continue;
                }

                if(var[i1][j]== -1*value)
                {
                    var[i1].erase(var[i1].begin()+j);
                    j=j-1;
                }
            }
        }
        //check for contradiction
        if(check_contradiction(var)){
            contra =1;
        }
        else
        {
            contra = 0;
        }
        
        
        //check for more elements to be added in the stack
        if(contra==0){
                for(int t=0;t<var.size();t++)
                {
                    int flag=0;
                    if(var[t].size()==2)
                    {
                      count++;
                      flag=1;
                      int value=var[t][0];
                      s1.push_back(value);

                      for(int i1=0;i1<var.size();i1++)
                      {
                          for(int j=0;i1<var.size() && j<var[i1].size();j++)
                          {
                              if(var[i1][j]==value)
                              {
                                  //cout<<"ERASE"<<endl;
                                  var.erase(var.begin()+i1);
                                  //i1=i1-1;
                                  j=-1;
                                  continue;
                              }
                              if(var[i1][j]== -1*value)
                              {
                                  var[i1].erase(var[i1].begin()+j);
                                  j=j-1;
                              }
                          }
                      }
                    }
                    else if(var[t].size()==1)
                    {
                        contra=1;
                        break;
                    }
              if(flag==1)
                t=-1;
          }
        }
     
       
        for(int i1=0;i1<var.size();i1++)                 //checking contradiction
        {
            if(var[i1].size()==1)
            {
              //cout<<"Again contradiction"<<endl;
                contra=1;
                break;
            }
        }
        
        
        
        //SAT condition
        if(var.size()==0)
        {
            return 1;
        }
   

        if(contra==1)                       //check
        {
            
            int l=length.back();
            if(i<(l-2)){

                  int in = index.back();
                  index.pop_back();
                  index.push_back(in+1);
                  int value1 = cvar[0][i+1];
                  for(int i3=0;i3<count;i3++){
                    s1.pop_back();
                  }
                  s1.push_back(value1);
                  if(rec(cvar,p_var,count_stack,value1,i+1,s1,index,length))
                    return 1;
                  else
                    return 0;
              }
            else
            {
                
                int flag=0;
                for(int i3=0;i3<count;i3++)
                        s1.pop_back();

                while(flag==0)
                {
                    length.pop_back();
                    index.pop_back();
                    
                    
                    count = count_stack.back();
                    count_stack.pop_back();
                    for(int i3=0;i3<count;i3++)
                        s1.pop_back();

                    int i_new=index.back();
                    

                    int len = length.back();

                    if(i_new<(len-2)){
                          
                          vector<vector<int> > pvar = p_var.back();
      			              p_var.pop_back();
                          
                          
                          int value1 =pvar[0][i_new+1];
                          flag=1;
                          s1.push_back(value1);
                          index.pop_back();
                          index.push_back(i_new+1);
                          if(rec(pvar,p_var,count_stack,value1,i_new+1,s1,index,length))
                            return 1;
                            else
                            return 0;
                          

                    }
                    else
                    {
                        if(p_var.size()!=0){
                            p_var.pop_back();
                          }
                        else{
                            return 0;
                        }

                    }
                }


        }
      }

        else
        {
            p_var.push_back(cvar);
            count_stack.push_back(count);
            int l=var[0].size();
            length.push_back(l);
            index.push_back(0);
            value = var[0][0];
            s1.push_back(value);
            if(rec(var,p_var,count_stack,value,0,s1,index,length))
              return 1;
            else
              return 0;
        }





    }
    else
        return 0;

}








int main()
{




    ifstream inFile;
    string p1;
    char p,pre;
    int number;
    string name;
    cout<<"Enter name of file: "<<endl;
    cin>>name;
    inFile.open(name);
    inFile >>pre;
    //cout<<pre<<endl;
    if(pre == 'p')
      cout<<"";
    else
    {
      inFile >> p;
      while(p != 'p' && pre != '\n')
      {
        pre=p;
        inFile>>p;
      }
    }
    inFile>>p1;
    int variables,rows;
    if(1)
    {
        inFile>>variables;
        inFile>>rows;

    }
    cout<<"No of variables "<<variables<<endl;
    cout<<"No of rows "<<rows<<endl;

    vector <vector <int> > var(rows);
    vector <int>s;
    for(int i=0;i<rows;i++)
    {
        inFile>>number;

        while(number!=0)
        {
            var[i].push_back(number);
            inFile>>number;

        }
        var[i].push_back(number);
    }

    rmv(var,s);
      
    vector<vector<vector<int> > > p_var;
    vector<int> count_stack;
    int value = var[0][0];
    vector<int> index;
    index.push_back(0);
    vector<int> length;
    length.push_back(var[0].size());
    int contradic=0;
    s.push_back(value);
    for(int i=0;i<var.size();i++)
    {
        if(var[i].size()==1)
        {
            contradic=1;
            break;
        }
    }
    int done=0;
    if(var.size()==0)
    {
        done=1;
    }
    int sat=0;
    if(contradic!=1 && done!=1){
        if(rec(var,p_var,count_stack,value,0,s,index,length))
        {
            sat=1;
            cout<<"SAT"<<endl;
        }            
        else
        {
            cout<<"UNSAT"<<endl;
        }
    }
    else if(contradic==1 && done!=1)
    {
        cout<<"UNSAT"<<endl;
    }
    else
    {
        sat=1;
        cout<<"SAT"<<endl;
    }
    //sort s vector
    if(sat==1){
      vector <int>arr;
      for(int i3 =0;i3<variables;i3++)
      {
        arr.push_back(0);
      }
      for(int i3 = 0;i3<s.size();i3++)
      {
        if(s[i3]<0)
        {
          int num = -1*s[i3]-1;
          arr[num] = 1;
        }
      }
      for(int i3 =0;i3<variables;i3++)
      {
        if(arr[i3]==0)
        {
          cout<<i3+1<<" ";
        }
        else
        {
          cout<<"-"<<i3+1<<" ";
        }
      }
      cout<<endl;
    }




    
    
}