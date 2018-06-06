#include "tie.hpp"

Trie::TrieNode::TrieNode()
{
    for (unsigned i = 0; i < 26; i++)
        child_[i] = nullptr;
    value_.store(-1);
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

int Trie::TrieNode::value_get() const
{
    return value_.load();
}

void Trie::TrieNode::value_set(int v)
{
    value_.store(v);
}
