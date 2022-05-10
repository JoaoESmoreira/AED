
#include <iostream>
#include <vector>

#include <cstdlib> 
#include <ctime> 
#include <chrono>

#define MAX_SIZE 100000


void read_raster (const int &size, int raster[]) {

    for (int i = 0; i < size; ++i) {
        //std::cin >> raster[i];
        raster[i] = (rand() % 10000);
    }
}


void counting_sort (int raster[], const int &size) {
    int index[MAX_SIZE];
    int new_raster[size];

    // inicializar a zero
    for (int i = 0; i < MAX_SIZE; ++i) {
        index[i] = 0;
    }

    // contagem de ocorrencias
    for (int i = 0; i < size; ++i) {
        index[raster[i]]++;
    }

    // soma acomulativa
    for (int i = 1; i < MAX_SIZE; ++i) {
        index[i] = index[i] + index[i - 1];
    }

    // ordenacao 
    for (int i = 0; i < size; ++i) {
        new_raster[index[raster[i]] - 1] = raster[i];
        index[raster[i]]--;
    }

    // copiar o array
    for (int i = 0; i < size; ++i) {
        raster[i] = new_raster[i];
    }
}

int amplitude (int raster[], const int &size) {
    return raster[size - 1] - raster[0];
}

int mediana (int raster[], const int &size) {
    int size_0 = size - 1;

    if ((size_0 + 1) % 2 == 0) {
        return (raster[size_0 / 2] + raster[(size_0 / 2) + 1]) / 2;
    } 
    return raster[((size_0) / 2)];
}
    
int percentil (int raster[], const int &size ,const int &value) {
    float count = 0;

    for (int i = 0; i < size; ++i) {
        if (raster[i] < value)
            count++;
        else
            return (count / size) * 100;
    }
    return (count / size) * 100;
}



int main(int argc, char *argv[]) {

    int raster[100000];
    std::string command;
    //int N, M;

    /*do {
        std::cin >> command;

        if (command.compare("RASTER") == 0) {
            // read array
            std::cin >> N >> M;
            read_raster(N*M, raster);
            counting_sort(raster, N*M);
            std::cout << "RASTER GUARDADO\n";

        } else if (command.compare("AMPLITUDE") == 0) {

            std::cout << amplitude(raster, N*M) << "\n";

        } else if (command.compare("MEDIANA") == 0) {

            std::cout << mediana(raster, N*M) << "\n";

        } else if (command.compare("PERCENTIL") == 0) {
            int t, input, output;

            std::cin >> t;
            for (int i = 1; i <= t; ++i) {
                std::cin >> input;

                output = percentil(raster, N*M, input);

                std::cout << output;
                if (i == t)
                    std::cout << "\n";
                else 
                    std::cout << " ";
            }
        }

    } while (command.compare("TCHAU"));*/



    if (argc != 2)
        return 1;

    int M = atoi(argv[1]);
   
    read_raster(M, raster);

    int aux;
    auto start = std::chrono::high_resolution_clock::now();

    counting_sort(raster, M);

    for (int i = 0; i <M; ++i) {
        aux = rand() % 10000;
        percentil(raster, M, aux);
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto all_time = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "N: " << M << " Time of execution: " << all_time.count() << " milliseconds\n";

    return 0;
}
