#pragma once

#include <atomic>
#include <string>

#include "IDictionary.hpp"

class Tie : public IDictionary
{
    class TieNode
    {
        public:
            TieNode();
            ~TieNode();
            std::atomic<TieNode*>& get(char);
            const std::atomic<TieNode*>& get(char) const;
            std::atomic<TieNode*>& get(const std::string&, unsigned);
            const std::atomic<TieNode*>& get(const std::string&, unsigned) const;
            void add(TieNode*, char);
            void add(TieNode*, const std::string&, unsigned);
        private:
            std::atomic<TieNode*> child_[26];
    };
};
