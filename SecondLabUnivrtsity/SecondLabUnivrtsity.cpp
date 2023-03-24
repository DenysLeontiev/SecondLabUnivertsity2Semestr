#include <iostream>
#include <fstream>
#include <windows.h>
#include <filesystem>

#define MAX_LEN 100

using namespace std;

struct Node {
    char data[MAX_LEN];
    Node* next;
};

Node* Push(Node* top, const char* str) {
    Node* new_node = new Node;
    strcpy(new_node->data, str);
    new_node->next = top;
    return new_node;
}

Node* Pop(Node* top) {
    if (top == NULL) {
        return NULL;
    }
    Node* temp = top;
    top = top->next;
    delete temp;
    return top;
}

void FreeStack(Node* top) {
    while (top != NULL) {
        top = Pop(top);
    }
}

void ShowFiles()
{
    cout << endl;
    WIN32_FIND_DATA FindFileData;
    HANDLE hFind;

    char buffer[MAX_PATH];
    GetCurrentDirectory(sizeof(buffer), buffer);

    cout << "Current directory: " << buffer << endl;
    hFind = FindFirstFile("*.txt", &FindFileData);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        cout << "Invalid File Handle. GetLastError() reports " << (double)GetLastError();
        return;
    }
    cout << "Your files:\n";
    cout << FindFileData.cFileName << endl;
    while (FindNextFile(hFind, &FindFileData) != 0)
    {
        cout << FindFileData.cFileName << endl;
    }
    FindClose(hFind);
}


int main() {

    ShowFiles();
    ifstream inputFile;
    char filename[MAX_LEN];
    char buffer[MAX_LEN];
    Node* top = NULL;

    cout << "Enter filename: ";
    cin >> filename;

    inputFile.open(filename);

    if (!inputFile) {
        cout << "Error opening file.\n";
        return 1;
    }

    while (inputFile.getline(buffer, MAX_LEN)) {
        char new_str[MAX_LEN];
        sprintf(new_str, "%d: %s", top == NULL ? 1 : atoi(top->data) + 1, buffer);
        cout << new_str << endl;
        top = Push(top, new_str);
    }

    FreeStack(top);

    inputFile.close();

    return 0;
}
