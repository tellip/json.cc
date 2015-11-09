#include <iostream>
#include "include/json.h"

using namespace aa;

int main() {
    typedef Json<> Json;
    /**
     * template:Json<   Number,     Char,   Array,      Object      >
     * default: Json<   double,     char,   std::deque, std::map    >
     * tested:  Json<   short       char    std::list   std::map    >
     *                  int         wchar_t std::vector
     *                  long                std::deque
     *                  unsigned
     *                  double
     *                  long double
     */

    //constructors
    Json
            j1,                                         //null
            j2 = false,                                   //boolean
            j3 = 1234,                                    //number, here saved as double
            j4 = "hello",                                 //string, here saved as std::string, will be std::wstring when Char is wchar_t
            j5 = Json::parse("[5,1,0]"),                  //array, here is std::deque<Json>
            j6 = Json::parse("{\"hello\":\"json\"}");    //object, here is std::map<const std::string,Json>

    if (j1.isNull()) std::cout << "j1 is null" << std::endl;
    if (j2.isBoolean()) {
        std::cout << "j2 is boolean." << std::endl;
        j2.boolean() = !j2.boolean();
    }
    if (j3.isNumber()) {
        std::cout << "j3 is number." << std::endl;
        j3.number()--; //double
    }
    if (j4.isString()) {
        std::cout << "j4 is string." << std::endl;
        j4.string() += " Use Json<X,wchar_t,X,X> then array will be saved as std::wstring."; //std::string
    }
    if (j5.isArray()) {
        std::cout << "j5 is array." << std::endl;
        j5.array()[1] = 2;
        j5.array().insert(j5.array().begin() + 1, 8); //here 8 is Json(8)
        j5.array().push_back(j6);
    }
    if (j6.isObject()) {
        std::cout << "j6 is object." << std::endl;
        j6.object()["enjoy"] = "json";
        j6.object()["array"] = j5;
        j6.object()["object"]=Json::parse("{\"number\":1234}");
    }

    Json::String jstr = stringify(Json(Json::Array({j1, j2, j3, j4, j5, j6})), 4); //4 is for 4 space indent
    jstr = std::string() + "/* block comments filterd! */" + jstr + "//line comments filtered! ";
    std::cout << jstr << std::endl;

    Json j7 = Json::parse(jstr);
    std::cout << stringify(j7) << std::endl;

    return 0;
}