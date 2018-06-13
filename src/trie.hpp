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
            void erase(const std::string&);
            std::pair<std::string, int> search(const std::string&) const;
            bool is_eow() const;
            void word_set(std::string);
            std::string word_get();
            void add(TrieNode*, char);
            void add(TrieNode*, const std::string&, unsigned);
        private:
            void search_rec(std::size_t, const std::vector<int>&, const std::vector<int>&, const std::string&, const std::string&, std::string&, int&);
            std::atomic<TrieNode*> child_[27];
            std::atomic<std::string*> word_;
    };
    public:
        Trie();
        virtual void init(const std::vector<std::string>& word_list);
        virtual std::future<result_t> search(const std::string& w) const;
        virtual std::future<void> insert(const std::string& w);
        virtual std::future<void> erase(const std::string& w);

    private:
        std::atomic<TrieNode*> root_;
        mutable std::atomic_size_t read_write_counter_;
        std::atomic_size_t remove_counter_;
};
