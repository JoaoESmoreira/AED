
#include <iostream>
#include <vector>


void read_raster (const int &M, std::vector<int> &raster) {
    int input;

    for (int i = 0; i < M; ++i) {
        std::cin >> input;
        raster.push_back(input);
    }
}

void print_raster (std::vector<int> &raster) {
    for (int i = 0; i < (int) raster.size(); ++i) {
        std::cout << raster[i] << " ";
    } 
    std::cout << "\n";
}

void insertion_sort(std::vector<int> &raster, int begin, int end) {

    // o i tem de ser até ao end inclusive, porque quando passo, passo o end e nao o tamanho real (N*M-1)
    for (int i = begin; i <= end; ++i) {
        for (int j = i; j > 0; --j) {
            if (raster[j] < raster[j - 1])
                std::swap(raster[j], raster[j - 1]);
            else
                break;
        }
    }
}

void quick_sort (std::vector<int> &raster, int start, int end) {

    // fazer insertion sort no caso de estarmos com arrays com tamanho menor que 30
    if (end - start <= 30) {
        insertion_sort(raster, start, end);
        return;
    }
    // fazer a mediana com o primeiro, o do meio e o ultimo elemento
    // ordenar esses elementos -> desta forma a mediana é o que se encontra no meio
    // este é o que queremos escolher como pivot
    // sendo assim, fazemos swap para o primeiro elemento, no final do processo
    int m = (end - start) / 2;

    if (raster[start] > raster[m]) {
        std::swap(raster[start], raster[m]);
    }
    if (raster[m] > raster[end]) {
        std::swap(raster[m], raster[end]);
    }
    if (raster[start] > raster[m]) {
        std::swap(raster[start], raster[m]);
    }

    
    std::swap(raster[start], raster[m]);

    int pivot = start;
    int i = end;
    int j = start;

    while (i != j) {

        for (; i > j; --i) {
            if (raster[pivot] >= raster[i]) {
                std::swap(raster[pivot], raster[i]);
                pivot = i;
                j++;
                break;
            }
        }

        for (; j < i; ++j) {
            if (raster[j] >= raster[pivot]) {
                std::swap(raster[pivot], raster[j]);
                pivot = j;
                i--;
                break;
            }
        }
    }

    quick_sort(raster, start, i - 1);
    quick_sort(raster, i + 1, end);
}


int amplitude (std::vector<int> &raster) {
    return raster[raster.size() - 1] - raster[0];
}

int mediana (std::vector<int> raster) {
    int size_0 = raster.size() - 1;

    if ((size_0 + 1) % 2 == 0) {
        return (raster[size_0 / 2] + raster[(size_0 / 2) + 1]) / 2;
    } 
    return raster[((size_0) / 2)];
}
    
int percentil (const std::vector<int> &raster, const int &value) {
    float count = 0;

    for (int i = 0; i < (int) raster.size(); ++i) {
        if (raster[i] < value)
            count++;
        else
            return (count / raster.size()) * 100;
    }
    return (count / raster.size()) * 100;
}



int main() {

    std::vector<int> raster;
    std::string command;
    int N, M;


    // DELETE!!!!!!!!!!!1
    std::cout << "\n";

    do {
        std::cin >> command;

        if (command.compare("RASTER") == 0) {
            // read array
            std::cin >> N >> M;
            read_raster(N*M, raster);
            std::cout << "RASTER GUARDADO\n";
            quick_sort(raster, 0, N*M - 1);

        } else if (command.compare("AMPLITUDE") == 0) {

            std::cout << amplitude(raster) << "\n";

        } else if (command.compare("MEDIANA") == 0) {

            std::cout << mediana(raster) << "\n";

        } else if (command.compare("PERCENTIL") == 0) {
            int t, input, output;

            std::cin >> t;
            for (int i = 1; i <= t; ++i) {
                std::cin >> input;

                output = percentil(raster, input);

                std::cout << output;
                if (i == t)
                    std::cout << "\n";
                else 
                    std::cout << " ";
            }
        }

    } while (command.compare("TCHAU"));

    print_raster(raster);


    return 0;
}