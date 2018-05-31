#pragma once

#include <atomic>
#include <optional>
#include <string>

#include "IDictionary.hpp"

class Tie : public IDictionary
{
    // Inner class
    class TieNode
    {
        public:
            TieNode();
            ~TieNode();
            std::atomic<TieNode*>& get(char);
            const std::atomic<TieNode*>& get(char) const;
            std::atomic<TieNode*>& get(const std::string&, unsigned);
            const std::atomic<TieNode*>& get(const std::string&, unsigned) const;
            intmax_t value_get() const;
            void value_set(intmax_t);
            void add(TieNode*, char);
            void add(TieNode*, const std::string&, unsigned);
        private:
            std::atomic<TieNode*> child_[26];
            std::atomic_intmax_t value_;
    };

    private:
        std::atomic_size_t read_write_counter_;
        std::atomic_size_t remove_counter_;
};
