#include <iostream>
#include "include/json.h"

using namespace aa;

int main() {
    using json=json<>;
    /**
     * template:json<   number_type,    char_type,  array_type,         object_type             >
     * default: json<   double,         char,       std::deque,         std::map                >
     * tested:  json<   short           char        std::list           std::map                >
     *                  int             wchar_t     std::vector         std::multimap           >
     *                  long                        std::deque          std::unordered_map      >
     *                  unsigned                    std::forward_list   std::unordered_multimap >
     *                  double
     *                  long double
     */

    //constructors
    json
            j1,                                         //null
            j2 = false,                                   //boolean
            j3 = 1234,                                    //number, here saved as double
            j4 = "hello",                                 //string, here saved as std::string, will be std::wstring when char_type is wchar_t
            j5 = json::parse("[5,1,0]"),                  //array, here is std::deque<json>
            j6 = json::parse("{\"hello\":\"json\"}");    //object, here is std::map<const std::string,json>

    if (j1.is_null()) std::cout << "j1 is null" << std::endl;
    if (j2.is_boolean()) {
        std::cout << "j2 is boolean." << std::endl;
        j2.b() = !j2.b();
    }
    if (j3.is_number()) {
        std::cout << "j3 is number." << std::endl;
        j3.n()--; //double
    }
    if (j4.is_string()) {
        std::cout << "j4 is string." << std::endl;
        j4.s() += " Use json<X,wchar_t,X,X> then array will be saved as std::wstring."; //std::string
    }
    if (j5.is_array()) {
        std::cout << "j5 is array." << std::endl;
        j5.a()[1] = 2;
        j5.a().insert(j5.a().begin() + 1, 8); //here 8 is json(8)
        j5.a().push_back(j6);
    }
    if (j6.is_object()) {
        std::cout << "j6 is object." << std::endl;
        j6.o()["enjoy"] = "json";
        j6.o()["array"] = j5;
        j6.o()["object"] = json::parse("{\"number\":1234}");
    }

    std::string jstr = stringify(json(std::deque<json>{j1, j2, j3, j4, j5, j6}), 4); //4 is for 4 space indent
    jstr = std::string() + "/* block comments filterd! */" + jstr + "//line comments filtered! ";
    std::cout << jstr << std::endl;

    json j7 = json::parse(jstr);
    std::cout << stringify(j7) << std::endl;

    return 0;
}