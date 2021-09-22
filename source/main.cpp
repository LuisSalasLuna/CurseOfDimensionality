#include <random>
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <ctime>
#include <vector>
#include <math.h>
#include <chrono>

using namespace std;

double DistanciaEuclidiana(vector<int> inicio, vector<int> fin) {
    double res = 0;
    for (int i = 0; i < inicio.size(); i++) {
        res += pow(fin[i] - inicio[i], 2);
    }
    return sqrt(res);
}
int main()
{
    chrono::time_point<chrono::high_resolution_clock> start, end;
    start = chrono::high_resolution_clock::now();
    random_device rd;  //Seed for the random number engine
    mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    int maxi = 1000;
    int Npoints = 20000;
    int dim = 25; //cambiar a cin
    uniform_int_distribution<> distrib(1, maxi);

    //Crear puntos
    vector<vector<int>> Points;
    for (int n = 0; n < Npoints; ++n) {
        vector<int> Point;
        for (int m = 0; m < dim; ++m)
            Point.push_back(distrib(gen));
        Points.push_back(Point);
    }
    //Print puntos
    /*for (int n = 0; n < Npoints; ++n) {
        for (int m = 0; m < dim; ++m)
            cout << Points[n][m] << ',';
        cout << '\n';
    }*/

    //Seleccionar un Punto aleatorio
    srand(time(NULL));
    int pos = rand() % Points.size();
    vector<int> A = Points[pos];
    Points.erase(Points.begin() + pos);
    //Imprimir punto elegido aleatoriamente
    /*cout << "Punto alt:";  
    for (int m = 0; m < dim; ++m)
        cout << A[m] << ',';
    cout << "\n";
    */
    //Calcular Distancias, min y max
    double min, max;
    vector<double> Distancias;
    for (int n = 0; n < Points.size(); ++n) {
        double dist = DistanciaEuclidiana(A, Points[n]);
        Distancias.push_back(dist);
        if (Distancias.size() == 1) {
            min = dist;
            max = min;
        }
        else {
            if (dist < min) min = dist;
            if (dist > max) max = dist;
        }
    }
    //Print Dostancias
    /*for (int n = 0; n < Distancias.size(); ++n) {
        cout << Distancias[n] << '\n';
    }*/
    //cout << "Min: " << min << endl;  // Distancia Minima
    //cout << "Max: " << max << endl;  // Distancia Maxima

    //Distribucion
    int arr[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
    for (int n = 0; n < Distancias.size(); ++n) {
        double posi = (10 * (Distancias[n] - min)) / (max - min);
        if (posi == 0) { arr[0] += 1; }
        else {
            int post = posi;
            arr[post + 1] += 1;
        }
    }
    //cout << endl;
    for (int n = 0; n < 12; ++n) {
        cout << arr[n] << "\n";
    }
    end = chrono::high_resolution_clock::now();
    int64_t duration = chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); // duration is holding the elapsed time
    cout <<"\n Tiempo: "<< duration;
}