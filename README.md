### The Json template

Before using the features, you should add this first:

```cpp
#include<.../json.hh>
...
using Json=json::Json<>;

/**
     * template:json<   number_type,        char_type,  array_type,         object_type             >
     * default:         double              char        std::list           std::unordered_map
     * supported:       (unsigned)short     char        std::list           std::map
     *                  (unsigned)int       wchar_t     std::forward_list   std::unordered_map
     *                  (unsigned)long                  std::deque          std::multimap
     *                  (unsigned)long long             std::vector         std::unordered_multimap
     *                  float                           std::deque
     *                  double                          std::set
     *                  long double                     std::multiset
     */
```

### JSON as first-class data type

Here are some examples to give you an idea how to use the class.

Assume you want to create the JSON object

```json
{
  "pi": 3.141,
  "happy": true,
  "name": "Niels",
  "nothing": null,
  "answer": {
    "everything": 42
  },
  "list": [1, 0, 2],
  "object": {
    "currency": "USD",
    "value": 42.99
  }
}
```

With this library, you could write:

```cpp
using Json=json::Json<>;

// create an object that is stored as std::unordered_map (note the storing types can be altered by the template type)
auto j = Json::Object();

// add a number that is stored as double
j["pi"] = 3.141;

// add a Boolean that is stored as bool
j["happy"] = true;

// add a string that is stored as std::string
j["name"] = "Niels";

// add another null object by passing nullptr
j["nothing"] = nullptr;

// add an object inside the object
j["answer"] = Json::Object();
j["answer"].as_object()["everything"] = 42;

// add an array that is stored as std::list
j["list"] = {1, 0, 2};

// add another object
j["object"] = Json::Object{
        {"currency", "USD"},
        {"value",    42.99}
};

// instead, you could also write (which looks very similar to the JSON above)
auto j2 = Json::Object{
        {"pi",      3.141},
        {"happy",   true},
        {"name",    "Niels"},
        {"nothing", nullptr},
        {"answer",  Json::Object{
                {"everything", 42}
        }},
        {"list",    {1, 0, 2}},
        {"object",  Json::Object{
                {"currency", "USD"},
                {"value",    42.99}
        }}
};
```

### STL-like access

I designed the JSON class to behave just like an STL container. In fact, it satisfies the [**ReversibleContainer**](https://en.cppreference.com/w/cpp/named_req/ReversibleContainer) requirement.

```cpp
 Json=json::Json<>;

// create an array using emplace_back
Json::Array j;
j.emplace_back("foo");
j.emplace_back(1);
j.emplace_back(true);

// iterate the array
for (auto &el : j) {
    std::cout << Json::stringify(el) << '\n';
}

// getter/setter
const auto tmp = j.front().as_string();
*std::next(j.begin()) = 42;
bool foo = std::prev(j.cend())->as_boolean();

// other stuff
j.size();     // 3 entries
j.empty();    // false
j.clear();    // the array is empty again

// convenience type checkers
Json jj = j;
jj.is_null();       // false
jj.is_boolean();    // false
jj.is_number();     // false
jj.is_object();     // false
jj.is_array();      // true
jj.is_string();     // false

// create an object
Json::Object o;
o["foo"] = 23;
o["bar"] = false;
o["baz"] = 3.141;

// also use emplace
o.emplace("weather", "sunny");

// special iterator member functions for objects
for (auto &it : o) {
    std::cout << it.first << " : " << Json::stringify(it.second) << "\n";
}

// even easier with structured bindings (C++17)
for (auto&[first, second] : o) {
    std::cout << first << " : " << Json::stringify(second) << "\n";
}

// find an entry
if (o.find("foo") != o.end()) {
    // there is an entry with key "foo"
}

// delete an entry
o.erase("foo");
```
