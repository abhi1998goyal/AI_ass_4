#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include<bits/stdc++.h>
#include <random>

// Format checker just assumes you have Alarm.bif and Solved_Alarm.bif (your file) in current directory
using namespace std;

// Our graph consists of a list of nodes where each node is represented as follows:
class Graph_Node{

private:
	string Node_Name;  // Variable name 
	vector<int> Children; // Children of a particular node - these are index of nodes in graph.
	vector<string> Parents; // Parents of a particular node- note these are names of parents
	int nvalues;  // Number of categories a variable represented by this node can take
	vector<string> values; // Categories of possible values
	vector<float> CPT; // conditional probability table as a 1-d array . Look for BIF format to understand its meaning
	map<string,float> cpt_map;
	vector<string> cpt_order;

public:
	// Constructor- a node is initialised with its name and its categories
    Graph_Node(string name,int n,vector<string> vals)
	{
		Node_Name=name;
	
		nvalues=n;
		values=vals;
		

	}

void set_cpt_map(vector<float> cpt , vector<string> cpt_comb)
{
		for(int i =0;i<cpt.size();i++){
			this->cpt_map[cpt_comb[i]]=cpt[i];
		}
}

void set_cpt_order(vector<string> cpt_order){
     this->cpt_order=cpt_order;
}


vector<string> get_cpt_order(){
     return cpt_order;
}

map<string,float> get_cpt_map()
{
    return cpt_map;
}


	string get_name()
	{
		return Node_Name;
	}
	vector<int> get_children()
	{
		return Children;
	}
	vector<string> get_Parents()
	{
		return Parents;
	}
	vector<float> get_CPT()
	{
		return CPT;
	}
	int get_nvalues()
	{
		return nvalues;
	}
	vector<string> get_values()
	{
		return values;
	}
	void set_CPT(vector<float> new_CPT)
	{
		CPT.clear();
		CPT=new_CPT;
	}
    void set_Parents(vector<string> Parent_Nodes)
    {
        Parents.clear();
        Parents=Parent_Nodes;
    }
    // add another node in a graph as a child of this node
    int add_child(int new_child_index )
    {
        for(int i=0;i<Children.size();i++)
        {
            if(Children[i]==new_child_index)
                return 0;
        }
        Children.push_back(new_child_index);
        return 1;
    }



};


 // The whole network represted as a list of nodes
class network{

	list <Graph_Node> Pres_Graph;

public:
	int addNode(Graph_Node node)
	{
		Pres_Graph.push_back(node);
		return 0;
	}
    
    
	int netSize()
	{
		return Pres_Graph.size();
	}
    // get the index of node with a given name
    int get_index(string val_name)
    {
        list<Graph_Node>::iterator listIt;
        int count=0;
        for(listIt=Pres_Graph.begin();listIt!=Pres_Graph.end();listIt++)
        {
            if(listIt->get_name().compare(val_name)==0)
                return count;
            count++;
        }
        return -1;
    }
// get the node at nth index
    list<Graph_Node>::iterator get_nth_node(int n)
    {
       list<Graph_Node>::iterator listIt;
        int count=0;
        for(listIt=Pres_Graph.begin();listIt!=Pres_Graph.end();listIt++)
        {
            if(count==n)
                return listIt;
            count++;
        }
        return listIt; 
    }
    //get the iterator of a node with a given name
    list<Graph_Node>::iterator search_node(string val_name)
    {
        list<Graph_Node>::iterator listIt;
        for(listIt=Pres_Graph.begin();listIt!=Pres_Graph.end();listIt++)
        {
            if(listIt->get_name().compare(val_name)==0)
                return listIt;
        }
    
            cout<<"node not found\n";
        return listIt;
    }
	

};

