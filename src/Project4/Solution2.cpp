#include <iostream>
#include <vector>

void read_raster (const int &N, const int &M, std::vector<int> &raster) {
    int input;

    for (int i = 0; i < N * M; ++i) {
        std::cin >> input;
        raster.push_back(input);
    }
}

void sorting(std::vector<int> &raster) {
    for (int i = 0; i < (int) raster.size() - 1; ++i) {
        for (int j = 0; j < (int) raster.size() - 1; ++j) {
            if (raster[j] > raster[j + 1]) {
                std::swap(raster[j], raster[j + 1]);
            }
        }
    }
}

void print_raster (const int &N, const int &M, std::vector<int> &raster) {
    for (int i = 0; i < N * M; ++i) {
        std::cout << raster[i] << " ";
    } 
    std::cout << "\n";
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
    int M, N;

    do {
        std::cin >> command;

        if (command.compare("RASTER") == 0) {
            // read array
            std::cin >> N >> M;
            read_raster(N, M, raster);
            sorting(raster);
            std::cout << "RASTER GUARDADO\n";
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

    return 0;
}