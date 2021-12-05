#ifndef TREESORT_SORTER_H
#define TREESORT_SORTER_H

#include <iostream>
#include <fstream>
#include <set>
#include <cstdio>
#include <algorithm>
#include "BinaryTree.h"

#define IN_MEMORY 0
#define IN_FILE 1

class Sorter {
private:
    static const uintmax_t inMemoryThreshold =  1024 * 1024 * 300;
    static const size_t sorterFileSizeThreshold = 1024 * 1024 * 10;
    std::ifstream inputStream;
    std::ofstream outputStream;
    int sorterMode;
    int sortFiles;
    bool sorted;
    bool printResult;

    void SortInMemory() {
        std::vector<int> values;
        int value;
        while (inputStream >> value) {
            values.push_back(value);
        }
        inputStream.close();

        BinaryTree binaryTree(values);
        std::vector<int> result = binaryTree.GetOrder();
//        std::sort(values.begin(), values.end());
//        std::vector<int> result = values;
        if (printResult) {
            for (auto entry : result) {
                outputStream << entry << " ";
            }
        }
        outputStream.close();
    }

    std::string GetSortFileName(int n) {
        return "res" + std::to_string(n) + ".txt";
    }

    void PartialSort(const std::vector<int>& values) {
        static intmax_t sortedEntries = 0;
        std::ofstream sortFile;
        std::string sortFileName = GetSortFileName(sortFiles);
        sortFile.open(sortFileName, std::fstream::out);
        BinaryTree binaryTree(values);
        std::vector<int> result = binaryTree.GetOrder();
        for (auto entry : result) {
            sortFile << entry << " ";
        }
        sortFile.close();
        sortedEntries += values.size();
        std::cout << "Sorted file no." << sortFiles << " Sorted entries: " << sortedEntries << "\n";
        sortFiles++;
    }

    void MergeFiles() {
        std::multiset<std::pair<int, std::ifstream*>> topElements;
        for (int i = 0; i < sortFiles; i++) {
            std::string sortFileName = GetSortFileName(i);
            auto* sortFile = new std::ifstream();
            sortFile->open(sortFileName, std::fstream::in);
            int value;
            *sortFile >> value;
            topElements.insert({value, sortFile});
        }
        while (!topElements.empty()) {
            auto winner = topElements.begin();
            if (printResult) {
                outputStream << winner->first << "\n";
            }
            auto sortFile = winner->second;
            topElements.erase(winner);
            int value;
            if (*sortFile >> value) {
                topElements.insert({value, sortFile});
            } else {
                sortFile->close();
            }
        }
        for (int i = 0; i < sortFiles; i++) {
            remove(GetSortFileName(i).c_str());
        }
        outputStream.close();
    }

    size_t GetSize(int value) {
            return sizeof(value);
    }

    void SortInFile() {
        std::vector<int> values;
        int value;
        size_t currentSize = 0;
        while (inputStream >> value) {
            values.push_back(value);
            currentSize += GetSize(value);
            if (currentSize > sorterFileSizeThreshold) {
                PartialSort(values);
                values.clear();
                currentSize = 0;
            }
        }
        if (!values.empty()) {
            PartialSort(values);
            values.clear();
        }
        MergeFiles();
    }

    static std::fstream::pos_type GetFileSize(const std::string& path) {
        std::ifstream testFile(path, std::ios::binary);
        const auto begin = testFile.tellg();
        testFile.seekg (0, std::ios::end);
        const auto end = testFile.tellg();
        const auto fsize = (end-begin);
        testFile.close();
        return fsize;
    }
public:
    explicit Sorter(const std::string& inputName, const std::string& outputName, bool printResult, bool forceInFile = false) :
        sorted(false), sortFiles(0), printResult(printResult) {
        uintmax_t fileSize = GetFileSize(inputName);
        if (fileSize > inMemoryThreshold || forceInFile) {
            sorterMode = IN_FILE;
            std::cout << "Using IN_FILE sorting\n";
        } else {
            sorterMode = IN_MEMORY;
            std::cout << "Using IN_MEMORY sorting\n";
        }
        inputStream = std::ifstream(inputName.c_str(), std::fstream::in);
        outputStream = std::ofstream(outputName.c_str(), std::fstream::out);
    }
    void Sort() {
        if (sorted) { return; }
        if (sorterMode == IN_MEMORY) {
            SortInMemory();
        } else {
            SortInFile();
        }
        sorted = true;
    }
};

#endif
