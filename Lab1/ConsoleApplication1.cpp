using namespace std;

#include <iostream>
#include <ctime>

const int N = 10;
static int merge_count;

class Sort
{
public:

	template <typename Type>
	static int shell_sort(Type** A, int n)
	{
		int i, j, h;
		for (h = 1; h <= n / 9; h = h * 3 + 1);
		while (h >= 1)
		{
			for (i = h; i < n; i++)
				for (j = i - h; j >= 0 && *A[j] < *A[j + h]; j -= h)
					swap(A[j], A[j + h]);
			h = (h - 1) / 3;
		}
		return 0;
	}

	template <typename Type>
	static void merge_rec(Type** A, int b, int e,
		Type** D)
	{
		int c = (b + e) / 2;
		if (b < c) merge_rec(A, b, c, D);
		if (c + 1 < e) merge_rec(A, c + 1, e, D);
		int i = b, j = c + 1, k;
		for (k = b; k <= e; k++)
		{
			if (j > e) D[k] = A[i++];
			else if (i > c) D[k] = A[j++];
			else if (*A[i] <= *A[j])
			{
				merge_count++;
				D[k] = A[i++];
			}
			else D[k] = A[j++];
			merge_count++;
		}

		for (int i = b; i <= e; i++)
			A[i] = D[i];
	}
	template <typename Type>
	static int merge_sort(Type** A, int n)
	{
		merge_count = 0;
		Type** D = new Type*[n];
		merge_rec(A, 0, n - 1, D);
		delete[] D;
		return merge_count;
	}


	template <typename Type>
	static bool is_sorted(Type **ptr, int n)
	{
		for (int i = 0; i < n - 1; i++)
		{
			if (*ptr[i] > *ptr[i + 1]) return false;
		}
		return true;
	};

};


int main()
{
	srand(time(0));
	int* ascending_order = new int[N]; // выделяем память 
	int* descending_order = new int[N];
	int* rand_array = new int[N];  
	for (int i = 0; i < N; i++)        // заполняем
	{
		ascending_order[i] = i;
		descending_order[i] = N - i;
		rand_array[i] = rand() % (N);
	}
	int** ptr_as = new int *[N];		// выделяем память 
	int** ptr_des = new int* [N];
	int** ptr_rand = new int* [N];
	for (int i = 0; i < N; i++)			// заполняем указатели
	{
		ptr_as[i] = &ascending_order[i]; 
		ptr_des[i] = &descending_order[i];
		ptr_rand[i] = &rand_array[i];
	}
	float shell_start_time = clock(); // начало отсчета

	int shell_counter_as = Sort::shell_sort(ptr_as, N);
	int shell_counter_des = Sort::shell_sort(ptr_des, N);
	int shell_counter_rand = Sort::shell_sort(ptr_rand, N);

	float shell_delta_time = clock() - shell_start_time; //засекаем + первод в с

	if (Sort::is_sorted(ptr_as, N) && Sort::is_sorted(ptr_des, N) && Sort::is_sorted(ptr_rand, N))
		cout << "\nAll arrays are SORETED by Shell!!"<<endl;
	else
		cout << "All arrays aren`t SORETED by Shell!!" << endl;
	cout << "Shell sort:\t\t" << endl << "ascending => \t\t" << shell_counter_as << endl;
	cout <<"descending => \t\t" << shell_counter_des << endl << "rand =>\t\t\t" << shell_counter_rand << endl;

	for (int i = 0; i < N; i++)			// заполняем указатели
	{
		ptr_as[i] = &ascending_order[i];
		ptr_des[i] = &descending_order[i];
		ptr_rand[i] = &rand_array[i];
	}

	float merge_start_time = clock();

	int merge_counter_as = Sort::merge_sort(ptr_as, N);
	int merge_counter_des = Sort::merge_sort(ptr_des, N);
	int merge_counter_rand = Sort::merge_sort(ptr_rand, N);

	float merge_delta_time = clock() - merge_start_time;

	if (Sort::is_sorted(ptr_as, N) && Sort::is_sorted(ptr_des, N) && Sort::is_sorted(ptr_rand, N))
		cout << "All arrays are SORETED by Merge!!" << endl;
	else
		cout << "All arrays aren`t SORETED by Merge!!";
	cout << "Merge sort:\t\t" << endl << "ascending => \t\t" << merge_counter_as << endl;
	cout<< "descending => \t\t" << merge_counter_des << endl << "rand =>\t\t\t" << merge_counter_rand << endl;
	
	cout << "\n\n\n\nProgram execution time == "<<clock() / 1000.0 <<" sec" << endl;
	cout << "Shell process time == " << shell_delta_time / 1000.0 << " sec" << endl;
	cout << "Merge process time == " << merge_delta_time / 1000.0 << " sec" << endl;
	//cout << "Shell " << merge_delta_time / shell_delta_time << " times faster" << endl;
	return 0;
}


