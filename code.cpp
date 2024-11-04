#include<bits/stdc++.h>
#include<fstream>
#include<cmath>
#include<random>

#define int long long
using namespace std;

std::random_device rd;  // Obtain a random seed from the hardware
std::mt19937 gen(rd());

class Point {
private:
    int x, y;
public:
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }

    int getX() {
        return this->x;
    }

    int getY() {
        return this->y;
    }
};

vector<Point>points; // vriable to store points
vector<Point>best_answer_till_now; // stores best answer till now
int NOS_OF_TRY = 10000;

double find_dist_between(Point A, Point B) {
    int x_diff = A.getX() - B.getX();
    x_diff *= 1ll * x_diff;

    int y_diff = A.getY() - B.getY();
    y_diff *= 1ll * y_diff;

    return sqrt(x_diff + y_diff);
}


void read_file(ifstream &file) {
    int number_of_points; file >> number_of_points;

    for(int i=0;i<number_of_points;++i) {
        int slno, x_cor, y_cor;
        file >> slno >> x_cor >> y_cor;
        Point temp = Point(x_cor, y_cor);
        points.push_back(temp);
    }
}

double find_cost_for_order() {
    double ans = 0.0;
    for(int i=0;i<points.size()-1;++i) {
        Point curr = points[i];
        Point next = points[i + 1];

        ans += 1.0 * find_dist_between(curr, next);
    }
    Point curr = points[points.size() - 1];
    Point next = points[0];
    ans += 1.0 * find_dist_between(curr, next);
    return ans;
}

void jumble() {
    int min = 0;
    int max = points.size() - 1;
    uniform_int_distribution<> distr(min, max);
    int random_idx1 = distr(gen);
    int random_idx2 = distr(gen);

    Point temp = points[random_idx1];
    points[random_idx1] = points[random_idx2];
    points[random_idx2] = temp;
}

double simulate() {
    double ans = find_cost_for_order();
    best_answer_till_now = points;

    for(int i=0; i<NOS_OF_TRY-1;++i) {
        jumble();
        double current_cost = find_cost_for_order();
        if(current_cost < ans) {
            ans = current_cost;
            best_answer_till_now = points;
        }
    }

    return ans;
}


int32_t main(int argc, char *argv[]) {
    if(argc < 1) {
        cerr << "You need to provide the input file path";
        return 1;
    }

    string input_file = argv[1];
    ifstream file(input_file);

    if(argc > 2) { // the number of try is mentioned
        NOS_OF_TRY = atoi(argv[2]);
    }
    
    // handle if the file path is incorrect
    if (!file) {
        cerr << "Unable to open " << input_file;
        return 1;
    }

    read_file(file);

    double min_cost_to_travel = simulate();
    cout << "After performing " << NOS_OF_TRY << " steps we got the minimum cost is " << min_cost_to_travel << endl;
    cout << "And the order of travel is :- " << endl;
    for(Point p: best_answer_till_now) cout << p.getX() << " " << p.getY() << endl; 
    cout << "==========\n";
    return 0;
}