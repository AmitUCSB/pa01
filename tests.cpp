#include "card_list.h"
#include "card.h"
#include <cassert>
#include <iostream>

using namespace std;

void testInsertAndContains() {
    card_list cl;
    Card c1('c', 'a');
    Card c2('d', '2');
    Card c3('s', 'j');
    
    assert(!cl.contains(c1));
    cl.insert(c1);
    assert(cl.contains(c1));
    cl.insert(c2);
    cl.insert(c3);
    assert(cl.contains(c2));
    assert(cl.contains(c3));
    cl.insert(c1);
    assert(cl.contains(c1));

    cout << "testInsertAndContains passed.\n";
}

void testRemove() {
    card_list cl;
    Card c1('c', 'a');
    Card c2('d', '2');

    cl.insert(c1);
    cl.insert(c2);

    cl.remove(c1);
    assert(!cl.contains(c1));
    assert(cl.contains(c2));

    Card c3('s', '5');
    cl.remove(c3); 

    cl.remove(c2);
    assert(!cl.contains(c2));

    cout << "testRemove passed.\n";
}

void testPrintDeck() {
    card_list cl;
    cl.insert(Card('c', 'a'));
    cl.insert(Card('h', 'k'));
    cl.insert(Card('d', '5'));
    cout << "Expected: c a, d 5, h k\nActual:\n";
    cl.printDeck();
    cout << "testPrintDeck completed (manual check for order).\n";
}

void testIterator() {
    card_list cl;
    assert(cl.begin() == cl.end());
    assert(cl.rbegin() == cl.rend());

    Card c('s', 'q');
    cl.insert(c);

    auto it = cl.begin();
    assert(*it == c);
    assert(++it == cl.end());

    auto rit = cl.rbegin();
    assert(*rit == c);
    assert(--rit == cl.rend());

    cout << "testIteratorBasic passed.\n";
}

void testIteratorOdr() {
    card_list cl;
    cl.insert(Card('d', '2'));
    cl.insert(Card('c', 'k'));
    cl.insert(Card('h', '3'));

    string expected[] = {"c k", "d 2", "h 3"};
    int i = 0;
    for (auto it = cl.begin(); it != cl.end(); ++it, ++i) {
        assert(it->toString() == expected[i]);
    }

    string expectedRev[] = {"h 3", "d 2", "c k"};
    i = 0;
    for (auto it = cl.rbegin(); it != cl.rend(); --it, ++i) {
        assert(it->toString() == expectedRev[i]);
    }

    cout << "testIteratorOrdering passed.\n";
}

void testplaygame_match() {
    card_list alice, bob;
    alice.insert(Card('c', 'a'));
    alice.insert(Card('h', '3'));
    bob.insert(Card('c', 'a'));
    bob.insert(Card('s', '5'));

    playGame(alice, bob);
    assert(!alice.contains(Card('c', 'a')));
    assert(!bob.contains(Card('c', 'a')));
    cout << "testPlayGame_MatchingCards passed.\n";
}

void testplaygame_empty() {
    card_list alice, bob;
    alice.insert(Card('d', '9'));
    playGame(alice, bob);
    assert(alice.contains(Card('d', '9')));
    cout << "testPlayGame_OneEmpty passed.\n";
}

void testplaygame_ovrlap() {
    card_list alice, bob;
    alice.insert(Card('c', '2'));
    bob.insert(Card('d', '2'));
    playGame(alice, bob);
    assert(alice.contains(Card('c', '2')));
    assert(bob.contains(Card('d', '2')));
    cout << "testPlayGame_NoOverlap passed.\n";
}

int main() {
    testInsertAndContains();
    testRemove();
    testPrintDeck();
    testIterator();
    testIteratorOdr();
    testplaygame_match();
    testplaygame_empty();
    testplaygame_ovrlap();
    cout << "\nAll tests completed successfully.\n";
    return 0;
}
