#include <iostream>
#include <vector>
#include <ctime>

class R_object {
public:
    void SetParametres(int large, int w, int p, std::vector<std::vector<int> > matrix_with_one) {
        weight = w;
        price = p; 
        size = large;
        matrix = matrix_with_one;
        BuildMatrix();
        MoveToLeftCorner();
    }

    std::vector<std::vector<int>> GetMatrix() {
        return matrix;
    }

    int GetWeight() {
        return weight;
    }

    int GetPrice() {
        return price;
    }

    int GetSize() {
        return size;
    }

    void MoveToLeftCorner() {       
        int farthest_left = matrix[0].size() - 1;
        int nearest_up = matrix.size() - 1;

        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[0].size(); j++) {
                if (matrix[i][j] == 1 && farthest_left > j)
                    farthest_left = j;

                if (matrix[i][j] == 1 && nearest_up > i) 
                    nearest_up = i;
                    
            }
        }

        if (farthest_left > 0)
            MoveHorizontalLeft(farthest_left);
        
        if (nearest_up > 0)
            MoveVerticalUp(nearest_up);
        
    }  

    void MoveHorizontalRight(int displacement) {
        for (int i = 0; i < matrix.size(); i ++) {
            for (int j = matrix.size() - 1; j > -1; j --) {
                if (matrix[i][j] == 1) {
                    matrix[i][j] = 0;
                    matrix[i][j+displacement] = 1;
                }
            }
        }    
    }

    void MoveVerticalUp(int displacement) {
        for (int i = 0; i < matrix.size(); i ++) {
            for (int j = 0; j < matrix.size(); j ++) {
                if (matrix[i][j] == 1) {
                    matrix[i][j] = 0;
                    matrix[i-displacement][j] = 1;
                }
            }
        }    
    }

    void MoveHorizontalLeft(int displacement) {
        for (int i = 0; i < matrix.size(); i ++) {
            for (int j = 0; j < matrix.size(); j ++) {
                if (matrix[i][j] == 1) {
                    matrix[i][j] = 0;
                    matrix[i][j-displacement] = 1;
                }
            }
        }    
    }

    void MoveVerticalDown(int displacement) {
        for (int i = matrix.size() - 1; i > -1; i --) {
            for (int j = 0; j < matrix.size(); j ++) {
                if (matrix[i][j] == 1) {
                    matrix[i][j] = 0;
                    matrix[i+displacement][j] = 1;
                }
            }
        }    
    }  

private:
    int weight;
    int price;
    int size;
    std::string output;
    std::vector<std::vector<int>> matrix;

    int rand_side() {
        return rand()%4;
    }

    std::pair<int, int> Find_first() {
        std::pair<int, int> numbers;

        for (int i = 0; i < matrix.size(); i ++) {
            for (int j = 0; j < matrix.size(); j++) {
                if (matrix[i][j] == 1) {
                    numbers.first = i;
                    numbers.second = j;
                    // std::cout << "first-pair = " << numbers.first << " : " << numbers.second << "\n";
                    return numbers;
                }
            }
        }
    }

    void BuildMatrix() {
        int volume = size;
        std::pair<int, int> pair_num = Find_first();
        std::pair<int, int> next_pair;
        
        for (int k = 1; k < volume; k ++) {
            next_pair = FindNext(rand_side(), pair_num);
            matrix[next_pair.first][next_pair.second] = 1;
            pair_num = next_pair;
        }
    }

    std::pair<int, int> FindNext(int side, std::pair<int, int> first_pair) {
        std::pair<int, int> next_pair;
        bool flag = false;

        while (flag == false) {
            // лево
            if (side == 0) {
                if (first_pair.second > 0 && matrix[first_pair.first][first_pair.second - 1] != 1) {
                    first_pair.second -= 1; 
                    next_pair = first_pair;
                    flag = true;
                    // std::cout << "Side = " << side << "\n";  
                    // std::cout << "L\n";       
                } else {
                    side = rand_side(); 
                    // std::cout << "no L\n";
                }
            } 

            // низ
            if (side == 1) {
                if (first_pair.first < matrix.size() - 1 && matrix[first_pair.first + 1][first_pair.second] != 1) {
                    first_pair.first += 1;
                    next_pair = first_pair;
                    flag = true;
                    // std::cout << "Side = " << side << "\n";
                    // std::cout << "D\n";
                } else {
                    side = rand_side();
                    // std::cout << "no D\n";
                }
            } 

            // право
            if (side == 2) {
                if (first_pair.second < matrix[0].size() - 1 && matrix[first_pair.first][first_pair.second + 1] != 1) {
                    first_pair.second += 1;
                    next_pair = first_pair;
                    flag = true;
                    // std::cout << "Side = " << side << "\n";
                    // std::cout << "R\n";
                } else {
                    side = rand_side();
                    // std::cout << "no R\n";
                }
            }

            // верх
            if (side == 3) {
                if (first_pair.first > 0 && matrix[first_pair.first - 1][first_pair.second] != 1) {
                    first_pair.first -= 1;
                    next_pair = first_pair;
                    flag = true;
                    // std::cout << "Side = " << side << "\n";
                    // std::cout << "U\n";
                } else {
                    side = rand_side();
                    // std::cout << "no U\n";
                }
            }  
        }

        return next_pair;
    }
}; 

