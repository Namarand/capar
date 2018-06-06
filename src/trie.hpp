#pragma once

#include <atomic>
#include <optional>
#include <string>

#include "IAsyncDictionary.hpp"

class Trie : public IAsyncDictionary
{
    // Inner class
    class TrieNode
    {
        public:
            TrieNode();
            ~TrieNode();
            std::atomic<TrieNode*>& get(char);
            const std::atomic<TrieNode*>& get(char) const;
            std::atomic<TrieNode*>& get(const std::string&, unsigned);
            const std::atomic<TrieNode*>& get(const std::string&, unsigned) const;
            void insert(const std::string&);
            void erase(const std::string&);
            std::pair<std::string, int> search(const std::string&) const;
            int value_get() const;
            void value_set(int);
            void add(TrieNode*, char);
            void add(TrieNode*, const std::string&, unsigned);
        private:
            std::atomic<TrieNode*> child_[26];
            std::atomic_int value_;
    };

    private:
        std::atomic<TrieNode*> root_;
        std::atomic_size_t read_write_counter_;
        std::atomic_size_t remove_counter_;
};
