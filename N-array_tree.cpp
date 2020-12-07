#include <iostream>
#include "Rusksak_obj.cpp"

template <class T> class tnode {
public:
	T data;
	std::vector<tnode*> children;

	tnode(const T& item):data(item) {
		children = {};
	}

	tnode* Add(const T& item) {
		tnode* new_node = new tnode (item);

		children.push_back(new_node);
		
		return new_node;
	}

	~tnode() {
		for (int i = 0; i < children.size() && children[i]; i++)
			delete children[i];
	}
};

template <class T> class N_array_tree {
public:
	N_array_tree(const T& object):root(new tnode<T>(object)) {
	
	}
	
	tnode<T>* GetRoot() {
		return root;
	}

	void FillTree(tnode<Rucksack>* start_node, std::vector<std::vector<R_object>> array) {
		for (int j = 0; j < array.size(); j++) {
			for (int i = 0; i < array[j].size(); i++) {
				if (start_node->data.CheckPut(array[j][i])) {
					tnode<Rucksack>* new_node = new tnode<Rucksack>(start_node->data);
					new_node->data.Put(array[j][i]);					
					start_node->children.push_back(new_node);

					std::vector<std::vector<int>> matrix;
					matrix = start_node->children[start_node->children.size()-1]->data.GetMatrix();

					std::vector<std::vector<R_object>> massive = array;
					int erase_count;
					erase_count = j;
					std::cout << "Erase = " << erase_count << "\n";

					massive.erase(massive.begin() + j,massive.begin() + j + 1);
					FillTree(new_node, massive);	
				}
			}
		}
	}

	void PrintTree(tnode<T> *root, std::string& s) {
		if(!root)
			return;

		s += root->data + "\n";

		for (int i = 0; i < root->children.size() && root->children[i]; i++) {
			s += "/";
			PrintTree(root->children[i], s);
		}

		s += "/ ";
	}

	std::string TreeToString() {
		std::string s;
		PrintTree(root, s);
		return s;
	}

	~N_array_tree() {
		delete root;
	}

	void PrintNodes(tnode<Rucksack>* node) {
		for (int i = 0; i < node->children.size(); i ++) {
			for (int j = 0; j < node->children[i]->data.GetMatrix().size(); j ++) {
				for (int k = 0; k < node->children[i]->data.GetMatrix()[j].size(); k ++)
					std::cout << node->children[i]->data.GetMatrix()[j][k] << " ";   
				std::cout << "\n"; 

			}
			std::cout << "\n";
			PrintNodes(node->children[i]);
		}
	}

	void GetAllLevesBySequnce(std::vector<std::vector<Rucksack>& Rucksack_array) {
		
	}
private:
	tnode<T>* root;
};

int main() {
	Rucksack R;
	R_object object_0;
	R_object object_1;
	R_object object;
	std::vector<R_object> array_of_objects_0;
	std::vector<R_object> array_of_objects_1;
	std::vector<std::vector<R_object>> array;
	int size_matrix = 3;
	std::vector<std::vector<int>> matrix(size_matrix, std::vector<int> (size_matrix));     

    // задание матрицы
    int z = 0;
    for (int i = 0; i < size_matrix; i++) {
        for (int j = 0; j < size_matrix; j++) 
            matrix[i][j] = z;  
    }

	R.Set(matrix);
	object_0.SetParametres(0, 3, 4, matrix);
    matrix[1][1] = 1;
    // конец задания матрицы

	object_0.SetParametres(4, 3, 4, matrix);
	std::cout << "First object :\n";
	for (int i = 0; i < size_matrix; i++) {
        for (int j = 0; j < size_matrix; j++) 
            std::cout << object_0.GetMatrix()[i][j] << " ";   
        std::cout << "\n"; 
    }
    std::cout << "\n";

	object_1.SetParametres(3, 3, 2, matrix);
	std::cout << "Second object :\n";
	for (int i = 0; i < size_matrix; i++) {
        for (int j = 0; j < size_matrix; j++) 
            std::cout << object_1.GetMatrix()[i][j] << " ";   
        std::cout << "\n"; 
    }
    std::cout << "\n";

	array_of_objects_0.push_back(object_0);
	MakeSequence_of_one_object(array_of_objects_0, object_0);
	array_of_objects_1.push_back(object_1);
	MakeSequence_of_one_object(array_of_objects_1, object_1);

	array.push_back(array_of_objects_0);
	array.push_back(array_of_objects_1);

	for (int k = 0; k < array.size(); k ++) {
		for (int l = 0; l < array[k].size(); l++) {
			for (int i = 0; i < size_matrix; i++) {
				for (int j = 0; j < size_matrix; j++) 
					std::cout << array[k][l].GetMatrix()[i][j] << " ";   
				std::cout << "\n"; 
			}
			std::cout << "\n";
		}	
	}
    N_array_tree<Rucksack> tree (R);

	std::cout << "\nhang yourself at home\n";

	tree.FillTree(tree.GetRoot(), array);
	tnode<Rucksack>* node = tree.GetRoot();

	std::cout << "Yep\n";
	tree.PrintNodes(node);

	return 0;
}