class Rucksack {
public:
    Rucksack() {

    }

    Rucksack(const Rucksack& R) {
        size = R.GetSize();
        weight = R.GetWeight();
        cost = R.GetCost();
        matrix = R.GetMatrix();
        object_array = R.GetObjectsArray();
    }

    void Set(std::vector<std::vector<int>> mat) {
        size = mat.size() * mat[0].size();
        weight = 0;
        cost = 0;
        matrix = mat;
    }

    void Put(R_object object) {
        if (CheckPut(object) == true) {
            size -= object.GetSize();
            weight += object.GetWeight();
            cost += object.GetPrice();
            object_array.push_back(object);

            for (int i = 0; i < matrix.size(); i++) {
                for (int j = 0; j < matrix[i].size(); j++) {
                    if (matrix[i][j] == 0 && object.GetMatrix()[i][j] == 1) 
                        matrix[i][j] = 1;
                }
            }
        }
    }

    bool CheckPut(R_object object) {
        if (CheckCapasity(object.GetSize()) == true) {
            for (int i = 0; i < matrix.size(); i++) {
                for (int j = 0; j < matrix[i].size(); j++) {
                    if (matrix[i][j] == 1 && object.GetMatrix()[i][j] == 1)
                        return false;
                }
            }
            return true;
        }  
        return false;
    } 

    int GetWeight() const {
        return weight;
    }

    int GetCost() const {
        return cost;
    }

    int GetSize() const {
        return size;
    }

    std::vector<std::vector<int>> GetMatrix() const {
        return matrix;
    }

    std::vector<R_object> GetObjectsArray() const {
        return object_array;
    }   

private:
    int size;
    int weight;
    int cost;
    std::string output;
    std::vector<std::vector<int>> matrix;
    std::vector<R_object> object_array;

    bool CheckCapasity(int volume) {
        if (size - volume < 0)
            return false;

        return true;
    }
};

std::pair<int, int> FindFarthestPair(R_object object) {
    std::pair<int, int> farthest_pair = {0,0};
    // цикл который ищет int farthest_right & farthest_down
    for (int i = 0; i < object.GetMatrix().size(); i++) {
        for (int j = 0; j < object.GetMatrix()[i].size(); j++) {
            if (object.GetMatrix()[i][j] == 1 && farthest_pair.second < j)
                    farthest_pair.second = j;

            if (object.GetMatrix()[i][j] == 1 && farthest_pair.first < i) 
                    farthest_pair.first = i; 
        }
    }
    return farthest_pair;
}

void MakeSequence_of_one_object(std::vector<R_object>& vec, R_object object_0) {
    std::pair<int, int> farthest_pair;
    R_object object = object_0;
    int count_down = 1;

    farthest_pair = FindFarthestPair(object);
    while (farthest_pair.second < object.GetMatrix().size()-1) {
        object.MoveHorizontalRight(1);
        vec.push_back(object);
        farthest_pair = FindFarthestPair(object);

        if (farthest_pair.first < object.GetMatrix().size()-1 && farthest_pair.second == object.GetMatrix().size()-1) {
            object.MoveToLeftCorner();
            object.MoveVerticalDown(count_down);
            count_down += 1;
            vec.push_back(object);
            farthest_pair = FindFarthestPair(object);
        }
    }
    
}
