#include <algorithm>
#include <limits>

#include "trie.hpp"

Trie::TrieNode::TrieNode()
{
    for (unsigned i = 0; i < 27; i++)
        child_[i] = nullptr;
    word_.store(nullptr);
}

Trie::TrieNode::~TrieNode()
{
    if (word_.load() != nullptr)
        delete word_.load();
    for (unsigned i = 0; i < 27; i++)
        if (child_[i].load() != nullptr)
            delete child_[i];
}

std::atomic<Trie::TrieNode*>& Trie::TrieNode::get(char c)
{
    return child_[c - 'a'];
}

const std::atomic<Trie::TrieNode*>& Trie::TrieNode::get(char c) const
{
    return child_[c - 'a'];
}

std::atomic<Trie::TrieNode*>& Trie::TrieNode::get(const std::string& s, unsigned u)
{
    return get(s[u]);
}

const std::atomic<Trie::TrieNode*>& Trie::TrieNode::get(const std::string& s, unsigned u) const
{
    return get(s[u]);
}

void Trie::TrieNode::add(Trie::TrieNode* node, char c)
{
    child_[c - 'a'] = node;
}

void Trie::TrieNode::add(Trie::TrieNode* node, const std::string& s, unsigned u)
{
    add(node, s[u]);
}

bool Trie::TrieNode::is_eow() const
{
    return word_.load() != nullptr;
}

void Trie::TrieNode::word_set(std::string s)
{
    word_.store(new std::string(s));
}

std::string Trie::TrieNode::word_get()
{
    return *word_.load();
}

void Trie::TrieNode::insert(const std::string& s, std::size_t index)
{
    if (index == s.length())
    {
        word_set(s);
        return;
    }
    auto node = get(s, index).load();
    if (node == nullptr)
    {
        node = new TrieNode();
        add(node, s.at(index));
    }
    node->insert(s, index + 1);
}

void Trie::TrieNode::erase(const std::string& s)
{
    if (s.empty())
        word_.store(nullptr);
    else
    {
        char first_char = s.front();
        auto node = get(first_char).load();
        if (node != nullptr)
            node->erase(s.substr(1, s.length() - 1));
    }
}

std::pair<std::string, int> Trie::TrieNode::search(const std::string& s) const
{
    std::string closest = "";
    int distance = std::numeric_limits<int>::max();
    std::size_t sz = s.size();

    // Naive DP initialization
    std::vector<int> current_row(sz + 1);
    for (std::size_t i = 0; i < sz; ++i)
        current_row[i] = i;
    current_row[sz] = sz;

    for (std::size_t i = 0 ; i < sz; ++i) {
        if (get(s[i]).load() != nullptr) {
            std::vector<int> v;
            std::string string = "";
            string += s[i];
            get(s[i]).load()->search_rec(0, current_row, v, s, string, closest, distance);
        }
    }
    return std::pair<std::string, int>(closest, distance);
}

void Trie::TrieNode::search_rec(std::size_t cnt, const std::vector<int>& last_row, const std::vector<int>& llast_row, const std::string& word, const std::string& str, std::string& closest, int& distance)
{
    std::size_t sz = last_row.size();

    std::vector<int> current_row(sz);
    current_row[0] = last_row[0] + 1;

    // Calculate the min cost of insertion, deletion, match or substution
    int insert_or_del, replace;
    for (std::size_t i = 1; i < sz; ++i) {
        int cost = 1;
        if (word[i-1] == str[cnt])
            cost = 0;
        insert_or_del = std::min(current_row[i-1] + 1, last_row[i] + 1);
        replace = last_row[i-1] + cost;

        current_row[i] = std::min(insert_or_del, replace);
    }

    // When we find a cost that is less than the min_cost, is because
    // it is the minimum until the current row, so we update
    if ((current_row[sz-1] < distance) && is_eow()) {
        distance = current_row[sz-1];
        closest = word_get();
    }

//    if i > 1 and j > 1 and a[i] = b[j-1] and a[i-1] = b[j] then
//        d[i, j] := minimum(d[i, j],
//                               d[i-2, j-2] + cost)  // transposition

    // If there is an element wich is smaller than the current minimum cost,
    //  we can have another cost smaller than the current minimum cost
    if (*std::min_element(current_row.begin(), current_row.end()) < distance) {
        for (std::size_t i = 0; i < 27; i++) {
            char val = 'a' + i;
            if (get(val).load() != nullptr)
                get(val).load()->search_rec(cnt + 1, current_row, last_row, word, str + val, closest, distance);
        }
    }
}
