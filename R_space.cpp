#include <iostream>
#include <cmath>
#include "N-array_tree.cpp"

void menu(int& flag, std::vector<std::vector<int>>& matrix);
void FindRucksacks(std::vector<Rucksack> vec_0, std::vector<Rucksack>& vec_1);
void menu(int& flag_check);
std::vector<float> HSVtoRGB(std::vector<float> vec);
void Draw(int flag, std::vector<std::vector<float>> Colors_vector, std::vector<Rucksack> R_vector);

int main() {
    int check_flag;
    int flag = 1;
    int flag_1 = 0;
    int size_matrix = 4;
    int sq_cons = size_matrix*size_matrix;
    int size_v = size_matrix*size_matrix*3;
    float vertices [size_v];
    float start_point_x = -0.8;
    float point_x = -0.8;
    float point_y = 0.8;
    float width = 1.6;
    float a = width / size_matrix;
    Rucksack R;
    std::vector<std::vector<R_object>> objects_array (6, std::vector<R_object> (1));
    std::vector<std::vector<int>> matrix (size_matrix, std::vector<int> (size_matrix));
    std::vector<Rucksack> R_array;
    std::vector<Rucksack> R_array_final;
    srand(time(NULL)); 

    // задание поля 
    for (int i = 0; i < size_v; i+=3) {
       vertices[i] = point_x + (i/3)%size_matrix*a + a/2;
       vertices[i+1] = point_y - (i/3)/size_matrix*a - a/2;
       vertices[i+2] = 0; 
    }
    // конец задания поля 

    std::vector<std::vector<float>> Colors_vector (2);

    for (int i = 0; i < Colors_vector.size(); i ++) {
        std::vector<float> vec = {static_cast<float> (360.0/float(Colors_vector.size())*float(i)), 1, 1};
        Colors_vector[i] = HSVtoRGB(vec);
    }

    for (int i = 0; i < size_matrix; i ++) {
        for (int j = 0; j < size_matrix; j ++)
            matrix[i][j] = 0; 
    }

    R.Set(matrix);
    matrix[size_matrix/2][size_matrix/2] = 1;
    N_array_tree<Rucksack> tree (R);

    // ввод параметров для объектов и получение всех возможных мест нахождения объектов в рюкзаке
    for (int i = 0; i < objects_array.size(); i ++) {
        objects_array[i][0].SetParametres(2 + rand()% (size_matrix - 1), 1 + rand()% 10000000, 10 + rand()% 10000000, matrix);
        MakeSequence_of_one_object(objects_array[i], objects_array[i][0]);
    }

    // заполнение дерева
    tree.FillTree(tree.GetRoot(),  objects_array);
    // tree.PrintNodes(tree.GetRoot());
   
    // получение всех листов
    tree.GetAllLevesBySequnce(tree.GetRoot(), R_array);

    // отбор рюкзаков по объему, стоимости и весу
    FindRucksacks(R_array, R_array_final);
    std::cout << "Размер массива = " << R_array_final.size() << "\n";

    while (flag != 0) {
        menu(check_flag);

        if (check_flag == 0)
            break;

        int check = 0;
        std::cout << "\nВведите номер рюкзака, матрицу которого вы бы хотели посмотреть\n";
        std::cin >> check;
        Draw(check, Colors_vector, R_array_final);
       
    }
	return 0;
}

void Draw(int flag, std::vector<std::vector<float>> Colors_vector, std::vector<Rucksack> R_vector) {
    std::cout << "\n";
    std::cout << "PRICE: " << R_vector[flag].GetCost() << " WEIGHT: " << R_vector[flag].GetWeight() << "\n";
    for (int k = 0; k < R_vector[flag].GetMatrix().size(); k ++) {
        for (int l = 0; l < R_vector[flag].GetMatrix().size(); l ++) {
            for (int m = 0; m < R_vector[flag].GetObjectsArray().size(); m ++) {
                if (R_vector[flag].GetMatrix()[k][l] == 0) {
                    std::cout<< "0\t";
                    break;
                } else if (R_vector[flag].GetMatrix()[k][l] == 1 && R_vector[flag].GetObjectsArray()[m].GetMatrix()[k][l] == 1) {
                    std::cout << m + 1<< "\t";
                }
            }
        }
        std::cout << "\n";
    }
}


void FindRucksacks(std::vector<Rucksack> vec_0, std::vector<Rucksack>& vec_1) {
    int volume = 100;
    int price = 0;
    int weight = 0;

    for (int i = 0; i < vec_0.size(); i ++) {
        if (vec_0[i].GetSize() < volume)
            volume = vec_0[i].GetSize();
        
        if (vec_0[i].GetCost() > price)
            price = vec_0[i].GetCost();
        
        if (vec_0[i].GetWeight() > weight)
            weight = vec_0[i].GetWeight();    
    }

    for (int i = 0; i < vec_0.size(); i ++) {
        if (vec_0[i].GetCost() == price || vec_0[i].GetWeight() == weight)
            vec_1.push_back(vec_0[i]);   
    }
}

std::vector<float> HSVtoRGB(std::vector<float> vec) {
    std::vector<float> color = {0.0, 0.0, 0.0};
    float fC = vec[2] * vec[1]; // Chroma
    float fHPrime = fmod(vec[0] / 60.0, 6);
    float fX = fC * (1 - fabs(fmod(fHPrime, 2) - 1));
    float fM = vec[2] - fC;

    if(0 <= fHPrime && fHPrime < 1) {
        color[0] = fC;
        color[1] = fX;
        color[2] = 0;
    } else if(1 <= fHPrime && fHPrime < 2) {
        color[0] = fX;
        color[1] = fC;
        color[2] = 0;
    } else if(2 <= fHPrime && fHPrime < 3) {
        color[0] = 0;
        color[1] = fC;
        color[2] = fX;
    } else if(3 <= fHPrime && fHPrime < 4) {
        color[0] = 0;
        color[1] = fX;
        color[2] = fC;
    } else if(4 <= fHPrime && fHPrime < 5) {
        color[0] = fX;
        color[1] = 0;
        color[2] = fC;
    } else if(5 <= fHPrime && fHPrime < 6) {
        color[0] = fC;
        color[1] = 0;
        color[2] = fX;
    } else {
        color[0] = 0;
        color[1] = 0;
        color[2] = 0;
    }

    color[0] += fM;
    color[1] += fM;
    color[2] += fM;

    return color;
}

void menu(int& flag) {
    std::cout << "\nДля начала работы программы введите 1\n";
    std::cout << "Если вы хотите выйти из программы нажмите введите 0\n";

    std::cin >> flag;
}

