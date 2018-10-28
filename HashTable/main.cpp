#include <algorithm>
#include <forward_list>
#include <iostream>
#include <string>
#include <vector>

class HashTable {
 public:
  explicit HashTable(size_t size);
  HashTable(const HashTable&) = delete;
  HashTable& operator=(const HashTable&) = delete;

  bool Has(const std::string& key) const;
  bool Add(const std::string& key);
  bool Remove(const std::string& key);

 private:
  std::vector<std::forward_list<std::string>> table;
};

int Hash(const std::string& key) {
  if (key.empty()) return 3;
  return key[0];
}

HashTable::HashTable(size_t size) :
    table(size)
{}

bool HashTable::Has(const std::string& key) const {
  const size_t hash = Hash(key) % table.size();
  const auto& list = table[hash];
  return std::find(list.begin(), list.end(), key) != list.end();
}

bool HashTable::Add(const std::string& key) {
  const size_t hash = Hash(key) % table.size();
  auto& list = table[hash];
  if (std::find(list.begin(), list.end(), key) != list.end()) {
    return false;
  }
  list.emplace_front(key);
  return true;
}

bool HashTable::Remove(const std::string& key) {
  const size_t hash = Hash(key) % table.size();
  auto& list = table[hash];
  if (list.empty()) return false;
  if (list.front() == key) {
    list.pop_front();
    return true;
  }
  // Итерируемся по списку, проверяя следующий элемент за текущим.
  for (auto it = list.begin(); std::next(it) != list.end(); ++it) {
    if (*std::next(it) == key) {
      // Удаляем следующий за текущим.
      list.erase_after(it);
      return true;
    }
  }
  return false;
}

int main() {
  HashTable strings(80);
  char command = 0;
  std::string key;
  while (std::cin >> command >> key) {
    switch (command) {
      case '?':
        std::cout << (strings.Has(key) ? "OK" : "FAIL") << std::endl;
        break;
      case '+':
        std::cout << (strings.Add(key) ? "OK" : "FAIL") << std::endl;
        break;
      case '-':
        std::cout << (strings.Remove(key) ? "OK" : "FAIL") << std::endl;
        break;
      default:
        std::cerr << "bad input" << std::endl;
        return 0;
    }
  }
  return 0;
}