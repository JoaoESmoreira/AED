#include <iostream>
#include <vector>

void read_raster (const int &N, const int &M, std::vector<std::vector<int>> &raster) {
    int input;

    for (int i = 0; i < N; ++i) {
        std::vector<int> aux;

        for (int j = 0; j < M; ++j) {
            std::cin >> input;
            aux.push_back(input);
        }
        raster.push_back(aux);
    }
}

void print_raster (const int &N, const int &M, std::vector<std::vector<int>> &raster) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            std::cout << raster[i][j] << " ";
        } std::cout << "\n";
    }
}

int amplitude (const int &N, const int &M, std::vector<std::vector<int>> &raster) {
    int max = raster[0][0], min = raster[0][0];

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (raster[i][j] > max)
                max = raster[i][j];
            if (raster[i][j] < min)
                min = raster[i][j];
        } 
    }
    return max - min;
}
    

int main() {
    std::vector<std::vector<int>> raster;
    std::string command;
    int N, M;

    do {
        std::cin >> command;

        if (command.compare("RASTER") == 0) {
            // read array
            std::cin >> N >> M;
            read_raster(N, M, raster);
        } else if (command.compare("AMPLITUDE") == 0) {
            std::cout << amplitude(N, M, raster) << "\n";
        }

    } while (command.compare("TCHAU"));


    print_raster(N, M, raster);

    return 0;
}