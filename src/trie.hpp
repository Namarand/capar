#pragma once

#include <atomic>
#include <optional>
#include <string>

#include "IDictionary.hpp"

class Trie : public IDictionary
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
