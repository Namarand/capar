#include "trie.hpp"

Trie::TrieNode::TrieNode()
{
    for (unsigned i = 0; i < 26; i++)
        child_[i] = nullptr;
    eow_.store(false);
}

Trie::TrieNode::~TrieNode()
{
    for (unsigned i = 0; i < 26; i++)
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
    return eow_.load();
}

void Trie::TrieNode::eow_set(bool v)
{
    eow_.store(v);
}

void Trie::TrieNode::insert(const std::string& s)
{
    if (s.empty())
    {
        eow_set(true);
        return;
    }
    char first_char = s.front();
    auto node = get(first_char).load();
    if (node == nullptr)
    {
        node = new TrieNode();
        add(node, first_char);
    }
    node->insert(s.substr(1, s.length() - 1));

}

void Trie::TrieNode::erase(const std::string& s)
{
}

std::pair<std::string, int> Trie::TrieNode::search(const std::string& s) const
{
}

