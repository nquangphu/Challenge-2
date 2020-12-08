#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


struct NODE {
	NODE* child[26];			//mảng lưu địa chỉ tới các node con của node đó
	bool isEndOfWord;			//là true nếu node đó là kết thúc của 1 từ
};

//Tạo 1 node rỗng 
NODE* creatNode() {	
	NODE* p = new NODE;
	p->isEndOfWord = false;
	for (int i = 0; i < 26; i++) p->child[i] = nullptr;

	return p;
}

//Thêm vào chuỗi s
void insert(NODE* root, string s) {
	NODE* p = root;

	for (int i = 0; i < s.size(); i++) {
		int index = s[i] - 'a';

		if (!p->child[index]) p->child[index] = creatNode();
		p = p->child[index];
	}

	p->isEndOfWord = true;
}

//Tìm kiếm chuỗi s
bool search(NODE* root, string s) {
	NODE* p = root;

	for (int i = 0; i < s.size(); i++) {
		int index = s[i] - 'a';
		
		if (!p->child[index]) return false;
		p = p->child[index];
	}

	return (p != nullptr && p->isEndOfWord);
}

//Đọc file Dic.txt
void readfile(ifstream& f, NODE* root) {
	if (!f.is_open()) {
		cout << "Can not open file!" << endl;
		return;
	}

	while (!f.eof()) {
		string line;
		getline(f, line);
		insert(root, line);
	}
}

string input(int* freq) {
	string s, prefixs;
	getline(cin, s);
	for (int i = 0; i < s.size(); i++) {
		if (s[i] != ' ') {
			prefixs += s[i];
			int index = s[i] - 'a';
			freq[index]++;
		}
	} 

	return prefixs;
}

//CREAT WORD
string s = "";
int wordCount(NODE* root, int freq[], vector<string>& ss) {
	int result = 0;

	if ((root->isEndOfWord) && (s.size() > 2)) {
		result++;
		ss.push_back(s);
	}

	for (int i = 0; i < 26; i++) {
		if (root->child[i] && freq[i] > 0) {
			freq[i]--;
			s += i + 'a';
			result += wordCount(root->child[i], freq, ss);
			freq[i]++;
			s = s.substr(0, s.size() - 1);
		}
	}

	return result;
}

int main() {
	string filename = "Dic.txt";
	ifstream f(filename);

	int freq[26] = { 0 };				//Mảnh lưu số lần xuất hiện của các ký tự trong input.
	vector<string> ss;					//Vd: input: a b e a == > freq[a]=2, freq[b]=1, freq[e]=1.
	NODE* root = creatNode();

	readfile(f, root);					//Đọc file Dic.txt
	string prefixs = input(freq);

	cout << wordCount(root, freq, ss) << endl;

	for (int i = 0; i < ss.size(); i++) {
		ss[i].reserve();
		cout << ss[i] << endl;
	}
	
	system("pause");
	return 0;
}