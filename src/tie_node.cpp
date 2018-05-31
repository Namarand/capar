#include "tie.hpp"

Tie::TieNode::TieNode()
{
    for (unsigned i = 0; i < 26; i++)
        child_[i] = nullptr;
}

Tie::TieNode::~TieNode()
{
    for (unsigned i = 0; i < 26; i++)
        if (child_[i].load() != nullptr)
            delete child_[i];
}

std::atomic<Tie::TieNode*>& Tie::TieNode::get(char c)
{
    return child_[c - 'a'];
}

const std::atomic<Tie::TieNode*>& Tie::TieNode::get(char c) const
{
    return child_[c - 'a'];
}

std::atomic<Tie::TieNode*>& Tie::TieNode::get(const std::string& s, unsigned u)
{
    return get(s[u]);
}

const std::atomic<Tie::TieNode*>& Tie::TieNode::get(const std::string& s, unsigned u) const
{
    return get(s[u]);
}

void Tie::TieNode::add(Tie::TieNode* node, char c)
{
    child_[c - 'a'] = node;
}

void Tie::TieNode::add(Tie::TieNode* node, const std::string& s, unsigned u)
{
    add(node, s[u]);
}

int main(){}
