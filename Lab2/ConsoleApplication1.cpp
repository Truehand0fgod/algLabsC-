using namespace std;

#include <iostream>
#include <ctime>

const int N = 10000000;
static int merge_count;

class Sort
{
public:

	static int shell_sort(int **mass, int n)
	{
		int i, j, step, count = 0;
		for (step = n / 2; step > 0; step /= 2)
			for (i = step; i < n; i++)
			{
				for (j = i; j >= step; j -= step, count++)
				{
					if (*mass[i] < *mass[j - step])
					{
						mass[j] = mass[j - step];
						count++;
					}
					else
					{
						count++;
						break;
					}
				}
				mass[j] = mass[i];
			}
		return count;
	}

		

	//static void heapify(int **arr, int n, int i)
	//{
	//	heap_count += 2;
	//	int largest = i;
	//	// Инициализируем наибольший элемент как корень
	//	int l = 2 * i + 1; // левый = 2*i + 1
	//	int r = 2 * i + 2; // правый = 2*i + 2

	// // Если левый дочерний элемент больше корня
	//	if (l < n && *arr[l] > *arr[largest])
	//	{
	//		largest = l;
	//		heap_count++;
	//	}
	//	// Если правый дочерний элемент больше, чем самый большой элемент на данный момент
	//	if (r < n && *arr[r] > *arr[largest])
	//	{
	//		largest = r;
	//		heap_count++;
	//	}
	//	// Если самый большой элемент не корень
	//	if (largest != i)
	//	{
	//		swap(arr[i], arr[largest]);

	////		// Рекурсивно преобразуем в двоичную кучу затронутое поддерево
	//		heapify(arr, n, largest);
	//	}
	//}

	//// Основная функция, выполняющая пирамидальную сортировку
	//static int heap_sort(int **arr, int n)
	//{
	//	heap_count = 0;
	//	// Построение кучи (перегруппируем массив)
	//	for (int i = n / 2 - 1; i >= 0; i--)
	//		heapify(arr, n, i);

	//	// Один за другим извлекаем элементы из кучи
	//	for (int i = n - 1; i >= 0; i--)
	//	{
	//		// Перемещаем текущий корень в конец
	//		swap(arr[0], arr[i]);

	//		// вызываем процедуру heapify на уменьшенной куче
	//		heapify(arr, i, 0);
	//	}
	//	return heap_count;
	//}

	static void merge_rec(int** A, int b, int e,
		int** D)
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

	static int merge_sort(int** A, int n)
	{
		merge_count = 0;
		int** D = new int*[n];
		merge_rec(A, 0, n - 1, D);
		delete[] D;
		return merge_count;
	}



	static bool is_sorted(int **ptr, int n)
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
	int** ptr_as = new int* [N];		// выделяем память 
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
		cout << "All arrays are SORETED by Shell!!"<<endl;
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


