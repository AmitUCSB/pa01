// card_list.cpp
// Author: Amit Karthikeyan, Neil Gadagkar
// Implementation of the classes defined in card_list.h

#include "card_list.h"
#include "card.h"
#include <iostream>
using namespace std;

card_list::card_list() : root(nullptr) {}

card_list::~card_list() {
    clear(root);
}

void card_list::clear(Node* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

void card_list::insert(const Card& c) {
    root = insert(root, c, nullptr);
}

card_list::Node* card_list::insert(Node* node, const Card& c, Node* parent) {
    if (!node) {
        Node* newNode = new Node(c);
        newNode->parent = parent;
        return newNode;
    }

    if (c < node->info) {
        node->left = insert(node->left, c, node);
    } else if (c > node->info) {
        node->right = insert(node->right, c, node);
    }
    return node;
}

bool card_list::contains(const Card& c) const {
    return find(root, c) != nullptr;
}

card_list::Node* card_list::find(Node* node, const Card& c) const {
    if (!node) return nullptr;
    if (c == node->info) return node;
    if (c < node->info) return find(node->left, c);
    return find(node->right, c);
}

void card_list::remove(const Card& c) {
    root = remove(root, c);
}

card_list::Node* card_list::remove(Node* node, const Card& c) {
    if (!node) return nullptr;

    if (c < node->info) {
        node->left = remove(node->left, c);
    } else if (c > node->info) {
        node->right = remove(node->right, c);
    } else {
        if (!node->left && !node->right) {
            delete node;
            return nullptr;
        } else if (!node->left) {
            Node* r = node->right;
            r->parent = node->parent;
            delete node;
            return r;
        } else if (!node->right) {
            Node* l = node->left;
            l->parent = node->parent;
            delete node;
            return l;
        } else {
            Node* succ = getMin(node->right);
            node->info = succ->info;
            node->right = remove(node->right, succ->info);
        }
    }
    return node;
}

card_list::Node* card_list::getMin(Node* node) const {
    while (node && node->left) node = node->left;
    return node;
}

card_list::Node* card_list::getMax(Node* node) const {
    while (node && node->right) node = node->right;
    return node;
}

void card_list::printDeck() const {
    for (Iterator it = begin(); it != end(); ++it) {
        std::cout << *it << std::endl;
    }
}
card_list::Iterator::Iterator() : current(nullptr) {}

card_list::Iterator::Iterator(Node* ptr) : current(ptr) {}

const Card& card_list::Iterator::operator*() const {
    return current->info;
}

const Card* card_list::Iterator::operator->() const {
    return &(current->info);
}

bool card_list::Iterator::operator==(const Iterator& other) const {
    return current == other.current;
}

bool card_list::Iterator::operator!=(const Iterator& other) const {
    return current != other.current;
}

card_list::Iterator& card_list::Iterator::operator++() {
    current = getSuccessorNode(current);
    return *this;
}

card_list::Iterator& card_list::Iterator::operator--() {
    current = getPredecessorNode(current);
    return *this;
}

card_list::Node* card_list::Iterator::getSuccessorNode(Node* node) const {
    if (node->right) {
        node = node->right;
        while (node->left) node = node->left;
        return node;
    }
    while (node->parent && node == node->parent->right)
        node = node->parent;
    return node->parent;
}

card_list::Node* card_list::Iterator::getPredecessorNode(Node* node) const {
    if (node->left) {
        node = node->left;
        while (node->right) node = node->right;
        return node;
    }
    while (node->parent && node == node->parent->left)
        node = node->parent;
    return node->parent;
}

card_list::Iterator card_list::begin() const {
    return Iterator(getMin(root));
}

card_list::Iterator card_list::end() const {
    return Iterator(nullptr);
}

card_list::Iterator card_list::rbegin() const {
    return Iterator(getMax(root));
}

card_list::Iterator card_list::rend() const {
    return Iterator(nullptr);
}

void playGame(card_list& alice, card_list& bob) {
    bool found = true;

    while (found) {
        found = false;

        for (card_list::Iterator it = alice.begin(); it != alice.end(); ++it) {
            if (bob.contains(*it)) {
                std::cout << "Alice picked matching card " << *it << std::endl;
                bob.remove(*it);
                alice.remove(*it);
                found = true;
                break;
            }
        }

        for (card_list::Iterator it = bob.rbegin(); it != bob.rend(); --it) {
            if (alice.contains(*it)) {
                std::cout << "Bob picked matching card " << *it << std::endl;
                alice.remove(*it);
                bob.remove(*it);
                found = true;
                break;
            }
        }
    }

    std::cout << "\nAlice's cards:" << std::endl;
    alice.printDeck();

    std::cout << "\nBob's cards:" << std::endl;
    bob.printDeck();
}
