#pragma once

#include <atomic>
#include <optional>
#include <string>
#include <vector>

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
            void insert(const std::string&, std::size_t);
            void erase(const std::string&, std::size_t);
            std::pair<std::string, int> search(const std::string&) const;
            bool is_eow() const;
            void eow_set(bool);
            void add(TrieNode*, char);
            void add(TrieNode*, const std::string&, unsigned);
            void dummy_search(const std::string, const std::string, int&, std::string&);
        private:
            bool exist(const std::string&, std::size_t) const;
            void search_rec(std::size_t, const std::vector<int>&, const std::vector<int>&, const std::string&, const std::string&, std::string&, int&);
            std::atomic<TrieNode*> child_[26];
            std::atomic_bool eow_;
    };
    public:
        Trie();
        virtual void init(const std::vector<std::string>& word_list);
        virtual std::future<result_t> search(const std::string& w) const;
        virtual std::future<void> insert(const std::string& w);
        virtual std::future<void> erase(const std::string& w);

    private:
        std::atomic<TrieNode*> root_;
};
