#include <iostream>
#include "include.hh"

using Json = json::Json<>;

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

int main() {

    //constructors
    Json
            j1,                                     //null
    j2 = false,                             //boolean
    j3 = 1234,                              //number, here saved as double
    j4 = "hello",                           //string, here saved as std::string, will be std::wstring when char_type is wchar_t
    j5 = {5, 1, 0},                         //array, here is std::list<json>
    j6 = Json::Object{{"hello", "json"}};   //object, here is std::unordered_map<const std::string,json>

    if (j1.is_null()) std::cout << "j1 is null" << std::endl;
    if (j2.is_boolean()) {
        std::cout << "j2 is boolean." << std::endl;
        j2.as_boolean() = !j2.as_boolean();
    }
    if (j3.is_number()) {
        std::cout << "j3 is number." << std::endl;
        j3.as_number()--; //double
    }
    if (j4.is_string()) {
        std::cout << "j4 is string." << std::endl;
        j4.as_string() += ". Use json<X,wchar_t,X,X> then array will be saved as std::wstring."; //std::string
    }
    if (j5.is_array()) {
        std::cout << "j5 is array." << std::endl;
        j5.as_array().front() = 2;
        j5.as_array().insert(std::next(j5.as_array().begin()), 8); //here 8 is json(8)
        j5.as_array().push_back(j6);
    }
    if (j6.is_boolean()) {
        std::cout << "j6 is object." << std::endl;
        j6.as_object()["enjoy"] = "json";
        j6.as_object()["array"] = j5;
        j6.as_object()["object"] = Json::parse("{\"number\":1234}");
    }

    std::string jstr = Json::stringify(Json::Array{j1, j2, j3, j4, j5, j6}, 4); //4 is for 4 space indent
    jstr = std::string() + "/* block comments filterd! */" + jstr + "//line comments filtered! ";
    std::cout << jstr << std::endl;

    Json j7 = Json::parse(jstr);
    std::cout << Json::stringify(j7) << std::endl;

    return 0;
}