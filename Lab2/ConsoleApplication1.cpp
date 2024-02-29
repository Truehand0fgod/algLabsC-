using namespace std;

#include <iostream>
#include <ctime>

static int merge_count;

class Sort
{
public:

	template <typename Type>
	static int shell_sort(Type **mass, int n)
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

private:

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


};

const int N = 10;

struct Participant
{
	int score;
	int n_solved;
	int time;
	int attempts;
	int id;
	
};

int main()
{
	srand(time(0));
	
	Participant** coder = new Participant* [N]; // Создаем динамический массив указателей

	for (int i = 0; i < N; i++) {
		coder[i] = new Participant;

		coder[i]->id = i; 
		coder[i]->n_solved = rand() % 5;
		coder[i]->time = rand() % 240 + 60;
		coder[i]->score = rand() % 25; 
		coder[i]->attempts = rand() % 20;

		std::cout << "Coder " << coder[i]->id << "\tscore is: " << coder[i]->score <<"\ttime is " <<coder[i]->time << std::endl;
	}

	Sort::shell_sort(coder, N);

	for (int i = 0; i < N; i++)
	{
		std::cout << "Coder " << coder[i]->id << "\tscore is: " << coder[i]->score << "\ttime is " << coder[i]->time << std::endl;
	}

	return 0;
}


