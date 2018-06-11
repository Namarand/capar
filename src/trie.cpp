#include "trie.hpp"

Trie::Trie()
    : root_(new TrieNode())
{}

void Trie::init(const std::vector<std::string>& word_list)
{
    //RESET
    for (auto const s: word_list)
        insert(s);
}

std::future<std::pair<std::string, int>> Trie::search(const std::string& w) const
{
    return std::async([this, w](){
       // while (remove_counter_.load() > 0) {}
       // read_write_counter_.fetch_add(1);
        auto res = root_.load()->search('{' + w);
       // read_write_counter_.fetch_sub(1);
       res.first = res.first.substr(1, res.first.length() - 1);
        return res;
    });
}

std::future<void> Trie::insert(const std::string& w)
{
    return std::async([this, w](){
       // while (remove_counter_.load() > 0) {}
       // read_write_counter_.fetch_add(1);
        root_.load()->insert('{' + w, 0);
       // read_write_counter_.fetch_sub(1);
    });
}

std::future<void> Trie::erase(const std::string& w)
{
    return std::async([this, w](){
       // remove_counter_.fetch_add(1);
       // while (read_write_counter_.load() > 0) {}
        root_.load()->erase('{' + w);
       // remove_counter_.fetch_sub(1);
    });
}
