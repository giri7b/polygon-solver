#include <bits/stdc++.h>
#include <chrono>
#include <fstream>
using namespace std;
using ll = long long;
using Clock = chrono::high_resolution_clock;

struct Building { 
    double x, y, cost; 
};
struct Point { 
    double x, y; 
};

class FastPolygonSolver {
public:
    FastPolygonSolver(const vector<Building>& buildings, int K)
      : B(buildings), N(buildings.size()), Kmin(K), bestCost(1e18)
    {}

    pair<double, vector<Point>> solve() {
        runAllNegatives();
        runPureCost();
        runGreedyImprove();
        return {bestCost, bestRect};
    }

private:
    const vector<Building>& B;
    int N, Kmin;
    double bestCost;
    vector<Point> bestRect;

    void evaluate(const vector<int>& sel) {
        if ((int)sel.size() < Kmin) return;
        double perim = calcPerimeter(sel);
        double sumCost = 0;
        for (int i : sel) 
            sumCost += B[i].cost;
        double total = perim + sumCost;
        if (total < bestCost) {
            bestCost = total;
            bestRect = makeRectangle(sel);
        }
    }

    double calcPerimeter(const vector<int>& idx) {
        double minX = B[idx[0]].x, maxX = minX;
        double minY = B[idx[0]].y, maxY = minY;
        for (int i : idx) {
            minX = min(minX, B[i].x);
            maxX = max(maxX, B[i].x);
            minY = min(minY, B[i].y);
            maxY = max(maxY, B[i].y);
        }
        return 2.0 * ((maxX - minX) + (maxY - minY));
    }

    vector<Point> makeRectangle(const vector<int>& idx) {
        double minX = B[idx[0]].x, maxX = minX;
        double minY = B[idx[0]].y, maxY = minY;
        for (int i : idx) {
            minX = min(minX, B[i].x);
            maxX = max(maxX, B[i].x);
            minY = min(minY, B[i].y);
            maxY = max(maxY, B[i].y);
        }
        return vector<Point>{
            {minX, minY},
            {maxX, minY},
            {maxX, maxY},
            {minX, maxY}
        };
    }

    void runAllNegatives() {
        vector<int> neg;
        for (int i = 0; i < N; i++) 
            if (B[i].cost < 0) 
                neg.push_back(i);
        vector<pair<double,int>> pos;
        for (int i = 0; i < N; i++) 
            if (B[i].cost >= 0) 
                pos.emplace_back(B[i].cost, i);
        sort(pos.begin(), pos.end());
        vector<int> sel = neg;
        for (size_t j = 0; j < pos.size() && sel.size() < (size_t)Kmin; j++)
            sel.push_back(pos[j].second);
        evaluate(sel);
    }

    void runPureCost() {
        vector<pair<double,int>> all; all.reserve(N);
        for (int i = 0; i < N; i++) 
            all.emplace_back(B[i].cost, i);
        sort(all.begin(), all.end());
        vector<int> sel;
        for (int i = 0; i < Kmin; i++) 
            sel.push_back(all[i].second);
        evaluate(sel);
    }

    void runGreedyImprove() {
        vector<pair<double,int>> all; all.reserve(N);
        for (int i = 0; i < N; i++) 
            all.emplace_back(B[i].cost, i);
        sort(all.begin(), all.end());
        vector<int> base;
        for (int i = 0; i < Kmin; i++) 
            base.push_back(all[i].second);
        evaluate(base);
        for (int i = Kmin; i < min(N, Kmin+10); i++) {
            if (all[i].first < 0) {
                vector<int> tmp = base;
                tmp.push_back(all[i].second);
                evaluate(tmp);
            }
        }
    }
};

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    ifstream in(argv[1]);
    if (!in) {
        cerr << "Cannot open input file: " << argv[1] << "\n";
        return 1;
    }

    int N, K;
    in >> N >> K;
    vector<Building> buildings(N);
    for (int i = 0; i < N; i++)
        in >> buildings[i].x >> buildings[i].y >> buildings[i].cost;

    auto t0 = Clock::now();
    FastPolygonSolver solver(buildings, K);
    auto result = solver.solve();
    auto t1 = Clock::now();

    double bestCost = result.first;
    const vector<Point>& bestRect = result.second;

    cout << fixed << setprecision(6) << bestCost << "\n";
    for (size_t i = 0; i < bestRect.size(); i++) {
        cout << bestRect[i].x << " " << bestRect[i].y << "\n";
    }

    double elapsed = chrono::duration<double>(t1 - t0).count();
    cerr << "Elapsed: " << elapsed << " s\n";
    return 0;
}
