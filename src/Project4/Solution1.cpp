#include <iostream>
#include <vector>

#include <cstdlib> 
#include <ctime> 
#include <chrono>


void read_raster (const int &N, const int &M, std::vector<int> &raster) {
    int input;

    for (int i = 0; i < N * M; ++i) {
        // std::cin >> input;
        input = (rand() % 10000);
        raster.push_back(input);
    }
}

void print_raster (const int &N, const int &M, std::vector<int> &raster) {
    for (int i = 0; i < N * M; ++i) {
        std::cout << raster[i] << " ";
    } std::cout << "\n";
}

int amplitude (const int &N, const int &M, std::vector<int> &raster) {
    int max = raster[0], min = raster[0];

    for (int i = 0; i < N * M; ++i) {
        if (raster[i] > max)
            max = raster[i];
        if (raster[i] < min)
            min = raster[i];
    }
    return max - min;
}

int mediana (std::vector<int> raster) {

    while ( raster.size() > 2) {
        int max = raster[0], min = raster[0];
        bool flag_max = true, flag_min = true;

        for (int i = 0; i < (int) raster.size(); ++i) {
            if (raster[i] > max) {
                max = raster[i];
            }

            if (raster[i] < min) {
                min = raster[i];
            }
        } 
        for (int i = 0; i < (int)raster.size(); ++i) {
            if (raster[i] == min && flag_min) {
                raster.erase(raster.begin() + i);
                flag_min = false;
            }

            if (raster[i] == max && flag_max) {
                raster.erase(raster.begin() + i);
                flag_max = false;
            }
        } 

    }
    if ((int)raster.size() < 2)
        return raster[0];
    else 
        return (raster[0] + raster[1]) / 2;
}
    
int percentil (const std::vector<int> &raster, const int &value) {
    float count = 0;

    for (int i = 0; i < (int) raster.size(); ++i) {
        if (raster[i] < value)
            count++;
    }
    return (count / raster.size()) * 100;
}

int main() {

    std::vector<int> raster;
    std::string command;


    srand((unsigned)time(0)); 



    /*do {
        std::cin >> command;

        if (command.compare("RASTER") == 0) {
            // read array
            std::cin >> N >> M;
            read_raster(N, M, raster);
            std::cout << "RASTER GUARDADO\n";
        } else if (command.compare("AMPLITUDE") == 0) {
            std::cout << amplitude(N, M, raster) << "\n";
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

    } while (command.compare("TCHAU"));*/

    int M = 10000, N = 10000;
    for (int i = 1; i <= 20; ++i) {
        M *= i;
        std::vector<int> raster;
        read_raster(N, M, raster);

        int aux;

        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < N*M; ++i) {
            aux = rand() % 10000;
            percentil(raster, aux);
        }
    std::cout << N << " " << M << "\n";

        auto stop = std::chrono::high_resolution_clock::now();
        auto all_time = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        std::cout << "Time of execution: " << all_time.count() << " milliseconds\n";
    }


    return 0;
}