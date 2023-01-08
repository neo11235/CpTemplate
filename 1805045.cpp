#include <bits/stdc++.h>
#define debug
using namespace std;
int toInt(string s)//tested
{
    int res=0;
    for(auto e:s)
    {
        res*=10;
        res+=e-'0';
    }
    return res;
}
vector<string> split(string input)//tested
{
    vector<string> res;
    string tmp;
    for(char e:input)
    {
        if(e>='0'&&e<='9')
            tmp+=e;
        else
        {
            if(tmp.size()>0)
                res.push_back(tmp);
            tmp.clear();
        }
    }
    if(tmp.size()>0)
        res.push_back(tmp);
    return res;
}
vector<int> fileReader(string path)//tested
{
    ifstream in;
    in.open(path,ios::in);
    if(!in.is_open())
    {
        cout<<"Cannot open input file\n";
        exit(1);
    }
    string all;
    string tmp;
    while(getline(in,tmp))
    {
        all+=tmp;
    }
    in.close();
    vector<string> token=split(all);
    vector<int> res(token.size());
    for(int i=0;i<(int)token.size();++i)
    {
        res[i]=toInt(token[i]);
    }
    return res;
}
struct LatinSquare{
    int **board;
    int boardSize;
    LatinSquare(){board=NULL;boardSize=0;}
};
void printBoard(LatinSquare* lt)
{
    for(int i=0;i<lt->boardSize;++i)
    {
        for(int j=0;j<lt->boardSize;++j)
            cout<<lt->board[i][j]<<' ';
        cout<<'\n';
    }
}
void loadBoard(string filename,LatinSquare* lt)
{
    vector<int> values=fileReader(filename);
    if(values.empty()||(int)values.size()!=(values[0]*values[0]+1))
    {
        cout<<"Invalid file read\n";
        exit(1);
    }
    int n=values[0];
    lt->boardSize=n;
    lt->board=new int*[n];
    if(lt->board==NULL)
    {
        cout<<"Cannot allocate memory\n";
        exit(1);
    }
    for(int i=0;i<n;++i)
    {
        lt->board[i]=new int[n];
        if(lt->board[i]==NULL)
        {
            cout<<"Cannot allocate memory\n";
            exit(1);
        }
    }
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            lt->board[i][j]=values[1+i*n+j];
        }
    }
    #ifdef debug
    printBoard(lt);
    #endif // debug
}
LatinSquare latinSquare;
#define max_size 101
#define pii pair<int,int>
int bl[max_size];
int **columnSet;//at any point marks which value is used at each column
int **rowSet;//at any point marks which value is used at each row
unsigned seed = chrono::system_clock::now().time_since_epoch().count();
linear_congruential_engine<uint_fast32_t, 1002517UL, 1001593UL, 2147483647UL> lcg(seed);
int domainSize(pii a);
int degree(pii a);
void allocateAdditionalMemory();
pii (*vah)();
pii vah1();
pii vah2();
pii vah3();
pii vah4();
pii vah5();

