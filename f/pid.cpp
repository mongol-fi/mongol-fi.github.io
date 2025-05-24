#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

int main(int argc,char**argv){
  string id,buf;
  vector<string>seq,name;

  for(string line;getline(cin,line);){
    if(line.empty())continue;
    if(line[0]=='>'){
      if(!id.empty()){
        name.push_back(id);
        transform(buf.begin(),buf.end(),buf.begin(),::tolower);
        seq.push_back(buf);
      }
      id=line.substr(1);
      buf.clear();
    }else buf+=line;
  }
  if(!id.empty()){
    name.push_back(id);
    transform(buf.begin(),buf.end(),buf.begin(),::tolower);
    seq.push_back(buf);
  }

  int seqs=seq.size(),positions=seq[0].size();

  vector<vector<int> >diffs(seqs,vector<int>(seqs));
  vector<vector<int> >totals(seqs,vector<int>(seqs));

  int ind=0;
  for(int i=0;i<seqs-1;i++){
    for(int j=i;j<seqs;j++){
      int diff=0,total=0;
      for(int k=0;k<positions;k++)
        if(seq[i][k]!='-'&&seq[j][k]!='-'){
          total++;
          if(seq[i][k]!=seq[j][k])diff++;
        }
      diffs[i][j]=diff;
      totals[i][j]=total;
    }
  }

  for(int i=0;i<seqs;i++)cout<<"\t"<<name[i];
  cout<<endl;
  for(int i=0;i<seqs;i++){
    cout<<name[i];
    for(int j=0;j<seqs;j++){
      int x=i<j?i:j,y=i<j?j:i;
      int diff=diffs[x][y],total=i==j?1:totals[x][y];
      printf("\t%.4f",100*(1-(float)diff/total));
    }
    cout<<endl;
  }
}
