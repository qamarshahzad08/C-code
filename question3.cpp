#include<iostream>
#include<vector>
using namespace std;
class obj
{
public:
	int data;
	bool Mark;
	obj()
	{
		Mark=false;
	}
};
typedef vector<vector<obj>> adjacency_list_t;
void bfs (adjacency_list_t v)
{
	

}
int main()
{
	vector<int> my_queue;
	for(int i=0;i<8;i++)
	{
	my_queue.push_back(i);
	}
	
	for(int i=0;i<my_queue.size();i++)
	{
		cout<<my_queue[i]<<endl;
	}


	
}