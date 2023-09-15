#include<unordered_map>
#include<map>
#include<cassert>
#include<iostream>

class myCache
{
  public:
    typedef int fileIDType;
    typedef int priorityType;
    int capacity;
    int size;

    myCache(int _capacity = 10): capacity(_capacity), size(0) {}

  private:
    std::multimap<priorityType, fileIDType, std::greater<priorityType> > _pfmap;
    std::unordered_map<fileIDType, priorityType> _fpmap;

  public:
    void push(const fileIDType &fileID, const priorityType &priority)
    {
      if(size == capacity)
        pop();

      _pfmap.insert({priority, fileID});
      if(_fpmap.find(fileID) != _fpmap.end())
      {
        assert(0 && "Error! Try to push an existing file ID!\n");
      }
      else
      {
        _fpmap[fileID] = priority;
      }
      size++;
    }

    int get_size() const
    {
      return size;
    }

    std::pair<fileIDType, priorityType> pop()
    {
      if(size < 1)
        assert(0 && "Error! Can not pop element since there is nothing in myCache!\n");
      auto it = _pfmap.begin();
      priorityType priority = it->first;
      fileIDType fileID = it->second;
      _pfmap.erase(it);
      _fpmap.erase(fileID);
      size--;
      return std::pair<fileIDType, priorityType>{fileID, priority};
    }

    std::pair<fileIDType, priorityType> top() const
    {
      if(size < 1)
        assert(0 && "Error! Can not find the top element since there is nothing in myCache!\n");
      auto it = _pfmap.begin();
      priorityType priority = it->first;
      fileIDType fileID = it->second;
      return std::pair<fileIDType, priorityType>{fileID, priority};
    }

    void modify(const fileIDType &fileID, const priorityType &priority)
    {
      if(size < 1)
      {
        assert(0 && "Error! Can not modify an empty myCache!\n");
      }
      auto it1 = _fpmap.find(fileID);
      if(it1 == _fpmap.end())
      {
        assert(0 && "Error! When doing modify, can not find element in myCache!\n");
      }
      auto range = _pfmap.equal_range(it1->second);
      _fpmap.erase(it1);
      auto it2 = range.first;
      while(it2 != range.second)
      {
        if(it2->second == fileID)
          break;
        it2++;
      }
      _pfmap.erase(it2);
      size--;
      push(fileID, priority);
    }

    void print() const
    {
      std::cout << "Size = " << get_size() << std::endl;
      std::cout << "Print fpmap: " << std::endl;
      for(const auto &e : _fpmap)
        std::cout << "{ " << e.first << " , " << e.second << " }  ";
      std::cout << std::endl;
      std::cout << "Print pfmap: " << std::endl;
      for(const auto &e : _pfmap)
        std::cout << "{ " << e.first << " , " << e.second << " }  ";
      std::cout << std::endl;
    }
};

void test1()
{
  myCache cache(5);
  cache.print();
  cache.push(100, 3);
  cache.print();
  cache.push(101, 2);
  cache.print();
  cache.push(102, 7);
  cache.print();
  cache.push(103, 4);
  cache.print();
  cache.push(104, 5);
  cache.print();
  cache.push(105, 2);
  cache.print();
  cache.push(106, 3);
  cache.print();
  cache.push(107, 8);
  cache.print();
  cache.modify(101, 11);
  cache.print();
  cache.push(108, 4);
  cache.print();
}

void test2()
{
  myCache cache(6);
  cache.push(100, 3);
  cache.push(101, 3);
  cache.push(102, 3);
  cache.push(103, 3);
  cache.push(104, 5);
  cache.push(105, 5);
  cache.push(106, 5);
  cache.push(107, 5);
  cache.print();
  cache.modify(101, 11);
  cache.print();
  cache.modify(103, 13);
  cache.print();
  cache.modify(105, 15);
  cache.print();
  cache.modify(100, 17);
  cache.print();
}

void test3()
{
  myCache cache(5);
  cache.push(100, 3);
  cache.push(101, 5);
  cache.push(102, 7);
  cache.print();
  cache.pop();
  cache.pop();
  cache.print();
  cache.pop();
  cache.print();
//  cache.pop();
  cache.push(103, 1);
  cache.push(104, 4);
  cache.push(105, 9);
  cache.push(106, 7);
  cache.push(107, 1);
  cache.push(108, 3);
  cache.push(109, 1);
  cache.push(110, 7);
  cache.push(111, 2);
  cache.print();
  cache.modify(111, 11);
  cache.print();
  cache.modify(107, 3);
  cache.print();
  cache.pop();
  cache.print();
  cache.modify(109, 17);
  cache.print();
}

int main()
{
//  test1();
//  test2();
  test3();
}
