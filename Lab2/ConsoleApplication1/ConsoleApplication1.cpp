using namespace std;

#include <fstream>
#include <iostream>
#include <ctime>

static int merge_count;

class Sort
{
public:
    template <typename Type>
    static void shell_sort(Type** A, int n)
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
    }


    template <typename Type>
    static int merge_sort(Type** A, int n)
    {
        merge_count = 0;
        Type** D = new Type * [n];
        merge_rec(A, 0, n - 1, D);
        delete[] D;
        return merge_count;
    }


    template <typename Type>
    static bool is_sorted(Type** ptr, int n)
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

const int N = 100;

struct Participant
{
    int score;
    int n_solved;
    int time;
    int attempts;
    int id;

    Participant operator= (const Participant& other)
    {
        if (this != &other)
        {
            score = other.score;
            n_solved = other.n_solved;
            time = other.time;
            attempts = other.attempts;
            id = other.id;
        }
        return *this;
    }

};

bool operator< (const Participant& left, const Participant& right)
{
    if (left.score < right.score)
    {
        return true;
    }
    else
    {
        if (left.score == right.score)
        {
            if (left.n_solved < right.n_solved)
            {
                return true;
            }
            else
            {
                if (left.n_solved == right.n_solved)
                {
                    if (left.time < right.time)
                    {
                        return false;
                    }
                    else
                    {
                        if (left.time == right.time)
                        {
                            if (left.attempts < right.attempts)
                            {
                                return false;
                            }
                            else
                            {
                                if (left.attempts == right.attempts)
                                {
                                    if (left.id < right.id)
                                    {
                                        return true;
                                    }
                                    else
                                    {
                                        return false;
                                    }
                                }
                                return true;
                            }
                        }
                        return true;
                    }
                }
                return false;
            }
        }
        return false;

    }
}

int main()
{
    srand(time(0));

    Participant** coder = new Participant * [N];

    for (int i = 0; i < N; i++) {
        coder[i] = new Participant;

        coder[i]->id = i;
        coder[i]->n_solved = rand() % 5;
        coder[i]->time = rand() % 240 + 60;
        coder[i]->score = rand() % 25;
        coder[i]->attempts = rand() % 20;

        //std::cout << "Coder " << coder[i]->id << "\tscore is: " << coder[i]->score <<"\tn_solved is " << coder[i]-> n_solved <<"\ttime is " << coder[i]->time << "\tattemps is " << coder[i] ->attempts << std::endl;
    }


    Sort::shell_sort<Participant>(coder, N);

    ofstream file("output.txt"); // создаем объект класса ofstream для записи в файл "output.txt"

    if (file.is_open()) // проверяем, что файл успешно открыт
    {
        for (int i = 0; i < N; i++)
        {
            file << "Coder " << coder[i]->id << " " << "\tscore is: " << coder[i]->score << "\tn_solved is " << coder[i]->n_solved << "\ttime is " << coder[i]->time << "\tattemps is " << coder[i]->attempts << std::endl;
        }
        file.close(); // закрываем файл
    }
    else
    {
        std::cout << "Unable to open file"; // выводим сообщение об ошибке, если файл не удалось открыть
    }


    return 0;
}