// card_list.h
// Author: Amit Karthikeyan, Neil Gadagkar
// All class declarations related to defining a BST that represents a player's hand
#ifndef CARD_LIST_H
#define CARD_LIST_H


#include "card.h"

class card_list {
    public:
        card_list();
        ~card_list();
        void insert(const Card& c);
        void remove(const Card& c);
        bool contains(const Card& c) const;
        void printDeck() const;
        class Iterator;
        Iterator begin() const;
        Iterator end() const;
        Iterator rbegin() const;
        Iterator rend() const;
    
    private:
        struct Node {
            Card info;
            Node* left;
            Node* right;
            Node* parent;
            Node(const Card& c) : info(c), left(nullptr), right(nullptr), parent(nullptr) {}
    };
        Node* root;
    
        Node* insert(Node* node, const Card& c, Node* parent);
        Node* find(Node* node, const Card& c) const;
        Node* getMin(Node* node) const;
        Node* getMax(Node* node) const;
        Node* remove(Node* node, const Card& c);
        void clear(Node* node);
    };

    class card_list::Iterator {
        public:
            Iterator();
            Iterator(Node* ptr);
            const Card& operator*() const;
            const Card* operator->() const;
            Iterator& operator++();  
            Iterator& operator--(); 
            bool operator==(const Iterator& other) const;
            bool operator!=(const Iterator& other) const;
        
        private:
            Node* current;
            Node* getSuccessorNode(Node* node) const;
            Node* getPredecessorNode(Node* node) const;
        };


void playGame(card_list& alice, card_list& bob);
        
#endif