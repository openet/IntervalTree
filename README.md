## Building
Compile the project. 
```bash
cmake .
make
```

## Unit Test
Execute google unit test.
```bash
./gtest/runUnitTests
```

## Usage

### Initialise
In this example we initialise IntervalTree::Tree with template <T = std::string>
```c++
IntervalTree::Tree<std::string>* tree = new IntervalTree::Tree<std::string>();
```

### Insert elements
Insert Intervals into the container
```c++
tree->insert(new IntervalTree::Interval(15,20), "v_1");
tree->insert(new IntervalTree::Interval(10,30), "v_2");
tree->insert(new IntervalTree::Interval(17,19), "v_3");
tree->insert(new IntervalTree::Interval(5,20) , "v_4");
tree->insert(new IntervalTree::Interval(12,15), "v_5");
tree->insert(new IntervalTree::Interval(30,40), "v_6");
```

### Query
Finally we invoke std::list<T> get(int point) and it will return all intersecting intervals.
```c++
for (auto v : tree->get(31)) std::cout << v << ",";
std::cout << std::endl;
for (auto v : tree->get(12)) std::cout << v << ",";
std::cout << std::endl;
for (auto v : tree->get(15)) std::cout << v << ",";
std::cout << std::endl;
for (auto v : tree->get(30)) std::cout << v << ",";
std::cout << std::endl;
for (auto v : tree->get(40)) std::cout << v << ",";
std::cout << std::endl;
```

###### output:
```bash
v_6,
v_2,v_4,v_5,
v_1,v_2,v_4,v_5,
v_2,v_6,
v_6,
```