network read_network()
{
	network Alarm;
	string line;
	int find=0;
  	ifstream myfile("alarm.bif"); 
  	string temp;
  	string name;
  	vector<string> values;
  	
    if (myfile.is_open())
    {
    	while (! myfile.eof() )
    	{
    		stringstream ss;
      		getline (myfile,line);
      		
      		
      		ss.str(line);
     		ss>>temp;
     		
     		
     		if(temp.compare("variable")==0)
     		{
                    
     				ss>>name;
					name = name.substr(1, name.size() - 2);
     				getline (myfile,line);
                   
     				stringstream ss2;
     				ss2.str(line);
     				for(int i=0;i<4;i++)
     				{
     					
     					ss2>>temp;
     					
     					
     				}
     				values.clear();
     				while(temp.compare("};")!=0)
     				{   
     					values.push_back(temp.substr(1, temp.size() - 2));
     					
     					ss2>>temp;
    				}
     				Graph_Node new_node(name,values.size(),values);
     				int pos=Alarm.addNode(new_node);

     				
     		}
     		else if(temp.compare("probability")==0)
     		{
                    
     				ss>>temp;
     				ss>>temp;
     				
					temp=temp.substr(1, temp.size() - 2);
                    list<Graph_Node>::iterator listIt;
                    list<Graph_Node>::iterator listIt1;
     				listIt=Alarm.search_node(temp);
                    int index=Alarm.get_index(temp);
                    ss>>temp;
                    values.clear();
     				while(temp.compare(")")!=0)
     				{   temp=temp.substr(1, temp.size() - 2);
                        listIt1=Alarm.search_node(temp);
                        listIt1->add_child(index);
     					values.push_back(temp);
     					
     					ss>>temp;

    				}
                    listIt->set_Parents(values);
    				getline (myfile,line);
     				stringstream ss2;
                    
     				ss2.str(line);
     				ss2>> temp;
                    
     				ss2>> temp;
                    
     				vector<float> curr_CPT;
                    string::size_type sz;
     				while(temp.compare(";")!=0)
     				{
                        
     					curr_CPT.push_back(atof(temp.c_str()));
     					
     					ss2>>temp;
                       
                        

    				}
                    
                    listIt->set_CPT(curr_CPT);


     		}
            else
            {
                
            }
     		
     		

    		
    		
    	}
    	
    	if(find==1)
    	myfile.close();
  	}


  	
  	return Alarm;
}

vector<vector<string>> read_data_file(string filename){
	vector<vector<string>> raw_data;
    ifstream dataFile(filename);
	if (dataFile.is_open()) {
    string line;
    while (getline(dataFile, line)) {
        istringstream iss(line);
        vector<string> row;
        string value;
        while (iss >> value) {
            row.push_back(value.substr(1,value.size()-2));
        }
        raw_data.push_back(row);
    }
    dataFile.close();
	
}
    return raw_data;
}

float find_prob(vector<string> row,network Alarm){
    float prob =1.0;
    for(int i =0;i<row.size();i++){
        Graph_Node node = (*Alarm.get_nth_node(i));
		vector<string> parents= node.get_Parents();
		string st=row[i]+"_";
		if(parents.size()>0){
			for(int j=0;j<parents.size();j++){
                st+=row[Alarm.get_index(parents[j])]+"_";
			}
			if(st[st.size()-1]=='_'){
				st=st.substr(0,st.size()-1);
			}
			prob*=node.get_cpt_map()[st];
		}
		else{
			if(st[st.size()-1]=='_'){
				st=st.substr(0,st.size()-1);
			}
			prob*=node.get_cpt_map()[st];
		}
	}
   return  prob;
}

vector<float> normalize(vector<float> prob){
	  float sum =0;
      for(int i=0;i<prob.size();i++){
        sum+=prob[i];
	  }
	  for(int i=0;i<prob.size();i++){
        prob[i]=prob[i]/sum;
	  }
   return prob;
}

