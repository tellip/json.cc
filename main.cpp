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
            j6 = Json::parse("{\"hello\":\"cjson\"}");    //object, here is std::map<const std::string,Json>

    if (j1.isNull()) std::cout << "j1 is null" << std::endl;
    if (j2.isBoolean()) {
        std::cout << "j2 is boolean." << std::endl;
        bool &b = j2.boolean();
        b = !b;
    }
    if (j3.isNumber()) {
        std::cout << "j3 is number." << std::endl;
        double &d = j3.number();
        Json::Number &d1 = d;
        d1 = -d1;
    }
    if (j4.isString()) {
        std::cout << "j4 is string." << std::endl;
        std::string &s = j4.string();
        Json::String &s1 = s;
        s1 += " Use Json<X,wchar_t,X,X> then array will be saved as std::wstring.";
    }
    if (j5.isArray()) {
        std::cout << "j5 is array." << std::endl;
        std::deque<Json> &a = j5.array();
        Json::Array &a1 = a;
        a[1] = 2;   //same as: a[1]=Json(8);
        a.insert(a.begin() + 1, 8);    //std::deque operations
    }
    if (j6.isObject()) {
        std::cout << "j6 is object." << std::endl;
        std::map<Json::String, Json> &o = j6.object();
        Json::Object &o1 = o;
        o1.insert(std::pair<Json::String, Json>("hello", "c++"));
        //also can be below:
        o1["enjoy"] = "json";
        o1["more"] = j5;
    }

    Json::Array all = {j1, j2, j3, j4, j5, j6}; //create a deque
    Json::String jstr = stringify(Json(std::move(all)), 4); //4 is for 4 space indent
    jstr = std::string() + "/* block comments filterd! */" + jstr + "//line comments filtered! ";
    std::cout << jstr << std::endl;

    Json j7 = Json::parse(jstr);
    std::cout << stringify(j7) << std::endl;

    return 0;
}