int exploredNode=0;
int bt=0;
int unassigned=0;
int leastContrainingH(pii pos,int val)
{
    int cnt=-2;
    for(int i=0;i<latinSquare.boardSize;++i)
    {
        if(!latinSquare.board[i][pos.second])
        {
            cnt+=(!rowSet[i][val]);
        }
        if(!latinSquare.board[pos.first][i])
        {
            cnt+=(!columnSet[i][val]);
        }
    }
    return cnt;
}
void assign(pii a,int val)
{
    rowSet[a.first][val]=1;
    columnSet[a.second][val]=1;
    latinSquare.board[a.first][a.second]=val;
}
void clear(pii a,int val)
{
    rowSet[a.first][val]=0;
    columnSet[a.second][val]=0;
    latinSquare.board[a.first][a.second]=0;
}
bool sbt()
{
//    cout<<"rec called "<<unassigned<<'\n';;
    if(unassigned==0)
        return true;
    ++exploredNode;
    pii var=vah();
    assert(var.first!=-1&&var.second!=-1&&(!latinSquare.board[var.first][var.second]));
//    cout<<var.first<<' '<<var.second<<' '<<domainSize(var)<<'\n';
    vector<pii> val;
    for(int i=1;i<=latinSquare.boardSize;++i)
    {
        if(rowSet[var.first][i]||columnSet[var.second][i])
            continue;
        val.push_back({leastContrainingH(var,i),i});
    }
    if(val.empty())
    {
        ++bt;
        return false;
    }
    sort(val.begin(),val.end());
    for(pii e:val)
    {
        assign(var,e.second);
        --unassigned;
        if(sbt())
            return true;
        clear(var,e.second);
        ++unassigned;
    }
    return false;
}
bool forwardCheck(pii pos)
{
    for(int i=0;i<latinSquare.boardSize;++i)
    {
        if(!latinSquare.board[i][pos.second])
        {
            if(!domainSize({i,pos.second}))
                return false;
        }
        if(!latinSquare.board[pos.first][i])
        {
            if(!domainSize({pos.first,i}))
                return false;
        }
    }
    return true;
}
bool fc()
{
    if(unassigned==0)
        return true;
    ++exploredNode;
    pii var=vah();
    assert(var.first!=-1);
    vector<pii> val;
    for(int i=1;i<=latinSquare.boardSize;++i)
    {
        if(rowSet[var.first][i]||columnSet[var.second][i])
            continue;
        val.push_back({leastContrainingH(var,i),i});
    }
    if(val.empty())
    {
        ++bt;
        return false;
    }
    sort(val.begin(),val.end());
    bool check=false;
    for(pii e:val)
    {
        assign(var,e.second);
        --unassigned;
        if(!forwardCheck(var)&&unassigned)
        {
            clear(var,e.second);
            ++unassigned;
            continue;
        }
        check=true;
        if(fc())
            return true;
        clear(var,e.second);
        ++unassigned;
    }
    bt+=(!check);
    return false;

}
int main(int argc ,char* argv[])//filename bt|fc vah$i
{
    if(argc!=4)
    {
        cout<<"Invalid argument\n"
        <<"Format 1805045.exe [filename] [bt|fc] [vah$i]\n";
        return 0;
    }
    loadBoard(string(argv[1]),&latinSquare);
    allocateAdditionalMemory();
    for(int i=0;i<latinSquare.boardSize;++i)
    {
        for(int j=0;j<latinSquare.boardSize;++j)
        {
            unassigned+=(latinSquare.board[i][j]==0);
        }
    }
    cout<<unassigned<<'\n';
    if(argv[3][3]=='1')
        vah=vah1;
    else if(argv[3][3]=='2')
        vah=vah2;
    else if(argv[3][3]=='3')
        vah=vah3;
    else if(argv[3][3]=='4')
        vah=vah4;
    else
        vah=vah5;
    ofstream log;
    log.open("log.txt",ios::out|ios::app);
    if(!log.is_open())
    {
        cout<<"Cannot open Log file\n";
        exit(1);
    }
    clock_t t1=clock();
    bool res;
    if(argv[2][0]=='b')
    {
        res=sbt();
    }
    else
    {
        res=fc();
    }
    clock_t t2=clock();
    log<<argv[1]<<' '<<argv[2]<<' '<<argv[3]<<" time: "<<t2-t1<<" bt: "<<bt<<" expnode: "<<exploredNode<<" res: "<<res<<'\n';
    #ifdef debug
        cout<<argv[1]<<' '<<argv[2]<<' '<<argv[3]<<" time: "<<t2-t1<<" bt: "<<bt<<" expnode: "<<exploredNode<<" res "<<res<<'\n';
        printBoard(&latinSquare);
    #endif
    log.flush();
    log.close();
    return 0;
}
pii vah1()
{
    pii res={-1,-1};
    int mn=INT_MAX;
    for(int i=0;i<latinSquare.boardSize;++i)
    {
        for(int j=0;j<latinSquare.boardSize;++j)
        {
            if(latinSquare.board[i][j]!=0)
                continue;
            int tmp=domainSize({i,j});
            if(tmp<mn)
            {
                mn=tmp;
                res={i,j};
            }
        }
    }
    return res;
}
pii vah2(){
    pii res={-1,-1};
    int mx=INT_MIN;
    for(int i=0;i<latinSquare.boardSize;++i)
    {
        for(int j=0;j<latinSquare.boardSize;++j)
        {
            if(latinSquare.board[i][j])
                continue;
            int tmp=degree({i,j});
            if(tmp>mx)
            {
                mx=tmp;
                res={i,j};
            }
        }
    }
    return res;
}
pii vah3()
{
    pii res={-1,-1};
    pii mn={INT_MAX,INT_MAX};
    for(int i=0;i<latinSquare.boardSize;++i)
    {
        for(int j=0;j<latinSquare.boardSize;++j)
        {
            if(latinSquare.board[i][j])
                continue;
            pii tmp={domainSize({i,j}),-degree({i,j})};
            if(tmp<mn)
            {
                mn=tmp;
                res={i,j};
            }
        }
    }
    return res;
}
pii vah4()
{
    pii res={-1,-1};
    double mn=INT_MAX;
    for(int i=0;i<latinSquare.boardSize;++i)
    {
        for(int j=0;j<latinSquare.boardSize;++j)
        {
            if(latinSquare.board[i][j])
                continue;
            double tmp=domainSize({i,j})/(degree({i,j})+1e-6);
            if(tmp<mn)
            {
                mn=tmp;
                res={i,j};
            }
        }
    }
    return res;
}
pii vah5()
{
    int id=lcg()%unassigned;
    for(int i=0;i<latinSquare.boardSize;++i)
    {
        for(int j=0;j<latinSquare.boardSize;++j)
        {
            if(latinSquare.board[i][j])
                continue;
            if(!id)
                return {i,j};
            --id;
        }
    }
    return {-1,-1};
}
int domainSize(pii a)
{
    int cnt=0;
    for(int i=1;i<=latinSquare.boardSize;++i)
    {
        cnt+=(columnSet[a.second][i]==1||rowSet[a.first][i]==1);
    }
    return latinSquare.boardSize-cnt;
}
int degree(pii a)
{
    int cnt=-2;
    for(int i=0;i<latinSquare.boardSize;++i)
    {
        cnt+=latinSquare.board[i][a.second]==0;
        cnt+=latinSquare.board[a.first][i]==0;
    }
    return cnt;
}
void allocateAdditionalMemory()
{
    int n=latinSquare.boardSize;
    columnSet=new int*[n];
    if(columnSet==NULL)
    {
        cout<<"Cannot allocate memory\n";
        exit(1);
    }
    rowSet=new int*[n];
    if(columnSet==NULL)
    {
        cout<<"Cannot allocate memory\n";
        exit(1);
    }
    for(int i=0;i<n;++i)
    {
        columnSet[i]=new int[n+1];
        if(columnSet[i]==NULL)
        {
            cout<<"Cannot allocate memory\n";
            exit(1);
        }
        memset(columnSet[i],0,sizeof(int)*(n+1));
        for(int j=0;j<n;++j)
        {
            if(latinSquare.board[j][i]&&columnSet[i][latinSquare.board[j][i]])
            {
                cout<<"Initial board not consistent\n";
                exit(1);
            }
            columnSet[i][latinSquare.board[j][i]]=1;
        }
    }
    for(int i=0;i<n;++i)
    {
        rowSet[i]=new int[n+1];
        if(rowSet[i]==NULL)
        {
            cout<<"Cannot allocate memory\n";
            exit(1);
        }
        memset(rowSet[i],0,sizeof(int)*(n+1));
        for(int j=0;j<n;++j)
        {
            if(latinSquare.board[i][j]&&rowSet[i][latinSquare.board[i][j]])
            {
                cout<<"Initial board is not consistent\n";
                exit(1);
            }
            rowSet[i][latinSquare.board[i][j]]=1;
        }
    }
}
