#include <iostream>
using namespace std;
//linux做出的修改
void sort(int arr[], int size)
{
	
}
	
int main()
{
	//win做出的修改
	int arr[] = {12, 4, 89, 43, 21, 78};
	int size = sizeof(arr) / sizeof(arr[0]);
	sort(arr, size);
	return 0;
}