pair<vector<vector<string>> ,vector<float>> calc_cpt_raw(vector<vector<string>> raw_data,network Alarm){
	vector<vector<string>> cpt1;
	vector<float> cpt1_prob;
    vector<int> missing_indx;
    for (vector<string> row : raw_data){
		int indx=0;
		 for(string col :row){
			if(col.compare("?")==0){
               missing_indx.push_back(indx);
			}
          indx++;
		 }
	}

	for (int row=0 ;row<raw_data.size();row++){
		cout<<row<<"\n";
		int no_attr_missing_node = (*Alarm.get_nth_node(missing_indx[row])).get_nvalues();
		vector<float> prob(no_attr_missing_node,0);
		for(int i=0;i<no_attr_missing_node;i++){
              vector<string> new_row=raw_data[row];
			  new_row[missing_indx[row]]=(*Alarm.get_nth_node(missing_indx[row])).get_values()[i];
			 prob[i]= find_prob(new_row,Alarm);
		}
		prob=normalize(prob);
		for(int j=0;j<no_attr_missing_node;j++){
              vector<string> new_row=raw_data[row];
			  new_row[missing_indx[row]]=(*Alarm.get_nth_node(missing_indx[row])).get_values()[j];
			  cpt1.push_back(new_row);
			 cpt1_prob.push_back(prob[j]);
		}
	}
	return make_pair(cpt1,cpt1_prob);
}

string row_constrct(vector<string> row,vector<int> tree_indx){
	 string cons="";
     for(int i=0;i<tree_indx.size();i++){
        cons+=row[tree_indx[i]]+"_";
	 }
	 if(cons[cons.size()-1]=='_'){
	 cons=cons.substr(0,cons.size()-1);
	 }
	 return cons;
}

map<string,float> normalize_cpt_map(map<string,float> cpt_map, Graph_Node node){
	   for (const auto& entry : cpt_map) 
        {    vector<float> to_normalize;
			 size_t pos = entry.first.find("_");
			 string cond="";
			 if (pos != string::npos) {
			    cond = "_"+entry.first.substr(pos+1,entry.first.size());
			 }
			 
			 for(string s:node.get_values()){
                 to_normalize.push_back(cpt_map[s+cond]);
			 }
             to_normalize=normalize(to_normalize);
			 for(int j=0;j<node.get_nvalues();j++){
                 cpt_map[node.get_values()[j]+cond]=to_normalize[j];
			 }

		}

		return cpt_map;
}

void assign_cpt(pair<vector<vector<string>>,vector<float>> cpt_table_prob,network& Alarm){
	vector<vector<string>> cpt_table = cpt_table_prob.first;
	vector<float> cpt_prob=cpt_table_prob.second;
    for(int i =0;i<Alarm.netSize();i++){
        Graph_Node node = *(Alarm.get_nth_node(i));
		map<string,float> cpt_map=node.get_cpt_map();
		for (auto& entry : cpt_map) {
             entry.second = 0.0;
           }
        vector<int> tree_indx;
		tree_indx.push_back(Alarm.get_index(node.get_name()));
        for(string parent:node.get_Parents()){
			tree_indx.push_back(Alarm.get_index(parent));
		}
	
	  for(int k=0;k<cpt_table.size();k++){
		  cpt_map[row_constrct(cpt_table[k],tree_indx)]+=cpt_prob[k];
	  }
	  vector<string> ne_cpt_val;
	  vector<float> ne_cpt_prob;
	  for(auto entry : normalize_cpt_map(cpt_map,node)){
            ne_cpt_val.push_back(entry.first);
			ne_cpt_prob.push_back(entry.second);
	  }
	  (*(Alarm.get_nth_node(i))).set_cpt_map(ne_cpt_prob, ne_cpt_val);
	}
}

vector<float> calc_new_cpt(vector<vector<string>> data,network Alarm){
	vector<float> prob;
    for(int i =0;i<data.size();i++){
		
			prob.push_back(find_prob(data[i],Alarm));
		
	}

return prob;
}

