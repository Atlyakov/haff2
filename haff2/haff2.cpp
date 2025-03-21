#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <string>
#include <windows.h>

using namespace std;

// Структура для узла дерева Хаффмана
struct Node {
    char ch; // Символ
    int freq; // Частота
    vector<Node*> children; // Дочерние узлы

    Node(char character, int frequency) : ch(character), freq(frequency) {}
};

// Компаратор для приоритетной очереди
struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->freq > right->freq; // Узел с меньшей частотой имеет более высокий приоритет
    }
};

// Рекурсивная функция для получения кодов Хаффмана
void getCodes(Node* root, const string& str, unordered_map<char, string>& huffmanCodes) {
    if (!root) return;

    // Если узел является листом, сохраняем код
    if (root->children.empty()) {
        huffmanCodes[root->ch] = str;
    }

    // Рекурсивно проходим по дочерним узлам
    for (size_t i = 0; i < root->children.size(); ++i) {
        getCodes(root->children[i], str + to_string(i), huffmanCodes); // Используем индекс как код
    }
}

// Основная функция для построения дерева Хаффмана
void buildHuffmanTree(const vector<char>& characters, const vector<int>& frequencies) {
    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    // Создаем узлы и добавляем их в приоритетную очередь
    for (size_t i = 0; i < characters.size(); ++i) {
        minHeap.push(new Node(characters[i], frequencies[i]));
    }

    // Построение дерева Хаффмана
    while (minHeap.size() > 1) {
        vector<Node*> selectedNodes;

        // Выбираем до 4 узлов с наименьшей частотой
        for (int i = 0; i < 4 && !minHeap.empty(); ++i) {
            selectedNodes.push_back(minHeap.top());
            minHeap.pop();
        }

        // Создаем новый узел с частотой, равной сумме частот выбранных узлов
        Node* newNode = new Node('\0', 0);
        for (Node* node : selectedNodes) {
            newNode->freq += node->freq;
            newNode->children.push_back(node);
        }

        minHeap.push(newNode);
    }

    // Корень дерева
    Node* root = minHeap.top();

    // Получаем коды Хаффмана
    unordered_map<char, string> huffmanCodes;
    getCodes(root, "", huffmanCodes);

    // Выводим коды
    cout << "Символы и их коды Хаффмана:\n";
    for (const auto& pair : huffmanCodes) {
        cout << pair.first << ": " << pair.second << endl;
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    // Символы и их частоты
    vector<char> characters = { '_', 'О', 'А', 'Н', 'Е', 'Т', 'И', 'С', 'Л', 'В', 'Р', 'Д', 'П', 'Ы', 'Я', 'Г', 'М', 'К', 'Ж', 'Ь', 'Х', 'Й', 'Б', 'Ч', 'З', 'У', 'Ш', 'Ю', 'Э', 'Ц', 'Щ'};
    vector<int> frequencies = { 104, 63, 54, 54, 54, 36, 35, 26, 21, 20, 19, 17, 13, 13, 12, 12, 11, 11, 10, 10, 9, 9, 8, 7, 7, 6, 4, 3, 2, 2, 1}; // Пример частот

    buildHuffmanTree(characters, frequencies);

    return 0;
}