#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <list>


typedef std::pair<int, std::string> HashMap;

class HashTable
{

public:

    HashTable(int tableSize)
    : m_tableSize(tableSize),
      m_table(tableSize)
    {

    }

    void insertHashMap(const HashMap & map)
    {
        int index = hash(map.first);

        m_table[index].push_back(map);
    }

    bool getValue(int key, std::string & value)
    {
        int index = hash(key);

        auto iter = m_table[index].begin();

        while (iter != m_table[index].end())
        {
            if (iter->first == key)
            {
                value = iter->second;
                return true;
            }

            iter++;
        }

        return false;
    }

private:

    int hash(int key)
    {
        int index = key % m_tableSize;

        return index;
    }

    int m_tableSize;

    std::vector<std::list<HashMap> > m_table;
    
};


int main(int argc, char* argv[])
{
    // Create hash table with 1000 indexes
    HashTable table = HashTable(1000);
    int key1 = 20;
    std::string value1 = "Mike";
    HashMap p1 = std::make_pair(key1, value1);
    table.insertHashMap(p1);
    std::string output1;
    bool success = table.getValue(key1, output1);
    if (success)
    {
        std::cout << "Value for " << key1 << " = " << output1 << "\n";
    }

    int key2 = 1020;
    std::string value2 = "Porsche";
    HashMap p2 = std::make_pair(key2, value2);
    table.insertHashMap(p2);
    std::string output2;
    success = table.getValue(key2, output2);
    if (success)
    {
        std::cout << "Value for " << key2 << " = " << output2 << "\n";
    }

    return 0;
}