void writeOutput(string out_file,string in_file,network Alarm){
	    ifstream infile(in_file); 
        string temp;
        string line;
        ofstream out;
        string name;
        out.open(out_file);
        if (!infile.is_open()){
            return;
		}
        else{
            while(!infile.eof()){
                stringstream ss;
                getline (infile,line);
                ss.str(line);
				ss>>temp;
				 if(temp.compare("probability")==0)
                {                        
                    ss>>temp;
                    ss>>temp;
					string node_name = temp.substr(1,temp.size()-2);
					Graph_Node node = (*Alarm.get_nth_node(Alarm.get_index(node_name)));
					out << line << endl;
                    getline(infile,line);
					out << "    table ";
					int i=0;
                    while(i < node.get_CPT().size())
                    {
                        if(node.get_cpt_map()[node.get_cpt_order()[i]]<0.0001)
                            out << "0.0001" << " ";
                        else
                            out << fixed << setprecision(4) << node.get_cpt_map()[node.get_cpt_order()[i]] << " ";
                        i++;
                    }
                    out << ";" << endl;
			    }
				else if(line.compare("")!=0){
                    out << line << endl;
				}
                else {
                    out << line;
				}
			
		    }

        }
}

int main()
{
	network Alarm;
	Alarm=read_network();
	std::random_device rd;
    std::mt19937 gen(rd());
    for(int i=0;i<Alarm.netSize();i++){
		Graph_Node node = *(Alarm.get_nth_node(i));
		vector<float> node_cpt(node.get_CPT().size(),0);
		for(int j=0;j<node.get_CPT().size()/node.get_nvalues();j++){
			float start=0.0;
            for(int k=0;k<node.get_nvalues()-1;k++){
				std::uniform_real_distribution<float> dis(start, 0.9999);
                float random_number = dis(gen);
                node_cpt[j+k*(node.get_CPT().size()/node.get_nvalues())]=random_number-start;
				start=random_number;
			}
			node_cpt[j+(node.get_nvalues()-1)*(node.get_CPT().size()/node.get_nvalues())]=1-start;
		}
		(*(Alarm.get_nth_node(i))).set_CPT(node_cpt);

		vector<string> rel_str;
	    rel_str.push_back("");
		stack<string> parent_stack;
        for(string parent :node.get_Parents()){
				parent_stack.push(parent);
		}
        while(!parent_stack.empty()){
		string parent = parent_stack.top();
		vector<string> parent_attrs=(*Alarm.search_node(parent)).get_values();
		vector<string> temp;
          for(string parent_attr:parent_attrs){
               for(string real_str : rel_str){
				   temp.push_back(parent_attr+"_"+real_str);
			   }
		  }
		  parent_stack.pop();
		 rel_str.clear();
		 rel_str=temp;
		}
		vector<string>finl_rel_str;
        for(string node_attr:node.get_values()){
             vector<string> temp_str;
			 for(int i=0;i<rel_str.size();i++){
				 temp_str.push_back(node_attr+"_"+rel_str[i]);
			 }
			 for(string st:temp_str){
				if(st[st.size()-1]='_'){
					st=st.substr(0,st.size()-1);
				}
				finl_rel_str.push_back(st);
			 }
		}

		(*(Alarm.get_nth_node(i))).set_cpt_order(finl_rel_str);

		(*(Alarm.get_nth_node(i))).set_cpt_map(node_cpt,finl_rel_str);
	}
  //  
   vector<vector<string>> raw_data = read_data_file("records.dat");
   pair<vector<vector<string>>,vector<float>> cpt_table_1=calc_cpt_raw(raw_data,Alarm);

  
   // for(vector<string> row : raw_data){

	//}
    vector<vector<string>> cpt_rows_curr=cpt_table_1.first;
	vector<float> cpt_prob_curr=cpt_table_1.second;
	for (int i=0;i<10;i++){
		assign_cpt(make_pair(cpt_rows_curr,cpt_prob_curr),Alarm);
		cpt_prob_curr=calc_cpt_raw(raw_data,Alarm).second;
	}

   writeOutput("solved_alarm.bif","alarm.bif",Alarm);
 return 0;
}





