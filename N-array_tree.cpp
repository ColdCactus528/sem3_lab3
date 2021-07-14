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

	#ifdef DEBUG 
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
	#endif

	void GetAllLevesBySequnce(tnode<Rucksack>* node, std::vector<Rucksack>& Rucksack_array) {
		if (node->children.size() < 1) 
			Rucksack_array.push_back(node->data); 

		for (int i = 0; i < node->children.size(); i ++) {
				GetAllLevesBySequnce(node->children[i], Rucksack_array);
		}
	}
private:
	tnode<T>* root;
};
