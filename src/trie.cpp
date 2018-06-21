#include "trie.hpp"

Trie::Trie()
    : root_(new TrieNode())
{}

void Trie::init(const std::vector<std::string>& word_list)
{
    for (auto const s: word_list)
        insert(s);
}

std::future<std::pair<std::string, int>> Trie::search(const std::string& w) const
{
    return std::async([this, w](){
        std::string str = "";
        int min = w.length() + 1;
        root_.load()->dummy_search(w, "", min, str);
        return std::pair<std::string, int>(str, min);
    });
}

std::future<void> Trie::insert(const std::string& w)
{
    return std::async([this, w](){
        root_.load()->insert(w, 0);
    });
}

std::future<void> Trie::erase(const std::string& w)
{
    return std::async([this, w](){
        root_.load()->erase(w, 0);
    });
}
