#include "trie.hpp"

void Trie::init(const std::vector<std::string>& word_list)
{
    //RESET
    for (auto const s: word_list)
        insert(s);
}

std::future<std::pair<std::string, int>> Trie::search(const std::string& w)
{
    while (remove_counter_.load() > 0) {}
    atomic_fetch_add(read_write_counter_, 1);
    root_.search(w);
    atomic_fetch_sub(read_write_counter_, 1);
}

std::future<void> Trie::insert(const std::string& w)
{
    while (remove_counter_.load() > 0) {}
    atomic_fetch_add(read_write_counter_, 1);
    root_.insert(w);
    atomic_fetch_sub(read_write_counter_, 1);
}

std::future<void> Trie::erase(const std::string& w)
{
    atomic_fetch_add(remove_counter_, 1);
    while (read_write_counter_.load() > 0) {}
    root_.erase(w);
    atomic_fetch_sub(remove_counter_, 1);
}
