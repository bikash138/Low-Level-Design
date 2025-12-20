#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

// We have taken a template to make the datatype generic because we dont know the datatype of the elements that we will be iterating over.
template <typename T>
// First create the Iterator interface
class Iterator
{
public:
  virtual bool hasNext() = 0;
  virtual T next() = 0;
};

// Now lets create a Iterable class
template <typename T>
class Iterable
{
public:
  // This method will return the Iterator type
  virtual Iterator<T> *getIterator() = 0;
};

// Now lets start creating the concrete classes for the Iterables
class LinkedList : public Iterable<int>
{
public:
  int data;
  // Reference of own type because we are creating a linked list
  LinkedList *next;
  // Ctor for the LinkedList
  LinkedList(int value)
  {
    data = value;
    next = nullptr;
  }
  // Override the getIterator method
  Iterator<int> *getIterator() override;
};

class BinaryTree : public Iterable<int>
{
public:
  int data;
  // Reference of own type because we are creating a linked list
  BinaryTree *left;
  BinaryTree *right;
  // Ctor for the LinkedList
  BinaryTree(int value)
  {
    data = value;
    left = nullptr;
    right = nullptr;
  }
  // Override the getIterator method
  Iterator<int> *getIterator() override;
};

// Song class and a Playlist class
class Song
{
public:
  string title;
  string artist;
  Song(const string &t, const string &a)
  {
    title = t;
    artist = a;
  }
};
class Playlist : public Iterable<Song>
{
public:
  vector<Song> songs;
  void addSong(const Song &song)
  {
    songs.push_back(song);
  }
  // Override the getIterator method
  Iterator<Song> *getIterator() override;
};

// Now lets create the concrete classes for the Iterators
class LinkedListIterator : public Iterator<int>
{
private:
  LinkedList *current;

public:
  LinkedListIterator(LinkedList *head)
  {
    current = head;
  }
  bool hasNext() override
  {
    return current != nullptr;
  }
  int next() override
  {
    // Store the current data in a temp variable
    int val = current->data;
    // Update the current to the next node
    current = current->next;
    return val;
  }
};

class BinaryTreeInorderIterator : public Iterator<int>
{
private:
  stack<BinaryTree *> stk;
  BinaryTree *curr;

  void pushLefts(BinaryTree *node)
  {
    while (node)
    {
      stk.push(node);
      node = node->left;
    }
  }

public:
  BinaryTreeInorderIterator(BinaryTree *root)
  {
    curr = root;
    pushLefts(curr);
  }

  bool hasNext() override
  {
    return !stk.empty();
  }

  int next() override
  {
    BinaryTree *node = stk.top();
    stk.pop();
    int val = node->data;
    if (node->right)
    {
      pushLefts(node->right);
    }
    return val;
  }
};

class PlayListIterator : public Iterator<Song> {
  private:
    vector<Song> songs;
    int currentIndex;
  public:
    PlayListIterator(vector<Song> s) {
      songs = s;
      currentIndex = 0;
    }
    bool hasNext() override {
      return currentIndex < songs.size();
    }
    Song next() override {
      return songs[currentIndex++];
    }
};

//Attaching iterators
Iterator<int>* LinkedList::getIterator() {
  return new LinkedListIterator(this);
}
Iterator<int>* BinaryTree::getIterator() {
  return new BinaryTreeInorderIterator(this);
}
Iterator<Song>* Playlist::getIterator() {
  return new PlayListIterator(songs);
}

int main() {
    //------------------------------------------------
    // LinkedList: 1 → 2 → 3
    LinkedList* list = new LinkedList(1);
    list->next = new LinkedList(2);
    list->next->next = new LinkedList(3);
    //Here the list has no idea hoe the iterator works. It just returns the iterator.
    Iterator<int>* iterator1 = list->getIterator();

    cout << "LinkedList contents: ";

    while (iterator1->hasNext()) {
      cout << iterator1->next() << " ";
    }

    cout << "\n";

    //------------------------------------------------

    // BinaryTree:
    //    2
    //   / \
    //  1   3
    BinaryTree* root = new BinaryTree(2);
    root->left  = new BinaryTree(1);
    root->right = new BinaryTree(3);

    Iterator<int>* iterator2 = root->getIterator();

    cout << "BinaryTree inorder: ";

    while (iterator2->hasNext()) {
        cout << iterator2->next() << " ";
    }

    cout << "\n";

    //------------------------------------------------

    // Playlist
    Playlist playlist;
    playlist.addSong(Song("Break up song", "Honey Singh"));
    playlist.addSong(Song("Tum Hi Ho", "Arijit Singh"));

    Iterator<Song>* iterator3 = playlist.getIterator();

    cout << "Playlist songs:\n";

    while (iterator3->hasNext()) {
        Song s = iterator3->next();
        cout << "  " << s.title << " by " << s.artist << "\n";
    }

    //------------------------------------------------

    // Cleanup
    delete list->next->next;
    delete list->next;
    delete list;
    delete root->left;
    delete root->right;
    delete root;

    return 0;
}